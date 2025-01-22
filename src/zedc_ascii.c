#include "zlib.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DEFAULT_PARAM -99

#pragma convert("IBM-1047")
static char *version_ebsidic = ZLIB_VERSION;
#pragma convert(pop)

typedef struct initparams {
  int level;
  int method;
  int windowBits;
  int memLevel;
  int strategy;
  const char *version;
  int stream_size;
} InitParams_t;


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

const char *  __zlibVersion_orig (void) __asm("zlibVersion");

int __deflate_orig (z_streamp strm, int flush) __asm("deflate");
int __inflate_orig (z_streamp strm, int flush) __asm("inflate");
int __deflateEnd_orig (z_streamp strm) __asm("DEEND");
int __inflateEnd_orig (z_streamp strm) __asm("INEND");
int __deflateReset_orig (z_streamp strm) __asm("deflateReset");
int __inflateReset_orig (z_streamp strm) __asm("inflateReset");


void store_params(z_streamp strm, 
    int  level,
    int  method,
    int  windowBits,
    int  memLevel,
    int  strategy,
    char *version,
    int stream_size)
{
    InitParams_t *p = calloc(1, sizeof(InitParams_t));
    if (p != NULL) {
        p->level = level;
        p->method = method;
        p->windowBits = windowBits;
        p->memLevel = memLevel;
        p->strategy = strategy;
        p->version = version;
        p->stream_size = stream_size;
        strm->reserved = (uLong)p;
    } else {
        fprintf(stderr, "Memory allocation failed for store_params\n");
    }
}

void free_params(z_streamp strm)
{
    InitParams_t *p = (InitParams_t*)strm->reserved;
    free(p);
    strm->reserved = 0;
}

void get_params(z_streamp strm, InitParams_t* param)
{
    memcpy(param, (InitParams_t*)strm->reserved, sizeof(InitParams_t));
}

void msg_to_ascii(z_streamp strm)
{
     if(strm->msg != NULL) {
        __e2a_s(strm->msg);    
     }
}

  /* For consistency deflateInit()/inflateInit() call compares zlib library version
   * that is defined in the library with the version defined in the header zlib.h
   * (ZLIB_VERSION). It works fine for zlib-based program that is built in EBCDIC
   * mode, but for ASCII program we get the error Z_VERSION_ERROR. The reason is
   * that IBM zlib library is built in EBCDIC mode and all string literals that are
   * used in the library are saved in EBCDIC encoding, but when we use zlib.h header
   * in ASCII program, all string literals from the header are converted to ASCII
   * encoding. Such string with library version in ASCII encoding is passed into the
   * internal function deflateInit_()/inflateInit_() (see zlib.h) and, when that
   * function is trying to compare the strings with the same content but in different
   * encodings, it returns the error Z_VERSION_ERROR. To avoid such behavior we can
   * convert "version" variable to EBSIDIC mode before passing to zedc functions.  (see how
   * the function deflateInit()/inflateInit() is defined in zlib.h). */

int __deflateInit_ascii(strm, level, version, stream_size)
    z_streamp strm;
    int level;
    const char *version;
    int stream_size;
{
    (void)version;
    int ret = __deflateInit_orig(strm, level, version_ebsidic, stream_size);
    msg_to_ascii(strm);

    if(ret == Z_OK)
    {
      store_params(strm, level, DEFAULT_PARAM, DEFAULT_PARAM, DEFAULT_PARAM, DEFAULT_PARAM,
                  version_ebsidic, stream_size);
    }

    return ret;
}


int __inflateInit_ascii(strm, version, stream_size)
    z_streamp strm;
    const char *version;
    int stream_size;
{
    (void)version;
    int ret = __inflateInit_orig(strm, version_ebsidic, stream_size);
    msg_to_ascii(strm);

    if(ret == Z_OK)
    {
      store_params(strm, DEFAULT_PARAM, DEFAULT_PARAM, DEFAULT_PARAM, DEFAULT_PARAM, DEFAULT_PARAM,
                  version_ebsidic, stream_size);
    }

    return ret;
}


