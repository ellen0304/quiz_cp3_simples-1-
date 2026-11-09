#ifndef FUNCOES_H
#define FUNCOES_H

#define MAX_PERGUNTAS 50
#define MAX_JOGADORES 100
#define TAM_ENUNCIADO 200
#define TAM_ALTERNATIVA 100
#define TAM_NOME 100

typedef struct {
    char enunciado[TAM_ENUNCIADO];
    char alternativas[4][TAM_ALTERNATIVA];
    char respostaCorreta;
} Pergunta;

typedef struct {
    char nome[TAM_NOME];
    int acertos;
    int totalPerguntas;
    float percentual;
} Jogador;

void limparBuffer(void);
void exibirMenu(void);
int carregarPerguntas(Pergunta perguntas[]);
void salvarPerguntas(Pergunta perguntas[], int total);
int carregarHistorico(Jogador jogadores[]);
void salvarJogador(Jogador jogador);
int cadastrarPergunta(Pergunta perguntas[], int total);
void listarPerguntas(Pergunta perguntas[], int total);
int jogarQuiz(Pergunta perguntas[], int totalPerguntas, Jogador jogadores[], int totalJogadores);
void ordenarRanking(Jogador jogadores[], int total);
void exibirRanking(Jogador jogadores[], int total);

#endif
