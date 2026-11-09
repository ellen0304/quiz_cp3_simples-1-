
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funcoes.h"

void limparBuffer(void) {
    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}

// o menu principa
void exibirMenu(void) {
    printf("\n====================================\n");
    printf("           MENTE EM JOGO\n");
    printf("     Desafie seus conhecimentos!\n");
    printf("====================================\n");
    printf("1 - Iniciar desafio\n");
    printf("2 - Criar pergunta\n");
    printf("3 - Consultar perguntas\n");
    printf("4 - Ver ranking\n");
    printf("0 - Encerrar\n");
    printf("====================================\n");
    printf("Escolha uma opcao: ");
}

// perguntas do arquivo
int carregarPerguntas(Pergunta perguntas[]) {
    FILE *arquivo;
    int total = 0;

    arquivo = fopen("data/perguntas.txt", "r");

    if (arquivo == NULL) {
        return 0;
    }

    while (total < MAX_PERGUNTAS &&
           fscanf(arquivo,
                  " %199[^;];%99[^;];%99[^;];%99[^;];%99[^;]; %c",
                  perguntas[total].enunciado,
                  perguntas[total].alternativas[0],
                  perguntas[total].alternativas[1],
                  perguntas[total].alternativas[2],
                  perguntas[total].alternativas[3],
                  &perguntas[total].respostaCorreta) == 6) {

        perguntas[total].respostaCorreta =
            toupper((unsigned char)perguntas[total].respostaCorreta);

        total++;
    }

    fclose(arquivo);

    return total;
}

// salva todas as perguntas 
void salvarPerguntas(Pergunta perguntas[], int total) {
    FILE *arquivo;

    arquivo = fopen("data/perguntas.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao salvar as perguntas!\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        fprintf(arquivo, "%s;%s;%s;%s;%s;%c\n",
                perguntas[i].enunciado,
                perguntas[i].alternativas[0],
                perguntas[i].alternativas[1],
                perguntas[i].alternativas[2],
                perguntas[i].alternativas[3],
                perguntas[i].respostaCorreta);
    }

    fclose(arquivo);
}

// Carrega o historico dos jogadores
int carregarHistorico(Jogador jogadores[]) {
    FILE *arquivo;
    int total = 0;

    arquivo = fopen("data/historico.txt", "r");

    if (arquivo == NULL) {
        return 0;
    }

    while (total < MAX_JOGADORES &&
           fscanf(arquivo, " %99[^;];%d;%d;%f",
                  jogadores[total].nome,
                  &jogadores[total].acertos,
                  &jogadores[total].totalPerguntas,
                  &jogadores[total].percentual) == 4) {

        total++;
    }

    fclose(arquivo);

    return total;
}

// Salva o resultado de um jogador no historico
void salvarJogador(Jogador jogador) {
    FILE *arquivo;

    arquivo = fopen("data/historico.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao salvar o historico!\n");
        return;
    }

    fprintf(arquivo, "%s;%d;%d;%.2f\n",
            jogador.nome,
            jogador.acertos,
            jogador.totalPerguntas,
            jogador.percentual);

    fclose(arquivo);
}

// Cadastra uma nova pergunta
int cadastrarPergunta(Pergunta perguntas[], int total) {
    char resposta;

    if (total >= MAX_PERGUNTAS) {
        printf("\nLimite de perguntas atingido!\n");
        return total;
    }

    printf("\nDigite o enunciado da pergunta: ");
    fgets(perguntas[total].enunciado, TAM_ENUNCIADO, stdin);
    perguntas[total].enunciado[
        strcspn(perguntas[total].enunciado, "\n")] = '\0';

    for (int i = 0; i < 4; i++) {
        printf("Digite a alternativa %c: ", 'A' + i);

        fgets(perguntas[total].alternativas[i],
              TAM_ALTERNATIVA, stdin);

        perguntas[total].alternativas[i][
            strcspn(perguntas[total].alternativas[i], "\n")] = '\0';
    }

    printf("Digite a resposta correta (A, B, C ou D): ");
    scanf(" %c", &resposta);
    limparBuffer();

    resposta = toupper((unsigned char)resposta);

    if (resposta < 'A' || resposta > 'D') {
        printf("\nResposta invalida! Pergunta nao cadastrada.\n");
        return total;
    }

    perguntas[total].respostaCorreta = resposta;

    total++;

    salvarPerguntas(perguntas, total);

    printf("\nPergunta cadastrada com sucesso!\n");

    return total;
}

