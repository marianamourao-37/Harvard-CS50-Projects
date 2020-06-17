// libraries imported
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SIZE_BYTES 512 // global variable to which is assigned the bytes chunk's size
typedef uint8_t BYTE; // definition of a data type (byte, 8 bits)

int main(int argc, char *argv[])
{
    if (argc != 2) // if name of the forensic image wasn't entered or it was entered more than 2 strings
        // (program's name and name of the forensic image)
    {
        printf("Please enter the name of a forensic image from which to recover JPEGs");
        return 1;
    }

    FILE *forensic_file = fopen(argv[1], "r"); // creates and opens for reading the forensic file

    if (forensic_file == NULL) // if an error occurred
    {
        return 1; // ends program
    }

    FILE *new_file = NULL; // creates and initiates the file that is going to store each image contained in the forensic file
    BYTE *bytes =  malloc(SIZE_BYTES * sizeof(
                              BYTE)); // previously allocates memory specifically for the chunk of bytes that are going to be stored in the new_file

    if (bytes == NULL) // if an error occurred
    {
        fclose(forensic_file); // close the file that was previously opened
        return 2; // ends program
    }

    int count_file = -1; // initiates the variable for the image counter (involved to specify the new_file's name)
    char name_new_jpg[8]; // creates the sequence of chars, including the null terminator, involved to specify the new_file's name (ex: '000.jpg')

    while (fread(bytes, sizeof(bytes), 1, forensic_file) == 1)  // while chunks of size sizeof(bytes) are successfully read
    {
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && bytes[3] >= 0xe0 && bytes[3] <= 0xef) // pattern of three bytes and
            // fourth byte’s first four bits that demarcates the start of a new JPEG image
        {
            count_file ++; // incrementation by 1

            if (count_file > 0) // if it isn't the first JPEG in the forensic file
            {
                fclose(new_file); // close previous file opened, that contains a complete JPEG image recovered
            }

            sprintf(name_new_jpg, "%03d.jpg", count_file); // new JPEG image name
            new_file = fopen(name_new_jpg, "w"); // open new JPEG image for writing

            if (new_file == NULL) // if the operation wasn't succefully done it
            {
                fclose(forensic_file); // close the forensic file
                free(bytes); // free the memory allocated for the chunk of bytes to be written
                return 2; // ends program
            }

            fwrite(bytes, sizeof(bytes), 1, new_file); // writes in the new JPEG file the chunk of bytes
        }

        else if (count_file >= 0) // if it wasn't found the pattern that demarcates the start of a new JPEG image
        {
            fwrite(bytes, sizeof(bytes), 1, new_file); // // writes in the same JPEG file previously opend the chunk of bytes
        }
    }

    fclose(forensic_file); // close forensic file
    fclose(new_file); // close last JPEG image file
    free(bytes); // free the memory allocated for the chunk of bytes to be written
}
