#include <stdio.h>
#include <cs50.h>

//hello world
int main(void)
{
    string n= get_string("What is your name?\n");
    
    printf("hello, %s\n", n);
}