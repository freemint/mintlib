/* Tester for calling inline string functions.
   Copyright (C) 1998 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <string.h>
#include <assert.h>

static int testcmp(const char* s1, const char* s2)
{
    int cmp = strcmp(s1, s2);
    if (cmp>0) {
        printf("'%s' > '%s'\n", s1, s2);
    } else if (cmp<0) {
        printf("'%s' < '%s'\n", s1, s2);
    } else {
        printf("'%s' = '%s'\n", s1, s2);
    }
    return cmp;
}

static void testmemchr(void)
{
    char tb[] = "abcdef\0ghijkl";

    assert(memchr(tb, 'a', 10) == tb);
    assert(memchr(tb, 'f', 10) != tb);
}

int main(void)
{
	int cmp;

    cmp = testcmp("abc", "def");
    assert(cmp < 0);
    cmp = testcmp("def", "def");
    assert(cmp == 0);
    cmp = testcmp("def", "abc");
    assert(cmp > 0);
    
    cmp = testcmp("abc", "");
    assert(cmp > 0);
    cmp = testcmp("abc", "ab");
    assert(cmp > 0);
    cmp = testcmp("", "abc");
    assert(cmp < 0);
    cmp = testcmp("ab", "abc");
    assert(cmp < 0);
    cmp = testcmp("ab\204d", "abcd");
    assert(cmp > 0);
    cmp = testcmp("ab\204", "ab");
    assert(cmp > 0);
    cmp = testcmp("ab", "ab\204");
    assert(cmp < 0);
    cmp = testcmp("abcd", "ab\204d");
    assert(cmp < 0);
    cmp = testcmp("ab\204d", "ab\204d");
    assert(cmp == 0);

    testmemchr();

    return 0;
}
