#include "zlib.h"
#include <stdio.h>
#include <string.h>

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

int ZEXPORT __deflateInit_ascii(strm, level, version, stream_size)
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


int ZEXPORT __inflateInit_ascii(strm, version, stream_size)
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

    int ret = __deflateInit2_orig(strm, level, method, windowBits, memLevel, strategy,
                  versionStr, stream_size);
    return ret;
}



int ZEXPORT __inflateInit2_ascii(strm, windowBits, version, stream_size)
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


int ZEXPORT __inflateBackInit_ascii(strm, windowBits, window, version, stream_size)
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


const char * ZEXPORT __zlibVersion_ascii(void)
{
    static int init = 0;
    
    if(!init)
    {
      strcpy(version_ascii, __zlibVersion_orig());
      __e2a_s(version_ascii);

      const char* suffix = "-zEDC";
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
