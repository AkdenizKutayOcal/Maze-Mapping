// TODO
// 

char **generateMap();
char **updateMap();
void printMap();
void assignSensorValues();


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
            return 0;
        }
        else if (strchr(input, ' ') != NULL)
        {
            strcpy(sensorValues, input);

            assignSensorValues(map, sensorValues, posRow, posCol);
            printMap(map, totalRow, totalCol, posRow, posCol);
        }
        else
        {
            if(strcmp(input,"gonorth")==0){

                map = updateMap(map,totalRow,totalCol,1,0);
                totalRow++;
            }
            else if(strcmp(input,"gowest")==0){

                map = updateMap(map,totalRow,totalCol,1,0);
                totalCol++;
            }
            else if(strcmp(input,"goeast")==0){

                map = updateMap(map,totalRow,totalCol,1,0);
                totalCol++;
            }
            else if(strcmp(input,"gosouth")==0){

                map = updateMap(map,totalRow,totalCol,0,0);
                totalRow++;
                posRow++;
            }
        }
    }
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

    for (int i = 0; i < row; i++)
    {
        if (posRow == i)
        {
            for (int j = 0; j < col; j++)
            {
                if (j == posCol)
                {
                    printf(".");
                }
                else
                {
                    printf("%c", *(*(map + i) + j));
                }
            }
            printf("\n");
        }
        else
        {
            printf("%s\n", *(map + i));
        }
    }
}

void assignSensorValues(char **map, char *values, int posRow, int posCol)
{

    *(*(map + posRow) + posCol) = ' ';
    *(*(map + posRow) + posCol - 1) = *values;
    *(*(map + posRow - 1) + posCol) = *(values + 2);
    *(*(map + posRow) + posCol + 1) = *(values + 4);
    *(*(map + posRow + 1) + posCol) = *(values + 6);
}

char **updateMap(char **map, int row, int col, int startRow, int startCol)
{
    // copy old array to new one starting from given indexes
    
    char **newMap = generateMap(row, col);
    
    return newMap;
}

