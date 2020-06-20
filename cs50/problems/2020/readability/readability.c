//TODO: make program better by ignoring the relaxations given in question
//like consider a sentence as anything ending with . or ? or !
//and consider no multiple spaces in a row.

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_letters(string s);
int count_words(string s);
int count_sentences(string s);

int main(void)
{
    string text = get_string("Text: ");


    //TODO: check if these funcs exist
    int num_letters = count_letters(text);
    int num_words = count_words(text);
    int num_sentences = count_sentences(text); //TODO: check if count(str, substr) exists

    float l = ((100 * (float)num_letters) / num_words);
    float s = ((100 * (float)num_sentences) / num_words);

    int index =  round(0.0588 * l - 0.296 * s - 15.8);
    
    //conditional printing
    if (index > 1)
    {
        printf("Grade ");
        if (index < 16)
        {
            printf("%i\n", index);
        }
        else
        {
            printf("16+\n");
        }
    }
    else
    {
        printf("Before Grade 1\n");
    }

}


int count_letters(string s)
{
    //iterate over the characters of the input string, if character is alphabetical, increment count
    int count = 0;
    for (int i = 0, l = strlen(s); i < l; i++)
    {
        if (isalpha(s[i]))
        {
            count++;
        }
    }
    return count;
}


int count_words(string s)
{
    //iterate over the characters of the input string, if character is a space, increment count
    int count = 0;
    for (int i = 0, l = strlen(s); i < l; i++)
    {
        if (s[i] == ' ')
        {
            count++;
        }
    }
    return count + 1;
}


int count_sentences(string s)
{
    //iterate over the characters of the input string, if character is a sentence ending punctuation, increment count
    int count = 0;
    for (int i = 0, l = strlen(s); i < l; i++)
    {
        if (s[i] == '.' || s[i] == '?' || s[i] == '!')
        {
            count++;
        }
    }
    return count;
}
