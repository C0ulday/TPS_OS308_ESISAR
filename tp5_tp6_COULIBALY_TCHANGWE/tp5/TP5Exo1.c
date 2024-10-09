#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>


/*Ecrire un programme qui ignore TOUS les signaux.

1. Tester la valeur de retour de la fonction signal pour relever les signaux qu'on ne peut ignorer.
2. Utiliser la fonction char* strsignal(int sig) de la bibliothèque signal.h pour afficher
les constantes symboliques associées aux signaux qu’on ne peut ignorer.
3. Faire <CTRL> C dans la fenêtre où le programme s’exécute. 
Envoyer également des signaux vers ce programme par le biais de kill depuis une autre fenêtre. 
Constater que SIGKILL (signal numéro 9) termine ce programme.*/

int main(void){

  int Nb_Sig;

  for(Nb_Sig = 1; Nb_Sig < NSIG ; Nb_Sig ++){

    if(signal(Nb_Sig, SIG_IGN) == SIG_ERR){
      printf("Signal %d non ignoré\n",Nb_Sig);
      printf("%s\n",strsignal(Nb_Sig));
    }
    
    //printf("%d\n",Nb_Sig);

    
  }
  while(1){
    sleep(5); // attend 5 secondes pour laisser le temps aux signaux
    // d'être reçu
  } 
  return 0;
}
