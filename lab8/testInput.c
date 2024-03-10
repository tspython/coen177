/* 
 # Name: Tushar Shrivastav
 # Date: Friday 2:15
 # Title: Lab8
 # Description: Implmentation to generate testInput.txt
*/

#include <stdio.h>

int main(int argc, char *argv[]) {
        FILE *fp;
        char buffer [sizeof(int)];
        int i;
        fp = fopen("testInput.txt", "w");
        for (i=0; i < 10; i++){
                sprintf(buffer, "%d\n", rand()%50);
                fputs(buffer, fp);
        }
        fclose(fp);
        return 0;
}
