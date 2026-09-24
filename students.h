#ifndef STUDENTS_H
#define STUDENTS_H

#include <stdbool.h>

#define STUDENTS_FILE "data/students.csv"

typedef struct {
    char matricula[64];
    char nome[256];
} Student;

/* CRUD */
bool add_student(const char *matricula, const char *nome);
bool find_student(const char *matricula, Student *out);
bool update_student(const char *matricula, const char *novo_nome);
bool delete_student(const char *matricula);

/* Lista todos */
void list_students(void);

#endif // STUDENTS_H
