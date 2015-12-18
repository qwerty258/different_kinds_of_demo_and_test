#include "stdafx.h"
#include "naluCommon.h"

void ReportNalu(FILE* src,FILE* rep)
{
 //unsigned char tempbuf[1];
 //unsigned char *pBuf;
 //int *dstlen;
 //   int fpos=0; 
 //int fstart=0;
 //int FileSize=0;
 //int BufSize; 
 //int dstpacketid=0;
 //unsigned int  SymState=0;
 //fseek(src,0,SEEK_END); 
 //FileSize=ftell(src);
 //printf("the src file size is %d \n",FileSize);
 //fseek(src,0,SEEK_SET);
 //do {
 // 
 // while (fread(tempbuf,sizeof(unsigned char),1,src))
 // {
 //  if(tempbuf[1]=="#") SymState++;
 //  else
 //  { 
 //   fpos=fstart+1;
 //   SymState=0;
 //   fseek(src,fpos,SEEK_SET);
 //  }
 //  if(SymState==4)
 //  {fpos+=4;break;}
 // }
 // 
 // fread(tempbuf,sizeof(unsigned char),1,src);
 // 
 // if(tempbuf=="B")
 // {
 //  SymState++;
 //  fpos+=1;
 // }
 // else
 // { 
 //  fpos=fstart+1;
 //  fseek(src,fpos,SEEK_SET);
 // }
 // 
 // if(SymState==5)   
 // {   
 //  dstpacketid++;
 //  fprintf(rep,"the %d dstpacket\n",dstpacketid);
 //  dstlen=(int*)malloc(sizeof(int));
 //  fread(dstlen,sizeof(unsigned char),4,src);
 //  BufSize=(int*)dstlen;
 //  pBuf=(unsigned char*)malloc(sizeof(unsigned char)*BufSize);
 //  fpos+=4;
 //  fread(pBuf,sizeof(unsigned char),BufSize,src);
 //  ParseRecBuf(pBuf,BufSize,rep);
 //  fstart=fpos;
 //  free(dstlen);
 //  free(pBuf);
 // } 
 // 
 //} while(fpos!=FileSize);// 
 
}


//####################################################
//# unsigned char *p  --T264 encode的一个dst长度为len#
//# int bufsize   --buffer的大小     # 
//##FILE* pReport     --文件指针，存放NAL的分析结果  #
//####################################################

void ParseRecBuf(unsigned char *p,int bufsize,FILE* pReport)
{

 
 //int bufpos=0;
 //int bUFSTART=0;
 //   struct NALU_t *mNal;
 //BOOL isfirst; 
 //BOOL starcode_ex;
 //BOOL zero_ex;
 //BOOL trail_ex;
 //int nALSIZE=0;
 //int nal_id=0;
 //BOOL firstfd=FALSE;
 //
 //while (bufpos<bufsize) 
 //{
 // if( !next_bits(p,bufpos,bufsize, 24 )  &&
 //  !next_bits(p,bufpos,bufsize,32 )  &&
 //  next_bits( p,bufpos,bufsize,8 ))
 // {bufpos+=8;isfirst=TRUE;firstfd=TRUE;}// leading_zero_8bits /* equal to 0x00 */ //f(8)
 // else{ isfirst=FALSE; }
 // 
 // if(!next_bits( p,bufpos,bufsize,24 )  &&    
 //  next_bits( p,bufpos,bufsize,8 )
 //  )  
 // {    
 //  bufpos+=8;//zero_byte /* equal to 0x00 */ f(8)
 //  zero_ex=TRUE;
 //  if( bufpos<bufsize &&
 //   next_bits(p,bufpos,bufsize, 24 ) )
 //  {      
 //   bufpos+=24; // start_code_prefix_one_3bytes /* equal to 0x000001 */ f(24)
 //   starcode_ex=TRUE;
 //   mNal=(struct NALU_t* )malloc(sizeof( NALU_t));
 //  if(gETNALandPROC(p,bufpos,bufsize,firstfd,mNal,nALSIZE,pReport))   
 //  {  
 //   nal_id++;
 //      fprintf(pReport," id of the nal packet above is %d\n",nal_id);
 //   bufpos+=(nALSIZE>>3);
 //   if(( bufpos<bufsize)  &&
 //    (!next_bits(p,bufpos,bufsize, 24 )) &&  
 //    (!next_bits(p,bufpos,bufsize, 32 ) ) &&
 //    (next_bits(p,bufpos, bufsize,8 )))
 //   {
 //    bufpos+=8; trail_ex=TRUE ;/*  trailing_zero_8bitsequal to 0x00 */
 //   }
 //   else trail_ex=FALSE;
 //   free(mNal);
 //  }
 //  else printf("cannot get any nal units\n");
 //  }
 //  else{starcode_ex=FALSE;}      
 // }
 // else
 // { zero_ex=FALSE; }
 // 
 // if (!zero_ex || !starcode_ex)
 //  bufpos=bUFSTART+1; 
 // else bUFSTART=bufpos;
 //} 
}

