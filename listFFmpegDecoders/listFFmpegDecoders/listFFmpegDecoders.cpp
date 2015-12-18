#ifdef __cplusplus
extern "C" {
#endif

#include <libavcodec\avcodec.h>
#include <libavformat\avformat.h>

#ifdef __cplusplus
}
#endif

#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    av_register_all();

    AVHWAccel* p_AVHWAccel = NULL;
    AVCodec* p_AVCodec = NULL;
    AVCodecContext* p_AVCodecContext = NULL;

    //p_AVCodec = avcodec_find_decoder(AV_CODEC_ID_H264);
    p_AVCodec = avcodec_find_encoder_by_name("h264_qsv");
    p_AVCodecContext = avcodec_alloc_context3(p_AVCodec);

    do
    {
        p_AVHWAccel = av_hwaccel_next(p_AVHWAccel);
        if(NULL != p_AVHWAccel)
        {
            cout << p_AVHWAccel->name << endl;
        }
    } while(NULL != p_AVHWAccel);

    do
    {
        p_AVHWAccel = av_hwaccel_next(p_AVHWAccel);
        if(0 == strncmp(p_AVHWAccel->name, "h264_dxva2", 30))
        {
            break;
        }
    } while(NULL != p_AVHWAccel);

    p_AVCodecContext->hwaccel = p_AVHWAccel;

    AVCodecDescriptor* pAVCodecDescriptor;

    FILE* pFile;
    errno_t error = fopen_s(&pFile, "D:\\codecs.txt", "wb");
    if(0 != error)
    {
        cout << "fopen error" << endl;
        exit(-1);
    }

    pAVCodecDescriptor = (AVCodecDescriptor*)avcodec_descriptor_get(AV_CODEC_ID_MPEG1VIDEO);
    do
    {
        fwrite(pAVCodecDescriptor->long_name, strlen(pAVCodecDescriptor->long_name), 1, pFile);
        fwrite("\n", 1, 1, pFile);
        pAVCodecDescriptor = (AVCodecDescriptor*)avcodec_descriptor_next(pAVCodecDescriptor);
    } while(NULL != pAVCodecDescriptor);

    fclose(pFile);

    system("pause");

    return 0;
}

