#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
int main()
{
pid_t p;
printf("before fork\n");
fork();
if(p<0){
printf("Error");
}
if(p==0)
{
printf("My parent's id is %d\n",getppid());
printf("I am child having id %d\n",getpid());

}
else{
printf("I am parent having id %d\n",getpid());
printf("My child's id is %d\n",getpid());

}
printf("Common\n");
}

