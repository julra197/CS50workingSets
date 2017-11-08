#import <stdio.h>
#import <stdbool.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // check number of cli arguments
    if(argc != 2)
    {
        fprintf(stderr, "Format: ./recover datafile");
        return 1;
    }
    //remember file name
    char *input = argv[1];

    //open file stream and check for success
    FILE *inptr = fopen(input, "r");
    if(inptr == NULL)
    {
        fprintf(stderr, "Cannot open file");
        return 2;
    }

    //Create a buffer for file reading
    unsigned char buffer[512];
    //A boolean to determine the beginning of the first jpg
    _Bool found = false;
    //File name of destination files
    char filename[7];
    //Counter of found imgs
    int imgNo = 0;
    //Create a file name for the first img
    sprintf(filename, "%03i.jpg", imgNo);
    //Create the first destination file
    FILE *img = fopen(filename, "w");
    if(img==NULL)
    {
        fprintf(stderr, "Cannot create destination file");
        return 3;
    }
    //Iterate while the buffer size is equal to 512, if it is smaller -> End of file
    while(fread(&buffer, 1, 512, inptr) == 512)
    {
        //check if a new file starts
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //check whether the first file already exists
            if(found)
            {
                //close the previous img file
                fclose(img);
                //update filename
                sprintf(filename, "%03i.jpg", imgNo);
                //increment img counter for next file name
                imgNo++;
                //create a new img file
                img = fopen(filename, "w");
                if(img==NULL)
                {
                    fprintf(stderr, "Cannot create destination file");
                    return 3;
                }
                //write bytes to the new file
                fwrite(&buffer, 1, 512, img);

            }
            //create write the first file
            else
            {
                //increment img counter for next file name
                imgNo++;
                //start writing the first block into the first file
                fwrite(&buffer, 1, 512, img);
            }
            //img found to true
                found = true;
        }
        //write the next 512 bytes of a file
        else if(found)
        {
            //wirte bytes to the file
            fwrite(&buffer, 1, 512, img);
        }
    }
    //wirte the remaining bytes to the last file
    fwrite(&buffer, 1, 512, img);
    //close the source file
    fclose(inptr);
    //close the last output file
    fclose(img);
    //success
    return 0;
}