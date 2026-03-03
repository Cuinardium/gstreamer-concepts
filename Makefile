CC = gcc
CFLAGS = $(shell pkg-config --cflags gstreamer-1.0)
LIBS = $(shell pkg-config --libs gstreamer-1.0)

SRCS = $(wildcard basic-tutorial-*.c)
PROGS = $(patsubst %.c,%.out,$(SRCS))

all: $(PROGS)

%.out: %.c
	$(CC) $< -o $@ $(CFLAGS) $(LIBS)

clean:
	rm -f $(PROGS)
