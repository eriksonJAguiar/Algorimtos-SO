// semaforo
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
void up(int pid);
void regiaoCritica(int valor,int pid);


//int semaforo = 1;
//celula filaProcessos;

int x = 0;

int semaforo;
celula filaProcessos;

int main()
{

    semaforo = 1;
    filaProcessos.prox = NULL;

//Processo A
    printf("Ola eu sou o processo %d\n",getpid());
    down(getpid());
    regiaoCritica(10,getpid());
//up(getpid());

//processo B
    int processo = fork();
    if(processo == 0)
    {
        printf("processo %d criado\n",getpid());
        down(getpid());
    }

    up(getpid()); //libera a entrada de outro processo

      if(processo == 0)
      regiaoCritica(15,getpid());

    printf("%d\n",x);


}
void regiaoCritica(int valor,int pid)
{
    printf("%d Entrou na regiao Critica\n",pid);
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
void up(int pid)
{
    semaforo++;
    if(semaforo <= 0)
    {
        remove_inicio(&filaProcessos);
        printf("processo %d liberado\n",pid);

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
