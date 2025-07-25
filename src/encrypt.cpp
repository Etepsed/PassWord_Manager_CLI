#include "../include/encrypt.h"
#include "../include/globals.h"

constexpr int KEY_LENGTH = 32;
constexpr int IV_LENGTH = 16;
constexpr int SALT_LENGTH = 8;
constexpr int ITERATIONS = 600000;
constexpr int BUFFER_SIZE = 1024;

void handleErrors() {
  ERR_print_errors_fp(stderr);
  throw std::runtime_error("OpenSSL error");
}

void encrypt_file(const string &in_json_str) {
  istringstream in(in_json_str);
  // ifstream in (USERNAME + ".json",ios::binary);
  ofstream out(USERNAME + ".bin", ios::binary);

  if (!in || !out) {
    cout << "error on open file" << endl;
    return;
  }

  unsigned char salt[SALT_LENGTH];
  if (!RAND_bytes(salt, SALT_LENGTH))
    handleErrors();

  unsigned char key[KEY_LENGTH];
  unsigned char iv[IV_LENGTH];

  if (!PKCS5_PBKDF2_HMAC(PASSWORD.c_str(), PASSWORD.size(), salt, SALT_LENGTH,
                         ITERATIONS, EVP_sha256(), KEY_LENGTH, key)) {
    handleErrors();
  }

  if (!RAND_bytes(iv, IV_LENGTH))
    handleErrors();

  out.write(reinterpret_cast<char *>(salt), SALT_LENGTH);
  out.write(reinterpret_cast<char *>(iv), IV_LENGTH);

  EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
  if (!ctx)
    handleErrors();

  if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv)) {
    handleErrors();
  }

  std::vector<unsigned char> inbuf(BUFFER_SIZE);
  std::vector<unsigned char> outbuf(BUFFER_SIZE + EVP_MAX_BLOCK_LENGTH);
  int inlen = 0, outlen = 0;

  while (in.read(reinterpret_cast<char *>(inbuf.data()), inbuf.size()) ||
         (inlen = in.gcount())) {
    inlen = in.gcount();
    if (1 !=
        EVP_EncryptUpdate(ctx, outbuf.data(), &outlen, inbuf.data(), inlen)) {
      handleErrors();
    }
    out.write(reinterpret_cast<char *>(outbuf.data()), outlen);
  }

  if (1 != EVP_EncryptFinal_ex(ctx, outbuf.data(), &outlen))
    handleErrors();

  out.write(reinterpret_cast<char *>(outbuf.data()), outlen);

  EVP_CIPHER_CTX_free(ctx);

  //	in.close();
  out.close();

  return;
}

int decrypt_file(string &out_json) {
  ifstream in(USERNAME + ".bin", ios::binary);
  // ofstream out(USERNAME + ".json", ios::binary);
  stringstream out;
  if (!in || !out) {
    cerr << "error opening file for writing or reading\n";
    return 1;
  }

  unsigned char salt[SALT_LENGTH];
  unsigned char iv[IV_LENGTH];
  unsigned char key[KEY_LENGTH];

  in.read(reinterpret_cast<char *>(salt), SALT_LENGTH);
  in.read(reinterpret_cast<char *>(iv), IV_LENGTH);

  if (!in) {
    cerr << "error on reading salt or IV of file\n";
    return 1;
  }

  if (!PKCS5_PBKDF2_HMAC(PASSWORD.c_str(), PASSWORD.size(), salt, SALT_LENGTH,
                         ITERATIONS, EVP_sha256(), KEY_LENGTH, key)) {
    handleErrors();
  }

  EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
  if (!ctx)
    handleErrors();

  if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv)) {
    handleErrors();
  }

  vector<unsigned char> inbuf(BUFFER_SIZE + EVP_MAX_BLOCK_LENGTH);
  vector<unsigned char> outbuf(BUFFER_SIZE);
  int inlen = 0, outlen = 0;

  while (true) {
    in.read(reinterpret_cast<char *>(inbuf.data()), BUFFER_SIZE);
    inlen = in.gcount();
    if (inlen <= 0)
      break;

    if (1 !=
        EVP_DecryptUpdate(ctx, outbuf.data(), &outlen, inbuf.data(), inlen)) {
      handleErrors();
    }
    out.write(reinterpret_cast<char *>(outbuf.data()), outlen);
  }

  if (1 != EVP_DecryptFinal_ex(ctx, outbuf.data(), &outlen)) {
    cerr << "error completing decryption\n";
    EVP_CIPHER_CTX_free(ctx);
    fs::remove(USERNAME + ".json");
    in.close();
    //	out.close();
    return 1;
  }

  out.write(reinterpret_cast<char *>(outbuf.data()), outlen);

  EVP_CIPHER_CTX_free(ctx);
  in.close();
  // out.close();
  out_json = out.str();
  return 0;
}

string gen_password() {
  string password;
  string characters = "abcdefghijklmnopqrstuvwxyz"
                      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                      "0123456789"
                      "!@#$%^&*()-_=+[]{}|;:,.<>?";

  random_device rd;
  mt19937 gerador(rd());
  uniform_int_distribution<> dist(0, characters.size() - 1);

  for (int i = 0; i < PASSWORD_LENGTH; ++i) {
    password += characters[dist(gerador)];
  }

  return password;
}
