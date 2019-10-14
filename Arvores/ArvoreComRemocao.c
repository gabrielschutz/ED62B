#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    int chave;
} Objeto;

typedef struct NoArvore *PtrArvore;

typedef struct NoArvore {
    Objeto elemento;
    PtrArvore left;
    PtrArvore right;
} NoArvore;

int numeroNosArvore(PtrArvore *arvore){

    if((*arvore)==NULL)
        return 0;
    else
        return (numeroNosArvore(&(*arvore)->right)+numeroNosArvore(&(*arvore)->left)+1);

}

int alturaArvore(PtrArvore *arvore){
    int taml;
    int tamr;

    if((*arvore)==NULL){
        return -1;
    }

    else
    {
        taml = (alturaArvore(&(*arvore)->right)+1);
        tamr = (alturaArvore(&(*arvore)->left)+1);
        if (taml >= tamr){
            return taml;
        }else{
            return tamr;
        }
    }


}

void iniciaArvore(PtrArvore *arvore){
    *arvore = NULL;
}

bool estaVazia(PtrArvore *arvore){
    return (*arvore == NULL);
}

void destroiArvore(PtrArvore *arvore);

void preOrdem(PtrArvore *arvore){
    if ((*arvore)==NULL)
        return;
    printf("%d ",(*arvore)->elemento.chave);
    preOrdem(&(*arvore)->left);
    preOrdem(&(*arvore)->right);
}

void posOrdem(PtrArvore *arvore){
    if ((*arvore)==NULL)
        return;
    posOrdem(&(*arvore)->left);
    posOrdem(&(*arvore)->right);
    printf("%d ",(*arvore)->elemento.chave);
}

void EmOrdem(PtrArvore *arvore){
    if ((*arvore)==NULL)
        return;
    EmOrdem(&(*arvore)->left);
    printf("%d ",(*arvore)->elemento.chave);
    EmOrdem(&(*arvore)->right);
}

bool insereItem(PtrArvore *arvore, Objeto x){

    if(estaVazia(arvore)){
        (*arvore) = malloc(sizeof(NoArvore));
        (*arvore)->right = (*arvore)->left = NULL;
        (*arvore)->elemento = x;
        return true;
    }

    if((*arvore)->elemento.chave == x.chave)
        return false;


    if((*arvore)->elemento.chave > x.chave){
        return (insereItem(&(*arvore)->left, x));
    }else{
        return (insereItem(&(*arvore)->right, x));
    }


}
bool procuraItem(PtrArvore *arvore, int key){
    if((*arvore)==NULL)
        return false;

    if((*arvore)->elemento.chave == key)
        return true;

    if(key < (*arvore)->elemento.chave)
        procuraItem(&(*arvore)->left,key);
    else
        procuraItem(&(*arvore)->right,key);

}

PtrArvore getMaxAux(PtrArvore *arvore){
    PtrArvore ret;
    if((*arvore)->right == NULL){
        ret = (*arvore);
        (*arvore) = (*arvore)->left;
        return (ret);
    }
    return (getMaxAux(&(*arvore)->right));
}

PtrArvore getMinAux(PtrArvore *arvore){
    PtrArvore ret;
    if((*arvore)->left == NULL){
        ret = (*arvore);
        (*arvore) = (*arvore)->right;
        return (ret);
    }
    return(getMaxAux(&(*arvore)->left));
}

bool removeItem(PtrArvore *arvore, int key) {

    if ((*arvore) == NULL) {
        printf("Nao existe elemento para ser removido!");
        return false;
        
    }else if ((*arvore)->elemento.chave == key) {
        PtrArvore aux;
        aux = (*arvore);
        if (((*arvore)->left == NULL) && ((*arvore)->right == NULL))
            (*arvore) = NULL;
        else if ((*arvore)->left == NULL)
            (*arvore) = (*arvore)->right;
        else if ((*arvore)->right == NULL)
            (*arvore) = (*arvore)->left;
        else {
            aux = getMinAux(&(*arvore)->right);
            (*arvore)->elemento = aux->elemento;
        }
        free(aux);
        return true;
    }

    if ((*arvore)->elemento.chave > key)
        return removeItem(&(*arvore)->left, key);
    else
        return removeItem(&(*arvore)->right, key);

}


PtrArvore maximo(PtrArvore *arvore);


PtrArvore maximoIterativo(PtrArvore *arvore);


PtrArvore minimo(PtrArvore *arvore);


PtrArvore minimoIterativo(PtrArvore *arvore);








int main() {

    PtrArvore raiz;
    iniciaArvore(&raiz);

    Objeto x;

    x.chave = 1;
    insereItem(&raiz,x);
    x.chave = 66;
    insereItem(&raiz,x);
    x.chave = 77;
    insereItem(&raiz,x);
    x.chave = 99;
    insereItem(&raiz,x);
    x.chave = 12;
    insereItem(&raiz,x);


    printf("Pré Ordem: \n");
    preOrdem(&raiz);
    printf("\n");
    printf("Pós Ordem: \n");
    posOrdem(&raiz);
    printf("\n");
    printf("Em Ordem: \n");
    EmOrdem(&raiz);

    printf("\n");

    removeItem(&raiz,7);

    printf("Pré Ordem: \n");
    preOrdem(&raiz);




    printf("\n");



    return 0;
}
