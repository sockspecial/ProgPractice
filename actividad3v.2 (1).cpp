/*
Grupo MB_02 Informatica
...
*/

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

void dcIBAN (char cadena[], char CodigoPais[], char dcontrolIBAN[]) {
    //Anadimos las letras y los dos ceros al final.
    int tmax = strlen(cadena);
    char cuenta[tmax];
    strcpy(cuenta, cadena);
    strcat(strcat(cuenta,CodigoPais),"00");

    char auxStorage[2*tmax+1];
    int numval;

    int i=0; int j=0;
    while (cuenta[i]!='\0') {
        if (cuenta[i]>='A' && cuenta[i]<='Z') {
            numval=cuenta[i]-'A'+10;
            auxStorage[j]=toChar(numval/10);
            j++;
            auxStorage[j]=toChar(numval%10);
            j++; i++;
        } else {
            auxStorage[j]=cuenta[i];
            j++; i++;
        }
    }
    auxStorage[j]='\0';

    int numero = 98 - resto(auxStorage,97);
    if (numero<10) {
        dcontrolIBAN[0]='0';
        dcontrolIBAN[1]=toChar(numero);
    } else {
        dcontrolIBAN[0]=toChar(numero/10);
        dcontrolIBAN[1]=toChar(numval%10);
    }
    dcontrolIBAN[2]='\0';
}

int main(void)
{
    char cadena[50] = "1234"; //entidad bancaria
    char sucursal[6]    = "5678";
    char cuenta[11]     = "1234567890";
    char digcontrol[3]  = "06";
    char CodigoPais[3]  = "ES";

    strcat(strcat(strcat(cadena,sucursal),digcontrol),cuenta);

    char dcontrolIBAN[3]= "00"; //{'0','0','\0'};

    dcIBAN(cadena,CodigoPais,dcontrolIBAN);

    printf("%s",dcontrolIBAN);

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
    int x, valor;

    //calculo del primer digito de control
    char cadenaAux[3] = {'0','0','\0'};
    x = dcCCCaux(strcat(strcat(cadenaAux,entbancaria),sucursal));
    valor = 11 - (x % 11);
    if      (valor  < 10)   a = toChar(valor);
    else if (valor == 10)   a = '1';
    else                    a = '0';

    //calculo del segundo digito de control
    x = dcCCCaux(cuenta);
    valor = 11 - (x % 11);
    if      (valor  < 10)   b = toChar(valor);
    else if (valor == 10)   b = '1';
    else                    b = '0';

    //almacenamos los resultados obtenidos
    digcontrol[0] = a;
    digcontrol[1] = b;
}
