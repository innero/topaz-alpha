/**
 * Topaz Tools - Spinning progress bar
 *
 * Copyright (c) 2014, T Parys
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <topaz/spinner.h>
using namespace topaz;

// Spinner characters
char const *spin_chars = "|/-\\";

// Constructor
spinner::spinner(int max)
    : cur(0), max(max), width(80), old_pos(0)
{
    int i;

    // Initial layout
    for (i = 0; i < width - 1; i++)
    {
        putchar(' ');
    }
    fputs("|\r| ", stdout);
    fflush(stdout);

    // Account for left/right edges
    width -= 2;
}

// Destructor
spinner::~spinner()
{
    putchar('\n');
    fflush(stdout);
}

// Mutator
void spinner::tick(int count)
{
    int new_pos;

    // Increment
    cur += count;

    // Calculate new position on progress
    new_pos = round((double)cur * width / max);

    // Move back one character
    putchar('\b');

    // Place progress meter, if appropriate
    for (int i = 0; i < (new_pos - old_pos); i++)
    {
        putchar('=');
    }
    old_pos = new_pos;

    // Update spinner
    putchar(spin_chars[cur % 4]);

    // Flush
    fflush(stdout);
}


