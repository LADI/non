
/*******************************************************************************/
/* Copyright (C) 2008-2020 Jonathan Moore Liles (as "Non-Session-Manager")     */
/* Copyright (C) 2020- Nils Hilbricht                                          */
/*                                                                             */
/* This file is part of New-Session-Manager                                    */
/*                                                                             */
/* New-Session-Manager is free software: you can redistribute it and/or modify */
/* it under the terms of the GNU General Public License as published by        */
/* the Free Software Foundation, either version 3 of the License, or           */
/* (at your option) any later version.                                         */
/*                                                                             */
/* New-Session-Manager is distributed in the hope that it will be useful,      */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of              */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               */
/* GNU General Public License for more details.                                */
/*                                                                             */
/* You should have received a copy of the GNU General Public License           */
/* along with New-Session-Manager. If not, see <https://www.gnu.org/licenses/>.*/
/*******************************************************************************/


#include "debug.h"

#include <string.h>
#include <stdio.h>
#include <stdarg.h>

extern char * program_invocation_short_name;

bool quietMessages = false;

void
warnf ( warning_t level,
       const char *module,
       const char *file,
       const char *function, int line, const char *fmt, ... )
{
    va_list args;
    static const char *level_tab[] = {
        "message", "",
        "warning", "",
        "assertion", ""
    };

        module = program_invocation_short_name;

    if ( module )
        fprintf( stderr, "[%s] ", module );
#ifndef NDEBUG
    if ( file )
        fprintf( stderr, "%s", file );
    if ( line )
        fprintf( stderr, ":%i", line );
    if ( function )
        fprintf( stderr, " %s()", function );

    fprintf( stderr, ": " );
#endif

    if ( unsigned( ( level << 1 ) + 1 ) <
         ( sizeof( level_tab ) / sizeof( level_tab[0] ) ) )
        fprintf( stderr, "%s", level_tab[( level << 1 ) + 1] );

    if ( fmt )
    {
        va_start( args, fmt );
        vfprintf( stderr, fmt, args );
        va_end( args );
    }

    fprintf( stderr, "\n" );
}
