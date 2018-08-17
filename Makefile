CC ?= gcc
AR ?= ar 

HOME_DIR := $(shell pwd)
export HOME_DIR
export CC
export AR

ifeq ($(v), 1)
MAKE := make
else
MAKE := make -s
endif

all:
	@$(MAKE) lib
	@$(MAKE) sample

lib:
	@$(MAKE) -C src clean
	@$(MAKE) -C src 
	@echo "#### compile lib success ####"

sample:
	@$(MAKE) -C demo clean
	@$(MAKE) -C demo
	@echo "#### compile sample success ####"

clean:
	@$(MAKE) -C demo clean
	@$(MAKE) -C src clean
	@rm -rf $(HOME_DIR)/bin/*
	@rm -rf $(HOME_DIR)/libs/*
	@echo "#### clean end ####"
	
