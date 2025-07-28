# Compiler
CXX = g++

# Directories
SRC_DIR = src
BUILD_DIR = build

# Source files
SRC = $(SRC_DIR)/main.cpp \
      $(SRC_DIR)/globals.cpp \
      $(SRC_DIR)/pages.cpp \
      $(SRC_DIR)/encrypt.cpp \
      $(SRC_DIR)/uttils.cpp

# Detect if building for Windows
ifeq ($(MAKECMDGOALS),windows)
    TARGET = windows
else
    TARGET = linux
endif

# Default values (Linux)
OUT = $(BUILD_DIR)/pam
CXXFLAGS = -Wall -std=c++17
LDFLAGS = -lcrypto -lssl

# Override if Windows
ifeq ($(TARGET),windows)
    OUT = $(BUILD_DIR)/pam.exe
    CXXFLAGS = -Wall -std=c++17 -static -static-libgcc -static-libstdc++
    LDFLAGS = -lcrypto -lssl -lws2_32 -lz -lcrypt32 -static
endif

# Targets
all: $(OUT)

windows: $(OUT)

$(OUT): $(SRC)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)



