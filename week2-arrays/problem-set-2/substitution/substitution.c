#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string file;
bool badNo(int argc);
bool badLen(string arg);
bool badKey(string arg);
bool hasDuplicates(char c, string arg, int start);
bool invalidInputs(int argc, string args);

void get_cipher(string plain, string sub);
int offset(char c);
char cap(char base, char target);

int main(int argc, string argv[]) {
    file = argv[0];
    if (invalidInputs(argc, argv[1])) {
        return 1;
    }
    string plain = get_string("plaintext:  ");
    printf("ciphertext: ");
    get_cipher(plain, argv[1]);

    return 0;
}

void get_cipher(string plain, string sub) {
    char letter;
    for (int i = 0, n = strlen(plain); i < n; i++) {
        if (!isalpha(plain[i])) {
            printf("%c", plain[i]);
            continue;
        }
        printf("%c", cap(plain[i], sub[offset(plain[i])]));
    }
    printf("\n");
}


int offset(char c) {
    char start = c == toupper(c) ? 'A' : 'a';
    return (c - start);
}


char cap(char base, char target) {
    if (base == toupper(base)) {
        return toupper(target);
    }
    return tolower(target);
}


bool badNo(int argc) {
    if (argc < 2 || argc > 2) {
        printf("Usage: %s key\n", file);
        return true;
    }
    return false;
}
bool invalidInputs(int argc, string arg) {
    return (badNo(argc) || badLen(arg) || badKey(arg));
}
bool badLen(string arg) {
    if (strlen(arg) != 26) {
        printf("Key must contain 26 characters.\n");
        return true;
    }
    return false;
}

bool badKey(string arg) {
    for (int i = 0, n = strlen(arg); i < n; i++) {
        if (!isalpha(arg[i]) || hasDuplicates(arg[i], arg, i))
            return true;
    }
    return false;
}

bool hasDuplicates(char c, string arg, int start) {
    for (int j = start + 1; j < 26; j++) {
        if (tolower(arg[start - 1]) == tolower(arg[j])) {
            return true;
        }
    }
    return false;
}