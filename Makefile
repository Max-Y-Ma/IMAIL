TARGET   := main
all: $(TARGET)

# Imail Library
IMAIL_LIB 		:= imail
IMAIL_INCLUDE 	:= imail
IMAIL_CXXFLAGS 	:= -I $(IMAIL_INCLUDE)
IMAIL_LDFLAGS	:= -L $(IMAIL_INCLUDE) -l $(IMAIL_LIB)
IMAIL_SRC		:= $(wildcard imail/*.cpp)
IMAIL_OBJECTS	:= $(IMAIL_SRC:.cpp=.o)

$(IMAIL_LIB): $(IMAIL_OBJECTS)
	ar rcs $(IMAIL_INCLUDE)/lib$@.a $^

$(IMAIL_OBJECTS): $(IMAIL_SRC)
	$(CXX) -c $(CXXFLAGS) $(IMAIL_CXXFLAGS) $(IMAIL_LDFLAGS) $< -o $@

# Main Program
CXX      := g++
CXXFLAGS := -Wall -Wextra -Werror
LDFLAGS  := 
BUILD    := bin
OBJ_DIR  := $(BUILD)/obj
INCLUDE  := 
SRC      := $(wildcard src/*.cpp)
OBJECTS  := $(SRC:.cpp=.o)

$(TARGET): $(OBJECTS) $(IMAIL_LIB) 
	mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) $(IMAIL_CXXFLAGS) $< $(IMAIL_LDFLAGS) -o $(BUILD)/$@

$(OBJECTS): $(SRC)
	$(CXX) -c $(CXXFLAGS) $(IMAIL_CXXFLAGS) $(IMAIL_LDFLAGS) $< -o $@

.PHONY: run
run:
	@./bin/$(TARGET)

# Google Test
GOOGLE_TEST_TARGET		:= test
GOOGLE_TEST_LIB 		:= gtest
GOOGLE_TEST_INCLUDE 	:= /usr/local/include
GOOGLE_TEST_CXXFLAGS 	:= -I $(GOOGLE_TEST_INCLUDE)
GOOGLE_TEST_LDFLAGS		:= -L /usr/local/lib -l $(GOOGLE_TEST_LIB) -l pthread
GOOGLE_TEST_SRC			:= $(wildcard test/*.cpp)
GOOGLE_TEST_OBJECTS		:= $(GOOGLE_TEST_SRC:.cpp=.o)

.PHONY: test
$(GOOGLE_TEST_TARGET): $(GOOGLE_TEST_OBJECTS)
	mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) $^ $(GOOGLE_TEST_LDFLAGS) -o $(BUILD)/$@

$(GOOGLE_TEST_OBJECTS): $(GOOGLE_TEST_SRC)
	$(CXX) -c $(CXXFLAGS) $(GOOGLE_TEST_CXXFLAGS) $(GOOGLE_TEST_LDFLAGS) $< -o $@

.PHONY: run_test
run_test:
	@./bin/$(GOOGLE_TEST_TARGET)

.PHONY: clean
clean:
	rm -rf $(BUILD) **/*.o **/*.a

.PHONY: info
info:
	@echo "[*] Compiler:		${CXX}     	   "
	@echo "[*] Compiler Flags: 	${CXXFLAGS}    "
	@echo "[*] Linker Flags: 	${LDFLAGS}     "
	@echo "[*] TARGET: 			${TARGET}      "
	@echo "[*] Object Dir:      ${OBJ_DIR}     "
	@echo "[*] Include Dir:     ${INCLUDE}     "
	@echo "[*] Sources:         ${SRC}         "
	@echo "[*] Objects:         ${OBJECTS}     "