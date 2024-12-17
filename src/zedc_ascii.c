#include "zlib.h"
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif

int __deflateInit_orig (z_streamp strm, int level, const char *version, int stream_size) __asm("DEIN");

int __inflateInit_orig (z_streamp strm, const char *version, int stream_size) __asm("ININ");

int __deflateInit2_orig (z_streamp strm, int  level, int  method,
                                      int windowBits, int memLevel,
                                      int strategy, const char *version,
                                      int stream_size) __asm("DEIN2");

int __inflateInit2_orig (z_streamp strm, int  windowBits,
                                      const char *version, int stream_size) __asm("ININ2");

int __inflateBackInit_orig (z_streamp strm, int windowBits,
                                         unsigned char FAR *window,
                                         const char *version,
                                         int stream_size) __asm("inflateBackInit_");


int ZEXPORT __deflateInit_ascii(strm, level, version, stream_size)
    z_streamp strm;
    int level;
    const char *version;
    int stream_size;
{
    fprintf(stderr, "Wrapper called. __deflateInit_ascii\n");
#pragma convert("IBM-1047")
    int ret = __deflateInit_orig(strm, level, version, stream_size);
#pragma convert(pop)
    return ret;
}


int ZEXPORT __inflateInit_ascii(strm, version, stream_size)
    z_streamp strm;
    const char *version;
    int stream_size;
{
    fprintf(stderr, "Wrapper called __inflateInit_ascii\n");
#pragma convert("IBM-1047")
    int ret = __inflateInit_orig(strm, version, stream_size);
#pragma convert(pop)
    return ret;
}


int ZEXPORT __deflateInit2_ascii(strm, level, method, windowBits, memLevel, strategy,
                  version, stream_size)
    z_streamp strm;
    int  level;
    int  method;
    int  windowBits;
    int  memLevel;
    int  strategy;
    const char *version;
    int stream_size;
{
    char versionStr[15];
    strcpy(versionStr, version);
    __a2e_s(versionStr);

    fprintf(stderr, "Wrapper called. __deflateInit2_ascii \n");
    
    fprintf(stderr,"level %d\n", level);
    fprintf(stderr,"method %d\n", method);
    fprintf(stderr,"windowBits %d\n", windowBits);
    fprintf(stderr, "memlevel %d\n", memLevel);
    fprintf(stderr,"strategy %d\n", strategy);
    fprintf(stderr,"stream_size %d\n", stream_size);
    fprintf(stderr, "version %s\n", version);

    int ret = __deflateInit2_orig(strm, level, method, windowBits, memLevel, strategy,
                  versionStr, stream_size);
    fprintf(stderr, "__deflateInit2_ascii returned %d\n", ret);
    return ret;
}



int ZEXPORT __inflateInit2_ascii(strm, windowBits, version, stream_size)
    z_streamp strm;
    int windowBits;
    const char *version;
    int stream_size;
{
    fprintf(stderr, "Wrapper called. __inflateInit2_ascii\n");
#pragma convert("IBM-1047")
	int ret = __inflateInit2_orig(strm, windowBits, version, stream_size);
#pragma convert(pop)
	return ret;
}


int ZEXPORT __inflateBackInit_ascii(strm, windowBits, window, version, stream_size)
    z_streamp strm;
    int windowBits;
    unsigned char FAR *window;
    const char *version;
    int stream_size;
{
    fprintf(stderr, "Wrapper called. __inflateBackInit_ascii\n");
#pragma convert("IBM-1047")
   int ret = __inflateBackInit_orig(strm, windowBits, window, version, stream_size);
#pragma convert(pop)
}

#ifdef __cplusplus
}
#endif
