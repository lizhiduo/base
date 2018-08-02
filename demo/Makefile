CC := gcc

IFLAG := -I $(HOME_DIR)/include
CFLAG := 

ifeq ($(debug), 1)
CFLAG += -D DEBUG -g
endif

SRC := $(wildcard *.c)  
OBJ := $(SRC:.c=.o)
BIN := test

all : $(OBJ)
	$(CC) -o $(BIN) $(OBJ) $(IFLAG) $(CFLAG)
	@mv $(BIN) $(HOME_DIR)/bin	

%.o : %.c
	$(CC) -c $< -o $@ $(IFLAG) $(CFLAG)

clean:
	@rm -rf *.o $(BIN)

