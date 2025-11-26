/**
 * @file csv_parser.c
 * @brief Parses a simple CSV file.
 *
 * This program demonstrates:
 * 1. Reading lines using fgets
 * 2. Tokenizing strings using strtok
 * 3. Parsing structured text data
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int main() {
    // Create a dummy CSV file for demonstration
    FILE *fp = fopen("data.csv", "w");
    if (fp) {
        fprintf(fp, "ID,Name,Age,City\n");
        fprintf(fp, "1,John Doe,30,New York\n");
        fprintf(fp, "2,Jane Smith,25,London\n");
        fprintf(fp, "3,Bob Johnson,40,Paris\n");
        fclose(fp);
    }

    // Open the CSV file
    fp = fopen("data.csv", "r");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int row_count = 0;

    printf("Reading CSV file:\n");
    printf("--------------------------------------------------\n");
    printf("%-5s %-20s %-5s %-15s\n", "ID", "Name", "Age", "City");
    printf("--------------------------------------------------\n");

    while (fgets(line, sizeof(line), fp)) {
        row_count++;
        // Skip header
        if (row_count == 1) continue;

        // Remove newline
        line[strcspn(line, "\n")] = 0;

        // Tokenize
        char *token;
        char *rest = line;
        
        // ID
        token = strtok_r(rest, ",", &rest);
        char *id = token ? token : "";

        // Name
        token = strtok_r(rest, ",", &rest);
        char *name = token ? token : "";

        // Age
        token = strtok_r(rest, ",", &rest);
        char *age = token ? token : "";

        // City
        token = strtok_r(rest, ",", &rest);
        char *city = token ? token : "";

        printf("%-5s %-20s %-5s %-15s\n", id, name, age, city);
    }

    fclose(fp);
    // Cleanup
    remove("data.csv");

    return 0;
}
