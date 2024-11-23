#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
sem_t* sem;
int n;
void * monTour(void* args){
  int i=*(int*)args;free(args);
  while(1){
  sem_wait(&sem[i]);
  printf("je suis le thread %d \n",i);
  sem_post(&sem[(i+1)%n]);
  }
  pthread_exit(NULL);
  
}
int main(int argc,char* argv[]){
  if (argc != 2) {
       perror("le nombre d'arguments insuffisants\n");
       printf("Usage: %s nombre argument\n", argv[0]);
        return 1;
    }
    n = atoi(argv[1]);
    if (n <= 0) {
        perror("le nombre de threads doit être un entier positif.\n");
        return 1;
    }
   pthread_t thread[n];
   sem=malloc(n*sizeof(sem_t));
   int resultat;
  
    for(int i=0;i<n;i++){
         resultat=sem_init(&sem[i],0,0);
         if(resultat==-1){
            perror("erreur de creation de thread %d \n");
            return 0;
          }
     }  
     sem_post(&sem[0]);
     
  for(int i=0;i<n;i++){
     int *arg=malloc(sizeof(int));
     *arg=i;
      resultat=pthread_create(&thread[i],NULL,monTour,arg);
     if(resultat==-1){
      perror("erreur de creation de thread %d \n");
      return 0;
    }
  }  
  for(int i=0;i<n;i++){
   pthread_join(thread[i],NULL);
  } 
  
    free(sem);  
  return 0;

}
