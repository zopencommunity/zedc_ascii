#ifndef ZOS_ZLIB_H_
#define ZOS_ZLIB_H_

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


extern int __deflateInit_ascii OF((z_streamp strm, int level,
                                     const char *version, int stream_size));
extern int __inflateInit_ascii OF((z_streamp strm,
                                     const char *version, int stream_size));
extern int __deflateInit2_ascii OF((z_streamp strm, int  level, int  method,
                                      int windowBits, int memLevel,
                                      int strategy, const char *version,
                                      int stream_size));
extern int __inflateInit2_ascii OF((z_streamp strm, int  windowBits,
                                      const char *version, int stream_size));
extern int __inflateBackInit_ascii OF((z_streamp strm, int windowBits,
                                         unsigned char FAR *window,
                                         const char *version,
                                         int stream_size));

extern const char *  __zlibVersion_ascii OF((void));

extern int deflateInit_ OF((z_streamp strm, int level,
                                     const char *version, int stream_size)) __asm("__deflateInit_ascii");
extern int inflateInit_ OF((z_streamp strm,
                                     const char *version, int stream_size)) __asm("__inflateInit_ascii");
extern int deflateInit2_ OF((z_streamp strm, int  level, int  method,
                                      int windowBits, int memLevel,
                                      int strategy, const char *version,
                                      int stream_size)) __asm("__deflateInit2_ascii");
extern int inflateInit2_ OF((z_streamp strm, int  windowBits,
                                      const char *version, int stream_size)) __asm("__inflateInit2_ascii");
extern int inflateBackInit_ OF((z_streamp strm, int windowBits,
                                         unsigned char FAR *window,
                                         const char *version,
                                         int stream_size)) __asm("__inflateBackInit_ascii");

extern const char *  zlibVersion OF((void)) __asm("__zlibVersion_ascii");

#if defined(__cplusplus)
}
#endif

#endif
