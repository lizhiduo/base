HOME_DIR := $(shell pwd)
export HOME_DIR

sample:
	@make -C demo

clean:
	@make -C demo clean
	rm -rf $(HOME_DIR)/bin/*

