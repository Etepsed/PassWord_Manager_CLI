#include "globals.h"
#include <filesystem>
#include <iostream>
#include <string>
#include <thread>

using namespace std;
using json = nlohmann::json;
namespace fs = filesystem;

void page_home(string UserName, const json &User_Data);
void change_password();
void page_one(string UserName, const json &User_Data);
void page_options();
void page_two(vector<string> sites, int choice, const json &User_Data,
              string UserName);
void page_tree(vector<string> accouts, vector<string> sites, int choice,
               const json &User_Data, string UserName, const json &All_data,
               int Selected_site);
void page_add_site(string UserName, const json &User_Data);
void new_site(string UserName, const json &User_Data);
void add_account(string UserName, const json &User_Data, string site);
void page_del(string UserName, const json &User_Data);
void account_del(string UserName, const json &User_Data);
void rm_account(string UserName, const json &User_Data, string site);
