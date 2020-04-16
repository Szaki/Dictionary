#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "features.h"
#include "misc.h"

void create(char *lang)
{
    char *words;
    int i = 1;
    char c;
    int srclen = 100;
    int tglen = 1000;

    FILE *fp;

    if (fopen(lang, "rt") != NULL)
    {
        printf("This file already exists. Do you want to overwrite it? Y/N\n");
        getchar();
        do
        {
            scanf("%c", &c);
            switch (c)
            {
            case 'Y':
                break;
            case 'N':
                getchar();
                return;
                break;
            default:
                getchar();
                printf("Invalid input.\n\n");
                break;
            };
        } while (c != 'Y' && c != 'N');
    };

    fp = fopen(lang, "wt");

    printf("\nCreated file. Editing mode.\nWhen you're done, input an enter instead of a word.\n\n");
    getchar();

    for (;;)
    {
        printf("Input the %d. word in the source language: ", i);
        words = (char *)malloc(srclen * sizeof(char));
        gets(words);
        if (strlen(words) == 0)
        {
            printf("File saved.\n");
            fclose(fp);
            return;
        }
        fprintf(fp, words);
        fprintf(fp, "\n");
        free(words);
        printf("Input the meanings of the %d. word: ", i);
        words = (char *)malloc(tglen * sizeof(char));
        gets(words);
        fprintf(fp, words);
        fprintf(fp, "\n");
        free(words);
        printf("\n");
        i++;
    };
    fclose(fp);
}

void search(FILE *fp)
{
    rewind(fp);
    wordlen(fp);
    int db = wordlen(fp);
    int i = 0;
    int const srclen = 100;
    Arrays k;

    load(&k, fp, db);

    char *searched;
    searched = (char *)malloc(srclen * (sizeof(char)));

    printf("Enter the word you're looking for: ");
    gets(searched);
    if (strlen(searched) == 0)
    {
        befejez(fp, searched, k, db);
        return;
    }

    strcat(searched, "\n");

    bool haveresult = false;

    for (i = 0; i < db; i++)
    {
        if (strcmp(k.src[i], searched) == 0)
        {
            printf("Meanings of the word: %s\n", k.tgt[i]);
            haveresult = true;
            break;
        };
    };

    if (haveresult == false)
    {
        printf("No result.\n\n");
    };

    search(fp);
};

void edit(FILE *fp, char *string)
{
    rewind(fp);
    wordlen(fp);
    int db = wordlen(fp);
    int const srclen = 100;
    int const tglen = 1000;

    Arrays k;
    load(&k, fp, db);

    int i = 0;

    char *newword;
    char c;

    printf("\nInput the new word in the source language: ");
    newword = (char *)malloc(srclen * sizeof(char));
    gets(newword);
    if (strlen(newword) == 0)
    {
        printf("\nFile edited.\n");
        befejez(fp, newword, k, db);
        return;
    }

    strcat(newword, "\n");
    bool haveresult = false;

    for (i = 0; i < db; i++)
    {
        if (strcmp(k.src[i], newword) == 0)
        {
            printf("This word already exists in the dictionary. Do you want to overwrite it or delete it? Y/N\n");
            do
            {
                scanf("%c", &c);
                switch (c)
                {
                case 'Y':
                    getchar();
                    free(newword);
                    printf("Enter the word in the source language or nothing to delete: ");
                    newword = (char *)malloc(srclen * sizeof(char));
                    gets(newword);
                    if (strlen(newword) == 0)
                    {
                        strcpy(k.src[i], "\0");
                        strcpy(k.tgt[i], "\0");
                        printf("Sz trlve.\n");
                        break;
                    }
                    else
                    {
                        strcat(newword, "\n");
                        strcpy(k.src[i], newword);
                        free(newword);
                        printf("Enter the meanings of the word: ");
                        newword = (char *)malloc(tglen * sizeof(char));
                        gets(newword);
                        strcat(newword, "\n");
                        strcpy(k.tgt[i], newword);
                        free(newword);
                        printf("Word edited.\n");
                    };
                    break;
                case 'N':
                    getchar();
                    break;
                default:
                    getchar();
                    printf("Invalid input.\n\n");
                    break;
                };
            } while (c != 'Y' && c != 'N');
            haveresult = true;
            writeback(fp, string, db, k);
            freeup(k, db);
            break;
        };
    };

    if (haveresult == false)
    {
        fprintf(fp, newword);
        free(newword);
        printf("Enter the meanings of the word to be added: ");
        newword = (char *)malloc(tglen * sizeof(char));
        gets(newword);
        fprintf(fp, newword);
        fprintf(fp, "\n");
        free(newword);
        freeup(k, db);
    };
    edit(fp, string);
};
