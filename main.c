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

void search(bool *db, int option);
void save_data(bool db);
void print(bool data);
void add_student();
void remove_student();
void sort_list();
void duplicate_db();
bool is_on_data(char *name);

int main(){

/*
* * Menu
*/

int option;
char str_option[30];
option = 1;
bool database = true;

while(option != 10){
    printf("\n1 : Buscar\n2 : Agregar Alumno\n3 : Eliminar Alumno\n7 : Imprimir Lista de Alumnos\n8 : Imprimir Datos\n9 : Ordenar\n10 : Salir\n\n");

    scanf("%s", str_option);
    option = atoi(str_option);
    if(option == 0){
        option = str_option[0] == '0' ? option : -1;
    }

    printf("\n");

    switch(option){
        case 1:
            printf("¿Que tipo de busqueda desea realizar?\n1 : Carrera\n2 : Nombre\n3 : Año\n4 : Promedio\n5 : Regresar\n%s", database ? "" : "6 : Reiniciar Filtro de Busqueda\n\n");
            scanf("%d", &option);
            switch(option){
                case 1:
                    printf("\nBusqueda por carrera\n");
                    search(&database, 2);
                    break;
                case 2:
                    printf("\nBusqueda por nombre\n");
                    search(&database, 1);
                    break;

                case 3:
                    printf("\nBusqueda por año\n");
                    search(&database, 3);
                    break;
                case 4:
                    printf("\nBusqueda por promedio\n");
                    search(&database, 4);
                    break;
                case 5:
                    printf("\nRegresando...\n");
                    break;
                case 6:
                    if(!database){
                        printf("Reiniciando el Filtro\n");
                        database = true;
                    }else{
                        printf("No hay filtro activo\n");
                    }
                    break;
                default:
                    printf("\nOpcion no valida\n");
                    break;
            }
            continue;

        case 2:
            printf("Agregar Alumno/s\n");
            add_student();
            continue;

        case 3:
            printf("Eliminar Alumno\n");
            remove_student();
            continue;

        case 7:
            printf("Imprimir todos los alumnos\n");
            print(0);
            continue;
        case 8:
            printf("Imprimir datos\n");
            print(1);
            continue;
        case 9: 
            sort_list();
            continue;
        case 10: 
            printf("Cerrando...\n");
            continue;
        default:
            printf("Opcion no valida\n");
            continue;
    }
}

    //Limpiar Archivos
    int rm;
    rm = remove("data");
    rm = remove("out");

    return 0;
}

void search(bool *db, int option){
    char name[30];
    FILE *read = *db ? fopen("database", "rb") : fopen("data", "rb");

    if(!read){
        printf("No se encontraron datos almacenados\n");
        return;
    }
    



    switch(option){
        case 1:
            printf("Ingrese el nombre de/los alumnos: ");
            break;
        case 2:
            printf("Ingrese la carrera: ");
            break;
        case 3:
            printf("Ingrese el año: ");
            break;
        case 4:
            printf("Ingrese el promedio minimo: ");
            break;
    }


    scanf("%s", name);
    float number = atof(name);

    switch(option){
        case 1:
            printf("\nEstudiantes llamados %s\n\n", name);
            break;
        case 2:
        case 3:
            printf("\nEstudiantes de %s\n\n", name);
            break;
        case 4:
            printf("\nEstudiantes con promedio igual o mayor a %.2f\n\n", number);
            break;
    }
    
    
    if(*db){
        *db = false;
    }

    FILE *write = fopen("out", "wb+");
    
    
    student_t student;
    
    bool found = false;


    while(!feof(read)){
        fread(&student, sizeof(student_t), 1, read);
        fscanf(read, "\n");


        switch(option){
            case 1:
                if(strcasecmp(student.name, name) == 0){
                    fwrite(&student, sizeof(student_t), 1, write);
                    printf("%s  %d  %s  %d  %.2f\n", student.name, student.key, student.bachelor, student.year, student.average);
                    found = true;
                }
                break;
            case 2:
                if(strcasecmp(student.bachelor, name) == 0){
                    fwrite(&student, sizeof(student_t), 1, write);
                    printf("%s  %d  %s  %d  %.2f\n", student.name, student.key, student.bachelor, student.year, student.average);
                    found = true;
                }
                break;
            case 3:
                if(student.year == (int)number){
                    fwrite(&student, sizeof(student_t), 1, write);
                    printf("%s  %d  %s  %d  %.2f\n", student.name, student.key, student.bachelor, student.year, student.average);
                    found = true;
                }
                break;
            case 4:
                if(student.average >= number){
                    //fprintf(write, "%s  %d  %s  %d  %.2f\n", student.name, student.key, student.bachelor, student.year, student.average);
                    fwrite(&student, sizeof(student_t), 1, write);
                    printf("%s  %d  %s  %d  %.2f\n", student.name, student.key, student.bachelor, student.year, student.average);
                    found = true;
                }
                break;
            default:
                break;
        }
    }

    if(!found){
        printf("No se encontraron resultados de su busqueda\n\nReiniciando Filtros...\n");
        *db = true;
    }

    fclose(read);
    fclose(write);

    save_data(false);
}

