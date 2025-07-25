#include "nlohmann/json.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <random>
#include <string>
#include <thread>
#include <unistd.h>
#include <vector>

using namespace std;
using json = nlohmann::json;
namespace fs = filesystem;

void handleErrors();
void encrypt_file(const string &in_json_str);
int decrypt_file(string &out_json);
string gen_password();
