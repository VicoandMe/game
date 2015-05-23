#include"def.h"

using namespace std;

struct button bplayer;
struct small_blind sbplayer;
struct big_blind bbplayer;
string holdmsg = "player ";

vector<struct card> myCards;
vector<struct card> flopCards;


string ID;
int jetton;
int money;

bool is_Fold;
bool is_AllIn;
ofstream outfile;

int string_to_int(char *a) {
  int len = strlen(a);
  int t = 0;
  int flag = 1;
  for(int i = 0; i < len; i++) {
    if(a[i] == '-') {
      flag = -1;
      continue;
    }
    if(a[i] <= '9' && a[i] >= '0') {
      t = t*10 + flag*(a[i] - '0');
    }
  }
  return t;
}

int string_to_int2(string a) {
  int len = a.length();
  int t = 0;
  int flag = 1;
  for(int i = 0; i < len; i++) {
    if(a[i] == '-') {
      flag = -1;
      continue;
    }
    if(a[i] <= '9' && a[i] >= '0') {
      t = t*10 + flag*(a[i] - '0');
    }
  }
  return t;
}

void split(char *a, int len, vector<string> &temp, char c) {
   string st;
   for(int i = 0; i < len; i++) {
     if(a[i] != c) {
       st.push_back(a[i]);
     } else {
       temp.push_back(st);
       st = "";
     }
   }
}

void split2(string a, int len, vector<string> &temp, char c) {
   string st;
   for(int i = 0; i < len; i++) {
     if(a[i] != c) {
       st.push_back(a[i]);
     } else {
       temp.push_back(st);
       st = "";
     }
   }
}

void seat_analyse(string msg) {
  vector<string> t;
  split2(msg,msg.length(),t,' ');
  if(t[0] == "button") {

    if (t[1] == ID) {
      jetton = string_to_int2(t[2]);
      money = string_to_int2(t[3]);
    }
    bplayer.pid = t[1];
    bplayer.jetton = string_to_int2(t[2]);
    bplayer.money = string_to_int2(t[3]);

  } else if(t[0] == "small") {
    if (t[1] == ID) {
      jetton = string_to_int2(t[2]);
      money = string_to_int2(t[3]);
    }
    sbplayer.pid = t[1];
    sbplayer.jetton = string_to_int2(t[2]);
    sbplayer.money = string_to_int2(t[3]);
  } else if(t[0] == "big") {
    if (t[1] == ID) {
      jetton = string_to_int2(t[2]);
      money = string_to_int2(t[3]);
    }
    bbplayer.pid = t[1];
    bbplayer.jetton = string_to_int2(t[2]);
    bbplayer.money = string_to_int2(t[3]);
  } else {
    if (t[0] == ID) {
      jetton = string_to_int2(t[1]);
      money = string_to_int2(t[2]);
    }
  }
}

int get_color(string msg) {
  if(msg == "SPADES") {
    return 1;
  } else if(msg == "HEARTS") {
    return 2;
  } else if(msg == "CLUBS") {
    return 3;
  } else if(msg == "DIAMONDS") {
    return 4;
  }
}

int get_point(string msg) {
  if(msg == "2") {
    return 2;
  } else if(msg == "3") {
    return 3;
  } else if(msg == "4") {
    return 4;
  } else if(msg == "5") {
    return 5;
  } else if(msg == "6") {
    return 6;
  } else if(msg == "7") {
    return 7;
  } else if(msg == "8") {
    return 8;
  } else if(msg == "9") {
    return 9;
  } else if(msg == "10") {
    return 10;
  } else if(msg == "J") {
    return 11;
  } else if(msg == "Q") {
    return 12;
  } else if(msg == "K") {
    return 13;
  } else if(msg == "A") {
    return 14;
  }
}

void flop_analyse(string msg) {
  struct card temp;
  vector<string> t;
  split2(msg, msg.length(), t, ' ');
  temp.color = get_color(t[0]);
  temp.point = get_point(t[1]);
  flopCards.push_back(temp);
}

