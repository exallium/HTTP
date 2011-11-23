CC=gcc
CFLAGS=-g -c
LDFLAGS=
SRC=entry.c http_setup.c http_imp.c
OBJ=$(SRC:.c=.o)
TARGET=http

all: $(SRC) $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJ)

distclean:
	rm $(TARGET)
	rm $(OBJ)
