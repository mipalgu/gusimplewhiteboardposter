/*
 *  gusimplewhiteboardposter.cc
 *
 *  Created by Rene Hexel on 29/04/13.
 *  Copyright (c) 2013, 2014, 2016 Rene Hexel.
 *  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *
 *        This product includes software developed by Rene Hexel.
 *
 * 4. Neither the name of the author nor the names of contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * -----------------------------------------------------------------------
 * This program is free software; you can redistribute it and/or
 * modify it under the above terms or under the terms of the GNU
 * General Public License as published by the Free Software Foundation;
 * either version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see http://www.gnu.org/licenses/
 * or write to the Free Software Foundation, Inc., 51 Franklin Street,
 * Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#pragma clang diagnostic ignored "-Wunused-macros"

#undef __block
#define __block _xblock
#include <unistd.h> //optargs
#include <libgen.h>
#undef __block
#define __block __attribute__((__blocks__(byref)))

#ifndef WITHOUT_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

#include "gu_util.h"
#include "gugenericwhiteboardobject.h"
#include "guwhiteboardtypelist_generated.h"
#include "guwhiteboardposter.h"
#include "guwhiteboardgetter.h"

#define TYPE_HISTORY    ((string(".") + progname + "_wbtype_history").c_str())
#define VALUE_HISTORY(m)((string(".") + progname + "_" + m + "_history").c_str())

static const char *progname;
static const char * const SHUTDOWN_WHITEBOARD = "SHUTDOWN_WHITEBOARD";

using namespace std;
using namespace CPP_WHITEBOARD_NAMESPACE;

static __attribute__((__noreturn__)) void usage(const char *cmd)
{
    cerr << "Usage: " << cmd << "\t[-w whiteboard_name]\n\t\t\t[-m Message Type Str]\n\t\t\t[-d String Constructor for Message Type Str]\n\t\t\tNote: One msg/data posting per invocation." << endl;
    exit(EXIT_FAILURE);
}


#ifndef WITHOUT_READLINE

/**
 * Return a match if the given text can be found in the history list
 */
static char *history_matcher(const char *text, int state)
{
        static unsigned long len;
	static int list_index;
        
        if (!state)
        {
                list_index = 0;
                len = strlen(text);
        }

        for (; list_index < history_length;)
        {
                HIST_ENTRY *entry = history_get(history_base+list_index);

                if (!entry)
                {
                        fprintf(stderr, "Error getting history entry %d at offset %d\n", list_index, history_base+list_index);
                        continue;
                }

                const char *name = entry->line;
                list_index++;
                
                if (!name[0]) continue;
                if (len < 1 || strncasecmp(name, text, len) == 0)
                        return gu_strdup(name);
        }
        
        /* no names matched */
        return NULLPTR;
}

/**
 * Return a list of possible completions from history
 */
static char **history_completion (const char *text, int /*start*/, int /*end*/)
{
        return rl_completion_matches(text, history_matcher);
}

/**
 * Return the last line entered into history
 */
static const char *last_history(void)
{
        if (history_length <= 0) return NULLPTR;
        HIST_ENTRY *entry = history_get(history_base+history_length-1);
        if (!entry) return NULLPTR;

        return entry->line;
}

/**
 * load message type history
 */
static void load_type_history(void)
{
        clear_history();
        if (read_history(TYPE_HISTORY) != 0)
        {
                for (int i = 0; i < GSW_NUM_TYPES_DEFINED; i++)
                        add_history(WBTypes_stringValues[i]);

                add_history(SHUTDOWN_WHITEBOARD);
        }
}


/**
 * load message value history
 */
static void load_value_history(string msgtype)
{
        clear_history();
        read_history(VALUE_HISTORY(msgtype));
}

#endif // WITHOUT_READLINE



/**
 * read intput from the user and post
 */
