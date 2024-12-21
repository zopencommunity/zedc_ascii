#ifndef ZOS_ZLIB_H_
#define ZOS_ZLIB_H_

#include "zos-macros.h"

#define __XPLAT 1


#undef deflateInit_
#define deflateInit_ __deflateInit_replaced
#undef inflateInit_
#define inflateInit_ __inflateInit_replaced
#undef deflateInit2_
#define deflateInit2_ __deflateInit2__replaced
#undef inflateInit2_
#define inflateInit2_ __inflateInit2_replaced
#undef inflateBackInit_
#define inflateBackInit_ __inflateBackInit_replaced
#undef zlibVersion
#define zlibVersion __zlibVersion_replaced
#include_next <zlib.h>

#undef deflateInit_
#undef inflateInit_
#undef deflateInit2_
#undef inflateInit2_
#undef inflateBackInit_
#undef zlibVersion

#if defined(__cplusplus)
extern "C" {
#endif


__Z_EXPORT ZEXTERN int __deflateInit_ascii OF((z_streamp strm, int level,
                                     const char *version, int stream_size));
__Z_EXPORT ZEXTERN int __inflateInit_ascii OF((z_streamp strm,
                                     const char *version, int stream_size));
__Z_EXPORT ZEXTERN int __deflateInit2_ascii OF((z_streamp strm, int  level, int  method,
                                      int windowBits, int memLevel,
                                      int strategy, const char *version,
                                      int stream_size));
__Z_EXPORT ZEXTERN int __inflateInit2_ascii OF((z_streamp strm, int  windowBits,
                                      const char *version, int stream_size));
__Z_EXPORT ZEXTERN int __inflateBackInit_ascii OF((z_streamp strm, int windowBits,
                                         unsigned char FAR *window,
                                         const char *version,
                                         int stream_size));

__Z_EXPORT ZEXTERN const char *  __zlibVersion_ascii OF((void));

__Z_EXPORT ZEXTERN int deflateInit_ OF((z_streamp strm, int level,
                                     const char *version, int stream_size)) __asm("__deflateInit_ascii");
__Z_EXPORT ZEXTERN int inflateInit_ OF((z_streamp strm,
                                     const char *version, int stream_size)) __asm("__inflateInit_ascii");
__Z_EXPORT ZEXTERN int deflateInit2_ OF((z_streamp strm, int  level, int  method,
                                      int windowBits, int memLevel,
                                      int strategy, const char *version,
                                      int stream_size)) __asm("__deflateInit2_ascii");
__Z_EXPORT ZEXTERN int inflateInit2_ OF((z_streamp strm, int  windowBits,
                                      const char *version, int stream_size)) __asm("__inflateInit2_ascii");
__Z_EXPORT ZEXTERN int inflateBackInit_ OF((z_streamp strm, int windowBits,
                                         unsigned char FAR *window,
                                         const char *version,
                                         int stream_size)) __asm("__inflateBackInit_ascii");

__Z_EXPORT ZEXTERN const char *  zlibVersion OF((void)) __asm("__zlibVersion_ascii");

#if defined(__cplusplus)
}
#endif

#endif
