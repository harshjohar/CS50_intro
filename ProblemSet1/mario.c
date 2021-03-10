#include <stdio.h>

int main(void)
{
    int h;
    do
    {
        printf("Height: ");
        scanf("%i", &h);
    }
    while (h < 1 || h > 8);
//and the story begins    
    for (int i = 1; i <= h; i++)
    {
        for (int j = h - i - 1; j >= 0; j--)
        {
            printf(" ");
        }
        //left side 
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }
        
        printf("  ");
        //right side
        for (int q = 1; q <= i; q++)
        {
            printf("#");
        }
        printf("\n");  //next line
    }
}