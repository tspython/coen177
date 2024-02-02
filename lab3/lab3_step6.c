/* In Computer Science, the producer–consumer problem is a classic multi- process synchronization */
/* example. The producer and the consumer share a common fixed-size buffer. The producer puts */
/* messages to the buffer while the consumer removes messages from the buffer. Pipes provide a perfect */
/* solution to this problem because of their built-in synchronization capability. So as a programmer, you do */
/* not have to worry about whether or not the buffer is empty or full to produce or consume messages. */
/* Write a C program to implement the producer-consumer message communication using pipes. */

/**************************
*   Lab3 - pipe()
**************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

// main
int main(int argc,char *argv[]){
   int  fds[2];
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
