#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **generateMap();
char **updateMap();
void printMap();
void printMapFull();
void assignSensorValues();
void findMapBounds();

int bound_x_s = 0, bound_x_e = 0, bound_y_s = 0, bound_y_e = 0;

int main(int argc, char *argv[])
{
    int totalRow = 3, totalCol = 3; // total number of Rows and Columns
    int posRow = 1, posCol = 1;     // position of the robot

    char **map; // map double char array
    char *sensorValues, *input;

    sensorValues = (char *)malloc(9 * sizeof(char));
    input = (char *)malloc(256 * sizeof(char));
    map = generateMap(3, 3);

    while (fgets(input, sizeof(input), stdin) != NULL)
    {
        scanf("%[^\n]s", input);

        if (strcmp(input, " ") == 0 || strcmp(input, "\n") == 0)
        {
            break;
        }
        else if (strchr(input, ' ') != NULL)
        {
            strcpy(sensorValues, input);

            assignSensorValues(map, sensorValues, posRow, posCol);
            //printMap(map, totalRow, totalCol, posRow, posCol);
        }
        else
        {
            if (strcmp(input, "gonorth") == 0)
            {

                if (posRow - 2 >= 0)
                {
                    posRow--;
                }
               
                else
                {
                    map = updateMap(map, totalRow, totalCol, totalRow + 1, totalCol, 1, 0);
                    totalRow++;
                }

                //printMap(map, totalRow, totalCol, posRow, posCol);
            }
            else if (strcmp(input, "gowest") == 0)
            {

                if (posCol - 2 >= 0)
                {
                    posCol--;
                }
              
                else
                {
                    map = updateMap(map, totalRow, totalCol, totalRow, totalCol + 1, 0, 1);
                    totalCol++;
                }
                //printMap(map, totalRow, totalCol, posRow, posCol);
            }
            else if (strcmp(input, "goeast") == 0)
            {
                //printf("gek3");
                if (posCol + 2 < totalCol)
                {
                    posCol++;
                }
                else
                {
                    map = updateMap(map, totalRow, totalCol, totalRow, totalCol + 1, 0, 0);
                    totalCol++;
                    posCol++;
                }
                //printMap(map, totalRow, totalCol, posRow, posCol);
            }
            else if (strcmp(input, "gosouth") == 0)
            {
                if (posRow + 2 < totalRow)
                {
                    posRow++;
                }
            
                else
                {

                    map = updateMap(map, totalRow, totalCol, totalRow + 1, totalCol, 0, 0);
                    totalRow++;
                    posRow++;
                }

                //printMap(map, totalRow, totalCol, posRow, posCol);
            }
        }
    }

    //printMapFull(map, totalRow, totalCol, posRow, posCol);
    //printf("\n\n");
    findMapBounds(map, totalRow, totalCol);

    printMap(map, (bound_y_e - bound_y_s) + 1, (bound_x_e - bound_x_s) + 1, posRow - bound_y_s, posCol - bound_x_s);
}

char **generateMap(int row, int col)
{

    char **matrix;
    matrix = (char **)malloc(row * sizeof(char *));

    for (int i = 0; i < row; i++)
    {
        *(matrix + i) = malloc(col * sizeof(char));
        for (int j = 0; j < col; j++)
        {
            strcat(*(matrix + i), "u");
        }
        *(matrix + i) = realloc(*(matrix + i), strlen(*(matrix + i) + 1));
    }

    return matrix;
}

void printMap(char **map, int row, int col, int posRow, int posCol)
{

    //printf("row %d col %d posRow %d posCol %d\n",row,col,posRow,posCol);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (posRow == i && posCol == j)
            {
                printf(".");
            }

            else if (*(*(map + i + bound_y_s) + j + bound_x_s) == 'o')
            {
                printf(" ");
            }

            else
            {
                printf("%c", *(*(map + i + bound_y_s) + j + bound_x_s));
            }
        }
        printf("\n");
    }
}

void printMapFull(char **map, int row, int col, int posRow, int posCol)
{

    printf("row %d col %d posRow %d posCol %d\n", row, col, posRow, posCol);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (posRow == i && posCol == j)
            {
                printf(".");
            }

            else if (*(*(map + i) + j) == 'o')
            {
                printf(" ");
            }

            else
            {
                printf("%c", *(*(map + i) + j));
            }
        }
        printf("\n");
    }
}

void assignSensorValues(char **map, char *values, int posRow, int posCol)
{

    *(*(map + posRow) + posCol) = 'o';
    *(*(map + posRow) + posCol - 1) = *values;
    *(*(map + posRow - 1) + posCol) = *(values + 2);
    *(*(map + posRow) + posCol + 1) = *(values + 4);
    *(*(map + posRow + 1) + posCol) = *(values + 6);
}

char **updateMap(char **map, int oldRow, int oldCol, int newRow, int newCol, int startRow, int startCol)
{
    // copy old array to new one starting from given indexes

    char **newMap = generateMap(newRow, newCol);

    for (int i = 0; i < oldRow; i++)
    {
        for (int j = 0; j < oldCol; j++)
        {
            *(*(newMap + startRow + i) + startCol + j) = *(*(map + i) + j);
        }
        //printf("\n");
    }

    free(map);
    return newMap;
}

void findMapBounds(char **map, int row, int col)
{
    bound_x_s = row;
    bound_x_e = 0;
    bound_y_s = col;
    bound_y_e = 0;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (*(*(map + i) + j) == 'o' || *(*(map + i) + j) == 'w')
            {
                if (i < bound_y_s)
                {
                    bound_y_s = i;
                }
                if (i > bound_y_e)
                {
                    bound_y_e = i;
                }
                if (j < bound_x_s)
                {
                    bound_x_s = j;
                }
                if (j > bound_x_e)
                {
                    bound_x_e = j;
                }
            }
        }
    }

    //printf("xs %d xe%d ys%d ye%d\n", bound_x_s, bound_x_e, bound_y_s, bound_y_e);
}
