
#include "stdafx.h"

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define __USE_LARGEFILE64

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


char *progname;
int pack_num;

char *basename;

int par_flag = 0;
int pes_flag = 0;
int debug = 0;


unsigned char packet_start_code_prefix[3] = {0x00, 0x00, 0x01};
unsigned char end_code[4] = {0x00, 0x00, 0x01, 0xb9};
unsigned char pack_start_code[4] = {0x00, 0x00, 0x01, 0xba};
unsigned char system_header_start_code[4] = {0x00, 0x00, 0x01, 0xbb};
/////////////////////////////////////////////////////////////////////////////
//   PES structure

//ESCR_flag
struct ps_escr
{
    LONGLONG escr;		//ESCR_base
    short extension;	//ESCR_extension
};
struct ps_esrate
{
    int rate;			//ES_rate
};
struct ps_trick
{
    short mode;			//trick_mode_control
    short content;		//
};
struct ps_add
{
    char info;			//additional_copy_info
};
struct ps_crc
{
    short crc;			//previous_PES_packet_CRC
};
struct ps_ext_pridata
{
    char pridata[16];	//PES_private_data
};
struct ps_ext_header
{
    short length;		//pack_field_length
};
struct ps_ext_counter
{
    short counter;		//program_packet_sequence_counter
    bool identifier;	//MPEG1_MPEG2_identifier
    short length;		//original_stuff_length
};
struct ps_ext_buffer
{
    bool scale;			//P-STD_buffer_scale
    short size;			//P-STD_buffer_size
};
struct ps_ext_ext
{
    short length;		//PES_extension_field_length
};
struct ps_ext
{
    bool pridata;		//PES_private_data_flag
    bool header;		//pack_header_field_flag
    bool counter;		//program_packet_sequence_counter_flag
    bool buffer;		//P-STD_buffer_flag
    bool extension;		//PES_extension_flag_2
    ps_ext_pridata prif;		//PES_private_data_field
    ps_ext_header headerf;		//pack_header_field_field
    ps_ext_counter countf;		//program_packet_sequence_counter_field
    ps_ext_buffer buff;			//P-STD_buffer_field
    ps_ext_ext extf;			//PES_extension_field

};
//PES packet
struct ps_packet
{
    unsigned char id;  //stream_id
    short length;      //PES_packet_length
    short flag;        //'10'
    short scramble;    //PES_scrambling_control
    bool priority;     //PES_priority
    bool align;        //data_alignment_indicator
    bool copyright;    //copyright
    bool origin;       //original_or_copy
    short ptsdts;      //PTS_DTS_flags
    bool escr;         //ESCR_flag
    bool rate;		   //ES_rate_flag
    bool trick;        //DSM_trick_mode_flag
    bool add;		   //additional_copy_info_flag
    bool crc;		   //PES_CRC_flag
    bool extension;	   //PES_extension_flag
    short hlength;	   //PES_header_data_length
    LONGLONG pts;
    LONGLONG dts;
    ps_escr escrf;     //ESCR_field
    ps_esrate ratef;   //ES_rate_field
    ps_trick trickf;   //DSM_trick_mode_field
    ps_add addf;	   //additional_copy_info_field	
    ps_crc crcf;	   //PES_CRC_field
    ps_ext extf;	   //PES_extension_field	

};
//////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//Pack structure
struct ps_pack
{
    LONGLONG scr;		//system_clock_reference_base
    short scre;			//system_clock_reference_extension
    int rate;			//program_mux_rate
    short stufflength;	//pack_stuffing_length
};
///////////////////////////////////////////////////////////////////////////////
void fatal(int ret, char *format, ...)
{


    fprintf(stderr, "fatal error");
    if(format)
    {
        fprintf(stderr, ": ");
        if(ret >= 2) fprintf(stderr, "pack num %d: ", pack_num);
    }
    else
        fprintf(stderr, "\n");

    exit(ret);
}




#define STREAM_MAPPING     0xbc
#define PRIVATE_STREAM_1   0xbd
#define PADDING_STREAM     0xbe
#define PRIVATE_STREAM_2   0xbf

