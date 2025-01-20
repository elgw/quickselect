CFLAGS=-Wall -Wextra -pedantic -std=gnu11

CFLAGS+=-Wfatal-errors

FSAN?=0
ifeq ($(FSAN),1)
CFLAGS+=-fanalyzer
DEBUG=1
endif


DEBUG?=0
ifeq ($(DEBUG),1)
CFLAGS+=-g3 -march=native
else
CFLAGS+=-O3 -DNDEBUG -mtune=native -march=native
CFLAGS+=-fno-math-errno
LDFLAGS+=-flto
endif


# CFLAGS+=-DQUICKSELECT_F32
QSFILES32=quickselect_test.c quickselect32.o
QSFILES64=quickselect_test.c quickselect64.o

quickselect_test32: $(QSFILES32)
	$(CC) $(CFLAGS) -DQUICKSELECT_F32 $(QSFILES32) $(LDFLAGS) -o quickselect_test32

quickselect_test64: $(QSFILES64)
	$(CC) $(CFLAGS) -DQUICKSELECT_F64 $(QSFILES64) $(LDFLAGS) -o quickselect_test64

quickselect32.o: quickselect.c
	$(CC) -c $(CFLAGS) -DQUICKSELECT_F32 quickselect.c -o quickselect32.o

quickselect64.o: quickselect.c
	$(CC) -c $(CFLAGS) -DQUICKSELECT_F64 quickselect.c -o quickselect64.o

med5_bench: med5_bench.c med5.o
	$(CC) $(CFLAGS) med5_bench.c med5.o $(LDFLAGS) -o med5_bench

med5.o: med5.c
	$(CC) -c $(CFLAGS) med5.c

med5.s: med5.c
	$(CC) -c -S $(CFLAGS) med5.c

med5.e: med5.c
	$(CC) -E $(CFLAGS) med5.c -o med5.e