//############################################
//#unsigned char *p =--buffer containing NALU#
//#int bufpos--current buffer position   #
//#int bs---buffersize                   #
//#int id                                #
//#  id=24   ----0x000001----FALSE   #
//#     id=32   ----0x00000001---FALSE   #
//#     id=8 ----0x00------TRUE    # 
//############################################
BOOL next_bits(unsigned char *p,int bufpos,int bs,int id )
{
 BOOL rERULT;
 switch(id) {
 case 8:   
  if(ShowBits(p,bufpos,bs,8)==0x00) rERULT=TRUE ;
  else rERULT=FALSE;
  break;
 case 24: 
  if(ShowBits(p,bufpos,bs,24)!=0x000001) rERULT=FALSE;
  else rERULT=TRUE;
  break;
 case 32 :
  if(ShowBits(p,bufpos,bs,32)!=0x00000001) rERULT=FALSE;
  else rERULT=TRUE;
  break;
 default:
  break;
 }
 return rERULT;
}
//##############################################
// # \brief         #
// #  Reads bits from the bitstream buffer     #
// # \param buffer        #
// #    buffer containing VLC-coded data bits  #
// # \param totbitoffset      #
// #    bit offset from start of partition     #
// # \param bytecount                          #
// #    total bytes in bitstream               #
// # \param numbits                            #
// #    number of bits to read                 #
// #############################################
int ShowBits (unsigned char buffer[],int totbitoffset,int bytecount, int numbits)
{
 
 register int inf;
 long byteoffset;      // byte from start of buffer
 int bitoffset;      // bit from start of byte
 
 byteoffset= totbitoffset/8;
 bitoffset= 7-(totbitoffset%8);
 
 inf=0;
 while (numbits)
 {
  inf <<=1;
  inf |= (buffer[byteoffset] & (0x01<<bitoffset))>>bitoffset;
  numbits--;
  bitoffset--;
  if (bitoffset < 0)
  {
   byteoffset++;
   bitoffset += 8;
   if (byteoffset > bytecount)
   {
    return -1;
   }
  }
 }
 
 return inf;   // return absolute offset in bit from start of frame
}    


//#########################################################################
// # \brief             

    #
// #    returns if new start code is found at byte aligned position buf.  #
// #    new-startcode is of form N 0x00 bytes, followed by a 0x01 byte.   #
// #  \return             

    #
// #     1 if start-code is found or                      \n              #
// #     0, indicating that there is no start code                        #
// #                                                                      #
// #  \param Buf                                                          #
// #     pointer to byte-stream                                           #
// #  \param   bufpos                                             #
// #     indicates current bufpos. 
//#     \bufsize
//  #   indicates   total buffer size                          #
//  #  \param      next_star_pos                                           #
//  #      indicates the next_start_code pos                               #
//  #  \param      fIRFD
//  #    is firs nal already found
// ########################################################################
static int FindStartCode (unsigned char *Buf, int bufpos,  int bufsize, int next_start_pos, BOOL fIRFD)
{
 int info;
 int tPOS;
 int tSTART=bufpos;
 BOOL sTARFOUND=FALSE;
 info = 1;
 while (!sTARFOUND && tSTART<bufsize) {
  for (tPOS = 0; tPOS < 3; tPOS++)
   if(Buf[tSTART+tPOS] != 0)
    info = 0;    
   if(Buf[tSTART+tPOS] != 1)
    info = 0;
   if (info==0)    tSTART++;    
   else sTARFOUND=TRUE; 
 }
 if (fIRFD && sTARFOUND)
 {  
  if(Buf[tSTART-1]==0 &&
   Buf[tSTART-2]==0)
  { info=2;//trailing zero found
  next_start_pos=tSTART-2;}
  else {info=1;
  next_start_pos=tSTART;}   
 } 
 return info;
}

