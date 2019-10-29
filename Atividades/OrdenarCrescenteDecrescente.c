#include <stdio.h>                                                                                                      //BIBLIOTECAS NECESSARIAS!.
#include <stdlib.h>
#include <stdbool.h>

typedef struct  {                                                                                                       //ESTRUTURA DO TIPO OBJETO.
    int chave;                                                                                                          //TIPOS DE DADOS DA ESTRUTRA, UTILIZAREMOS SOMENTE A CHAVE PARA VERIFICACAO DE INSERCAO.
} Objeto;

typedef struct NoLista *PtrNoLista;                                                                                     //DFINE UM PONTEIRO DO TIPO NOLISTA PARA FACILITAR A IMPLEMENTACAO.

typedef struct NoLista {                                                                                                //ESTRUTURA DE UM NO DE LISTA.
    Objeto item;                                                                                                        //QUE TIPO DE DADOS A LISTA SERA COMPOSTA, NO NOSSO CASO DO E UM OBJETO QUE POSSUI SOMENTE UM CHAVE!.
    PtrNoLista proximo;                                                                                                 //PONTEIRO PARA O PROXIMO.
    PtrNoLista anterior;                                                                                                //PONTEIRO PARA O ANTERIOR.
} NoLista;

typedef struct {                                                                                                        //ESTRUTURA DE UMA LISTA.
    PtrNoLista inicio;                                                                                                  //TERA UM INICIO.
    PtrNoLista fim;                                                                                                     //TERA UM FIM.
    int tamanho;                                                                                                        //TERA UM TAMANHO.
} Lista;


void iniciaLista(Lista *list){                                                                                          //INICIA A LISTA PARA NAO HAVER LIXOS DE MEMORIA!.
    list->inicio = NULL;                                                                                                //O INICIO RECEBE NULL.
    list->fim = NULL;                                                                                                   //O FIM RECEBE NULL.
    list->tamanho = 0;                                                                                                  //TAMANHO RECEBE NULL.
}

void imprimirListaComeco(Lista *list){                                                                                  //IMPRIME NO TERMINAL UMA LISTA A PARTIR DO INICIO!.
    PtrNoLista aux;                                                                                                     //CRIA UMA VARIAVEL AUX PARA PERCORRER A LISTA.
    aux = list->inicio;                                                                                                 //ELA COMECA DO INICIO.
    printf("Lista = {");                                                                                                //INDENTACAO!.
    while (aux->proximo!=NULL){                                                                                         //PERCORRER ATE QUE O PROXIMO DELA NAO EXISTA, OU SEJA NAO HA MAIS ELEMENTOS PELA FRENTE.
        printf("%i,",aux->item.chave);                                                                                  //IMPRIME O ELEMENTO ATUAL.
        aux = aux->proximo;                                                                                             //FAZ ELA IR PARA O PROXIMO ELEMENTO.
    }
    printf("%i",aux->item.chave);                                                                                       //PRINT PARA IMPRIMIR O ULTIMO ELEMENTO POIS ELE NAO ENTRA NO LOOP.
    printf("}\n");                                                                                                      //INDENTACAO!.
}

void imprimirCresc(Lista *list,FILE *x,int n){                                                                          //IMPRIME NUM ARQUIVO UMA LISTA EM ORDEM CRESCENTE, COM O TAMANHO DELA INCLUSO!.
    PtrNoLista aux;                                                                                                     //CRIA UMA VARIAVEL AUX PARA PERCORRER A LISTA.
    aux = list->inicio;                                                                                                 //ELA COMECA DO INICIO.
    fprintf(x,"Tamanho = %i\n",n);                                                                                      //INICIALMENTE IMPRIME O TAMANHO DA LISTA NO ARQUIVO, PASSADA POR PARAMETRO PELA FUNCAO.
    fprintf(x,"Lista = {");                                                                                             //INDENTACAO.
    while (aux->proximo!=NULL){                                                                                         //FAZ NOSSO PONTEIRO PERCORRER A LISTA ATE QUE NAO EXISTA ELEMENTOS NA FRENTE.
        fprintf(x,"%i",aux->item.chave);                                                                                //IMPRIME A CHAVE ATUAL NO ARQUIVO.
        fprintf(x,",");                                                                                                 //IMPRIME UMA VIRGULA PARA DIFERENCIAR OS ELEMENTOS.
        aux = aux->proximo;                                                                                             //ATUALIZA A VARIAVEL AUX(ELA VAI PARA O PROXIMO ELEMENTO).
    }
    fprintf(x,"%i",aux->item.chave);                                                                                    //PRINTA O ULTIMO ELEMENTO POIS ELE NAO ENTRA NO LOOP.
    fprintf(x,"}");                                                                                                     //PRINTA A IDENTACAO.
}

