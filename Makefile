CC ?= riscv64-unknown-linux-gnu-clang
CFLAGS ?= -O3 -march=rv64gcv -fPIC
DEFINES = -DHAVE_INTRINSICS_RVV

SRC_DIRS = qpel

SRCS = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))

LIB_SO = libh264opt.so
LIB_A = libh264opt.a

all: $(LIB_SO) $(LIB_A)

$(LIB_SO): $(SRCS)
	$(CC) -shared $(CFLAGS) $(DEFINES) -o $@ $^

$(LIB_A): $(SRCS)
	$(CC) -c $(CFLAGS) $(DEFINES) $(SRCS)
	ar rcs $@ *.o
	rm -f *.o

clean:
	rm -f $(LIB_SO) $(LIB_A)

.PHONY: all clean