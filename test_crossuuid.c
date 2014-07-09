/*

The MIT License (MIT)

Copyright (c) 2014 Guilherme Steinmann

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

/* test_crossuuid.c */

#include "crossuuid.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FAIL_IF(func,msg) if(func==0){fprintf(stderr, "ERROR on line %d: %s\n",__LINE__,msg);exit(1);}

int main(int argc, char** argv)
{
	char buffer[64];

	crossuuid_t d, d2;
	crossuuid_generate(d);

	FAIL_IF(crossuuid_string(d, buffer, sizeof(buffer)), "crossuuid_string");
	fprintf(stderr, "UUID 1(%d): %s\n", (int)strlen(buffer), buffer);

	FAIL_IF(crossuuid_fromString(d2, buffer), "crossuuid_fromString");

	FAIL_IF(crossuuid_string(d2, buffer, sizeof(buffer)), "crossuuid_string");
	fprintf(stderr, "UUID 2(%d): %s\n", (int)strlen(buffer), buffer);

	FAIL_IF(crossuuid_equals(d, d2), "crossuuid_equals");
	crossuuid_clear(d);

	return 0;
}
