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
#define A 2
#define B 3
#define RET (A * B)
const int a = 2;
const int b = 3;
int main(int argc, char *argv[])
{
    int ret = RET;
    printf("%d\n", ret);
    ret = A * B;
    printf("%d\n", ret);
    ret = a * b;
    printf("%d\n", ret);
    return 0;
}
