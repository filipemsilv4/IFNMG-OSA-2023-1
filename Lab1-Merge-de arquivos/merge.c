// Author: Paulo Filipe Moreira da Silva
// Date: 16th of February 2023
// Description: Merges two files in alphabetical order (See README.md for more information)

// Usage: ./merge.exe , then input of the files to be merged

// If the files are not in the same directory as the program, and both are in the same directory, you can specify the path as an argument when running the program in order to avoid having to input the path twice
// Example: If the folder with the files is in the same directory as the program: ./merge.exe ./TestFiles/
// Example: If the folder with the files is not in the same directory as the program: ./merge.exe /home/user/TestFiles/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


// for ever macro
#define ever (;;)


FILE* open_file(char *file_name, char *mode);


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
    FILE *fileptr1 = open_file(file1, "rb");
    FILE *fileptr2 = open_file(file2, "rb");

    // Create output file name
    char *output = malloc(strlen(file1) + strlen(".merge") + 1);
    strcpy(output, file1);
    strcat(output, ".merge");

    // Open output file
    FILE *output_file = open_file(output, "wb");

    for ever{
        long long int size1, size2;
        char *str1, *str2;
        // Reads the size of the string from file 1
        if (fread(&size1, sizeof(long long int), 1, fileptr1) != 1){ // If it can't read, it means it reached the end of the file
            while (fread(&size2, sizeof(long long int), 1, fileptr2) == 1){ // So, copy the rest of the file 2 to the output file
                fwrite(&size2, sizeof(long long int), 1, output_file);
                str2 = malloc(size2);
                fread (str2, sizeof(char), size2, fileptr2)   ;
                printf("%s\n", str2);
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
                printf("%s\n", str1);
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
            printf("%s\n", str1);
            fwrite(&size1, sizeof(long long int), 1, output_file);
            fwrite(str1, sizeof(char), size1, output_file);
            free(str1);
            // Bring the pointer of file 2 back to the position of the string
            fseek(fileptr2, -sizeof(long long int), SEEK_CUR);
            fseek(fileptr2, -size2, SEEK_CUR); 
        } else {
            printf("%s\n", str2);
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
    fclose(output_file);
    free  (output);
    free  (file1) ;
    free  (file2) ;

    return 0;
}

// Function that opens a file and checks if it was opened correctly, returns a pointer to the file
FILE* open_file(char *file_name, char *mode){
    FILE *file = fopen(file_name, mode);
    
    if (file == NULL){
        printf("Error opening file %s\n", file_name);
        exit(1);
    }

    return file;
}


// I hope it works