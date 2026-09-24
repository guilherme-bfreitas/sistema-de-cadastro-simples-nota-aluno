#include "grades.h"
#include "utils.h"
#include "students.h"
#include "exams.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

static bool parse_grade_line(char *line, Grade *out) {
    if (!line || !out) return false;
    chomp(line);
    char *mat = strtok(line, ",");
    char *exam = strtok(NULL, ",");
    char *note = strtok(NULL, ",\n");
    if (!mat || !exam || !note) return false;
    trim(mat);
    trim(exam);
    trim(note);
    strncpy(out->matricula, mat, sizeof(out->matricula) - 1);
    out->matricula[sizeof(out->matricula) - 1] = '\0';
    strncpy(out->exam_id, exam, sizeof(out->exam_id) - 1);
    out->exam_id[sizeof(out->exam_id) - 1] = '\0';
    out->nota = strtod(note, NULL);
    return true;
}

bool add_grade(const char *matricula, const char *exam_id, double nota) {
    if (!matricula || !exam_id) return false;
    if (nota < 0.0 || nota > 10.0) return false;
    if (!find_student(matricula, NULL) || !find_exam(exam_id, NULL)) return false;
    FILE *f = fopen(GRADES_FILE, "a");
    if (!f) return false;
    fprintf(f, "%s,%s,%.2f\n", matricula, exam_id, nota);
    fclose(f);
    return true;
}

bool find_grade(const char *matricula, const char *exam_id, Grade *out) {
    if (!matricula || !exam_id) return false;
    FILE *f = fopen(GRADES_FILE, "r");
    if (!f) return false;
    char line[LINE_BUF];
    while (fgets(line, sizeof(line), f)) {
        char copy[LINE_BUF];
        strcpy(copy, line);
        Grade grade;
        if (!parse_grade_line(copy, &grade)) continue;
        if (strcmp(grade.matricula, matricula) == 0 && strcmp(grade.exam_id, exam_id) == 0) {
            if (out) *out = grade;
            fclose(f);
            return true;
        }
    }
    fclose(f);
    return false;
}

bool update_grade(const char *matricula, const char *exam_id, double nova_nota) {
    if (!matricula || !exam_id) return false;
    if (nova_nota < 0.0 || nova_nota > 10.0) return false;
    FILE *f = fopen(GRADES_FILE, "r");
    if (!f) return false;
    FILE *tmp = fopen("data/grades.tmp", "w");
    if (!tmp) { fclose(f); return false; }
    char line[LINE_BUF];
    bool updated = false;
    while (fgets(line, sizeof(line), f)) {
        char copy[LINE_BUF];
        strcpy(copy, line);
        Grade grade;
        if (parse_grade_line(copy, &grade) && strcmp(grade.matricula, matricula) == 0 && strcmp(grade.exam_id, exam_id) == 0) {
            fprintf(tmp, "%s,%s,%.2f\n", matricula, exam_id, nova_nota);
            updated = true;
        } else {
            fputs(line, tmp);
        }
    }
    fclose(f);
    fclose(tmp);
    remove(GRADES_FILE);
    rename("data/grades.tmp", GRADES_FILE);
    return updated;
}

bool delete_grade(const char *matricula, const char *exam_id) {
    if (!matricula || !exam_id) return false;
    FILE *f = fopen(GRADES_FILE, "r");
    if (!f) return false;
    FILE *tmp = fopen("data/grades.tmp", "w");
    if (!tmp) { fclose(f); return false; }
    char line[LINE_BUF];
    bool removed = false;
    while (fgets(line, sizeof(line), f)) {
        char copy[LINE_BUF];
        strcpy(copy, line);
        Grade grade;
        if (parse_grade_line(copy, &grade) && strcmp(grade.matricula, matricula) == 0 && strcmp(grade.exam_id, exam_id) == 0) {
            removed = true;
            continue;
        }
        fputs(line, tmp);
    }
    fclose(f);
    fclose(tmp);
    remove(GRADES_FILE);
    rename("data/grades.tmp", GRADES_FILE);
    return removed;
}

bool delete_grades_by_student(const char *matricula) {
    if (!matricula) return false;
    FILE *f = fopen(GRADES_FILE, "r");
    if (!f) return false;
    FILE *tmp = fopen("data/grades.tmp", "w");
    if (!tmp) { fclose(f); return false; }
    char line[LINE_BUF];
    bool removed = false;
    while (fgets(line, sizeof(line), f)) {
        char copy[LINE_BUF];
        strcpy(copy, line);
        Grade grade;
        if (parse_grade_line(copy, &grade) && strcmp(grade.matricula, matricula) == 0) {
            removed = true;
            continue;
        }
        fputs(line, tmp);
    }
    fclose(f);
    fclose(tmp);
    remove(GRADES_FILE);
    rename("data/grades.tmp", GRADES_FILE);
    return removed;
}

