#include <cs50.h>
#include <stdio.h>

void hash(int number_hashes_row, int height_pyramid); // prints the hashes for each row 

int main(void)
{
    int height; // creates an integer variable, relative to the pyramid's height 
    do // guarantees a first iteration that prompts the user to specify the pyramid's height
    {
        height = get_int("Please select the pyramid's height: "); // prompts the user to specify the pyramid's height
    }  
    while (height <= 0 || height > 8); // if the value assigned isn't positive, prompts the user again  
        
    for (int i = 0; i < height; i++) // for each row, starting from up to down in the pyramid geometry 
    {
        hash(i, height); // prints the hashes for each row 
    }
}

void hash(int number_hashes_row, int
          height_pyramid) // function that receives as inputs a specific row of the pyramid and the pyramid's height, and executes the printing of that same row 
{    
    for (int j = 0; j < height_pyramid;
         j++) // for each j column in the specified row, until it reaches the gap in the pyramid(the distance between the beginning of the row and the gap is 
              // the same for all rows, being a constant equivalent to the pyramid's height)
    {
        if (j < height_pyramid - (number_hashes_row + 1)) // specific for each row, the initiation of the block printing differs
        {
            printf(" "); // prints black spaces until it reaches the blocks to be printing
        }
        else 
        {
            printf("#"); // block printing
        }
    }
    printf("  "); // prints the gap in the middle of the pyramid 

    for (int l = 0; l <= number_hashes_row;
         l++) // for each l column in the specified row of the pyramid's second part, until all blocks are printing (as many as the row number, incremented by 1 because of the convention to start the counting at 0)
    {
        printf("#"); // block printing
    }
    printf("\n"); // passes to the next row automatically
}
