/*
    Anthon Uniform Configuration Helper
    Copyright (C) 2016 bobcao3 <bobcaocheng@163.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "virtrootfs.h"

void log_internal(const char* function_name, const char* format, ...) {
  time_t time_t_time = time(NULL);
  va_list ap;
  va_start(ap, format);
  printf("[%d][%s][%s] ", time_t_time, "DBG Log", function_name);
  vprintf(format, ap);
  putchar('\n');
  va_end(ap);
}
