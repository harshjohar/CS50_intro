#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float dollar;
    do
    {
     dollar= get_float("Change Owed: ");
    }
    while (dollar<0);

    int cent = round(dollar*100);
//quarters=25
//dimes=10
//nickles=5
//pennies=1

//number of quarters
    int q= floor(cent/25);

//number of dimes
    int l1= (cent-25*q);
    int d= floor(l1/10);

//number of nickles
    int l2= (l1-10*d);
    int n= floor(l2/5);

//number of pennies
    int l3= (l2-5*n);
    int p= floor(l3);

//total number of minimum coins required
    int t= (q+d+n+p);

    printf("%i\n", t);
}