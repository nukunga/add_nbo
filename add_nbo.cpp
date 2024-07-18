#include <stddef.h> // for size_t
#include <stdint.h> // for uint8_t
#include <stdio.h> // for printf
#include <netinet/in.h>

int check_4bytes(FILE *file) { // 숫자가 4바이트인지 확인
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (filesize != sizeof(uint32_t)) {
        printf("[!] File must be 4 Bytes\n");
        return 1;
    }
    return 0;
}

int main(int argc, char **argv) {
    uint32_t num1, num2, res;

    if (argc != 3) {
        printf("[!] This program must receive 2 files.\n");
        return 1;
    }

    FILE *f1 = fopen(argv[1], "rb");
    FILE *f2 = fopen(argv[2], "rb");

    if (f1 == NULL || f2 == NULL) { // 정상적으로 파일이 open 되었는지 확인
        printf("[!] This file is in an invalid format.\n");
        if (f1 != NULL) fclose(f1);
        if (f2 != NULL) fclose(f2);
        return 1;
    }

    if (check_4bytes(f1) || check_4bytes(f2)) {
        fclose(f1);
        fclose(f2);
        return 1;
    }

    fread(&num1, sizeof(uint32_t), 1, f1);
    fread(&num2, sizeof(uint32_t), 1, f2);

    num1 = ntohl(num1);
    num2 = ntohl(num2);

    res = num1 + num2;

    printf("%d(%#x) + %d(%#x) = %d(%#x)\n", num1, num1, num2, num2, res, res);

    fclose(f1);
    fclose(f2);

    return 0;
}
