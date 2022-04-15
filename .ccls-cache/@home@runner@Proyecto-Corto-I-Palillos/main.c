#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
    if(source[row][i] == 1)
    {
      printf("%i", i + 1);
      if(i + 1 < limit)
      {
        if(i < limit - 2)
        {
          printf(" - ");
        }
        else if(source[row][limit - 1] == 1)
        {
          printf(" - ");
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

  int score[2] = {0, 0}; //Vector para punteo
  int activePlayer = 1; //Jugador activo
  int invert; //Jugador inactivo
  int currentRow; //Fila seleccionada
  int turn = 1; //Turno actual
  int selectionQuantity; //Cantidad de palillos a elegir
  int selection; //Seleccion de entidades para sistema de eleccion - Pendiente

  //Ciclo para turnos
  while(checkInventory(inventory))
  {
    //Imprime datos del juego
    system("clear");
    printInventory(inventory);
    printf("Jugador actual: %s\n", playerRoster[activePlayer - 1]);
    printf("Turno actual: %i\n", turn);
    for(int i = 0; i < 3; i++)
    {
      if (checkInventoryRow(inventory, i))
      {
         printf("Row %i disponible\n", i + 1);
       }
      else
      {
        printf("Row %i vacio\n", i + 1);
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
        for(int i = 0; i < selectionQuantity; i++)  
        {
          printf("Elija palillo a retir\n>");
          scanf("%i", &selection);

          //Valida que seleccion este dentro de sus limites y este disponible
          if (selection <= 3 + 2 * (currentRow - 1) && inventory[currentRow - 1][selection - 1] == 1)
          {
            inventory[currentRow - 1][selection - 1] = 0;
          }
        }
        //Cambia jugador activo para el siguiente turno
        if (activePlayer == 1)
        {
          activePlayer = 2;
          invert = 1;
        }
        else
        {
          activePlayer = 1;
          invert = 2;
        }
        turn++;
      }
    }
  }

  //Sistema de punteo
  if(inventoryQuantity(inventory, currentRow - 1) == 1)
  {
    score[invert - 1] += 3;
  }
  else
  {
    score[0] += 1;
    score[1] += 1;
  }

  //Imprime datos finales del juego
  printf("El juego termino\nPunteos:\n%s: %i\n%s: %i\n", playerRoster[0], score[0], playerRoster[1], score[1]);

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