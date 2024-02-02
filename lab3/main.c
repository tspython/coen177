/*Sample C program for Lab assignment 3*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
//main
int main() {
int fds[2];
pipe(fds);
/*child 1 duplicates downstream into stdin */
if (fork() == 0) {
dup2(fds[0], 0);
close(fds[1]);
execlp("more", "more", 0);
}
/*child 2 duplicates upstream into stdout */
else if (fork() == 0) {
dup2(fds[1], 1);
close(fds[0]);
execlp("ls", "ls", 0);
}
else { /*parent closes both ends and wait for children*/
close(fds[0]);
close(fds[1]);
wait(0);
wait(0);
}
return 0;
}
Step 2. Compile and run the following program
/*Sample C program for Lab assignment 3*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
// main
int main(int argc,char *argv[]){
int fds[2];
char buff[60];
int count;
int i;
pipe(fds);
if (fork()==0){
printf("\nWriter on the upstream end of the pipe -> %d arguments \n",argc);
close(fds[0]);
for(i=0;i<argc;i++){
write(fds[1],argv[i],strlen(argv[i]));
}
exit(0);
COEN 177 – Lab assignment 3 3/4
}
else if(fork()==0){
printf("\nReader on the downstream end of the pipe \n");
close(fds[1]);
while((count=read(fds[0],buff,60))>0){
for(i=0;i<count;i++){
write(1,buff+i,1);
write(1," ",1);
}
printf("\n");
}
exit(0);
}
else{
close(fds[0]);
close(fds[1]);
wait(0);
wait(0);
}
return 0;
}
