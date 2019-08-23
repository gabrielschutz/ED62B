#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXTAM 10

typedef struct {
    int chave;
} Objeto;

typedef struct {
    Objeto array[MAXTAM];
    int topo;
} pilhaEstatica;


void iniciaPilha(pilhaEstatica *pilha){
    pilha->topo =0;
}

bool estaVazia(pilhaEstatica *pilha) {
    if(pilha->topo == 0){
        return true;
    }else{
        return false;
    }
}

bool estaCheia(pilhaEstatica *pilha) {
    if(pilha->topo == MAXTAM){
        return true;
    }else{
        return false;
    }
}

void empilha(Objeto item, pilhaEstatica *pilha) {
    pilha->array[pilha->topo] = item;
    pilha->topo += 1;
}

void desempilha(Objeto *item, pilhaEstatica *pilha) {
    *item = pilha->array[pilha->topo-1];
    pilha->topo = pilha->topo - 1;
}

int tamanhoPilha(int *topo,pilhaEstatica *pilha) {
    *topo = pilha->topo;
}

Objeto topo(pilhaEstatica *pilha) {
    // adicione seu codigo aqui
}

void imprimePilha(pilhaEstatica *pilha) {
    // adicione seu codigo aqui
}

int main(){
    return 0;
}
