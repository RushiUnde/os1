#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>

sem_t empty,full;
pthread_mutex_t mutex;
int buffer[5];
int count =0;

void *producer(void *arg){
     long int num =(long int)arg;
    //producer is trying to produce the data;
     sem_wait(&empty);
     //producer is allowed to produce a data
     //producer is waiting for his turn

     pthread_mutex_lock(&mutex);
     //producer is producing a data
     buffer[count]= rand()%10;
      printf("\nproducer: %ld produced:%d",num+1,buffer[count]);
      count++;
      //sleep(1); 

      pthread_mutex_unlock(&mutex);

     sem_post(&full);//producer is incrementing full value
     pthread_exit(NULL);
}
void *consumer(void *arg){
     long int num =(long int)arg;
    //consumer is trying to consume the data;
     sem_wait(&full);
     //if full is 0 it cant consume
     //consumer is allowed to consume a data
     //consumer is waiting for his turn

     pthread_mutex_lock(&mutex);
     //consume is consuming a data
      count--;
      printf("\n consumer: %ld consumed:%d",num+1,buffer[count]);
     // sleep(1); 

      pthread_mutex_unlock(&mutex);

     sem_post(&empty);
     pthread_exit(NULL);
}

int main(){
   
   int np,nc;
   pthread_t p[10],c[10];  
   unsigned long int i,j,k,l;
   printf("enter the number of producer and consumers");
   scanf("%d %d",&np,&nc);


   //initialise semaphore variable here
   sem_init(&empty,0,5);  
   sem_init(&full,0,0);

   //declaration of mutex
   pthread_mutex_init(&mutex,NULL);


   //create producer thread
   for(i=0;i<np;i++){
    pthread_create(&p[i],NULL,producer,(void *)i);
   }

   //create consumer threads

   for(j=0;j<nc;j++){
    pthread_create(&c[j],NULL,consumer,(void *)j);
   }
   //join producer threads
   for(k=0;k<np;k++)
   pthread_join(p[k],NULL);

   //join consumewr threads
   for(l=0;l<nc;l++)
   pthread_join(c[l],NULL);



}

