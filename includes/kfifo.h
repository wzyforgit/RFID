#ifndef KFIFO_H
#define KFIFO_H

struct kfifo {
	unsigned char *buffer;	/* the buffer holding the data */
	unsigned int size;	/* the size of the allocated buffer */
	unsigned int in;	/* data is added at offset (in % size) */
	unsigned int out;	/* data is extracted from off. (out % size) */
};

extern unsigned int kfifo_put(struct kfifo *fifo, const unsigned char *buffer, unsigned int len);
extern unsigned int kfifo_get(struct kfifo *fifo, unsigned char *buffer, unsigned int len);
extern unsigned int kfifo_len(struct kfifo *fifo);
extern void kfifo_reset(struct kfifo *fifo);

#endif