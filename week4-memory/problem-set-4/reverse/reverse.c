#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);
void reverse_audio(FILE *in, FILE *out, int end_header, const int BLOCK_SIZE);


int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: %s input.wav output.wav\n", argv[0]);
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("Error opening file %s\n", argv[1]);
        return 1;
    }

    // Read header into an array
    // TODO #3
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, infile);

    // Use check_format to ensure WAV format
    // TODO #4
    if (!check_format(header))
    {
        fclose(infile);
        printf("File %s is in wrong format, only .wav is supported", argv[1]);
        return 2;
    }

    // Open output file for writing
    // TODO #5
    FILE *outfile = fopen(argv[2], "w");
    if (outfile == NULL)
    {
        fclose(infile);
        printf("Input is not a WAV file.");
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&header, sizeof(WAVHEADER), 1, outfile);

    // Use get_block_size to calculate size of block
    // TODO #7
    const int BLOCK_SIZE = get_block_size(header);

    // Write reversed audio to file
    // TODO #8
    reverse_audio(infile, outfile, sizeof(WAVHEADER), BLOCK_SIZE);

    fclose(infile);
    fclose(outfile);
    return 0;
}

int check_format(WAVHEADER header)
{
    const BYTE expected[4] = { 'W', 'A', 'V', 'E' };
    int size = sizeof(header.format) / sizeof(BYTE);

    for (int i = 0; i < size; i++)
    {
        if (header.format[i] != expected[i])
        {
            return 0;
        }
    }

    return 1;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return header.numChannels * (header.bitsPerSample / 8);
}

void reverse_audio(FILE *in, FILE *out, int end_header, const int BLOCK_SIZE)
{
    BYTE buffer[BLOCK_SIZE];
    fseek(in, BLOCK_SIZE, SEEK_END);

    while (ftell(in) - BLOCK_SIZE > end_header)
    {
        fseek(in, -2 * BLOCK_SIZE, SEEK_CUR);
        fread(buffer, BLOCK_SIZE, 1, in);
        fwrite(buffer, BLOCK_SIZE, 1, out);
    }
}