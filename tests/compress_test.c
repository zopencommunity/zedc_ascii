#include "zlib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    const char *data = "This is a test of the zEDC-enabled zlib library on z/OS. "
                       "It should be able to compress and decompress this data correctly. "
                       "We are using a somewhat long string to ensure it's worth compressing.";
    uLong sourceLen = strlen(data) + 1;
    uLong destLen = compressBound(sourceLen);
    unsigned char *dest = (unsigned char *)malloc(destLen);
    unsigned char *uncompressed = (unsigned char *)malloc(sourceLen);

    if (dest == NULL || uncompressed == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Original data: %s\n", data);
    printf("Original length: %lu\n", sourceLen);

    int res = compress(dest, &destLen, (const unsigned char *)data, sourceLen);
    if (res != Z_OK) {
        fprintf(stderr, "Compression failed with error %d\n", res);
        return 1;
    }

    printf("Compressed length: %lu\n", destLen);

    uLong uncompressedLen = sourceLen;
    res = uncompress(uncompressed, &uncompressedLen, dest, destLen);
    if (res != Z_OK) {
        fprintf(stderr, "Decompression failed with error %d\n", res);
        return 1;
    }

    printf("Uncompressed length: %lu\n", uncompressedLen);
    if (strcmp(data, (const char *)uncompressed) == 0) {
        printf("SUCCESS: Uncompressed data matches original\n");
    } else {
        printf("FAILURE: Uncompressed data does not match original\n");
        free(dest);
        free(uncompressed);
        return 1;
    }

    free(dest);
    free(uncompressed);

    printf("Testing error message conversion...\n");
    z_stream strm2;
    memset(&strm2, 0, sizeof(strm2));
    // Calling deflateInit with an invalid level should return Z_STREAM_ERROR or Z_ERRNO
    res = deflateInit(&strm2, 99); 
    if (res != Z_OK) {
        if (strm2.msg != NULL) {
            printf("Caught expected error: %s (code %d)\n", strm2.msg, res);
        } else {
            printf("Caught expected error code %d, but no message set\n", res);
        }
    } else {
        printf("deflateInit(99) unexpectedly returned Z_OK\n");
        deflateEnd(&strm2);
    }

    return 0;
}
