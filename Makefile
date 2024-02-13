CXX      := g++
CXXFLAGS := -Wall -Wextra -Werror
LDFLAGS  := 
BUILD    := bin
OBJ_DIR  := $(BUILD)/obj
TARGET   := program
INCLUDE  := 
SRC      := $(wildcard src/*.cpp)
OBJECTS  := $(SRC:.cpp=.o)

# Google Test
GOOGLE_TEST_TARGET		:= test
GOOGLE_TEST_LIB 		:= gtest
GOOGLE_TEST_INCLUDE 	:= /usr/local/include
GOOGLE_TEST_CXXFLAGS 	:= -I $(GOOGLE_TEST_INCLUDE)
GOOGLE_TEST_LDFLAGS		:= -L /usr/local/lib -l $(GOOGLE_TEST_LIB) -l pthread
GOOGLE_TEST_SRC			:= $(wildcard tests/*.cpp)
GOOGLE_TEST_OBJECTS		:= $(GOOGLE_TEST_SRC:.cpp=.o)


.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJECTS)
	mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: test
$(GOOGLE_TEST_TARGET): $(GOOGLE_TEST_OBJECTS)
	mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) $^ $(GOOGLE_TEST_LDFLAGS) -o $(BUILD)/$@

%.o: $(GOOGLE_TEST_SRC)
	$(CXX) -c $(CXXFLAGS) $(GOOGLE_TEST_CXXFLAGS) $(GOOGLE_TEST_LDFLAGS) $< -o $@

.PHONY: run_test
run_test:
	./bin/$(GOOGLE_TEST_TARGET)

.PHONY: clean
clean:
	rm -rf $(BUILD) **/*.o

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