/*Ecrire un programme qui génère deux processus, père et fils. Le fils se met dans une boucle d'attente.
Après 5 secondes, le père lui envoie le signal SIGINT pour l'arrêter. A la réception, le fils attend 2
secondes et s'arrête. Le père attend la fin du fils avant de s'arrêter lui aussi.*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>


void fonction(int sig){
    sleep(2);
    printf("j'ai attendu je meurs\n");
    exit(0);
}

int main(void){

pid_t fils = fork();

switch (fils){
    case 0: 
        signal(SIGINT, fonction); //installation du signal SIGINT pour le fils
        pause(); // le fils attend un signal de son père
        break;

    default : 
        sleep(5); // le père dort 5 secondes
        kill(fils,SIGINT); // le père envoie le signalm au fils
        break;
}
  return 0;
}