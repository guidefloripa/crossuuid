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

/* crossuuid.c */

#include "crossuuid.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef HAVE_APPLE
#include <CoreFoundation/CFUUID.h>
#endif

#ifdef HAVE_WINDOWS
#include <objbase.h>
#endif

#ifdef HAVE_LIBUUID
#include <uuid/uuid.h>
#endif

#define CROSSUUID_LEN sizeof(crossuuid_t)
#define CROSSUUID_STRING_LEN 36 /* 32 + 4 (bytes in hex + 4 slashes) */

static void _generate_uuid_bytes(crossuuid_t data);
static unsigned char _get_uchar_hexvalue(char ch);
static unsigned char _get_uchar(char a, char b);

/*---------------------------------------------------------------------------*/

void crossuuid_generate(crossuuid_t data)
{
	_generate_uuid_bytes(data);
}

/*---------------------------------------------------------------------------*/

void crossuuid_clear(crossuuid_t data)
{
	memset(data, 0, sizeof(crossuuid_t));
}

/*---------------------------------------------------------------------------*/

int crossuuid_equals(crossuuid_t d1, crossuuid_t d2)
{
	return d1 && d2 && memcmp(d1, d2, sizeof(crossuuid_t))==0 ? 1 : 0;
}

/*---------------------------------------------------------------------------*/

int crossuuid_string(const crossuuid_t data, char* buffer, int len)
{
	int i, offset;

	if (!data) return 0;
	if (!buffer) return 0;
	if (len <= CROSSUUID_STRING_LEN) return 0;

	offset = 0;
	for (i=0; i<CROSSUUID_LEN; i++) {
		if (i==4 || i==6 || i==8 || i==10) {
			buffer[2*i+offset] = '-';
			offset++;
		}
		sprintf(&buffer[(2*i)+offset], "%02x", (int)data[i]);
	}

	return 1;
}

/*---------------------------------------------------------------------------*/

int crossuuid_fromString(crossuuid_t data, const char* uuid_string)
{
	int i, offset;

	if (!data) return 0;
	if (!uuid_string) return 0;
	if ((int)strlen(uuid_string) < CROSSUUID_STRING_LEN) return 0;

	offset = 0;
	for (i=0; i<CROSSUUID_LEN; i++) {
		if (i==4 || i==6 || i==8 || i==10) {
			if (uuid_string[2*i+offset] == '-') {
				offset++;
			}
		}
		data[i] = _get_uchar(uuid_string[2*i+offset], uuid_string[2*i+offset+1]);
	}

	return 1;
}

/*---------------------------------------------------------------------------*/

unsigned char _get_uchar_hexvalue(char ch)
{
	if (ch>='0' && ch<='9')
		return ch - '0';
	if (ch>='a' && ch<='f')
		return ch - 'a' + 10;
	if (ch>='A' && ch<='F')
		return ch - 'A' + 10;
	return 0;
}

/*---------------------------------------------------------------------------*/

unsigned char _get_uchar(char a, char b)
{
	return 16*_get_uchar_hexvalue(a) + _get_uchar_hexvalue(b);
}

/*---------------------------------------------------------------------------*/

#ifdef HAVE_APPLE
void _generate_uuid_bytes(crossuuid_t data)
{
	CFUUIDRef id;
	CFUUIDBytes idbytes;

	id = CFUUIDCreate(NULL);
	idbytes = CFUUIDGetUUIDBytes(id);
	CFRelease(id);

	data[0]  = idbytes.byte0;
	data[1]  = idbytes.byte1;
	data[2]  = idbytes.byte2;
	data[3]  = idbytes.byte3;
	data[4]  = idbytes.byte4;
	data[5]  = idbytes.byte5;
	data[6]  = idbytes.byte6;
	data[7]  = idbytes.byte7;
	data[8]  = idbytes.byte8;
	data[9]  = idbytes.byte9;
	data[10] = idbytes.byte10;
	data[11] = idbytes.byte11;
	data[12] = idbytes.byte12;
	data[13] = idbytes.byte13;
	data[14] = idbytes.byte14;
	data[15] = idbytes.byte15;
}
#endif

/*---------------------------------------------------------------------------*/

#ifdef HAVE_WINDOWS
void _generate_uuid_bytes(crossuuid_t data)
{
	GUID id;
	if (CoCreateGuid(&id)!= S_OK) {
		memset(data, 0, sizeof(data));
		return;
	}

	data[0]  = (id.Data1 >> 24) & 0xFF;
	data[1]  = (id.Data1 >> 16) & 0xFF;
	data[2]  = (id.Data1 >> 8) & 0xFF;
	data[3]  = (id.Data1) & 0xff;

	data[4]  = (id.Data2 >> 8) & 0xFF;
	data[5]  = (id.Data2) & 0xff;

	data[6]  = (id.Data3 >> 8) & 0xFF;
	data[7]  = (id.Data3) & 0xFF;

	data[8]  = id.Data4[0];
	data[9]  = id.Data4[1];
	data[10] = id.Data4[2];
	data[11] = id.Data4[3];
	data[12] = id.Data4[4];
	data[13] = id.Data4[5];
	data[14] = id.Data4[6];
	data[15] = id.Data4[7];
}
#endif

/*---------------------------------------------------------------------------*/

#ifdef HAVE_LIBUUID
void _generate_uuid_bytes(crossuuid_t data)
{
	uuid_t id;
	uuid_generate(id);
	memcpy(data, id, sizeof(uuid_data));
}
#endif

/*---------------------------------------------------------------------------*/
