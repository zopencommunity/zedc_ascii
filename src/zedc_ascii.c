#include "zlib.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DEFLATE_THRESHOLD_VAR "_HZC_DEFLATE_THRESHOLD"
#define INFLATE_THRESHOLD_VAR "_HZC_INFLATE_THRESHOLD"
#define COMPRESSION_METHOD_VAR "_HZC_COMPRESSION_METHOD"
#define COMPRESSION_METHOD_SOFTWARE "software"
#define MIN_THRESHOLD 1
#define MAX_THRESHOLD 9999999

#pragma convert("IBM-1047")
static char *version_ebsidic = ZLIB_VERSION;
#pragma convert(pop)

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


#define MSG_BUFFER_SIZE 256
#define MSG_BUFFER_COUNT 4

typedef struct {
    char buffers[MSG_BUFFER_COUNT][MSG_BUFFER_SIZE];
    int current;
} thread_msg_t;

static pthread_key_t msg_key;
static pthread_once_t msg_key_once = PTHREAD_ONCE_INIT;
static int msg_key_failed = 0;

static void msg_key_destroy(void *ptr) {
    free(ptr);
}

static void msg_key_make(void) {
    if (pthread_key_create(&msg_key, msg_key_destroy) != 0) {
        msg_key_failed = 1;
    }
}

void msg_to_ascii(z_streamp strm)
{
    if (strm->msg == NULL) return;

    if (pthread_once(&msg_key_once, msg_key_make) != 0 || msg_key_failed) {
        return;
    }

    thread_msg_t *msg_data = (thread_msg_t *)pthread_getspecific(msg_key);

    if (msg_data == NULL) {
        msg_data = (thread_msg_t *)calloc(1, sizeof(thread_msg_t));
        if (msg_data == NULL) return;
        if (pthread_setspecific(msg_key, msg_data) != 0) {
            free(msg_data);
            return;
        }
    }

    /* Check if strm->msg already points to one of our buffers */
    for (int i = 0; i < MSG_BUFFER_COUNT; ++i) {
        if (strm->msg == msg_data->buffers[i]) {
            return; /* Already converted */
        }
    }

    /* Copy and convert */
    char *buf = msg_data->buffers[msg_data->current];
    strncpy(buf, strm->msg, MSG_BUFFER_SIZE - 1);
    buf[MSG_BUFFER_SIZE - 1] = '\0';
    __e2a_s(buf);
    
    strm->msg = buf;
    msg_data->current = (msg_data->current + 1) % MSG_BUFFER_COUNT;
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

int __deflateInit_ascii(z_streamp strm, int level, const char *version, int stream_size)
{
    (void)version;
    int ret = __deflateInit_orig(strm, level, version_ebsidic, stream_size);
    msg_to_ascii(strm);
    return ret;
}


int __inflateInit_ascii(z_streamp strm, const char *version, int stream_size)
{
    (void)version;
    int ret = __inflateInit_orig(strm, version_ebsidic, stream_size);
    msg_to_ascii(strm);
    return ret;
}


int __deflateInit2_ascii(z_streamp strm, int level, int method, int windowBits, int memLevel, int strategy,
                  const char *version, int stream_size)
{
    (void)version;
    int ret = __deflateInit2_orig(strm, level, method, windowBits, memLevel, strategy,
                  version_ebsidic, stream_size);
    msg_to_ascii(strm);

    return ret;
}



int __inflateInit2_ascii(z_streamp strm, int windowBits, const char *version, int stream_size)
{
    (void)version;
    int ret = __inflateInit2_orig(strm, windowBits, version_ebsidic, stream_size);
    msg_to_ascii(strm);
    return ret;
}


int __inflateBackInit_ascii(z_streamp strm, int windowBits, unsigned char FAR *window, const char *version, int stream_size)
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
    int ret;
    ret = __inflate_orig(strm, flush);
    msg_to_ascii(strm);
    return ret;
}

int __deflateEnd_ascii (z_streamp strm)
{
    int ret;
    ret = __deflateEnd_orig(strm);
    msg_to_ascii(strm);
    return ret;
}

int __inflateEnd_ascii (z_streamp strm)
{
    int ret;
    ret = __inflateEnd_orig(strm);
    msg_to_ascii(strm);
    return ret;
}

int __deflateReset_ascii (z_streamp strm)
{
    int ret;
    ret = __deflateReset_orig(strm);
    msg_to_ascii(strm);
    return ret;
}

int __inflateReset_ascii (z_streamp strm)
{
    int ret;
    ret = __inflateReset_orig(strm);
    msg_to_ascii(strm);
    return ret;
}

const char * __zlibVersion_ascii(void) {
    static int init = 0;
    static char version_ascii[32] = {0};
    if (!init) {
        const char* orig_version = __zlibVersion_orig();
        strncpy(version_ascii, orig_version, sizeof(version_ascii) - 1);
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

__attribute__((constructor))
void set_threshold_variable() {
    const char *compression_method = getenv(COMPRESSION_METHOD_VAR);
    if (compression_method != NULL && strcmp(compression_method, COMPRESSION_METHOD_SOFTWARE) == 0) {
        return;
    }

    char value_str[12];
    snprintf(value_str, sizeof(value_str), "%d", MIN_THRESHOLD);

    if (getenv(DEFLATE_THRESHOLD_VAR) == NULL) {
        if (setenv(DEFLATE_THRESHOLD_VAR, value_str, 1) != 0) {
            fprintf(stderr, "Failed to set environment variable %s: %s\n", DEFLATE_THRESHOLD_VAR, strerror(errno));
        }
    }

    if (getenv(INFLATE_THRESHOLD_VAR) == NULL) {
        if (setenv(INFLATE_THRESHOLD_VAR, value_str, 1) != 0) {
            fprintf(stderr, "Failed to set environment variable %s: %s\n", INFLATE_THRESHOLD_VAR, strerror(errno));
        }
    }
}

#ifdef __cplusplus
}
#endif
