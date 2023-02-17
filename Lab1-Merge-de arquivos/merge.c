// Author: Paulo Filipe Moreira da Silva
// Date: 16th of February 2023
// Description: Merges two files in alphabetical order (See README.md for more information)

// Usage: ./merge.exe , then type the names of the files to be merged

// If the file is not in the same directory as the executable, you need to specify the path as an argument
// Example: If the folder is in the same directory as the executable: ./merge.exe ./TestFiles/
// Example: If the folder is not in the same directory as the executable: ./merge.exe /home/user/TestFiles/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


// for ever macro
#define ever (;;)


bool file_error(FILE *file, char *file_name);


int main(int argc, char *argv[]){
    // Get user input for file names
    char *file1 = malloc(100);
    char *file2 = malloc(100);
    scanf("%s", file1);
    scanf("%s", file2);

    // Check for invalid input
    if (file1 == NULL || file2 == NULL){
        printf("Invalid input\n");
        return 1;
    }

    // If the user specified the path as an argument, use it
    if (argc == 2){
        char *path = argv[1];
        char *temp = malloc(strlen(path) + strlen(file1) + 1);
        strcpy(temp, path);
        strcat(temp, file1);
        free(file1);
        file1 = temp;

        temp = malloc(strlen(path) + strlen(file2) + 1);
        strcpy(temp, path);
        strcat(temp, file2);
        free(file2);
        file2 = temp;
    }

    // Open files
    FILE *fileptr1 = fopen(file1, "rb");
    if (file_error(fileptr1, file1) == true) return 1;

    FILE *fileptr2 = fopen(file2, "rb");
    if (file_error(fileptr2, file2) == true) return 1;

    // Create output file name
    char *output = malloc(strlen(file1) + strlen(".merge") + 1);
    strcpy(output, file1);
    strcat(output, ".merge");

    // Open output file
    FILE *output_file = fopen(output, "wb");
    if (file_error(output_file, output) == true) return 1;

    for ever{
        long long int size1, size2;
        char *str1, *str2;
        // Reads the size of the string from file 1
        if (fread(&size1, sizeof(long long int), 1, fileptr1) != 1){ // If it can't read, it means it reached the end of the file
            while (fread(&size2, sizeof(long long int), 1, fileptr2) == 1){ // So, copy the rest of the file 2 to the output file
                fwrite(&size2, sizeof(long long int), 1, output_file);
                str2 = malloc(size2);
                fread (str2, sizeof(char), size2, fileptr2)     ;
                fwrite(str2, sizeof(char), size2, output_file);
                free(str2);
            }
            break;
        }

        // Reads the string from file 1
        str1 = malloc(size1);
        fread(str1, sizeof(char), size1, fileptr1);

        if (fread(&size2, sizeof(long long int), 1, fileptr2) != 1){
            fwrite(&size1, sizeof(long long int), 1, output_file);
            fwrite(str1, sizeof(char), size1, output_file);
            free(str1);
            while (fread(&size1, sizeof(long long int), 1, fileptr1) == 1){
                fwrite(&size1, sizeof(long long int), 1, output_file);
                str1 = malloc(size1);
                fread (str1, sizeof(char), size1, fileptr1)   ;
                fwrite(str1, sizeof(char), size1, output_file);
                free(str1);
            }
            break;
        }

        str2 = malloc(size2);
        fread(str2, sizeof(char), size2, fileptr2);

        // Compare the strings
        // If the string from file 1 is smaller or is a number, write it to the output file
        if (strcmp(str1, str2) < 0 || isdigit(str1[0])){ 
            //printf("str1: %s < str2 %s\n", str1, str2);
            fwrite(&size1, sizeof(long long int), 1, output_file);
            fwrite(str1, sizeof(char), size1, output_file);
            free(str1);
            // Bring the pointer of file 2 back to the position of the string
            fseek(fileptr2, -sizeof(long long int), SEEK_CUR);
            fseek(fileptr2, -size2, SEEK_CUR); 
        } else {
            //printf("str2: %s < str1\n", str2, str1);
            fwrite(&size2, sizeof(long long int), 1, output_file);
            fwrite(str2, sizeof(char), size2, output_file);
            free(str2);

            fseek(fileptr1, -sizeof(long long int), SEEK_CUR);
            fseek(fileptr1, -size1, SEEK_CUR);
        }
    }

    // Closes files and frees memory
    fclose(fileptr1 );
    fclose(fileptr2 );
    free  (output);

    return 0;
}


// Function that checks if the file was opened correctly, returning true if there is an error
bool file_error(FILE *file, char *file_name){
    if (file == NULL){
        printf("Error opening file %s\n", file_name);
        return true;
    }
    return false;
}


// I hope it works