#define FIRST_AUDIO_STREAM 0xc0
#define LAST_AUDIO_STREAM  0xdf

#define FIRST_VIDEO_STREAM 0xe0
#define LAST_VIDEO_STREAM  0xef

#define STREAM_DIRECTORY   0xff

HANDLE open_output(int stream)
{
    HANDLE fd;
    char *extension;
    char fn[200];
    //if a packet is a audio packet,store it in mp3 file
    if((stream >= FIRST_AUDIO_STREAM) && (stream <= LAST_AUDIO_STREAM))
    {
        stream -= 0xc0;
        extension = "mp3";
    }
    //if a packet is a video packet,store it in mpg file
    if((stream >= FIRST_VIDEO_STREAM) && (stream <= LAST_VIDEO_STREAM))
    {
        stream -= 0xe0;
        extension = "mpg";
    }

    basename = "f:\\mpeg\\Stream";

    _snprintf(fn, sizeof(fn), "%s-%d.%s", basename, stream, extension);
    fd = CreateFile(fn, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ |
                    FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, NULL);
    if(fd == INVALID_HANDLE_VALUE)
        fatal(2, "error opening output file %s\n", fn);

    return (fd);
}


unsigned char * parse_system_header(unsigned char *p)
{
    int header_length;

    /* printf ("pack number %d has system header\n", pack_num); */

    p += 4;  /* skip start code */
    header_length = (*(p++)) << 8;
    header_length += *(p++);

    p += header_length;

    return (p);
}


LONGLONG parse_time_stamp(unsigned char *p)
{
    int b;
    LONGLONG val;

    b = *p++;
    val = (b & 0x0e) << 29;

    b = (*(p++)) << 8;
    b += *(p++);
    val += ((b & 0xfffe) << 14);

    b = (*(p++)) << 8;
    b += *(p++);
    val += ((b & 0xfffe) >> 1);

    return (val);
}

LONGLONG parse_scr(unsigned char *p)
{
    int tmp;
    LONGLONG ltmp;

    tmp = *p++;
    if(((tmp >> 6) & 3) != 1)
        fatal(2, "This file is not a MPEG2 file!\n");
    //get scr and scr ext;
    ltmp = (tmp & 0x38) << 27;
    tmp <<= 8;
    tmp += *(p++);
    ltmp += (tmp & 0x03ff) << 20;
    tmp = *(p++);
    ltmp += (tmp & 0xf8) << 12;
    tmp <<= 8;
    tmp += *(p++);
    ltmp += (tmp & 0x03ff) << 5;
    tmp = *(p++);
    ltmp += (tmp & 0xf8);
    return (ltmp);
}

LONGLONG parse_scre(unsigned char *p)
{
    int tmp;
    LONGLONG ltmp;

    tmp = *p++;
    tmp <<= 8;
    tmp += *(p++);
    ltmp = (tmp & 0x03fe) >> 1;
    return (ltmp);
}

LONGLONG parse_muxrate(unsigned char *p)
{
    int tmp;
    LONGLONG ltmp;

    tmp = *p++;
    tmp <<= 8;
    tmp += *(p++);
    tmp <<= 8;
    tmp += *(p++);
    ltmp = (tmp & 0xfffffc) >> 1;
    return (ltmp);
}

int found_stream[256];
HANDLE out_fd[256];

unsigned char found_pts[256];
LONGLONG pts[256];

unsigned char found_dts[256];
LONGLONG dts[256];

LONGLONG par[4];
HANDLE parname;




void write_stream(int stream, unsigned char *p, int count)
{
    while(count)
    {
        DWORD dwWritten;
        WriteFile(out_fd[stream], (PVOID)p, (DWORD)count, &dwWritten, NULL);
        int c2 = (int)dwWritten;
        if(c2 < 0)
        {
            perror("write error");
            fatal(2, "write error on stream %02x\n", stream);
        }
        p += c2;
        count -= c2;
    }

}


