#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int chave;
} Objeto;

typedef struct NoFila *PtrNoFila;

typedef struct NoFila{
    Objeto obj;
    PtrNoFila proximo;
} NoFila;

typedef struct {
    PtrNoFila inicio;
    PtrNoFila fim;
    int tamanho;
} FilaDinamica;


void iniciaFila(FilaDinamica *fila){
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
}

int tamanhoFila(FilaDinamica *fila){
    return fila->tamanho;
}

void imprimeFila(FilaDinamica *fila){
    PtrNoFila aux=fila->inicio;
    while (aux != NULL){
        printf("%d",aux->obj.chave);
        aux = aux->proximo;
    }

}

int estaVazia(FilaDinamica *fila){
    return (fila->tamanho == 0);
}

void enfileira(Objeto x, FilaDinamica *fila){
    PtrNoFila aux;
    aux = (PtrNoFila)malloc(sizeof(NoFila));
    aux->obj=x;
    if (estaVazia(fila)){
        fila->inicio = fila->fim = aux;
        aux->proximo = NULL;
    } else{
        aux->proximo=NULL;
        fila->fim->proximo=aux;
        fila->fim=fila->fim->proximo;
    }
    fila->tamanho++;
}

Objeto desenfileira(FilaDinamica *fila){
    if (estaVazia(fila)){
        printf("Esta vazia! \n");
    }else{
        PtrNoFila aux;
        aux=fila->inicio;
        fila->inicio=fila->inicio->proximo;
        Objeto ret=aux->obj;
        fila->tamanho--;
        free(aux);
        return (ret);
    }
}

Objeto inicioFila(FilaDinamica *fila){
    return fila->inicio->obj;
}
Objeto fimFila(FilaDinamica *fila){
    return fila->fim->obj;
}

int main(){

    FilaDinamica minhafila;
    iniciaFila(&minhafila);

    Objeto ind;

    ind.chave = 1;

    enfileira(ind,&minhafila);

    ind.chave = 7;

    enfileira(ind,&minhafila);

    ind.chave = 9;

    enfileira(ind,&minhafila);

    imprimeFila(&minhafila);
    printf("%d",inicioFila(&minhafila).chave);

}
