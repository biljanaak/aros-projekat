#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define UKUPAN_BROJ_MUSTERIJA 11
#define UKUPAN_BROJ_STOLICA  5

pthread_mutex_t mutex;
int slobodne_stolice = UKUPAN_BROJ_STOLICA;
int gotove_musterije = 0;

sem_t musterijaSemafor;
sem_t frizerSemafor;

void *frizerFunkcija() {

    while(1) {
        sem_wait( &musterijaSemafor );
        pthread_mutex_lock( &mutex );
        printf("Frizer poziva musteriju\n");
        slobodne_stolice++;
        pthread_mutex_unlock( &mutex );
        sleep(3);
        sem_post( &frizerSemafor );
        printf("Frizer je zavrsio sa musterijom\n");
        pthread_mutex_lock( &mutex );
        gotove_musterije++;
        pthread_mutex_unlock( &mutex );
        if(gotove_musterije==UKUPAN_BROJ_MUSTERIJA) break;
    }
        
}

void *musterijaFunkcija() {

    pthread_mutex_lock( &mutex );
    if(slobodne_stolice > 0) { 
        slobodne_stolice--;
        printf("Musterija je stigla i ceka. Broj praznih stolica je %d!\n", slobodne_stolice);
        pthread_mutex_unlock( &mutex );

        sem_post( &musterijaSemafor );
        sem_wait( &frizerSemafor );
        printf("Musterija je sela kod frizera!\n");

    } else {
        pthread_mutex_unlock( &mutex );
        printf("Musterija vidi da je guzva i odlazi!\n");
        pthread_mutex_lock( &mutex );
        gotove_musterije++;
        pthread_mutex_unlock( &mutex );
        pthread_exit(NULL);
    }
}

int main() {
    pthread_t niti[UKUPAN_BROJ_MUSTERIJA];
    pthread_t frizer;

    sem_init( &musterijaSemafor, 1, 0 );
    sem_init( &frizerSemafor, 1, 0 );

    pthread_mutex_init(&mutex,NULL);

    pthread_create(&frizer, NULL, frizerFunkcija, NULL);

    for(int i=0; i<UKUPAN_BROJ_MUSTERIJA; i++) {
        int cekanje =(rand() % 3);
        sleep(cekanje);
        pthread_create(&niti[i], NULL, musterijaFunkcija, NULL);
    }

    for(int i=0; i<UKUPAN_BROJ_MUSTERIJA; i++) {
        pthread_join(niti[i], NULL);
    }
    
    pthread_join(frizer, NULL);

    printf("Zadatak je gotov!\n");

    return 0;
}