// Lista todas as perguntas cadastradas
void listarPerguntas(Pergunta perguntas[], int total) {
    if (total == 0) {
        printf("\nNenhuma pergunta cadastrada.\n");
        return;
    }

    printf("\n========== PERGUNTAS CADASTRADAS ==========\n");

    for (int i = 0; i < total; i++) {
        printf("\nPergunta %d: %s\n", i + 1,
               perguntas[i].enunciado);

        for (int j = 0; j < 4; j++) {
            printf("%c) %s\n", 'A' + j,
                   perguntas[i].alternativas[j]);
        }
    }
}

// Executa o quiz
int jogarQuiz(Pergunta perguntas[], int totalPerguntas,
              Jogador jogadores[], int totalJogadores) {

    int acertos = 0;
    char resposta;

    if (totalPerguntas == 0) {
        printf("\nNao existem perguntas cadastradas!\n");
        return totalJogadores;
    }

    if (totalJogadores >= MAX_JOGADORES) {
        printf("\nLimite de jogadores atingido!\n");
        return totalJogadores;
    }

    printf("\nDigite o nome do jogador: ");

    fgets(jogadores[totalJogadores].nome, TAM_NOME, stdin);

    jogadores[totalJogadores].nome[
        strcspn(jogadores[totalJogadores].nome, "\n")] = '\0';

    
    while (strlen(jogadores[totalJogadores].nome) == 0 ||
           strspn(jogadores[totalJogadores].nome, " \t") ==
           strlen(jogadores[totalJogadores].nome)) {

        printf("Nome vazio! Digite novamente: ");

        fgets(jogadores[totalJogadores].nome, TAM_NOME, stdin);

        jogadores[totalJogadores].nome[
            strcspn(jogadores[totalJogadores].nome, "\n")] = '\0';
    }

    printf("\n========== INICIO DO DESAFIO ==========\n");

    for (int i = 0; i < totalPerguntas; i++) {
        printf("\nPergunta %d: %s\n", i + 1,
               perguntas[i].enunciado);

        for (int j = 0; j < 4; j++) {
            printf("%c) %s\n", 'A' + j,
                   perguntas[i].alternativas[j]);
        }

        printf("Sua resposta: ");
        scanf(" %c", &resposta);
        limparBuffer();

        resposta = toupper((unsigned char)resposta);

        if (resposta == perguntas[i].respostaCorreta) {
            printf("Resposta correta!\n");
            acertos++;
        } else {
            printf("Resposta incorreta!\n");
        }
    }

    jogadores[totalJogadores].acertos = acertos;
    jogadores[totalJogadores].totalPerguntas = totalPerguntas;

    jogadores[totalJogadores].percentual =
        (float)acertos * 100 / totalPerguntas;

    printf("\n========== RESULTADO ==========\n");
    printf("Jogador: %s\n", jogadores[totalJogadores].nome);
    printf("Acertos: %d de %d\n", acertos, totalPerguntas);
    printf("Aproveitamento: %.2f%%\n",
           jogadores[totalJogadores].percentual);

    salvarJogador(jogadores[totalJogadores]);

    printf("\nResultado salvo no historico!\n");

    return totalJogadores + 1;
}

// Ordena o ranking usando Bubble Sort
void ordenarRanking(Jogador jogadores[], int total) {
    Jogador aux;

    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - 1 - i; j++) {

            if (jogadores[j].percentual <
                jogadores[j + 1].percentual) {

                aux = jogadores[j];
                jogadores[j] = jogadores[j + 1];
                jogadores[j + 1] = aux;
            }
        }
    }
}

// Exibe o ranking 
void exibirRanking(Jogador jogadores[], int total) {
    if (total == 0) {
        printf("\nNenhum jogador registrado ainda.\n");
        return;
    }

    ordenarRanking(jogadores, total);

    printf("\n========== RANKING ==========\n");

    for (int i = 0; i < total; i++) {
        printf("%d lugar - %s | Acertos: %d/%d | "
               "Aproveitamento: %.2f%%\n",
               i + 1,
               jogadores[i].nome,
               jogadores[i].acertos,
               jogadores[i].totalPerguntas,
               jogadores[i].percentual);
    }
}