#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>

//TODAS AS VARI�VEIS S�O GLOBAIS PARA FACILITAR O FUNCIONAMENTO DO PROGRAMA
//plp
char numero[10];
char equacao[10];
char operacao[7] = {'+','-','*','/','R','f','F'};

int auxSoma[10]={0,0,0,0,0,0,0,0,0,0};
int auxSub[10]={0,0,0,0,0,0,0,0,0,0};
int auxMulti[10]={0,0,0,0,0,0,0,0,0,0};
int auxDiv[10]={0,0,0,0,0,0,0,0,0,0};
int auxFat[10]={0,0,0,0,0,0,0,0,0,0};
int auxRaiz[10]={0,0,0,0,0,0,0,0,0,0};
int auxFib[10]={0,0,0,0,0,0,0,0,0,0};

int jMulti = 0;
int jDiv = 0;
int jSub = 0;
int jSoma = 0;
int jFat = 0;
int jRaiz = 0;
int jFib = 0;
int contOP;
int m=0;
int cont=0;
int x=0;
int i=0;
int j =0;
int aux=9;
int aux1=0;
int cont2=0;
int n=0;
int auxOP=0;
int auxPos=0;
int posAux=0;

char regAux[5];
char num1[20]="li $s0, \n";//COMANDO PADR�O PARA TODAS AS OPERA��ES NO ASSEMBLY
char num2[20] ="li $s1, \n";

FILE *fptr;

void leEquacao(){
    strcpy(regAux,"$t0");
    for(x=0; x < strlen(equacao);x++){
        if(equacao[x] == operacao[2]){//PROCURA NA EQUACAO PARA VER SE TEM O OPERADOR DE MULTIPLICA��O
            auxMulti[jMulti] = x;
            jMulti++;
        }
        if(equacao[x] == operacao[3]){//PROCURA NA EQUACAO PARA VER SE TEM O OPERADOR DE DIVIS�O
            auxDiv[jDiv] = x;
            jDiv++;
        }
        if(equacao[x] == operacao[0]){//PROCURA NA EQUACAO PARA VER SE TEM O OPERADOR DE SOMA
            auxSoma[jSoma] = x;
            jSoma++;
        }
        if(equacao[x] == operacao[1]){//PROCURA NA EQUACAO PARA VER SE TEM O OPERADOR DE SUBTRA��O
            auxSub[jSub] = x;
            jSub++;
        }
    }


    //FAZ UMA COMPARA��O PRA SABER EM QUAL POSI��O DA EQUA��O TEM RAIZ QUADRADA
    for(x=0; x < strlen(equacao); x++){
        if(equacao[x] == operacao[4]){
            auxRaiz[jRaiz] = x;
            jRaiz++;
        }
    }

    //FAZ UMA COMPARA��O PRA SABER EM QUAL POSI��O DA EQUA��O TEM FIBONACCI
    for(x=0; x < strlen(equacao); x++){
        if(equacao[x] == operacao[6]){
            auxFib[jFib] = x;
            jFib++;
        }
    }

    //FAZ UMA COMPARA��O PRA SABER EM QUAL POSI��O DA EQUA��O TEM FATORIAL
    for(x=0; x < strlen(equacao); x++){
        if(equacao[x] == operacao[5]){
            auxFat[jFat] = x;
            jFat++;
        }
    }

    contOP = (jMulti+jDiv+jSub+jSoma+jFat+jRaiz+jFib);//PARA SABER QUANTAS OPERA��ES TEM NA EQUA��O

}