void imprimirListaFim(Lista *list){                                                                                     //IMPRIME NO TERMINAL UMA LISTA A PARTIR DO FIM!.
    PtrNoLista aux;                                                                                                     //CRIA UMA VARIAVEL AUX PARA PERCORRER A LISTA.
    aux = list->fim;                                                                                                    //ELA COMECA DO FIM.
    printf("Lista = {");                                                                                                //INDENTACAO!.
    while (aux->anterior!=NULL){                                                                                        //PERCORRER ATE QUE O ANTERIOR DELA NAO EXISTA, OU SEJA NAO HA MAIS ELEMENTOS ANTES.
        printf("%i,",aux->item.chave);                                                                                  //IMPRIME O ELEMENTO ATUAL.
        aux = aux->anterior;                                                                                            //FAZ ELA IR PARA O ELEMENTO ANTERIRO.
    }
    printf("%i",aux->item.chave);                                                                                       //PRINT PARA IMPRIMIR O ULTIMO ELEMENTO POIS ELE NAO ENTRA NO LOOP.
    printf("}\n");                                                                                                      //INDENTACAO!.

}

void imprimirDecresc(Lista *list,FILE *x,int n){                                                                        //IMPRIME NUM ARQUIVO UMA LISTA EM ORDEM DECRESCENTE, COM O TAMANHO DELA INCLUSO!.
    PtrNoLista aux;                                                                                                     //CRIA UMA VARIAVEL AUX PARA PERCORRER A LISTA.
    aux = list->fim;                                                                                                    //ELA COMECA DO FIM.
    fprintf(x,"Tamanho = %i\n",n);                                                                                      //INICIALMENTE IMPRIME O TAMANHO DA LISTA NO ARQUIVO, PASSADA POR PARAMETRO PELA FUNCAO.
    fprintf(x,"Lista = {");                                                                                             //INDENTACAO.
    while (aux->anterior!=NULL){                                                                                        //FAZ NOSSO PONTEIRO PERCORRER A LISTA ATE QUE NAO EXISTA ELEMENTOS ANTES.
        fprintf(x,"%i",aux->item.chave);                                                                                //IMPRIME A CHAVE ATUAL NO ARQUIVO.
        fprintf(x,",");                                                                                                 //IMPRIME UMA VIRGULA PARA DIFERENCIAR OS ELEMENTOS.
        aux = aux->anterior;                                                                                            //ATUALIZA A VARIAVEL AUX(ELA VAI PARA O ELEMENTO ANTERIOR.
    }
    fprintf(x,"%i",aux->item.chave);                                                                                    //PRINTA O ULTIMO ELEMENTO POIS ELE NAO ENTRA NO LOOP.
    fprintf(x,"}");                                                                                                     //PRINTA A IDENTACAO.

}

int estaVazia(Lista *list){                                                                                             //VERIFICACAO SE UMA LISTA ESTA OU NAO VAZIA.
    return (list->tamanho==0);                                                                                          //RETORNA ESSE TAMANHO.
}

void destruirLista(Lista *list){                                                                                        //DESTROI UMA LISTA.
    if (estaVazia(list)==1){                                                                                            //VERIFICA SE A LISTA ESTA VAZIA.
        printf("Sua Lista esta vazia impossivel Destruir!");                                                            //MSG DE WARNING.
    }else{
        PtrNoLista aux;                                                                                                 //CRIA PONTEIRO AUXILIAR.
        aux = list->inicio;                                                                                             //ELE COMECA DO INICIO.
        while (aux!= NULL){                                                                                             //VAI ATE O FIM.
            list->inicio = list->inicio->proximo;                                                                       //FAZ O INICIO RECEBER O PROXIMO.
            free(aux);                                                                                                  //DESALOCA O INICIO.
            aux=list->inicio;                                                                                           //COMECA DO NOVO INICIO.
        }
        printf("Lista Destruida!!");                                                                                    //MSG DE CONCLUSAO.
    }

}

