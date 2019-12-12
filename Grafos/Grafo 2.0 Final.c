#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Coloracao{Branco, Cinza, Preto};                                                                                   //Define a cor do vertice, usado para Bfs e Dfs

int MatrizGrafo[200][200];                                                                                              //Variavel global para a representacao da Matriz

typedef struct NoLista {                                                                                                //Lista para Adjacentes de um Vertice
    int chave;
    struct NoLista *proximodafila;
}NoLista;


typedef struct vertice {                                                                                                //Estrutura de um vertice
    int data;
    int d;
    int f;
    char nome[50];
    enum Coloracao cor;
    NoLista *comeco;
}vertice;

int tempo;                                                                                                              //Variavel global tempo usada para o DFS

typedef struct Grafo{                                                                                                   //Estrutura de um Grafo
    int NumeroDeVertices;
    vertice array[];
}Grafo;

vertice* NovoVertice(int data) {                                                                                        //Inicia novo vertice
    vertice *z;
    z = malloc(sizeof(vertice));
    z->data = data;
    z->d = 0;
    z->f = 0;
    strcpy((z->nome), "");
    z->comeco = NULL;
    z->cor = Branco;

    return z;
}

NoLista* AdjacentesDoVertice(int item_index) {                                                                          //Inicia lista dos adjacentes do vertice
    NoLista *z;
    z = malloc(sizeof(NoLista));
    z->chave = item_index;
    z->proximodafila = NULL;
    return z;
}


Grafo* Novo_Grafo(int NumeroDeVertices) {                                                                               //Cria novo grafo

    Grafo *g = malloc(sizeof(Grafo) + (NumeroDeVertices*sizeof(vertice)));
    g->NumeroDeVertices = NumeroDeVertices;


    int i;
    for(i=0; i<NumeroDeVertices; i++) {
        vertice *z = NovoVertice(-1);
        g->array[i] = *z;
    }

    return g;
}

void AdicionarVerticeNoGrafo(Grafo *g, int data) {                                                                      //Adiciona vertice no Grafo

    vertice *z = NovoVertice(data);

    int i;
    for(i=0; i<g->NumeroDeVertices; i++) {
        if (g->array[i].data < 0) {
            g->array[i] = *z;
            break;
        }
    }
}

int DefineValorDoVertice(Grafo *g, int data) {                                                                          //Define o nome ou valor do vertice, no caso usaremos um inteiro para representalo
    int i;
    for(i=0; i<g->NumeroDeVertices; i++) {
        if(g->array[i].data == data)
            return 1;
    }
    return 0;
}

void AdicionarAresta(Grafo *g, int source, int dest) {                                                                  //Adiciona uma aresta entre 2 vertices

    if(!DefineValorDoVertice(g, source)) {
        AdicionarVerticeNoGrafo(g, source);
    }
    if(!DefineValorDoVertice(g, dest)) {
        AdicionarVerticeNoGrafo(g, dest);
    }

    int i,j;

    for(i=0; i<g->NumeroDeVertices; i++) {
        if(g->array[i].data == source) {

            int ChaveDeDestino;

            for(j=0; j<g->NumeroDeVertices; j++) {
                if(g->array[j].data == dest) { \
                    ChaveDeDestino = j;
                    break;
                }
            }

            NoLista *n = AdjacentesDoVertice(ChaveDeDestino); \
            if (g->array[i].comeco == NULL) {
                g->array[i].comeco = n;
            }
            else {
                NoLista *temp;
                temp = g->array[i].comeco;


                while(temp->proximodafila != NULL) {
                    temp = temp->proximodafila;
                }
                temp->proximodafila = n;
            }
            break;
        }
    }
}


void PrintarGrafoLista(Grafo *g) {                                                                                      //Printa a lista de Adjacencia do Grafo
    int i;
    for(i=0; i<g->NumeroDeVertices; i++) {
        NoLista *temp;
        temp = g->array[i].comeco;
        printf("%d\t",g->array[i].data);
        while(temp != NULL) {
            printf("%d\t",g->array[temp->chave].data);
            temp = temp->proximodafila;
        }
        printf("\n");
    }
}

void printMatriz(Grafo *g) {                                                                                            //Printa a matriz do grafo
    for(int i=0; i<g->NumeroDeVertices; i++) {
        printf("\t%d",g->array[i].data);

    }

    printf("\n");

    for(int i = 0; i < g->NumeroDeVertices; i++) {
        printf("%d\t",g->array[i].data);
        for(int j = 0; j < g->NumeroDeVertices; j++) {
            printf("%d\t",MatrizGrafo[i][j]);
        }
        printf("\n");
    }
}

