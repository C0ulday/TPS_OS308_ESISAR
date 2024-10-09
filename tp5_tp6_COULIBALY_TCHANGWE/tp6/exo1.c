#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>




/*Ecrire un programme qui crée deux processus, père et fils. Le père affiche les nombres entiers impairs compris
entre 1 et 100, alors que le fils affiche les entiers pairs compris dans le même intervalle. Synchroniser les
processus à l'aide des signaux pour que le résultat d'affichage soit : 1 2 3 ... 100*/


void fonction(int sig){
    // deroutement
}

int main(void){

    signal(SIGUSR1,fonction);
    pid_t fils = fork();

    switch (fils){

        case 0:
 
            printf("Je suis le fils %d \n", getpid());
            for(int i=2; i<=100; i+=2){
                pause(); // attend que le père ait fini
                printf("fils %d\n",i);
                kill(getppid(), SIGUSR1);
                  
                
            }
        break;

        default : 
            sleep(1); // 1 seconde pour laisser le temps au fils de se mettre en place
            printf("Je suis le père %d\n", getpid());
            for(int i=1;i<100 ;i+=2){
                    printf("pere %d\n",i); 
                    kill(fils, SIGUSR1);
                    pause();
                }
            break;
    } 
       
        
 
    return 0;
}

