#include <stdio.h>
#include <stdbool.h>

typedef struct{
    char name[30];
    char bachelor[30];
    int year;
    int key;
    float average;
} student_t;

int main(){
    FILE *bin = fopen("database", "wb+");
    FILE *db = fopen("database.txt", "r");
    student_t student;
    while(!feof(db)){
        fscanf(db, "%s%d%s%d%f\n", student.name, &student.key, student.bachelor, &student.year, &student.average);
        fprintf(bin, "%s  %d  %s  %d  %.2f\n", student.name, student.key, student.bachelor, student.year, student.average);
    }

    fclose(bin);
    fclose(db);


}