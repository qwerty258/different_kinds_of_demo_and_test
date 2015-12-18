#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ParseContext
{   
    unsigned int FrameStartFound;    
    unsigned int iFrameLength;    

} ParseContext; 
signed int DecLoadAU(unsigned char* pStream, unsigned int iStreamLen,int fpsNum, ParseContext *pc)
    {   
        unsigned int i;   
        unsigned int state = 0xffffffff;   
        if( NULL == pStream )   
        {   
            return -1;   
        }   
		int j=0;
        for( i = 0; i < iStreamLen; i++)   
        {   
            /* 查找nal类型为1和5的nal头 */ 
            if( (state & 0xFFFFFF1F) == 0x101 || (state & 0xFFFFFF1F) == 0x105 )   /*百度不给力日，101*/
			{   
                if (i >= iStreamLen) /* 到达Buffer尾部，退出查找循环 */ 
                {   
                    break;   
                }if( pStream[i] & 0x80) /* 查找first_mb_in_slice为0的slice头确定一幅图像的开始 */ 
                {   
                    if(pc->FrameStartFound) /* 查找到下一幅图像的开始就可以确定图像的起始和结束 */ 
                    {   
                        if (j<fpsNum)
						{
							j++;
							continue;
						}
						else
						{
						    pc->iFrameLength = i - 3;   
                            pc->FrameStartFound = 0;   
                            state = 0xffffffff;  
							
                            return 0; /* 找到一幅图像的边界返回0 */
						}
                    }   
                    else 
                    {   
                        pc->FrameStartFound = 1;   
                    }   
                }   
            }   
            if (i < iStreamLen)   
            {   
                state = (state << 8) | pStream[i];  
            }   
        }   
        pc->FrameStartFound = 0;   
        return -1; /* 没有找到AU边界返回-1 */ 
    }

int dingwei(FILE *fp,int k)			//!定位NAL的起始位置的函数
{   char buf[2];
    int i=0;
	fseek(fp,k,SEEK_SET);		//!指针定位，从开头开始
	for(;feof(fp)==0;)
		{
			fread(buf,1,1,fp) ;
			k++;
			if(i<4)
			{
				if(buf[0]==0)   {i=i+1;}
				else		{i=0;}
			}
			if(i==4&&buf[0]==1)
			{
		    	return k;					//!此时定位在开始码0x000001的01处
			}
	}

exit(-1);
}

char NALU(FILE *fp,int dis,unsigned char nal_unit_type)	//!判断NALU的类型的函数
{	unsigned char buf1[2];
	fseek(fp,dis,SEEK_SET);
	fread(buf1,1,1,fp);
	nal_unit_type=(buf1[0]&0x1f);					//!取buf1[0]中的低五位bit
	//!输出片类型
	return nal_unit_type;
}

char slice(FILE *fp,int k)		      //!判断片类型的函数
{  // FILE *fp;
	int j=0;
	unsigned char buf1[2];
	int count=0;
	char slice_type=0;
	//fp=fopen(FILE_PATH,"rb+");
	fseek(fp,k,SEEK_SET);
	fread(buf1,1,1,fp);
	buf1[1]=buf1[0];			             //!以下函数程序完成的是Golomb熵编码信息提取
	for(count=0;count<2;count++)
	{	buf1[0]=buf1[1];
		buf1[0]<<=j;
		buf1[1]=buf1[0];
		for(j=1;(buf1[j]&0x80)!=0x80;j++)    //!j为0的计数
			{buf1[j]<<=1;}
		if(count==1)   
		{	
			slice_type=(buf1[1]>>=(9-2*j));
			slice_type=slice_type-1;
		}
	}
  return slice_type;
}
char sliceEx(FILE *fp,int k)
{
	int j=0;
	unsigned char buf1[2];
	int count=0;
	char slice_type=0;
	//fp=fopen(FILE_PATH,"rb+");
	fseek(fp,k,SEEK_SET);
	fread(buf1,1,2,fp);
	if (buf1[1]&0x80==0x80)
	{return 1;}
	else
	{return 0;}

}
int count_long(int dis,FILE *fp)	//!计算该帧的长度的函数，以字节为单位计数
{	char buf[2];int i=0;int count=0;
	fseek(fp,dis,SEEK_SET);

	for(;feof(fp)==0;)						//!结束调节为测到文件结束标记时
	{count++;
	fread(buf,1,1,fp) ;
	if(i<3)
	{
		if(buf[0]==0)   {i=i+1;}
		else{i=0;}
		
	}
	if(i==3&&buf[0]==1)  return count;						//!返回值count为该帧长的字节数
	}	
return count ;
}
int GetHeadBuf(char* buf,FILE *fp)   //将264头放入buf
{
    int k=0;
	k=dingwei(fp,k);
	k=k+count_long(k,fp);
	fseek(fp,0,0);
	fread(buf,1,k-4,fp);
	return k-4;
}
int setbeginTime(char *filename,int beginTime)
{
	FILE *fp;
	char nut=0;char buf[350000];		
	int i=0,k=0,j=0,times,min,ms,framerate=25,num1,tp,count=0,m=0,n=0,p=0;
	char st=0;
	times=beginTime;
	num1=beginTime;		               //!时间换算帧数   +2是把PPS和SPS补偿掉
    fp=fopen(filename,"rb+");
	 for(;num1>0;num1--)	  
    {	k=dingwei(fp,k);              //定位
	    //char st=slice(fp,k);
	    k=k+count_long(k,fp);
			
	 }
	fclose(fp);
	return k-4;
}

int setbeginPoint(char *filename,int beginTime)
{
	FILE *fp;
	char nut=0;char buf[350000];		
	int i=0,k=0,j=0,times,min,ms,framerate=25,num1,tp,count=0,m=0,n=0,p=0;
	char st=0;
	times=beginTime;
	num1=beginTime;		               //!时间换算帧数   +2是把PPS和SPS补偿掉
    fp=fopen(filename,"rb+");
	 for(;num1>0;num1--)	  
    {	k=dingwei(fp,k);               //定位坐标点
	    char st=sliceEx(fp,k);           //定位帧边界
	    if(st==1)
		{
		   k=k+count_long(k,fp)-4;     //开头的4字节
           
		}	
	 }
	fclose(fp);
	return k-4;
}

