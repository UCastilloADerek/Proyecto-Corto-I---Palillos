#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void repeat(char c, int count)
{
  for(int i = 0; i < count; i++)
  {
    putchar(c);
  }
}

void printInventory(int source[3][7])
{

//(no se donde se pone no encuentro el in main jajaja)
//str jugador1, jugador2;

//Printf("Jugador 1 bienvenido ingresa tu nombre --: ");
//Scanf("%s \n", &jugador1);

//Printf("Jugador 2 bienvenido ingresa tu nombre --: ");
//Scanf("%s \n", &jugador2);
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
  int inventory[3][7] =
  {
          {1, 1, 1, NULL, NULL, NULL, NULL},
       {1, 1, 1, 1, 1, NULL, NULL},
    {1, 1, 1, 1, 1, 1, 1}
  };

  int currentRow;
  int selection;
  while(checkInventory(inventory))
  {
    system("clear");
    printInventory(inventory);
    for(int i = 0; i < 3; i++)
    {
      if (checkInventoryRow(inventory, i))
      {
         printf("Row %i available\n", i + 1);
       }
      else
      {
        printf("Row %i unavailable\n", i + 1);
      }
    }
    printf("Select row\n>");
    scanf("%i", &currentRow);
    printf("Available in row: "); printRow(inventory, currentRow - 1);
    printf("Choose entities\n>");
    scanf("%i", &selection);
  }
  printf("The game has ended");
  return 0;
}