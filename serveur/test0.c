
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  char truc[10] = {'a','b','\0','c','d','\0'};
  char *args[3];
  args[0] = "test";
  args[1] = truc;
  args[2] = NULL;
  int pid;
  pid = fork();
  if(pid == 0)
  {
    execve("test",args,NULL);
    exit(-1);
  }
  sleep(10);
  return 0;
}