void hold_cards_msg(string msg) {
  struct card temp;
  vector<string> t;
  split2(msg, msg.length(), t, ' ');
  temp.color = get_color(t[0]);
  temp.point = get_point(t[1]);
  myCards.push_back(temp);
}

void blind_msg(string msg) {
  vector<string> temp;
  split2(msg, msg.length(), temp, ' ');
  if(temp[0] == ID + ":") {
     jetton = jetton - string_to_int2(temp[1]);
     jetton = jetton > 0? jetton:0;
  }
}

void pot_msg(string msg) {
  vector<string> temp;
  split2(msg, msg.length(), temp, ' ');
  if(temp[0] == ID + ":") {
     jetton = jetton + string_to_int2(temp[1]);
  }
}

bool cardCmp(struct card a, struct card b) {
  return a.point > b.point;
}

int two_Card(vector<struct card> &allCard) {
  if (allCard[0].point == allCard[1].point) {
    return 3;
  } else if (allCard[0].color == allCard[1].color) {
    return 2;
  } else if (allCard[0].point - allCard[1].point < 3) {
    return 2;
  } else if (allCard[0].point > 10 || allCard[1].point > 10) {
    return 2;
  } else {
    return 4;
  }
}

int five_Card(vector<struct card> allCard) {
  int pair_num = 0;
  int con = 0;
  int max_con = 0;
  int sam = 0;
  int three = 0;
  int four = 0;
  int c[4] = {0,0,0,0};
  int last_point;
  int last_color;
  last_point = allCard[0].point;
  c[last_color]++;
  for(int i = 1; i < allCard.size(); i++) {
    if (last_point == allCard[i].point) {
      sam++;
    } else {
      if(sam == 1) {
        pair_num++;
      } else if(sam == 2) {
        three++;
      } else if(sam == 3) {
        four++;
      }
      sam = 0;
    }
    if (last_point == allCard[i].point+1) {
      con++;
    } else {
      max_con = max_con > con? max_con:con;
      con = 0;
    }
    last_point = allCard[i].point;
  }
  if(sam == 1) {
    pair_num++;
    } else if(sam == 2) {
      three++;
    } else if(sam == 3) {
      four++;
    }
   max_con = max_con > con? max_con:con;
   if(four == 1 || max_con == 4 || (three == 1 && pair_num > 0)) {
     return 3;
   }

   if(three || pair_num > 0) {
     return 2;
   }

   if(max_con > 2) {
     return 2;
   }

   return 4;
}

int six_Card(vector<struct card> allCard) {
  int pair_num = 0;
  int con = 0;
  int max_con = 0;
  int sam = 0;
  int three = 0;
  int four = 0;
  int c[4] = {0,0,0,0};
  int last_point;
  int last_color;
  last_point = allCard[0].point;
  c[last_color]++;
  for(int i = 1; i < allCard.size(); i++) {
    if (last_point == allCard[i].point) {
      sam++;
    } else {
      if(sam == 1) {
        pair_num++;
      } else if(sam == 2) {
        three++;
      } else if(sam == 3) {
        four++;
      }
      sam = 0;
    }
    if (last_point == allCard[i].point+1) {
      con++;
    } else {
      max_con = max_con > con? max_con:con;
      con = 0;
    }
    last_point = allCard[i].point;
  }
  if(sam == 1) {
    pair_num++;
    } else if(sam == 2) {
      three++;
    } else if(sam == 3) {
      four++;
    }
   max_con = max_con > con? max_con:con;
   if(four == 1 || max_con == 4 || (three == 1 && pair_num > 0)) {
     return 3;
   }

   if(three || pair_num > 0) {
     return 2;
   }

   if(max_con > 3) {
     return 2;
   }

   return 4;
}

