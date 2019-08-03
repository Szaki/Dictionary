#ifndef MISC_H_INCLUDED
#define MISC_H_INCLUDED

typedef struct Arrays {
    char **src;
    char **tgt;
} Arrays;

void filename(char *array, char *array2);

int wordcount(FILE *fp);

void load(Arrays *t, FILE *fp, int db);

void freeup(Arrays t, int db);

void end(FILE *fp, char *string, Arrays k, int db);

void writeback(FILE *fp, char *string, int db, Arrays k);

#endif // MISC_H_INCLUDED
