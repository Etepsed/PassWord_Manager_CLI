#include "globals.h"
#include <filesystem>
#include <iostream>
#include <string>
#include <thread>

using namespace std;
using json = nlohmann::json;

void page_home();
void page_showpassword_chose_site();
void page_showpassword_chose_account(string site);
void page_showpassword(string site, string account);
void change_password();
void page_add_site();
void page_options();
void new_site(string UserName, const json &User_Data);
void add_account(string UserName, const json &User_Data, string site);
void page_del(string UserName, const json &User_Data);
void account_del(string UserName, const json &User_Data);
void rm_account(string UserName, const json &User_Data, string site);
