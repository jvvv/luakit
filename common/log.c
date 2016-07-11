/*
 * common/log.c - logging functions
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "globalconf.h"
#include "common/log.h"

#include <glib/gprintf.h>
#include <stdlib.h>
#include <unistd.h>

/* Print error and exit with EXIT_FAILURE code. */
void
_fatal(gint line, const gchar *fct, const gchar *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    va_fatal(line, fct, fmt, ap);
    va_end(ap);
}

void
va_fatal(gint line, const gchar *fct, const gchar *fmt, va_list ap) {
    gint atty = isatty(STDERR_FILENO);
    if (atty) g_fprintf(stderr, ANSI_COLOR_BG_RED);
    g_fprintf(stderr, "[%#12f] ", l_time() - globalconf.starttime);
    g_fprintf(stderr, "E: %s:%d: ", fct, line);
    g_vfprintf(stderr, fmt, ap);
    if (atty) g_fprintf(stderr, ANSI_COLOR_RESET);
    g_fprintf(stderr, "\n");
    exit(EXIT_FAILURE);
}

/* Print error message on stderr. */
void
_warn(gint line, const gchar *fct, const gchar *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    va_warn(line, fct, fmt, ap);
    va_end(ap);
}

void
va_warn(gint line, const gchar *fct, const gchar *fmt, va_list ap) {
    gint atty = isatty(STDERR_FILENO);
    if (atty) g_fprintf(stderr, ANSI_COLOR_RED);
    g_fprintf(stderr, "[%#12f] ", l_time() - globalconf.starttime);
    g_fprintf(stderr, "E: %s:%d: ", fct, line);
    g_vfprintf(stderr, fmt, ap);
    if (atty) g_fprintf(stderr, ANSI_COLOR_RESET);
    g_fprintf(stderr, "\n");
}

/* Print debug message on stderr. */
void
_debug(gint line, const gchar *fct, const gchar *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    va_debug(line, fct, fmt, ap);
    va_end(ap);
}

void
va_debug(gint line, const gchar *fct, const gchar *fmt, va_list ap) {
    if (globalconf.verbose) {
        g_fprintf(stderr, "[%#12f] ", l_time() - globalconf.starttime);
        g_fprintf(stderr, "D: %s:%d: ", fct, line);
        g_vfprintf(stderr, fmt, ap);
        g_fprintf(stderr, "\n");
    }
}

// vim: ft=c:et:sw=4:ts=8:sts=4:tw=80
