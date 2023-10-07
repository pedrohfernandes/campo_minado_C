#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int positionIsValid(int size, int row, int column);
void checkAndShowAdjacents(int size, int minefield[size][size], int showPosition[size][size], int row, int column);

int main()
{
    printf("\n\n** BEM VINDO AO CAMPO MINADO **\n\n");

    int size = 0;

    printf("\n** Determine o tamanho do Campo Minado **\n");
    printf(">> DICA: Tamanhos ideais para o campo: 8, 9 ou 10 <<\n\n");
    while (size <= 0 || size > 20)
    {
        printf("Digite o tamanho desejado: ");
        scanf("%d", &size);

        if (size <= 0 || size > 20)
            printf("Tamanho invalido!\n\n");
    }

    int showPosition[size][size];
    int minefield[size][size];

    // Inicializa todas as posições do campo minado
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            minefield[i][j] = 0;
            showPosition[i][j] = 0;
        }
    }

    int bombsNumber;

    printf("\n** Determine a quantidade de bombas no Campo Minado **\n");
    printf(">> DICA: Quantidade de bombas ideal para um campo %dx%d: %d <<\n\n", size, size, size > 10 ? size + 5 : size + 1);
    do
    {
        printf("Digite o numero de bombas: ");
        scanf("%d", &bombsNumber);

        if (bombsNumber <= 0 || bombsNumber >= size * size)
            printf("Qunatidade invalida!\n\n");

    } while (bombsNumber <= 0 || bombsNumber >= size * size);

    // Sorteando as posições das bombas
    srand(time(NULL));
    for (int i = 0; i < bombsNumber; i++)
    {
        int row = rand() % size;
        int column = rand() % size;

        if (minefield[row][column] == 0)
            minefield[row][column] = 50; // Número arbitrário escolhido para representar uma bomba

        else // Caso na posição sorteada já exista uma bomba
            i--;
    }

    // Identificando o número de bombas existentes ao redor de uma posição
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (minefield[i][j] >= 50) // Verifica se há bomba na posição dado o número arbitrário definido
            {
                if (positionIsValid(size, i - 1, j))
                    minefield[i - 1][j]++; // Posição acima

                if (positionIsValid(size, i - 1, j - 1))
                    minefield[i - 1][j - 1]++; // Posição diagonal a esquerda acima

                if (positionIsValid(size, i - 1, j + 1))
                    minefield[i - 1][j + 1]++; // Posição diagonal a direita acima

                if (positionIsValid(size, i + 1, j))
                    minefield[i + 1][j]++; // Posição abaixo

                if (positionIsValid(size, i + 1, j - 1))
                    minefield[i + 1][j - 1]++; // Posição diagonal a esquerda abaixo

                if (positionIsValid(size, i + 1, j + 1))
                    minefield[i + 1][j + 1]++; // Posição diagonal a direita abaixo

                if (positionIsValid(size, i, j - 1))
                    minefield[i][j - 1]++; // Posição a esquerda

                if (positionIsValid(size, i, j + 1))
                    minefield[i][j + 1]++; // Posição a direita
            }
        }
    }

    // Exibindo o campo minado
    printf("\nCampo gerado:\n\n");

    int bombSelected = 0;
    int lineSize = (size * 4) + 1; // Relação que permite uma exibição correta do campo

    do
    {
        // Printa os números das colunas
        printf("\t   ");
        for (int i = 0; i < size; i++)
            printf(" %d  ", i);
        printf("\n");

        for (int i = 0; i < size; i++)
        {
            // Printa as linhas de separação
            printf("\t  ");
            for (int a = 0; a < lineSize; a++)
                printf("-");

            // Printa o número das linhas
            printf("\n\t%d |", i);

            // Printa o campo
            for (int j = 0; j < size; j++)
            {
                if (!showPosition[i][j])
                    printf(" \xdb |");
                else
                {
                    if (minefield[i][j] >= 50)
                        printf(" B |");
                    else if (minefield[i][j] == 0)
                        printf("   |");
                    else
                        printf(" %d |", minefield[i][j]);
                }
            }
            printf("\n");

            // Printa a última linha de separação
            if (i == size - 1)
            {
                printf("\t  ");
                for (int a = 1; a <= lineSize; a++)
                    printf("-");
            }
        }
        printf("\n");

        // Verificando se o jogador perdeu
        if (bombSelected)
        {
            printf("\n\nBumm! Voce selecionou uma bomba!\nFim de jogo!\n\n");
            break;
        }

        // Verificando se o jogador ganhou
        int counter = 0;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (showPosition[i][j] == 0 && minefield[i][j] < 50)
                {
                    counter++;
                }
            }
        }
        if (!counter)
        {
            printf("\n\nParabens! Voce nao selecionou nenhuma bomba!\nGanhou o jogo!\n\n");
            break;
        }

        // Escolhendo uma posição
        int row, column;
        printf("\nEscolha uma posicao (formato: \"l c\")\n");
        printf("Digite a posicao que deseja exibir: ");
        scanf("%d %d", &row, &column);
        printf("\n");

        // Determinando a exibição da posição escolhida
        if (minefield[row][column] == 0)
            checkAndShowAdjacents(size, minefield, showPosition, row, column);

        else
            showPosition[row][column] = 1;

        // Determinando o fim do jogo pela escolha de uma bomba
        if (minefield[row][column] >= 50)
            bombSelected = 1;

    } while (1);

    return 0;
}

int positionIsValid(int size, int row, int column)
{
    // Verifica se a posição escolhida pelo usuário é válida
    if (row >= 0 && row < size && column >= 0 && column < size)
        return 1;

    else
        return 0;
}

void checkAndShowAdjacents(int size, int minefield[size][size], int showPosition[size][size], int row, int column)
{
    // Checa se as posições adjacentes também não são bombas e determina sua exibição
    if (positionIsValid(size, row, column))
    {
        showPosition[row][column] = 1;

        if (positionIsValid(size, row - 1, column) && minefield[row - 1][column] == 0 && showPosition[row - 1][column] == 0)
            // Chamada recursiva da função para verificar se o adjacente ao adjacente atual (e etc) também não é bomba
            checkAndShowAdjacents(size, minefield, showPosition, row - 1, column);

        else
        {
            // Exibe a posição adjacente que possui contagem de bombas caso não seja 0
            if (positionIsValid(size, row - 1, column))
                showPosition[row - 1][column] = 1;
        }

        if (positionIsValid(size, row + 1, column) && minefield[row + 1][column] == 0 && showPosition[row + 1][column] == 0)
            checkAndShowAdjacents(size, minefield, showPosition, row + 1, column);

        else
        {
            if (positionIsValid(size, row + 1, column))
                showPosition[row + 1][column] = 1;
        }

        if (positionIsValid(size, row, column - 1) && minefield[row][column - 1] == 0 && showPosition[row][column - 1] == 0)
            checkAndShowAdjacents(size, minefield, showPosition, row, column - 1);

        else
        {
            if (positionIsValid(size, row, column - 1))
                showPosition[row][column - 1] = 1;
        }

        if (positionIsValid(size, row, column + 1) && minefield[row][column + 1] == 0 && showPosition[row][column + 1] == 0)
            checkAndShowAdjacents(size, minefield, showPosition, row, column + 1);

        else
        {
            if (positionIsValid(size, row, column + 1))
                showPosition[row][column + 1] = 1;
        }
    }
}