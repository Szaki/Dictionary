#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "misc.h"

void filename(char *array, char *array2) {
    printf("Please input the language code of the source language: ");
    scanf("%s", array);
    while (strlen(array) != 2) {
        printf("Invalid input.\n\n");
        scanf("%s", array);
    };
    printf("\nPlease input the language code of the target language: ");
    scanf("%s", array2);
    while (strlen(array2) != 2) {
        printf("Invalid input.\n\n");
        scanf("%s", array2);
    };
    strcat(array, "-");
    strcat(array, array2);
    strcat(array, ".txt");
    return;
}

int wordcount(FILE *fp) {
    rewind(fp);
    char c;
    int db = 0;
    while (feof(fp) == 0) {
        c = fgetc(fp);
        if (c == '\n')
            db++;
    }
    rewind(fp);
    return db / 2;
}

void load(Arrays *t, FILE *fp, int db) {
    int i;
    int const srclen = 100;
    int const tgtlen = 1000;

    t->src = (char **) malloc(db * sizeof(char *));
    for (i = 0; i < db; ++i)
        t->src[i] = (char *) malloc(srclen * sizeof(char));

    t->tgt = (char **) malloc(db * sizeof(char *));
    for (i = 0; i < db; ++i)
        t->tgt[i] = (char *) malloc(tgtlen * sizeof(char));

    int x = 0;

    while (feof(fp) == 0) {
        fgets(t->src[x], srclen, fp);
        fgets(t->tgt[x], tgtlen, fp);
        x++;
    };

}

void freeup(Arrays t, int db) {
    int i = 0;
    for (i = 0; i < db; ++i) {
        free(t.src[i]);
    }
    free(t.src);
    for (i = 0; i < db; ++i) {
        free(t.tgt[i]);
    }
    free(t.tgt);
}

void end(FILE *fp, char *string, Arrays k, int db) {
    freeup(k, db);
    free(string);
    fclose(fp);
}

void writeback(FILE *fp, char *string, int db, Arrays k) {
    int i;
    fclose(fp);
    fp = fopen(string, "w+t");
    for (i = 0; i < db; i++) {
        fprintf(fp, k.src[i]);
        fprintf(fp, k.tgt[i]);
    };
}
