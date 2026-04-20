#include "zlib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    const char *test_file = "test_gzdopen.gz";
    const char *data = "This is a test of gzdopen on z/OS using zEDC-enabled zlib. "
                       "Compressed data should be written and read back correctly.";
    size_t data_len = strlen(data);

    // 1. Write compressed data using gzdopen
    int fd = open(test_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        perror("open for write failed");
        return 1;
    }

    gzFile gz = gzdopen(fd, "wb");
    if (gz == NULL) {
        fprintf(stderr, "gzdopen for write failed\n");
        close(fd);
        return 1;
    }

    if (gzwrite(gz, data, data_len) <= 0) {
        fprintf(stderr, "gzwrite failed\n");
        gzclose(gz);
        return 1;
    }
    gzclose(gz);

    // 2. Read back and verify
    fd = open(test_file, O_RDONLY);
    if (fd == -1) {
        perror("open for read failed");
        return 1;
    }

    gz = gzdopen(fd, "rb");
    if (gz == NULL) {
        fprintf(stderr, "gzdopen for read failed\n");
        close(fd);
        return 1;
    }

    char buffer[256];
    int bytes_read = gzread(gz, buffer, sizeof(buffer) - 1);
    if (bytes_read <= 0) {
        fprintf(stderr, "gzread failed\n");
        gzclose(gz);
        return 1;
    }
    buffer[bytes_read] = '\0';
    gzclose(gz);

    if (strcmp(data, buffer) == 0) {
        printf("SUCCESS: gzdopen write/read test passed\n");
    } else {
        printf("FAILURE: Data mismatch!\n");
        printf("Original: %s\n", data);
        printf("Read:     %s\n", buffer);
        unlink(test_file);
        return 1;
    }

    unlink(test_file);
    return 0;
}
