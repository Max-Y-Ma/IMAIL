# Main Program
CXX      := g++
CXXFLAGS := -Wall -g
LDFLAGS  := 
BUILD    := bin
OBJ_DIR  := $(BUILD)/obj
INCLUDE  := 
SRC      := $(wildcard src/*.cpp)
OBJECTS  := $(patsubst src/%.cpp, $(BUILD)/%.o, $(SRC))

# Imail Library
IMAIL_LIB 		:= imail
IMAIL_INCLUDE 	:= imail
IMAIL_CXXFLAGS 	:= -I $(IMAIL_INCLUDE)
IMAIL_LDFLAGS	:= -L $(IMAIL_INCLUDE) -L $(BUILD) -l $(IMAIL_LIB) -lpthread
IMAIL_SRC		:= $(wildcard imail/*.cpp)
IMAIL_OBJECTS	:= $(patsubst imail/%.cpp, $(BUILD)/%.o, $(IMAIL_SRC))

TARGET   := main
all: $(TARGET)

# Main Targets
$(TARGET): $(OBJECTS) $(IMAIL_LIB) 
	mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) $(IMAIL_CXXFLAGS) $< $(IMAIL_LDFLAGS) -o $(BUILD)/$@

$(BUILD)/%.o: src/%.cpp
	mkdir -p $(BUILD)
	$(CXX) -c $(CXXFLAGS) $(IMAIL_CXXFLAGS) $(IMAIL_LDFLAGS) $< -o $@

.PHONY: run
run:
	@./bin/$(TARGET)

# Imail Targets
$(IMAIL_LIB): $(IMAIL_OBJECTS)
	mkdir -p $(BUILD)
	ar rcs $(BUILD)/lib$@.a $^

$(BUILD)/%.o: imail/%.cpp
	mkdir -p $(BUILD)
	$(CXX) -c $(CXXFLAGS) $(IMAIL_CXXFLAGS) $(IMAIL_LDFLAGS) $< -o $@

# Google Test
GOOGLE_TEST_TARGET		:= test
GOOGLE_TEST_LIB 		:= gtest
GOOGLE_TEST_INCLUDE 	:= /usr/local/include
GOOGLE_TEST_CXXFLAGS 	:= -I $(GOOGLE_TEST_INCLUDE)
GOOGLE_TEST_LDFLAGS		:= -L /usr/local/lib -l $(GOOGLE_TEST_LIB) -l pthread
GOOGLE_TEST_SRC			:= $(wildcard test/*.cpp)
GOOGLE_TEST_OBJECTS		:= $(patsubst test/%.cpp, $(BUILD)/%.o, $(GOOGLE_TEST_SRC))

.PHONY: test
$(GOOGLE_TEST_TARGET): $(GOOGLE_TEST_OBJECTS)
	mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) $^ $(GOOGLE_TEST_LDFLAGS) -o $(BUILD)/$@

$(BUILD)/%.o: test/%.cpp
	mkdir -p $(BUILD)
	$(CXX) -c $(CXXFLAGS) $(GOOGLE_TEST_CXXFLAGS) $(GOOGLE_TEST_LDFLAGS) $< -o $@

.PHONY: run_test
run_test:
	@./bin/$(GOOGLE_TEST_TARGET)

.PHONY: clean
clean:
	@rm -rf $(BUILD)

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