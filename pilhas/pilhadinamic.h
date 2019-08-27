#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int chave;
} Objeto;

typedef struct NoPilha *PtrNoPilha;

typedef struct NoPilha{
    Objeto obj;
    PtrNoPilha proximo;
} NoPilha;

typedef struct {
    PtrNoPilha topo;
    int tamanho;
} PilhaDinamica;

void iniciaPilha(PilhaDinamica *p){
    p->topo = NULL;
    p->tamanho = 0;
};

bool estaVazia(PilhaDinamica *p){
    return (p->tamanho == 0);
};

void empilha(Objeto obj, PilhaDinamica *p){
    PtrNoPilha aux;
    aux = (PtrNoPilha)malloc(sizeof(PtrNoPilha));
    aux->obj=obj;
    aux->proximo=p->topo;
    p->topo=aux;
    p->tamanho=p->tamanho+1;
};

int main(){
    return 0;
}