void mostra(){

    for(i=0;i<strlen(equacao);i++){
        if(auxRaiz[i] != 0){
            if(contOP > 1){//SE HOUVER MAIS QUE UMA EQUA��O
                if(auxOP > auxRaiz[i]){
                    auxPos = 1;//SE A PRIMEIRA OPERA��O VIER ANTES DA DIVIS�O
                }
                //A PRIMEIRA OPERA��O NA ORDEM DE PRECED�NCIA MATEM�TICA
                else{
                    auxPos = 2;//SE A PRIMEIRA OPERA��O VIER DEPOIS DA DIVIS�O
                }
                raiz(i);
            }
            else if(contOP == 1){//SE HOUVER SOMENTE UMA OPERA��O JA ESCREVE EM ASSEMBLY PARA EXIBIR NO MARS
                raiz(i);
                fputs("li $v0,1 \n",fptr);
                fputs("move $a0,$t0\n",fptr);
                fputs("syscall", fptr);
                fputs("\n#FIM RAIZ\n\n",fptr);

                break;
            }

            auxOP = auxRaiz[i];

            fputs("\n#FIM RAIZ\n\n",fptr);
            break;
        }
    }

    for(i=0;i<strlen(equacao);i++){
        if(auxFat[i] != 0){
            if(contOP > 1){//SE HOUVER MAIS QUE UMA EQUA��O
                if(auxOP > auxFat[i]){
                    auxPos = 1;//SE A PRIMEIRA OPERA��O VIER ANTES DA DIVIS�O
                }
                //A PRIMEIRA OPERA��O NA ORDEM DE PRECED�NCIA MATEM�TICA
                else{
                    auxPos = 2;//SE A PRIMEIRA OPERA��O VIER DEPOIS DA DIVIS�O
                }
                fat(i);
            }
            else if(contOP == 1){//SE HOUVER SOMENTE UMA OPERA��O JA ESCREVE EM ASSEMBLY PARA EXIBIR NO MARS
                fat(i);
                fputs("li $v0,1 \n",fptr);
                fputs("move $a0,$t0\n",fptr);
                fputs("syscall", fptr);

                break;
            }

            auxOP = auxFat[i];

            fputs("\n#FIM FATORIAL\n\n",fptr);
            //break;
        }
    }

    for(i=0;i<strlen(equacao);i++){
        if(auxFib[i] != 0){
            if(contOP > 1){//SE HOUVER MAIS QUE UMA EQUA��O
                if(auxOP > auxFib[i]){
                    auxPos = 1;//SE A PRIMEIRA OPERA��O VIER ANTES DA DIVIS�O
                }
                //A PRIMEIRA OPERA��O NA ORDEM DE PRECED�NCIA MATEM�TICA
                else{
                    auxPos = 2;//SE A PRIMEIRA OPERA��O VIER DEPOIS DA DIVIS�O
                }
                fib(i);
            }
            else if(contOP == 1){//SE HOUVER SOMENTE UMA OPERA��O JA ESCREVE EM ASSEMBLY PARA EXIBIR NO MARS
                fib(i);
                fputs("li $v0,1 \n",fptr);
                fputs("move $a0,$t0\n",fptr);
                fputs("syscall", fptr);

                break;
            }

            auxOP = auxFib[i];

            fputs("\n#FIM FIBONNACI\n\n",fptr);
            break;
        }
    }


    for(i=0;i<strlen(equacao);i++){
        if(auxMulti[i] != 0){
            Multi(i);
            if(contOP == 1){//SE HOUVER SOMENTE UMA OPERA��O JA ESCREVE EM ASSEMBLY PARA EXIBIR NO MARS
                fputs("li $v0,1 \n",fptr);
                fputs("move $a0,$t0\n",fptr);
                fputs("syscall", fptr);

                break;
            }
            else{
                auxOP = auxMulti[i];
            }

            fputs("#FIM MULTIPLICA��O\n\n",fptr);
        }
    }


    for(i=0;i<strlen(equacao);i++){
        if(auxDiv[i] != 0){
            if(contOP > 1){//SE HOUVER MAIS QUE UMA EQUA��O
                if(auxOP > auxDiv[i]){
                    auxPos = 1;//SE A PRIMEIRA OPERA��O VIER ANTES DA DIVIS�O
                }
                //A PRIMEIRA OPERA��O NA ORDEM DE PRECED�NCIA MATEM�TICA
                else{
                    auxPos = 2;//SE A PRIMEIRA OPERA��O VIER DEPOIS DA DIVIS�O
                }
                Div(i);
            }
            else if(contOP == 1){//SE HOUVER SOMENTE UMA OPERA��O JA ESCREVE EM ASSEMBLY PARA EXIBIR NO MARS
                Div(i);
                fputs("li $v0,1 \n",fptr);
                fputs("move $a0,$t0\n",fptr);
                fputs("syscall", fptr);

                //break;
            }

            auxOP = auxDiv[i];

            fputs("\n#FIM DIVIS�O\n\n",fptr);
            //break;
        }
    }

    for(i=0;i<strlen(equacao);i++){
        if(auxSoma[i] != 0){
            if(contOP > 1){//SE HOUVER MAIS QUE UMA EQUA��O
                if(auxOP > auxSoma[i]){
                    auxPos = 1;//SE A PRIMEIRA OPERA��O VIER ANTES DA DIVIS�O
                }
                //A PRIMEIRA OPERA��O NA ORDEM DE PRECED�NCIA MATEM�TICA
                else{
                    auxPos = 2;//SE A PRIMEIRA OPERA��O VIER DEPOIS DA DIVIS�O
                }
                Soma(i);
            }
            else if(contOP == 1){//SE HOUVER SOMENTE UMA OPERA��O JA ESCREVE EM ASSEMBLY PARA EXIBIR NO MARS
                Soma(i);
                fputs("li $v0,1 \n",fptr);
                fputs("move $a0,$t0\n",fptr);
                fputs("syscall", fptr);

            }

            auxOP = auxSoma[i];

            fputs("\n#FIM SOMA\n\n",fptr);
        }
    }

    for(i=0;i<strlen(equacao);i++){
        if(auxSub[i] != 0){
            if(contOP > 1){//SE HOUVER MAIS QUE UMA EQUA��O
                if(auxOP > auxSub[i]){
                    auxPos = 1;//SE A PRIMEIRA OPERA��O VIER ANTES DA DIVIS�O
                }
                //A PRIMEIRA OPERA��O NA ORDEM DE PRECED�NCIA MATEM�TICA
                else{
                    auxPos = 2;//SE A PRIMEIRA OPERA��O VIER DEPOIS DA DIVIS�O
                }
                Sub(i);
            }
            if(contOP == 1){//SE HOUVER SOMENTE UMA OPERA��O JA ESCREVE EM ASSEMBLY PARA EXIBIR NO MARS
                Sub(i);
                fputs("li $v0,1 \n",fptr);
                fputs("move $a0,$t0\n",fptr);
                fputs("syscall", fptr);


            }

            auxOP = auxSub[i];

            fputs("\n#FIM SUBTRA��O\n\n",fptr);
        }
    }



}

