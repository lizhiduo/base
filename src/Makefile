module_name := base

IFLAG := -I $(HOME_DIR)/include
CFLAG := 

SRC := $(wildcard *.c)
OBJS := $(SRC:.c=.o)

all : $(OBJS)
	@$(AR) -r lib$(module_name).a $^
	@mv lib$(module_name).a $(HOME_DIR)/libs

%.o : %.c
	@$(CC) $(IFLAG) -c $^ -o $@

clean:
	@rm -rf *.o

