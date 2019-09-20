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

void imprimirLista(Lista *list){
    PtrNoLista aux;
    aux = list->inicio;
    while (aux->proximo!=NULL){
        printf("%i ",aux->item.chave);
        aux = aux->proximo;
    }
    printf("%i",aux->item.chave);
}
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

int removeElemento(Lista *list, Objeto item){
    PtrNoLista aux = list->inicio;
    PtrNoLista remove;
    int item1;
    if (estaVazia(list)||item.chave < list->inicio->item.chave){
        printf("Nao foi possivel remover: \n");
    }else{
        if(item.chave == list->inicio->item.chave){
            item1 = list->inicio->item.chave;
            remove = list->inicio;
            list->inicio = list->inicio->proximo;
            list->tamanho--;
            free(remove);
            return item1;
        }
        while ((aux->proximo != NULL)&&(item.chave > aux->proximo->item.chave)){
            aux = aux->proximo;
        }
        if(aux->proximo == NULL || item.chave < aux->proximo->item.chave){
            printf("Nao existe esse elemento na sua lista! \n");
        }else {
            remove = aux->proximo;
            item1 = aux->proximo->item.chave;
            aux->proximo = aux->proximo->proximo;
            free(remove);
            list->tamanho--;
            return item1;
        }
    }
}


void removePrimeiro(Lista *list, Objeto *item);
void removeUltimo(Lista *list, Objeto *item);
Objeto primeiro(Lista *list);
Objeto ultimo(Lista *list);

int main(){
    Lista test;
    iniciaLista(&test);
    Objeto x;
    int t1=0;

    x.chave = 3;
    inserir(&test,x);
    x.chave = 2;
    inserir(&test,x);
    x.chave = 1;
    inserir(&test,x);
    imprimirLista(&test);
    x.chave = 3;

    printf("\n");

    removeElemento(&test,x);
    imprimirLista(&test);

}