void Multi(int valor){
    pegaNum(1,valor);

    fputs(num1,fptr);
    fputs("\n", fptr);

    fputs("move $s4 $s0\n", fptr);

    fputs(num2,fptr);
    fputs("\n", fptr);

    fputs("move $t1, $s1\n",fptr);

    fputs("move $t0,$0\n",fptr);

    fputs("Loop1:\n",fptr);
    fputs("add $t0, $t0, $s4 \n",fptr);

    fputs("sub $s1, $s1,1 \n", fptr);
    fputs("beq $s1, $0, Exit1 \n", fptr);
    fputs("j Loop1 \n",fptr);
    fputs("Exit1: \n",fptr);

    if(cont == 2){
        fputs("li $v0,1 \n",fptr);
        fputs("move $a0,$t0\n",fptr);
        fputs("syscall", fptr);
    }
}

void Div(int valor){
    pegaNum(2,valor);

    fputs(num1,fptr);
    fputs("\n",fptr);

    fputs(num2,fptr);
    fputs("\n",fptr);

    fputs("Loop2: \n",fptr);
    fputs("add $s2,$s2, $s1\n",fptr);
    fputs("slt $s4, $s2, $s0\n",fptr);

    fputs("add $s7,$s7,1\n",fptr);
    fputs("beq $s2, $s0, Exit2\n",fptr);
    fputs("beq $s4, $0,Exit3\n",fptr);

    fputs("j Loop2\n",fptr);


    fputs("Exit3:\n",fptr);
    fputs("sub $s7,$s7,1\n",fptr);
    fputs("j Exit2\n",fptr);

    fputs("Exit2: \n",fptr);
    fputs("move $t0,$s7\n",fptr);

    if(cont == 2){
        fputs("li $v0,1 \n",fptr);
        fputs("move $a0,$t0\n",fptr);
        fputs("syscall", fptr);
    }
}

void Soma(int valor){//REGISTRADOR PADRAO $T0
    pegaNum(3,valor);

    fputs(num1,fptr);
    fputs("\n",fptr);

    fputs(num2,fptr);
    fputs("\n",fptr);
    fputs("add $t0, $s1, $s0\n",fptr);

    if(cont == 2){
        fputs("li $v0,1 \n",fptr);
        fputs("move $a0,$t0\n",fptr);
        fputs("syscall", fptr);
    }

}

