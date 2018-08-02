HOME_DIR := $(shell pwd)
export HOME_DIR

ifeq ($(v), 1)
MAKE := make
else
MAKE := make -s
endif

sample:
	@$(MAKE) -C demo clean
	@$(MAKE) -C demo
	@echo "#### compile success ####"

clean:
	@$(MAKE) -C demo clean
	@rm -rf $(HOME_DIR)/bin/*
	@echo "#### clean end ####"
	
