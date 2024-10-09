#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

/*Ecrire un programme C qui utilise 3 processus H, M, S qui incrémentent les 3 « aiguilles » d'une horloge. 
S reçoit un signal SIGALRM chaque seconde (émis par la fonction alarm(1)) et émet un signal à M quand son compteur passe de 59 à 0.
Quand M reçoit un signal, il incrémente son compteur. Quand son compteur passe de 59 à 0, M envoie un signal à H. 
Les paramètres correspondent aux valeurs d'initialisation des compteurs*/

// on utlise 3 au lieu de 60 pour le temps de test

// declaration globale
int m =0;
int s =0;
int h =0;
int temps = 3;

pid_t fils1,fils2;
// fin declaration globale


// declaration des handlers
void heures(int sig){
    h++;
    printf("heures %d\n",h);
}

void minutes(int sig){
    if( m <temps){
        m ++;
        printf("minutes %d\n",m);
    }
    else {
        m = 0;
        //appeler un autre process charge des heures
        kill(fils2,SIGUSR1);
    }
    
}

void secondes(int sig){

    if(s < temps){ 
        s++;
        printf("%d\n",s);
    }
    else{
        s = 0;
        //appeler un autre process charge des minutes
        kill(fils1,SIGUSR1);
    }
    alarm(1); // se rapelle
}

//
int main(void){

    if( (fils1 = fork() ) ==0){ 

        signal(SIGUSR1,minutes); //prepartion du fils pour les minutes

        if( (fils2 = fork() ) == 0){ // le premier fils crée un autre
        // pour éviter que la création simultannée des processus crée des problèmes

            signal(SIGUSR1, heures); //prepartion du fils pour les heures
            while(1); // maintient en vie du fils heures
        }

        while(1); // maintient en vie du fils minutes

    }
    else{

        //pere gère les secondes
        signal(SIGALRM,secondes);
        alarm(1); // envoie 1s equivaut à un kill(envoie d'un signal)
        while(1); // maintient vivant le processus pere
    }


    return 0;
}