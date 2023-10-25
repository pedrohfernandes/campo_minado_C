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
        for (int row = 0; row < size; row++)
        {
            for (int column = 0; column < size; column++)
            {
                if (field[row][column] >= 50) // Verifica se há bomba na posição dado o número arbitrário definido
                {
                    // Itera por todas as posições adjacentes e incrementa seu valor devido à presença de bomba na posição atual
                    for (int i = -1; i < 2; i++)
                    {
                        for (int j = -1; j < 2; j++)
                        {
                            if (positionIsValid(size, row + i, column + j))
                                field[row + i][column + j]++;
                        }
                    }
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
    int isValid;

    if (row >= 0 && row < size && column >= 0 && column < size)
        // Verifica se a posição recebida é válida
        isValid = 1;

    else
        isValid = 0;

    return isValid;
}

void checkAndShowAdjacents(int size, int field[size][size], int showPosition[size][size], int row, int column)
{
    showPosition[row][column] = 1;

    // Itera por todas as posições adjacentes, verifica se não são bombas e determina sua exibição
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if (row + i == row && column + j == column)
                // Evita que a própria posição seja checada novamente
                continue;

            else if (positionIsValid(size, row + i, column + j) && field[row + i][column + j] == 0 && showPosition[row + i][column + j] == 0)
                // Chamada recursiva da função para verificar se o adjacente ao adjacente atual (e etc) também não é bomba
                checkAndShowAdjacents(size, field, showPosition, row + i, column + j);

            else
            {
                if (positionIsValid(size, row + i, column + j))
                    // Exibe a posição adjacente que possui contagem de bombas caso não seja 0
                    showPosition[row + i][column + j] = 1;
            }
        }
    }
}