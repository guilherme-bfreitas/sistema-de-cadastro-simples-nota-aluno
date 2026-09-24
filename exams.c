#include "exams.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool add_exam(const char *id, const char *nome, const char *data) {
    if (!id || !nome || !data) return false;
    FILE *f = fopen(EXAMS_FILE, "a");
    if (!f) return false;
    fprintf(f, "%s,%s,%s\n", id, nome, data);
    fclose(f);
    return true;
}

bool find_exam(const char *id, Exam *out) {
    if (!id) return false;
    FILE *f = fopen(EXAMS_FILE, "r");
    if (!f) return false;
    char line[LINE_BUF];
    while (fgets(line, sizeof(line), f)) {
        chomp(line);
        char copy[LINE_BUF];
        strcpy(copy, line);
        char *eid = strtok(copy, ",");
        char *nome = strtok(NULL, ",");
        char *data = strtok(NULL, "\n");
        if (!eid) continue;
        trim(eid);
        if (strcmp(eid, id) == 0) {
            if (out) {
                strncpy(out->id, eid, sizeof(out->id) - 1);
                out->id[sizeof(out->id) - 1] = '\0';
                if (nome) {
                    trim(nome);
                    strncpy(out->nome, nome, sizeof(out->nome) - 1);
                    out->nome[sizeof(out->nome) - 1] = '\0';
                } else {
                    out->nome[0] = '\0';
                }
                if (data) {
                    trim(data);
                    strncpy(out->data, data, sizeof(out->data) - 1);
                    out->data[sizeof(out->data) - 1] = '\0';
                } else {
                    out->data[0] = '\0';
                }
            }
            fclose(f);
            return true;
        }
    }
    fclose(f);
    return false;
}

bool update_exam(const char *id, const char *novo_nome, const char *nova_data) {
    if (!id || !novo_nome || !nova_data) return false;
    FILE *f = fopen(EXAMS_FILE, "r");
    if (!f) return false;
    FILE *tmp = fopen("data/exams.tmp", "w");
    if (!tmp) { fclose(f); return false; }
    char line[LINE_BUF];
    bool updated = false;
    while (fgets(line, sizeof(line), f)) {
        char copy[LINE_BUF];
        strcpy(copy, line);
        chomp(copy);
        char *eid = strtok(copy, ",");
        if (eid && strcmp(id, eid) == 0) {
            fprintf(tmp, "%s,%s,%s\n", id, novo_nome, nova_data);
            updated = true;
        } else {
            fputs(line, tmp);
        }
    }
    fclose(f);
    fclose(tmp);
    remove(EXAMS_FILE);
    rename("data/exams.tmp", EXAMS_FILE);
    return updated;
}

bool delete_exam(const char *id) {
    if (!id) return false;
    FILE *f = fopen(EXAMS_FILE, "r");
    if (!f) return false;
    FILE *tmp = fopen("data/exams.tmp", "w");
    if (!tmp) { fclose(f); return false; }
    char line[LINE_BUF];
    bool removed = false;
    while (fgets(line, sizeof(line), f)) {
        char copy[LINE_BUF];
        strcpy(copy, line);
        chomp(copy);
        char *eid = strtok(copy, ",");
        if (eid && strcmp(id, eid) == 0) {
            removed = true;
            continue;
        }
        fputs(line, tmp);
    }
    fclose(f);
    fclose(tmp);
    remove(EXAMS_FILE);
    rename("data/exams.tmp", EXAMS_FILE);
    return removed;
}

void list_exams(void) {
    FILE *f = fopen(EXAMS_FILE, "r");
    if (!f) { printf("Nenhuma avaliacao cadastrada (arquivo ausente).\n"); return; }
    char line[LINE_BUF];
    printf("ID\tNome\tData\n");
    printf("--\t----\t----\n");
    while (fgets(line, sizeof(line), f)) {
        chomp(line);
        char *eid = strtok(line, ",");
        char *nome = strtok(NULL, ",");
        char *data = strtok(NULL, "\n");
        if (eid) {
            trim(eid);
            if (nome) trim(nome);
            if (data) trim(data);
            printf("%s\t%s\t%s\n", eid, nome ? nome : "", data ? data : "");
        }
    }
    fclose(f);
}