int seven_Card(vector<struct card> allCard) {
     int pair_num = 0;
  int con = 0;
  int max_con = 0;
  int sam = 0;
  int three = 0;
  int four = 0;
  int c[4] = {0,0,0,0};
  int last_point;
  int last_color;
  last_point = allCard[0].point;
  c[last_color]++;
  for(int i = 1; i < allCard.size(); i++) {
    if (last_point == allCard[i].point) {
      sam++;
    } else {
      if(sam == 1) {
        pair_num++;
      } else if(sam == 2) {
        three++;
      } else if(sam == 3) {
        four++;
      }
      sam = 0;
    }
    if (last_point == allCard[i].point+1) {
      con++;
    } else {
      max_con = max_con > con? max_con:con;
      con = 0;
    }
    last_point = allCard[i].point;
  }
  if(sam == 1) {
    pair_num++;
    } else if(sam == 2) {
      three++;
    } else if(sam == 3) {
      four++;
    }
   max_con = max_con > con? max_con:con;
   if(four == 1 || max_con == 4 || (three == 1 && pair_num > 0)) {
     return 3;
   }

   if(three || pair_num > 0) {
     return 2;
   }

   return 4;
}

int card_analyse() {
  vector<struct card> allCard;
  allCard.clear();
  allCard.push_back(myCards[0]);
  allCard.push_back(myCards[1]);
  for (int i = 0; i < flopCards.size(); i++) {
    allCard.push_back(flopCards[i]);
  }
  sort(allCard.begin(),allCard.end(), cardCmp);
  switch(allCard.size()) {
    case 2: return two_Card(allCard);break;
    case 5: return five_Card(allCard);break;
    case 6: return six_Card(allCard);break;
    case 7: return seven_Card(allCard);break;
  }
}

void inquire_analyse(string msg) {
  vector<string> temp;
  split2(msg, msg.length(), temp, ' ');
  if(temp[0] == ID) {
    if(jetton != string_to_int2(temp[1])) {
      jetton == string_to_int2(temp[1]);
    }
    if(money != string_to_int2(temp[2])) {
      money == string_to_int2(temp[2]);
    }
  }
}

