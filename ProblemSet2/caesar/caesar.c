//inspired from try3c.c

#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

//prompting a command line argument

int main(int argc, string argv[])
{
    int key;
    string d;
    bool valid = false;

    if(argc>2 || argc<2)
    {
        valid= false;
    }

    else
    {
     d= argv[1];

     for(int i=0; i<strlen(d); i++)
     {
         int c= (int) d[i];

         if(c<48 || c>57)
         {
             valid= false;
         }

         else
         {
             key= atoi(d);
             valid= true;
         }
     }
    }
// checked that the command line argument is an integer!
    if(valid==true)
    {
        string text= get_string("plaintext: ");  //input
        printf("ciphertext: ");  //output heading

        for(int i=0; i<strlen(text); i++)
        {
            int c= (int) text[i];
            int s= c + key;
            char s2;

            //capital letters

            if(c>=65 && c<=90)
            {
              if(s<90)
              {
                  s2= (char) s;
                  printf("%c", s2);
              }

              else
              {
                  while(s>90)
                  {
                      s= s-26;
                  }
                  s2= (char) s;
                  printf("%c", s2);
              }
            }

            //small letters
            else if(c>=97 && c<=122)
            {
              if(s<122)
              {
                  s2= (char) s;
                  printf("%c", s2);
              }

              //other characters
              else
              {
                  while(s>122)
                  {
                      s= s-26;
                  }
                  s2= (char) s;
                  printf("%c", s2);
              }
            }

            else
            {
                s2= (char) c;
                printf("%c", s2);
            }
        }

        printf("\n");
        return 0;
    }

    else if (valid == false)
    {
        printf("Usage: ./caeser key\n");
        return 1;
    }
}