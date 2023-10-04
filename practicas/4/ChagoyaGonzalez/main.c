#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem_hola, sem_mundo;

void *imprimir_hola(void *arg) {
    sem_wait(&sem_hola); // Espera a que el sem�foro de "Hola" est� desbloqueado
    printf("Hola ");
    sem_post(&sem_mundo); // Libera el sem�foro de "Mundo"
    return NULL;
}

void *imprimir_mundo(void *arg) {
    sem_wait(&sem_mundo); // Espera a que el sem�foro de "Mundo" est� desbloqueado
    printf("Mundo\n");
    sem_post(&sem_hola); // Libera el sem�foro de "Hola"
    return NULL;
}

int main() {
    pthread_t hilo_hola, hilo_mundo;

    sem_init(&sem_hola, 0, 1);  // Inicializa el sem�foro de "Hola" en 1
    sem_init(&sem_mundo, 0, 0); // Inicializa el sem�foro de "Mundo" en 0

    pthread_create(&hilo_hola, NULL, imprimir_hola, NULL);
    pthread_create(&hilo_mundo, NULL, imprimir_mundo, NULL);

    pthread_join(hilo_hola, NULL);
    pthread_join(hilo_mundo, NULL);

    sem_destroy(&sem_hola);
    sem_destroy(&sem_mundo);

    return 0;
}
