#include <memory.h>


#ifndef _NALUCOMMON_H_
#define _NALUCOMMON_H_

typedef struct 
{
 int startcodeprefix_len;      //! 4 for parameter sets and first slice in picture, 3 for everything else (suggested)
 unsigned len;                 //! Length of the NAL unit (Excluding the start code, which does not belong to the NALU)
 unsigned max_size;            //! Nal Unit Buffer size
 int nal_unit_type;            //! NALU_TYPE_xxxx
 int nal_reference_idc;        //! NALU_PRIORITY_xxxx
 int forbidden_bit;            //! should be always FALSE
 unsigned char *buf;        //! conjtains the first byte followed by the EBSP
} NALU_t;

#define MAXRBSPSIZE 64000

#define NALU_TYPE_SLICE    1
#define NALU_TYPE_DPA      2
#define NALU_TYPE_DPB      3
#define NALU_TYPE_DPC      4
#define NALU_TYPE_IDR      5
#define NALU_TYPE_SEI      6
#define NALU_TYPE_SPS      7
#define NALU_TYPE_PPS      8
#define NALU_TYPE_AUD      9
#define NALU_TYPE_EOSEQ    10
#define NALU_TYPE_EOSTREAM 11
#define NALU_TYPE_FILL     12

#define NALU_PRIORITY_HIGHEST     3
#define NALU_PRIORITY_HIGH        2
#define NALU_PRIRITY_LOW          1
#define NALU_PRIORITY_DISPOSABLE  0


#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef BOOL
#define BOOL unsigned int
#endif

void ReportNalu(FILE* src,FILE* rep);
void ParseRecBuf(unsigned char *p,int bufsize,FILE* pReport);
int ShowBits (unsigned char buffer[],int totbitoffset,int bytecount, int numbits);
BOOL next_bits(unsigned char *p,int bufpos,int bs,int id );
static int FindStartCode (unsigned char *Buf, int bufpos,  int bufsize, int next_start_pos, BOOL fIRFD);
BOOL gETNALandPROC(unsigned char *p,int bufpos,int bufsize, BOOL fisrtfd,NALU_t *mNal,int inc_SIZE,FILE *pReport);
#endif
