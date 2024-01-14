#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void edit_line(char* buffer, int current_line)
{
    // Search for the char '\n' at the start of the line and go to the next char
    for (int i = 0; i < current_line; i++)
    {
        buffer = strchr(buffer, '\n') + 1;
    }

    // Search for the end of the line and skip to the next line
    char* line_end = strchr(buffer, '\n');

    // Save the rest of the line in the saved buffer
    char saved[1024] = { 0 };
    strcpy(saved, line_end);

    // Read user input to overwrite the current line
    printf("Enter new text for line %d: ", current_line);
    scanf(" %[^\n]", buffer); // Use %[^\n] to read until newline

    // Append the saved line to the buffer
    strcpy(buffer + strlen(buffer), saved);
}

int main(int argc, char** argv)
{
    // Scan for the file path
    printf("Set the path of the file: ");
    char file_path[100];
    scanf("%s", file_path);

    char close = 'n';
    do {
        // Open the file
        FILE* fp = fopen(file_path, "r");
        //check if file-path is null
        if (fp == NULL)
        {
            printf("Error opening the file.\n");
            return 1;
        }
        //define a buffer
        char buffer[1024] = {0};
        // Read the file content into the buffer
        fread(buffer, 1024, 1, fp);
        // Close the file
        fclose(fp);

        // Print the content of the file
        printf("Contents: \n%s\n", buffer);
        // Set the current line to edit
        int current_line = 0;
        printf("Choose the line to edit. Starts at 0: ");
        scanf("%d", &current_line);

        // Edit the current line
        edit_line(buffer, current_line);

        // Open the file for writing
        fp = fopen(file_path, "w");
        // Write the content of the buffer, using the length of the buffer
        fwrite(buffer, strlen(buffer), 1, fp);
        // Close the file
        fclose(fp);
        //prompt for continuing editing
        printf("Do you want to continue editing? (y/n): ");
        scanf(" %c", &close);
    } while (close == 'y');
    
    return 0;
}
