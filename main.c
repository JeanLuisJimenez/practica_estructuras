#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_EVAL 10
#define MAX_STUDENTS 20

typedef struct {
    char description[100];
    float pecentGrade;
    float value;
} Evaluation;

typedef struct {
    float percentGrade;
    char letter;
} Grade;

typedef struct {
    int id;
    char name[100];
    Evaluation evaluations[MAX_EVAL];
    Grade grade;
} Student;

void print_grades(const Student *students, const Evaluation *evaluations, int studentsNum, int evalsNum);
void regist_evaluations(Evaluation *evaluationsint, int *evalsNum);
void grade_letter(Grade *grade);
void regist_students(Student *students, const Evaluation *evaluations, int *studentsNum, int evalsNum);
void menu(int *option, Student *students, Evaluation *evaluations, int *studentsNum, int *evalsNum);
void consult_student(Student *students, int studentsNum, int evalsNum);

int main()
{
    Student students[MAX_STUDENTS];
    Evaluation evaluations[MAX_EVAL];
    int evalsNum, studentsNum, option;

    menu(&option, students, evaluations, &studentsNum, &evalsNum);
    return 0;
}

void menu(int *option, Student *students, Evaluation *evaluations, int *studentsNum, int *evalsNum) {
    system("@cls||clear");
    printf("\nMENU:\n\t1- Introducir informacion de estudiantes.\n\t2- Ingresar evaluaciones.\n\t3- Imprimir calificaciones.\n\t4- Consultar estudiante.\n\n\t0- Salir\n\n");
    scanf("%d", option);
    getchar();
    system("@cls||clear");
    switch (*option) {
        case 0:
            break;
        case 1:
            regist_students(students, evaluations, studentsNum, *evalsNum);

            menu(option, students, evaluations, studentsNum, evalsNum);
            break;
        case 2:
            regist_evaluations(evaluations, evalsNum);
            menu(option, students, evaluations, studentsNum, evalsNum);
            break;
        case 3:
            print_grades(students, evaluations, *studentsNum, *evalsNum);
            menu(option, students, evaluations, studentsNum, evalsNum);
            break;
        case 4:
            consult_student(students, *studentsNum, *evalsNum);
            menu(option, students, evaluations, studentsNum, evalsNum);
            break;
        default:
            printf("Intente con una opcion valida (Presione enter para continuar)\n");
            getchar();
            menu(option, students, evaluations, studentsNum, evalsNum);
            break;
    }
}

void consult_student(Student *students, int studentsNum, int evalsNum) {
    int option;
    printf("Seleccione el estudiante que quiere consultar (No.):\n");
    printf("\nNo.\t| ID\t| Nombre\n");
    for (int studentsCount = 0; studentsCount < studentsNum; studentsCount++) {
        printf("\n%d\t| %d\t| %s\n", studentsCount + 1, students[studentsCount].id, students[studentsCount].name);
    }

    scanf("%d", &option);
    getchar();
    system("@cls||clear");

    printf("\tID: %d\n\tNombre: %s\n\n\t", students[option - 1].id, students[option - 1].name);

    for (int evalsCount = 0; evalsCount < evalsNum; evalsCount++) {
        printf("\tCalif. %s valor en calificacion final: %.2f%c\n", students[option - 1].evaluations[evalsCount].description, students[option - 1].evaluations[evalsCount].value, 37);
        printf("\tCalif. %s calificacion en base a 100%c: %.2f%c\n", students[option - 1].evaluations[evalsCount].description, 37, students[option - 1].evaluations[evalsCount].pecentGrade, 37);
        printf("\tCalif. %s calificacion en base a %.2f%c: %.2f%c\n\n", students[option - 1].evaluations[evalsCount].description, students[option - 1].evaluations[evalsCount].value, 37, (students[option - 1].evaluations[evalsCount].value / 100) * students[option - 1].evaluations[evalsCount].pecentGrade, 37);
    }

    printf("\tCalif. final: %d (%c)", students[option - 1].grade.percentGrade, students[option - 1].grade.letter);

    printf("\nPresione enter para continuar\n");
    getchar();
}

