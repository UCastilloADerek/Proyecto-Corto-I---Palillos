#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void main()
{
  //Existencia/Inventario
  int inventory[3][7] =
  {
          {1, 1, 1, NULL, NULL, NULL, NULL},
       {1, 1, 1, 1, 1, NULL, NULL},
    {1, 1, 1, 1, 1, 1, 1}
  };

  //Sistema de nombres
  char player1[50], player2[50];
  char playerRoster[2][50];
  printf("Ingrese nombre jugador 1\n>");
  scanf("%s", &player1);
  strncpy(playerRoster[0], player1, 50);
  printf("Ingrese nombre jugador 2\n>");
  scanf("%s", &player2);
  strncpy(playerRoster[1], player2, 50);

  bool continueGame = true;
  int score[2] = {0, 0}; //Vector para punteo
  int activePlayer = 1; //Jugador activo
  int currentRow; //Fila seleccionada
  int turn = 1; //Turno actual
  int selectionQuantity; //Cantidad de palillos a elegir
  int selection; //Seleccion de entidades para sistema de eleccion - Pendiente
  int available = 0;
  //Ciclo para turnos
  do
  {
    bool check = true;
    while(check)
    {
      //Imprime datos del juego
      system("clear");
      //Aesthetic
      putchar('+');
      for(int i = 0; i < 17; i++)
      {
        putchar('-');
      }
      printf("+\n");
      //Aesthetic
  
      int limit = 3;
      for(int i = 0; i < 3; i++)
      {
        //Aesthetic
        putchar('|');
        printf("%*s", 6 - i * 2, "");
        //Aesthetic
        for(int j = 0; j < 3 + 2 * i; j++)
        {
          if(inventory[i][j] == 1)
          {
            printf("| ");
          }
          else
          {
            printf("  ");
          }
        }

        //Aesthetic
        printf("%*s", 5 - i * 2, "");
        printf("|\n");
        //Aesthetic
      }
      //Aesthetic
      putchar('+');
      for(int i = 0; i < 17; i++)
      {
        putchar('-');
      }
      printf("+\n\n");
      //Aesthetic
      printf("Jugador actual: %s\n", playerRoster[activePlayer - 1]);
      printf("Turno actual: %i\nFilas disponibles:\n", turn);
      for(int i = 0; i < 3; i++)
      {
        available = 0;
        for (int j = 0; j < 3 + 2 * i; j++)
        {
          available += inventory[i][j];
        }
        if (available > 0)
        {
          check = true;
        }
        else
        {
          check = false;
        }
        if (check)
        {
           printf("Fila %i\n", i + 1);
        }
      }
      printf("Elija una fila disponible\n>");
      scanf("%i", &currentRow);

      available = 0;
      for (int i = 0; i < 3 + 2 * (currentRow - 1); i++)
      {
        available += inventory[currentRow - 1][i];
      }
      if (available > 0)
      {
        check = true;
      }
      else
      {
        check = false;  
      }
      //Valida si la fila seleccionada esta vacia y este dentro de sus limites
      if (currentRow <= 3 && currentRow >= 1 && check)
      {
        printf("Palillos disponibles: ");
        for(int i = 0; i < 3 + 2 * (currentRow - 1); i++)
        {
          if (inventory[currentRow - 1][i] == 1)
          {
            printf("%i", i + 1);
            for(int j = i + 1; j < 3 + 2 * (currentRow - 1); j++)
            {
              if (inventory[currentRow - 1][j] == 1)
              {
                printf(" - ");
                break;
              }
            }
          }
        }
        printf("\n");
        printf("Escoger cantidad de palillos\n>");
        scanf("%i", &selectionQuantity);

        available = 0;
        for (int i = 0; i < 3 + 2 * (currentRow - 1); i++)
        {
          available += inventory[currentRow - 1][i];
        }
        //Sistema de eleccion de palillos: No mayor de la cantidad disponible
        if (selectionQuantity <= available)
        {
          //Valida si la cantidad a retirar es igual a la cantidad restante
          if (selectionQuantity == available)
          {
            for(int j = 0; j < 3 + 2 * (currentRow - 1); j++)
            {
              inventory[currentRow - 1][j] = 0;
            }
          }
          else
          {
            for(int i = 0; i < selectionQuantity; i++)  
            {
              printf("Elija palillo a retirar\n>");
              scanf("%i", &selection);

              //Valida que seleccion este dentro de los limites de la fila y este disponible el palillo
              if (selection <= 3 + 2 * (currentRow - 1) && inventory[currentRow - 1][selection - 1] == 1)
              {
                inventory[currentRow - 1][selection - 1] = 0;
              }
            }
          }
          //Cambia jugador activo para el siguiente turno
          activePlayer = activePlayer == 1 ? 2 : 1;
          turn++;
        }
      }
      available = 0;
      for (int i = 0; i < 3; i++)
      {
        for(int j = 0; j < 3 + 2 * i; j++)
        {
          available += inventory[i][j];
        }
      }
    
      if (available > 1)
      {
        check = true;
      }
      else
      {
        check = false;
      }
    }

    available = 0;
    for (int i = 0; i < 3; i++)
    {
      for(int j = 0; j < 3 + 2 * i; j++)
      {
        available += inventory[i][j];
      }
    }
    //Sistema de punteo
    if(available == 1)
    {
      score[(activePlayer == 0 ? 1 : 0)] += 3;
    }
    else
    {
      score[0] += 1;
      score[1] += 1;
    }

    //Reseteo
    for(int i = 0; i < 3; i++)
    {
      for(int j = 0; j < 3 + 2 * i; j++)
      {
        inventory[i][j] = 1;
      }
    }
    activePlayer = 1;
    turn = 1;

    //Imprime datos finales del juego
    printf("\nPunteos:\n%s: %i\n%s: %i\n", playerRoster[0], score[0], playerRoster[1], score[1]);
    char input[2];
    printf("\n¿Desea jugar de nuevo? (Y/N)\n>");
    scanf("%s", &input);
    
    
    if (strcasecmp(input, "N") == 0)
    {
      continueGame = false;
    }
  } while (continueGame);

  int winner;
  if (score[0] > score[1])
  {
    winner = 0;
  }
  else if(score[1] > score[0])
  {
    winner = 1;
  }
  else
  {
    winner = 2;
  }
  
  printf("Ganador: %s", (winner != 2 ? playerRoster[winner]: "Empate"));
  return;
}