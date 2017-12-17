#pragma warning(disable : 4996)     /*  used beacuse of newer compiler versions */

#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE      "predaj.txt"    /*  file with car data          */
#define MAX_LINE_CHARS  50              /* longest possible line input  */

/*
 * Function:  OpenRecords
 * --------------------
 * loads records from INPUT_FILE and prints them
 *
 *  file: pointer to main FILE object
 *
 *  returns: pointer fo FILE onject
 *           returns NULL on error (if file could not be open)
 */

FILE* OpenRecords(FILE *file)
{
    char str_buffer[MAX_LINE_CHARS];    /*  buffer for line input */

    /*
     *  Open INPUT_FILE, if unsuccefful return NULL
     */
    if ((file = fopen(INPUT_FILE, "r")) == NULL)
    {
        printf("Neotvoreny subor\n");
        return NULL;
    }

    /*
     * Loop through all the records and print them line by line
     */
    while (feof(file) == 0)
    {
        /* read and print customer name */
        fgets(str_buffer, MAX_LINE_CHARS, file);
        printf("meno priezvisko: %s", str_buffer);

        /* read and print car licence plate */
        fscanf(file, "%s", &str_buffer);
        printf("SPZ: %s\n", str_buffer);

        /* read and print car type  */
        fscanf(file, "%s", &str_buffer);
        printf("typ auta: %s\n", str_buffer);

        /* read and print car price */
        fscanf(file, "%s", &str_buffer);
        printf("cena: %s\n", str_buffer);

        /* read and print date of purchase  */
        fscanf(file, "%s", &str_buffer);
        printf("datum: %s\n", str_buffer);

        printf("\n");

        /*  skips blank line between records    */
        if (feof(file) == 0)
            fscanf(file, "\n");
    }

    return file;
}

int prikaz_o(long current_date, FILE *file)
{
    char name[50], spz[8];
    int car_age;
    double car_price;
    long employee_date;
    if (file == NULL)
        return -1;

    rewind(file);
    while (!(feof(file)))
    {
        /*
         * File reading part
         */
        fgets(name, 50, file);
        fscanf(file, "%s", &spz);
        fscanf(file, "%d", &car_age);
        fscanf(file, "%lf", &car_price);
        fscanf(file, "%ld", &employee_date);
        if (!(feof(file)))                      /*  skips blank line in input file  */
            fscanf(file, "\n");

        /*
         * Logic and printing part
         */
        if (current_date - employee_date >= 10000)
        {
            int i = 0;
            while (1)
            {
                if (name[i] != '\n')
                    printf("%c", name[i]);
                else break;
                i++;
            }
            printf(" %s ", spz);
            if (car_age == 1)
                printf("%.2lf\n", car_price*0.015);
            else if (car_age == 0)
                printf("%.2lf\n", car_price*0.022);
        }

    }
    return 0;
}

int prikaz_n(FILE *file, char **spz)
{
    char buffer[50];
    int cars = 0;
    if (file == NULL)
        return 0;
    if (*spz != NULL)
        free(*spz);
    *spz = NULL;
    rewind(file);
    *spz = (char*)realloc(*spz, (1));
    *spz[0] = '\0';
    while (!(feof(file)))
    {
        fgets(buffer, 50, file);
        fscanf(file, "%s", &buffer);
        cars++;
        *spz = (char*) realloc(*spz, (cars*7)+1);
        strcat(*spz, buffer);
        fgets(buffer, 50, file);
        fgets(buffer, 50, file);
        fgets(buffer, 50, file);
        fgets(buffer, 50, file);
        if (!(feof(file)))          /*  skips blank line in input file  */
            fscanf(file, "\n");
    }
    return 0;
}

int prikaz_s(char *spz)
{
    if (spz == NULL)
    {
        printf("Pole nie je vytvorene\n");
        return 0;
    }
    int i, plates = strlen(spz)/7;
    for (i = 0; i < plates; i++)
        printf("%.2s %.3s %.2s\n", spz+i*7, spz+i*7+2, spz+i*7+5);
    return 0;
}

int prikaz_p(char *spz)
{
    if (spz == NULL)
    {
        printf("Pole nie je vytvorene\n");
        return 0;
    }
    int i, j, plates = strlen(spz) / 7;
    for (i = 0; i < plates; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (spz[j+i*7] != spz[6 - j + i * 7])
                break;
        }
        if (j == 3)
            printf("%.2s\n", spz + i * 7);
    }
    return 0;
}

int prikaz_z(char *spz)
{
    if (spz == NULL)
        return -1;
    char (*prefix)[3] = NULL;
    int *count = NULL;
    int max = 0, i, j, c = 0, cars, cached = 0;
    cars = strlen(spz) / 7;
    for (i = 0; i < cars; i++)
    {
        for (j = 0; j < cached; j++)
        {
            if (prefix != NULL && prefix[j][0] == *(spz + i * 7) && prefix[j][1] == *(spz + i * 7 + 1))
            {
                count[j]++;
                c = 1;
                max = (max > count[j]) ? (max) : (count[j]);
            }
        }

        if (!(c))
        {
            if (prefix == NULL)
            {
                prefix = malloc((cached + 2) * 2 * sizeof(char));
                count = malloc((cached + 2) * sizeof(int));
            }
            else
            {
                prefix = (char *)realloc(prefix, (cached + 2) * 2 * sizeof(char));
                count = (int *)realloc(count, (cached + 2) * sizeof(int));
            }
            prefix[cached][0] = *(spz + i * 7);
            prefix[cached][1] = *(spz + i * 7 + 1);
            count[cached] = 1;
            cached++;
        }
        c = 0;

    }
    for (j = 0; j < cached; j++)
    {
        if (max == count[j])
        {
            printf("%c%c ", prefix[j][0], prefix[j][1]);
            printf("%d\n", count[j]);
        }
    }
    return 0;
}

int main()
{
    char command;       /*  stores the typed in command                 */
    char *spz = NULL;   /*  points to the licence plate array           */
    FILE *file = NULL;  /*  points to the input file                    */
    long date;          /*  stores the typed in date for command 'o'    */

    /*
     *  Read all user commands and execute them
     *  Exit on command 'k'
     */
    while (1)
    {
        scanf("%c", &command);  /* get command  */

        switch (command)
        {
            /*
             * employee bonus
             */
            case 'o':
                scanf("%ld", &date);
                prikaz_o(date, file);
                break;

            /*
             * open records and print them out
             */
            case 'v':
                file = OpenRecords(file);
                break;

            /*
             * print best selling region
             */
            case 'z':
                prikaz_z(spz);
                break;

            /*
             * create licence plate array
             */
            case 'n':
                prikaz_n(file, &spz);
                break;

            /*
             * print licence plates
             */
            case 's':
                prikaz_s(spz);
                break;

            /*
             * print licence plate palindromes
             */
            case 'p':
                prikaz_p(spz);
                break;

            /*
             * exit command
             */
            case 'k':
                return 0;
                break;

            /*
             * blank line entered
             */
            case '\n':
                break;

            /*
             * command not recognized
             */
            default:
                printf("Command not recognized! %c\n", command);

        }
    }
}
