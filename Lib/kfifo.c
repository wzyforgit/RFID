#include<stc12c5a.h> //硬件相关
#include<string.h>	 //字符串处理
#include"kfifo.h"	 

#define min(a, b) ((a) > (b) ? (b) : (a))

static void CodeLock(void)
{
	TR0=0;
	EA=0;
}

static void CodeUnlock(void)
{
	EA=1;
	TR0=1;
}

/**
 * __kfifo_put - puts some data into the FIFO, no locking version
 * @fifo: the fifo to be used.
 * @buffer: the data to be added.
 * @len: the length of the data to be added.
 *
 * This function copies at most @len bytes from the @buffer into
 * the FIFO depending on the free space, and returns the number of
 * bytes copied.
 *
 * Note that with only one concurrent reader and one concurrent
 * writer, you don't need extra locking to use these functions.
 */
static unsigned int __kfifo_put(struct kfifo *fifo, const unsigned char *buffer, unsigned int len)
{
	unsigned int l;

	len = min(len, fifo->size - fifo->in + fifo->out);

	//	smp_mb();

	/* first put the data starting from fifo->in to buffer end */
	l = min(len, fifo->size - (fifo->in & (fifo->size - 1)));
	memcpy(fifo->buffer + (fifo->in & (fifo->size - 1)), buffer, l);

	/* then put the rest (if any) at the beginning of the buffer */
	memcpy(fifo->buffer, buffer + l, len - l);

	//	smp_wmb();

	fifo->in += len;

	return len;
}

/**
 * __kfifo_get - gets some data from the FIFO, no locking version
 * @fifo: the fifo to be used.
 * @buffer: where the data must be copied.
 * @len: the size of the destination buffer.
 *
 * This function copies at most @len bytes from the FIFO into the
 * @buffer and returns the number of copied bytes.
 *
 * Note that with only one concurrent reader and one concurrent
 * writer, you don't need extra locking to use these functions.
 */
static unsigned int __kfifo_get(struct kfifo *fifo, unsigned char *buffer, unsigned int len)
{
	unsigned int l;

	len = min(len, fifo->in - fifo->out);

//	smp_rmb();

	/* first get the data from fifo->out until the end of the buffer */
	l = min(len, fifo->size - (fifo->out & (fifo->size - 1)));
	memcpy(buffer, fifo->buffer + (fifo->out & (fifo->size - 1)), l);

	/* then get the rest (if any) from the beginning of the buffer */
	memcpy(buffer + l, fifo->buffer, len - l);

//	smp_mb();

	fifo->out += len;

	return len;
}

/**
 * kfifo_put - puts some data into the FIFO
 * @fifo: the fifo to be used.
 * @buffer: the data to be added.
 * @len: the length of the data to be added.
 *
 * This function copies at most @len bytes from the @buffer into
 * the FIFO depending on the free space, and returns the number of
 * bytes copied.
 */
unsigned int kfifo_put(struct kfifo *fifo, const unsigned char *buffer, unsigned int len)
{
	unsigned int ret;

	CodeLock();

	ret = __kfifo_put(fifo, buffer, len);

	CodeUnlock();

	return ret;
}

/**
 * kfifo_get - gets some data from the FIFO
 * @fifo: the fifo to be used.
 * @buffer: where the data must be copied.
 * @len: the size of the destination buffer.
 *
 * This function copies at most @len bytes from the FIFO into the
 * @buffer and returns the number of copied bytes.
 */
unsigned int kfifo_get(struct kfifo *fifo, unsigned char *buffer, unsigned int len)
{
	unsigned int ret;

	CodeLock();

	ret = __kfifo_get(fifo, buffer, len);

	/*
	 * optimization: if the FIFO is empty, set the indices to 0
	 * so we don't wrap the next time
	 */
	if (fifo->in == fifo->out)
		fifo->in = fifo->out = 0;

	CodeUnlock();

	return ret;
}

/**
 * __kfifo_len - returns the number of bytes available in the FIFO, no locking version
 * @fifo: the fifo to be used.
 */
static unsigned int __kfifo_len(struct kfifo *fifo)
{
	return fifo->in - fifo->out;
}

/**
 * kfifo_len - returns the number of bytes available in the FIFO
 * @fifo: the fifo to be used.
 */
unsigned int kfifo_len(struct kfifo *fifo)
{
	unsigned int ret;

	CodeLock();

	ret = __kfifo_len(fifo);

	CodeUnlock();

	return ret;
}

/**
* __kfifo_reset - removes the entire FIFO contents, no locking version
* @fifo: the fifo to be emptied.
*/
static void __kfifo_reset(struct kfifo *fifo)
{
	fifo->in = fifo->out = 0;
}

/**
* kfifo_reset - removes the entire FIFO contents
* @fifo: the fifo to be emptied.
*/
void kfifo_reset(struct kfifo *fifo)
{
	CodeLock();

	__kfifo_reset(fifo);

	CodeUnlock();
}