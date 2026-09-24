#include "utils.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/**
 * Função: chomp
 * ----------------
 * Remove caracteres de nova linha ('\n') e retorno cursor ('\r') 
 * do final de uma string, caso existam.
 *
 * Parâmetros:
 *   - s: ponteiro para a string que será modificada.
 *
 * Comportamento:
 *   - Se a string for nula ou vazia, não faz nada.
 *   - Se o último caractere for '\n', ele é substituído por '\0'.
 *   - Se houver '\r' antes do '\n', também é removido.
 *
 * Uso típico:
 *   - Após ler uma linha com fgets(), para eliminar a quebra de linha.
 */
void chomp(char *s) {
    if (!s) return;
    size_t len = strlen(s);
    if (len == 0) return;
    if (s[len-1] == '\n') s[len-1] = '\0';
    if (len > 1 && s[len-2] == '\r') s[len-2] = '\0';
}

/**
 * Função: trim
 * ----------------
 * Remove espaços em branco do início e do fim de uma string.
 *
 * Parâmetros:
 *   - s: ponteiro para a string que será modificada.
 *
 * Comportamento:
 *   - Avança o ponteiro até o primeiro caractere não espaço.
 *   - Move o conteúdo restante para o início da string.
 *   - Remove espaços em branco do final, substituindo-os por '\0'.
 *
 * Uso típico:
 *   - Para limpar entradas do usuário ou tokens lidos de arquivos CSV.
 */
void trim(char *s) {
    if (!s) return;
    char *start = s;
    while (isspace((unsigned char)*start)) start++;
    if (start != s) memmove(s, start, strlen(start)+1);
    char *end = s + strlen(s) - 1;
    while (end >= s && isspace((unsigned char)*end)) *end-- = '\0';
}

/**
 * Função: safe_token
 * ----------------
 * Recebe um token (string) e aplica a função trim() para remover
 * espaços em branco extras. Retorna o próprio token tratado.
 *
 * Parâmetros:
 *   - tok: ponteiro para o token (string) que será tratado.
 *
 * Retorno:
 *   - Ponteiro para o token limpo, ou NULL se tok for NULL.
 *
 * Uso típico:
 *   - Após usar strtok() para dividir uma linha CSV, garantindo que
 *     o token não tenha espaços indesejados.
 */
char *safe_token(char *tok) {
    if (!tok) return NULL;
    trim(tok);
    return tok;
}
