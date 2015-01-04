/*
    Copyright (c) 2014-2015 Wirebird Labs LLC. All rights reserved.

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom
    the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#ifndef FTW_PCRE_H_INCLUDED
#define FTW_PCRE_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/*  Suppress exporting PCRE functions since they are statically linked. */
#define PCRE_EXP_DECL

#include "../ftw.h"
#include "upstream/pcre.h"

/*  FTW-PCRE types. */
struct ftw_pcre_callout_data {
    int32_t callout_id;
    int32_t subject_current_pos;
    int32_t subject_start_match_pos;
    int32_t capture_top;
    int32_t capture_last;
    int32_t pattern_position;
};

typedef struct {
    int32_t dimsize;
    struct ftw_pcre_callout_data element[1];
} CalloutAccumulator;

struct ftw_callout_args {

    /*  Buffer that stores an array of callback data. */
    CalloutAccumulator **accumulator;

    /*  Current write position into the callback array. */
    int32_t  index;

    /*  Change these parameters to control how the accumulator grows. */
    int32_t  num_elements_increment;
};

/*  FTW-PCRE exported functions. */
FTW_EXPORT const char *ftw_pcre_version(void);

FTW_EXPORT pcre *ftw_pcre_compile(const char *regex, int options, LStrHandle error_string,
    int32_t *error_offset_in_regex);

FTW_EXPORT int32_t ftw_pcre_capture_groups(const pcre *compiled_regex,
    LStrHandleArray **named_capturing_groups);

FTW_EXPORT intptr_t ftw_pcre_exec(const pcre *compiled_regex, const LStrHandle subject,
    int32_t startoffset, int32_t options, int32_t *match_begin, int32_t *match_end,
    I32Array **submatch_buffer, CalloutAccumulator **callout);

FTW_EXPORT void ftw_pcre_free(pcre *compiled_regex);

#ifdef __cplusplus
}
#endif

#endif
