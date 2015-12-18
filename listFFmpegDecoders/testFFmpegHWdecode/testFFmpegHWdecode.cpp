// testFFmpegHWdecode.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "testFFmpegHWdecode.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <libavcodec\avcodec.h>
#include <libavformat\avformat.h>
#include <libswscale\swscale.h>
#include <libavutil\avutil.h>

#ifdef __cplusplus
}
#endif

typedef struct
{
    BOOL bLoop;
    HWND hWnd;
}ThreadParameter;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
TCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND hWnd;

AVHWAccel* p_g_AVHWAccel = NULL;
AVCodec* p_g_AVCodec = NULL;
AVCodecContext* p_g_AVCodecContext = NULL;
SwsContext* p_g_SwsContext_for_RGB = NULL;

int window_width;
int window_hight;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

DWORD WINAPI DecodeThread(LPVOID lpParam)
{
    AVPacket AVPacketH264Packet;
    ThreadParameter* pThreadParameter = static_cast<ThreadParameter*>(lpParam);
    AVFrame* p_AVFrame_for_decode = av_frame_alloc();
    AVFrame* p_AVFrame_for_RGB = av_frame_alloc();

    AVFrame* p_AVFrame_test = av_frame_alloc();
    uint8_t* buf = (uint8_t*)av_malloc(avpicture_get_size(AV_PIX_FMT_NV12, 1920, 1080));
    avpicture_fill(
        (AVPicture*)p_AVFrame_test,
        buf,
        AV_PIX_FMT_NV12,
        1280,
        720);
    av_freep(&buf);
    av_frame_free(&p_AVFrame_test);

    BITMAPINFO bitmap_info;
    HDC hDC = GetDC(pThreadParameter->hWnd);
    SetStretchBltMode(hDC, COLORONCOLOR);

    p_g_AVCodec = avcodec_find_decoder_by_name("h264_qsv");
    p_g_AVCodecContext = avcodec_alloc_context3(p_g_AVCodec);

    do
    {
        p_g_AVHWAccel = av_hwaccel_next(p_g_AVHWAccel);
        if(0 == strncmp(p_g_AVHWAccel->name, "h264_dxva2", 30))
        {
            break;
        }
    } while(NULL != p_g_AVHWAccel);

    p_g_AVCodecContext->hwaccel = p_g_AVHWAccel;

    if(0 > avcodec_open2(p_g_AVCodecContext, p_g_AVCodec, NULL))
    {
        return 0;
    }

    FILE* pDataFile = fopen("test_video_data.h264", "rb");
    FILE* pSizeFile = fopen("test_video_size", "rb");

    fseek(pDataFile, 0, SEEK_END);
    fseek(pSizeFile, 0, SEEK_END);

    int test_video_data_file_size = ftell(pDataFile);
    int test_video_size_file_size = ftell(pSizeFile);

    rewind(pDataFile);
    rewind(pSizeFile);

    unsigned int* size = new unsigned int[test_video_size_file_size / 4];
    char* buffer = new char[test_video_data_file_size];

    fread(size, test_video_size_file_size, 1, pSizeFile);
    fread(buffer, test_video_data_file_size, 1, pDataFile);

    fclose(pSizeFile);
    fclose(pDataFile);

    unsigned int CurrentPos = 0;
    unsigned int DataJumpBytes = 0;
    int got_picture;
    bool first_round = true;

    while(pThreadParameter->bLoop)
    {
        av_init_packet(&AVPacketH264Packet);

        AVPacketH264Packet.size = size[CurrentPos];
        AVPacketH264Packet.data = (uint8_t*)(buffer + DataJumpBytes);

        if(0 > avcodec_decode_video2(p_g_AVCodecContext, p_AVFrame_for_decode, &got_picture, &AVPacketH264Packet))
        {
            break;
        }

        if(first_round)
        {
            p_g_SwsContext_for_RGB = sws_getContext(
                p_g_AVCodecContext->width,
                p_g_AVCodecContext->height,
                p_g_AVCodecContext->pix_fmt,
                p_g_AVCodecContext->width,
                p_g_AVCodecContext->height,
                AV_PIX_FMT_BGR24,
                SWS_BILINEAR,
                NULL,
                NULL,
                NULL);

            bitmap_info.bmiColors->rgbBlue = 0;
            bitmap_info.bmiColors->rgbGreen = 0;
            bitmap_info.bmiColors->rgbRed = 0;
            bitmap_info.bmiColors->rgbReserved = 0;

            bitmap_info.bmiHeader.biBitCount = 24;
            bitmap_info.bmiHeader.biClrImportant = 0;
            bitmap_info.bmiHeader.biClrUsed = 0;
            bitmap_info.bmiHeader.biCompression = BI_RGB;
            bitmap_info.bmiHeader.biHeight = p_g_AVCodecContext->height;
            bitmap_info.bmiHeader.biPlanes = 1;
            bitmap_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            bitmap_info.bmiHeader.biSizeImage = (p_g_AVCodecContext->width * 24 + 31) / 32 * 4 * p_g_AVCodecContext->height;
            bitmap_info.bmiHeader.biWidth = p_g_AVCodecContext->width;
            bitmap_info.bmiHeader.biXPelsPerMeter = 100;
            bitmap_info.bmiHeader.biYPelsPerMeter = 100;

            if(0 > avpicture_alloc((AVPicture*)p_AVFrame_for_RGB, AV_PIX_FMT_BGR24, p_g_AVCodecContext->width, p_g_AVCodecContext->height))
            {
                break;
            }

            first_round = false;
        }

        p_AVFrame_for_decode->data[0] += (p_AVFrame_for_decode->linesize[0] * (p_AVFrame_for_decode->height - 1));
        p_AVFrame_for_decode->linesize[0] *= -1;
        p_AVFrame_for_decode->data[1] += (p_AVFrame_for_decode->linesize[1] * (p_AVFrame_for_decode->height / 2 - 1));
        p_AVFrame_for_decode->linesize[1] *= -1;
        p_AVFrame_for_decode->data[2] += (p_AVFrame_for_decode->linesize[2] * (p_AVFrame_for_decode->height / 2 - 1));
        p_AVFrame_for_decode->linesize[2] *= -1;


        sws_scale(
            p_g_SwsContext_for_RGB,
            p_AVFrame_for_decode->data,
            p_AVFrame_for_decode->linesize,
            0,
            p_g_AVCodecContext->height,
            p_AVFrame_for_RGB->data,
            p_AVFrame_for_RGB->linesize);

        StretchDIBits(
            hDC,
            0,
            0,
            window_width,
            window_hight,
            0,
            0,
            p_g_AVCodecContext->width,
            p_g_AVCodecContext->height,
            p_AVFrame_for_RGB->data[0],
            &bitmap_info,
            DIB_RGB_COLORS,
            SRCCOPY);

        DataJumpBytes += size[CurrentPos];
        CurrentPos++;
        if(CurrentPos >= test_video_size_file_size / 4)
        {
            CurrentPos = 0;
            DataJumpBytes = 0;
        }
    }

    avpicture_free((AVPicture*)p_AVFrame_for_RGB);

    av_frame_free(&p_AVFrame_for_decode);
    av_frame_free(&p_AVFrame_for_RGB);

    delete[] buffer;
    delete[] size;

    avcodec_free_context(&p_g_AVCodecContext);

    ReleaseDC(pThreadParameter->hWnd, hDC);

    return 0;
}

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    MSG msg;
    HACCEL hAccelTable;

    // Initialize global strings
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_TESTFFMPEGHWDECODE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if(!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTFFMPEGHWDECODE));

    av_register_all();
    ThreadParameter structThreadParameter;
    structThreadParameter.bLoop = TRUE;
    structThreadParameter.hWnd = hWnd;

    DWORD dDecodeThreadID;
    HANDLE hDecodeThread;

    hDecodeThread = CreateThread(NULL, 0, DecodeThread, &structThreadParameter, 0, &dDecodeThreadID);

    // Main message loop:
    while(GetMessage(&msg, NULL, 0, 0))
    {
        if(!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    structThreadParameter.bLoop = FALSE;

    WaitForSingleObject(hDecodeThread, INFINITE);

    return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTFFMPEGHWDECODE));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCE(IDC_TESTFFMPEGHWDECODE);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

    if(!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rect_temp;

    switch(message)
    {
        case WM_COMMAND:
            wmId = LOWORD(wParam);
            wmEvent = HIWORD(wParam);
            // Parse the menu selections:
            switch(wmId)
            {
                case IDM_ABOUT:
                    DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                    break;
                case IDM_EXIT:
                    DestroyWindow(hWnd);
                    break;
                default:
                    return DefWindowProc(hWnd, message, wParam, lParam);
            }
            break;
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code here...
            EndPaint(hWnd, &ps);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_SIZE:
            GetWindowRect(hWnd, &rect_temp);
            window_width = rect_temp.right - rect_temp.left;
            window_hight = rect_temp.bottom - rect_temp.top;
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch(message)
    {
        case WM_INITDIALOG:
            return (INT_PTR)TRUE;

        case WM_COMMAND:
            if(LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
            {
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
            break;
    }
    return (INT_PTR)FALSE;
}
