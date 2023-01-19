#CC=arm-linux-gcc
CC=gcc
CFLAGS=-I.
LDFLAGS=
DEPS =
OBJ = MyAppli.o

%.o: %.c $(DEPS) 
	$(CC) -c -o $@ $< $(CFLAGS) 

MyAppli: $(OBJ) 
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)