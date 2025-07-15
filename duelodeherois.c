#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

typedef struct {
    char nome[20];
    int vida;
    int ataque;
    int defesa;
} Heroi;

int gerarNumeroAleatorio(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

void cadastrarHerois(Heroi herois[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        printf("Digite o nome do heroi numero %d:\n", i + 1);

        fgets(herois[i].nome, 20, stdin);
        herois[i].nome[strcspn(herois[i].nome, "\n")] = '\0';

        herois[i].vida = gerarNumeroAleatorio(50, 100);
        herois[i].ataque = gerarNumeroAleatorio(10, 30);
        herois[i].defesa = gerarNumeroAleatorio(5, 20);
    }
}

void realizarAtaque(Heroi herois[], int atacante, int vitima)
{
    int dano = herois[atacante].ataque - herois[vitima].defesa;

    printf("%s atacou %s\n", herois[atacante].nome, herois[vitima].nome);

    if (dano > 0)
    {
        herois[vitima].vida -= dano;

        printf("%s perdeu %d pontos de vida. agora possui %d pontos de vida.\n", herois[vitima].nome, dano, herois[vitima].vida);
    }
    else
    {
        printf("%s conseguiu defender todo o ataque\n", herois[vitima].nome);
    }
}

int verificarDerrota(Heroi herois[], int indice)
{
    if (herois[indice].vida <= 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    srand(time(NULL));

    Heroi herois[2];

    cadastrarHerois(herois, 2);

    if (herois[0].ataque <= herois[1].defesa && herois[1].ataque <= herois[0].defesa)
    {
        printf("Os herois batalharao para sempre\n");

        return 0;
    }

    int vez = 0;
    while (1)
    {
        printf("Agora eh vez de %s\n", herois[vez].nome);

        realizarAtaque(herois, vez, 1 - vez);

        if (verificarDerrota(herois, 1 - vez))
        {
            printf("%s morreu\n", herois[1 - vez].nome);
            printf("%s eh o ganhador!\n", herois[vez].nome);

            break;
        }

        printf("\n");

        vez = 1 - vez;
    }

    return 0;
}