# Password Manager CLI

A simple and secure command-line password manager written in C++. It uses AES-256 encryption (via OpenSSL) to securely store login credentials for multiple websites, protected by a master password.

## Features

-  AES-256-CBC file encryption using OpenSSL
-  PBKDF2 password hashing with salt and iteration (600,000 iterations)
-  Simple interactive command-line interface
-  Site and account organization structure
-  Automatic strong password generator
-  Encrypted storage in `.bin` file per user

## Requirements

- C++17 or later
- OpenSSL library (e.g., `libssl-dev`)
- `nlohmann/json` for JSON handling (included in `include/` folder)

## Build & Run

### Dependencies

Install OpenSSL (Ubuntu/Debian):

```bash
sudo apt update
sudo apt install libssl-dev
```

### Compile for linux

```bash
make
```

### Compile for Windows with MSYS2 (Static Executable)

## Requirements

- MSYS2 installed
- MSYS2 updated

```bash
pacman -Syu
```

1. **Use the "MSYS2 UCRT64"** .

2. **Install the required packages**:

```bash
pacman -S \
  mingw-w64-ucrt-x86_64-gcc \
  mingw-w64-ucrt-x86_64-openssl \
  mingw-w64-ucrt-x86_64-zlib \
  make
```
3. **Compile the project with make**:

```bash
make windows
```
--


## Run

```bash
./pam <username> <master_password>
```

## Usage

Once launched, the application will guide you through:

- **[1] Show passwords** – Navigate and view stored credentials.
- **[2] Add password** – Add a new account under an existing or new site.
- **[3] Delete account** – Remove an account under a specific site.
- **[4] Delete site** – Remove an entire site and its associated accounts.
- **[0] Exit** – Exit and automatically save changes in an encrypted `.bin` file.

All data is encrypted and stored in a file named:

```
<username>.bin
```

## Encryption Details

- **Algorithm**: AES-256-CBC
- **Key Derivation**: PBKDF2 (HMAC-SHA256)
- **Iterations**: 600,000
- **Salt**: 8 bytes
- **IV**: 16 bytes
- **Key Size**: 32 bytes

## Example

```bash
./pam alice my_secure_password
```

- If `alice.bin` exists: decrypt it using the password.
- If not: a new encrypted file will be created upon exit.

## Security Notes

- Do not share your `*.bin` file or master password.
- Passwords are only shown in plaintext on screen (not copied to clipboard).

## License

MIT License – see [LICENSE](LICENSE) for details.

## Acknowledgments

- [nlohmann/json](https://github.com/nlohmann/json)
- [OpenSSL](https://www.openssl.org/)
