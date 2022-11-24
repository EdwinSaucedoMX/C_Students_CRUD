#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct{
    char name[30];
    char bachelor[30];
    int year;
    int key;
    float average;
} student_t;

int main(){
    FILE *bin = fopen("database", "rb");
    FILE *db = fopen("database.txt", "r");
    student_t *student = (student_t*)malloc(sizeof(student_t));
    char *line;
    char space;
    while(!feof(bin)){
        //fscanf(db, "%s%d%s%d%f", student->name, &student->key, student->bachelor, &student->year, &student->average);
        
        fread(student, sizeof(student_t), 1, bin);
        fscanf(bin, "\n");
        //fread(&space, 1, 1, bin);
        printf("%s %d %s %d %.2f\n", student->name, student->key, student->bachelor, student->year, student->average);
        //fwrite(student, sizeof(student_t), 1, bin);
        
        //fscanf(db, "\n");
    }

    free(student);
    fclose(bin);
    fclose(db);


}