void list_grades(void) {
    FILE *f = fopen(GRADES_FILE, "r");
    if (!f) { printf("Nenhuma nota cadastrada (arquivo ausente).\n"); return; }
    char line[LINE_BUF];
    printf("Matricula\tAvaliacao\tNota\tAluno\tAvaliacao Nome\n");
    printf("---------\t---------\t----\t-----\t-------------\n");
    while (fgets(line, sizeof(line), f)) {
        char copy[LINE_BUF];
        strcpy(copy, line);
        Grade grade;
        if (!parse_grade_line(copy, &grade)) continue;
        Student aluno;
        Exam prova;
        char aluno_nome[256] = "(desconhecido)";
        char prova_nome[256] = "(desconhecido)";
        if (find_student(grade.matricula, &aluno)) strncpy(aluno_nome, aluno.nome, sizeof(aluno_nome) - 1);
        if (find_exam(grade.exam_id, &prova)) strncpy(prova_nome, prova.nome, sizeof(prova_nome) - 1);
        printf("%s\t%s\t%.2f\t%s\t%s\n", grade.matricula, grade.exam_id, grade.nota, aluno_nome, prova_nome);
    }
    fclose(f);
}

bool report_grades_by_student(const char *matricula) {
    if (!matricula) return false;
    Student aluno;
    if (!find_student(matricula, &aluno)) {
        printf("Aluno nao encontrado: %s\n", matricula);
        return false;
    }
    FILE *f = fopen(GRADES_FILE, "r");
    if (!f) { printf("Nenhuma nota cadastrada.\n"); return false; }
    char line[LINE_BUF];
    double soma = 0.0;
    int contador = 0;
    printf("Notas do aluno %s (%s):\n", aluno.nome, aluno.matricula);
    printf("Avaliacao\tNota\n");
    printf("---------\t----\n");
    while (fgets(line, sizeof(line), f)) {
        char copy[LINE_BUF];
        strcpy(copy, line);
        Grade grade;
        if (!parse_grade_line(copy, &grade)) continue;
        if (strcmp(grade.matricula, matricula) != 0) continue;
        Exam prova;
        char prova_nome[256] = "(desconhecido)";
        if (find_exam(grade.exam_id, &prova)) strncpy(prova_nome, prova.nome, sizeof(prova_nome) - 1);
        printf("%s\t%.2f\n", prova_nome, grade.nota);
        soma += grade.nota;
        contador++;
    }
    fclose(f);
    if (contador == 0) {
        printf("Nenhuma nota encontrada para este aluno.\n");
        return true;
    }
    printf("Media: %.2f\n", soma / contador);
    return true;
}

bool report_grades_by_exam(const char *exam_id) {
    if (!exam_id) return false;
    Exam prova;
    if (!find_exam(exam_id, &prova)) {
        printf("Avaliacao nao encontrada: %s\n", exam_id);
        return false;
    }
    FILE *f = fopen(GRADES_FILE, "r");
    if (!f) { printf("Nenhuma nota cadastrada.\n"); return false; }
    char line[LINE_BUF];
    double soma = 0.0;
    int contador = 0;
    printf("Notas da avaliacao %s (%s):\n", prova.nome, prova.id);
    printf("Matricula\tAluno\tNota\n");
    printf("---------\t-----\t----\n");
    while (fgets(line, sizeof(line), f)) {
        char copy[LINE_BUF];
        strcpy(copy, line);
        Grade grade;
        if (!parse_grade_line(copy, &grade)) continue;
        if (strcmp(grade.exam_id, exam_id) != 0) continue;
        Student aluno;
        char aluno_nome[256] = "(desconhecido)";
        if (find_student(grade.matricula, &aluno)) strncpy(aluno_nome, aluno.nome, sizeof(aluno_nome) - 1);
        printf("%s\t%s\t%.2f\n", grade.matricula, aluno_nome, grade.nota);
        soma += grade.nota;
        contador++;
    }
    fclose(f);
    if (contador == 0) {
        printf("Nenhuma nota encontrada para esta avaliacao.\n");
        return true;
    }
    printf("Media da avaliacao: %.2f\n", soma / contador);
    return true;
}