void inserir(Lista *list, Objeto x){                                                                                    //INSERE UM OBJETO NUMA LISTA.
    PtrNoLista novo;                                                                                                    //CRIA UMA VARIAVEL DO TIPO NO PARA COLOCAR NA FILA.
    novo = (PtrNoLista)malloc(sizeof(NoLista));                                                                         //ALLOCA A MEMORIA DELA .
    novo->item = x;                                                                                                     //FAZ ELA RECEBER A CHAVE DE INSERCAO.

    if ((estaVazia(list)==1)){                                                                                          //1 CASO = CASO A LISTA ESTEJA VAZIA.
        novo->anterior = list->inicio;                                                                                  //O ANTERIOR RECEBE O INICIO .
        novo->proximo = list->fim;                                                                                      //O PROXIMO RECEBE O FIM .
        list->inicio = novo;                                                                                            //O INICIO RECEBE O NOVO.
        list->fim = novo;                                                                                               //O FIM RECEBE O NOVO TAMBEM POIS AINDA NAO EXISTE ELEMENTOS ESSE SERA O PRIMEIRO PORTANTO ELE SERA O COMECO E O FIM.
        list->tamanho++;                                                                                                //INCREMENTA O TAM.
    } else if ((x.chave < list->inicio->item.chave)){                                                                   //2 CASO = CASO O ELEMENTO A SER INSERIDO SEJA MENOR QUE O 1 ELEMENTO DA LISTA(VAI INSERIR ANTES DELE!).
        novo->anterior = NULL;                                                                                          //O ANTERIOR DO NOVO SERA NULO POIS ELE E O MENOR ELEMENTO DA LISTA.
        novo->proximo = list->inicio;                                                                                   //O SEU PROXIMO RECEBE O COMECO DA LISTA.
        list->inicio->anterior = novo;                                                                                  //O PRIMEIRO ELEMENTO DA LISTA AGORA SERA O NOVO.
        list->inicio = novo;                                                                                            //PORTANTO AGORA ESSE SERA SEU NOVO 1 ELEMENTO.
        list->tamanho++;                                                                                                //INCREMENTA TAMANHO.

    }else if ((x.chave > list->fim->item.chave)) {                                                                      //3 CASO = CASO O ELEMENTO SEJA MAIOR QUE O ULTIMO ELEMENTO DA LISTA(VAI INSERIR DEPOIS DELE!).
        novo->proximo = NULL;                                                                                           //COMO SERA O ULTIMO ELEMENTO O PROXIMO SERA O FINAL.
        novo->anterior = list->fim;                                                                                     //O ANTERIOR VAI SER O FIM .
        list->fim->proximo = novo;                                                                                      //O PROXIMO DO FIM DA LISTA VAI RECEBER O ELEMENTO POIS ESSE E O ULTIMO.
        list->fim = novo;                                                                                               //O FIM DA LISTA AGORA VAI SER ELE.
        list->tamanho++;                                                                                                //INCREMENTA O TAMANHO.

    }else{                                                                                                              //4 CASO = CASO NAO SEJA NENHUM DOS CASOS ANTERIORES!.

        PtrNoLista aux;                                                                                                 //CRIA UMA VARAIVEL PARA ACHAR UMA POSICAO PARA INSERIR.
        aux = list->inicio;                                                                                             //COMECA DO INICIO.
        if (aux->item.chave == x.chave){                                                                                //4.1 = CASO O ELEMENTO JA ESTEJA NA LISTA NAO DEVERA SER INSERIDO NOVAMENTE! (OPCIONAL AO USUARIO).
        }else{

            while (aux->proximo != NULL && x.chave > aux->proximo->item.chave){                                         //PERCORRE ATE QUE O PROXIMO ELEMENTO NAO SEJA MENOR QUE O QUE VOCE QUER INSERIR, PORTANTO O AUX PARA UM NO ANTES.
                aux = aux->proximo;
            }

            novo->proximo = aux->proximo;                                                                               //O PROXIMO DO ELEMENTO DO NOVO SERA O ATUAL PROXIMO DO AUX.
            novo->anterior = aux;                                                                                       //O ANTERIOR DO NOVO SERA O AUX .
            aux->proximo->anterior = novo;                                                                              //O PROXIMO DO ANTERIOR DO AUXILIAR AGORA SERA O NOVO.
            aux->proximo = novo;                                                                                        //E O PROXIMO DO AUX SERA O NOVO.
            list->tamanho++;                                                                                            //INCREMENTA O TAMANHO.
        }
    }

}

int tamanhoLista(Lista *list){                                                                                          //RETORNA TAMANHO DA LISTA ATRAVES DO CONTADOR NA INSERCAO DE ELEMENTOS.
    return list->tamanho;
}

