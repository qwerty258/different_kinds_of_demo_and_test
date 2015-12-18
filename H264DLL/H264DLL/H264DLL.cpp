// H264DLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
extern "C" 
{
#include <stdint.h>
#include <x264.h>
};

typedef struct
{
	int width;
	int height;
	int fps;
}paramInput;

unsigned int g_uiPTSFactor = 0;
unsigned int uiComponent = 0;
int iNal = 0;
x264_nal_t* pNals = NULL;
int iResult = 0,iDataLen=0,filesize=0;
x264_t* pX264Handle = NULL;
x264_picture_t* pPicIn ;
x264_picture_t* pPicOut;

//初始化DLL参数
//==0 success ，<0 false 
extern __declspec(dllexport) int InitDLL(paramInput *paramUser)
{
    x264_param_t* pX264Param = new x264_param_t;
	x264_param_default_preset(pX264Param, "ultrafast", "zerolatency");
	pX264Param->i_threads =1;
	pX264Param->i_width = paramUser->width; //* 宽度.
	pX264Param->i_height =paramUser->height ; //* 高度
	pX264Param->i_keyint_min=5;
    pX264Param->i_keyint_max=2;
	//pX264Param->i_bframe_pyramid = 0;
	//pX264Param->i_bframe_adaptive = X264_B_ADAPT_TRELLIS;
	pX264Param->i_bframe = 16;  //I和P之间的B帧数 
	pX264Param->rc.i_bitrate = 40960;
	pX264Param->rc.i_rc_method =X264_RC_CRF;
	//pX264Param->b_intra_refresh = 1;
	pX264Param->i_fps_den = 1; //* 帧率分母
	pX264Param->i_fps_num = paramUser->fps; //* 帧率分子
	x264_param_apply_profile(pX264Param, x264_profile_names[0]);
	//* 打开编码器句柄,通过x264_encoder_parameters得到设置给X264
	//* 的参数.通过x264_encoder_reconfig更新X264的参数
	pX264Handle = x264_encoder_open(pX264Param);
	if (pX264Handle==NULL)
	{
		return -1;
	}
	//* 获取整个流的PPS和SPS,不需要可以不调用.
	iResult = x264_encoder_headers(pX264Handle, &pNals, &iNal);
	if (iResult<0)
	{
		return -2;
	}
	//* 获取允许缓存的最大帧数.
	int iMaxFrames = x264_encoder_maximum_delayed_frames(pX264Handle);
	//* 编码需要的参数.
    pPicIn = new x264_picture_t;
    pPicOut = new x264_picture_t;
	x264_picture_init(pPicOut);
	x264_picture_alloc(pPicIn, X264_CSP_I420, pX264Param->i_width,
	pX264Param->i_height);
	pPicIn->img.i_csp = X264_CSP_I420;
	pPicIn->img.i_plane = 3;
	pPicIn->i_type= X264_TYPE_AUTO;
	BYTE *bufptr;
	//* 创建文件,用于存储编码数据
	//* 示例用编码数据.
	iDataLen = pX264Param->i_width * pX264Param->i_height;
	filesize=pX264Param->i_width * pX264Param->i_height*1.5;
	return 0;
}

extern __declspec(dllexport) int EncodeBuf(BYTE *inBuf,int inBufsize,int picType,BYTE *outBuf)
{
     if(inBufsize<filesize) return -1;
	 if (picType==0)  //yuv12
	 {
	 memcpy(pPicIn->img.plane[0], inBuf,iDataLen);//YUV的Y分量
	 memcpy(pPicIn->img.plane[2], inBuf+iDataLen, iDataLen / 4);//YUV的U分量
	 memcpy(pPicIn->img.plane[1], inBuf+iDataLen+iDataLen / 4, iDataLen / 4);//YUV的V分量  
	 }if (picType==1)  //yuv420
	 {
		 memcpy(pPicIn->img.plane[0], inBuf,iDataLen);//YUV的Y分量
		 memcpy(pPicIn->img.plane[1], inBuf+iDataLen, iDataLen / 4);//YUV的U分量
		 memcpy(pPicIn->img.plane[2], inBuf+iDataLen+iDataLen / 4, iDataLen / 4);//YUV的V分量
	 }
	 //开始编码 	
	if (uiComponent <= 1000) 
	{
		  pPicIn->i_pts = uiComponent + g_uiPTSFactor * 1000;
		  x264_encoder_encode(pX264Handle, &pNals, &iNal, pPicIn, pPicOut);
	} else 
	{
		int iResult = x264_encoder_encode(pX264Handle, &pNals, &iNal, NULL, pPicOut);
		if (0 == iResult) 
		{
		//break; //* 取空,跳出
		uiComponent = 0;
		++g_uiPTSFactor;
		}
		uiComponent++;
    }
	//将编码数据写入缓冲
	int outBufsize=0;
	BYTE *bufptr=(BYTE *)outBuf;
    for (int i=0;i<iNal;++i)
	{
		memcpy(bufptr,pNals[i].p_payload,pNals[i].i_payload);
		bufptr +=pNals[i].i_payload;
		outBufsize+=pNals[i].i_payload;
	}
	return outBufsize;
}

extern __declspec(dllexport) void ClearDLL(void)
{
  x264_picture_clean(pPicIn);
  x264_picture_clean(pPicOut);
}