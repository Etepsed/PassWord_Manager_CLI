# Compiler
CXX = g++

# Compilation flags (includes link with OpenSSL)
CXXFLAGS = -Wall -std=c++17

# Linking flags
LDFLAGS = -lcrypto -lssl

# Directories
SRC_DIR = src
BUILD_DIR = build

# Source files
SRC = $(SRC_DIR)/main.cpp  $(SRC_DIR)/globals.cpp   $(SRC_DIR)/pages.cpp  $(SRC_DIR)/encrypt.cpp  $(SRC_DIR)/uttils.cpp

# Executable name
OUT = $(BUILD_DIR)/pam

# Default rule
all: $(OUT)

# Creating the executable
$(OUT): $(SRC)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# clean
clean:
	rm -rf $(BUILD_DIR)

