#pragma warning(disable : 4996)     /*  used beacuse of newer compiler versions */

#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE          "predaj.txt"    /* file with car data               */
#define MAX_LINE_CHARS      50              /* longest possible line input      */
#define LICENCE_PLATE_CHARS 7               /* num of chars in a licence plate  */
#define TRUE                1
#define FALSE               0


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


/*
 * Function:  EmployeeBonus
 * --------------------
 * prints out the bonuses each employee should receive to the current date
 *
 *  current_date: int representation on current date
 *  file:         pointer to main FILE object
 *
 *  returns: 0
 */

int EmployeeBonus(long current_date, FILE *file)
{
    char licence_plate[LICENCE_PLATE_CHARS+1];  /* buffer for licence plate     */
    char name[MAX_LINE_CHARS];  /* buffer for seller employee   */
    int car_age;                /* buffer for car age           */
    double car_price;           /* buffer for car price         */
    long purchase_date;         /* buffer for date of purchace  */

    /* check whether file is open   */
    if (file == NULL)
        return -1;

    rewind(file);   /* move cursor to beginning of INPUT_FILE   */

    /*
     *  Read through the file and print the bonuses
     */
    while (feof(file) == 0)
    {
        /*
         * File reading part
         */
        fgets(name, MAX_LINE_CHARS, file);      /* read emplayee name   */
        fscanf(file, "%s", &licence_plate);     /* read licence plate   */
        fscanf(file, "%d", &car_age);           /* read car age         */
        fscanf(file, "%lf", &car_price);        /* read car price       */
        fscanf(file, "%ld", &purchase_date);    /* read purchase date   */

        if (!(feof(file)))                      /*  skips blank line in input file  */
            fscanf(file, "\n");


        /*
         * Logic and printing part
         */
        if (current_date - purchase_date >= 10000)  /* 10000 is one year defference */
        {
            int char_index = 0;     /* used in for cycle    */

            /*
             *  print employee name by character until '\n' character
             */
            while (1)
            {
                if (name[char_index] != '\n')
                    printf("%c", name[char_index]);
                else
                    break;
                char_index++;
            }

            /* print licen plate    */
            printf(" %s ", licence_plate);

            /*
             *  print employee bonus
             */
            if (car_age == 1)       /* if new car   */
                printf("%.2lf\n", car_price*0.015);
            else if (car_age == 0)  /* if old car   */
                printf("%.2lf\n", car_price*0.022);
        }

    }
    return 0;
}


/*
 * Function:  LoadLicencePlates
 * --------------------
 * loads records from INPUT_FILE and stores them into an array
 *
 *  file:           pointer to main FILE object
 *  licence_plates: pointer to licence plate array
 *
 *  returns: 0
 */

int LoadLicencePlates(FILE *file, char **licence_plates)
{
    char buffer[MAX_LINE_CHARS];    /*  buffer for line input */
    int puchaces = 0;               /*  stores the number of purchaces  */

    /* check whether file is open   */
    if (file == NULL)
        return 0;

    /* delete any existing records from the array   */
    if (*licence_plates != NULL)
    {
        free(*licence_plates);
        *licence_plates = NULL;
    }

    rewind(file);   /* move cursor to beginning of INPUT_FILE   */

    /* create single char string '\0'   */
    *licence_plates = (char*)realloc(*licence_plates, sizeof(char));
    *licence_plates[0] = '\0';

    /*
     *  loop through all the records and append the lecense plate number
     *  to the 'licence_plates' string
     */
    while (feof(file) == 0)
    {
        puchaces++;

        fgets(buffer, MAX_LINE_CHARS, file);    /*  read customer name              */
        fscanf(file, "%s\n", &buffer);          /*  read license plate number       */

        /*  increase 'licence_plates' string size by LICENCE_PLATE_CHARS            */
        *licence_plates = (char*) realloc(*licence_plates, (puchaces * LICENCE_PLATE_CHARS)+1);

        strcat(*licence_plates, buffer);        /*  append new licence plate number */
        fgets(buffer, MAX_LINE_CHARS, file);    /*  read car type                   */
        fgets(buffer, MAX_LINE_CHARS, file);    /*  read car price                  */
        fgets(buffer, MAX_LINE_CHARS, file);    /*  read date of purchase           */

        /*  skips blank line between records  */
        if (feof(file) == 0)
            fscanf(file, "\n");
    }
    return 0;
}


