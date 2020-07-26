// libraries needed:
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int num_sentences, num_charact, num_word; // creates the number of sentences, characters and words as global variables

void count_sentences_words_charact(string
                                   text); // declaration of the function that actualizes the number of sentences, characters and words (global variables) in the given text entered by the user
int Coleman_Liau_index(float num_charact_per100,
                       float num_senteces_per100); // declaration of the function that calculates the Coleman-Liau index


int main(void)
{
    string text; // creation of the variable to which the text typed by the user will be assigned
    float num_charact_per100,
          num_senteces_per100; // creation of the variables (floats) to which are going to be assigned the averaged numbers of characters and sentences per 100 words in the given text, respectively
    int grade; // creation of the variable to which is going to be assigned the grade given by Coleman-Liau's algorithm
    text = get_string("Text: "); // promps the user to entered a text

    count_sentences_words_charact(
        text); // function that atualizes the number of sentences, characters and words (global variables) in the given text entered by the user

    num_charact_per100 = ((float) num_charact * 100) / (float)
                         num_word; // assignment of the average number of characters per 100 words in the given text
    num_senteces_per100 = ((float) num_sentences * 100) / (float)
                          num_word; // assignment of the average number of senteces per 100 words in the given text

    grade = Coleman_Liau_index(num_charact_per100,
                               num_senteces_per100); // assignment of the grade determined by the Coleman-Liau's algorithm

    // printing of the grade:
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }

    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }

    else
    {
        printf("Grade %i\n", grade);
    }
}

void count_sentences_words_charact(string text)
// implementation of the function that actualizes the number of sentences, characters and words (global variables) in the given text entered by the
// user
{
    char charact; // creates the variable charact to which is going to be assigned each character (in a for loop) of the given text

    for (int i = 0, n_text = strlen(text); i < n_text; i++)
        // for each i character in the given text
    {
        charact = text[i]; // character i in the given text

        if (charact == '!' || charact == '?' || charact == '.') // characters associated with a termination of a sentence
        {
            num_sentences ++; // increments by 1 the number of sentences in the given text
        }

        if (charact == ' ') // character associated with the separation of words
        {
            num_word ++; // increments by 1 the number of words in the given text
        }

        if (charact >= 'A' && charact <= 'z') // characters associated with all of the possible letters that can exist in a text
        {
            num_charact ++; // increments by 1 the number of characters in the given text
        }

    }

    if (num_charact != 0) // if the text entered by the user has at least 1 character
    {
        num_word ++; // actualizes the correct number of words in the given text by considering that for i spaces between words exists i+1 words
    }
}

int Coleman_Liau_index(float num_charact_per100, float num_senteces_per100)
// implementation of the function that calculates the Coleman-Liau index, based on the number of characters and sentences per 100 words in
// the given text
{
    return round(0.0588 * num_charact_per100 - 0.296 * num_senteces_per100 - 15.8); // rounds to an integer the Coleman-Liau index
}