void Sub(int valor){
    pegaNum(4,valor);

    fputs(num1,fptr);
    fputs("\n",fptr);

    fputs(num2,fptr);
    fputs("\n",fptr);

    fputs("sub $s2, $s0, $s1\n",fptr);
    fputs("move $t0,$s2\n",fptr);

    if(cont == 2){
        fputs("li $v0,1 \n",fptr);
        fputs("move $a0,$t0\n",fptr);
        fputs("syscall", fptr);
    }
}

void fat(valor){
    pegaUm(5,valor);

    fputs(num1,fptr);
    fputs("\n", fptr);

    fputs("add $t0, $t0, 1\n", fptr);
    fputs("li $t3, 1\n", fptr);

    fputs("Loop:\n", fptr);

    fputs("mult $s0, $t0\n", fptr);
    fputs("mflo $s3\n", fptr);

    fputs("move $t0,$s3\n", fptr);
    fputs("sub $s0, $s0, 1\n", fptr);

    fputs("slt $6, $s0, $t3", fptr);
    fputs("\n",fptr);
    fputs("beq $6, $0,Loop\n", fptr);

    fputs("j Exit\n", fptr);

    fputs("Exit:\n", fptr);

    fputs("move $t0,$s3\n",fptr);

    if(cont == 2){
        fputs("li $v0,1 \n",fptr);
        fputs("move $a0,$t0\n",fptr);
        fputs("syscall", fptr);
    }
}

void raiz(int valor){
    pegaUm(6,valor);

    fputs(num1,fptr);
    fputs("\n",fptr);

    fputs("addi $t1, $t1,2 \n",fptr);
    fputs("addi $t3, $t3,2 \n",fptr);
    fputs("addi $t2,$0,0 \n",fptr);
    fputs("Loop: \n",fptr);
    fputs("add $t2,$t2,$t1 \n",fptr);
    fputs("sub $t3,$t3,1 \n",fptr);
    fputs("beq $t3,$0,Prox\n",fptr);
    fputs("j Loop \n",fptr);

    fputs("Prox: \n",fptr);
    fputs("beq $t2,$s0,Else \n",fptr);
    fputs("add $t3,$t1,1 \n",fptr);
    fputs("add $t1,$t1,1 \n",fptr);
    fputs("add $t2,$0,$0 \n",fptr);
    fputs("j Loop\n",fptr);
    fputs("Else:\n",fptr);
    fputs("move $t0,$t1\n",fptr);


    if(cont == 2){
        fputs("li $v0,1 \n",fptr);
        fputs("move $a0,$t0\n",fptr);
        fputs("syscall", fptr);
    }

    fputs("\n",fptr);
}

void fib(valor){
    pegaUm(7,valor);

    fputs(num1, fptr);
    fputs("\n", fptr);

    fputs("li $t1,0\n", fptr);
    fputs("li $t2,1\n", fptr);
    fputs("li $s1,1\n", fptr);

    fputs("sub $s0, $s0,1\n", fptr);

    fputs("Loop:\n", fptr);

    fputs("add $t3, $t2, $t1\n", fptr);
    fputs("add $t1, $t2,0\n", fptr);
    fputs("add $t2,$t3,0\n", fptr);
    fputs("sub $s0,$s0,1\n", fptr);

    fputs("slt $6,$s0,$s1\n", fptr);
    fputs("beq $6, $0,Loop\n", fptr);

    fputs("j Exit\n", fptr);

    fputs("Exit:\n", fptr);

    fputs("move $t0,$t3\n",fptr);

    if(cont == 2){
        fputs("li $v0,1 \n",fptr);
        fputs("move $a0,$t0\n",fptr);
        fputs("syscall", fptr);
    }
}