/*
 * Function:  PrintLicencePlates
 * --------------------
 * prints all licence plates from memory
 * in a 'XX 000 XX\n' format
 *
 *  licence_plates: pointer to licence plates string
 *
 *  returns: 0
 */

int PrintLicencePlates(char *licence_plates)
{
    int current_plate_index;    /* used in for cycle            */
    int first_plate_char;       /* used in for cycle            */
    int num_of_plates;          /* store total num of plates    */

    /* check whether icence plates are loaded, otherwise return 0   */
    if (licence_plates == NULL)
    {
        printf("Pole nie je vytvorene\n");
        return 0;
    }

    /* divide total lenght on string by lenght of 1 licence plate to get number of plates   */
    num_of_plates = strlen(licence_plates)/LICENCE_PLATE_CHARS;

    /*
     * print all licence plates in a 'XX 000 XX\n' format
     */
    for (current_plate_index = 0; current_plate_index < num_of_plates; current_plate_index++)
    {
        first_plate_char = licence_plates + (current_plate_index * LICENCE_PLATE_CHARS);
        printf("%.2s %.3s %.2s\n", first_plate_char, first_plate_char+2, first_plate_char+5);
    }

    return 0;
}


/*
 * Function:  PrintPalindromes
 * --------------------
 * prints all licence plates from memory which are palindomes
 * in a 'XX\n' format
 *
 *  licence_plates: pointer to licence plates string
 *
 *  returns: 0
 */

int PrintPalindromes(char *licence_plates)
{
    /* check whether icence plates are loaded, otherwise return 0   */
    if (licence_plates == NULL)
    {
        printf("Pole nie je vytvorene\n");
        return 0;
    }

    int plate_id, char_num;             /* used in for cycle  */
    int left_char_id, right_char_id;    /* used in for cycle  */
    int num_of_plates;                  /* stores the number of licence plates  */

    num_of_plates = strlen(licence_plates) / LICENCE_PLATE_CHARS;

    /*
     *  loop through all licen plates
     */
    for (plate_id = 0; plate_id < num_of_plates; plate_id++)
    {
        /*
         *  check first 3 letters with last 3 letters to find palindromes
         */
        for (char_num = 0; char_num < 3; char_num++)
        {
            left_char_id = (plate_id * LICENCE_PLATE_CHARS) + char_num;
            right_char_id = ((plate_id + 1) * LICENCE_PLATE_CHARS) - 1 - char_num;

            /*  if not the same, break for cycle */
            if (licence_plates[left_char_id] != licence_plates[right_char_id])
                break;
        }

        /*  if licence plate is a apalindrome   */
        if (char_num == 3)  /* print first 2 letters    */
            printf("%.2s\n", licence_plates + (plate_id * LICENCE_PLATE_CHARS));
    }
    return 0;
}


/*
 * Function:  BestSelling
 * --------------------
 * prints all best selling regions by licence plate
 * in a 'XX <number>\n' format
 *
 *  licence_plates: pointer to licence plates string
 *
 *  returns: 0
 *           returns -1 when licence_plates were not loaded
 */

