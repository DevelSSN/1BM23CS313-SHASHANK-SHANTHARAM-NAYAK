#include <stdio.h>
#include <string.h>

#define MAX_MESSAGE_SIZE 1024
#define MAX_POLY_SIZE 33

void xor_with_polynomial(char *data, const char *polynomial, int poly_len) {
    for (int i = 0; i < poly_len; i++) {
        data[i] = (data[i] == polynomial[i]) ? '0' : '1';
    }
}

void crc_calculate(char *message, char *polynomial, int message_len, int poly_len, char *result) {
    char crc[message_len + poly_len - 1];
    memset(crc, '0', sizeof(crc));
    strncpy(crc, message, message_len);

    for (int i = 0; i < message_len; i++) {
        if (crc[i] == '1') {
            xor_with_polynomial(&crc[i], polynomial, poly_len);
        }
    }

    strncpy(result, &crc[message_len], poly_len - 1);
    result[poly_len - 1] = '\0';
}

void append_crc(char *message, char *polynomial, int message_len, int poly_len) {
    char crc[poly_len];
    crc_calculate(message, polynomial, message_len, poly_len, crc);
    strcat(message, crc);
}

int check_crc(char *message, char *polynomial, int poly_len) {
    int message_len = strlen(message) - poly_len + 1;
    char crc[poly_len];
    crc_calculate(message, polynomial, message_len, poly_len, crc);

    for (int i = 0; i < poly_len - 1; i++) {
        if (crc[i] != '0') {
            return 0;
        }
    }

    return 1;
}

int main() {
    char message[MAX_MESSAGE_SIZE];
    char polynomial[MAX_POLY_SIZE];

    printf("Enter the message (binary string): ");
    fgets(message, MAX_MESSAGE_SIZE, stdin);
    message[strcspn(message, "\n")] = 0;

    printf("Enter the CRC polynomial (binary string): ");
    fgets(polynomial, MAX_POLY_SIZE, stdin);
    polynomial[strcspn(polynomial, "\n")] = 0;

    int message_len = strlen(message);
    int poly_len = strlen(polynomial);

    printf("\nOriginal message: %s\n", message);
    
    append_crc(message, polynomial, message_len, poly_len);
    
    printf("Message with CRC appended: %s\n", message);

    if (check_crc(message, polynomial, poly_len)) {
        printf("CRC is valid. Message received correctly.\n");
    } else {
        printf("CRC is invalid. Message has errors.\n");
    }

    return 0;
}
