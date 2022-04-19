#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//Para repetir un caracter
void repeat(char c, int count)
{
  for(int i = 0; i < count; i++)
  {
    putchar(c);
  }
}

//Imprimir la existencia
void printInventory(int source[3][7])
{
  //Aesthetic
  putchar('+');
  repeat('-', 17);
  printf("+\n");
  //Aesthetic
  
  int limit = 3;
  for(int i = 0; i < 3; i++)
  {
    //Aesthetic
    putchar('|');
    printf("%*s", 6 - i * 2, "");
    //Aesthetic
    for(int j = 0; j < limit; j++)
    {
      if(source[i][j] == 1)
      {
        printf("| ");
      }
      else
      {
        printf("  ");
      }
    }
    limit += 2;

    //Aesthetic
    printf("%*s", 5 - i * 2, "");
    printf("|\n");
    //Aesthetic
  }
  //Aesthetic
  putchar('+');
  repeat('-', 17);
  printf("+\n\n");
  //Aesthetic
}

//Revisar si la existencia tiene mas que 1
bool checkInventory(int source[3][7])
{
  int available = 0;
  int limit = 3;
  for (int i = 0; i < 3; i++)
  {
    for(int j = 0; j < limit; j++)
    {
      available += source[i][j];
    }
    limit += 2;
  }
  if (available > 1)
  {
    return true;
  }
  return false;
}

//Regresa cantidad de palillos disponibles
int inventoryQuantity(int source[3][7], int row)
{
  int available = 0;
  int limit = 3 + 2 * row;
  for (int i = 0; i < limit; i++)
  {
    available += source[row][i];
  }
  return available;
}

//Revisar si una fila tiene la cantidad de entidades disponibles mayor a 0
bool checkInventoryRow(int source[3][7], int row)
{
  int available = 0;
  int limit = 3 + 2 * row;
  for (int i = 0; i < limit; i++)
  {
    available += source[row][i];
  }
  if (available > 0)
  {
    return true;
  }
  return false;
}

//Imprime una fila
void printRow(int source[3][7], int row)
{
  int limit = 3 + 2 * row;
  for(int i = 0; i < limit; i++)
  {
    if (source[row][i] == 1)
    {
      printf("%i", i + 1);
      for(int j = i + 1; j < limit; j++)
      {
        if (source[row][j] == 1)
        {
          printf(" - ");
          break;
        }
      }
    }
  }
  printf("\n");
}

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

  //Ciclo para turnos
  do
  {
    while(checkInventory(inventory))
    {
      //Imprime datos del juego
      system("clear");
      printInventory(inventory);
      printf("Jugador actual: %s\n", playerRoster[activePlayer - 1]);
      printf("Turno actual: %i\nFilas disponibles:\n", turn);
      for(int i = 0; i < 3; i++)
      {
        if (checkInventoryRow(inventory, i))
        {
           printf("Fila %i\n", i + 1);
        }
      }
      printf("Elija una fila disponible\n>");
      scanf("%i", &currentRow);

      //Valida si la fila seleccionada esta vacia y este dentro de sus limites
      if (currentRow <= 3 && currentRow >= 1 && checkInventoryRow(inventory, currentRow - 1))
      {
        printf("Palillos disponibles: "); printRow(inventory, currentRow - 1);
        printf("Escoger cantidad de palillos\n>");
        scanf("%i", &selectionQuantity);

        //Sistema de eleccion de palillos: No mayor de la cantidad disponible
        if (selectionQuantity <= inventoryQuantity(inventory, currentRow - 1))
        {
          //Valida si la cantidad a retirar es igual a la cantidad restante
          if (selectionQuantity == inventoryQuantity(inventory, currentRow - 1))
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
    }  
    //Sistema de punteo
    if(inventoryQuantity(inventory, currentRow - 1) == 1)
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