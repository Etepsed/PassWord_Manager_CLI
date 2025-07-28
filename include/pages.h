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
void page_addpassword_chose_site();
void page_addpassword_add_account(string site);
void page_delaccount_chose_site();
void page_delaccount_delete_account(string site);
void page_delete_site();
void page_options();
void new_site();

void change_password();