void save_data(bool db){
    FILE *read = fopen("out", "rb");
    FILE *write = db ? fopen("database", "wb+") : fopen("data", "wb+");

    student_t student;

    while(!feof(read)){
        
        fread(&student, sizeof(student_t), 1, read);
        fwrite(&student, sizeof(student_t), 1, write);
        fscanf(read, "\n");

    }

    fclose(read);
    fclose(write);
}

void print(bool data){
    FILE *fp = !data ? fopen("database", "rb") : fopen("out", "rb");
    
    if(!fp){
        printf("No se encontraron datos almacenados\n");
        return;
    }
    
    student_t student;
    int count = 1;
    printf("\n%s\n\n", data ? "Datos de busqueda" : "Base de datos");

    while(!feof(fp)){
        fread(&student, sizeof(student_t), 1, fp);
        fscanf(fp, "\n");
        printf("%d:  %s  %d  %s  %d  %.2f\n", count++, student.name, student.key, student.bachelor, student.year, student.average);
    }
}

void add_student(){
    duplicate_db();
    FILE *out = fopen("out", "ab");

    student_t student;

    printf("¿Cuantos alumnos desea agregar? ");
    int n;
    scanf("%d", &n);
    while(n--){
        printf("Nombre: ");
        scanf("%s", student.name);
        printf("Matricula: ");
        scanf("%d", &student.key);
        printf("Carrera: ");
        scanf("%s", student.bachelor);
        printf("Generacion: ");
        scanf("%d", &student.year);
        printf("Promedio: ");
        scanf("%f", &student.average);
        fwrite(&student, sizeof(student_t), 1, out);
    }
    
    fclose(out);

    save_data(true);
    printf("\nEstudiante agregado\n");
}

void remove_student(){
    char name[30];
    printf("Ingrese el nombre de el/los estudiante/s a eliminar: ");
    scanf("%s", name);

    FILE *db = fopen("database", "rb");
    FILE *out = fopen("out", "wb+");

    student_t student;

    bool found = false;

    while(!feof(db)){
        fread(&student, sizeof(student_t), 1, db);
        fscanf(db, "\n");

        if(strcasecmp(student.name, name) != 0){
            fwrite(&student, sizeof(student_t), 1, out);
        }else{
            found = true;
        }
        
    }

    fclose(out);
    fclose(db);

    if(found){
        save_data(true);
        printf("\nEstudiante/s eliminado/s\n");
    }else{
        printf("\nNo se encontraron estudiantes\n");
    }
}

void sort_list(){

    duplicate_db();

    FILE *data = fopen("out", "rb+");
    student_t student;
    student_t minor;

    fseek(data, 0, SEEK_END);

    long end = ftell(data), pos = 0, curr;
    rewind(data);

    while(ftell(data) <= end - sizeof(student_t)){
        fread(&minor,sizeof(student_t), 1, data);
        pos = ftell(data);
        while(ftell(data) < end){
            fread(&student, sizeof(student_t), 1, data);
            
            if(strcasecmp(minor.name, student.name) > 0){
                curr = ftell(data) - sizeof(student_t);
                fseek(data, pos - sizeof(student_t), SEEK_SET);
                fwrite(&student, sizeof(student_t), 1, data);
                
                fseek(data, curr, SEEK_SET);
                fwrite(&minor, sizeof(student_t), 1, data);

                minor = student;
            }
        }
        //printf("Minor : %s\n", student.name);

        fseek(data, pos, SEEK_SET);
    }
    fclose(data);

    printf("\nLista ordenada\n");


    printf("Desea guardar en la base de datos? (s/n): ");

    char c;

    scanf("%c", &c);

    bool save = c == 's' ? true : false;

    save_data(save);
}

void swap(student_t *a, student_t *b){
    student_t c;
    c = *a;
    *a = *b;
    *b = c;
}

bool is_on_data(char *name){
    FILE *fp = fopen("out", "rb");
    student_t student;

    while(!feof(fp)){
        fread(&student, sizeof(student_t), 1, fp);
        fscanf(fp, "\n");

        if(strcasecmp(student.name, name) == 0){
            fclose(fp);
            return true;
        }
    }
    fclose(fp);
    return false;
}

void duplicate_db(){
    FILE *read = fopen("database", "rb");
    FILE *write = fopen("out", "wb+");

    student_t student;

    while(!feof(read)){
        fread(&student, sizeof(student_t), 1, read);
        fwrite(&student, sizeof(student_t), 1, write);

        fscanf(read, "\n");
    }

    fclose(read);
    fclose(write);
}