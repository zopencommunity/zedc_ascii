#include "zlib.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

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

const char *  __zlibVersion_orig (void) __asm("zlibVersion");

static char version_ascii[15] = {0};

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
    char versionStr[15];
    strcpy(versionStr, version);
    __a2e_s(versionStr);

    int ret = __deflateInit_orig(strm, level, versionStr, stream_size);
    return ret;
}


int __inflateInit_ascii(strm, version, stream_size)
    z_streamp strm;
    const char *version;
    int stream_size;
{
    char versionStr[15];
    strcpy(versionStr, version);
    __a2e_s(versionStr);

    int ret = __inflateInit_orig(strm, versionStr, stream_size);
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
    char versionStr[15];
    strcpy(versionStr, version);
    __a2e_s(versionStr);

    int ret = __deflateInit2_orig(strm, level, method, windowBits, memLevel, strategy,
                  versionStr, stream_size);
    return ret;
}



int __inflateInit2_ascii(strm, windowBits, version, stream_size)
    z_streamp strm;
    int windowBits;
    const char *version;
    int stream_size;
{
    char versionStr[15];
    strcpy(versionStr, version);
    __a2e_s(versionStr);

    int ret = __inflateInit2_orig(strm, windowBits, versionStr, stream_size);
    return ret;
}


int __inflateBackInit_ascii(strm, windowBits, window, version, stream_size)
    z_streamp strm;
    int windowBits;
    unsigned char FAR *window;
    const char *version;
    int stream_size;
{
    char versionStr[15];
    strcpy(versionStr, version);
    __a2e_s(versionStr);

    int ret = __inflateBackInit_orig(strm, windowBits, window, versionStr, stream_size);
    return ret;
}


const char * __zlibVersion_ascii(void)
{
    static int init = 0;
    
    if(!init)
    {
      strcpy(version_ascii, __zlibVersion_orig());
      __e2a_s(version_ascii);

      const char* suffix = "-zEDC";  //Remove zEDC suffix if present
      size_t suffix_len = strlen(suffix);

      char* pos = strstr(version_ascii, suffix);

      if (pos != NULL) {
        if (pos + suffix_len == version_ascii + strlen(version_ascii)) {
          *pos = '\0'; 
	}
      }

      init = 1;
    }
    return version_ascii;
}

#ifdef __cplusplus
}
#endif
