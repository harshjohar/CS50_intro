#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

int main(void)
{
    int countw = 0, i;
    int counts = 0, j;
    int countl = 0, k;
    char p[1000];

//prompt the text from user
    printf("Text: ");
    scanf("%[^\n]", p);

//counting number of words
    for (i = 0 ; p[i] != '\0'; i++)
    {
        if (p[i] == ' ' && p[i + 1] != ' ')

        countw++;

    }

//counting number of sentences
    for (j = 0 ; p[j] != '\0'; j++)
    {
        if (p[j] == '.' || p[j] == '?' || p[j] == '!')

        counts++;

    }

//counting number of letters
    for (k = 0 ; p[k] != '\0'; k++)
    {
        if ((p[k] >= 'a' && p[k] <= 'z') || (p[k] >= 'A' && p[k] <= 'Z'))

        countl++;

    }

//counting number of letters per 100 words
    float L = ((float)countl / (countw + 1)) * 100;

//counting number of sentences per 100 words
    float S = ((float)counts / (countw + 1)) * 100;

//readability
    int R = round((0.0588 * L) - (0.296 * S) - 15.8);

//grade
    if (R < 1)
    printf("Before Grade 1\n");

    else if (R >= 1 && R <= 16)
    printf("Grade %i\n", R);

    else
    printf("Grade 16+\n");
}




