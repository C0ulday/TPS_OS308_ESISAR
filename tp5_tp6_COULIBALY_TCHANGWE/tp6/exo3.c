#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void action_fils(int fils_numero);
void action_pere(int sig);
void action_pere_vivant(int sig);

int entier = 1;

int main(void) {
    pid_t pid = 0;

    for (int i = 1; i <= 6; i++) {
        pid = fork();

        if (pid == 0) {
            printf("Je suis le fils %d\n", i);
            action_fils(i);
            pause(); // ils se mettent en pause jusqu'à ce que
                     // leur père les appelle
        }
        if (pid == -1) {
            perror("Erreur lors de la création du fils");
            exit(EXIT_FAILURE);
        }
    }
    sleep(5); // le père attend que ses fils se crée
    signal(SIGUSR1, action_pere);      // pour qu'un fils annonce sa mort
    signal(SIGUSR2, action_pere_vivant); // pour qu'un fils annonce sa survie

    printf("Coucou je suis le père !\n");

    for (int i = 1; i <= 6; i++) {
        kill(i,SIGUSR1);
        pause(); // attendre réponse du fils
    }

    return 0;
}

void action_fils(int fils_numero) {

    printf("Je suis le fils %d. Je lis le barillet !\n", fils_numero);
    if (entier == fils_numero) {
        printf("Oh non ! J'ai lu mon numéro !\n");
        kill(getppid(), SIGUSR1);
        exit(EXIT_SUCCESS);
    } else {
        printf("Je suis encore vivant !\n");
        kill(getppid(), SIGUSR2);
        pause(); // il se met en pause
    }
}

void action_pere(int sig) {
    // déroutement
    printf("▄︻┻═┳一 ! Vous êtes libres les autres !\n");

    for (int i = 1; i <= 6; i++) {
        kill(i, SIGTERM);
        wait(NULL);
    }

    exit(EXIT_SUCCESS);
}

void action_pere_vivant(int sig) {
    // déroutement
    printf("Réception du signal de survie du fils.\n");
}