void pegaUm(int n, int valor){
    if(n == 5){
        aux = auxFat[valor];
    }
    else if(n==6){
        aux = auxRaiz[valor];
    }
    else if(n==7){
        aux = auxFib[valor];
    }
    //AUX = POS���O DA OPERA��O
    int v=0;
    int prox=7;
    int auxValor=0;


    if(contOP == 1){//SE FOR �NICA OPERA��O
        for(x=0;x<aux;x++){//ADICIONA NO NUM1 OS NUMEROS DA EQUA��O
            auxValor = equacao[x];
            if(auxValor >= 48 && auxValor <= 57){//SE ELE FOR UM INTEIRO DA TABELA ASCII DAS POSI��ES ENT�O � UM N�MERO DE 0 A 9
                num1[prox] = equacao[x];
                prox++;
            }
            else{
                break;
            }
        }
    }
    else if(contOP == 2){//SE HOUVER MAIS QUE UMA OPERA��O
        if(auxPos ==1){

            for(x=(posAux+1);x<aux;x++){
                    auxValor = equacao[x];
                    if(auxValor >= 48 && auxValor <= 57){
                        num2[prox] = equacao[x];
                        prox++;
                    }
                }
        }
        if(auxPos==2){

            for(x=0;x<aux;x++){
                auxValor = equacao[x];
                if(auxValor >= 48 && auxValor <= 57){
                    num1[prox] = equacao[x];
                    prox++;
                }
                else{
                    break;
                }
            }
        }
    }

    printf("%s",num1);
    printf("\n");
    printf("%s",num2);
    cont++;
}

void pegaNum(int n, int valor){

    /*
        NESSE ENCADEAMENTO DE IFs O AUX RECEBE A POSI��O DA OPERA��O NA EQUA��O
        ASSIM MAIS ABAIXO O PROGRAMA CONSEGUE PEGAR O N�MERO ANTES E DEPOIS DA OPERA��O
    */
    if(n==1){
        aux = auxMulti[valor];
    }
    else if(n==2){
        aux = auxDiv[valor];
    }
    else if(n==3){
        aux = auxSoma[valor];
    }
    else if(n==4){
        aux = auxSub[valor];
    }


    int v=0;
    int m=0;
    int auxValor=0;
    int prox = 7;

    if(cont == 0){
        for(v=0; v< strlen(equacao);v++){
            if(v == aux){//PERCORRE A EQUA��O AT� CHEGAR NA POSI��O DO OPERADOR
                for(m=0;m<strlen(num1);m++){
                    if(num1[m] == ','){
                        num1[m+1] = equacao[v-1];
                    }
                }
                for(j=0;j<strlen(num2);j++){
                    if(num2[j] == ','){
                        num2[j+1]=equacao[v+1];
                    }
                }
            }
        }
    }
    else if(cont == 1){
        for(v=0; v < strlen(equacao);v++){
            if(v == aux){//PERCORRE A EQUA��O AT� CHEGAR NA POSI��O DO OPERADOR
                if(auxPos == 1){
                    strcpy(num2,"move $s1, ");
                    strcat(num2,regAux);
                    strcat(num2,"\n");

                    for(j=0;j<strlen(num1);j++){//COLOCA OS VALORES DA EQUA��O NO NUM1
                        if(num1[j] == ','){
                            num1[j+1]=equacao[v-1];
                        }
                    }
                }
                else if(auxPos == 2){
                    strcpy(num1,"move $s0, ");
                    strcat(num1,regAux);
                    strcat(num1,"\n");

                    for(m=0;m<strlen(num2);m++){//COLOCA OS VALORES DA EQUA��O NO NUM2
                        if(num2[m] == ','){
                            num2[m+1] = equacao[v+1];
                        }
                    }
                }
            }
        }
    }

    printf("%s",num1);
    printf("\n");
    printf("%s",num2);

    cont++;
}


int main(){
    setlocale(LC_ALL, "Portuguese");

    printf("=========================================\n");
    printf("|  INFORMACOES GERAIS SOBRE O PROGRAMA  |\n");
    printf("=========================================\n");
    printf("ADI��O = +\n");
    printf("SUBTRA��O = -\n");
    printf("MULTIPLI��O = *\n");
    printf("DIVIS�O = /\n");
    printf("RAIZ QUADRADA = n�mero + R\n");
    printf("FATORIAL = n�mero + f\n");
    printf("FIBONNACI = n�mero + F\n\n");


    printf("Digite sua equa��o: ");
    scanf("%s", &equacao);


    fptr = fopen("trabalho.asm","w+");//ABRE O ARQUIVO NO FORMATO .ASM PARA SER ABERTO PELO MARS
    fputs(".data\n",fptr);
    fputs(".text\n\n",fptr);

    leEquacao();
    mostra();

    fclose(fptr);//FECHA O ARQUIVO
    return 0;
}

