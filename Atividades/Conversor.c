#include <stdio.h>
#include <stdlib.h>
#define TAM 100                                                                                                         //TAMANHO DA PILHA ESTATICA

#include "PilhaEstatica.h"
#include "PilhaDinamica.h"


long converter(int decimal){                                                                                            //FUNCAO PARA CONVERSAO DE UM DECIMAL PARA INTEIRO...
    long binario=0,restante,a=1;
    while(decimal != 0)
    {
        restante = decimal % 2;
        binario = binario + restante * a;
        a = a * 10;
        decimal = decimal / 2;
    }
    return binario;
}

int main(int argc, char *argv[]) {
    FILE *arq1;                                                                                                         //CRIA O ARQUIVO 1 (ENTRADA)
    FILE *arq2;                                                                                                         //CRIA O ARQUIVO 2 (SAIDA)

    char tipo;                                                                                                          //VARIAVEL PARA VER QUAL TIPO DE PILHA SERA USADA
    int numeros;                                                                                                        //VARIAVEL PARA LER OS NUMEROS INTEIROS DO ARQUIVO

    arq1 = fopen(argv[1],"r");                                                                                          //ABRE O ARQUIVO 1 (ENTRADA) EM R(LEITURA) POR PARAMETROS QUE O USUARIO DIGITOU
    arq2 = fopen(argv[2],"w+");                                                                                         //ABRE O ARQUIVO 2 (SAIDA) EM W(ESCRITA) POR PARAMETROS QUE O USUARIO DIGITOU

    if (arq1 == NULL||arq2 == NULL){
        printf("OCORREU ALGUM ERRO AO ABRIR OS ARQUIVOS");
    } else{
        fscanf(arq1,"%c",&tipo);                                                                                        //LE O PRIMEIRO CARACTER DO ARQUIVO E ARMAZENA NA VARIAVEL TIPO
        if (tipo == 'd'){                                                                                               //CASO O USUARIO ESCOLHEU PILHA DINAMICA
            pilhaDinamica minhapilha;                                                                                   //CRIA UMA PILHA DINAMICA
            ObjetoD obj;                                                                                                //CRIA UMA VARIAVEL DE OBJETOS
            iniciaPilhaD(&minhapilha);                                                                                  //INICIA A PILHA DINAMICA "MINHAPILHA"
            for (int i = 0; !feof(arq1) ; ++i) {                                                                        //CRIA UM LACO QUE PERCORRE O ARQUIVO DE ENTRADA !
                fscanf(arq1,"%i",&numeros);                                                                             //LE OQUE ESTA NO ARQUIVO E ARMAZENA NA VARAIVEL NUMEROS(SOBREPONHA OQUE JA ESTA DENTRO DELA)
                obj.chave = converter(numeros);                                                                         //VARIAVEL DO TIPO OBJETOD RECEBE O RETORNO DA FUNCAO BINARIA QUE RECEBEU OS NUMEROS DO ARQUIVO
                empilhaD(obj,&minhapilha);                                                                              //EMPILHA A VARIAVEL OBJETOD NA PILHA(MINHAPILHA)
            }
            //imprimePilhaArqD(&minhapilha,arq2);                                                                       //CHAMA A FUNCAO IMPRIME A PILHA DINAMICA NUM ARQUIVO DE TEXTO!, PASSANDO POR PARAMETROS A PILHA QUE QUER IMPRIMIR E O ARQUIVO A QUAL SERA IMPRESSO! (OUTRA MANEIRA DE FAZER!)
            ObjetoD obj1;                                                                                               //VARIAVEL DO TIPO OBJETO AUXILIAR
            int k = tamanhoPilhaD(&minhapilha);                                                                         //K RECEBE O TAMANHO DA PILHA
            for (int j = 0; j < k ; ++j) {                                                                              //UM LACO PARA DESEMPILHAR TODA A PILHA
                fprintf(arq2,"%d\n",desempilhaD(&minhapilha,obj1));                                                     //PRINTA NO ARQUIVO O OBJETO DESEMPILHADO
            }
            }
        }

        if (tipo == 'e'){                                                                                               //CASO O USUARIO ESCOLHEU PILHA ESTATICA
            char chr;                                                                                                   //CRIA UMA VARIAVEL PARA LER OS CARACTERES DO ARQUIVO
            int qtd_decimais=0;                                                                                         //CRIA VARIAVEL PARA CONTAR AS LINHAS DO ARQUIVO
            while((feof(arq1)) == 0) {                                                                                  //WHILE PARA RODAR O ARQUIVO
                chr = fgetc(arq1);                                                                                      //CHR RECEBE O CARACTER ATUAL QUE O PONTEIRO APONTA
                if (chr == '\n') {                                                                                      //SE ESSE CARACTER FOR QUEBRA DE LINHA ADICIONA MAIS 1 AO CONTADOR
                    qtd_decimais++;
                }
            }
            fseek(arq1,2,SEEK_SET);                                                                                     //COLOCA O PONTEIRO DO ARQUIVO DE VOLTA PARA POSICAO DO 3 CARACTER
            printf("O SEU ARQUIVO CONTEM %i NUMEROS A SEREM CONVERTIDOS, A PILHA ESTATICA ESTA DEFINA PARA TAMANHO %i, MUDE O VALOR DE TAM NO CABECOTE DO PROGRAMA CASO PRECISE QUE SUA PILHA SEJA MAIOR!\n",qtd_decimais,TAM); //MSG DE AVISO
            if(TAM<qtd_decimais){                                                                                       //CONDICAO PARA QUE A PILHA ESTATICA NAO SEJA MENOR QUE O NUMERO DE DECIMAIS
                printf("Erro no programa! (TAMANHO DA PILHA E MENOR QUE O TAMANHO DE DECIMAIS A SEREM CONVERTIDOS)");   //MSG DE ERRO
            }else{
                pilhaEstatica minhapilha;                                                                               //CRIA A PILHA ESTATICA
                ObjetoE obj;                                                                                            //CRIA OBJETO ESTATICO
                iniciaPilhaE(&minhapilha);                                                                              //INICIA A PILHA
                for (int i = 0; !feof(arq1) ; ++i) {                                                                    //CRIA UM LACO QUE PERCORRE O ARQUIVO DE ENTRADA !
                    fscanf(arq1,"%i",&numeros);                                                                         //LE OQUE ESTA NO ARQUIVO E ARMAZENA NA VARAIVEL NUMEROS(SOBREPONHA OQUE JA ESTA DENTRO DELA);
                    obj.chave = converter(numeros);                                                                     //VARIAVEL DO TIPO OBJETOD RECEBE O RETORNO DA FUNCAO BINARIA QUE RECEBEU OS NUMEROS DO ARQUIVO
                    empilhaE(obj,&minhapilha);                                                                          //EMPILHA A VARIAVEL OBJETOE NA PILHA(MINHAPILHA)
                }
                //imprimePilhaArqE(&minhapilha,arq2);                                                                   //CHAMA A FUNCAO IMPRIME A PILHA ESTATICA NUM ARQUIVO DE TEXTO!, PASSANDO POR PARAMETROS A PILHA QUE QUER IMPRIMIR E O ARQUIVO A QUAL SERA IMPRESSO! (OUTRA MANEIRA DE FAZER!)
                ObjetoE obj1;                                                                                           //VARIAVEL DO TIPO OBJETO AUXILIAR
                int k = tamanhoPilhaE(&minhapilha);                                                                     //K RECEBE O TAMANHO DA PILHA
                for (int j = 0; j < k ; ++j) {                                                                          //UM LACO PARA DESEMPILHAR TODA A PILHA
                    fprintf(arq2,"%d\n",desempilhaE(obj1,&minhapilha));                                                 //PRINTA NO ARQUIVO O OBJETO DESEMPILHADO
                }
            }
    }

    return 0;
}
