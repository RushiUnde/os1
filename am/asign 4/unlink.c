#include <stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
int main(){
int fd1,ret;
fd1 = open ("t.txt",O_RDONLY|O_CREAT,0777);
ret = unlink ("t.txt");
printf("\n 0 is sucess \n -1 is failure");
printf("\n result %d",ret);
return 0;
}

