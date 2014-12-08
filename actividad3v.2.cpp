#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

int toInt(char);
int resto (char cadena[], int divisor);
char toChar(int);
void escribeIBAN(char IBAN[]);
int dcCCCaux (char cadena[]);
void dcCCC (char entbancaria[], char sucursal[], char cuenta[], char digcontrol[]);



void escribeIBAN(char x[]);

void dcIBAN (char cuenta[], char CodigoPais[]) {
    //Anadimos las letras y los dos ceros al final.
    strcat(strcat(cuenta,CodigoPais),"00");


}

void reemplazaLetra(char cadena[]) {
    int tmax = strlen(cadena);
    char storage[tmax];
    char aux[2];
    int numval;
    for (int i=0;i<tmax;i++) {
        numval = toInt(cadena[i]);
        //Comprobamos si es el elemento i de cadena
        //una letra entre A y Z mayusculas o no.
        if (numval>=65 || numval<=90){
            aux[0] = toChar((int)(numval/10));
            aux[1] = toChar(numval%10);
            strcat(storage,aux);

        }
    }


}



int main(void)
{

    char entbancaria[5] = "8987";
    char sucursal[6]    = "9876";
    char cuenta[20]     = "8888888888";
    char digcontrol[3]  = "";


    double x = 4.99;
    char a[2];

    printf("%d", (int)x);



    return 0;
}



int toInt(char digito) {
    return digito - '0';
}

char toChar(int n) {
    return (char)(n + '0');
}

void escribeIBAN(char IBAN[]) {
    int longIBAN = strlen(IBAN);
    for (int i=1;i<longIBAN+1;i++) {
        printf("%s",IBAN[i-1]);
        if (i % 4 == 0)
            printf(" ");
    }
}

int resto (char cadena[], int divisor) {
    int r  = 0;
    int longCadena = strlen(cadena);
    for (int k=0;k<longCadena;k++) {
        r  =  10*r+toInt(cadena[k]);
        r %=  divisor;
    }
    return r;
}

int dcCCCaux (char cadena[]) {
    //introducir aqui condicional para ver si tiene caracteres numericos o no

    int longCadena = strlen(cadena);
    int exp2       = 1;
    int resultado  = 0;
    for (int i=0;i<longCadena;i++) {
        resultado += (toInt(cadena[i]) * exp2) % 11;
        exp2      *= 2;
    }
    resultado     %= 11;
    return resultado;
}

void dcCCC (char entbancaria[], char sucursal[], char cuenta[], char digcontrol[]) {
    char a, b;

    //calculo del segundo digito de control
    int x = dcCCCaux(cuenta);
    int valor = 11 - (x % 11);
    if      (valor  < 10)   b = toChar(valor);
    else if (valor == 10)   b = '1';
    else                    b = '0';

    //calculos el primer digito de control
    char cadenaAux[3] = {'0','0','\0'};
    x = dcCCCaux(strcat(strcat(cadenaAux,entbancaria),sucursal));
    valor = 11 - (x % 11);
    if      (valor  < 10)   a = toChar(valor);
    else if (valor == 10)   a = '1';
    else                    a = '0';

    //almacenamos los resultados obtenidos
    digcontrol[0]= a;
    digcontrol[1]= b;
}
