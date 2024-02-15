# Main Program
TARGET   := main
CXX      := g++
CXXFLAGS := -Wall -Werror -g
LDFLAGS  := 
BUILD    := bin
OBJ_DIR  := $(BUILD)/obj
INCLUDE  := 
SRC      := $(wildcard src/*.cpp)
OBJECTS  := $(patsubst src/%.cpp,$(BUILD)/%.o, $(SRC))

# Imail Library
IMAIL_LIB 		:= imail
IMAIL_INCLUDE 	:= imail
IMAIL_CXXFLAGS 	:= -I $(IMAIL_INCLUDE)
IMAIL_LDFLAGS	:= -L $(IMAIL_INCLUDE) -L $(BUILD) -l $(IMAIL_LIB) -lpthread
IMAIL_SRC		:= $(wildcard imail/*.cpp)
IMAIL_OBJECTS	:= $(patsubst imail/%.cpp,$(BUILD)/%.o, $(IMAIL_SRC))

all: $(BUILD) $(TARGET)

# Rule to create the build directory
$(BUILD):
	mkdir -p $(BUILD)

# Main Targets
$(TARGET): $(OBJECTS) $(IMAIL_LIB) 
	$(CXX) $(CXXFLAGS) $(IMAIL_CXXFLAGS) $< $(IMAIL_LDFLAGS) -o $(BUILD)/$@

$(BUILD)/%.o: src/%.cpp
	$(CXX) -c $(CXXFLAGS) $(IMAIL_CXXFLAGS) $(IMAIL_LDFLAGS) $< -o $@

.PHONY: run
run:
	@./bin/$(TARGET)

# Imail Targets
$(IMAIL_LIB): $(IMAIL_OBJECTS)
	ar rcs $(BUILD)/lib$@.a $^

$(BUILD)/%.o: imail/%.cpp
	$(CXX) -c $(CXXFLAGS) $(IMAIL_CXXFLAGS) $(IMAIL_LDFLAGS) $< -o $@

# Google Test
GTEST_TARGET		:= unittest
GTEST_LIB 			:= gtest
GTEST_INCLUDE 		:= /usr/local/include
GTEST_CXXFLAGS 		:= -I $(GTEST_INCLUDE)
GTEST_LDFLAGS		:= -L /usr/local/lib -l $(GTEST_LIB) -l pthread
GTEST_SRC			:= $(wildcard test/*.cpp)
GTEST_OBJECTS		:= $(patsubst test/%.cpp,$(BUILD)/%.o, $(GTEST_SRC))

.PHONY: test
test: $(BUILD) $(GTEST_TARGET)

$(GTEST_TARGET): $(GTEST_OBJECTS) $(IMAIL_LIB) 
	$(CXX) $(CXXFLAGS) $(IMAIL_CXXFLAGS) $(GTEST_OBJECTS) $(IMAIL_LDFLAGS) $(GTEST_LDFLAGS) -o $(BUILD)/$@

$(BUILD)/%.o: test/%.cpp
	$(CXX) -c $(CXXFLAGS) $(IMAIL_CXXFLAGS) $(GTEST_CXXFLAGS) $(IMAIL_LDFLAGS) $(GTEST_LDFLAGS) $< -o $@

	$(CXX) -c $(CXXFLAGS) $(IMAIL_CXXFLAGS) $(IMAIL_LDFLAGS) $< -o $@

.PHONY: run_test
run_test:
	@./bin/$(GTEST_TARGET)

.PHONY: clean
clean:
	@rm -rf $(BUILD)

# Define color codes
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

.PHONY: info
info:
	@echo "$(GREEN)[*] Compiler:$(RESET) ${CXX}"
	@echo "$(GREEN)[*] Compiler Flags:$(RESET) ${CXXFLAGS}"
	@echo "$(GREEN)[*] Linker Flags:$(RESET) ${LDFLAGS}"
	@echo "$(GREEN)[*] TARGET:$(RESET) ${TARGET}"
	@echo "$(GREEN)[*] Object Dir:$(RESET) ${OBJ_DIR}"
	@echo "$(GREEN)[*] Include Dir:$(RESET) ${INCLUDE}"
	@echo "$(GREEN)[*] Sources:$(RESET) ${SRC}"
	@echo "$(GREEN)[*] Objects:$(RESET) ${OBJECTS}"