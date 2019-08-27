#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>



int main(){

    FILE *arq1=NULL;
    FILE *arq2=NULL;

    arq1 = fopen("/media/home/antman/arq1.txt","r");
    arq2 = fopen("/media/home/antman/arq2.txt","w+");

    if ((arq1 == NULL)||(arq2 == NULL)) {
       printf ("Houve um erro ao abrir o arquivo.\n");
       return 1;
    }

    int cont=0;
    char chr;

    while(feof(arq1) == 0){
        chr = fgetc(arq1);
        if(chr == EOF){
            break;
        }
        chr = tolower(chr);
        if ((chr == 'a')||(chr == 'e')||(chr == 'i')||(chr == 'o')||(chr == 'u')){
            fputc('*',arq2);
        }else{
            fputc(chr,arq2);
        }

        if(chr=='\n'){
            cont++;
        }



    }

    printf("O arquivo contem %i linhas. \n",cont);

    fclose(arq1);
    fclose(arq2);




    return 0;
}
