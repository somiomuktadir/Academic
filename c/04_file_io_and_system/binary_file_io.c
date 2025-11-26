/**
 * @file binary_file_io.c
 * @brief Reads and writes structs to a binary file.
 *
 * This program demonstrates:
 * 1. fwrite and fread for binary data
 * 2. Serializing and deserializing structures
 * 3. Random access using fseek (optional, but good to know)
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    float gpa;
} Student;

int main() {
    const char *filename = "students.dat";
    Student students[] = {
        {1, "Alice", 3.8},
        {2, "Bob", 3.5},
        {3, "Charlie", 3.9}
    };
    int count = sizeof(students) / sizeof(students[0]);

    // Write to binary file
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("Error opening file for writing");
        return 1;
    }

    size_t written = fwrite(students, sizeof(Student), count, fp);
    printf("Wrote %zu records to %s\n", written, filename);
    fclose(fp);

    // Read from binary file
    fp = fopen(filename, "rb");
    if (!fp) {
        perror("Error opening file for reading");
        return 1;
    }

    Student read_students[3];
    size_t read = fread(read_students, sizeof(Student), count, fp);
    printf("Read %zu records from %s:\n", read, filename);

    for (int i = 0; i < read; i++) {
        printf("ID: %d, Name: %s, GPA: %.2f\n", 
               read_students[i].id, read_students[i].name, read_students[i].gpa);
    }

    fclose(fp);
    
    // Cleanup
    remove(filename);

    return 0;
}
