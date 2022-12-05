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
void backup_data();

int main(){

/*
* * Menu
*/

int option;
char str_option[30];

//Asigning 1 to enter menu
option = 1;
bool database = true;

while(option != 7){
    printf("\n1 : Buscar\n2 : Agregar Alumno\n3 : Eliminar Alumno\n4 : Imprimir Lista de Alumnos\n5 : Imprimir Datos\n6 : Ordenar\n7 : Salir\n\n");

    //Reading as String to avoid errors
    scanf("%s", str_option);

    //Converting String to Int
    option = atoi(str_option);

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

        case 4:
            printf("Imprimir todos los alumnos\n");
            print(0);
            continue;
        case 5:
            printf("Imprimir ultima busqueda\n");
            print(1);
            continue;
        case 6: 
            sort_list();
            continue;
        case 7: 
            printf("Cerrando...\n");
            continue;
        default:
            printf("Opcion no valida\n");
            continue;
    }
}

    //Clear output
    int rm;
    rm = remove("data");
    rm = remove("out");

    return 0;
}

/*
* * Search Function
*/

void search(bool *db, int option){
    char name[30];
    FILE *read = *db ? fopen("database", "rb") : fopen("data", "rb");


    //Checking if file exists
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


    //Printing string according to option
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
    
    //Changing database to data once a search is made
    if(*db){
        *db = false;
    }

    FILE *write = fopen("out", "wb+");
    
    
    student_t student;
    
    bool found = false;


    while(!feof(read)){
        fread(&student, sizeof(student_t), 1, read);

        //Reading break just in case
        fscanf(read, "\n");

        //Checking if student is found and printing it on screen and on file

        switch(option){
            case 1: //Name
                if(strcasecmp(student.name, name) == 0){
                    fwrite(&student, sizeof(student_t), 1, write);
                    printf("%-15s %-6d %-25s %-8d %.2f\n", student.name, student.key, student.bachelor, student.year, student.average);
                    found = true;
                }
                break;
            case 2: //Bachelor
                if(strcasecmp(student.bachelor, name) == 0){
                    fwrite(&student, sizeof(student_t), 1, write);
                    printf("%-15s %-6d %-25s %-8d %.2f\n", student.name, student.key, student.bachelor, student.year, student.average);
                    found = true;
                }
                break;
            case 3: //Year
                if(student.year == (int)number){
                    fwrite(&student, sizeof(student_t), 1, write);
                    printf("%-15s %-6d %-25s %-8d %.2f\n", student.name, student.key, student.bachelor, student.year, student.average);
                    found = true;
                }
                break;
            case 4: //Average
                if(student.average >= number){
                    //fprintf(write, "%s  %d  %s  %d  %.2f\n", student.name, student.key, student.bachelor, student.year, student.average);
                    fwrite(&student, sizeof(student_t), 1, write);
                    printf("%-15s %-6d %-25s %-8d %.2f\n", student.name, student.key, student.bachelor, student.year, student.average);
                    found = true;
                }
                break;
            default:
                break;
        }
    }

    //Checking if student wasn't found and printing it on screen and clearing database boolean

    if(!found){
        printf("No se encontraron resultados de su busqueda\n\nReiniciando Filtros...\n");
        *db = true;
    }

    fclose(read);
    fclose(write);

    //To backup data
    save_data(false);
}

void save_data(bool db){
    FILE *read = fopen("out", "rb");
    FILE *write = db ? fopen("database", "wb+") : fopen("data", "wb+");

    student_t student;

    while(!feof(read)){
        
        fread(&student, sizeof(student_t), 1, read);
        fwrite(&student, sizeof(student_t), 1, write);
        
        //Reading break just in case
        fscanf(read, "\n");

    }

    fclose(read);
    fclose(write);
}

void print(bool data){

    //Checking wich file to read
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

        //Reading break just in case
        fscanf(fp, "\n");
        printf("%-2d : %-15s %-6d %-25s %-8d %.2f\n", count++, student.name, student.key, student.bachelor, student.year, student.average);
    }
}

/*
* * Function to add a student to the database
*/