int main(int argc, char *argv[]){

    FILE *arq1=NULL;                                                                                                    //VARIAVEL PARA ARQUIVO DE ENTRADA!.
    FILE *arq2=NULL;                                                                                                    //VARIAVEL PARA ARQUIVO DE SAIDA!.

    arq1 = fopen(argv[1], "r");                                                                                         //ABRE O ARQUIVO DE ENTRADA.
    arq2 = fopen(argv[2], "w+");                                                                                         //ABRE O ARQUIVO DE SAIDA.

    char c;                                                                                                             //VARIAVEL PARA LEITURA DO PRIMEIRO CARACTER!.
    int n=0;                                                                                                            //VARIAVEL PARA LEITURA DOS NUMEROS.
    Objeto numeros;                                                                                                     //VARIAVEL DO TIPO OBJETO PARA OS NUMEROS.

    if (arq1 == NULL) {                                                                                                 //ERRO ABERTURA DO ARQUIVO 1.
        printf ("Erro ao abrir arquivo de entrada! \n");
    } else if (arq2 == NULL) {                                                                                          //ERRO ABERTURA ARQUIVO 2.
        printf ("Erro ao abrir arquivo de saida! \n");
    }else{                                                                                                              //CASO NAO APRESENTE ERROS.
        c = fgetc(arq1);                                                                                                //VARIAVEL C PEGA PRIMEIRO OBJ.
        if (c == 'c') {                                                                                                 //CASO O 1 CARACTER SEJA C.
            Lista crescente;                                                                                            //CRIA A LISTA CRESCENTE.
            iniciaLista(&crescente);                                                                                    //INCIA A LISTA CRESCENTE.
            fseek (arq1 , 3 , SEEK_SET );                                                                               //SETA O PONTEIRO DO ARQUIVO PARA A 1 POSICAO DA LINHA DE BAIXO! PULANDO DEMAIS CARACTER(QUEBRA DE LINHA).

            for (int i = 0; !feof (arq1); i++) {                                                                        //CONDICAO DE LOOP PARA PERCORRER TODO ARQUIVO .
                fscanf(arq1,"%i",&numeros.chave);                                                                       //LE UM NUMERO DO ARQUIVO E ARMAZENA NA CHAVE DO OBJETO NUMEROS.
                inserir(&crescente,numeros);                                                                            //INSERI ESSE OBJETO NA LISTA.
                fscanf(arq1,"%c",&c);                                                                                   //LE A VIRGULA.

            }

            printf("O arquivo comeca com o caracter 'C', a lista sera ordenada crescentemente!\n");                     //MENSAGEM DE AVISO.
            printf("Tamanho = %i\n",tamanhoLista(&crescente));                                                          //IMPRIME TAMANHO DA LISTA NO TERMINAL.
            imprimirListaComeco(&crescente);                                                                            //IMPRIME LISTA NO TERMINAL.
            imprimirCresc(&crescente,arq2,tamanhoLista(&crescente));                                                    //IMPRIME A LISTA COM TAMANHO E ORDEM NO ARQUIVO DE SAIDA.
            destruirLista(&crescente);                                                                                  //DESTROI A LISTA.


        }else if(c == 'd'){                                                                                             //CASO O 1 CARACTER SEJA D.
            Lista decrescente;                                                                                          //INCIA A LISTA DECRESCENTE.
            iniciaLista(&decrescente);                                                                                  //CRIA A LISTA DECRESCENTE.
            fseek (arq1 , 3 , SEEK_SET );                                                                               //SETA O PONTEIRO DO ARQUIVO PARA A 1 POSICAO DA LINHA DE BAIXO! PULANDO DEMAIS CARACTER(QUEBRA DE LINHA).

            for (int i = 0; !feof (arq1); i++) {                                                                        //CONDICAO DE LOOP PARA PERCORRER TODO ARQUIVO .
                fscanf(arq1,"%i",&numeros.chave);                                                                       //LE UM NUMERO DO ARQUIVO E ARMAZENA NA CHAVE DO OBJETO NUMEROS.
                inserir(&decrescente,numeros);                                                                          //INSERI ESSE OBJETO NA LISTA.
                fscanf(arq1,"%c",&c);                                                                                   //LE A VIRGULA.
            }

            printf("O arquivo comeca com o caracter 'D', a lista sera ordenada decrescentemente!\n");                   //MENSAGEM DE AVISO.
            printf("Tamanho = %i\n",tamanhoLista(&decrescente));                                                        //IMPRIME TAMANHO DA LISTA NO TERMINAL.
            imprimirListaFim(&decrescente);                                                                             //IMPRIME LISTA NO TERMINAL.
            imprimirDecresc(&decrescente,arq2,tamanhoLista(&decrescente));                                              //IMPRIME A LISTA COM TAMANHO E ORDEM NO ARQUIVO DE SAIDA.
            destruirLista(&decrescente);                                                                                //DESTROI A LISTA.

        }else{                                                                                                          //CASO O PRIMEIRO CARCTER NAO SEJA NEM D NEM C.
            printf("ERROR!");                                                                                           //IMRPRIME NO TERMINAL MENSAGEM DE ERRO.
            fprintf(arq2,"%s","ERROR!!");                                                                               //IMPRIME NO ARQUIVO MENSAGEM DE ERRO.
        }

        fclose(arq1);                                                                                                   //FECHA O ARQUIVO 1.
        fclose(arq2);                                                                                                   //FECHA O ARQUIVO 2.
    }

    return 0;
}