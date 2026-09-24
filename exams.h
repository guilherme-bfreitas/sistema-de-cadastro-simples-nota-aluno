#ifndef EXAMS_H
#define EXAMS_H

#include <stdbool.h>

#define EXAMS_FILE "data/exams.csv"

typedef struct {
    char id[64];
    char nome[256];
    char data[32];
} Exam;

/* CRUD */
bool add_exam(const char *id, const char *nome, const char *data);
bool find_exam(const char *id, Exam *out);
bool update_exam(const char *id, const char *novo_nome, const char *nova_data);
bool delete_exam(const char *id);

/* Lista todos */
void list_exams(void);

#endif // EXAMS_H
