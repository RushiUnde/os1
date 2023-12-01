[11:09 PM, 8/20/2023] Rushikesh Unde: }
[11:11 PM, 8/20/2023] Rushikesh Unde: #include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
int main()
{
int fd;
char buffer[80];
char msg[50] = "My name is Rushi";
fd = open ("check.txt",O_RDWR);
printf("fd = %d",fd);
if(fd != -1)
{
printf("\n check.txt opened with read write access\n");
write(fd,msg,sizeof(msg));
lseek(fd,0,SEEK_SET);
read(fd,buffer,sizeof(msg));
printf("\n %s was written to my file\n", buffer);
close(fd);
}
return 0;
}


