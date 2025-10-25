#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

#define MAX_ITENS 10
#define TAM_NOME 50
#define TAM_TIPO 30

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).
typedef enum {
    ORDENAR_POR_NOME = 1,
    ORDENAR_POR_TIPO,
    ORDENAR_POR_PRIORIDADE
} CriterioOrdenacao;

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
    int prioridade;  // 1 a 5
} Item;

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).
Item mochila[MAX_ITENS];
int numItens = 0;
int comparacoes = 0;
bool ordenadaPorNome = false;

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.
void limparTela() {
    for (int i = 0; i < 50; i++) {
        printf("\n");
    }
}

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.
void exibirMenu() {
    printf("\n========================================\n");
    printf("   CODIGO DA ILHA - EDICAO FREE FIRE\n");
    printf("   Nivel: MESTRE - Ordenacao e Busca Binaria\n");
    printf("========================================\n");
    printf("Itens na mochila: %d/%d\n", numItens, MAX_ITENS);
    printf("Ordenada por nome: %s\n", ordenadaPorNome ? "SIM" : "NAO");
    printf("========================================\n");
    printf("1. Adicionar um item\n");
    printf("2. Remover um item\n");
    printf("3. Listar todos os itens\n");
    printf("4. Ordenar os itens por criterio\n");
    printf("5. Realizar busca binaria por nome\n");
    printf("0. Sair\n");
    printf("========================================\n");
    printf("Escolha uma opcao: ");
}

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".
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

    do {
        printf("Prioridade (1 a 5): ");
        scanf("%d", &novoItem.prioridade);
        if (novoItem.prioridade < 1 || novoItem.prioridade > 5) {
            printf("[ERRO] Prioridade deve estar entre 1 e 5!\n");
        }
    } while (novoItem.prioridade < 1 || novoItem.prioridade > 5);

    mochila[numItens] = novoItem;
    numItens++;
    ordenadaPorNome = false;  // Ao adicionar, a lista não está mais ordenada

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
    printf("%-20s %-15s %-12s %s\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
    printf("--------------------------------------------------------\n");

    for (int i = 0; i < numItens; i++) {
        printf("%-20s %-15s %-12d %d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade,
               mochila[i].prioridade);
    }

    printf("========================================\n");
}

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)
void insertionSort(CriterioOrdenacao criterio) {
    comparacoes = 0;

    for (int i = 1; i < numItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;

        // Define a condição de comparação baseada no critério
        bool moverElemento = false;

        while (j >= 0) {
            comparacoes++;

            if (criterio == ORDENAR_POR_NOME) {
                moverElemento = strcmp(mochila[j].nome, chave.nome) > 0;
            } else if (criterio == ORDENAR_POR_TIPO) {
                moverElemento = strcmp(mochila[j].tipo, chave.tipo) > 0;
            } else if (criterio == ORDENAR_POR_PRIORIDADE) {
                // Prioridade: da mais alta (5) para a mais baixa (1)
                moverElemento = mochila[j].prioridade < chave.prioridade;
            }

            if (!moverElemento) {
                break;
            }

            mochila[j + 1] = mochila[j];
            j--;
        }

        mochila[j + 1] = chave;
    }

    // Atualiza flag se ordenado por nome
    if (criterio == ORDENAR_POR_NOME) {
        ordenadaPorNome = true;
    } else {
        ordenadaPorNome = false;
    }
}

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).
void menuDeOrdenacao() {
    if (numItens == 0) {
        printf("\n[INFO] Mochila vazia! Nenhum item para ordenar.\n");
        return;
    }

    int opcao;

    printf("\n--- ORDENAR ITENS ---\n");
    printf("Escolha o criterio de ordenacao:\n");
    printf("1. Ordenar por nome\n");
    printf("2. Ordenar por tipo\n");
    printf("3. Ordenar por prioridade\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    CriterioOrdenacao criterio;

    switch (opcao) {
        case 1:
            criterio = ORDENAR_POR_NOME;
            break;
        case 2:
            criterio = ORDENAR_POR_TIPO;
            break;
        case 3:
            criterio = ORDENAR_POR_PRIORIDADE;
            break;
        default:
            printf("\n[ERRO] Opcao invalida!\n");
            return;
    }

    insertionSort(criterio);

    printf("\n[SUCESSO] Itens ordenados com sucesso!\n");
    printf("Comparacoes realizadas: %d\n", comparacoes);
}

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
void buscaBinariaPorNome() {
    if (numItens == 0) {
        printf("\n[INFO] Mochila vazia! Nenhum item para buscar.\n");
        return;
    }

    if (!ordenadaPorNome) {
        printf("\n[ERRO] A mochila precisa estar ordenada por nome para realizar busca binaria!\n");
        printf("Utilize a opcao 4 e escolha 'Ordenar por nome' primeiro.\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\n--- BUSCA BINARIA POR NOME ---\n");
    printf("Digite o nome do item a ser buscado: ");
    scanf(" %[^\n]", nomeBusca);

    int esquerda = 0;
    int direita = numItens - 1;
    int indiceEncontrado = -1;

    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        int comparacao = strcmp(mochila[meio].nome, nomeBusca);

        if (comparacao == 0) {
            indiceEncontrado = meio;
            break;
        } else if (comparacao < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }

    if (indiceEncontrado != -1) {
        printf("\n========================================\n");
        printf("   ITEM ENCONTRADO!\n");
        printf("========================================\n");
        printf("Nome:       %s\n", mochila[indiceEncontrado].nome);
        printf("Tipo:       %s\n", mochila[indiceEncontrado].tipo);
        printf("Quantidade: %d\n", mochila[indiceEncontrado].quantidade);
        printf("Prioridade: %d\n", mochila[indiceEncontrado].prioridade);
        printf("========================================\n");
    } else {
        printf("\n[ERRO] Item '%s' nao encontrado na mochila.\n", nomeBusca);
    }
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
            case 4:
                menuDeOrdenacao();
                break;
            case 5:
                buscaBinariaPorNome();
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
