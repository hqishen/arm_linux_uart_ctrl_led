CC=arm-linux-gnueabihf-gcc

OUT_BIN = uart_app
SRCS :=  \
		main.c \
		uart.c


INCLUDE += -I.
LIBS  :=

CFLAGS := -g -Wall -Wno-comment $(INCLUDE) -lc $(LIBS)

build: $(SRCS)
	$(CC) $(SRCS) $(CFLAGS) -o ${OUT_BIN}

clean: 
	rm ${OUT_BIN}


