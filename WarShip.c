/*
    > Migliorie per le varibili-coordinate
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SI 1
#define NO 0

void mare_giocatore(char giocatore[8][8], int numero) // stampa mare
{

    printf("\nMare del Giocatore %d\n", numero);
    for (int i = 0; i < 33; i++)
    {
        printf("_");
    }
    printf("\n");
    for (int y = 0; y < 8; y++)
    {
        printf("| ");
        for (int x = 0; x < 8; x++)
        {
            if (x < 7)
            {
                printf("%c - ", giocatore[y][x]);
            }
            else
            {
                printf("%c", giocatore[y][x]);
            }
        }
        printf(" |\n");
    }
    for (int i = 0; i < 33; i++)
    {
        printf("⎺");
    }
}
void posizionamento_navi(char giocatore[8][8], int numero) // posizionamento navi
{
    int yg, xg, y, x, conferma, direzione, continua;
    for (int nave = 0; nave < 4; nave++) // numero di navi g1
    {
        do
        {
            printf("\nGiocatore %d, \nImposta il punto centrale per una nave da 3 celle (Numeri da 1 a 8)\nCoordinata Y:", numero);
            scanf("%d", &yg);
            printf("Coordinata X:");
            scanf("%d", &xg);
            xg = xg - 1;
            yg = yg - 1;

            if ((xg == 0 && yg == 0) || (xg == 7 && yg == 7) || (xg == 0 && yg == 7) || (xg == 7 && yg == 0)) // controllo angoli
            {
                direzione = 3;
            }
            else if ((yg == 7 && xg >= 1 && xg <= 6) || (yg == 0 && xg >= 1 && xg <= 6)) // controllo lato orizzontale
            {
                direzione = 1;
            }
            else if ((xg == 7 && yg >= 1 && yg <= 6) || (xg == 0 && yg >= 1 && yg <= 6)) // controllo lato verticale
            {
                direzione = 0;
            }
            else
            {
                do
                {
                    printf("0: Verticale 1: Orizzontale\nDirezioni: ");
                    scanf("%d", &direzione);
                } while (direzione != 0 && direzione != 1);
            }
            switch (direzione) // controllo della cella O
            {
            case 1:
                for (int i = -1; i <= 1; i++)
                {
                    if (giocatore[yg][xg + i] != 'O')
                    {
                        direzione = 3;
                    }
                }
                if (direzione == 3)
                {
                    printf("Nave presente nelle 3 celle, reimpostare le coordinate\n");
                }
                break;
            case 0:
                for (int i = -1; i <= 1; i++)
                {
                    if (giocatore[yg + i][xg] != 'O')
                    {
                        direzione = 3;
                    }
                }
                if (direzione == 3)
                {
                    printf("Nave presente nelle 3 celle, reimpostare le coordinate");
                }
                break;
            }
            do
            {
                printf("0:NO 1:SI\nConfermi?");
                scanf("%d", &conferma);
            } while (conferma != 0 && conferma != 1);
        } while (conferma == NO || yg < 0 || yg > 7 || xg < 0 || xg > 7 || direzione == 3);

        switch (direzione) // direzione
        {
        case 1:
            for (int i = -1; i <= 1; i++)
            {
                giocatore[yg][xg + i] = 'A' + nave;
            }
            break;
        case 0:
            for (int i = -1; i <= 1; i++)
            {
                giocatore[yg + i][xg] = 'A' + nave;
            }
            break;
        }

        mare_giocatore(giocatore, 1);
    }
}
int attacco_navi(char giocatore[8][8], int numero)
{
    int yg, xg, continua, abbattuto = 0, entra = NO, vittoria_giocatore1, vittoria_giocatore2;
    do
    {
        printf("\nGiocatore %d, \nInserisci coordinate di attacco (Numeri da 1 a 8)\nCoordinata Y:", numero);
        scanf("%d", &yg);
        printf("Coordinata X:");
        scanf("%d", &xg);
        xg = xg - 1;
        yg = yg - 1;

        if (yg < 0 || yg >= 8 || xg < 0 || xg >= 8)
        {
            printf("Coordinate non valide. Riprova.\n");
            continua = SI;
            entra = NO;
            continue;
        }
        else if (giocatore[yg][xg] == 'O')
        {
            printf("Colpo vuoto\n");
            giocatore[yg][xg] = 'X';
            continua = NO;
            entra = NO;
        }
        else if (giocatore[yg][xg] == 'X')
        {
            printf("Colpo già fatto, ritenta\n");
            continua = SI;
            entra = NO;
        }
        else if (giocatore[yg][xg] != 'O' && giocatore[yg][xg] != 'X')
        {
            printf("Nave colpita\n");
            continua = SI;
            giocatore[yg][xg] = tolower(giocatore[yg][xg]);
            entra = SI;
        }
        if (numero == 1)
        {
            if (entra == SI)
            {
                vittoria_giocatore1 = 0;
                for (int nave = 0; nave < 4; nave++)
                {
                    abbattuto = 0;
                    for (int y = 0; y < 8; y++)
                    {
                        for (int x = 0; x < 8; x++)
                        {
                            if (giocatore[y][x] == 'a' + nave)
                            {
                                abbattuto++;
                            }
                        }
                    }
                    if (abbattuto == 3)
                    {
                        continua = SI;
                        printf("Hai abbattuto la nave %c\n", 'A' + nave);
                        vittoria_giocatore1++;
                    }
                }
                if (vittoria_giocatore1 == 4)
                {
                    printf("Vittoria del Giocatore 1");
                    return 1;
                }
            }
            mare_giocatore(giocatore, numero);
        }
        else if (numero == 2)
        {
            if (entra == SI)
            {
                vittoria_giocatore2 = 0;
                for (int nave = 0; nave < 4; nave++)
                {
                    abbattuto = 0;
                    for (int y = 0; y < 8; y++)
                    {
                        for (int x = 0; x < 8; x++)
                        {
                            if (giocatore[y][x] == 'a' + nave)
                            {
                                abbattuto++;
                            }
                        }
                    }
                    if (abbattuto == 3)
                    {
                        continua = SI;
                        printf("Hai abbattuto la nave %c\n", 'A' + nave);
                        vittoria_giocatore2++;
                    }
                }
                if (vittoria_giocatore2 == 4)
                {
                    printf("Vittoria del Giocatore 2");
                    return 1;
                }
            }
            mare_giocatore(giocatore, numero);
        }
    } while (continua == SI);
    return 0;
}
int main()
{
    char giocatore1[8][8], giocatore2[8][8];
    int xg, yg, continua, vittoria, abbattuto = 0, entra = NO, vittoria_giocatore1, vittoria_giocatore2;
    for (int y = 0; y < 8; y++) // riempimento dei mari
    {
        for (int x = 0; x < 8; x++)
        {
            giocatore1[y][x] = 'O';
            giocatore2[y][x] = 'O';
        }
    }
    mare_giocatore(giocatore1, 1);
    mare_giocatore(giocatore2, 2);
    posizionamento_navi(giocatore1, 1);
    posizionamento_navi(giocatore2, 2);
    mare_giocatore(giocatore1, 1);
    mare_giocatore(giocatore2, 2);
    while (SI)
    {
        vittoria = attacco_navi(giocatore1, 1);
        if (vittoria)
            return 0;
        vittoria = attacco_navi(giocatore2, 2);
        if (vittoria)
            return 0;
    }
    return 0;
}
