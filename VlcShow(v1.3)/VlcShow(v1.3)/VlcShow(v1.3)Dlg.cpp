// VlcShow(v1.3)Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "VlcShow(v1.3).h"
#include "VlcShow(v1.3)Dlg.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#include <SDL_mutex.h>
#include <vlc\vlc.h>
#include <windows.h>
#include "H264check.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



typedef struct ctx
{
    SDL_Surface *surf;
    SDL_mutex *mutex;

} pctx;

  libvlc_media_player_t *mp; 
  libvlc_instance_t * inst;
  int surfaceIndex=0;
  pctx ctx;

static void *lock(void *data, void **p_pixels)
{
	if (data==NULL) return NULL;
	pctx* ctx = (pctx *)data;
	SDL_LockMutex(ctx->mutex);
	SDL_LockSurface(ctx->surf);
	*p_pixels = ctx->surf->pixels;
	char filename[255];
	surfaceIndex++;
	sprintf_s(filename,255,"%s%d.bmp","c:\\bmpLib\\",surfaceIndex);
	::SDL_SaveBMP(ctx->surf,filename);
    return NULL; /* picture identifier, not needed here */
}
static void unlock(void *data, void *id, void *const *p_pixels)
{
    return ;
}

static void display(void *data, void *id)
{
 return;
}




// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CVlcShowv13Dlg dialog




CVlcShowv13Dlg::CVlcShowv13Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVlcShowv13Dlg::IDD, pParent)
	, filenameEdt(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVlcShowv13Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, filenameEdt);
}