void add_student(){
    backup_data();
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

/*
* * Remove student from database function
*/

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

        //Reading break just in case
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

/*
* * Function for sorting the database
*/

void sort_list(){

    backup_data();

    printf("¿Que tipo de ordenamiento desea realizar?\n1 : Nombre\n2 : Carrera\n3 : Matricula\n4 : Año\n5 : Promedio\n6 : Regresar\n\n");
    int option;
    scanf("%d", &option);

    if(option == 6){
        return;
    }

    FILE *data = fopen("out", "rb+");

    //Declaring variables to swap
    student_t student;
    student_t minor;

    fseek(data, 0, SEEK_END);

    //Reading last position
    long end = ftell(data), pos = 0, curr;

    //Rewinding file
    rewind(data);
    char type[30];


    //Printing according to option
    switch(option){
        case 1:
            strcpy(type, "Nombre");
            break;
        case 2:
            strcpy(type, "Carrera");
            break;
        case 3:
            strcpy(type, "Matricula");
            break;
        case 4:
            strcpy(type, "Generacion");
            break;
        case 5:
            strcpy(type, "Promedio");
            break;
        default:
            break;
    }

    printf("Ordenando por %s", type);

    //Loop wich will read all the file and swap the minor with the current position
    while(ftell(data) <= end - sizeof(student_t)){

        //Reading student according to position
        fread(&minor,sizeof(student_t), 1, data);

        //Reading current position
        pos = ftell(data);


        //While current position is less than end of file
        while(ftell(data) < end){
            fread(&student, sizeof(student_t), 1, data);
            
            switch(option){

                    //Overwriting minor and current according to positions

                case 1: //Name
                    if(strcasecmp(minor.name, student.name) > 0){
                    

                    //Current position inside loop
                    curr = ftell(data) - sizeof(student_t);

                    //Overwriting minor and current
                    fseek(data, pos - sizeof(student_t), SEEK_SET);
                    fwrite(&student, sizeof(student_t), 1, data);
                    
                    fseek(data, curr, SEEK_SET);
                    fwrite(&minor, sizeof(student_t), 1, data);

                    minor = student;
                    }
                    break;
                case 2: //Bachelor
                    if(strcasecmp(minor.bachelor, student.bachelor) > 0){
                    curr = ftell(data) - sizeof(student_t);
                    fseek(data, pos - sizeof(student_t), SEEK_SET);
                    fwrite(&student, sizeof(student_t), 1, data);
                    
                    fseek(data, curr, SEEK_SET);
                    fwrite(&minor, sizeof(student_t), 1, data);

                    minor = student;
                    }
                    break;
                case 3: //Key
                    if(minor.key > student.key){
                    curr = ftell(data) - sizeof(student_t);
                    fseek(data, pos - sizeof(student_t), SEEK_SET);
                    fwrite(&student, sizeof(student_t), 1, data);
                    
                    fseek(data, curr, SEEK_SET);
                    fwrite(&minor, sizeof(student_t), 1, data);

                    minor = student;
                    }
                    break;
                case 4: //Year
                    if(minor.year > student.year){
                    curr = ftell(data) - sizeof(student_t);
                    fseek(data, pos - sizeof(student_t), SEEK_SET);
                    fwrite(&student, sizeof(student_t), 1, data);
                    
                    fseek(data, curr, SEEK_SET);
                    fwrite(&minor, sizeof(student_t), 1, data);

                    minor = student;
                    }
                    break;
                case 5: //Average
                    if(minor.average > student.average){
                    curr = ftell(data) - sizeof(student_t);
                    fseek(data, pos - sizeof(student_t), SEEK_SET);
                    fwrite(&student, sizeof(student_t), 1, data);
                    
                    fseek(data, curr, SEEK_SET);
                    fwrite(&minor, sizeof(student_t), 1, data);

                    minor = student;
                    }
                    break;
                default: 
                    break;
            }
            
        }

        //Rewinding file according to position saved before
        fseek(data, pos, SEEK_SET);
    }

    fclose(data);

    printf("\nLista ordenada\n");

    //Message to save changes on database
    printf("Desea guardar en la base de datos? (s/n): ");

    char c;
    
    scanf(" %c", &c);

    bool save = c == 's' ? true : false;

    //Save changes on the file selected
    save_data(save);
}

/*
* * Swap function to swap two students
*/

void swap(student_t *a, student_t *b){
    student_t c;
    c = *a;
    *a = *b;
    *b = c;
}

/*
* * Function to backup data on files
*/

void backup_data(){
    FILE *read = fopen("database", "rb");
    FILE *write = fopen("out", "wb+");

    student_t student;

    while(!feof(read)){
        fread(&student, sizeof(student_t), 1, read);
        fwrite(&student, sizeof(student_t), 1, write);
        
        //Reading break just in case
        fscanf(read, "\n");
    }

    fclose(read);
    fclose(write);
}