unsigned char * parse_packet(int stream, unsigned char *p)
{
    int length;
    unsigned char *end;
    unsigned char *data_start;
    int i;
    int count;
    int tmp;				//32bit temperatory
    LONGLONG ltmp;			//64bit temperatory
    int flags, pes_header_data_length;
    short trick_flags, ext_flags, PES_ext_field_len;
    ps_packet psp;

    p += 3;  /* skip start code*/
    psp.id = *(p++);
    psp.length = (*(p++)) << 8;
    psp.length += *(p++);

    end = p + psp.length;



    if(psp.id == PADDING_STREAM)  goto done;  /* ignore */
    else
    {
        //found_stream array marks the existed stream id
        //i.e,when a stream packet whose id is 0xbe comes,found_stream[0xbe] will be set '1'.
        if(!found_stream[stream])
        {
            found_stream[stream] = 1;
            out_fd[stream] = open_output(stream);
        }
        //flags contains PES_scrambling_control,PES_priority,data_alignment_indicator,copyright,...

        flags = (*(p++)) << 8;
        flags += *(p++);

        psp.flag = (flags >> 14) & 3;

        if(psp.flag != 2)    fatal(2, "bad flags %04x\n", flags);//if psp.flag is not equal to '10',this is a bad stream packet.
        psp.hlength = *(p++);
        //get the data start address
        data_start = p + psp.hlength;
        //get pts & dts
        psp.ptsdts = (flags >> 6) & 3;
        switch(psp.ptsdts)
        {
            case 2:
                if(!found_pts[stream])
                {
                    found_pts[stream] = 1;
                    pts[stream] = parse_time_stamp(p);
                    psp.pts = pts[stream];
                    psp.dts = 0;

                }

                p += 5;
                break;
            case 3:
                if(!found_pts[stream])
                {
                    found_pts[stream] = 1;
                    pts[stream] = parse_time_stamp(p);
                    psp.pts = pts[stream];

                }
                p += 5;
                if(!found_dts[stream])
                {
                    found_dts[stream] = 1;
                    dts[stream] = parse_time_stamp(p);
                    psp.dts = dts[stream];
                }

                p += 5;
                break;
            case 0:
                break;
            default:
                fatal(2, "bad time stamp code\n");
        }

        psp.escr = (flags >> 5) & 1;
        if(psp.escr == TRUE)
        {

            psp.escrf.escr = parse_scr(p);
            p += 4;
            psp.escrf.extension = parse_scre(p);
            p += 2;

        }

        psp.rate = (flags >> 4) & 1;
        if(psp.rate == TRUE)
        {
            tmp = *(p++);
            tmp <<= 8;
            tmp += *(p++);
            tmp <<= 8;
            tmp += *(p++);
            psp.ratef.rate = (tmp & 0x7ffffe) >> 1;
        }

        psp.trick = (flags >> 3) & 1;
        if(psp.trick == TRUE)
        {
            tmp = *(p++);
            psp.trickf.mode = (tmp & 0xe0) >> 5;
            psp.trickf.content = tmp & 0x1f;

        }

        psp.add = (flags >> 2) & 1;
        if(psp.add == TRUE)
        {
            psp.addf.info = *(p++) >> 1;
        }

        psp.crc = (flags >> 1) & 1;
        if(psp.crc == TRUE)
        {
            tmp = *(p++);
            tmp <<= 8;
            tmp += *(p++);
            psp.crcf.crc = tmp;
        }

        psp.extension = flags & 1;
        if(psp.extension == TRUE)
        {
            tmp = (*(p++));
            psp.extf.pridata = (tmp >> 7) & 1;
            psp.extf.header = (tmp >> 6) & 1;
            psp.extf.counter = (tmp >> 5) & 1;
            psp.extf.buffer = (tmp >> 4) & 1;
            psp.extf.extension = tmp & 1;
            if(psp.extf.pridata == TRUE)
            {
                for(i = 0; i < 16; i++)
                {
                    psp.extf.prif.pridata[i] = *p++;
                }
            }
            if(psp.extf.header == TRUE)
            {
                psp.extf.headerf.length = *p++;

            }
            if(psp.extf.counter == TRUE)
            {
                psp.extf.countf.counter = *p++ & 0x7f;

            }
            if(psp.extf.buffer == TRUE)
            {
                tmp = *p++;
                tmp += *p++;
                psp.extf.buff.scale = (tmp & 0x2000) >> 13;
                psp.extf.buff.size = tmp & 0x1fff;

            }
            if(psp.extf.extension == TRUE)
            {

                psp.extf.extf.length = *(p++) & 0x7f;
                p += PES_ext_field_len;

            }

        }

        p = data_start;

        count = (end - p);
        //store audio data
        if((stream >= FIRST_AUDIO_STREAM) && (stream <= LAST_AUDIO_STREAM))
        {
            write_stream(stream, p, count);
        }

        //store video data
        if((stream >= FIRST_VIDEO_STREAM) && (stream <= LAST_VIDEO_STREAM))
        {
            write_stream(stream, p, count);
        }
    }
done:
    //DWORD dwWritten;	
    //WriteFile(parname, (PVOID)&par, 32, &dwWritten, NULL);
    return (end);
}