int BestSelling(char *licence_plates)
{
    char (*found_prefixes)[3] = NULL;   /*  stores all found prefixes in a 2D array             */
    int *count = NULL;                  /*                                                      */
    int max_sales = 0;                  /*  stores the number of most sales in a single region  */
    int plate_id, region_id;            /*  used in for cycles                                  */
    int prefix_found;                   /*                                                      */
    int cars;                           /*                                                      */
    int num_of_found_regions = 0;       /*  stores hoe many different regions were found        */

    cars = strlen(licence_plates) / LICENCE_PLATE_CHARS;

    /* check whether licence plates are loaded, otherwise return -1 */
    if (licence_plates == NULL)
        return -1;

    /*
     *  loop through all licence plates and count all the sales
     */
    for (plate_id = 0; plate_id < cars; plate_id++)
    {
        prefix_found = FALSE;

        /*
         *  loop through all previously found regions
         */
        for (region_id = 0; region_id < num_of_found_regions; region_id++)
        {

            /*
             *  if current prefix is in found_prefixes, increase the number in the array
             */
            if (found_prefixes != NULL
                && found_prefixes[region_id][0] == *(licence_plates + plate_id * LICENCE_PLATE_CHARS)
                && found_prefixes[region_id][1] == *(licence_plates + plate_id * LICENCE_PLATE_CHARS + 1))
            {
                count[region_id]++;     /* increase region count    */
                prefix_found = TRUE;    /* skip adding a new region */

                /*  set max_sales to the biggest number of sales in a region    */
                max_sales = (max_sales > count[region_id]) ? (max_sales) : (count[region_id]);
            }
        }

        if (prefix_found == FALSE)
        {
            /*
             *  check whether arrays are created
             *  if not, create them with one new region
             *  if yes, append a new region
             */
            if (found_prefixes == NULL)
            {
                found_prefixes = malloc((num_of_found_regions + 2) * 2 * sizeof(char));
                count = malloc((num_of_found_regions + 2) * sizeof(int));
            }
            else
            {
                found_prefixes = (char *)realloc(found_prefixes, (num_of_found_regions + 2) * 2 * sizeof(char));
                count = (int *)realloc(count, (num_of_found_regions + 2) * sizeof(int));
            }

            /*  Save first 2 licence place characters in to the array   */
            found_prefixes[num_of_found_regions][0] = *(licence_plates + plate_id * LICENCE_PLATE_CHARS);
            found_prefixes[num_of_found_regions][1] = *(licence_plates + plate_id * LICENCE_PLATE_CHARS + 1);

            count[num_of_found_regions] = 1;    /*  set number of sales in the new region to 1          */
            num_of_found_regions++;             /*  increase the variable storing total num of regions  */
        }
    }


    /*
     *  print best selling region / regions
     */
    for (region_id = 0; region_id < num_of_found_regions; region_id++)
    {
        if (max_sales == count[region_id])  /*  if best selling region  */
        {
            /*  print region prefix */
            printf("%c%c ", found_prefixes[region_id][0], found_prefixes[region_id][1]);

            /*  print number of sales in the region */
            printf("%d\n", count[region_id]);
        }
    }
    return 0;
}


int main()
{
    char command;                   /*  stores the typed in command                 */
    char *licence_plates = NULL;    /*  points to the licence plate array           */
    FILE *file = NULL;              /*  points to the input file                    */
    long date;                      /*  stores the typed in date for command 'o'    */

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
                scanf("%ld", &date);        /* load current date parameter  */
                EmployeeBonus(date, file);
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
                BestSelling(licence_plates);
                break;

            /*
             * load licence plates and store them in to an array
             */
            case 'n':
                LoadLicencePlates(file, &licence_plates);
                break;

            /*
             * prints licence plates
             */
            case 's':
                PrintLicencePlates(licence_plates);
                break;

            /*
             * print licence plate palindromes
             */
            case 'p':
                PrintPalindromes(licence_plates);
                break;

            /*
             * exit command
             */
            case 'k':
                return 0;   /* exit program */
                break;

            /*
             * blank line entered
             */
            case '\n':
                break;      /* do nothing   */

            /*
             * command not recognized
             */
            default:
                printf("Command not recognized! %c\n", command);

        }
    }
}
