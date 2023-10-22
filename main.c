#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int positionIsValid(int size, int row, int column);
void checkAndShowAdjacents(int size, int field[size][size], int showPosition[size][size], int row, int column);

int main()
{
    char option = 'S';

    while (option == 'S' || option == 's')
    {
        printf("\n\n** BEM VINDO(A) AO CAMPO MINADO **\n\n");

        int size = 0;

        printf("\n** Determine o tamanho do Campo Minado **\n");
        printf(">> DICA: Tamanhos ideais para o campo: 8, 9 ou 10 <<\n\n");

        while (size < 5 || size > 20)
        {
            printf("Digite o tamanho desejado: ");
            scanf("%d", &size);

            if (size < 5 || size > 20)
                printf("\nTamanho invalido!\nEscolha um numero maior do que 4 e menor do que 21.\n\n");
        }

        int showPosition[size][size];
        int field[size][size];

        // Inicializa todas as posições do campo minado
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                field[i][j] = 0;
                showPosition[i][j] = 0;
            }
        }

        int bombsNumber = 0;

        printf("\n** Determine a quantidade de bombas no Campo Minado **\n");
        printf(">> DICA: Quantidade de bombas ideal para um campo %dx%d: %d <<\n\n", size, size, size > 10 ? size + 5 : size + 1);

        while (bombsNumber <= 0 || bombsNumber >= size * size / 2)
        {
            printf("Digite o numero de bombas: ");
            scanf("%d", &bombsNumber);

            if (bombsNumber <= 0 || bombsNumber >= size * size / 2)
                printf("\nQuantidade invalida!\nEscolha um numero maior do que 0 e menor do que %d\n\n", size * size / 2);
        }

        // Sorteando as posições das bombas
        srand(time(NULL));
        for (int i = 0; i < bombsNumber; i++)
        {
            int row = rand() % size;
            int column = rand() % size;

            if (field[row][column] == 0)
                field[row][column] = 50; // Número arbitrário escolhido para representar uma bomba

            else // Caso na posição sorteada já exista uma bomba
                i--;
        }

        // Identificando o número de bombas existentes ao redor de uma posição
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (field[i][j] >= 50) // Verifica se há bomba na posição dado o número arbitrário definido
                {
                    if (positionIsValid(size, i - 1, j))
                        field[i - 1][j]++; // Posição acima

                    if (positionIsValid(size, i - 1, j - 1))
                        field[i - 1][j - 1]++; // Posição diagonal a esquerda acima

                    if (positionIsValid(size, i - 1, j + 1))
                        field[i - 1][j + 1]++; // Posição diagonal a direita acima

                    if (positionIsValid(size, i + 1, j))
                        field[i + 1][j]++; // Posição abaixo

                    if (positionIsValid(size, i + 1, j - 1))
                        field[i + 1][j - 1]++; // Posição diagonal a esquerda abaixo

                    if (positionIsValid(size, i + 1, j + 1))
                        field[i + 1][j + 1]++; // Posição diagonal a direita abaixo

                    if (positionIsValid(size, i, j - 1))
                        field[i][j - 1]++; // Posição a esquerda

                    if (positionIsValid(size, i, j + 1))
                        field[i][j + 1]++; // Posição a direita
                }
            }
        }

        // Exibindo o campo minado
        printf("\nCampo gerado:\n\n");

        int bombSelected = 0;
        int lineSize = (size * 4) + 1; // Relação que permite uma exibição visual correta do campo

        do
        {
            // Printa os números das colunas
            if (size <= 10)
            {
                printf("\t   ");
                for (int i = 0; i < size; i++)
                    printf(" %d  ", i);

                printf("\n");
            }
            else // Altera a exibição dos números das colunas para mostrar corretamente índices com dois dígitos
            {
                printf("\t    ");
                for (int i = 0; i < size; i++)
                {
                    if (i < 10)
                        printf(" %d  ", i);

                    else
                        printf(" %d ", i);
                }
                printf("\n");
            }

            for (int i = 0; i < size; i++)
            {
                // Printa as linhas de separação
                if (size <= 10)
                {
                    printf("\t  ");
                    for (int a = 0; a < lineSize; a++)
                        printf("-");
                }
                else // Altera a exibição das linhas para se adequar ao layout para índices com dois dígitos
                {
                    printf("\t   ");
                    for (int a = 0; a < lineSize; a++)
                        printf("-");
                }

                // Printa o número das linhas
                if (size <= 10)
                    printf("\n\t%d |", i);
                else // Altera a exibição dos números das linhas para mostrar corretamente índices com dois dígitos
                {
                    if (i < 10)
                        printf("\n\t%d  |", i);

                    else
                        printf("\n\t%d |", i);
                }
                // Printa o campo
                for (int j = 0; j < size; j++)
                {
                    if (!showPosition[i][j])
                        printf(" \xdb |");

                    else
                    {
                        if (field[i][j] >= 50)
                            printf(" B |");

                        else if (field[i][j] == 0)
                            printf("   |");

                        else
                            printf(" %d |", field[i][j]);
                    }
                }
                printf("\n");

                // Printa a última linha de separação
                if (i == size - 1)
                {
                    if (size <= 10)
                    {
                        printf("\t  ");
                        for (int a = 0; a < lineSize; a++)
                            printf("-");
                    }
                    else // Altera a exibição da linha para se adequar ao layout para índices com dois dígitos
                    {
                        printf("\t   ");
                        for (int a = 0; a < lineSize; a++)
                            printf("-");
                    }
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
                    if (showPosition[i][j] == 0 && field[i][j] < 50)
                        counter++;
                }
            }
            if (!counter)
            {
                printf("\n\nParabens! Voce nao selecionou nenhuma bomba!\nGanhou o jogo!\n\n");
                break;
            }

            // Solicitando ao usuário uma escolha de posição
            int row, column;
            printf("\nEscolha uma posicao (formato: \"l c\")\n");
            printf("Digite a posicao que deseja exibir: ");
            scanf("%d %d", &row, &column);
            printf("\n");

            // Determinando a exibição da posição escolhida
            if (positionIsValid(size, row, column) && field[row][column] == 0)
                checkAndShowAdjacents(size, field, showPosition, row, column);

            else
            {
                if (positionIsValid(size, row, column))
                    showPosition[row][column] = 1;
            }

            // Determinando o fim do jogo caso uma bomba seja escolhida
            if (positionIsValid(size, row, column) && field[row][column] >= 50)
                bombSelected = 1;

        } while (1);

        printf("Deseja iniciar um novo jogo (S/N)? ");
        getchar(); // Necessário para capturar o \n armazenado em buffer
        scanf("%c", &option);
    }

    printf("\nSaindo...\n\n");
    return 0;
}

