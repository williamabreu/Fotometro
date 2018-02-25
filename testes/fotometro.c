/**
 * Simulação do software embarcado do Fotômetro.
 * 
 * Ele deve ser capaz de identificar o ponto exato da mudança de cor
 * da titulação de acordo com os valores lidos de um LDR.
 * 
 * Utilizando dados coletados experimentalmente e salvos nos arquivos:
 * - "dados1.txt" (ponto de mudança na linha 69);
 * - "dados2.txt" (ponto de mudança na linha 112).
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Variáveis de estado:
float mean = 0;
float var = 0;
int count = 0;

void add(int dado) {
    // Algoritmos de Estimação Recursiva:
    // http://www.mfap.com.br/pesquisa/arquivos/20081212090656-31608.pdf
    count++;
    var = var + ((count - 1) * (dado - mean) * (dado - mean)  / count - var) / count; 
    mean = mean + (dado - mean) / (count);
}

int main(int argc, char** argv) {
    FILE* file = fopen(argv[1], "r");
    int dadoLido;
    
    int i = 0;

    // Monta o estado inicial a partir dos 30 primeiros valores:
    while (i < 30) {
        fscanf(file, "%d", &dadoLido);
        i++;
        add(dadoLido);
    }

    while (!feof(file)) {
        fscanf(file, "%d", &dadoLido);
        i++;

        // Detecta o ponto de interesse:
        // Heurística - valor lido deve ser maior que 4x desvio padrão em cima da média recursiva.
        if (abs(dadoLido - mean) > 4*sqrt(var)) {
            printf("%d: %d", i, dadoLido);
            break;
        }
        
        add(dadoLido);

        //printf("%d  %d  %.0f  %.4f\n", i++, dadoLido, mean, sqrt(var));
    }
    
    putchar('\n');

    fclose(file);

    return 0;
}
