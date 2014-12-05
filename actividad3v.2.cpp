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

int main(void)
{

    char entbancaria[5] = "8987";
    char sucursal[6]    = "9876";
    char cuenta[11]     = "8888888888";
    char digcontrol[3] = "";

    dcCCC(entbancaria,sucursal,cuenta,digcontrol);

    printf("%s",digcontrol);


   // cout << dcCCC(cadena) ;



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
        cout << IBAN[i-1];
        if (i % 4 == 0)
            cout << " ";
    }
}

int resto (char cadena[], int divisor) {
    int r = 0;
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
        resultado += (toInt(cadena[i])*exp2)%11;
        exp2       = exp2*2;
    }
    resultado %= 11;
    cout << "Resultado: " << resultado << endl;
    return resultado;
}

void dcCCC (char entbancaria[], char sucursal[], char cuenta[], char digcontrol[]) {
    char a, b;

    /*calculo del segundo digito de control*/
    int x = dcCCCaux(cuenta);
    int valor = 11 - (x % 11);
    if      (valor  < 10)   b = toChar(valor);
    else if (valor == 10)   b = '1';
    else                    b = '0';

    /*calculos el primer digito de control*/
    char cadenaAux[3] = {'0','0','\0'};
    x = dcCCCaux(strcat(strcat(cadenaAux,entbancaria),sucursal));
    valor = 11 - (x % 11);
    if      (valor  < 10)   a = toChar(valor);
    else if (valor == 10)   a = '1';
    else                    a = '0';

    /*almacenamos los resultados obtenisdos*/
    digcontrol[0]= a;
    digcontrol[1]= b;
}
