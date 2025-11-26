/**
 * @file log_system.c
 * @brief Implements a simple logging system writing to a file.
 *
 * This program demonstrates:
 * 1. Appending to a file ("a" mode)
 * 2. Getting current time using time.h
 * 3. Variadic functions for formatted logging
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>

#define LOG_FILE "app.log"

typedef enum {
    INFO,
    WARNING,
    ERROR
} LogLevel;

/**
 * @brief Get current timestamp string.
 */
void get_timestamp(char *buffer) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, 20, "%Y-%m-%d %H:%M:%S", t);
}

/**
 * @brief Write a log message to the file.
 */
void log_message(LogLevel level, const char *format, ...) {
    FILE *fp = fopen(LOG_FILE, "a");
    if (!fp) {
        perror("Failed to open log file");
        return;
    }

    char timestamp[20];
    get_timestamp(timestamp);

    const char *level_str;
    switch (level) {
        case INFO:    level_str = "INFO"; break;
        case WARNING: level_str = "WARN"; break;
        case ERROR:   level_str = "ERROR"; break;
        default:      level_str = "UNKNOWN"; break;
    }

    fprintf(fp, "[%s] [%s] ", timestamp, level_str);

    va_list args;
    va_start(args, format);
    vfprintf(fp, format, args);
    va_end(args);

    fprintf(fp, "\n");
    fclose(fp);
}

int main() {
    printf("Logging messages to %s...\n", LOG_FILE);

    log_message(INFO, "Application started.");
    log_message(INFO, "User %s logged in.", "admin");
    log_message(WARNING, "Disk space low: %d%% remaining.", 15);
    log_message(ERROR, "Connection failed to database %s.", "db_prod");
    log_message(INFO, "Application shutting down.");

    printf("Done. Check %s for content.\n", LOG_FILE);
    
    // Display content for verification
    printf("\n--- Log Content ---\n");
    FILE *fp = fopen(LOG_FILE, "r");
    if (fp) {
        char ch;
        while ((ch = fgetc(fp)) != EOF) putchar(ch);
        fclose(fp);
    }
    
    // Cleanup
    remove(LOG_FILE);

    return 0;
}
