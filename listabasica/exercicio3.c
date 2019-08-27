#include <stdio.h>

int potencia(int base,int expoente){
    if (expoente == 0){
        return 1;
    }else{
        return (base * potencia(base,expoente-1));
    }
}

int main() {
    float base,expoente,resultado;
    printf("Digite a base: \n");
    scanf("%f",&base);
    printf("Digite a expoente: \n");
    scanf("%f",&expoente);

    resultado = potencia(base,expoente);

    printf("O resultado de %.0f elevado a %.0f é: %.2f",base,expoente,resultado);

    return 0;
}
