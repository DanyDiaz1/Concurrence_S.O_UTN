#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define MAX 10

sem_t cont1,cont2,cont3;
sem_t s1,s2,s3;
sem_t semA,semB;
sem_t A,B,C;
sem_t Ej2;
int x;
///Prototipado

void H1();
void H2();
void H3();
void *funcion1();
void mostrarA(char a);
void mostrarB(char b);
void mostrarC(char c);
void funcionA();
void funcionB();
void proceso1();
void proceso2();
void proceso3();

int main()
{
    int opcion=0;
    char seguir;

    //Ejercicio 1
    sem_init(&cont1,0,1);
    sem_init(&cont2,0,0);
    sem_init(&cont3,0,0);
    pthread_t h1,h2,h3;

    //Ejercicio 2
    pthread_attr_t attr;
    pthread_t thid[MAX];
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    sem_init(&Ej2,0,1);

    //Ejercicio 3
    sem_init(&s1,0,1); //1 ABC,ABC,ABC
    sem_init(&s2,0,0); //1 BCA,BCA,BCA
    sem_init(&s3,0,0);
    pthread_t ArrayHilos[3];
    char uno='A';
    char dos='B';
    char tres='C';

    //Ejercicio 5
    pthread_t hiloA;
    pthread_t hiloB;

    sem_init(&semA,0,1);
    sem_init(&semB,0,0);

    //Ejercicio 6
    pthread_t proc1;
    pthread_t proc2;
    pthread_t proc3;

    sem_init(&A,0,0);
    sem_init(&B,0,1);
    sem_init(&C,0,0);

    do
    {
        printf("Ingrese el numero de operacion que desea realizar...\n\n");
        printf("Ejercicio 1\n");
        printf("Ejercicio 2\n");
        printf("Ejercicio 3\n");
        printf("Ejercicio 4\n");
        printf("Ejercicio 5\n");
        printf("Ejercicio 6\n");


        scanf("%i",&opcion);

        switch(opcion)
        {
        case 1:

            pthread_create(&h1,NULL,H1,NULL);
            pthread_create(&h2,NULL,H2,NULL);
            pthread_create(&h3,NULL,H3,NULL);

            pthread_join(h1,NULL);
            pthread_join(h2,NULL);
            pthread_join(h3,NULL);

            break;

        case 2:

            for(int i = 0; i < MAX; i++)
            {

                pthread_create(&thid[i],&attr,funcion1,NULL);

                printf("Start sleep\n");
                Sleep(1000);
                printf("End sleep\n");
            }


            break;

        case 3:

            pthread_create(&ArrayHilos[0],NULL,mostrarA,uno);
            pthread_create(&ArrayHilos[1],NULL,mostrarB,dos);
            pthread_create(&ArrayHilos[2],NULL,mostrarC,tres);

            break;

        case 5:

            pthread_create(&hiloA,NULL,funcionA,NULL);
            pthread_create(&hiloB,NULL,funcionB,NULL);
            pthread_join(hiloA,NULL);
            pthread_join(hiloB,NULL);

            break;

        case 6:

            pthread_create(&proc1,NULL,proceso1,NULL);
            pthread_create(&proc2,NULL,proceso2,NULL);
            pthread_create(&proc3,NULL,proceso3,NULL);
            pthread_join(proc1,NULL);
            pthread_join(proc2,NULL);
            pthread_join(proc3,NULL);

            break;

        case 0:

            printf("El programa se cerrara...\n");

            break;

        default:

            printf("Numero de operacion incorrecto, vuelva a intentar\n\n");

            break;
        }

        printf("Desea realizar otra operacion? [s/n]\n");
        fflush(stdin);
        scanf("%c",&seguir);

        system("pause");
        system("cls");

    }
    while(opcion!=0 && seguir=='s');

    return 0;
}

//Ejercicio 1

void H1() /* Hilo Hi con i=1,2,3 */
{
    int i=0;
    while (i<5)
    {
        sem_wait(&cont1);
        printf("Soy el hilo %i \n",pthread_self());
        sem_post(&cont2);
        i++;
    }
}

void H2() /* Hilo Hi con i=1,2,3 */
{
    int i=0;

    while (i<5)
    {
        sem_wait(&cont2);
        printf("Soy el hilo %i \n",pthread_self());
        sem_post(&cont3);
        i++;
    }
}

void H3() /* Hilo Hi con i=1,2,3 */
{
    int i=0;
    while (i<5)
    {
        sem_wait(&cont3);
        printf("Soy el hilo %i \n",pthread_self());
        sem_post(&cont1);
        i++;
    }
}

//Ejercicio 2

void *funcion1()
{
    sem_wait(&Ej2);
    printf("Thread: %d\n", pthread_self());
    sem_post(&Ej2);
}

//Ejercicio 3

void mostrarA(char a)
{
    int i=0;

    while(i<5)
    {
        sem_wait(&s1);
        printf("%c\n",a);
        sem_post(&s2);
        i++;
    }
}

void mostrarB(char b)
{
    int i=0;

    while(i<5)
    {
        sem_wait(&s2);
        printf("%c\n",b);
        sem_post(&s3);
        i++;
    }
}

void mostrarC(char c)
{
    int i=0;

    while(i<5)
    {
        sem_wait(&s3);
        printf("%c\n",c);
        sem_post(&s1);
        i++;
    }
}


//Ejercicio 5
void funcionA()
{
    sem_wait(&semA);
    x=199;
    x=x+1;
    printf("%i\n",x);
    sem_post(&semB);
}

void funcionB()
{
    sem_wait(&semB);
    x=500;
    x=x/10;
    printf("%i\n",x);
    sem_post(&semA);
}


//Ejercicio 6

void proceso1()
{
    sem_wait(&A);
    printf("\nSoy el proceso %i\n",pthread_self());
    sem_post(&C);
}

void proceso2()
{
    sem_wait(&B);
    printf("\nSoy el proceso %i\n",pthread_self());
    sem_post(&A);
    sem_post(&B);
}

void proceso3()
{
    sem_wait(&B);
    sem_wait(&C);
    printf("\nSoy el proceso %i\n",pthread_self());
    sem_post(&B);
}
