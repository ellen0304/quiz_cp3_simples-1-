#include <stdio.h>
#include "funcoes.h"

int main(void) {
    Pergunta perguntas[MAX_PERGUNTAS];
    Jogador jogadores[MAX_JOGADORES];
    int totalPerguntas;
    int totalJogadores;
    int opcao;

    totalPerguntas = carregarPerguntas(perguntas);
    totalJogadores = carregarHistorico(jogadores);

    printf("Perguntas carregadas: %d\n", totalPerguntas);
    printf("Jogadores no historico: %d\n", totalJogadores);

    do {
        exibirMenu();
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                totalJogadores = jogarQuiz(perguntas, totalPerguntas,
                                           jogadores, totalJogadores);
                break;
            case 2:
                totalPerguntas = cadastrarPergunta(perguntas, totalPerguntas);
                break;
            case 3:
                listarPerguntas(perguntas, totalPerguntas);
                break;
            case 4:
                exibirRanking(jogadores, totalJogadores);
                break;
            case 0:
                printf("Saindo do quiz...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
