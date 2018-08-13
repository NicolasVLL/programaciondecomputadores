/*
 * Basado en el c�digo: http://labix.org/snippets/labsolver
 * gcc -Wall -o 05_laberinto 05_laberinto.c
 */

#include <stdio.h>
#include <stdbool.h>

#define VACIO     ' ' // nunca se ha visitado
#define PRINCIPIO 'P'
#define FIN       'F'
#define VISITADO  '.' // visitado pero no es el camino correcto
#define OK        'o' // camino correcto
#define COL 29        // numero de columnas del laberinto
#define FIL 18        // numero de filas del laberinto

char L[FIL][COL] =
{
    "#############################",
    "P #     #   #   #     #   # #",
    "# # ### ### # # # ### ### # #",
    "# # #       # # # #       # #",
    "# #   ### # # # #   ### # # #",
    "# # # #   # # # # # #   # # F",
    "#   # # # # # #   # # # # # #",
    "##### # # # # ##### # # # # #",
    "#     # # #   #     # # #   #",
    "# #     #   # # #     #   # #",
    "# # ### ### # # # ### ### # #",
    "# # #       # # # #       # #",
    "# #   ### # # # #   ### # # #",
    "# # # #   # # # # # #   # # #",
    "#   # # # # # #   # # # # # #",
    "##### # # # # ##### # # # # #",
    "#     # # #   #     # # #   #",
    "#############################"
};

void imprimir_laberinto();
bool resolver();

int main(void)
{
    if (resolver())
        imprimir_laberinto();
    else
        puts("El laberinto no tiene soluci�n");

    return 0;
}

// Imprime el laberinto
void imprimir_laberinto()
{
    int i, j;
    for (i=0; i<FIL; i++)
    {
        for (j=0; j<COL; j++)
            putchar(L[i][j]);
        putchar('\n');
    }
}

// Busca el comienzo del laberinto y desde all� la b�squeda
bool resolver()
{
// Pararse en la posici�n (i,j) moverse desde esta posici�n hacia la derecha,
// abajo, izquierda o arriba, en ese orden
// Esta funci�n devuelve TRUE si a partir de la posici�n "i,j" se pudo mover
// y devuelve FALSE si se lleg� al final de un camino y se tuvo que devolver
    bool _resolver(int i, int j) // funci�n anidada
    {
        // si se sali� del laberinto, devolverse una posici�n e intentar de nuevo
        if (!(j>=0 && j<COL && i>=0 && i<FIL)) return false;

        char posactual = L[i][j];

        switch(posactual)
        {
        case VACIO:
        case PRINCIPIO:
            if (posactual==VACIO) L[i][j] = VISITADO; // se�alar que aqu� estuve
            if (_resolver(i, j+1) || // mover derecha  (recuerde como se usa el)
                _resolver(i+1, j) || // mover abajo    (OR en lenguaje C)
                _resolver(i, j-1) || // mover izquierda
                _resolver(i-1, j))   // mover arriba
            {
                // si en alguna de las posiciones circundantes hay salida, decir
                // que hubo exito y retornar un verdadero
                if (posactual==VACIO) L[i][j] = OK;
                return true; // movimiento OK
            }
            else // en ninguna de las posiciones alrededor hay salida, por lo
                 // que toca devolverse una posici�n e intentar de nuevo
                return false;
            // break;
        case FIN: // el fin
        case OK:  // camino correcto
            return true; // terminamos!!!
            // break;
        default: //'#', '.' = muro o camino falso
            return false;
        }
    }

    int i, j;
    bool encontrado = false;

    // Se buscan "los" principios del laberinto. De alg�n lado tenemos que partir
    for (i=0; i<FIL; i++)
        for (j=0; j<COL; j++)
            if (L[i][j] == PRINCIPIO)
                encontrado |= _resolver(i,j);

    return encontrado;
}
