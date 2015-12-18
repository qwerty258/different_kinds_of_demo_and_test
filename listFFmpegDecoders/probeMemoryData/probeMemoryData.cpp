#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <libavformat\avformat.h>

#ifdef __cplusplus
}
#endif // __cplusplus

#include <stdio.h>
#include <stdint.h>

uint8_t* p_global_PS_data;
uint8_t* p_current_position;
uint32_t* p_global_PS_data_size;
uint32_t global_PS_data_size;
uint32_t global_PS_data_size_size;
uint32_t global_i;

int fill_iobuffer(void* opaque, uint8_t* buf, int bufSize)
{
    //bufSize = p_global_PS_data_size[global_i];

    //memcpy(buf, p_current_position, bufSize);

    //p_current_position += bufSize;
    //global_i++;
    //if(global_i >= global_PS_data_size_size)
    //{
    //    global_i = 0;
    //}

    memcpy(buf, p_global_PS_data, global_PS_data_size);

    return bufSize;

}

int main(int argc, char* argv[])
{
    av_register_all();

    FILE* p_PS_data_file;
    FILE* p_PS_data_size_file;

    p_PS_data_file = fopen("D:\\PSdata", "rb");
    p_PS_data_size_file = fopen("D:\\PSdataSize", "rb");

    fseek(p_PS_data_file, 0, SEEK_END);
    fseek(p_PS_data_size_file, 0, SEEK_END);

    global_PS_data_size = ftell(p_PS_data_file);
    global_PS_data_size_size = ftell(p_PS_data_size_file);

    p_global_PS_data = (uint8_t*)malloc(global_PS_data_size);
    p_global_PS_data_size = (uint32_t*)malloc(global_PS_data_size_size);

    rewind(p_PS_data_file);
    rewind(p_PS_data_size_file);

    fread(p_global_PS_data, global_PS_data_size, 1, p_PS_data_file);
    fread(p_global_PS_data_size, global_PS_data_size_size, 1, p_PS_data_size_file);

    fclose(p_PS_data_file);
    fclose(p_PS_data_size_file);
    p_PS_data_file = NULL;
    p_PS_data_size_file = NULL;

    global_i = 0;
    p_current_position = p_global_PS_data;

    uint8_t* p_iobuffer = (uint8_t*)av_malloc(global_PS_data_size + 1000);

    AVIOContext* p_AVIOContext = avio_alloc_context(
        p_iobuffer,
        global_PS_data_size + 1000,
        0,
        NULL,
        fill_iobuffer,
        NULL,
        NULL);

    int result;

    AVFormatContext* fmt_ctx = avformat_alloc_context();

    fmt_ctx->pb = p_AVIOContext;

    result = avformat_open_input(&fmt_ctx, fmt_ctx->filename, fmt_ctx->iformat, NULL);

    result = avformat_find_stream_info(fmt_ctx, NULL);

    AVPacket* pAVPacket = (AVPacket*)av_malloc(sizeof(AVPacket));

    for(size_t i = 0; i < 100; i++)
    {
        av_read_frame(fmt_ctx, pAVPacket);

        av_free_packet(pAVPacket);
    }

    avformat_free_context(fmt_ctx);

    //av_freep(&p_iobuffer);

    free(p_global_PS_data);
    free(p_global_PS_data_size);

    return 0;
}

