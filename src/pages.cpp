#include "../include/encrypt.h"
#include "../include/pages.h"
#include "../include/uttils.h"
#include <ios>
#include <limits>

void page_home() {

  while (true) {
    clear_screen();
    int choice;
    cout << "hello, " << USERNAME << endl;
    cout << "password manager:" << endl;
    cout << " [" << 1 << "] " << "show passwords" << endl;
    cout << " [" << 2 << "] " << "add password" << endl;
    cout << " [" << 3 << "] " << "del account" << endl;
    cout << " [" << 4 << "] " << "del site" << endl;
    cout << " [" << 5 << "] " << "options" << endl;
    cout << endl << "[" << 0 << "] " << "exit and save" << endl;
    cout << "/>: ";
    cin >> choice;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }

    switch (choice) {
    case 1:
      page_showpassword_chose_site();
      return;
      break;
    case 2:
      page_addpassword_chose_site();
      return;
      break;
    case 3:
      page_delaccount_chose_site();
      break;
    case 4:
      page_delete_site();
      return;
      break;
    case 5:
      page_options();
      return;
      break;
    case 0:
      return;
      break;
    }
  }
}

void page_showpassword_chose_site() {
  int choice = -1;
  vector<string> sites;

  while (true) {
    sites.clear();
    clear_screen();
    cout << "Show password" << endl;
    cout << "Choose a site:\n";

    int i = 1;
    for (const auto &[site, _] : USERDATA.items()) {
      cout << " [" << i << "] " << site << endl;
      sites.push_back(site);
      i++;
    }

    cout << "\n[0] Back" << endl;
    cout << "/>: ";

    cin >> choice;

    // Handle invalid input
    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }

    // Check valid range
    if (choice == 0) {
      page_home();
      return;
    }

    if (choice > 0 && choice <= static_cast<int>(sites.size())) {
      clear_screen();
      page_showpassword_chose_account(sites[choice - 1]);
      return;
    } else {
      cout << "Invalid choice. Try again.\n";
    }
  }
}

void page_showpassword_chose_account(string site) {
  int choice = -1;
  vector<string> accounts;

  while (true) {
    accounts.clear();
    clear_screen();
    cout << "Site: (" << site << ")" << endl;
    cout << "Accounts:\n";

    int i = 1;
    for (const auto &[account, _] : USERDATA[site].items()) {
      cout << " [" << i << "] " << account << endl;
      accounts.push_back(account);
      i++;
    }

    cout << "\n[0] Back" << endl;
    cout << "/>: ";

    cin >> choice;

    // Handle invalid input
    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }

    // Check valid range
    if (choice == 0) {
      page_showpassword_chose_site();
      return;
    }

    if (choice > 0 && choice <= i - 1) {
      clear_screen();
      // page three
      page_showpassword(site, accounts[choice - 1]);
      return;
    } else {
      cout << "Invalid choice. Try again.\n";
    }
  }
}

void page_showpassword(string site, string account) {

  int choice = -1;
  while (true) {
    clear_screen();

    cout << "site: (" << site << ") " << endl;
    cout << "accout: (" << account << ") " << endl;
    cout << "login:" << endl;
    cout << " [ user/email ]: "
         << USERDATA[site][account]["login"].get<string>() << endl;
    cout << " [  password  ]: "
         << USERDATA[site][account]["password"].get<string>() << endl;
    cout << "\n[0] Back" << endl;
    cout << "/>: ";

    cin >> choice;

    // Handle invalid input
    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }

    // Check valid range
    if (choice == 0) {
      page_showpassword_chose_account(site);
      return;
    }
  }
}

void page_addpassword_chose_site() {
  int choice = -1;
  vector<string> sites;
  while (true) {
    sites.clear();
    clear_screen();
    cout << "Add password" << endl;
    cout << "Choose a site: " << endl;
    cout << " [1] new site" << endl;

    int i = 2;
    for (const auto &[site, _] : USERDATA.items()) {
      cout << " [" << i << "] " << site << endl;
      sites.push_back(site);
      i++;
    }

    cout << endl << "[0] Back" << endl;
    cout << "/>: ";
    cin >> choice;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }

    if (choice == 0) {
      page_home();
      return;
    }

    clear_screen();

    if (choice == 1) {
      new_site();
      return;
    }
    if (choice > 1 && choice <= i - 1) {
      clear_screen();
      // page for add password
      page_addpassword_add_account(sites[choice - 2]);
      return;
    } else {
      cout << "Invalid choice. Try again.\n";
    }
  }
}

void page_addpassword_add_account(string site) {
  clear_screen();
  string login, password, choice;
  cout << "site: " << site << endl;
  cout << "enter your login: " << endl;
  cout << "login: ";
  cin >> login;
  while (choice != "1" && choice != "2") {
    clear_screen();
    cout << "site: " << site << endl;
    cout << " login: " << login << endl;
    cout << "use automatic password generation?" << endl;
    cout << " [1] yes ( recommended ) \n [2] not ( not recommended )" << endl;
    cout << "/>: ";
    cin >> choice;
  }
  bool auto_gen = false;
  if (choice == "2") {
    clear_screen();
    cout << "site: " << site << endl;
    cout << " login: " << login << endl;
    cout << "entrer your password:" << endl;
    cout << "password: ";
    cin >> password;

  } else if (choice == "1") {
    // gen a new password;
    password = gen_password();
    auto_gen = true;
  }
  choice = "";
  while (choice != "1" && choice != "2") {
    clear_screen();
    cout << "site: " << site << endl;
    cout << " login: " << login << endl;
    cout << " password: " << password << endl;
    cout << endl << "chose an option:" << endl;
    cout << " [1] save \n [2] delete " << endl;
    cout << " [3] edit login" << endl;
    cout << " [4] edit password" << endl;

    if (auto_gen) {
      cout << " [5] gen password" << endl;
    }
    cout << "/>: ";
    cin >> choice;

    if (choice == "3") {
      cout << "enter your login: " << endl;
      cout << "login: ";
      cin >> login;
    }

    if (choice == "4") {
      cout << "entrer your password:" << endl;
      cout << "password: ";
      cin >> password;
    }
    if (choice == "2") {
      page_home();
      return;
    }

    if (choice == "5" && auto_gen == true) {
      password = gen_password();
    }
  }

  if (choice == "1") {
    USERDATA[site][login]["login"] = login;
    USERDATA[site][login]["password"] = password;
    page_home();
    return;
  }
}

