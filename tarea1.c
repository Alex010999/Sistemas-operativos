#include <stdio.h>

int main()
{
    //Vars definitions
    int area, length, width;

    //Ask for the variables values
    printf("\nIntroduce el valor de la altura del rectangulo: ");
    scanf("%d", &length);
    
    printf("\nIntroduce el valor del ancho del rectangulo: ");  
    scanf("%d", &width);

    //do the operation
    area = length * width;

    //show the result
    printf("\nEl area del rectangulo es: %d", area);

}