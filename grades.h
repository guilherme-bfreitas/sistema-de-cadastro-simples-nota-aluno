#ifndef GRADES_H
#define GRADES_H

#include <stdbool.h>

#define GRADES_FILE "data/grades.csv"

typedef struct {
    char matricula[64];
    char exam_id[64];
    double nota;
} Grade;

/* CRUD */
bool add_grade(const char *matricula, const char *exam_id, double nota);
bool find_grade(const char *matricula, const char *exam_id, Grade *out);
bool update_grade(const char *matricula, const char *exam_id, double nova_nota);
bool delete_grade(const char *matricula, const char *exam_id);
bool delete_grades_by_student(const char *matricula);

/* Listagem e relatórios */
void list_grades(void);
bool report_grades_by_student(const char *matricula);
bool report_grades_by_exam(const char *exam_id);

#endif // GRADES_H
