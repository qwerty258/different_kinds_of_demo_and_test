// *************************************************************************
//
// Copyright (C) 2019  yaofei zheng
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>

#define NAME_WIDTH 20

int main(int argc, char *argv[])
{
    av_register_all();

    AVCodec *p_AVCodec = NULL;
    printf("Codecs:\n");
    do
    {
        p_AVCodec = av_codec_next(p_AVCodec);
        if (NULL != p_AVCodec)
        {
            if (NULL != p_AVCodec->name)
            {
                printf("%s", p_AVCodec->name);
                for (size_t i = 0; i < NAME_WIDTH - strlen(p_AVCodec->name); i++)
                {
                    printf(" ");
                }
            }
            else
            {
                for (size_t i = 0; i < NAME_WIDTH; i++)
                {
                    printf(" ");
                }
            }

            if (NULL != p_AVCodec->long_name)
            {
                printf("%s\n", p_AVCodec->long_name);
            }
        }
    } while (NULL != p_AVCodec);

    return 0;
}