void parse_pack(unsigned char *buf, int size)
{
    int stream;
    unsigned char *p = buf;//
    unsigned char *pstart = buf;
    int tmp; //32bit temperatory
    LONGLONG ltmp;//64bit temperatory
    ps_pack pp;
    //skip start code
    p += 4;
    //if next 2bit is not '01', an error occurs.
    tmp = *p;
    if(((tmp >> 6) & 3) != 1)
        fatal(2, "This file is not a MPEG2 file!\n");
    //get scr;
    pp.scr = parse_scr(p);
    //get scr ext;
    p += 4;

    pp.scre = parse_scre(p);
    //get mux rate;
    p += 2;
    pp.rate = parse_muxrate(p);

    p = pstart + sizeof(pack_start_code) + 10;
    // parse system header;
    if(memcmp(p, system_header_start_code, sizeof(system_header_start_code)) == 0)
        p = parse_system_header(p);
    // parse pes packet;
    while(p < (buf + size))
    {
        if(memcmp(p, packet_start_code_prefix, sizeof(packet_start_code_prefix)) != 0)
        {
            fatal(2, "missing packet start code prefix\n");
        }
        stream = *(p + 3);
        p = parse_packet(stream, p);
    }
    //verify 
    if(p != (buf + size)) fatal(2, "packet extends past end of pack\n");
}


#define BLKSIZE 2048

unsigned char buf[BLKSIZE];

int main(int argc, char *argv[])
{
    char *in_fn;
    HANDLE mf;
    int s;


    //get input file name
    if(argc < 2)
        in_fn = "f:\\mpeg\\testps.mpg";
    else
        in_fn = argv[1];
    progname = argv[0];
    pack_num = 0;



    //open media file
    mf = CreateFile(in_fn, GENERIC_READ, FILE_SHARE_READ, NULL,
        OPEN_EXISTING, 0, NULL);
    if(mf == INVALID_HANDLE_VALUE)
        fatal(2, "error opening output file %s\n", mf);

    //parse packet
    DWORD dwRead;
    for(;;)
    {
        //read a 2048 byte packet 
        ReadFile(mf, (PVOID)&buf, (DWORD)BLKSIZE, &dwRead, NULL);
        s = (int)dwRead;
        if(s < 0)
        {
            perror("read error\n");
            break;
        }
        if(s == 0)
        {
            // end of file 
            break;
        }
        if(s != BLKSIZE)
        {
            // end of file 
            if(memcmp(buf, end_code, sizeof(end_code)) != 0)
                fprintf(stderr, "pack num %d: expected %d, got %d\n", pack_num, BLKSIZE, s);
            break;
        }
        //parse a packet
        if(memcmp(buf, pack_start_code, sizeof(pack_start_code)) == 0)
            parse_pack(buf, BLKSIZE);
        else if(memcmp(buf, end_code, sizeof(end_code)) == 0)
        {
            printf("end code\n");
            break;
        }
        else
        {
            fprintf(stderr, "pack num %d: bad pack start code\n", pack_num);
            break;
        }
        pack_num++;
    }

    for(s = 0; s < 255; s++)
        if(out_fd[s])  CloseHandle(out_fd[s]);
    CloseHandle(parname);
    CloseHandle(mf);
    return 0;
}