void print_grades(const Student *students, const Evaluation *evaluations, int studentsNum, int evalsNum) {
    printf("%50s\n\n%10s%10s%20s", "Informe de Calificaciones", "No.", "ID", "Nombre");
    for (int evalsCount = 0; evalsCount < evalsNum; evalsCount++) {
        printf("%*s\t%*.2f%c", 10, evaluations[evalsCount].description, 10, evaluations[evalsCount].value, 37);
    }
    printf("%10sCalif. Final\n\n", " ");

    for (int studentsCount = 0; studentsCount < studentsNum; studentsCount++) {
        printf("%10d%10d%20s\t", studentsCount, students[studentsCount].id, students[studentsCount].name);
            for (int evalsCount = 0; evalsCount < evalsNum; evalsCount++) {
                printf("%7.2f%c%11.2f%c", students[studentsCount].evaluations[evalsCount].pecentGrade, 37, (students[studentsCount].evaluations[evalsCount].value / 100) * students[studentsCount].evaluations[evalsCount].pecentGrade, 37);
            }
        printf("%11.2f%5c\n", students[studentsCount].grade.percentGrade, students[studentsCount].grade.letter);
    }

    printf("\nPresione enter para continuar\n");
    getchar();
}

void regist_evaluations(Evaluation *evaluations, int *evalsNum) {
    printf("Digite cantidad de evaluaciones: ");

    float total = 0;
    scanf("%d", evalsNum);
    getchar();

    int count;
    for (count = 0; count < *evalsNum; count++) {

        Evaluation evaluation;
        char *pch;
        printf("\nDescripción Evaluación No.%d: ", count + 1);
        fgets(evaluation.description, 99, stdin);
        pch = strchr(evaluation.description, 10);

        if (pch != NULL) *pch = '\0';

        printf("Porcentaje Evaluación No.%d: ", count + 1);
        scanf("%f", &(evaluation.value));
        getchar();
        if ((count == *evalsNum - 1 && evaluation.value + total != 100) || evaluation.value + total > 100) {
            count--;
            printf("\nLa suma de todas las evaluaciones deben ser 100%, la suma de sus calificaciones es %.2f, intente de nuevo\n", total);
            continue;
        }

        evaluations[count] = evaluation;

        total += evaluation.value;
    }

    printf("\nPresione enter para continuar\n");
    getchar();
}

void grade_letter(Grade *grade) {
    if (grade->percentGrade >= 90) grade->letter = 'A';
    else if (grade->percentGrade >= 80) grade->letter = 'B';
    else if (grade->percentGrade >= 70) grade->letter = 'C';
    else if (grade->percentGrade >= 60) grade->letter = 'D';
    else grade->letter = 'F';
}

void regist_students(Student *students, const Evaluation *evaluations, int *studentsNum, const int evalsNum) {
    if (!evalsNum) {
        printf("Primero agrega algunas evaluaciones. (Presione enter para continuar)\n");
        getchar();

        return;
    }

    printf("\nDigite cantidad de estudiantes: ");

    float total = 0;
    scanf("%d", studentsNum);

    int studentsCount, evalsCount;
    getchar();
    for (studentsCount = 0; studentsCount < *studentsNum; studentsCount++) {
        printf("\nEstudiante No.%d", studentsCount + 1);
        Student student;
        printf("\nID: ");
        scanf("%d", &(student.id));

        getchar();

        int *pch;
        printf("Nombre: ");
        fgets(student.name, 99, stdin);
        pch = strchr(student.name, 10);

        if (pch != NULL) *pch = '\0';

        Evaluation evaluation;
        for (evalsCount = 0, total = 0; evalsCount < evalsNum; evalsCount++) {

            strncpy(evaluation.description, evaluations[evalsCount].description, 99);
            evaluation.value = evaluations[evalsCount].value;

            printf("Calif. %s: ", evaluation.description);
            scanf("%f", &(evaluation.pecentGrade));

            total += (evaluation.value / 100) * evaluation.pecentGrade;
            student.evaluations[evalsCount] = evaluation;
        }
        getchar();

        student.grade.percentGrade = total;

        grade_letter(&(student.grade));

        students[studentsCount] = student;
    }

    printf("\nPresione enter para continuar\n");
    getchar();
}
