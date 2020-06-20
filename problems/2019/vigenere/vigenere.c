#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


//Prototype functions.
bool valid_key(int c, string v[]);
char make_cipher(int k, char pt);
int shift(char c);



int main(int argc, string argv[])
{
   /*checks if valid argument is given
   continues if valid, otherwise tells 
    correct input format*/
    if (valid_key(argc, argv))
    {
        string ptxt = get_string("plaintext: ");
        string keyword = argv[1];
        int len_keyword = strlen(keyword);
        
        printf("ciphertext: ");
        //iterate over each character in plaintext
        for (int i = 0, l = strlen(ptxt), j = 0; i < l; i++)
        {
            char ch = ptxt[i];
            if (isalpha(ch))
            {    
                int key = shift(keyword[j % len_keyword]);
                printf("%c", make_cipher(key, ch));
                j++;
             }
            else
            {
                printf("%c", ch);
            }
        }
        printf("\n");                    
    }
    else
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
}



bool valid_key(int c, string v[])
{
    if (c != 2)
    {
        return false;
    }
    for (int i = 0, l = strlen(v[1]); i < l; i++)
    {
        if (isalpha(v[1][i]) == false)
        {
            return false;
        }
    }
    return true;
  
}



int shift(char c)
{
    if (isupper(c))
    {
        return (c - 65);
    }
    else
    {
        return (c - 97);
    }
}

                    
char make_cipher(int k, char pt)
{
    if (isupper(pt))
    {

        return ((((pt - 65) + k) % 26) + 65);
    }
    else
    {
        return ((((pt - 97) + k) % 26) + 97);
    }  
}


