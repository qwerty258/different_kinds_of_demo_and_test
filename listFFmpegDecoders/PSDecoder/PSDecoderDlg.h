
// PSDecoderDlg.h : header file
//

#pragma once

#ifdef __cplusplus
extern "C" {
#endif // _cplusplus
#include <libavformat\avformat.h>
#include <libswscale\swscale.h>
#include <libavutil\imgutils.h>
#ifdef __cplusplus
}
#endif // _cplusplus

// CPSDecoderDlg dialog
class CPSDecoderDlg : public CDialogEx
{
    // Construction
public:
    CPSDecoderDlg(CWnd* pParent = NULL);	// standard constructor

    // Dialog Data
    enum
    {
        IDD = IDD_PSDECODER_DIALOG
    };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


    // Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
private:
    FILE* m_p_PS_data_file;
    FILE* m_p_PS_data_size_file;
    uint8_t* m_p_buffer;
    uint8_t* m_p_buffer_current_position;
    uint32_t* m_p_PS_data_size;
    uint32_t m_PS_data_size;
    uint32_t m_PS_data_size_size;
    uint8_t* m_p_iobuffer;
public:
    AVIOContext* m_p_AVIOContext;
    int m_result;
    enum AVCodecID m_AVCodecID;
    enum AVCodecID m_AVCodecID_audio;
    unsigned int m_video_stream_index;
    unsigned int m_audio_stream_index;
    AVFormatContext* m_p_fmt_ctx;
    BOOL m_loop;
    HANDLE m_thread_handle;
    DWORD m_thread_ID;
    HWND m_playing_HWND;
    virtual BOOL DestroyWindow();
    int ReadMemory(uint8_t* buf, int bufSize);
    afx_msg void OnClickedButtonPlay();
};

int fill_iobuffer(void* opaque, uint8_t* buf, int bufSize);