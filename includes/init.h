#ifndef INIT_H
#define INIT_H

#define BUFSIZE 128

#if (BUFSIZE<=1||(BUFSIZE^(BUFSIZE&~(BUFSIZE - 1))))
#error "Size of FIFO buffer must be power of 2"
#endif

extern void InitFifo(void);
extern void Init(void);

#endif