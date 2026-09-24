#include "students.h"
#include "grades.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Função: add_student
 * -------------------
 * Adiciona um novo aluno ao arquivo CSV de alunos.
 *
 * Parâmetros:
 *   - matricula: string com a matrícula do aluno (não nula)
 *   - nome: string com o nome do aluno (não nula)
 *
 * Comportamento:
 *   - Abre o arquivo definido por STUDENTS_FILE em modo append.
 *   - Escreve uma linha no formato "matricula,nome\n".
 *   - Fecha o arquivo e retorna true quando bem-sucedido.
 *   - Retorna false se algum parâmetro for nulo ou se o arquivo
 *     não puder ser aberto.
 *
 * Uso típico:
 *   - Chamada direta ao adicionar um novo registro de aluno.
 */
bool add_student(const char *matricula, const char *nome) {
    if (!matricula || !nome) return false;
    FILE *f = fopen(STUDENTS_FILE, "a");
    if (!f) return false;
    fprintf(f, "%s,%s\n", matricula, nome);
    fclose(f);
    return true;
}

/**
 * Função: find_student
 * --------------------
 * Procura um aluno pela matrícula e, se encontrado, preenche
 * a estrutura `Student` fornecida em `out`.
 *
 * Parâmetros:
 *   - matricula: matrícula a ser buscada (não nula)
 *   - out: ponteiro para uma estrutura Student que receberá os
 *          dados quando o aluno for encontrado (pode ser NULL)
 *
 * Comportamento:
 *   - Abre o arquivo STUDENTS_FILE em modo leitura e varre linha
 *     a linha procurando pelo token da matrícula.
 *   - Usa `strtok` para separar matrícula e nome, aplica `trim`
 *     e copia os valores para `out` quando localizado.
 *   - Retorna true se encontrado, false caso contrário ou em
 *     situações de erro (arquivo ausente, parâmetro inválido).
 */
bool find_student(const char *matricula, Student *out) {
    if (!matricula) return false;
    FILE *f = fopen(STUDENTS_FILE, "r");
    if (!f) return false;
    char line[LINE_BUF];
    while (fgets(line, sizeof(line), f)) {
        chomp(line);
        char *m = strtok(line, ",");
        char *n = strtok(NULL, "\n");
        if (!m) continue;
        trim(m);
        if (strcmp(m, matricula) == 0) {
            if (out) {
                strncpy(out->matricula, m, sizeof(out->matricula)-1);
                out->matricula[sizeof(out->matricula)-1] = '\0';
                if (n) {
                    trim(n);
                    strncpy(out->nome, n, sizeof(out->nome)-1);
                    out->nome[sizeof(out->nome)-1] = '\0';
                } else out->nome[0] = '\0';
            }
            fclose(f);
            return true;
        }
    }
    fclose(f);
    return false;
}

/**
 * Função: update_student
 * ----------------------
 * Atualiza o nome de um aluno identificado pela matrícula.
 *
 * Parâmetros:
 *   - matricula: matrícula do aluno a ser atualizada (não nula)
 *   - novo_nome: novo nome a ser atribuído (não nulo)
 *
 * Comportamento:
 *   - Lê o arquivo original linha a linha e escreve em um arquivo
 *     temporário (`data/students.tmp`), substituindo a linha do
 *     aluno quando encontrado.
 *   - Ao final, substitui o arquivo original pelo temporário.
 *   - Retorna true se uma atualização foi feita, false caso contrário
 *     ou em caso de erro de E/S.
 */
bool update_student(const char *matricula, const char *novo_nome) {
    if (!matricula || !novo_nome) return false;
    FILE *f = fopen(STUDENTS_FILE, "r");
    if (!f) return false;
    FILE *tmp = fopen("data/students.tmp", "w");
    if (!tmp) { fclose(f); return false; }
    char line[LINE_BUF];
    bool updated = false;
    while (fgets(line, sizeof(line), f)) {
        char copy[LINE_BUF];
        strcpy(copy, line);
        chomp(copy);
        char *m = strtok(copy, ",");
        if (m && strcmp(matricula, m) == 0) {
            fprintf(tmp, "%s,%s\n", matricula, novo_nome);
            updated = true;
        } else {
            fputs(line, tmp);
        }
    }
    fclose(f);
    fclose(tmp);
    remove(STUDENTS_FILE);
    rename("data/students.tmp", STUDENTS_FILE);
    return updated;
}

/**
 * Função: delete_student
 * ----------------------
 * Remove um aluno do arquivo CSV com base na matrícula.
 *
 * Parâmetros:
 *   - matricula: matrícula do aluno a remover (não nula)
 *
 * Comportamento:
 *   - Cria um arquivo temporário e regrava todas as linhas exceto
 *     a do aluno que deve ser removido.
 *   - Substitui o arquivo original pelo temporário ao final.
 *   - Retorna true se uma linha foi removida, false caso contrário
 *     ou em caso de erro.
 */
bool delete_student(const char *matricula) {
    if (!matricula) return false;
    FILE *f = fopen(STUDENTS_FILE, "r");
    if (!f) return false;
    FILE *tmp = fopen("data/students.tmp", "w");
    if (!tmp) { fclose(f); return false; }
    char line[LINE_BUF];
    bool removed = false;
    while (fgets(line, sizeof(line), f)) {
        char copy[LINE_BUF];
        strcpy(copy, line);
        chomp(copy);
        char *m = strtok(copy, ",");
        if (m && strcmp(matricula, m) == 0) {
            removed = true;
            continue; // skip writing this line
        }
        fputs(line, tmp);
    }
    fclose(f);
    fclose(tmp);
    remove(STUDENTS_FILE);
    rename("data/students.tmp", STUDENTS_FILE);
    if (removed) {
        delete_grades_by_student(matricula);
    }
    return removed;
}

/**
 * Função: list_students
 * ---------------------
 * Lista todos os alunos presentes no arquivo CSV, imprimindo
 * matrícula e nome na saída padrão.
 *
 * Comportamento:
 *   - Abre STUDENTS_FILE e, se não existir, informa que não há
 *     alunos cadastrados.
 *   - Para cada linha do arquivo, separa os campos e aplica
 *     `trim`/`chomp` antes de imprimir.
 *
 * Uso típico:
 *   - Chamado para exibir uma tabela simples de alunos no menu.
 */
void list_students(void) {
    FILE *f = fopen(STUDENTS_FILE, "r");
    if (!f) { printf("Nenhum aluno cadastrado (arquivo ausente).\n"); return; }
    char line[LINE_BUF];
    printf("Matrícula\tNome\n");
    printf("---------\t----\n");
    while (fgets(line, sizeof(line), f)) {
        chomp(line);
        char *m = strtok(line, ",");
        char *n = strtok(NULL, "\n");
        if (m) {
            trim(m);
            if (n) trim(n);
            printf("%s\t%s\n", m, n ? n : "");
        }
    }
    fclose(f);
}
