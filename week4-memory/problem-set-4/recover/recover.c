#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const int BLOCK_SIZE = 512;


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s IMAGE\n", argv[0]);
        return 1;
    }

    char *img = argv[1];
    FILE *file = fopen(img, "r");
    if (file == NULL)
    {
        printf("Cannot read image %s\n", img);
        return 1;
    }

    unsigned char buffer[512];
    FILE *new_img = NULL;
    int no_of_img = -1;
    bool begin = false;
    // the +1 is for the nul character generated by sprintf
    char *filename = malloc(sizeof(char) * strlen("###.jpg") + 1);

    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        bool new_jpeg = (buffer[0] == 0xff && buffer[1] == 0xd8
                         && buffer[2] == 0xff && buffer[3]);

        // means just look at the first four bits of this 8-bit byte
        // and set the remaining four bits to 0
        // i.e. 0xe1, 0xe2, 0xe3... all become 0xe0
        // using bitwise and (&)
        bool fourth_byte = (buffer[3] & 0xf0) == 0xe0; // since fourth byte is 0xe0 to 0xef

        if (new_jpeg && fourth_byte) // then for sure it's a start of a new jpeg image
        {
            if (no_of_img > -1)
            {
                fclose(new_img);
            }

            begin = true;
            no_of_img++;
            // filenames -> ###.jpg [starting with 000.jpg]
            sprintf(filename, "%03i.jpg", no_of_img);
            new_img = fopen(filename, "w");
        }

        if (begin)
        {
            fwrite(buffer, 1, BLOCK_SIZE, new_img);
        }

    }

    free(filename);
    fclose(file);
    fclose(new_img);
    return 0;
}