#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define COUNT 10                //Para Printar

typedef struct{
    int chave;
} Objeto;

typedef struct NoArvoreAvl *PtrArvoreAvl;

typedef struct NoArvoreAvl {
    Objeto elemento;
    PtrArvoreAvl left;
    PtrArvoreAvl right;
    int altura;
} NoArvoreAvl;

int numeroNosArvore(PtrArvoreAvl *arvore){

    if((*arvore)==NULL)
        return 0;
    else
        return (numeroNosArvore(&(*arvore)->right)+numeroNosArvore(&(*arvore)->left)+1);

}

int alturaArvore(PtrArvoreAvl *arvore){
    int taml;
    int tamr;

    if((*arvore)==NULL){
        return 0;
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

void iniciaArvore(PtrArvoreAvl *arvore){
    *arvore = NULL;
}

bool estaVazia(PtrArvoreAvl *arvore){
    return (*arvore == NULL);
}

void destroiArvore(PtrArvoreAvl *arvore);

void preOrdem(PtrArvoreAvl *arvore){
    if ((*arvore)==NULL)
        return;
    printf("%d ",(*arvore)->elemento.chave);
    preOrdem(&(*arvore)->left);
    preOrdem(&(*arvore)->right);
}

void PrintArvoreRec(PtrArvoreAvl *arvore, int space){
    if ((*arvore) == NULL)
        return;

    int hd = alturaArvore(&(*arvore)->right);
    int he = alturaArvore(&(*arvore)->left);
    int fator = hd - he;

    space += COUNT;

    PrintArvoreRec(&(*arvore)->right, space);


    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d(V = %i)\n", (*arvore)->elemento.chave,fator);

    PrintArvoreRec(&(*arvore)->left, space);

}


void posOrdem(PtrArvoreAvl *arvore){
    if ((*arvore)==NULL) {
        printf("\n");
        return;
    }

    int hd = alturaArvore(&(*arvore)->right);
    int he = alturaArvore(&(*arvore)->left);
    int fator = hd - he;

    posOrdem(&(*arvore)->left);
    posOrdem(&(*arvore)->right);
    printf("%d(V = %i)", (*arvore)->elemento.chave,fator);

}

void EmOrdem(PtrArvoreAvl *arvore){
    if ((*arvore)==NULL)
        return;
    EmOrdem(&(*arvore)->left);
    printf("%d ",(*arvore)->elemento.chave);
    EmOrdem(&(*arvore)->right);
}

int atualizaAlturaArvoreAVL(PtrArvoreAvl esquerda, PtrArvoreAvl direita){
    int ae,ad;
    ae = alturaArvore(&(esquerda));
    ad = alturaArvore(&(direita));

    if (ae > ad)
        return (ae +1);
    else
        return (ad + 1);

}

void rotacaoSimplesEsquerda(PtrArvoreAvl *node){
    PtrArvoreAvl u;
    u = (*node)->right;
    (*node)->right=u->left;
    u->left = (*node);
    (*node)=u;
}

void rotacaoSimplesDireita(PtrArvoreAvl *node){
    PtrArvoreAvl u;
    u = (*node)->left;
    (*node)->left = u->right;
    u->right = (*node);
    (*node)=u;
}

void rotacaoDuplaEsquerda(PtrArvoreAvl *node){
    PtrArvoreAvl u,v;
    u = (*node)->right;
    v = u->left;
    (*node)->right = v->left;
    u->left = v->right;
    v->right = u;
    v->left = (*node);
    (*node) = v;
}

void rotacaoDuplaDireita(PtrArvoreAvl *node){
    PtrArvoreAvl u,v;
    u = (*node)->left;
    v = u->right;
    (*node)->left = v->right;
    u->right = v->left;
    v->right = (*node);
    v->left = u;
    (*node) = v;
}



void rotacoes(PtrArvoreAvl *arvore){
    int hd = alturaArvore(&(*arvore)->right);
    int he = alturaArvore(&(*arvore)->left);

    if (he>hd){

        PtrArvoreAvl x = (*arvore)->left;

        if(alturaArvore(&(x->left))>= alturaArvore(&(x->right))){
            printf("Rotacao Simples para a direita:");
            printf("%i\n",((*arvore)->elemento.chave));
            rotacaoSimplesDireita(&(*arvore));
        }else{
            printf("Rotacao Dupla para direita:");
            printf("%i\n",((*arvore)->elemento.chave));
            rotacaoDuplaDireita(&(*arvore));
        }

    }else{

        PtrArvoreAvl y = (*arvore)->right;

        if(alturaArvore(&(y->right))>alturaArvore(&(y->left))){
            printf("Rotacao Simples para a esquerda:");
            printf("%i\n",((*arvore)->elemento.chave));
            rotacaoSimplesEsquerda(&(*arvore));

        }else{
            printf("Rotacao Dupla para esquerda:");
            printf("%i\n",((*arvore)->elemento.chave));
            rotacaoDuplaEsquerda(&(*arvore));
        }

    }
}



bool insereItem(PtrArvoreAvl *arvore, Objeto x){
    int ae,ad,v;

    bool aux;

    if(estaVazia(arvore)){
        (*arvore) = malloc(sizeof(NoArvoreAvl));
        (*arvore)->right = (*arvore)->left = NULL;
        (*arvore)->elemento = x;
        (*arvore)->altura = 1;
        return true;
    }

    if((*arvore)->elemento.chave == x.chave)
        return false;

    if((*arvore)->elemento.chave > x.chave){
        aux = (insereItem(&(*arvore)->left, x));
    }else{
        aux = (insereItem(&(*arvore)->right, x));
    }

    if (!aux)
        return (false);

    ae = alturaArvore(&(*arvore)->left);
    ad = alturaArvore(&(*arvore)->right);
    v = ad - ae;

    if ((v==-2)||(v==+2))
        rotacoes(&(*arvore));

    (*arvore)->altura = atualizaAlturaArvoreAVL((*arvore)->left,(*arvore)->right);
    return true;


}
bool procuraItem(PtrArvoreAvl *arvore, int key){
    if((*arvore)==NULL)
        return false;

    if((*arvore)->elemento.chave == key)
        return true;

    if(key < (*arvore)->elemento.chave)
        procuraItem(&(*arvore)->left,key);
    else
        procuraItem(&(*arvore)->right,key);

}

PtrArvoreAvl getMaxAux(PtrArvoreAvl *arvore){
    PtrArvoreAvl ret;
    if((*arvore)->right == NULL){
        ret = (*arvore);
        (*arvore) = (*arvore)->left;
        return (ret);
    }
    return (getMaxAux(&(*arvore)->right));
}

PtrArvoreAvl getMinAux(PtrArvoreAvl *arvore){
    PtrArvoreAvl ret;
    if((*arvore)->left == NULL){
        ret = (*arvore);
        (*arvore) = (*arvore)->right;
        return (ret);
    }
    return(getMaxAux(&(*arvore)->left));
}

bool removeItem(PtrArvoreAvl *arvore, int key) {

    int ae,ad,v;

    bool Rot;

    if ((*arvore) == NULL) {
        printf("Nao existe elemento para ser removido!\n");
        return false;

    }else if ((*arvore)->elemento.chave == key) {
        PtrArvoreAvl aux;
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
        Rot = removeItem(&(*arvore)->left, key);
    else
        Rot = removeItem(&(*arvore)->right, key);


    if (Rot == false)
        return (false);


    ae = alturaArvore(&(*arvore)->left);
    ad = alturaArvore(&(*arvore)->right);
    v = ad - ae;

    if ((v==-2)||(v==+2))
        rotacoes(&(*arvore));

    (*arvore)->altura = atualizaAlturaArvoreAVL((*arvore)->left,(*arvore)->right);
    return true;

}


void maximo(PtrArvoreAvl *arvore) {
    if(((*arvore)->right) == NULL){
        printf("%d ", (*arvore)->elemento.chave);
        return;
    }

    maximo(&(*arvore)->right);

}


PtrArvoreAvl maximoIterativo(PtrArvoreAvl *arvore);


void minimo(PtrArvoreAvl *arvore){

    if(((*arvore)->left) == NULL){
        printf("%d ", (*arvore)->elemento.chave);
        return;
    }

    minimo(&(*arvore)->left);

}


PtrArvoreAvl minimoIterativo(PtrArvoreAvl *arvore);


int main() {

    PtrArvoreAvl raiz;
    iniciaArvore(&raiz);

    Objeto x;

    x.chave = 13;
    insereItem(&raiz,x);
    x.chave = 10;
    insereItem(&raiz,x);
    x.chave = 15;
    insereItem(&raiz,x);
    x.chave = 5;
    insereItem(&raiz,x);
    x.chave = 11;
    insereItem(&raiz,x);
    x.chave = 14;
    insereItem(&raiz,x);
    x.chave = 16;
    insereItem(&raiz,x);
    x.chave = 4;
    insereItem(&raiz,x);
    x.chave = 6;
    insereItem(&raiz,x);


    posOrdem(&raiz);

    removeItem(&raiz,14);


    removeItem(&raiz,13);


    removeItem(&raiz,6);


    removeItem(&raiz,4);


    removeItem(&raiz,10);


    printf("=================================\n");

    posOrdem(&raiz);




    return 0;
}