static int read_input_and_post_to_whiteboard(gu_simple_whiteboard_descriptor *wbd, FILE *in)
{
	string previous_type, prompt, old_value;
        char *line = NULLPTR;
        size_t linecap = 0;
        ssize_t linelen;

        do
        {
#ifndef WITHOUT_READLINE
                if (in != stdin)
                {
#endif
                        linelen = getline(&line, &linecap, in);
                        if (linelen <= 0)
                                return ferror(in) ? EXIT_FAILURE : EXIT_SUCCESS;
#ifndef WITHOUT_READLINE
                }
                else
                {
                        load_type_history();
                        if (previous_type.length() == 0)
                        {
                                const char *h = last_history();
                                previous_type = h ? h : "";
                        }
                        prompt = string("msg type (") + previous_type + ")? ";
                        line = readline(prompt.c_str());
                }
#endif
                string msgtype(line);
                gu_trim(msgtype);
                if (!msgtype.length())
                        msgtype = previous_type;
#ifndef WITHOUT_READLINE
                else if (in == stdin && msgtype != previous_type)
                {
                        add_history(msgtype.c_str());
                        write_history(TYPE_HISTORY);
                }
#endif
                if (msgtype == "exit" || msgtype == "quit")
                        return EXIT_SUCCESS;
                if (msgtype == SHUTDOWN_WHITEBOARD)
                        return EXIT_FAILURE;    // XXX: should remove wb
                /*
                 * check if type is on known to the new whiteboard
                 */
                try
                {
                        previous_type = msgtype;
                        old_value = getmsg(msgtype, NULLPTR, wbd);
                        if (old_value == "##unsupported##")
                        {
                                cerr << msgtype << " (" << types_map[msgtype] << "): unsupported string conversion" << endl;
                                continue;
                        }
                }
                catch (...)
                {
                        cerr << msgtype << " (" << types_map[msgtype] << ") does not support string conversion" << endl;
                        continue;
                }
#ifndef WITHOUT_READLINE
                if (in != stdin)
                {
#endif
                        linelen = getline(&line, &linecap, in);
                        if (linelen <= 0)
                                return ferror(in) ? EXIT_FAILURE : EXIT_SUCCESS;
#ifndef WITHOUT_READLINE
                }
                else
                {
                        load_value_history(msgtype);
                        prompt = string("value (") + old_value + ")? ";
                        line = readline(prompt.c_str());
                }
#endif
                string value(line);
                gu_trim(value);
                if (!value.length())
                        value = old_value;
#ifndef WITHOUT_READLINE
                else if (in == stdin && value != old_value)
                {
                        add_history(value.c_str());
                        write_history(VALUE_HISTORY(msgtype));
                }
#endif
                if (post(msgtype, value, wbd))
                        old_value = value;
                else
                        cerr << "Could not set " << msgtype << " (" << types_map[msgtype] << ") to '" << value << "'" << endl;
        }
        while (!feof(in));

        return EXIT_SUCCESS;
}

static int cli_post_to_whiteboard(gu_simple_whiteboard_descriptor *wbd, const char* msgtype, const char* data)
{
    // Get message type
    string old_value;
    try
    {
        old_value = getmsg(msgtype, NULLPTR, wbd);
        if (old_value == "##unsupported##")
        {
            cerr << msgtype << " (" << types_map[msgtype] << "): unsupported string conversion" << endl;
            return EXIT_FAILURE;
        }
    }
    catch (...)
    {
        cerr << msgtype << " (" << types_map[msgtype] << ") does not support string conversion" << endl;
        return EXIT_FAILURE;
    }
    if (!post(msgtype, data, wbd))
    {
        cerr << "Could not set " << msgtype << " (" << types_map[msgtype] << ") to '" << data << "'" << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/**
 * Simplewhiteboard poster main function.
 * @param argv  no parameters are used except for the program name
 * @return EXIT_SUCCESS if exiting normally, EXIT_FAILURE if SHUTDOWN_WHITEBOARD command was issued or an unrecoverable error occurred.
 */
int main(int argc, char *argv[])
{
        progname = basename(argv[0]);
        bool cli = false;
        const char* msgType;
        const char* msgData;

#ifndef WITHOUT_READLINE
        using_history();
        rl_readline_name = const_cast<char *>(progname);
        rl_attempted_completion_function = history_completion;
#endif

#ifdef CUSTOM_WB_NAME
        const char *wbname = CUSTOM_WB_NAME;
#else
        const char *wbname = NULLPTR;
#endif
        gu_simple_whiteboard_descriptor *wbd = NULLPTR;
        int ch;
        while ((ch = getopt(argc, argv, "w:m:d:")) != -1) switch (ch)
        {
            case 'w':
                wbname = optarg;
                break;
            case 'm':
                if (cli)
                {
                    usage(argv[0]);  // Caller has already used '-m'.
                }
                msgType = optarg;
                cli = true;
                break;
            case 'd':
                msgData = optarg;
                break;
            case '?':
            default:
                usage(argv[0]);
        }

        int rv = 0;
        if (wbname) wbd = gsw_new_whiteboard(wbname);
        if (cli)
        {
            rv = cli_post_to_whiteboard(wbd, msgType, msgData);
        } else {
            rv = read_input_and_post_to_whiteboard(wbd, stdin);
        }
        if (wbd) gsw_free_whiteboard(wbd);

        return rv;
}



