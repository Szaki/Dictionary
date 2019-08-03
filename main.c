#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

int main() {
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);

    int a = 0;
    char lang[10];
    char lang2[10];
    printf("Please choose a menu option: \n\n");
    printf("(1) Create new file\n(2) Select existing file\n(3) Exit\n\n");
    do {
        scanf("%d", &a);
        switch (a) {
            case 1:
                filename(lang, lang2);
                create(lang);
                printf("\n");
                main();
                break;
            case 2:
                filename(lang, lang2);

                char c;
                int b = 0;

                FILE *fp;
                fp = fopen(lang, "r+t");

                if (fp == NULL) {
                    printf("\nNo such file found. Would you like to create it? Y/N\n");
                    getchar();
                    do {
                        scanf("%c", &c);
                        switch (c) {
                            case 'Y':
                                create(lang);
                                printf("\n");
                                main();
                                break;
                            case 'N':
                                printf("\n");
                                main();
                                break;
                            default:
                                printf("\nInvalid input.\n\n");
                                break;
                        };
                    } while (c != 'Y' && c != 'N');
                } else {
                    printf("\nFile loaded. You have the following options:\n\n");
                    printf("(1) Search\n(2) Edit\n(3) Main menu\n\n");
                    do {
                        scanf("%d", &b);
                        switch (b) {
                            case 1:
                                printf("Searching mode. When you're done, press enter.\n");
                                getchar();
                                search(fp);
                                printf("\n");
                                fclose(fp);
                                main();
                                break;
                            case 2:
                                printf("Editing mode. When you're done, press enter.\n");
                                getchar();
                                edit(fp, lang);
                                printf("\n");
                                fclose(fp);
                                main();
                                break;
                            case 3:
                                getchar();
                                main();
                                break;
                            default:
                                getchar();
                                printf("Invalid input.\n\n");
                                break;
                        };
                    } while (b != 1 && b != 2 && b != 3);
                };
                break;
            case 3:
                break;
            default:
                printf("Invalid input.\n\n");
                break;
        }
    } while (a != 1 && a != 2 && a != 3);
    return 0;
};
