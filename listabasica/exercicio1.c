#include <stdio.h>
#include <stdlib.h>



int converter(int totalMinutos,int *horas,int *minutos){
    int minu = totalMinutos%60;
    int hora = totalMinutos/60;
    *horas=hora;
    *minutos=minu;
}

int main(){
    
    int totalMinutos;
    int horas, minutos;
    
    printf("Digite o total de minutos: \n");
    scanf("%i",&totalMinutos);
    
    converter(totalMinutos,&horas,&minutos);
    
    printf("Horas: %i",horas);
    printf("Minutos: %i",minutos);


    return 0;
}
