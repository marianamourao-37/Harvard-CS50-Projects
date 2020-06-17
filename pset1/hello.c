#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("Please enter your name:"); // it prompts the user for typing its name
    printf("hello, %s\n", name); // personalized hello printing, by specifying the user's name 
}
