#include <stdio.h>
#include <cs50.h>

//firstly prompt user to select the value betweeen 1 and 8 (both inclusive)
int main(void)
{
    int n;
    do
    {
        n= get_int("Height: ");
    }
    while (n < 1 || n > 8);

//now # will cover a step of pyramid and " " (space) will cover the empty space
    int space;
    int hash;
    for (int i=1; i<=n; i++)
    {
        for (space = n-i; space>0; space--)
        {
            printf(" ");
        }
        for (hash = 1; hash <= i; hash++)
        {
            printf("#");
        }
        printf("\n");
    }
}