static int FindSps (unsigned char *Buf, int bufpos,  int bufsize, int next_start_pos, BOOL fIRFD)
{
	int spsBuf;
	int tops=0;
	int ru=-1;
	while (tops<bufsize)
	{
		if ((spsBuf & 0x00000001)==0)
		{
           return ru;
		}
	}
}

//#####################################
//# unsigned char *p      #
//# int bufpos                    #
//# NALU_t *mNal          #
//# int n_SIZE       #
//#           #
//#           # 
//#####################################
BOOL gETNALandPROC(unsigned char *p,
       int bufpos,
       int bufsize,
       BOOL fisrtfd,
       NALU_t *mNal,
       int inc_SIZE,
       FILE *pReport)
{  
 BOOL getNfailed=FALSE;
    int nal_BUFSIZE=0;
 int next_start_point=0;
 int mNal_size=0;
 int b_bufpos=bufpos/8;
 unsigned int finresult;
 BOOL info=TRUE;
 finresult=FindStartCode (p,b_bufpos,bufsize,next_start_point,fisrtfd);
 if (finresult==1 || finresult==2) {   
  nal_BUFSIZE=next_start_point-b_bufpos-1;
  inc_SIZE=nal_BUFSIZE;
  mNal->buf=(unsigned char *)malloc(sizeof(unsigned char)*nal_BUFSIZE);
  mNal->len=nal_BUFSIZE;
  memcpy (mNal->buf, &p[b_bufpos+1], mNal->len);
  mNal->forbidden_bit = (mNal->buf[0]>>7) & 1;
  mNal->nal_reference_idc = (mNal->buf[0]>>5) & 3;
  mNal->nal_unit_type = (mNal->buf[0]) & 0x1f;
  fprintf(pReport,"#########################################################################\n");
  fprintf(pReport,"nal len is %d\n",mNal->len);
  fprintf(pReport,"fobidden bit is % d\n",mNal->forbidden_bit);
  fprintf(pReport,"nal_reference_idc is d%\n",mNal->nal_reference_idc);
  switch(mNal->nal_unit_type) {
  case NALU_TYPE_SLICE :
   fprintf(pReport," nal type is  * NALU_TYPE_SLICE\n");
   break;
  case NALU_TYPE_DPA:
   fprintf(pReport,"nal type is *  NALU_TYPE_DPA\n");
   break;
  case NALU_TYPE_DPB :
   fprintf(pReport,"nal type is  * NALU_TYPE_DPB\n");
   break;
  case NALU_TYPE_DPC:
   fprintf(pReport,"nal type is  * NALU_TYPE_DPC\n");
   break;
  case NALU_TYPE_IDR:
   fprintf(pReport,"nal type is  * NALU_TYPE_IDR\n");
   break;
  case NALU_TYPE_SEI:
   fprintf(pReport,"nal type is  * NALU_TYPE_SEI\n");
   break;
  case NALU_TYPE_SPS:
   fprintf(pReport,"nal type is  * NALU_TYPE_SPS\n");
   break;
  case NALU_TYPE_PPS:
   fprintf(pReport,"nal type is  * NALU_TYPE_PPS\n");
   break;
  case NALU_TYPE_AUD:
   fprintf(pReport,"nal type is  * NALU_TYPE_AUD\n");
   break;
  case NALU_TYPE_EOSEQ:
   fprintf(pReport,"nal type is  * NALU_TYPE_EOSEQ\n");
   break;
  case NALU_TYPE_EOSTREAM:
   fprintf(pReport,"nal type is  * NALU_TYPE_EOSTREAM\n");
   break;
  case NALU_TYPE_FILL  :
   fprintf(pReport,"nal type is  * NALU_TYPE_FILL\n");
   break;
  default:
   break;
  }
  fprintf(pReport,"nal start code len is %d\n",mNal->startcodeprefix_len);
  fprintf(pReport,"#########################################################################\n"); 
  free(mNal->buf);
  mNal->buf=NULL;
  }
 else info=FALSE;
 return info;
}