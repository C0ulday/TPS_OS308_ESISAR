#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


/*
Ecrire un programme qui :
Affiche son numéro ( pid ) via l'appel à getpid()
Traite tous les signaux, sauf SIGUSR1 et SIGUSR2 , par une fonction fonc qui se contente
d'afficher le numéro du signal reçu.
3.
Traite le signal SIGUSR1 par une fonction fonc1 et le signal SIGUSR2 par fonc2 :
(a)
fonc1 affiche le numéro du signal reçu et la liste des utilisateurs de la machine (appel à la
commande who par system("who") )
(b)
fonc2 affiche le numéro du signal reçu et l'espace disque utilisé sur la machine (appel à la
commande df . par system("df .") )*/

void fonc(int sig){
  
   if((sig != 10) && (sig != 12)){
    printf("%d\n", sig); // on affiche le numéro du signal si c'est pas SIGUSR1 ou SIGUSR2
   }
}

void fonc2 (int NumSignal){
  printf("%d\n", NumSignal); 
  system("df .");
}

void fonc1 (int NumSignal){
  printf("%d\n", NumSignal);
  system("who");  
}

int main (void){

  int Nb_Sig;
  pid_t monPid = getpid();

  printf("mon pid est %d\n", monPid);

  
  for(Nb_Sig = 1; Nb_Sig < NSIG ; Nb_Sig ++){
    signal(Nb_Sig, fonc);
  
   
  }  
  signal(SIGUSR1, fonc1);
  signal(SIGUSR2, fonc2);

  while (1){
    sleep(100);
  } 
  return 0;
}