int positionIsValid(int size, int row, int column)
{
    // Verifica se a posição recebida é válida
    if (row >= 0 && row < size && column >= 0 && column < size)
        return 1;

    else
        return 0;
}

void checkAndShowAdjacents(int size, int field[size][size], int showPosition[size][size], int row, int column)
{
    showPosition[row][column] = 1;

    // Checa se as posições adjacentes também não são bombas e determina sua exibição
    if (positionIsValid(size, row - 1, column) && field[row - 1][column] == 0 && showPosition[row - 1][column] == 0)
        // Chamada recursiva da função para verificar se o adjacente ao adjacente atual (e etc) também não é bomba
        checkAndShowAdjacents(size, field, showPosition, row - 1, column);

    else
    {
        // Exibe a posição adjacente que possui contagem de bombas caso não seja 0
        if (positionIsValid(size, row - 1, column))
            showPosition[row - 1][column] = 1;
    }

    if (positionIsValid(size, row + 1, column) && field[row + 1][column] == 0 && showPosition[row + 1][column] == 0)
        checkAndShowAdjacents(size, field, showPosition, row + 1, column);

    else
    {
        if (positionIsValid(size, row + 1, column))
            showPosition[row + 1][column] = 1;
    }

    if (positionIsValid(size, row, column - 1) && field[row][column - 1] == 0 && showPosition[row][column - 1] == 0)
        checkAndShowAdjacents(size, field, showPosition, row, column - 1);

    else
    {
        if (positionIsValid(size, row, column - 1))
            showPosition[row][column - 1] = 1;
    }

    if (positionIsValid(size, row, column + 1) && field[row][column + 1] == 0 && showPosition[row][column + 1] == 0)
        checkAndShowAdjacents(size, field, showPosition, row, column + 1);

    else
    {
        if (positionIsValid(size, row, column + 1))
            showPosition[row][column + 1] = 1;
    }
    // Checando as posições diagonais
    // Direita acima
    if (positionIsValid(size, row - 1, column + 1) && field[row - 1][column + 1] == 0 && showPosition[row - 1][column + 1] == 0)
        checkAndShowAdjacents(size, field, showPosition, row - 1, column + 1);

    else
    {
        if (positionIsValid(size, row - 1, column + 1))
            showPosition[row - 1][column + 1] = 1;
    }
    // Esquerda acima
    if (positionIsValid(size, row - 1, column - 1) && field[row - 1][column - 1] == 0 && showPosition[row - 1][column - 1] == 0)
        checkAndShowAdjacents(size, field, showPosition, row - 1, column - 1);

    else
    {
        if (positionIsValid(size, row - 1, column - 1))
            showPosition[row - 1][column - 1] = 1;
    }
    // Direita abaixo
    if (positionIsValid(size, row + 1, column + 1) && field[row + 1][column + 1] == 0 && showPosition[row + 1][column + 1] == 0)
        checkAndShowAdjacents(size, field, showPosition, row + 1, column + 1);

    else
    {
        if (positionIsValid(size, row + 1, column + 1))
            showPosition[row + 1][column + 1] = 1;
    }
    // Esquerda abaixo
    if (positionIsValid(size, row + 1, column - 1) && field[row + 1][column - 1] == 0 && showPosition[row + 1][column - 1] == 0)
        checkAndShowAdjacents(size, field, showPosition, row + 1, column - 1);

    else
    {
        if (positionIsValid(size, row + 1, column - 1))
            showPosition[row + 1][column - 1] = 1;
    }
}