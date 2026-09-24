#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "students.h"
#include "exams.h"
#include "grades.h"
#include "utils.h"

/*
ADICIONE SEU NOME E MATRÍCULA AQUI: 
NOME: Fulano de Oliveira
MATRICULA: 2026002222111
*/


static void pause_and_clear() {
    printf("\n\nPressione Enter para continuar...\n");
    getchar();
}

int main(void) {
    int opt = 0;
    char buf[256];
    int c;

    // Menu principal em loop, usando scanf para opções e 
    //fgets para entradas de texto, com tratamento de buffer.
    while (1) {
        printf("\n=== Sistema para cadastros de avaliacoes e notas de alunos salvando os dados em arquivo .CSV` ===\n");
        printf("1. Listar alunos\n");
        printf("2. Adicionar aluno\n");
        printf("3. Atualizar aluno\n");
        printf("4. Remover aluno\n");
        printf("5. Listar avaliacoes\n");
        printf("6. Adicionar avaliacao\n");
        printf("7. Atualizar avaliacao\n");
        printf("8. Remover avaliacao\n");
        printf("9. Listar notas\n");
        printf("10. Adicionar nota\n");
        printf("11. Atualizar nota\n");
        printf("12. Remover nota\n");
        printf("13. Relatorio: notas por aluno\n");
        printf("14. Relatorio: notas por avaliacao\n");
        printf("0. Sair\n");
        printf("Escolha: ");

        //Usa o retorno de scanf para validar entrada numérica e limpar buffer em caso de erro.
        // scanf retorna a quantidade de itens lidos, se quantidade for 1 então é um número válido. 
        // Se for diferente, limpa o buffer até o próximo newline.
        if (scanf("%d", &opt) != 1) { 
            while ( (c = getchar()) != '\n' && c != EOF ); // limpa entrada
            continue; 
        }
        getchar(); // consome newline

        if (opt == 0) 
            break;

        if (opt == 1) { 
            list_students(); 
            pause_and_clear(); 
            continue; 
        }
        if (opt == 2) {
            char mat[64], nome[256];

            printf("Matrícula: "); 
            fgets(mat, sizeof(mat), stdin); 
            chomp(mat); 
            trim(mat);

            printf("Nome: "); 
            fgets(nome, sizeof(nome), stdin); 
            chomp(nome); 
            trim(nome);

            if (add_student(mat, nome)) 
                printf("Aluno adicionado.\n"); 
            else 
                printf("Erro ao adicionar.\n");
            pause_and_clear(); 
            continue;
        }
        if (opt == 3) {
            char mat[64], nome[256];
            
            printf("Informe o numero de Matricula: "); 
            fgets(mat, sizeof(mat), stdin); 
            chomp(mat); 
            trim(mat);
            
            printf("Novo nome: "); 
            fgets(nome, sizeof(nome), stdin); 
            chomp(nome); 
            trim(nome);
            
            if (update_student(mat, nome)) 
                printf("Atualizado.\n"); 
            else 
                printf("Nao encontrado.\n");
            pause_and_clear(); 
            continue;
        }
        if (opt == 4) {
            char mat[64];

            printf("Matricula a remover: "); 
            fgets(mat, sizeof(mat), stdin); 
            chomp(mat); 
            trim(mat);

            if (delete_student(mat)) 
                printf("Removido.\n"); 
            else 
                printf("Nao encontrado.\n");
            pause_and_clear(); 
            continue;
        }
        if (opt == 5) { 
            list_exams();
            pause_and_clear();
            continue;
        }
        if (opt == 6) {
            char id[64], nome[256], data[32];

            printf("ID da avaliacao: ");
            fgets(id, sizeof(id), stdin);
            chomp(id);
            trim(id);

            printf("Nome da avaliacao: ");
            fgets(nome, sizeof(nome), stdin);
            chomp(nome);
            trim(nome);

            printf("Data (YYYY-MM-DD): ");
            fgets(data, sizeof(data), stdin);
            chomp(data);
            trim(data);

            if (add_exam(id, nome, data))
                printf("Avaliacao adicionada.\n");
            else
                printf("Erro ao adicionar avaliacao.\n");
            pause_and_clear();
            continue;
        }
        if (opt == 7) {
            char id[64], nome[256], data[32];

            printf("ID da avaliacao a atualizar: ");
            fgets(id, sizeof(id), stdin);
            chomp(id);
            trim(id);

            printf("Novo nome da avaliacao: ");
            fgets(nome, sizeof(nome), stdin);
            chomp(nome);
            trim(nome);

            printf("Nova data (YYYY-MM-DD): ");
            fgets(data, sizeof(data), stdin);
            chomp(data);
            trim(data);

            if (update_exam(id, nome, data))
                printf("Avaliacao atualizada.\n");
            else
                printf("Nao encontrado ou erro.\n");
            pause_and_clear();
            continue;
        }
        if (opt == 8) {
            char id[64];

            printf("ID da avaliacao a remover: ");
            fgets(id, sizeof(id), stdin);
            chomp(id);
            trim(id);

            if (delete_exam(id))
                printf("Avaliacao removida.\n");
            else
                printf("Nao encontrado.\n");
            pause_and_clear();
            continue;
        }
        if (opt == 9) { 
            list_grades();
            pause_and_clear();
            continue;
        }
        if (opt == 10) {
            char mat[64], exam_id[64], nota_str[32];
            double nota;

            printf("Matricula do aluno: ");
            fgets(mat, sizeof(mat), stdin);
            chomp(mat);
            trim(mat);

            printf("ID da avaliacao: ");
            fgets(exam_id, sizeof(exam_id), stdin);
            chomp(exam_id);
            trim(exam_id);

            printf("Nota: ");
            fgets(nota_str, sizeof(nota_str), stdin);
            chomp(nota_str);
            trim(nota_str);
            nota = strtod(nota_str, NULL);

            if (add_grade(mat, exam_id, nota))
                printf("Nota adicionada.\n");
            else
                printf("Erro ao adicionar nota. Verifique matricula e avaliacao.\n");
            pause_and_clear();
            continue;
        }
        if (opt == 11) {
            char mat[64], exam_id[64], nota_str[32];
            double nota;

            printf("Matricula do aluno: ");
            fgets(mat, sizeof(mat), stdin);
            chomp(mat);
            trim(mat);

            printf("ID da avaliacao: ");
            fgets(exam_id, sizeof(exam_id), stdin);
            chomp(exam_id);
            trim(exam_id);

            printf("Nova nota: ");
            fgets(nota_str, sizeof(nota_str), stdin);
            chomp(nota_str);
            trim(nota_str);
            nota = strtod(nota_str, NULL);

            if (update_grade(mat, exam_id, nota))
                printf("Nota atualizada.\n");
            else
                printf("Nao encontrado ou erro.\n");
            pause_and_clear();
            continue;
        }
        if (opt == 12) {
            char mat[64], exam_id[64];

            printf("Matricula do aluno: ");
            fgets(mat, sizeof(mat), stdin);
            chomp(mat);
            trim(mat);

            printf("ID da avaliacao: ");
            fgets(exam_id, sizeof(exam_id), stdin);
            chomp(exam_id);
            trim(exam_id);

            if (delete_grade(mat, exam_id))
                printf("Nota removida.\n");
            else
                printf("Nao encontrado.\n");
            pause_and_clear();
            continue;
        }
        if (opt == 13) {
            char mat[64];

            printf("Matricula do aluno: ");
            fgets(mat, sizeof(mat), stdin);
            chomp(mat);
            trim(mat);

            report_grades_by_student(mat);
            pause_and_clear();
            continue;
        }
        if (opt == 14) {
            char exam_id[64];

            printf("ID da avaliacao: ");
            fgets(exam_id, sizeof(exam_id), stdin);
            chomp(exam_id);
            trim(exam_id);

            report_grades_by_exam(exam_id);
            pause_and_clear();
            continue;
        }

        printf("Opcao invalida.\n");
    }

    printf("Encerrando.\n");
    return 0;
}
