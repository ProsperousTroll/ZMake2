BUILD := $(wildcard build)
COMPILER=g++
OPTIONS=-I

INCLUDE=./inc/*
SOURCE=./src/*

PROJECT=zmake

all: $(INCLUDE) $(SOURCE)
ifeq ($(BUILD),build)
else
	@mkdir build
endif
	$(COMPILER) $(OPTIONS)$(INCLUDE) $(SOURCE) -o ./$(BUILD)/$(PROJECT)

clean:
ifeq ($(BUILD),build)
	@rm -rf ./$(BUILD)
	@echo All clean!
else
	@echo nothing to clean...
endif

run:
ifeq ($(BUILD),build)
	./$(BUILD)/$(PROJECT)
else
	@echo ERROR: Cannot find build folder. Did you build yet?
endif
