#define ZLIB_VERSION "1.2.11"
#define ZLIB_VERNUM 0x12b0
#define ZLIB_VER_MAJOR 1
#define ZLIB_VER_MINOR 2
#define ZLIB_VER_REVISION 11

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
#undef deflate
#define deflate __deflate__replaced
#undef inflate
#define inflate __inflate__replaced
#undef deflateEnd
#define deflateEnd __deflateEnd__replaced
#undef inflateEnd
#define inflateEnd __inflateEnd__replaced
#undef deflateReset
#define deflateReset __deflateReset_replaced
#undef inflateReset
#define inflateReset __inflateReset_replaced
#undef gzopen
#define gzopen __gzopen_replaced
#undef gzdopen
#define gzdopen __gzdopen_replaced
#undef gzgets
#define gzgets __gzgets_replaced
#undef gzputs
#define gzputs __gzputs_replaced

#include_next <zlib.h>

#undef deflateInit_
#undef inflateInit_
#undef deflateInit2_
#undef inflateInit2_
#undef inflateBackInit_
#undef zlibVersion
#undef deflate
#undef inflate
#undef deflateEnd
#undef inflateEnd
#undef deflateReset
#undef inflateReset
#undef gzopen
#undef gzdopen
#undef gzgets
#undef gzputs

#if defined(__cplusplus)
extern "C" {
#endif

extern int __deflateInit_ascii OF((z_streamp strm, int level, const char *version, int stream_size));
extern int __inflateInit_ascii OF((z_streamp strm, const char *version, int stream_size));
extern int __deflateInit2_ascii OF((z_streamp strm, int level, int method, int windowBits, int memLevel, int strategy, const char *version, int stream_size));
extern int __inflateInit2_ascii OF((z_streamp strm, int windowBits, const char *version, int stream_size));
extern int __inflateBackInit_ascii OF((z_streamp strm, int windowBits, unsigned char FAR *window, const char *version, int stream_size));

extern const char * __zlibVersion_ascii OF((void));
extern int __deflate_ascii OF((z_streamp strm, int flush));
extern int __inflate_ascii OF((z_streamp strm, int flush));
extern int __deflateEnd_ascii OF((z_streamp strm));
extern int __inflateEnd_ascii OF((z_streamp strm));
extern int __deflateReset_ascii OF((z_streamp strm));
extern int __inflateReset_ascii OF((z_streamp strm));

extern gzFile __gzopen_ascii OF((const char *path, const char *mode));
extern gzFile __gzdopen_ascii OF((int fd, const char *mode));
extern char * __gzgets_ascii OF((gzFile file, char *buf, int len));
extern int    __gzputs_ascii OF((gzFile file, const char *s));

extern int deflateInit_ OF((z_streamp strm, int level, const char *version, int stream_size)) __asm("__deflateInit_ascii");
extern int inflateInit_ OF((z_streamp strm, const char *version, int stream_size)) __asm("__inflateInit_ascii");
extern int deflateInit2_ OF((z_streamp strm, int level, int method, int windowBits, int memLevel, int strategy, const char *version, int stream_size)) __asm("__deflateInit2_ascii");
extern int inflateInit2_ OF((z_streamp strm, int windowBits, const char *version, int stream_size)) __asm("__inflateInit2_ascii");
extern int inflateBackInit_ OF((z_streamp strm, int windowBits, unsigned char FAR *window, const char *version, int stream_size)) __asm("__inflateBackInit_ascii");

extern const char * zlibVersion OF((void)) __asm("__zlibVersion_ascii");
extern int deflate OF((z_streamp strm, int flush)) __asm("__deflate_ascii");
extern int inflate OF((z_streamp strm, int flush)) __asm("__inflate_ascii");
extern int deflateEnd OF((z_streamp strm)) __asm("__deflateEnd_ascii");
extern int inflateEnd OF((z_streamp strm)) __asm("__inflateEnd_ascii");
extern int deflateReset OF((z_streamp strm)) __asm("__deflateReset_ascii");
extern int inflateReset OF((z_streamp strm)) __asm("__inflateReset_ascii");

extern gzFile gzopen OF((const char *path, const char *mode)) __asm("__gzopen_ascii");
extern gzFile gzdopen OF((int fd, const char *mode)) __asm("__gzdopen_ascii");
extern char * gzgets OF((gzFile file, char *buf, int len)) __asm("__gzgets_ascii");
extern int    gzputs OF((gzFile file, const char *s)) __asm("__gzputs_ascii");

#if defined(__cplusplus)
}
#endif

#endif
