#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
   int fd,rd;
   char buf[80];
   fd = open(argv[1],O_RDONLY);
   if(fd<0) {
      perror("open");
      exit(0);
   }
   do {
      rd = read(fd,buf,80);
      printf("%s",buf);
   } while(rd > 0);
   close(fd);
}
