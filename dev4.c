#include <stdio.h>
#include <pthread.h>
#include<stdlib.h>
#include <unistd.h>
#include<semaphore.h>
int i=0;
int compteur=0;
int n=100;
sem_t semSecondaire,semTertiaire;
void * threadsecondaire(void* arg){
	while(i<1000){
	sem_wait(&semSecondaire);
	for(int j=1;j<=n;j++){
	printf("%d \n",compteur++);
	
	}
	sem_post(&semTertiaire);
	++i;
	}
  pthread_exit(NULL);
}
void * threadtertiaire(void* arg){
	while(1){
	sem_wait(&semTertiaire);
	for(int j=1;j<=n;j++){
	printf(" %d\n",-compteur--);
	}
	sem_post(&semSecondaire);
	++i;
	}
  pthread_exit(NULL);
}
int main(    ){
    int resultat;
    pthread_t th,th1;
    resultat=sem_init(&semSecondaire,0,1);
    if(resultat==-1){
    perror("Thread erreur de creation \n");
     return 0;
    }
    
    resultat=sem_init(&semTertiaire,0,0);
   if(resultat==-1){
        perror("Thread erreur de creation \n");
     return 0;
    }

	resultat=pthread_create(&th,NULL,threadsecondaire,(void*)NULL);
  if(resultat==-1){
    perror("Thread erreur de creation \n");
     return 0;
    }
    
    resultat=pthread_create(&th1,NULL,threadtertiaire,(void*)NULL);
     if(resultat==-1){
	    perror("Thread erreur de creation \n");
	     return 0;
    }
	pthread_join(th,NULL);
	pthread_join(th1,NULL);
  
  return 0;
}
