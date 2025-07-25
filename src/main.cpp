#include "../include/encrypt.h"
#include "../include/globals.h"
#include "../include/include.h"
#include "../include/pages.h"
#include "../include/uttils.h"

int main(int argc, char *argv[]) {

  if (argc != 3) {
    cout << "use: " << argv[0] << "<UserName> <Password>";
    return 0;
  }
  signal(SIGINT, close_program);

  USERNAME = argv[1];
  PASSWORD = argv[2];
  if (fs::exists(USERNAME + ".bin")) {
    string decrypted_json;
    if (decrypt_file(decrypted_json)) {
      system("clear");
      cout << "invalid password\n";
      return 1;
    }
    USERDATA = json::parse(decrypted_json);
  } else {
  }
  page_home(USERNAME, USERDATA);
  system("clear");
  string json_str = USERDATA.dump(4);
  encrypt_file(json_str);
  return 0;
}
