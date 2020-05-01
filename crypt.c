#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int lenunique;
int values[10]; //Result numbers --  put it in structures
char letters[10]; // Given letters -- put it in structure


int position(char str[], char x)
{
    int m, n;

    n = strlen(str);
    //printf ("Position str: %s\n", str);
    //printf ("Position letter: %c\n", x);
    for (m=0; m<n; m++)
    {
        if (str[m] == x)
        {
            //printf ("Position M: %d\n", m);
            //first occurance of the letter in the string in the example 'SEND & MORE'
            //'E' is repeated so 'E' position and value is always same
            return m;
        }
    }
    return m;
}

//truncate to get uniques letters from all the 3 strings ex. SEND MORE MONEY will be SENDMORY
void unique(char str[])
{
    int i, j, l;
    l = strlen(str);

    for (i = 0; i<l; i++)
    {
        for (j = lenunique - 1; j>= 0; j--)
        {
            if (letters[j] == str[i])
                break;
        }
        if (j == -1)
        {
            letters[lenunique] = str[i];
            lenunique++;
        }
    }
}

//Genarate random numbers
void findnextvalue()
{
    int i;
    for (i=0; i<lenunique; i++)
    {
        values[i] = rand()%10;
        //printf("%d", values[i]);
    }
    //printf("\n");
}

int main(int argc, string argv[])
//int main()
{
    int i, j, k, n1, n2, n3, l1, l2, l3, tries; //length of each word (l), number formed (n)
    //char w1[20], w2[20], w3[30]; //store given words in char array
    char* w1;
    char* w2;
    char* w3;
    char* op1;
    char* op2;
    int len = 0;

    printf("enter the equation: %d\n\n", argc);

    if (argc != 6)
    {
        printf("Usage: addend1 + addend2 = sum \n\n");
        return 1;
    }


    len = strlen(argv[1]);
    printf("Length of argv[1] = %d\n", len);

    w1 = (char*)malloc(sizeof(char) * strlen(argv[1])); //'SEND'
    strcpy(w1, argv[1]);

    printf("First String: %s\n", w1);

    w2 = (char*)malloc(sizeof(char) * strlen(argv[3])); //'MORE'
    strcpy(w2, argv[3]);

    printf("Second String: %s\n", w2);

    w3 = (char*)malloc(sizeof(char) * strlen(argv[5])); //'MONEY'
    strcpy(w3, argv[5]);

    printf("Result string: %s\n", w3);

    op1 = argv[2]; // '+'
    printf("Operation: %s\n", op1);

    op2 = argv[4]; //'='
    printf("Resulting: %s\n", op2);

    l1 = strlen(w1);
    l2 = strlen(w2);
    l3 = strlen(w3);
    lenunique = 0;

    unique(w1);
    unique(w2);
    unique(w3);

    printf("Unique letters length: %d\n", lenunique);
    if (lenunique > 10)
    {
        printf(" something is not right with input \n");
        return 0;
    }
    printf("Unique letters: %s\n", letters);

    //Initialize the values array to 0
    for (i=0; i<lenunique; i++)
    {
        values[i] = 0;
    }

    //Put it in a recursive function
    //Reccursive function may not yeild multiple solutions
    //run it upto 50000 times to get multiple solutions
   int q = 0;
   for (i=1; i<=4000000; i++)
   {
        findnextvalue(); //generate random number with mod
        for (j=0; j<lenunique; j++)
        {
            for (k=j+1; k<lenunique; k++)
            {
                if (values[j] == values[k]) //found repetitive digits in the number
                {
                    //printf("Here %d %d\n",values[j], values[k] );
                    findnextvalue(); // Repeat this till we find unique number(digits) for evaluated uniqueword
                    j = -1;
                    break;
                }
            }
        }

        n1 = 0;
        n2 = 0;
        n3 = 0;

        //assign first digits(4) to first string(4) to begin with, SEND(4)
        for (j=0; j<l1; j++)
        {
            n1 = (n1*10) + values[position(letters, w1[j])]; //One letter at a time 'S', 'E', 'N', 'D'
            //printf("n1: %d\n", n1);
        }

        //printf("n11: %d\n", n1);

        for (j=0; j<l2; j++)
        {
            n2 = (n2*10) + values[position(letters, w2[j])];
            //printf("n2: %d\n", n2);
        }
        //printf("n22: %d\n", n2);

        for (j=0; j<l3; j++)
        {
            n3 = (n3*10) + values[position(letters, w3[j])];
            //printf("n3: %d\n", n3);
        }
        //printf("n33: %d\n", n3);

        if (n1+n2 == n3)
        {
            printf("\n\n Solution found: %d", ++q);
            printf(" At iteration: %d\n", i);
               // printf("n1: %d\n", n1);
              // printf("n2: %d\n", n2);
             // printf("n3: %d\n\n", n3);
            //q++;
            for (j=0; j<lenunique; j++)
            {
                printf("%c", letters[j]);
                printf(" = %d", values[j]);
                printf("\n");
            }
            printf("Press RETURN for next solution: ");
            getchar();
        }
        if (i == 4000000)       //10! = 3628800
           printf("\n\n Total Solutions found = %d\n", q);
    }
    free(w1);
    free(w2);
    free(w3);
    //getchar();
    return 0;
}


