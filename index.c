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
        //printf("%s\t\t\t%d\t\t\t%s\t\t\t%d\t\t\t%.2f\n", student.name, student.key, student.bachelor, student.year, student.average);
        //fwrite(&student, sizeof(student_t), 1, bin);
    }

    fclose(bin);
    fclose(db);


}