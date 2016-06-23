#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#define NUM_PROCESSOS 15
#define QUANTUM 50

typedef struct celula celula;
typedef struct processo processo;



struct processo{
  int id;
  pthread_t thread;
  int contadorTempo;
  int tempoExecucao;
};

int primeiro = 0;
int ultimo = 0;
struct processo listaP[NUM_PROCESSOS];
int tam = 0;

void inserir(processo p){
    if(ultimo < NUM_PROCESSOS){
      listaP[ultimo] = p;
      ultimo++;
      tam++;
    }
    else{
      printf("Estourou o tamanho da Lista\n");
    }
}
/*void inserir_ultimo(processo p){
    if(ultimo < NUM_PROCESSOS){
      listaP[ultimo] = p;
      ultimo++;
      tam++;
    }
    else{
      printf("Estourou o tamanho da Lista\n");
    }
}*/
processo *retirar_primeiro(void){

  processo *p;

  if(primeiro != ultimo){
    int i;
    int tam = ultimo;
    p  = &listaP[primeiro];
    listaP[0] = listaP[1];
    for(i = 1;i<tam;i++){
        listaP[i] = listaP[i+1];
    }
    ultimo--;
    tam--;
  }
  else{
    printf("Lista vazia\n");
    return NULL;
  }
  return p;
}

void *funcao(void *ptr) {
  processo *t = (processo *) ptr;

      if(t->contadorTempo > 0){
          printf("Continuando Thread %d\n\n\n",t->id);
      }
      else if(t->contadorTempo >= t->tempoExecucao){
          //printf("Executou else if\n");
          printf("Thread %d Terminada\n\n\n",t->id);
        }
      else{
          //printf("Executou else\n");
          printf("Executando Thread %d\n\n\n",t->id);
      //execl("/bin/nano","nano texto.txt",NULL);
    }
}

int main(){

    int i;
      srand(time(NULL));
    for(i = 0;i<10;i++){
        processo p;
        int temp = 0;
        printf("Digite o tempo em ms que o processo %d precisara para terminar sua tarefa\n",i+1);
        scanf("%d",&temp);
        //p.tempoExecucao = (rand()%700)+10;
        p.tempoExecucao = temp;
        p.contadorTempo = 0;
        p.id = i + 1;
        inserir(p);
    }
    //i = 0;
    while(tam > 0){ //cria as threads
      //pthread_t t;
      processo *p = retirar_primeiro();
      //listaP[0].thread = t;
      pthread_create(&p->thread,NULL,funcao,(void *)(p));
        int cont = 0;
        while (cont < QUANTUM || cont < p->tempoExecucao) {
          sleep(1/60);//sleep de 1 milesimo
          cont++;
        }
        p->contadorTempo+=cont;

        if((p->contadorTempo) <= (p->tempoExecucao)){
            inserir(*p);
            printf("Thread %d Interrompida\n",p->id);
        }
        else{
            printf("Thread %d Terminada\n\n\n",p->id);
            pthread_join(p->thread,NULL);
        }

        //pthread_join(p->thread,NULL);
        i++;
    }

    /*while(tam > 10){ //continua o processo
      processo *p = retirar_primeiro();
        funcao((void *)(p)); // chama processo
        int cont = 0;
        while (cont < QUANTUM || cont < p->tempoExecucao) {
          sleep(1/60);//sleep de 1 milesimo
          cont++;
        }
        p->contadorTempo+=cont;

        if((p->contadorTempo) <= (p->tempoExecucao)){
            inserir(*p);
        }
        else{
            printf("Thread %d Terminada\n\n\n",p->id);
            pthread_join(p->thread,NULL);
        }

        //pthread_join(p->thread,NULL);
    }*/



    //printf("Fora\n");

    pthread_exit(EXIT_SUCCESS);

}
