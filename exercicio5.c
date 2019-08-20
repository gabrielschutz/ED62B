#include <stdio.h>
#include <printf.h>
#include <string.h>
#include <stdlib.h>



typedef struct {
    char nome[30];
    char tipo[30];
    int integrantes;
    int rank;
}bandas;

void limpar_buffer(){
    char c;
    while((c = getchar()) != '\n' && c != EOF) { }
}

void func(bandas *cad){

    printf("Digite o nome da banda: \n");
    fgets(cad->nome, sizeof(cad->nome),stdin);
    cad->nome[strcspn(cad->nome, "\n")] = '\0';
    printf("Digite o tipo de som da banda: \n");
    fgets(cad->tipo, sizeof(cad->tipo),stdin);
    cad->tipo[strcspn(cad->tipo, "\n")] = '\0';
    printf("Digite a quantidade de pessoas: \n");
    scanf("%i",&cad->integrantes);
    limpar_buffer();
    printf("Digite a posicao do rank das banda: \n");
    scanf("%i",&cad->rank);
    limpar_buffer();
};

void func2(bandas *print){
    printf("NOME: ");
    printf("%s \n",print->nome);
    printf("TIPO: ");
    printf("%s \n",print->tipo);
    printf("INTEGRANTES: ");
    printf("%i \n",print->integrantes);
    printf("Ranking: ");
    printf("%i \n",print->rank);
    printf("\n");

};


int main(){

    bandas *lista = NULL;
    lista = (bandas *) malloc (5 * sizeof(bandas));

    for (int i = 0; i < 5; ++i) {
        func(&lista[i]);
    }

    for (int j = 0; j < 5; ++j) {
        if(lista[j].rank == 1){
            func2(&lista[j]);
        }else if(lista[j].rank == 2){
            func2(&lista[j]);
        }else if(lista[j].rank == 3){
            func2(&lista[j]);
        }else if(lista[j].rank == 4){
            func2(&lista[j]);
        }else{
            func2(&lista[j]);
        }
    }

    int l;
    printf("Digite o rank que deseja imprimir: \n");
    scanf("%i",&l);
    limpar_buffer();
    func2(&lista[l]);
    

    free(lista);

    
    return (0);
}

