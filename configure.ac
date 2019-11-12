# *************************************************************************
#
# Copyright (C) 2019  yaofei zheng
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#

AC_INIT([demo_and_test], [0.0], [github.com/qwerty258/demo_and_test])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_PROG_CC
AC_PROG_CXX
AM_PROG_AR
AC_PROG_RANLIB
AC_SUBST([CFLAGS], ["-ggdb -Wall"])
AC_SUBST([CXXFLAGS], ["-ggdb -Wall"])
AC_SUBST([LDADD], [""])

AC_CONFIG_FILES([                   \
    Makefile                        \
    ffmpeg/Makefile                 \
    macro_vs_const/Makefile         \
    sizeof_data_types/Makefile      \
    socket_can/Makefile             \
    unordered_map_map_and_if_else/Makefile])

AC_OUTPUT
