#include "calculadora.h"

int main() {
    char expressao[256];

    printf("Digite uma expressão posfixada: ");
    fgets(expressao, sizeof(expressao), stdin);
    expressao[strcspn(expressao, "\n")] = 0;  // Remover a nova linha do final

    double resultado = avaliar_posfixada(expressao);
    printf("Resultado: %lf\n", resultado);

    // Exemplo de uso da struct Expressao
    Expressao exp;
    strcpy(exp.posFixa, expressao);
    strcpy(exp.inFixa, getFormaInFixa(expressao));
    exp.valor = getValor(expressao);

    printf("Expressão Infixa: %s\n", exp.inFixa);


    return 0;
}
