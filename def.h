#include <iostream>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fstream>
#include <unistd.h>
using namespace std;
struct button {
  string pid;
  int jetton;
  int money;
};

struct small_blind {
  string pid;
  int jetton;
  int money;
};

struct big_blind {
  string pid;
  int jetton;
  int money;
};

struct card {
  int color;
  int point;
};
