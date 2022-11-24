#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    char name[30];
    char bachelor[30];
    int year;
    int key;
    float average;
} student_t;

void search_bachelor(bool *db);
void search_year(bool *db);
void search_name(bool *db);
void search_average(bool *db);
void save_data(bool db);

int main(){

//char line[70];

/* float average;

while(!feof(fp2)){
    fscanf(fp2, "%s%d%s%d%f", student.name, &student.key, student.bachelor, &student.year, &student.average);
    printf("%s%d%s%d%.2f", student.name, student.key, student.bachelor, student.year, student.average);
    fwrite(&student, sizeof(struct student),  1, fp2);
} */

/*
* * Menu
*/

int option;

option = 1;
bool database = true;

while(option){
    printf("\n0 : Salir\n1 : Buscar por Carrera\n2 : Buscar por Año\n3 : Buscar por Promedio\n4 : Buscar por nombre\n7 : Reiniciar Filtro de Busqueda\n\n");

    scanf("%d", &option);

    printf("\n");

    switch(option){
        case 0: 
            printf("Cerrando...\n");
            continue;
        case 1:
            printf("Buscar por Carrera\n");
            search_bachelor(&database);
            continue;
        case 2:
            printf("Buscar por Año\n");
            search_year(&database);
            continue;
        case 3:
            printf("Buscar por Promedio\n");
            search_average(&database);
            continue;
        case 4:
            printf("Buscar por Nombre\n");
            search_name(&database);
            continue;
        case 7:
            printf("Reiniciando el Filtro\n");
            database = true;
            continue;
        default:
            printf("Opcion no valida\n");
            continue;
    }
}

    //Limpiar Archivos
    FILE *tmp;
    tmp = fopen("data", "wb+");
    fclose(tmp);
    tmp = fopen("out", "wb+");
    fclose(tmp);

    return 0;
}

/*
* * Buscar por Nombre
*/

void search_name(bool *db){
    char name[30];
    
    printf("Ingrese el nombre del alumno: ");
    scanf("%s", name);

    
    //printf("\nBuscando alumnos llamados %s...\n", name);

    FILE *read = *db ? fopen("database", "rb") : fopen("data", "rb");
    
    if(*db){
        *db = false;
    }

    FILE *write = fopen("out", "wb+");
    
    
    student_t student;
    
    bool found = false;


    while(!feof(read)){
        fscanf(read, "%s%d%s%d%f\n", student.name, &student.key, student.bachelor, &student.year, &student.average);

        if(strcmp(student.name, name) == 0){

            //fprintf(write, "%s%d  %s  %d  %.2f\n", student.name, student.key, student.bachelor, student.year, student.average);
            
            fwrite(&student, sizeof(student_t), 1, write);
            printf("%s  %d  %s  %d  %.2f\n", student.name, student.key, student.bachelor, student.year, student.average);
        
            found = true;
        }
    }

    if(!found){
        printf("No se encontro alumnos con ese nombre\n");
    }

    fclose(read);
    fclose(write);

    save_data(false);
}

/*
* * Buscar por carrera
*/

void search_bachelor(bool *db){
    char name[30];
    
    printf("Ingrese el nombre de la carrera: ");
    scanf("%s", name);

    FILE *read = *db ? fopen("database", "rb") : fopen("data", "rb");
    
    if(*db){
        *db = false;
    }

    FILE *write = fopen("out", "wb+");
    
    
    student_t student;
    
    bool found = false;


    while(!feof(read)){
        fscanf(read, "%s%d%s%d%f\n", student.name, &student.key, student.bachelor, &student.year, &student.average);

        if(strcmp(student.bachelor, name) == 0){

            //fprintf(write, "%s  %d  %s  %d  %.2f\n", student.name, student.key, student.bachelor, student.year, student.average);

            fwrite(&student, sizeof(student_t), 1, write);
            printf("%s  %d  %s  %d  %.2f\n", student.name, student.key, student.bachelor, student.year, student.average);
        
            found = true;
        }
    }

    if(!found){
        printf("\bNo se encontro la carrera\n");
    }

    fclose(read);
    fclose(write);

    save_data(false);
}

/*
* * Buscar por generacion
*/

void search_year(bool *db){
    int year;
    
    printf("Ingrese el año: ");
    scanf("%d", &year);

    FILE *read = *db ? fopen("database", "rb") : fopen("data", "rb");
    FILE *write = fopen("out", "wb+");
    
    if(*db){
        *db = false;
    }
    
    student_t student;
    
    bool found = false;

    printf("\nEstudiantes de %d\n", year);
    while(!feof(read)){
        fscanf(read, "%s%d%s%d%f\n", student.name, &student.key, student.bachelor, &student.year, &student.average);

        if(student.year == year){
            //fprintf(write, "%s  %d  %s  %d  %.2f\n", student.name, student.key, student.bachelor, student.year, student.average);
            fwrite(&student, sizeof(student_t), 1, write);
            printf("%s  %d  %s  %d  %.2f\n", student.name, student.key, student.bachelor, student.year, student.average);
        
            found = true;
        }
    }

    if(!found){
        printf("No se encontro la generacion");
    }

    printf("\n");

    fclose(read);
    fclose(write);

    save_data(false);
}

/*
* * Buscar por promedio
*/

void search_average(bool *db){
    float min;
    
    printf("Ingrese el promedio minimo: ");
    scanf("%f", &min);

    FILE *read = *db ? fopen("database", "rb") : fopen("data", "rb");
    FILE *write = fopen("out", "wb+");
    
    if(*db){
        *db = false;
    }
    
    student_t student;
    
    bool found = false;

    printf("\nEstudiantes con promedio igual o mayor a %.2f\n", min);
    while(!feof(read)){
        fscanf(read, "%s%d%s%d%f\n", student.name, &student.key, student.bachelor, &student.year, &student.average);

        if((int) student.average >= (int) min){
            //fprintf(write, "%s  %d  %s  %d  %.2f\n", student.name, student.key, student.bachelor, student.year, student.average);
            fwrite(&student, sizeof(student_t), 1, write);
            printf("%s  %d  %s  %d  %.2f\n", student.name, student.key, student.bachelor, student.year, student.average);
        
            found = true;
        }
    }

    if(!found){
        printf("No se encontro alumnos con con promedio igual o mayor a %.2f", min);
    }

    printf("\n");

    fclose(read);
    fclose(write);

    save_data(false);
}

void save_data(bool db){
    FILE *read = fopen("out", "rb");
    FILE *write = db ? fopen("database", "wb+") : fopen("data", "wb+");

    student_t student;

    while(!feof(read)){
        
        fscanf(read, "%s%d%s%d%f\n", student.name, &student.key, student.bachelor, &student.year, &student.average);
        //fprintf(write, "%s  %d  %s  %d  %.2f\n", student.name, student.key, student.bachelor, student.year, student.average);
        fwrite(&student, sizeof(student_t), 1, write);

    }

    fclose(read);
    fclose(write);
}