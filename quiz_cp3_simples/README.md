# Quiz em C — CP3

## Sobre o projeto

O Quiz em C é um projeto acadêmico desenvolvido para a disciplina de programação, com o objetivo de aplicar os principais conceitos estudados durante o semestre utilizando a linguagem C.

O sistema permite realizar quizzes, armazenar perguntas e registrar informações em arquivos, trabalhando com organização e manipulação de dados.

## Tecnologias utilizadas

- Linguagem C
- GCC (compilador)
- Visual Studio Code

## Conceitos aplicados

- Structs (estruturas)
- Vetores
- Funções
- Arquivos de texto
- Ordenação Bubble Sort

## Estrutura do projeto

```text
quiz_cp3_simples/
│
├── src/
│   ├── main.c
│   └── funcoes.c
│
├── include/
│   └── funcoes.h
│
├── data/
│   ├── perguntas.txt
│   └── historico.txt
│
├── README.md
```

## Como executar no Windows

### 1. Abrir o projeto

Abra a pasta `quiz_cp3_simples` no Visual Studio Code.

### 2. Abrir o terminal

Acesse Terminal → Novo Terminal.

### 3. Compilar o programa

Execute:

```powershell
gcc -Wall -Wextra -Iinclude src/main.c src/funcoes.c -o quiz.exe
```

### 4. Executar o programa

Após a compilação sem erros, execute:

```powershell
.\quiz.exe
```

## Links do projeto

**Repositório no GitHub:**

https://github.com/ellen0304/quiz_cp3_simples-1-/tree/main

**Vídeo de demonstração (não listado):**

https://drive.google.com/file/d/1N5xQpAp_ghdv7IJBKWMBgioc0Ro7Vsy8/view?usp=sharing

## Objetivo acadêmico

Este projeto representa a aplicação prática dos conhecimentos adquiridos durante o semestre, reunindo conceitos de lógica de programação, estruturas de dados, funções, manipulação de arquivos e ordenação em linguagem C.

**Projeto desenvolvido para fins acadêmicos — CP3.**