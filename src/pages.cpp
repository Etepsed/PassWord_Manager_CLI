#include "../include/encrypt.h"
#include "../include/pages.h"

void page_home(string UserName, const json &User_Data) {
  system("clear");
  int choice;
  cout << "hello, " << UserName << endl;
  cout << "password manager:" << endl;
  cout << " [" << 1 << "] " << "show passwords" << endl;
  cout << " [" << 2 << "] " << "add password" << endl;
  cout << " [" << 3 << "] " << "del account" << endl;
  cout << " [" << 4 << "] " << "del site" << endl;
  cout << " [" << 5 << "] " << "options" << endl;
  cout << endl << "[" << 0 << "] " << "exit and save" << endl;
  cout << "/>: ";
  cin >> choice;
  switch (choice) {
  case 1:
    page_one(UserName, User_Data);
    break;
  case 2:
    page_add_site(UserName, User_Data);
    break;
  case 3:
    account_del(UserName, User_Data);
    break;
  case 4:
    page_del(UserName, User_Data);
    break;
  case 5:
    page_options();
    break;
  case 0:
    return;
  default:
    page_home(UserName, User_Data);
    break;
  }
  return;
}

void account_del(string UserName, const json &User_Data) {
  system("clear");
  int choice;
  int i = 1;
  vector<string> sites;

  cout << "delete account" << endl;
  cout << "choose a site: " << endl;
  for (const auto &[site, _] : User_Data.items()) {
    cout << " [" << i << "] " << site << endl;
    sites.push_back(site);
    i++;
  }

  cout << endl << "[0] back" << endl;
  cout << "/>: ";
  cin >> choice;

  if (choice == 0) {
    page_home(UserName, User_Data);
    return;
  }

  if (choice < 0 || choice > i - 1) {
    page_del(UserName, User_Data);
  }

  string site = sites[choice - 1];

  rm_account(UserName, User_Data, site);
}

void rm_account(string UserName, const json &User_Data, string site) {
  system("clear");
  int choice;
  int i = 1;
  string choc;
  vector<string> accounts;
  cout << "delete account" << endl;
  cout << "site: " << site << endl;
  cout << "choose a account: " << endl;
  for (const auto &[account, _] : User_Data[site].items()) {
    cout << " [" << i << "] " << account << endl;
    accounts.push_back(account);
    i++;
  }

  cout << endl << "[0] back" << endl;
  cout << "/>: ";
  cin >> choice;

  if (choice == 0) {
    page_home(UserName, User_Data);
    return;
  }

  if (choice < 0 || choice > i - 1) {
    rm_account(UserName, User_Data, site);
    return;
  }

  while (choc != "1" && choc != "2") {
    system("clear");
    cout << "[ " << accounts[choice - 1] << " ]" << endl;
    cout << "you want to delete this account?" << endl;
    cout << " [1] yes \n [2] not " << endl;
    cout << "/>: ";
    cin >> choc;
  }

  if (choc == "1") {
    string FileName = UserName + ".json";
    json user_data = User_Data;

    user_data[site].erase(accounts[choice - 1]);
    USERDATA = user_data;
    rm_account(UserName, user_data, site);
  } else {
    rm_account(UserName, User_Data, site);
    return;
  }
}

void page_options() {
  system("clear");
  cout << "options: " << endl;
  cout << " [" << 1 << "] " << "change Password" << endl;
  cout << " [" << 0 << "] " << "back" << endl;
  cout << "/>: ";
  int choice;
  cin >> choice;

  switch (choice) {
  case 1:
    change_password();
    break;
  case 0:
    page_home(USERNAME, USERDATA);
    break;
  }
}

void page_del(string UserName, const json &User_Data) {
  string choc, site;
  int choice;
  system("clear");

  int i = 1;
  vector<string> sites;
  cout << "delete mode" << endl;
  cout << "choose a site: " << endl;
  for (const auto &[site, _] : User_Data.items()) {
    cout << " [" << i << "] " << site << endl;
    sites.push_back(site);
    i++;
  }

  cout << endl << "[0] back" << endl;
  cout << "/>: ";
  cin >> choice;

  if (choice == 0) {
    page_home(UserName, User_Data);
    return;
  }

  if (choice < 0 || choice > i - 1) {
    page_del(UserName, User_Data);
  }

  site = sites[choice - 1];

  while (choc != "1" && choc != "2") {
    system("clear");
    cout << "site: [ " << site << " ]" << endl;
    cout << "delete this site with all password storege?" << endl;
    cout << " [1] yes \n [2] not " << endl;
    cout << "/>: ";
    cin >> choc;
  }

  if (choc == "1") {
    string FileName = UserName + ".json";
    json user_data = User_Data;

    user_data.erase(site);
    USERDATA = user_data;
    page_del(UserName, user_data);
  } else {
    page_del(UserName, User_Data);
    return;
  }
}

void page_add_site(string UserName, const json &User_Data) {

  system("clear");

  int i = 2;
  vector<string> sites;
  cout << "add password" << endl;
  cout << "choose a site: " << endl;
  cout << " [1] new site" << endl;
  for (const auto &[site, _] : User_Data.items()) {
    cout << " [" << i << "] " << site << endl;
    sites.push_back(site);
    i++;
  }

  cout << endl << "[0] back" << endl;
  int choice;
  cout << "/>: ";
  cin >> choice;

  if (choice == 0) {
    page_home(UserName, User_Data);
    return;
  }

  system("clear");

  if (choice == 1) {
    new_site(UserName, User_Data);
    return;
  }

  if (choice < 1 || choice > i - 1) {
    page_one(UserName, User_Data);
    return;
  }
  // page for add password
  add_account(UserName, User_Data, sites[choice - 2]);
  return;
}

