IFLAG := -I $(HOME_DIR)/include
CFLAG := 

ifeq ($(debug), 1)
CFLAG += -D DEBUG -g
endif

LIBS := -L $(HOME_DIR)/libs -lbase

SRC := $(wildcard *.c)  
OBJ := $(SRC:.c=.o)
BIN := demo

all : $(OBJ)
	$(CC) -o $(BIN) $(OBJ) $(IFLAG) $(CFLAG) $(LIBS)
	@mv $(BIN) $(HOME_DIR)/bin	

%.o : %.c
	$(CC) -c $< -o $@ $(IFLAG) $(CFLAG)

clean:
	@rm -rf *.o $(BIN)