void AdicionaArestaNaMatriz(int u, int v) {                                                                             //Coloca 1 na matriz caso um vertice se conecta com outro
    MatrizGrafo[u-1][v-1] = 1;
}

typedef struct NoFila {                                                                                                 //Estrutura de um NoFila para o BFS
    vertice *n;
    struct NoFila *proximodafila;
}NoFila;

struct FILA{                                                                                                            //Estrutura de uma fila
    int tamanhoFila;
    NoFila *proximodafila;
    NoFila *anteriordafila;
};
typedef struct FILA FILA;

int FilaEstaVazia(FILA *q)                                                                                              //Funcao retorna se a fila esta vazia
{
    return !(q->tamanhoFila);
}

void enfilera(FILA *q, vertice *n)                                                                                      //Funcao Enfilera item
{
    NoFila *aux;
    aux = malloc(sizeof(NoFila));
    aux->n = n;
    aux->proximodafila = NULL;
    if(!FilaEstaVazia(q))
    {
        q->anteriordafila->proximodafila = aux;
        q->anteriordafila = aux;
    }
    else
    {
        q->proximodafila = q->anteriordafila = aux;
    }
    q->tamanhoFila++;
}

NoFila* densenfilera(FILA *q)                                                                                           //Funcao desenfilera
{
    NoFila *tmp;
    tmp = q->proximodafila;
    q->proximodafila = q->proximodafila->proximodafila;
    q->tamanhoFila--;
    return tmp;
}

FILA* inicia_fila()                                                                                                     //Funcao para inicar fila
{
    FILA *q;
    q = malloc(sizeof(FILA));
    q->tamanhoFila = 0;
    q->proximodafila = NULL;
    q->anteriordafila = NULL;
    return q;
}


void bfs(Grafo *g,int verticenicial,FILE *arq) {                                                                        //Funcao do BFS, usando um parametro do tipo FILE para ja imprimir direto no arquivo de saida

    vertice s = g->array[verticenicial - 1];
    int i;
    for(i=0; i<g->NumeroDeVertices; i++) {
        g->array[i].cor = Branco;
        g->array[i].d = 999;
    }

    s.cor = Cinza;
    s.d = 0;

    FILA* q = inicia_fila();
    enfilera(q, &s);

    while(!FilaEstaVazia(q)) {

        NoFila *u = densenfilera(q);
        NoLista *temp;
        temp = u->n->comeco;


        while(temp != NULL) {
            if (g->array[temp->chave].cor == Branco) {
                g->array[temp->chave].cor = Cinza;
                g->array[temp->chave].d = s.d + 1;
                enfilera(q, &g->array[temp->chave]);
            }
            temp = temp->proximodafila;
        }
        u->n->cor = Preto;
        fprintf(arq,"%d [d=%i]\n",u->n->data,u->n->d);
    }


    if (FilaEstaVazia(q)){
        for (int j = 0; j < (g->NumeroDeVertices-1); ++j) {
            if (g->array[j].d >=999){
                fprintf(arq,"%d [d=%i]\n",g->array[j].data,g->array[j].d);
            }
        }
    }

}

void dfs_visit(Grafo *g, vertice *i) {                                                                                  //Funcao auxiliar do DFS
    tempo = tempo + 1;
    i->cor = Cinza;
    i->d = tempo;

    NoLista *temp;
    temp = i->comeco;
    while(temp != NULL) {
        if (g->array[temp->chave].cor == Branco) {
            dfs_visit(g, &g->array[temp->chave]);
        }
        temp = temp->proximodafila;
    }
    i->cor = Preto;
    tempo = tempo+1;
    i->f = tempo;

   // printf("%d [d=%i,f=%i]\n",i->data,i->d,i->f);
}

void dfs(Grafo *g,FILE *arq) {                                                                                          //Funcao DFS, usa tambem um parametro do Tipo FILE para imprimir direto ao arquivo
    int i;

    for(i=0; i<g->NumeroDeVertices; i++) {
        g->array[i].cor = Branco;
    }

    tempo = 0;

    for(i=0; i<g->NumeroDeVertices; i++) {
        if (g->array[i].cor == Branco) {
            dfs_visit(g, &g->array[i]);
        }
    }

    for (int j = 0; j <g->NumeroDeVertices ; ++j) {
        fprintf(arq,"%d [d=%i,f=%i]\n",g->array[j].data,g->array[j].d,g->array[j].f);
    }
}

