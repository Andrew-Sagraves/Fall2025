#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
int main() {
  int mypipes[2];
  pipe(mypipes);

  int pid = fork();
  if (pid == 0) {
    close(mypipes[0]);
    execlp("ls", "ls", "-l", NULL);
    perror("execlp");
    return 1;
  }

  int status;
  close (mypipes[1]);

  int bytes;
  bytes = read(mypipes[0], data, 255);
  data[bytes] = '\0';
  waitpid(pid, &status, 0);
  write(mypipes[1], "Hello", strlen("Hello"));

  char bytes[256];
  int len;

  // 0 is read, 1 is write;
  len = read(mypipes[0], bytes, 256);

  bytes[len] = '\0';

  printf("%s", bytes);

  return 0;
}
