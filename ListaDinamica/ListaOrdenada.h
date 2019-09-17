#ifndef UNTITLED_LISTAORDENA_H
#define UNTITLED_LISTAORDENA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct  {
    int chave;
} Objeto;

typedef struct NoLista *PtrNoLista;

typedef struct NoLista {
    Objeto item;
    PtrNoLista proximo;
    PtrNoLista anterior;
} NoLista;

typedef struct {
    PtrNoLista inicio;
    int tamanho;
} Lista;


void iniciaLista(Lista *list){
    list->inicio = NULL;
    list->tamanho = 0;
}

void imprimirLista(Lista *list);
void destruirLista(Lista *list);

int estaVazia(Lista *list){
    return (list->tamanho==0);
}

void inserir(Lista *list, Objeto x){
    PtrNoLista novo;
    novo = (PtrNoLista)malloc(sizeof(NoLista));
    novo->item = x;

    if ((estaVazia(list)==1) || (x.chave < list->inicio->item.chave)){
        novo->proximo = list->inicio;
        list->inicio = novo;
    }else{
        PtrNoLista aux;
        aux = list->inicio;

        while (aux->proximo != NULL && x.chave > aux->proximo->item.chave){
            aux = aux->proximo;
        }

        novo->proximo = aux->proximo;
        aux->proximo = novo;
    }
    list->tamanho++;
}

bool pesquisar(Lista *list, int key){
    if(estaVazia(list))
        return false;
    PtrNoLista aux=list->inicio;
    while (aux!=NULL && key> aux->item.chave ){
        aux = aux->proximo;
    }
    if (aux==NULL||aux->item.chave > key)
        return false;
    return true;

}

int tamanhoLista(Lista *list){
    return list->tamanho;
}
void removeElemento(Lista *list, int chave, Objeto *item);
void removePrimeiro(Lista *list, Objeto *item);
void removeUltimo(Lista *list, Objeto *item);
Objeto primeiro(Lista *list);
Objeto ultimo(Lista *list);

#endif //UNTITLED_LISTAORDENA_H
