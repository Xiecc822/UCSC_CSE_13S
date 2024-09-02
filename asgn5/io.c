#include "io.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct buffer {

    int fd; // file descriptor from open() or creat()
    int offset; // offset in to buffer a[]

    int num_remaining; // number of bytes remaining in buffer (reading)
    uint8_t a[BUFFER_SIZE]; // buffer
};

Buffer *read_open(const char *filename) {

    int fd = open(filename, O_RDONLY);
    if (fd < 0) {

        return NULL;
    }

    Buffer *buf = malloc(sizeof(Buffer));
    if (buf == NULL) {

        close(fd);
        return NULL;
    }

    buf->fd = fd;
    buf->offset = 0;
    buf->num_remaining = 0;

    return buf;
}

void read_close(Buffer **pbuf) {

    if (pbuf == NULL || *pbuf == NULL) {

        return;
    }

    close((*pbuf)->fd);
    free(*pbuf);
    *pbuf = NULL;
}

bool read_uint8(Buffer *buf, uint8_t *x) {

    if (buf->num_remaining == 0) {

        ssize_t rc = read(buf->fd, buf->a, sizeof(buf->a));
        if (rc < 0) {

            // TODO: report error
            return false;
        }

        if (rc == 0) {

            return false; // end of file
        }

        buf->num_remaining = rc;
        buf->offset = 0;
    }

    *x = buf->a[buf->offset++];
    buf->num_remaining--;

    return true;
}

bool read_uint16(Buffer *buf, uint16_t *x) {

    uint8_t a, b;
    if (!read_uint8(buf, &a) || !read_uint8(buf, &b)) {

        return false;
    }

    *x = a | (b << 8);

    return true;
}

bool read_uint32(Buffer *buf, uint32_t *x) {

    uint16_t a, b;
    if (!read_uint16(buf, &a) || !read_uint16(buf, &b)) {

        return false;
    }

    *x = a | (b << 16);

    return true;
}

Buffer *write_open(const char *filename) {

    int fd = creat(filename, 0664);
    if (fd < 0) {

        return NULL;
    }

    Buffer *buf = malloc(sizeof(Buffer));
    buf->fd = fd;
    buf->offset = 0;
    buf->num_remaining = 0;

    return buf;
}

void write_close(Buffer **pbuf) {

    if (pbuf == NULL || (*pbuf) == NULL) {

        return;
    }

    write_uint8(*pbuf, 0);
    close((*pbuf)->fd);
    free(*pbuf);
    *pbuf = NULL;
}

void write_uint8(Buffer *buf, uint8_t x) {

    if (buf->offset == BUFFER_SIZE) {

        uint8_t *start = buf->a;
        int num_bytes = buf->offset;
        do {

            ssize_t rc = write(buf->fd, start, num_bytes);
            if (rc < 0) {

                // TODO: report error
                return;
            }

            start += rc;
            num_bytes -= rc;

        } while (num_bytes > 0);

        buf->offset = 0;
    }

    buf->a[buf->offset++] = x;
}

void write_uint16(Buffer *buf, uint16_t x) {

    write_uint8(buf, x & 0xFF);
    write_uint8(buf, (x >> 8) & 0xFF);
}

void write_uint32(Buffer *buf, uint32_t x) {

    write_uint16(buf, x & 0xFFFF);
    write_uint16(buf, (x >> 16) & 0xFFFF);
}
