#include<stdio.h>

typedef enum { Nuevo, Abrir, Guardar, Cerrar, Salir } opciones;

int main(void)
{
   opciones caso;

   caso = Guardar;
   switch (caso)
   {
   case Nuevo:   printf("\nSe ha seleccionado la opci�n Nuevo\n\n");
      break;
   case Abrir:   printf("\nSe ha seleccionado la opci�n Abrir\n\n");
      break;
   case Salir:   printf("\nSe ha seleccionado la opci�n Salir\n\n");
      break;
   }

   return 0;
}

