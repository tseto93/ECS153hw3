//Tony Seto

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/wait.h>
int main()
{
  int seconds, seconds2;
  struct stat sb;
  struct stat rp;
  time_t now;
  time(&now);
  char *execveargv[] = {"chown", "0:95", "sniff", NULL};
  char *execveenv[] = {"/usr/bin/chown", NULL};
  //if(argc != 2){
    //printf("Incorrect number of arguements.\n");
    //exit(1);
  //}
  //else{
    //printf("You have entered: %s\n\n", argv[1]);
  //}

  //part 2
  if(stat("sniff", &sb) == -1){
    printf("No such file");
    exit(1);
  }
  //part 1
  stat("runpriv.c", &rp);
  //printf("UID of runpriv.c: %d\n", rp.st_uid);

  //part 3
  if(sb.st_uid != getuid()){
    //printf("User ID of owner: %d, User ID of calling process: %d\n", sb.st_uid, getuid());//user ID of sniff, user ID of person
    printf("uid not the same \n");
    exit(1);

  }

  //printf("File permissions %lo\n", (unsigned long) sb.st_mode);
  unsigned long bit1 = sb.st_mode%8;
  unsigned long bit2 = (sb.st_mode/8)%8;
  unsigned long bit3 = (sb.st_mode/64)%8;

  //printf("lsb: %lo, msb: %lo, msb: %lo\n", bit1, bit2, bit3);
  if(bit1 || bit2 != 0){
    printf("Able to be read, write, executed by others beside owner\n");
    exit(1);
  }
  if(bit3 != 1 && bit3 != 3 && bit3 != 5 && bit3 != 7){
    printf("Not executable\n");
    exit(1);
  }
  //part 4
  //printf("Current time: %s\n", ctime(&now));
  //printf("Last status change: %s\n", ctime(&sb.st_ctime));
  //printf("Last file modification: %s\n", ctime(&sb.st_mtime));

  seconds = difftime(now, sb.st_ctime);
  seconds2 = difftime(now, sb.st_mtime);
  //printf("%d seconds from last status change.\n", seconds);
  if(seconds < 60 || seconds2 < 60){
    printf("status change or modification less than 1 minute ago\n");
    exit(1);
  }
  //seconds2 = difftime(now, sb.st_mtime);
  //printf("%d time difference between current and last mod change.\n", seconds2);
  //if(seconds2 < 60){
    //printf("modified less than 1 min ago\n");
    //exit(1);
  //}

  //part 5
  fork();
  execve("/usr/bin/chown", execveargv, execveenv);

  wait(NULL);
  char *execveargv1[] = {"chmod", "4550", "sniff", NULL};
  char *execveenv1[] = {"/usr/bin/chmod", NULL};
  fork();
  execve("/usr/bin/chmod", execveargv1, execveenv1);
  return 0;
}

