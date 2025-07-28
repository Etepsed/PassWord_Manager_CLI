#include "../include/encrypt.h"
#include "../include/globals.h"
#include "../include/uttils.h"

void clear_screen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void close_program(int sinal) {
  cout << "program is closed!" << endl;
  clear_screen();
  string json_str = USERDATA.dump(4);
  encrypt_file(json_str);

  exit(0);
}