void page_delaccount_chose_site() {
  clear_screen();
  int choice = -1;

  vector<string> sites;
  bool active = true;
  while (active) {

    sites.clear();
    cout << "delete account" << endl;
    cout << "choose a site: " << endl;
    int i = 1;

    for (const auto &[site, _] : USERDATA.items()) {
      cout << " [" << i << "] " << site << endl;
      sites.push_back(site);
      i++;
    }

    cout << endl << "[0] back" << endl;
    cout << "/>: ";
    cin >> choice;
    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }
    if (choice == 0) {
      active = false;
      page_home();
      return;
    }

    if (choice > 0 && choice <= static_cast<int>(sites.size())) {
      active = false;
      page_delaccount_delete_account(sites[choice - 1]);
      return;
    }
  }
}

void page_delaccount_delete_account(string site) {
  int choice = -1;
  vector<string> accounts;
  bool active = true;
  while (active) {
    clear_screen();
    accounts.clear();
    cout << "delete account" << endl;
    cout << "site: " << site << endl;
    cout << "choose a account: " << endl;
    int i = 1;
    for (const auto &[account, _] : USERDATA[site].items()) {
      cout << " [" << i << "] " << account << endl;
      accounts.push_back(account);
      i++;
    }

    cout << endl << "[0] back" << endl;
    cout << "/>: ";
    cin >> choice;
    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }
    if (choice == 0) {
      page_delaccount_chose_site();
      return;
    }

    if (choice > 0 && choice <= static_cast<int>(accounts.size())) {
      active = false;
    }
  }

  string choc;
  while (choc != "1" && choc != "2") {
    clear_screen();
    cout << "[ " << accounts[choice - 1] << " ]" << endl;
    cout << "you want to delete this account?" << endl;
    cout << " [1] yes \n [2] not " << endl;
    cout << "/>: ";
    cin >> choc;
  }

  if (choc == "1") {
    USERDATA[site].erase(accounts[choice - 1]);
    page_delaccount_delete_account(site);
    return;
  } else {
    page_delaccount_delete_account(site);
    return;
  }
}

void page_options() {
  while (true) {
    clear_screen();
    cout << "options: " << endl;
    cout << " [" << 1 << "] " << "change Password" << endl;
    cout << " [" << 0 << "] " << "back" << endl;
    cout << "/>: ";
    int choice;
    cin >> choice;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }
    switch (choice) {
    case 1:
      change_password();
      return;
      break;
    case 0:
      page_home();
      return;
      break;
    }
  }
}

void page_delete_site() {
  vector<string> sites;
  string choc, site;
  int choice = -1;
  bool active = true;
  while (active) {
    clear_screen();
    sites.clear();

    cout << "delete mode" << endl;
    cout << "choose a site: " << endl;
    int i = 1;
    for (const auto &[site, _] : USERDATA.items()) {
      cout << " [" << i << "] " << site << endl;
      sites.push_back(site);
      i++;
    }

    cout << endl << "[0] back" << endl;
    cout << "/>: ";
    cin >> choice;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }

    if (choice == 0) {
      page_home();
      return;
    }

    if (choice > 0 && choice < static_cast<int>(sites.size())) {
      active = false;
      site = sites[choice - 1];
    }
  }

  while (choc != "1" && choc != "2") {
    clear_screen();
    cout << "site: [ " << site << " ]" << endl;
    cout << "delete this site with all password storege?" << endl;
    cout << " [1] yes \n [2] not " << endl;
    cout << "/>: ";
    cin >> choc;
  }

  if (choc == "1") {

    USERDATA.erase(site);
    page_delete_site();
  } else {
    page_delete_site();
    return;
  }
}

void new_site() {
  string site, choice;

  clear_screen();
  cout << "enter your [site] or [0] to back:" << endl;
  cout << "/>: ";
  cin >> site;
  if (site == "0") {
    page_addpassword_chose_site();
    return;
  }

  if (USERDATA.contains(site)) {
    page_addpassword_add_account(site);
    return;
  }

  while (true) {
    clear_screen();
    cout << "site: " << site << endl;
    cout << "you want to add this site? " << endl;
    cout << " [1] yes " << " [2] not " << endl;
    cout << "/>: ";
    cin >> choice;
    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }
    if (choice == "1") {
      USERDATA[site] = {};
      page_addpassword_add_account(site);
      return;

    } else if (choice == "2") {
      new_site();
      return;
    }
  }
}

void change_password() {
  clear_screen();
  string ss, jj;
  cout << "current password: ";
  cin >> ss;
  if (ss == PASSWORD) {
    bool a = true;
    while (a) {
      cout << "new password: ";
      cin >> jj;
      cout << "confirm password: ";
      cin >> ss;
      if (jj == ss) {
        PASSWORD = jj;
        a = false;
      }
    }
  } else {
    cout << "invalid password" << endl;
    this_thread::sleep_for(1s);
    page_options();
  }

  page_home();
}
