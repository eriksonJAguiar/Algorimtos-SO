// semaforo
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct celula celula;
int tam = 0;

struct celula
{
    int conteudo;
    celula *prox;
};



void remove_celula(celula *p);
void insere_fim(celula *ini, int x);
void remove_inicio(celula *ini);
celula *nova(int x);
void down(int processo);
void up();
void regiaoCritica(int valor);
void * function(void *arg);



//int semaforo = 1;
//celula filaProcessos;

int x = 0;

int semaforo;
celula filaProcessos;


int main()
{

    semaforo = 1;
    filaProcessos.prox = NULL;

    pthread_t t1, t2;

    int id1 = 1;
    int id2 = 2;



    pthread_create(&t2, NULL,function, (void *)(&id2));


    sleep(5);

    pthread_create(&t1, NULL,function, (void *)(&id1));

    down(id2);

    up();

    pthread_join(t1,NULL);

}
void * function(void *arg){

  int *val = (int *)(arg);

  printf("Thread criada %d\n",*val);

    down(*val);

  if(*val == 1)
    regiaoCritica(10);
  else if(*val == 2)
    regiaoCritica(15);

    printf("%d\n",x);

}


void regiaoCritica(int valor)
{
    printf("Entrou na regiao Critica\n");
    x = valor;

}


void down(int processo)
{
    semaforo--;
    if(semaforo < 0)
    {
        insere_fim(&filaProcessos,processo);
        printf("Processo %d bloqueado\n",processo);
    }

}
void up()
{
    semaforo++;
    if(semaforo <= 0)
    {
        remove_inicio(&filaProcessos);
        printf("processo liberado\n");

    }
}
//fila de processos
celula *nova(int x)
{
    celula *p = malloc(sizeof(celula));
    if(p==NULL)
    {
        printf("ERRO: Memória insuficiente\n");
        exit(1);
    }
    p->conteudo=x;
    p->prox=NULL;
    return p;
}
void insere(int x, celula *p)
{
    celula *q = nova(x);
    q->prox=p->prox;
    p->prox=q;
    tam++;
}

void remove_celula(celula *p)
{
    celula *q = p->prox;
    p->prox = q->prox;
    free(q);
    tam--;
}

void insere_fim(celula *ini, int x)
{
    celula *u=ini->prox;
    if(u==NULL)
    {
        insere(x,ini);
        return;
    }
    while(u->prox !=NULL)
    {
        u=u->prox;
    }
    insere(x,u);
}
void remove_inicio(celula *ini)
{
    if(ini->prox!=NULL)
    {
        remove_celula(ini);
    }
}
