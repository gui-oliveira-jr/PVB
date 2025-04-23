#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ARQUIVO "plateia.txt"
#define LINHAS 10
#define COLUNAS 12

int entradaInt(char *cabecalho)
{
    char s[100];
    int valor;
    while (1)
    {
        printf("%s", cabecalho);
        scanf("%s", s);
        int ok = 1;
        for (int i = 0; s[i]; i++)
        {
            if (!isdigit(s[i]))
            {
                ok = 0;
                break;
            }
        }
        if (!ok)
        {
            printf("Nao e um inteiro! ");
            continue;
        }
        valor = atoi(s);
        break;
    }
    return valor;
}

char entradaChar(char *cabecalho, char opcoes[])
{
    char s[10];
    while (1)
    {
        printf("%s", cabecalho);
        scanf("%s", s);
        fflush(stdin);
        if (strlen(s) == 1)
        {
            char c = toupper(s[0]);
            for (int i = 0; opcoes[i]; i++)
            {
                if (c == opcoes[i])
                    return c;
            }
        }
        printf("Opcao invalida! ");
    }
}

char **criarMatriz()
{
    char **matriz = malloc(LINHAS * sizeof(char *));
    for (int i = 0; i < LINHAS; i++)
    {
        matriz[i] = malloc(COLUNAS * sizeof(char));
    }
    return matriz;
}

void liberarMatriz(char **matriz)
{
    for (int linha = 0; linha < LINHAS; linha++)
    {
        free(matriz[linha]);
    }
    free(matriz);
}

void salvarMatriz(char **matriz)
{
    FILE *f = fopen(ARQUIVO, "w");
    for (int linha = 0; linha < LINHAS; linha++)
    {
        for (int coluna = 0; coluna < COLUNAS; coluna++)
            fputc(matriz[linha][coluna], f);
        fputc('\n', f);
    }
    fclose(f);
}

void carregarMatriz(char **m)
{
    FILE *arquivo = fopen(ARQUIVO, "r");
    if (!arquivo)
    {
        arquivo = fopen(ARQUIVO, "w");
        for (int i = 0; i < LINHAS; i++)
        {
            for (int j = 0; j < COLUNAS; j++)
            {
                fputc('-', arquivo);
                m[i][j] = '-';
            }
            fputc('\n', arquivo);
        }
        fclose(arquivo);
    }
    else
    {
        for (int i = 0; i < LINHAS; i++)
        {
            for (int j = 0; j < COLUNAS; j++)
                m[i][j] = fgetc(arquivo);
            fgetc(arquivo);
        }
        fclose(arquivo);
    }
}

void mostrarPlateia(char **m)
{
    printf("PLATEIA\n");
    printf("------------------------------------------\n");
    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            if (m[i][j] == '-')
            {
                int num = i * COLUNAS + j + 1;
                printf("%4d", num);
            }
            else
                printf("    ");
        }
        printf("\n");
    }
    printf("------------------------------------------\n");
    printf("FIM PLATEIA\n");
}

void mostrarOcupacao(char **m)
{
    int meia = 0, inteira = 0;
    printf("OCUPACAO\n");
    printf("------------------------------\n");
    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            char c = m[i][j];
            if (c == '-')
                printf(" - ");
            else
            {
                printf(" %c ", tolower(c));
                if (tolower(c) == 'm')
                    meia++;
                if (tolower(c) == 'i')
                    inteira++;
            }
        }
        printf("\n");
    }
    printf("------------------------------\n");
    printf("Poltronas meias vendidas....: %d\n", meia);
    printf("Poltronas inteiras vendidas.: %d\n", inteira);
    printf("------------------------------\n");
    printf("FIM OCUPACAO\n");
}

void venderIngresso(char **m)
{
    int num;
    char tipo;
    while (1)
    {
        mostrarPlateia(m);
        num = entradaInt("Digite o numero da poltrona <1..120> (zero encerra): ");
        if (num == 0)
            return;
        if (num < 1 || num > LINHAS * COLUNAS)
        {
            printf("Valor deve estar entre 1 e %d.\n", LINHAS * COLUNAS);
            continue;
        }
        int i = (num - 1) / COLUNAS;
        int j = (num - 1) % COLUNAS;
        if (m[i][j] != '-')
        {
            printf("Poltrona ocupada. Digite outro numero de poltrona: ");
            continue;
        }
        break;
    }

    while (1)
    {
        tipo = entradaChar("Digite se a entrada e (m)eia ou (i)nteira: ", "MI");
        tipo = tolower(tipo);
        if (tipo == 'm' || tipo == 'i')
            break;
    }

    int i = (num - 1) / COLUNAS;
    int j = (num - 1) % COLUNAS;

    m[i][j] = tipo;

    salvarMatriz(m);

    printf("Poltrona vendida: %d (%s).\n", num, tipo == 'm' ? "meia" : "inteira");
    printf("(Fileira %d, coluna %d).\n", i + 1, j + 1);
    
    int op = entradaInt("Vender outro ingresso (0:nao; 1:sim)? ");
    if (op == 1)
        venderIngresso(m);
}

void cancelarIngresso(char **m)
{
    int num;
    while (1)
    {
        printf("CANCELAMENTO DE INGRESSOS\n");
        num = entradaInt("Digite a poltrona a cancelar (zero encerra): ");
        if (num == 0)
            return;
        if (num < 1 || num > LINHAS * COLUNAS)
        {
            printf("Valor deve estar entre 1 e %d.\n", LINHAS * COLUNAS);
            continue;
        }
        int i = (num - 1) / COLUNAS, j = (num - 1) % COLUNAS;
        if (m[i][j] == '-')
        {
            printf("Poltrona vazia. Digite outra poltrona: ");
            continue;
        }
        char tipo = m[i][j];
        m[i][j] = '-';
        salvarMatriz(m);
        printf("Poltrona com venda cancelada: %d (%s).\n", num, tipo == 'm' ? "meia" : "inteira");
        break;
    }
    int op;
    do
    {
        op = entradaInt("Cancelar outro ingresso (0:nao; 1:sim)? ");
        if (op < 0 || op > 1)
            printf("Valor deve estar entre 0 e 1.\n");
    } while (op < 0 || op > 1);
    if (op == 1)
        cancelarIngresso(m);
}

void menu()
{
    printf("-------------------------------\n");
    printf("             MENU\n");
    printf("-------------------------------\n");
    printf("0-Sair do programa\n");
    printf("1-Mostrar plateia\n");
    printf("2-Mostrar ocupacao\n");
    printf("3-Vender ingresso\n");
    printf("4-Cancelar ingresso (devolucao)\n");
    printf("-------------------------------\n");
}

int main()
{
    char **plateia = criarMatriz();
    carregarMatriz(plateia);
    int opc;
    do
    {
        menu();
        opc = entradaInt("Escolha uma opcao: ");
        switch (opc)
        {
        case 0:
            break;
        case 1:
            mostrarPlateia(plateia);
            break;
        case 2:
            mostrarOcupacao(plateia);
            break;
        case 3:
            venderIngresso(plateia);
            break;
        case 4:
            cancelarIngresso(plateia);
            break;
        default:
            printf("Valor deve estar entre 0 e 4.\n");
            break;
        }
    } while (opc != 0);
    printf("Programa encerrado com sucesso...\n");
    liberarMatriz(plateia);
    return 0;
}
