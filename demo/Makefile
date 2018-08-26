IFLAG := -I $(HOME_DIR)/include 

LIBS := -L $(HOME_DIR)/libs -lbase
LIBS +=  -lpthread

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