void new_site(string UserName, const json &User_Data) {
  system("clear");
  string FileName = UserName + ".json";
  string site, choice;
  json user_data = User_Data;
  cout << "enter your [site] or [0] to back:" << endl;
  cout << "/>: ";
  cin >> site;

  if (site == "0") {
    page_add_site(UserName, User_Data);
    return;
  }

  if (user_data.contains(site)) {
    add_account(UserName, user_data, site);
    return;
  }

  system("clear");
  cout << "site: " << site << endl;
  cout << "you want to add this site? " << endl;
  cout << " [1] yes " << " [2] not " << endl;
  cout << "/>: ";
  cin >> choice;

  if (choice == "1") {
    user_data[site] = {};
    USERDATA = user_data;
    add_account(UserName, user_data, site);
    return;

  } else {
    new_site(UserName, User_Data);
  }
}

void add_account(string UserName, const json &User_Data, string site) {
  system("clear");
  string FileName = UserName + ".json";
  string login, password, choice;
  json user_data = User_Data;
  cout << "site: " << site << endl;
  cout << "enter your login: " << endl;
  cout << "login: ";
  cin >> login;
  while (choice != "1" && choice != "2") {
    system("clear");
    cout << "site: " << site << endl;
    cout << " login: " << login << endl;
    cout << "use automatic password generation?" << endl;
    cout << " [1] yes ( recommended ) \n [2] not ( not recommended )" << endl;
    cout << "/>: ";
    cin >> choice;
  }
  bool auto_gen = false;
  if (choice == "2") {
    system("clear");
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
    system("clear");
    cout << "site: " << site << endl;
    cout << " login: " << login << endl;
    cout << " password: " << password << endl;
    cout << endl << "is you data correct?" << endl;
    cout << " [1] yes \n [2] not " << endl;
    cout << " [3] edit login" << endl;
    cout << " [4] edit password" << endl;
    cout << " [5] back to home" << endl;
    if (auto_gen) {
      cout << " [6] gen password" << endl;
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
    if (choice == "5") {
      page_home(UserName, User_Data);
      return;
    }

    if (choice == "6" && auto_gen == true) {
      password = gen_password();
    }
  }

  if (choice == "1") {
    user_data[site][login]["login"] = login;
    user_data[site][login]["password"] = password;
    USERDATA = user_data;
    page_home(UserName, user_data);
    return;

  } else if (choice == "2") {
    add_account(UserName, User_Data, site);
  }
}

void change_password() {
  system("clear");
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

  page_home(USERNAME, USERDATA);
}

void page_one(string UserName, const json &User_Data) {

  system("clear");

  int i = 1;
  vector<string> sites;
  cout << "show password" << endl;
  cout << "chose a site: " << endl;
  for (const auto &[site, _] : User_Data.items()) {
    cout << " [" << i << "] " << site << endl;
    sites.push_back(site);
    i++;
  }

  cout << endl << "[0] back" << endl;
  int choice;
  cout << "/>: ";
  cin >> choice;

  if (choice == 0) {
    page_home(UserName, User_Data);
    return;
  }

  system("clear");

  if (choice < 0 || choice > i - 1) {
    page_one(UserName, User_Data);
    return;
  }

  page_two(sites, choice, User_Data, UserName);
  return;
}

void page_two(vector<string> sites, int choice, const json &User_Data,
              string UserName) {
  system("clear");
  vector<string> accouts;
  int i, Selected_site;

  Selected_site = choice - 1;
  cout << "site: (" << sites[choice - 1] << ")" << endl;
  cout << "accouts: " << endl;
  i = 1;
  for (const auto &[accout, _] : User_Data[sites[choice - 1]].items()) {
    cout << " [" << i << "] " << accout << endl;
    accouts.push_back(accout);
    i++;
  }
  cout << endl
       << "[" << 0
       << "] "
          "back"
       << endl;

  cout << "/>: ";
  cin >> choice;

  if (choice == 0) {
    page_one(UserName, User_Data);
    return;
  }

  if (choice < 0 || choice > i - 1) {
    page_two(sites, Selected_site + 1, User_Data, UserName);
    return;
  }

  page_tree(accouts, sites, choice, User_Data[sites[Selected_site]], UserName,
            User_Data, Selected_site);
  return;
}

void page_tree(vector<string> accouts, vector<string> sites, int choice,
               const json &User_Data, string UserName, const json &All_data,
               int Selected_site) {

  system("clear");
  vector<string> data;
  int j;
  j = choice;

  cout << "site: (" << sites[Selected_site] << ") " << endl;
  cout << "accout: (" << accouts[choice - 1] << ") " << endl;
  cout << "login:" << endl;
  cout << " [ user/email ]: "
       << User_Data[accouts[choice - 1]]["login"].get<string>() << endl;
  cout << " [  password  ]: "
       << User_Data[accouts[choice - 1]]["password"].get<string>() << endl;

  cout << endl
       << "[" << 0
       << "] "
          "back"
       << endl;

  cout << "/>: ";
  cin >> choice;

  if (choice == 0) {
    page_two(sites, Selected_site + 1, All_data, UserName);
    return;
  }

  if (choice < 0 || choice > 0) {
    page_tree(accouts, sites, j, User_Data, UserName, All_data, Selected_site);
    return;
  }

  return;
}
