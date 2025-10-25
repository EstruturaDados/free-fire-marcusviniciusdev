#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Novato
// Este programa simula o gerenciamento básico de uma mochila com itens coletados durante a fuga de uma ilha.

#define MAX_ITENS 10
#define TAM_NOME 50
#define TAM_TIPO 30

// Struct Item:
// Representa um componente com nome, tipo e quantidade.
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

// Vetor mochila:
// Armazena até 10 itens coletados.
Item mochila[MAX_ITENS];
int numItens = 0;

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.
void limparTela() {
    for (int i = 0; i < 50; i++) {
        printf("\n");
    }
}

// exibirMenu():
// Apresenta o menu principal ao jogador.
void exibirMenu() {
    printf("\n========================================\n");
    printf("   CODIGO DA ILHA - EDICAO FREE FIRE\n");
    printf("   Nivel: NOVATO - Inventario Basico\n");
    printf("========================================\n");
    printf("Itens na mochila: %d/%d\n", numItens, MAX_ITENS);
    printf("========================================\n");
    printf("1. Adicionar um item\n");
    printf("2. Remover um item\n");
    printf("3. Listar todos os itens\n");
    printf("0. Sair\n");
    printf("========================================\n");
    printf("Escolha uma opcao: ");
}

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo e quantidade.
void inserirItem() {
    if (numItens >= MAX_ITENS) {
        printf("\n[ERRO] Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novoItem;

    printf("\n--- ADICIONAR ITEM ---\n");
    printf("Nome do item: ");
    scanf(" %[^\n]", novoItem.nome);

    printf("Tipo do item: ");
    scanf(" %[^\n]", novoItem.tipo);

    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);

    mochila[numItens] = novoItem;
    numItens++;

    printf("\n[SUCESSO] Item '%s' adicionado a mochila!\n", novoItem.nome);
}

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.
void removerItem() {
    if (numItens == 0) {
        printf("\n[ERRO] Mochila vazia! Nao ha itens para remover.\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\n--- REMOVER ITEM ---\n");
    printf("Digite o nome do item a ser removido: ");
    scanf(" %[^\n]", nomeBusca);

    int indiceEncontrado = -1;

    // Busca o item pelo nome
    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            indiceEncontrado = i;
            break;
        }
    }

    if (indiceEncontrado == -1) {
        printf("\n[ERRO] Item '%s' nao encontrado na mochila.\n", nomeBusca);
        return;
    }

    // Reorganiza o vetor, movendo os itens posteriores uma posição para trás
    for (int i = indiceEncontrado; i < numItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    numItens--;
    printf("\n[SUCESSO] Item '%s' removido da mochila!\n", nomeBusca);
}

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.
void listarItens() {
    if (numItens == 0) {
        printf("\n[INFO] Mochila vazia! Nenhum item para exibir.\n");
        return;
    }

    printf("\n========================================\n");
    printf("   ITENS NA MOCHILA\n");
    printf("========================================\n");
    printf("%-20s %-15s %s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("----------------------------------------\n");

    for (int i = 0; i < numItens; i++) {
        printf("%-20s %-15s %d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }

    printf("========================================\n");
}

int main() {
    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 0:
                printf("\n[INFO] Saindo do programa. Boa sorte na ilha!\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida! Tente novamente.\n");
        }

        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar();
            getchar();
            limparTela();
        }

    } while (opcao != 0);

    return 0;
}
