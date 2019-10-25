void rotacaoSimplesEsquerda(PointeiroArvoreAVL *node){
    PointeiroArvoreAVL u;
    u = (*node)->direita;
    (*node)->direita=u->esquerda;
    u->esquerda = (*node);
    (*node)=u;
}

void rotacaoSimplesDireita(PointeiroArvoreAVL *node){
    PointeiroArvoreAVL u;
    u = (*node)->esquerda;
    (*node)->esquerda = u->direita;
    u->direita = (*node);
    (*node)=u;
}

void rotacaoDuplaEsquerda(PointeiroArvoreAVL *node){
    PointeiroArvoreAVL u,v;
    u = (*node)->direita;
    v = u->esquerda;
    (*node)->direita = v->esquerda;
    u->esquerda = v->direita;
    v->direita = u;
    v->esquerda = (*node);
    (*node) = v;
}

void rotacaoDuplaDireita(PointeiroArvoreAVL *node){
    PointeiroArvoreAVL u,v;
    u = (*node)->esquerda;
    v = u->direita;
    (*node)->esquerda = v->direita;
    u->direita = v->esquerda;
    v->direita = (*node);
    v->esquerda = u;
    (*node) = v;
}