int main(int argc, char** argv) {
   int sockfd, n, rec_len;
   char recvline[4096],sendline[4096];
   char buf[4096];
   struct sockaddr_in servaddr;
   struct sockaddr_in cliaddr;
   //cout<<argv[1]<<endl;
   sockfd = socket(AF_INET, SOCK_STREAM, 0);

   memset(&cliaddr, 0, sizeof(cliaddr));
   cliaddr.sin_family = AF_INET;
   cliaddr.sin_port = htons(string_to_int(argv[4]));
   inet_pton(AF_INET, argv[3], &cliaddr.sin_addr);
   if(bind(sockfd, (struct sockaddr*)&cliaddr, sizeof(cliaddr)) == -1) {
     cout<<"bind error"<<endl;
   }

   memset(&servaddr, 0, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons(string_to_int(argv[2]));
   inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
   while(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
     //cout<<"connect error"<<endl;
     sleep(2);
     outfile.open(argv[5],ios::app);
     outfile<<"connect error\n";
     outfile.close();
   }
   string temp = "reg:";
   temp += " ";
   for(int i = 0; i < strlen(argv[5]);i++) {
     temp.push_back(argv[5][i]);
     ID.push_back(argv[5][i]);
   }
   temp += " ";
   for(int i = 0; i < strlen(argv[5]);i++) {
     temp.push_back(argv[5][i]);
   }
   temp += " ";
   temp += "\n";
   for(int i = 0; i < temp.length();i++) {
     sendline[i] = temp[i];
   }
   send(sockfd,sendline,temp.length(),0);
   is_Fold = 0;
   is_AllIn = 0;

   outfile.open(argv[5],ios::app);
   char t[10] = "strat\n";
   for(int i = 0; i < strlen(t);i++) {
         outfile<<t[i];
   }
   outfile.close();
   while(1) {
      rec_len = recv(sockfd, recvline, 4096,0);
      recvline[rec_len] = '\0';
      outfile.open(argv[5],ios::app);
      outfile<<recvline;
      outfile<<"-----------------------------------";
      outfile.close();
      if(strcmp(recvline, "game-over") == 0) {
        break;
      }
      vector<string> servmsg;
      servmsg.clear();
      split(recvline,rec_len,servmsg,'\n');
      outfile.open(argv[5],ios::app);
      outfile<<servmsg[0];
      outfile<<'\n';
      outfile.close();
      int msg_index = 0;
      while(msg_index < servmsg.size()) {
      if (servmsg[msg_index] == "seat/ ") {
          //outfile.open(argv[5],ios::app);
          //outfile<<'1';
          //outfile<<'\n';
          //outfile.close();
         myCards.clear();
         flopCards.clear();
         msg_index++;
         for(; msg_index < servmsg.size();) {
            seat_analyse(servmsg[msg_index]);
            msg_index++;
            if(servmsg[msg_index] == "/seat ") {
              break;
            }
         }
      } else if (servmsg[msg_index] == "hold/ ") {
         myCards.clear();
         flopCards.clear();
         msg_index++;
         for(;msg_index < servmsg.size();) {
           hold_cards_msg(servmsg[msg_index]);
           msg_index++;
           if(servmsg[msg_index] == "/hold ") {
             break;
           }
         }
      } else if (servmsg[msg_index] == "inquire/ ") {
        msg_index++;
        for(; msg_index < servmsg.size();) {
          if(servmsg[msg_index] == "/inquire ") {
            break;
          }
          inquire_analyse(servmsg[msg_index]);
          msg_index++;
        }
        int cmd = 0;
        if(!is_Fold || !is_AllIn) {
          cmd = card_analyse();
          char cmd1[20] = "check\n\0";
          char cmd2[20] = "call\n\0";
          char cmd3[20] = "all_in\n\0";
          char cmd4[20] = "fold\n\0";
          if (cmd == 1) {
            strcpy(sendline,cmd1);
          } else if (cmd == 2) {
            strcpy(sendline,cmd2);
          } else if (cmd == 3) {
            strcpy(sendline,cmd3);
          } else if (cmd == 4) {
            strcpy(sendline,cmd4);
          }
          outfile.open(argv[5],ios::app);
          outfile<<sendline;
          outfile<<myCards.size()+flopCards.size();
          outfile<<'\n';
          outfile.close();
          send(sockfd,sendline,strlen(sendline),0);
        }
      } else if (servmsg[msg_index] == "flop/ ") {
        flopCards.clear();
        msg_index++;
        for(; msg_index < servmsg.size();) {
           if(servmsg[msg_index] == "/flop ") {
             break;
           }
           flop_analyse(servmsg[msg_index]);
           msg_index++;
        }
      } else if (servmsg[msg_index] == "turn/ ") {
        msg_index++;
        for(; msg_index < servmsg.size();) {
           if(servmsg[msg_index] == "/turn ") {
             break;
           }
           flop_analyse(servmsg[msg_index]);
           msg_index++;
        }
      } else if (servmsg[msg_index] == "river/ ") {
        msg_index++;
        for(; msg_index < servmsg.size();) {
           if(servmsg[msg_index] == "/river ") {
             break;
           }
           flop_analyse(servmsg[msg_index]);
           msg_index++;
        }
      } else if (servmsg[msg_index] == "blind/ "){
          //for(int i = 1; i < servmsg.size() - 1; i++) {
          //  blind_msg(servmsg[i]);
          //}
        msg_index++;
        for(; msg_index < servmsg.size();) {
           if(servmsg[msg_index] == "/blind ") {
             break;
           }
           blind_msg(servmsg[msg_index]);
           msg_index++;
        }
      } else if (servmsg[msg_index] == "pot-win/ ") {
          //for(int i = 1; i < servmsg.size() - 1; i++) {
          //  pot_msg(servmsg[i]);
          //}
        msg_index++;
        for(; msg_index < servmsg.size();) {
           if(servmsg[msg_index] == "/pot-win ") {
             break;
           }
           pot_msg(servmsg[msg_index]);
           msg_index++;
        }
        myCards.clear();
        flopCards.clear();
        is_Fold = 0;
        is_AllIn = 0;
      } else if (servmsg[msg_index] == "showdown/ ") {
        msg_index++;
        for(; msg_index < servmsg.size();) {
           if(servmsg[msg_index] == "/showdown ") {
             break;
           }
           msg_index++;
        }
         myCards.clear();
         flopCards.clear();
      }
      msg_index++;
      }
   }
   outfile.close();
}
