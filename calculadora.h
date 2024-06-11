#ifndef CALCULADORA_H
#define CALCULADORA_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Definição da struct Expressao
typedef struct {
    char posFixa[512];  // Expressão na forma posfixa
    char inFixa[512];   // Expressão na forma infixa
    float valor;        // Valor numérico da expressão
} Expressao;

// Declarações das funções exigidas pelo professor
char *getFormaInFixa(char *Str);    // Retorna a forma infixa de Str (posfixa)
float getValor(char *Str);          // Calcula o valor de Str (na forma posfixa)

// Função para avaliar a expressão posfixada
double avaliar_posfixada(const char* expressao);

// Funções das operações matemáticas
double adicionar(double a, double b);
double subtrair(double a, double b);
double multiplicar(double a, double b);
double dividir(double a, double b);
double exponenciar(double base, double expoente);
double logaritmo_base10(double a);
double seno(double a);
double cosseno(double a);

#endif