int __deflateInit2_ascii(strm, level, method, windowBits, memLevel, strategy,
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
    (void)version;

    int ret = __deflateInit2_orig(strm, level, method, windowBits, memLevel, strategy,
                  version_ebsidic, stream_size);
    msg_to_ascii(strm);
    
    if(ret == Z_OK) {
      store_params(strm, level, method, windowBits, memLevel, strategy,
                  version_ebsidic, stream_size);
    }

    return ret;
}



int __inflateInit2_ascii(strm, windowBits, version, stream_size)
    z_streamp strm;
    int windowBits;
    const char *version;
    int stream_size;
{
    (void)version;
    int ret = __inflateInit2_orig(strm, windowBits, version_ebsidic, stream_size);
    msg_to_ascii(strm);

    if(ret == Z_OK)
    {
      store_params(strm, DEFAULT_PARAM, DEFAULT_PARAM, windowBits, DEFAULT_PARAM, DEFAULT_PARAM,
                  version_ebsidic, stream_size);
    }
    return ret;
}


int __inflateBackInit_ascii(strm, windowBits, window, version, stream_size)
    z_streamp strm;
    int windowBits;
    unsigned char FAR *window;
    const char *version;
    int stream_size;
{
    (void)version;
    int ret = __inflateBackInit_orig(strm, windowBits, window, version_ebsidic, stream_size);
    msg_to_ascii(strm);
    return ret;
}

int __deflate_ascii (z_streamp strm, int flush)
{
    int ret = __deflate_orig(strm, flush);
    msg_to_ascii(strm);
    return ret;
}

int __inflate_ascii (z_streamp strm, int flush)
{
    int ret = __inflate_orig(strm, flush);
    msg_to_ascii(strm);
    return ret;
}

int __deflateEnd_ascii (z_streamp strm)
{
    int ret;
    free_params(strm);
    ret = __deflateEnd_orig(strm);
    msg_to_ascii(strm);
    return ret;
}

int __inflateEnd_ascii (z_streamp strm)
{
    int ret;
    free_params(strm);
    ret = __inflateEnd_orig(strm);
    msg_to_ascii(strm);
    return ret;
}

int __deflateReset_ascii (z_streamp strm)
{
    int ret;
    InitParams_t p;
    get_params(strm, &p);

    ret = __deflateEnd_ascii(strm);

    if(ret != Z_OK)
      return ret;

    if(p.strategy != DEFAULT_PARAM) {
        ret = __deflateInit2_ascii(strm, p.level, p.method, p.windowBits, p.memLevel, p.strategy, p.version, p.stream_size);
    } else {  
        ret = __deflateInit_ascii(strm, p.level, p.version, p.stream_size);
    }

    return ret;
}

int __inflateReset_ascii (z_streamp strm)
{
    int ret;
    InitParams_t p;
    get_params(strm, &p);
    
    ret = __inflateEnd_ascii(strm);

    if(ret != Z_OK)
      return ret;

    if(p.windowBits != DEFAULT_PARAM) {
        ret = __inflateInit2_ascii(strm, p.windowBits, p.version, p.stream_size);
    } else {
        ret = __inflateInit_ascii(strm, p.version, p.stream_size);
    }

    return ret;
}

const char * __zlibVersion_ascii(void) {
    static int init = 0;
    static char version_ascii[15] = {0};
    if (!init) {
        strcpy(version_ascii, __zlibVersion_orig());
        __e2a_s(version_ascii);
        const char *suffix = "-zEDC";  // Remove zEDC suffix if present
        size_t suffix_len = strlen(suffix);
        char *pos = strstr(version_ascii, suffix);
        if (pos != NULL && pos + suffix_len == version_ascii + strlen(version_ascii)) {
            *pos = '\0';
        }
        init = 1;
    }
    return version_ascii;
}


#ifdef __cplusplus
}
#endif
