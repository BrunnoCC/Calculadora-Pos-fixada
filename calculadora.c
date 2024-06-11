#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "calculadora.h"

#define MAX_SIZE 100

typedef struct {
    double itens[MAX_SIZE];
    int topo;
} Pilha;

typedef struct {
    char* itens[MAX_SIZE];
    int topo;
} PilhaString;

void inicializar_pilha(Pilha* pilha) {
    pilha->topo = -1;
}

void inicializar_pilha_string(PilhaString* pilha) {
    pilha->topo = -1;
}

int pilha_vazia(Pilha* pilha) {
    return pilha->topo == -1;
}

int pilha_string_vazia(PilhaString* pilha) {
    return pilha->topo == -1;
}

int pilha_cheia(Pilha* pilha) {
    return pilha->topo == MAX_SIZE - 1;
}

int pilha_string_cheia(PilhaString* pilha) {
    return pilha->topo == MAX_SIZE - 1;
}

void empilhar(Pilha* pilha, double valor) {
    if (!pilha_cheia(pilha)) {
        pilha->itens[++pilha->topo] = valor;
    } else {
        printf("Erro: Pilha cheia\n");
        exit(EXIT_FAILURE);
    }
}

void empilhar_string(PilhaString* pilha, char* valor) {
    if (!pilha_string_cheia(pilha)) {
        pilha->itens[++pilha->topo] = valor;
    } else {
        printf("Erro: Pilha cheia\n");
        exit(EXIT_FAILURE);
    }
}

double desempilhar(Pilha* pilha) {
    if (!pilha_vazia(pilha)) {
        return pilha->itens[pilha->topo--];
    } else {
        printf("Erro: Pilha vazia\n");
        exit(EXIT_FAILURE);
    }
}

char* desempilhar_string(PilhaString* pilha) {
    if (!pilha_string_vazia(pilha)) {
        return pilha->itens[pilha->topo--];
    } else {
        printf("Erro: Pilha de strings vazia\n");
        exit(EXIT_FAILURE);
    }
}

double avaliar_posfixada(const char* expressao) {
    Pilha pilha;
    inicializar_pilha(&pilha);

    char expressao_copia[strlen(expressao) + 1];
    strcpy(expressao_copia, expressao);
    char* token = strtok(expressao_copia, " ");

    while (token != NULL) {
        if (strcmp(token, "+") == 0) {
            double b = desempilhar(&pilha);
            double a = desempilhar(&pilha);
            empilhar(&pilha, adicionar(a, b));
        } else if (strcmp(token, "-") == 0) {
            double b = desempilhar(&pilha);
            double a = desempilhar(&pilha);
            empilhar(&pilha, subtrair(a, b));
        } else if (strcmp(token, "*") == 0) {
            double b = desempilhar(&pilha);
            double a = desempilhar(&pilha);
            empilhar(&pilha, multiplicar(a, b));
        } else if (strcmp(token, "/") == 0) {
            double b = desempilhar(&pilha);
            double a = desempilhar(&pilha);
            empilhar(&pilha, dividir(a, b));
        } else if (strcmp(token, "^") == 0) {
            double expoente = desempilhar(&pilha);
            double base = desempilhar(&pilha);
            empilhar(&pilha, exponenciar(base, expoente));
        } else if (strcmp(token, "log") == 0) {
            double a = desempilhar(&pilha);
            empilhar(&pilha, logaritmo_base10(a));
        } else if (strcmp(token, "sen") == 0) {
            double a = desempilhar(&pilha);
            empilhar(&pilha, seno(a));
        } else if (strcmp(token, "cos") == 0) {
            double a = desempilhar(&pilha);
            empilhar(&pilha, cosseno(a));
        } else {
            empilhar(&pilha, atof(token));
        }
        token = strtok(NULL, " ");
    }
    return desempilhar(&pilha);
}

double adicionar(double a, double b) {
    return a + b;
}

double subtrair(double a, double b) {
    return a - b;
}

double multiplicar(double a, double b) {
    return a * b;
}

double dividir(double a, double b) {
    if (b == 0) {
        printf("Erro: Divisão por zero\n");
        exit(EXIT_FAILURE);
    }
    return a / b;
}

double exponenciar(double base, double expoente) {
    return pow(base, expoente);
}

double logaritmo_base10(double a) {
    if (a <= 0) {
        printf("Erro: Logaritmo de número não positivo\n");
        exit(EXIT_FAILURE);
    }
    return log10(a);
}

double seno(double a) {
    return sin(a * (M_PI / 180.0));
}

double cosseno(double a) {
    return cos(a * (M_PI / 180.0));
}

char* getFormaInFixa(char *str) {
    PilhaString pilha;
    inicializar_pilha_string(&pilha);

    char* token = strtok(str, " ");
    while (token != NULL) {
        if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 || strcmp(token, "*") == 0 || strcmp(token, "/") == 0 || strcmp(token, "^") == 0) {
            char* b = desempilhar_string(&pilha);
            char* a = desempilhar_string(&pilha);

            char* infixa = (char*)malloc(strlen(a) + strlen(b) + 4);
            sprintf(infixa, "(%s %s %s)", a, token, b);
            empilhar_string(&pilha, infixa);

            free(a);
            free(b);
        } else if (strcmp(token, "log") == 0 || strcmp(token, "sen") == 0 || strcmp(token, "cos") == 0) {
            char* a = desempilhar_string(&pilha);

            char* infixa = (char*)malloc(strlen(a) + strlen(token) + 3);
            sprintf(infixa, "%s(%s)", token, a);
            empilhar_string(&pilha, infixa);

            free(a);
        } else {
            char* operando = (char*)malloc(strlen(token) + 1);
            strcpy(operando, token);
            empilhar_string(&pilha, operando);
        }
        token = strtok(NULL, " ");
    }

    char* resultado = desempilhar_string(&pilha);
    return resultado;
}

float getValor(char *Str) {
    return avaliar_posfixada(Str);
}
