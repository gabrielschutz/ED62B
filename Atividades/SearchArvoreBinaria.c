#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct{                                                                                                         //DEFINICAO DA DATA DA ARVORES
    int chave;
    int paginas[100];
    char *palavra;
} Objeto;

typedef struct NoArvore *PtrArvore;

typedef struct NoArvore {                                                                                               //PONTEIROS DA ARVORES
    Objeto elemento;
    PtrArvore left;
    PtrArvore right;
} NoArvore;

void iniciaArvore(PtrArvore *arvore){                                                                                   //INICIA A ARVORE
    *arvore = NULL;
}

bool estaVazia(PtrArvore *arvore){                                                                                      //VERIFICA SE ESTA VAZIA OU NAO
    return (*arvore == NULL);
}

void destroiArvore(PtrArvore *arvore){                                                                                  //DESTROI A ARVORE

    if(estaVazia(arvore)==true){
        destroiArvore(&(*arvore)->left);
        destroiArvore(&(*arvore)->right);
        free(*arvore);
    }
    arvore = NULL;
}


bool insereItem(PtrArvore *arvore, Objeto x){                                                                           //INSERI ELEMENTOS NA ARVORE

    if(estaVazia(arvore)){
        (*arvore) = malloc(sizeof(NoArvore));
        (*arvore)->right = (*arvore)->left = NULL;
        (*arvore)->elemento = x;
        return true;
    }

    if(strcmp ((*arvore)->elemento.palavra, x.palavra) == 0)
        return false;


    if(strlen((*arvore)->elemento.palavra)  > strlen(x.palavra)){                                                       //METODO DE INSERCAO E ATRAVES DO TAMANHO DA PALAVRA
        return (insereItem(&(*arvore)->left, x));
    }else{
        return (insereItem(&(*arvore)->right, x));
    }


}

void comparador(PtrArvore *arvore,char teste[50],int pag,FILE *arq){                                                    //FUNCAO PARA COMPARAR STRINGS

    if ((*arvore)==NULL)                                                                                                //CASO BASE
        return;

    comparador((&(*arvore)->left), teste,pag,arq);                                                                      //RECURSAO PARA ESQUERDA DA ARVORE
    comparador((&(*arvore)->right), teste,pag,arq);                                                                     //RECURSAO PARA DIREITA DA ARVORE


    if(strcmp((*arvore)->elemento.palavra,teste)==0){                                                                   //SE A PALAVRA DA ATUAL NODE DE ARVORE FOR IGUAL A PALAVRA RETIRADA DO TEXTO
        for (int j = 0; j <100 ; ++j) {                                                                                 //PERCORREDOR DO VETOR DE PAGINAS DO ELEMENTO PAGINAS
            if ((*arvore)->elemento.paginas[j] == pag) {                                                                //CASO PARA VER SE JA NAO EXISTE ESSA PAGINA (IMPRIMIR PAGINAS VARIAS VEZES)
                break;                                                                                                  //SAI DO CICLO
            }
            if ((*arvore)->elemento.paginas[j] == -1) {                                                                 //CASO ESSA CASA ESTEJA DISPONIVEL!
                (*arvore)->elemento.paginas[j] = pag;                                                                   //ARMAZENA
                break;                                                                                                  //SAI DO CICLO
            }
        }
    }

}

void imprimirArq(PtrArvore *arvore,FILE *arq){                                                                          //IMPRESSOR DO ARQUIVO 2

    if ((*arvore)==NULL)                                                                                                //CASO BASE
        return;


    fprintf(arq,"%s",(*arvore)->elemento.palavra);                                                                      //IMPRIME A PALAVRA DO NO ATUAL

    for (int i = 0; i <100 ; ++i) {
        if ((*arvore)->elemento.paginas[i]==-1){                                                                        //PARA NAO IMPRIMIR CASAS VAZIAS
        }else{
            fprintf(arq,",%i",(*arvore)->elemento.paginas[i]);
        }
    }
    fprintf(arq,"\n");

    
    imprimirArq((&(*arvore)->right),arq);                                                                               //RECURSAO PARA DIREITA
	imprimirArq((&(*arvore)->left),arq);                                                                                //RECURSAO PARA ESQUERDA
	
}

