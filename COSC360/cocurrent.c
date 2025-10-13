// acync - do stuff at the same time
// init - PID#1
// everything else is a fork
// copy on write - as soon as it writes, it copies

// fork, exec, and then join
// don't leave an orphan process
// race condition - two processes trying to write to one memory
//
//
// fork, then execute, then wait
// waitpid waits and then joins
// pipe, fork, exec, and then wait/join
// pipes have two ends
// child writes to pipe 0, parent reads from pipe 1
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
  pid_t pid;
  int status;
  int mypipes[2];
  pipe(mypipes);

  pid = fork();
  if (pid == 0) {
    // child process pid == 0
    close(mypipes[0]);
    dup2(mypipes[1], STDOUT_FILENO);
    execlp("ls", "ls", "-l", NULL);
    perror("execlp");
    return 69;
  } else {
    // parent process pid != 0
    close(mypipes[1]);

    // read from child;
    char data[256];
    int bytes;
    bytes = read(mypipes[0], data, 256);
    data[bytes] = '\0';
    waitpid(pid, &status, 0);

    printf("%s", data);
  }
}