int main(int argc, char *argv[]) {                                                                                      //Main

    FILE *arq1 = fopen(argv[1], "r");                                                                                   //Abre os arquivos com r pra leitura e w+ para escrita
    FILE *arq2 = fopen(argv[2], "w+");

    char c;                                                                                                             //Var c para armazenar os primeiros caracters do nosso arquivo
    int num1 = 0, num2 = 0,maior = 0;                                                                                   //Var para armazenar nossas arestas e o nosso vertice que no caso sera para onde ira a maior aresta


    if (arq1 == NULL || arq2 == NULL)                                                                                   //Caso erro de arquivo
        printf("\nErro no Arquivo!!!\n");
    else {
        c = fgetc(arq1);                                                                                                //Pega primeiro caracter
        if (c == 'M') {                                                                                                 //Caso seja M de matriz
            fseek(arq1, 3, SEEK_SET);                                                                                   //Pula o \n do arquivo
            c = fgetc(arq1);                                                                                            //Pega 2 caracter
            if (c == 'B') {                                                                                             //Caso seja B de BFS
                fseek(arq1, 8, SEEK_SET);                                                                               //Seta o nosso ponteiro para ir direto para o 1 valor de uma aresta
                printf("Arestas: \n");
                while (c != '\n'){                                                                                      //Rodar ate que a linha de arestas acabe
                    if ((c != '(')&&(c != ',')&&(c != ')')){                                                            //Caso o C nao seja parenteses nem virgulas
                        fseek(arq1, -1, SEEK_CUR);                                                                      //Volta um valor do ponteiro para podermos pegar os dados da 1 aresta
                        fscanf(arq1,"%i",&num1);                                                                        //Escaneia o 1 numero
                        c=fgetc(arq1);                                                                                  //Le a virgula
                        fscanf(arq1,"%i",&num2);                                                                        //Escaneia o 2 Numero

                        if (maior<num1){                                                                                //Condicao para verificar se a variavel maior e maior que o num1 e armazenar, para obtermos o numero de Vertices total
                            maior=num1;
                        }
                        if (maior<num2){                                                                                //Condicao para verificar se a variavel maior e maior que o num2 e armazenar, para obtermos o numero de Vertices total
                            maior=num2;
                        }

                        printf("(%i,%i)\t",num1,num2);                                                                  //Printar as arestas encontradas
                    }
                    c = fgetc(arq1);
                }
                printf("\nMaior numero de um vertice foi %i, quantidade de vertices sera de %i.\n",maior,maior);        //Printa o numero de Vertices

                Grafo *g = Novo_Grafo(maior);                                                                           //Cria o grafo e ja inicializa ele

                fseek(arq1, 7, SEEK_SET);                                                                               //Volta o ponteiro novamente, agora para pegar as arestas
                c = fgetc(arq1);
                while (c != '\n'){
                    if ((c != '(')&&(c != ',')&&(c != ')')){
                        fseek(arq1, -1, SEEK_CUR);
                        fscanf(arq1,"%i",&num1);
                        c=fgetc(arq1);
                        fscanf(arq1,"%i",&num2);
                        AdicionarAresta(g, num1, num2);                                                                 //Adiciona uma aresta com os valores encontrados no arquivo
                        AdicionaArestaNaMatriz(num1,num2);                                                              //Adiciona essa aresta na Matriz global para impressao posteriormente
                    }
                    c = fgetc(arq1);
                }
                int vi=0;                                                                                               //Variavel para o Vertice Inicial

                fscanf(arq1,"%i",&vi);                                                                                  //Escaneia o vertice inicial para o BFS
                printf("Vertice Inicial %i\n",vi);

                printf("Representacao por matriz: \n");

                printMatriz(g);                                                                                         //Printa o grafo por matriz conforme pede o arquivo


                bfs(g,vi,arq2);                                                                                         //Chama a funcao BFS para imprimir no arquvo S2

            }
            if (c == 'D') {                                                                                             //Caso seja DFS que o usuario deseja, repetira todo o processo, porem agora nao teremos mais o vertice inicial
                fseek(arq1, 8, SEEK_SET);
                printf("Arestas: \n");
                while (c != '\n'){
                    if ((c != '(')&&(c != ',')&&(c != ')')){
                        fseek(arq1, -1, SEEK_CUR);
                        fscanf(arq1,"%i",&num1);
                        c=fgetc(arq1);
                        fscanf(arq1,"%i",&num2);

                        if (maior<num1){
                            maior=num1;
                        }
                        if (maior<num2){
                            maior=num2;
                        }

                        printf("(%i,%i)\t",num1,num2);
                    }
                    c = fgetc(arq1);
                }
                printf("\nMaior numero de um vertice foi %i, quantidade de vertices sera de %i.\n",maior,maior);


                Grafo *g = Novo_Grafo(maior);

                fseek(arq1, 7, SEEK_SET);
                c = fgetc(arq1);
                while (c != '\n'){
                    if ((c != '(')&&(c != ',')&&(c != ')')){
                        fseek(arq1, -1, SEEK_CUR);
                        fscanf(arq1,"%i",&num1);
                        c=fgetc(arq1);
                        fscanf(arq1,"%i",&num2);
                        AdicionarAresta(g, num1, num2);
                        AdicionaArestaNaMatriz(num1,num2);

                    }
                    c = fgetc(arq1);
                }

                printf("Representacao por matriz: \n");

                printMatriz(g);

                dfs(g,arq2);
            }

        }
        if (c == 'L') {                                                                                                 //Caso o usuario deseja a representacao por Lista, o programa continuara o mesmo, porem agora printara uma lista de adjacencia para representacao
            fseek(arq1, 3, SEEK_SET);
            c = fgetc(arq1);
            if (c == 'B') {
                fseek(arq1, 8, SEEK_SET);
                printf("Arestas: \n");
                while (c != '\n'){
                    if ((c != '(')&&(c != ',')&&(c != ')')){
                        fseek(arq1, -1, SEEK_CUR);
                        fscanf(arq1,"%i",&num1);
                        c=fgetc(arq1);
                        fscanf(arq1,"%i",&num2);

                        if (maior<num1){
                            maior=num1;
                        }
                        if (maior<num2){
                            maior=num2;
                        }

                        printf("(%i,%i)\t",num1,num2);
                    }
                    c = fgetc(arq1);
                }
                printf("\nMaior numero de um vertice foi %i, quantidade de vertices sera de %i.\n",maior,maior);

                Grafo *g = Novo_Grafo(maior);

                fseek(arq1, 7, SEEK_SET);
                c = fgetc(arq1);
                while (c != '\n'){
                    if ((c != '(')&&(c != ',')&&(c != ')')){
                        fseek(arq1, -1, SEEK_CUR);
                        fscanf(arq1,"%i",&num1);
                        c=fgetc(arq1);
                        fscanf(arq1,"%i",&num2);
                        AdicionarAresta(g, num1, num2);
                    }
                    c = fgetc(arq1);
                }
                int vi=0;

                fscanf(arq1,"%i",&vi);
                printf("Vertice Inicial %i\n",vi);

                printf("Representacao por Lista: \n");
                PrintarGrafoLista(g);

                bfs(g,vi,arq2);

            }
            if (c == 'D') {
                fseek(arq1, 8, SEEK_SET);
                printf("Arestas: \n");
                while (c != '\n'){
                    if ((c != '(')&&(c != ',')&&(c != ')')){
                        fseek(arq1, -1, SEEK_CUR);
                        fscanf(arq1,"%i",&num1);
                        c=fgetc(arq1);
                        fscanf(arq1,"%i",&num2);

                        if (maior<num1){
                            maior=num1;
                        }
                        if (maior<num2){
                            maior=num2;
                        }

                        printf("(%i,%i)\t",num1,num2);
                    }
                    c = fgetc(arq1);
                }
                printf("\nMaior numero de um vertice foi %i, quantidade de vertices sera de %i.\n",maior,maior);

                Grafo *g = Novo_Grafo(maior);

                fseek(arq1, 7, SEEK_SET);
                c = fgetc(arq1);
                while (c != '\n'){
                    if ((c != '(')&&(c != ',')&&(c != ')')){
                        fseek(arq1, -1, SEEK_CUR);
                        fscanf(arq1,"%i",&num1);
                        c=fgetc(arq1);
                        fscanf(arq1,"%i",&num2);
                        AdicionarAresta(g, num1, num2);
                    }
                    c = fgetc(arq1);
                }

                printf("Representacao por Lista: \n");
                PrintarGrafoLista(g);
                dfs(g,arq2);
            }

        }
    }

    fclose(arq1);                                                                                                       //Fecha os arquivos
    fclose(arq2);

    return 0;                                                                                                           //Fim de programa, retorna 0
}