int main(int argc, char *argv[]) {

    FILE *arq1;                                                                                                         //VARIAVEL ARQ 1 ENTRADA
    FILE *arq2;                                                                                                         //VARIAVEL ARQ 2 SAIDA

    arq1 = fopen (argv[1], "r");                                                                                        //PARAMETROS
    arq2 = fopen (argv[2], "w+");
    

    PtrArvore arvorebusca;                                                                                              //CRIA ARVORE

    Objeto x1;                                                                                                          //CRIA O OBJETO

    iniciaArvore(&arvorebusca);                                                                                         //INICIA A ARVORE

    char buscar[10001], texto[1001], *PtrDePalavras, *PtrDePalavras2;                                                   //VARIAVEIS
    int pagina=0;

    if ((arq1 == NULL) || (arq2 == NULL))                                                                               //ANTI ERRO DE ARQUIVOS
        printf ("Erro ao abrir arquivos!\n");
    else {
        fgets (buscar, sizeof(buscar), arq1);                                                                           //PEGA 1 LINHA DO ARQUIVO E COLOCA NA STRING BUSCA
        buscar[strcspn (buscar, ">")] = '\0';                                                                           //SUBSTITUI O > POR CARACTER NULO(PARA O PONTEIRO NAO PEGAR)

        printf("Palavras a serem buscadas no texto:{");

        PtrDePalavras = strtok (buscar, ":");                                                                           //FUNCAO DE QUEBRA DE STRING


        while (PtrDePalavras != NULL) {
            PtrDePalavras = strtok (NULL, ",");                                                                         //CRITERIO DE SEPARACAO
            if (PtrDePalavras != NULL) {
                x1.palavra = PtrDePalavras;                                                                             //OBJETO RECEBE A PALAVRA ATUAL QUE O PTR ESTA APONTANDO
                for (int i = 0; i <100 ; ++i) {
                    x1.paginas[i] = -1;                                                                                 //COLOCA TODO O VETOR DE PAGINAS PARA -1
                }
                insereItem(&arvorebusca,x1);
                printf(" %s,",PtrDePalavras);

            }
        }

        printf("}.\n");


        printf("\nTEXTO: {\n");

        while (!feof (arq1)) {                                                                                          //WHILE PARA PERCORRER TODO ARQUIVO
            fgets (texto, sizeof (texto), arq1);                                                                        //PEGA A LINHA ATUAL E COLOCA NA STRING TEXTO
            if ((texto[0] == '<') && (texto[1] == 'p') && (texto[2] == 'a') && (texto[3] == 'g') && (texto[4] == 'e')   //VERIFICA SE NAO E UM CABECALHO DE PAGINA
                && (texto[5] == ':')) {
                pagina ++;                                                                                              //CONTADOR PARA VERIFICAR A ATUAL PAGINA
            }else{
                PtrDePalavras2 = strtok(texto," ,.:\n");                                                                //FUNCAO DE QUEBRA DE STRING

                while( PtrDePalavras2 != NULL ) {
                    printf("%s ", PtrDePalavras2);                                                                      //PRINTA NO TERMINAL A PALAVRA ATUAL
                    comparador(&arvorebusca,PtrDePalavras2,pagina,arq2);                                                //CHAMA A FUNCAO PARA COMPARAR A PALAVRA ATUAL COM TODAS AS PALAVRAS DA ARVORE
                    PtrDePalavras2 = strtok(NULL, " ,.:\n");                                                            //CRITEIRO DE SEPARACAO
                }
            }
        }

        printf("\n}");

        imprimirArq(&arvorebusca,arq2);                                                                                 //IMPRIME A ARVORE NO ARQUIVO

        destroiArvore(&arvorebusca);                                                                                    //DESTROI ARVORE
    }

    return 0;
}