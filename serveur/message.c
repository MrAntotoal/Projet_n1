#include "message.h"

void get_msg_next(char *buffer, char *res){
  int i = 0;
  while (buffer[i] != '\0') {
    i++;
  }
  i++;
  strcpy(res,buffer + i);
}
