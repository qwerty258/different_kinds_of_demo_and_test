
// PSDecoderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PSDecoder.h"
#include "PSDecoderDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPSDecoderDlg dialog



CPSDecoderDlg::CPSDecoderDlg(CWnd* pParent /*=NULL*/):CDialogEx(CPSDecoderDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_result = 0;
}

void CPSDecoderDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPSDecoderDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_BUTTON_PLAY, &CPSDecoderDlg::OnClickedButtonPlay)
END_MESSAGE_MAP()


// CPSDecoderDlg message handlers

BOOL CPSDecoderDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);			// Set big icon
    SetIcon(m_hIcon, FALSE);		// Set small icon

    // TODO: Add extra initialization here
    av_register_all();

    m_p_PS_data_file = fopen("D:\\test.dat", "rb");
    m_p_PS_data_size_file = fopen("D:\\PSdataSize", "rb");

    fseek(m_p_PS_data_file, 0, SEEK_END);
    fseek(m_p_PS_data_size_file, 0, SEEK_END);

    m_PS_data_size = ftell(m_p_PS_data_file);
    m_PS_data_size_size = ftell(m_p_PS_data_size_file);

    m_p_buffer = (uint8_t*)malloc(m_PS_data_size);
    m_p_PS_data_size = (uint32_t*)malloc(m_PS_data_size_size);

    rewind(m_p_PS_data_file);
    rewind(m_p_PS_data_size_file);

    fread(m_p_buffer, m_PS_data_size, 1, m_p_PS_data_file);
    fread(m_p_PS_data_size, m_PS_data_size_size, 1, m_p_PS_data_size_file);

    fclose(m_p_PS_data_file);
    fclose(m_p_PS_data_size_file);

    m_p_iobuffer = (uint8_t*)av_malloc(4096);

    m_p_AVIOContext = avio_alloc_context(
        m_p_iobuffer,
        4096,
        0,
        this,
        fill_iobuffer,
        NULL,
        NULL);

    m_p_fmt_ctx = avformat_alloc_context();

    m_p_fmt_ctx->pb = m_p_AVIOContext;

    m_p_buffer_current_position = m_p_buffer;

    m_result = avformat_open_input(&m_p_fmt_ctx, m_p_fmt_ctx->filename, NULL, NULL);

    m_result = avformat_find_stream_info(m_p_fmt_ctx, NULL);

    for(unsigned int i = 0; i < m_p_fmt_ctx->nb_streams; i++)
    {
        if(AVMEDIA_TYPE_VIDEO == m_p_fmt_ctx->streams[i]->codec->codec_type)
        {
            m_AVCodecID = m_p_fmt_ctx->streams[i]->codec->codec_id;
            m_video_stream_index = i;
        }
        if(AVMEDIA_TYPE_AUDIO == m_p_fmt_ctx->streams[i]->codec->codec_type)
        {
            m_AVCodecID_audio = m_p_fmt_ctx->streams[i]->codec->codec_id;
            m_audio_stream_index = i;
        }
    }

    m_playing_HWND = GetDlgItem(IDC_PICTURE_AREA)->m_hWnd;

    return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPSDecoderDlg::OnPaint()
{
    if(IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPSDecoderDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}


BOOL CPSDecoderDlg::DestroyWindow()
{
    // TODO: Add your specialized code here and/or call the base class

    m_loop = FALSE;

    WaitForSingleObject(m_thread_handle, INFINITE);
    CloseHandle(m_thread_handle);

    avformat_close_input(&m_p_fmt_ctx);

    free(m_p_buffer);
    free(m_p_PS_data_size);

    return CDialogEx::DestroyWindow();
}

int readover;

int fill_iobuffer(void* opaque, uint8_t* buf, int bufSize)
{
    if(!readover)
    {
        CPSDecoderDlg* p_CPSDecoderDlg = (CPSDecoderDlg*)opaque;
        return p_CPSDecoderDlg->ReadMemory(buf, bufSize);
        readover = 1;
    }
    else
    {
        return 0;
    }
}

int CPSDecoderDlg::ReadMemory(uint8_t* buf, int bufSize)
{
    int leftover = m_PS_data_size - (m_p_buffer_current_position - m_p_buffer);
    if(leftover > 0 && leftover < bufSize)
    {
        memcpy(buf, m_p_buffer_current_position, leftover);
        m_p_buffer_current_position = m_p_buffer;
        return leftover;
    }
    else
    {
        memcpy(buf, m_p_buffer_current_position, bufSize);
        m_p_buffer_current_position += bufSize;
        return bufSize;
    }
}

DWORD WINAPI decoding_thread(LPVOID lpParam)
{
    int got_picture;
    AVPacket* pAVPacket = (AVPacket*)av_malloc(sizeof(AVPacket));
    CPSDecoderDlg* pCPSDecoderDlg = (CPSDecoderDlg*)lpParam;
    AVCodec* pCodec = avcodec_find_decoder(pCPSDecoderDlg->m_AVCodecID);
    AVCodec* pCodecAudio = avcodec_find_decoder(pCPSDecoderDlg->m_AVCodecID_audio);
    AVCodecContext* pCodecCtx = pCPSDecoderDlg->m_p_fmt_ctx->streams[pCPSDecoderDlg->m_video_stream_index]->codec;
    AVCodecContext* pCodecCtxAudio = pCPSDecoderDlg->m_p_fmt_ctx->streams[pCPSDecoderDlg->m_audio_stream_index]->codec;
    AVFrame* pFrame = av_frame_alloc();
    AVFrame* pFrameAudio = av_frame_alloc();

    uint8_t* RGB24Data[4];
    int RGB24Linesize[4];
    got_picture = av_image_alloc(RGB24Data, RGB24Linesize, pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_RGB24, 4);
    struct SwsContext* img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_RGB24, SWS_FAST_BILINEAR, NULL, NULL, NULL);

    BITMAPINFO bmpinfo;
    memset(&bmpinfo, 0x0, sizeof(BITMAPINFOHEADER));
    bmpinfo.bmiHeader.biBitCount = 24;
    bmpinfo.bmiHeader.biClrImportant = 0;
    bmpinfo.bmiHeader.biClrUsed = 0;
    bmpinfo.bmiHeader.biCompression = BI_RGB;
    bmpinfo.bmiHeader.biHeight = pCodecCtx->height;
    bmpinfo.bmiHeader.biPlanes = 1;
    bmpinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmpinfo.bmiHeader.biSizeImage = pCodecCtx->width * pCodecCtx->height * 3;
    bmpinfo.bmiHeader.biWidth = pCodecCtx->width;
    bmpinfo.bmiHeader.biXPelsPerMeter = 0;
    bmpinfo.bmiHeader.biYPelsPerMeter = 0;

    int PlayingWidth;
    int PlayingHeight;

    RECT rect;
    GetWindowRect(pCPSDecoderDlg->m_playing_HWND, &rect);
    PlayingWidth = rect.right - rect.left;
    PlayingHeight = rect.bottom - rect.top;

    HDC hDC = GetDC(pCPSDecoderDlg->m_playing_HWND);
    got_picture = SetStretchBltMode(hDC, COLORONCOLOR);

    got_picture = avcodec_open2(pCodecCtx, pCodec, NULL);
    got_picture = avcodec_open2(pCodecCtxAudio, pCodecAudio, NULL);

    uint8_t* p_uint8_t_temp;

    while(pCPSDecoderDlg->m_loop)
    {
        Sleep(40);
        av_read_frame(pCPSDecoderDlg->m_p_fmt_ctx, pAVPacket);
        if(pAVPacket->stream_index == pCPSDecoderDlg->m_video_stream_index)
        {
            avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, pAVPacket);
            if(got_picture)
            {
                p_uint8_t_temp = pFrame->data[1];
                pFrame->data[1] = pFrame->data[2];
                pFrame->data[2] = p_uint8_t_temp;
                pFrame->data[0] += pFrame->linesize[0] * (pCodecCtx->height - 1);
                pFrame->linesize[0] *= -1;
                pFrame->data[1] += pFrame->linesize[1] * (pCodecCtx->height / 2 - 1);
                pFrame->linesize[1] *= -1;
                pFrame->data[2] += pFrame->linesize[2] * (pCodecCtx->height / 2 - 1);
                pFrame->linesize[2] *= -1;
                got_picture = sws_scale(img_convert_ctx, pFrame->data, pFrame->linesize, 0, pCodecCtx->height, RGB24Data, RGB24Linesize);
                got_picture = StretchDIBits(hDC, 0, 0, PlayingWidth, PlayingHeight, 0, 0, pCodecCtx->width, pCodecCtx->height, RGB24Data[0], (BITMAPINFO*)&bmpinfo, DIB_RGB_COLORS, SRCCOPY);
            }
        }
        if(pAVPacket->stream_index == pCPSDecoderDlg->m_audio_stream_index)
        {
            avcodec_decode_audio4(pCodecCtxAudio, pFrameAudio, &got_picture, pAVPacket);
            if(got_picture)
            {
                got_picture = 1;
            }
        }

        av_free_packet(pAVPacket);
    }

    sws_freeContext(img_convert_ctx);
    av_freep(&RGB24Data[0]);
    av_frame_free(&pFrame);
    av_frame_free(&pFrameAudio);
    avcodec_close(pCodecCtx);
    avcodec_close(pCodecCtxAudio);

    ReleaseDC(pCPSDecoderDlg->m_playing_HWND, hDC);

    return 0;
}

void CPSDecoderDlg::OnClickedButtonPlay()
{
    m_loop = TRUE;
    m_thread_handle = CreateThread(NULL, 0, decoding_thread, this, 0, &m_thread_ID);
}
