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

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <sys/types.h>

#define PRINT_SIZE(type) printf(#type ": %zu\n", sizeof(type));

typedef enum
{
    A,
    B
} enum_define;

int main(int argc, char *argv[])
{
    PRINT_SIZE(struct timespec);
    PRINT_SIZE(((struct timespec *)0)->tv_sec);
    PRINT_SIZE(((struct timespec *)0)->tv_nsec);
    PRINT_SIZE(size_t);
    PRINT_SIZE(ssize_t);
    PRINT_SIZE(char);
    PRINT_SIZE(unsigned char);
    PRINT_SIZE(short);
    PRINT_SIZE(unsigned short);
    PRINT_SIZE(int);
    PRINT_SIZE(unsigned int);
    PRINT_SIZE(long);
    PRINT_SIZE(unsigned long);
    PRINT_SIZE(long int);
    PRINT_SIZE(long long);
    PRINT_SIZE(float);
    PRINT_SIZE(double);
    PRINT_SIZE(long double);
    PRINT_SIZE(int8_t);
    PRINT_SIZE(int16_t);
    PRINT_SIZE(int32_t);
    PRINT_SIZE(int64_t);
    PRINT_SIZE(uint8_t);
    PRINT_SIZE(uint16_t);
    PRINT_SIZE(uint32_t);
    PRINT_SIZE(uint64_t);
    PRINT_SIZE(int_fast8_t);
    PRINT_SIZE(int_fast16_t);
    PRINT_SIZE(int_fast32_t);
    PRINT_SIZE(int_fast64_t);
    PRINT_SIZE(int_least8_t);
    PRINT_SIZE(int_least16_t);
    PRINT_SIZE(int_least32_t);
    PRINT_SIZE(int_least64_t);
    PRINT_SIZE(enum_define);
    return 0;
}