BEGIN_MESSAGE_MAP(CVlcShowv13Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CVlcShowv13Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CVlcShowv13Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CVlcShowv13Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDCANCEL, &CVlcShowv13Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON3, &CVlcShowv13Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CVlcShowv13Dlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CVlcShowv13Dlg message handlers

BOOL CVlcShowv13Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}
void video_lock_cb(void *opaque, void **planes)
{
	//::MessageBox(0,L"ok",L"ok",MB_OK);
	return ;
}
void video_unlock_cb(void *opaque, void *picture,void *const *planes)
{
  return ;
}
void video_display_cb(void *opaque, void *picture)
{
	return;
}
void CVlcShowv13Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVlcShowv13Dlg::OnPaint()
{
	if (IsIconic())
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVlcShowv13Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CVlcShowv13Dlg::OnBnClickedOk()
{
    //libvlc_media_player_t *mp;
   //  libvlc_instance_t * inst;
     libvlc_media_t *m;
    
	  

   //const char * const vlc_args[] = {
   //           "-I", "dummy", /* Don't use any interface */
   //           "--ignore-config", /* Don't use VLC's config */
   //           "--vout directx",
   //           "--plugin-path=C:\Program Files\VideoLAN\VLC\plugins" };

     /* Load the VLC engine */
     inst = libvlc_new (0, NULL);
	 char filename[255];
	 ::GetDlgItemTextA(CVlcShowv13Dlg::m_hWnd,IDC_EDIT1,filename,sizeof(filename));
//	 char timeStr[255];
//     GetDlgItemTextA(CVlcShowv13Dlg::m_hWnd,IDC_EDIT2,timeStr,sizeof(timeStr));
//	 long times=atoi(timeStr);
	
//	 memcpy(filename,filenameEdt,filenameEdt.GetLength());
     //inst = libvlc_new(1, vlc_args);
     /* Create a new item */
	 //play video Remove pc 
	 // m = libvlc_media_new_path (inst, "rtsp://192.168.0.168:8557/PSIA/Streaming/channels/2?videoCodecType=H.264");
	 //play video Local file
	
	 //m = libvlc_media_new_path (inst, "rtsp://192.168.0.221");   
      m = libvlc_media_new_path (inst,filename);   
	 /* Create a media player playing environement */
     mp = libvlc_media_player_new_from_media (m);
     
     /* No need to keep the media now */
     libvlc_media_release (m);
 
 #if 1
     /* This is a non working code that show how to hooks into a window,
      * if we have a window around */
	// libvlc_drawable_t drawable = (libvlc_drawable_t)(GetDlgItem(IDC_STATIC)->GetSafeHwnd());
      //libvlc_media_player_set_xdrawable (mp, xdrawable);
     /* or on windows */
	 HWND hd=GetDlgItem(IDC_STATIC)->m_hWnd;
	 libvlc_media_player_set_hwnd (mp, hd);
     /* or on mac os */
     // libvlc_media_player_set_nsobject (mp, view);
#endif
     /* play the media_player */
	 //libvlc_video_set_callbacks(mp,lock, unlock, display, &ctx);
     // libvlc_video_set_format(mp, "RV16", 20, 10, 40);

     libvlc_media_player_play (mp);
	// libvlc_media_player_set_time(mp,times);
	// float f_speed=0.1;
 //   libvlc_media_player_set_rate(mp,f_speed); 
     Sleep (10); /* Let it play a bit */
	 //libvlc_video_take_snapshot(mp,0,"C:\VLCBMP",100,100);
     /* Stop playing */
     // libvlc_media_player_stop (mp);
     /* Free the media_player */
     // libvlc_media_player_release (mp);
     //libvlc_release (inst);
     return ;
 
}

void CVlcShowv13Dlg::OnBnClickedButton1()
{
		 float f_speed=0.1;
    libvlc_media_player_set_rate(mp,f_speed); 
	// TODO: Add your control notification handler code here
	//Get png format picture file 
	//Only need Directory ,fileName will auto Declare;
	//libvlc_video_take_snapshot(mp,0,"C:\\VLCBMP",0,0);
	//unsigned int st=0x00000003;
	//unsigned int bin=0xFFFFFFF1;
	//unsigned int doi=st & bin;
	//doi++;
	//return ;

	//char *filename="c:\\3.h264";
	//int st2=setbeginTime(filename,1);
	//BYTE *buf;
	//buf= new BYTE[st2];
	//FILE *f1=fopen(filename,"rb");
 //   FILE *f2=fopen("c:\\set264Time.H264","wb");
	//fseek(f1,0,0);
	//fread(buf,1,st2,f1);
	//fwrite(buf,1,st2,f2);
	//int st=setbeginPoint(filename,150);
	//fseek(f1,0,SEEK_END);
	//long fsize=ftell(f1);
	//fseek(f1,st,0);
	//BYTE *pbuf;
	//pbuf=new BYTE[fsize-st];
	//fread(pbuf,1,fsize-st,f1);
	//fclose(f1);
	//fwrite(pbuf,1,fsize-st,f2);
	//fclose(f2);
	return ;
	//FILE *f1=fopen("c:\\3.H264","rb");
	//fseek(f1,0,SEEK_END);
	//long fsize=ftell(f1);
	//fseek(f1,0,0);
	//BYTE *pbuf;
	//pbuf=new BYTE[fsize];
	//fread(pbuf,1,fsize,f1);
	//fclose(f1);
 //   ParseContext *p1= new ParseContext;
	////memset(p1,0,sizeof(ParseContext));
	//p1->FrameStartFound=1;
	//p1->iFrameLength=0;
	//DecLoadAU((unsigned char *)pbuf,fsize,1,p1);
 //   BYTE * bufpoint;
	//FILE *f2=fopen("c:\\set264Time.H264","wb");
	////fwrite(pbuf,1,p1->iFrameLength,f2);//FT，貌似要拷贝头文件
	//DecLoadAUEx((unsigned char *)pbuf+p1->iFrameLength,fsize,100,p1);
 //   bufpoint=pbuf+p1->iFrameLength-1;
 //   fwrite(bufpoint,1,fsize-p1->iFrameLength-1,f2);
	//fclose(f2);
	//libvlc_video_set_callbacks(mp,video_lock_cb,&video_unlock_cb,&video_display_cb,pbuf);
}

void CVlcShowv13Dlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	 /* Stop playing */
     libvlc_media_player_stop (mp);
     /* Free the media_player */
     libvlc_media_player_release (mp);
     libvlc_release (inst);
}



void CVlcShowv13Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	 SYSTEM_INFO SystemInfo;
	 GetSystemInfo(&SystemInfo);  
	 int pn=SystemInfo.dwNumberOfProcessors;
	 DWORD s1,s2;
	::GetProcessAffinityMask(::GetCurrentProcess(),&s1,&s2);
	s1++;
	::SetProcessAffinityMask(::GetCurrentProcess(),s1);
}

void CVlcShowv13Dlg::OnBnClickedButton3()
{
    CFileDialog fileDlg(TRUE);
	if(IDOK==fileDlg.DoModal())
	{
	  filenameEdt =fileDlg.GetPathName();
	}
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
}

void CVlcShowv13Dlg::OnBnClickedButton4()
{
			 float f_speed=2;
    libvlc_media_player_set_rate(mp,f_speed); 
	// TODO: Add your control notification handler code here
}
