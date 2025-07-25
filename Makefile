# Compilador
CXX = g++

# Flags de compilação (inclui link com OpenSSL)
CXXFLAGS = -Wall -std=c++17

# Flags de linkagem
LDFLAGS = -lcrypto -lssl

# Diretórios
SRC_DIR = src
BUILD_DIR = build

# Arquivos-fonte
SRC = $(SRC_DIR)/main.cpp  $(SRC_DIR)/globals.cpp   $(SRC_DIR)/pages.cpp  $(SRC_DIR)/encrypt.cpp  $(SRC_DIR)/uttils.cpp

# Nome do executável
OUT = $(BUILD_DIR)/pam

# Regra padrão
all: $(OUT)

# Criação do executável
$(OUT): $(SRC)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Limpeza
clean:
	rm -rf $(BUILD_DIR)

