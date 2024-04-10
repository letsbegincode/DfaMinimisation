// This code is for DFA minimization, where a transition table is taken as input at runtime.
// Caution: It works only for two input symbols. For further modifications, you need to add a four-equivalence method that contains 16 for loops and split the thirdEqui 2D matrix accordingly.
// Caution: If you are modifying the code, kindly take care of the 3D matrix used here.

// Idea and approach
// This code is based on a procedural way of finding minimization.
// First, find 0 equivalence, then 1, and so on.
// Storing all the equivalence elements in the final 3D matrix and also using the incol-2D and inrow 1D for storing limits of the valid elements contained in the equivalence-final table. This prevents you from grabbing garbage values.

#include <stdio.h>
#include <stdlib.h>

int numFinalStates;
int states;
int transitions;

int final[4][10][10]; //for storing equivalence matrix 
int incol[4][10];
int inrow[4];

// setting matrix to -1
void setmatrix(int m, int n, int mat[m][n])
{
    int i, j;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            mat[i][j] = -1;
        }
    }
}

// Function to print a matrix
void printMatrix(int dfa[states][transitions])
{
    int i, j;
    for (i = 0; i < states; i++)
    {
        for (j = 0; j < transitions; j++)
        {
            printf("%d ", dfa[i][j]);
        }
        printf("\n");
    }
}

// Function to check if a state is final
int isFinal(int state, int finals[numFinalStates])
{
    int i;
    for (i = 0; i < numFinalStates; i++)
    {
        if (state == finals[i])
            return 1;
    }
    return 0;
}

// Function to separate final and non-final states
void zeroEquivalence(int dfa[states][states], int finals[numFinalStates])
{
    int nonFinalCount = 0, finalCount = 0;
    int i;
    // Populate the zeroState matrix
    for (i = 0; i < states; i++)
    {
        if (isFinal(i, finals))
            final[0][0][incol[0][0]++] = i;
        else
            final[0][1][incol[0][1]++] = i;
    }
    inrow[0] = 2;
}

// Function to filter the DFA table based on 1-equivalence
void oneEquivalence(int inx, int dfa[states][transitions], int finals[numFinalStates], int oneState[4][states], int in1[4])
{
    int i;

    for (i = 0; i < 4; i++)
    {
        in1[i] = 0;
    }

    for (i = 0; i < incol[0][inx]; i++)
    {
        int in = final[0][inx][i];

        if (isFinal(dfa[in][0], finals) && isFinal(dfa[in][1], finals))
        {
            oneState[0][in1[0]++] = in;
        }
        else if (!isFinal(dfa[in][0], finals) && isFinal(dfa[in][1], finals))
        {
            oneState[1][in1[1]++] = in;
        }
        else if (isFinal(dfa[in][0], finals) && !isFinal(dfa[in][1], finals))
        {
            oneState[2][in1[2]++] = in;
        }
        else if (!isFinal(dfa[in][0], finals) && !isFinal(dfa[in][1], finals))
        {
            oneState[3][in1[3]++] = in;
        }
    }
}

//crating second equi
void secondEquivalence(int onlyinrow, int dfa[states][transitions], int finals[numFinalStates], int secondState[16][states], int in2[16])
{
    int i, j;

    for (i = 0; i < 16; i++)
    {
        in2[i] = 0;
    }

    int f1, f2, f3, f4, k;

    for (f1 = 0; f1 <= 1; f1++)
    {
        for (f2 = 0; f2 <= 1; f2++)
        {
            for (f3 = 0; f3 <= 1; f3++)
            {
                for (f4 = 0; f4 <= 1; f4++)
                {
                    for (i = 0; i < incol[1][onlyinrow]; i++)
                    {
                        int in = final[1][onlyinrow][i];
                        int zz = dfa[dfa[in][0]][0];
                        int oo = dfa[dfa[in][1]][1];
                        int zo = dfa[dfa[in][0]][1];
                        int oz = dfa[dfa[in][1]][0];

                        if (isFinal(zz, finals) == f1 && isFinal(zo, finals) == f2 && isFinal(oz, finals) == f3 && isFinal(oo, finals) == f4)
                        {
                            secondState[f1 * 8 + f2 * 4 + f3 * 2 + f4][in2[f1 * 8 + f2 * 4 + f3 * 2 + f4]++] = in;
                        }
                    }
                }
            }
        }
    }

    // Print the secondState matrix
}

void thirdEquivalence(int inrowonly, int dfa[states][transitions], int finals[numFinalStates], int thirdState[256][states], int in3[256])
{
    int i, j;

    for (i = 0; i < 256; i++)
    {
        in3[i] = 0;
    }

    int f1, f2, f3, f4, f5, f6, f7, f8;
    for (f1 = 0; f1 <= 1; f1++)
    {
        for (f2 = 0; f2 <= 1; f2++)
        {
            for (f3 = 0; f3 <= 1; f3++)
            {
                for (f4 = 0; f4 <= 1; f4++)
                {
                    for (f5 = 0; f5 <= 1; f5++)
                    {
                        for (f6 = 0; f6 <= 1; f6++)
                        {
                            for (f7 = 0; f7 <= 1; f7++)
                            {
                                for (f8 = 0; f8 <= 1; f8++)
                                {
                                    for (i = 0; i < incol[2][inrowonly]; i++)
                                    {
                                        int in = final[2][inrowonly][i];
                                        int zzz = dfa[dfa[dfa[in][0]][0]][0];
                                        int zzo = dfa[dfa[dfa[in][0]][1]][0];
                                        int zoz = dfa[dfa[dfa[in][1]][0]][0];
                                        int zoo = dfa[dfa[dfa[in][1]][1]][0];
                                        int ozz = dfa[dfa[dfa[in][0]][0]][1];
                                        int ozo = dfa[dfa[dfa[in][0]][1]][1];
                                        int ooz = dfa[dfa[dfa[in][1]][0]][1];
                                        int ooo = dfa[dfa[dfa[in][1]][1]][1];

                                        if (isFinal(zzz, finals) == f1 && isFinal(zzo, finals) == f2 && isFinal(zoz, finals) == f3 && isFinal(zoo, finals) == f4 &&
                                            isFinal(ozz, finals) == f5 && isFinal(ozo, finals) == f6 && isFinal(ooz, finals) == f7 && isFinal(ooo, finals) == f8)
                                        {
                                            thirdState[f1 * 128 + f2 * 64 + f3 * 32 + f4 * 16 + f5 * 8 + f6 * 4 + f7 * 2 + f8][in3[f1 * 128 + f2 * 64 + f3 * 32 + f4 * 16 + f5 * 8 + f6 * 4 + f7 * 2 + f8]++] = in;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Print the thirdState matrix
}

void copyarr(int row, int from, int to)
{
    int i;
    for (i = 0; i < incol[from][row]; i++)
    {
        final[to][inrow[to]][incol[to][inrow[to]]++] = final[from][row][i];
    }
    inrow[to]++;
}

//This method helps to copy temporary respective equi matrix to final 3d matrix 
void copymatrix(int m, int n, int mat[m][n], int in[m], int to)
{
    int i, j;
    for (i = 0; i < m; i++)
    {
        if (in[i] > 0)
        {
            for (j = 0; j < in[i]; j++)
            {
                final[to][inrow[to]][incol[to][inrow[to]]++] = mat[i][j];
            }
            inrow[to]++;
        }
    }
}

//This is for printing the calculating equivalnce table according to type of equi present in final
void printFinals(int equi)
{
    int i, j;
    for (i = 0; i < inrow[equi]; i++)
    {
        printf("Equivalence Class %d:\n", i);
        for (j = 0; j < incol[equi][i]; j++)
        {
            printf("%d ", final[equi][i][j]);
        }
        printf("\n");
    }
}

// Function to sort an array using bubble sort
void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to find the set of transitions for a given state
void findSetOfTransitions(int row, int elements[], int dfa[states][transitions], int equifor[][states], int in[inrow[3]], int trans)
{
    int i;
    int check[states];
    for (i = 0; i < states; i++)
    {
        check[i] = 0;
    }

    for (i = 0; i < incol[3][row]; i++)
    {
        int state = elements[i];
        if (trans == 0)
        {
            int val = dfa[state][0];
            if (check[val] == 0)
            {
                equifor[row][in[row]] = val; // Transition for 0
                check[val] = 1;
                in[row]++; // Increment the count of transitions for this row
            }
        }
        else
        {
            int val = dfa[state][1];
            if (check[val] == 0)
            {
                equifor[row][in[row]] = val; // Transition for 1
                check[val] = 1;
                in[row]++; // Increment the count of transitions for this row
            }
        }
    }
}
//This help in to find next state of the final calculated equi...
void match(int transitionTable[inrow[3]][2], int equifor[states], int in, int row, int col)
{
    int i, j, k;
    for (i = 0; i < inrow[3]; i++)
    {
        for (j = 0; j < in; j++)
        {
            for (k = 0; k < incol[3][i]; k++)
                if (equifor[j] == final[3][i][k])
                {
                    transitionTable[row][col] = i;
                    return; // Exit the function if any match is found
                }
        }
    }
}

// Inside main()

int main()
{
    int i, j;
    printf("Enter the number of states: ");
    scanf("%d", &states);
    printf("\nEnter the number of input symbols : ");
    scanf("%d", &transitions);
    // Input for final states
    printf("\nEnter the number of final states: ");
    scanf("%d", &numFinalStates);

    int finals[numFinalStates];
    printf("\nEnter all final states: ");
    for (i = 0; i < numFinalStates; i++)
    {
        scanf("%d", &finals[i]);
    }

    printf("\nEnter the DFA transition table:\n");
    int dfa[states][transitions];

    for (i = 0; i < states; i++)
    {
        printf("From state %d, go to states: ", i);
        for (j = 0; j < transitions; j++)
        {
            scanf("%d", &dfa[i][j]);
        }
    }

    finals[0] = 7;

    for (i = 0; i < 4; i++)
    {
        inrow[i] = 0;
    }
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 10; j++)
            incol[i][j] = 0;
    }

    printf("Entered DFA transition table:\n");
    printMatrix(dfa);

    printf("Entered final states:\n");
    for (i = 0; i < numFinalStates; i++)
    {
        printf("%d ", finals[i]);
    }

    // storing zero-equi in first[0] array
    zeroEquivalence(dfa, finals);
    printf("\n\n 0 equi \n");
    printFinals(0);

    // for storing one-equivalnce in final[1] array
    for (i = 0; i < inrow[0]; i++)
    {
        if (incol[0][i] == 1)
        {
            copyarr(i, 0, 1);
        }
        else
        {
            int oneState[4][states];
            int in1[4];
            oneEquivalence(i, dfa, finals, oneState, in1);
            copymatrix(4, states, oneState, in1, 1);
        }
    }

    // printing
    printf("\n\n One equi \n");
    printFinals(1);

    // for storing second-equivalnce in final[2] array
    for (i = 0; i < inrow[1]; i++)
    {
        if (incol[1][i] == 1)
        {
            copyarr(i, 1, 2);
        }
        else
        {
            int secondState[16][states];
            int in2[16];
            secondEquivalence(i, dfa, finals, secondState, in2);
            copymatrix(16, states, secondState, in2, 2);
        }
    }

    printf("\n\n 2nd equi \n");
    printFinals(2);

    // for storing third-equivalnce in final[3] array
    for (i = 0; i < inrow[2]; i++)
    {
        if (incol[2][i] == 1)
        {
            copyarr(i, 2, 3);
        }
        else
        {
            int thirdState[256][states];
            int in3[256];
            thirdEquivalence(i, dfa, finals, thirdState, in3);
            copymatrix(256, states, thirdState, in3, 3);
        }
    }

    printf("\n\n 3rd equi \n");
    printFinals(3);

    // Sorting row wise third equivalence
    for (i = 0; i < inrow[3]; i++)
    {
        // Sort final[3][i] up to incol[3][i]
        bubbleSort(final[3][i], incol[3][i]);
    }

    // Assigning letters to each row
    printf("\n\nLet assume the set is : \n");

    for (i = 0; i < inrow[3]; i++)
    {
        printf("%c ->", i + 'A');
        for (j = 0; j < incol[3][i]; j++)
        {
            printf(" %d ", final[3][i][j]);
        }
        printf("\n");
    }

    // finding transtion of the elements
    int equiforA[inrow[3]][states];
    int equiforB[inrow[3]][states];
    int inA[inrow[3]];
    int inB[inrow[3]];
    for (i = 0; i < inrow[3]; i++)
    {
        inA[i] = 0;
        inB[i] = 0;
    }

    // printf("\n Till here all ok \n");

    for (i = 0; i < inrow[3]; i++)
    {
        findSetOfTransitions(i, final[3][i], dfa, equiforA, inA, 0);
        findSetOfTransitions(i, final[3][i], dfa, equiforB, inB, 1);
    }

    // Sorting the transiton of tables A and B for further matching

    for (i = 0; i < inrow[3]; i++)
    {
        bubbleSort(equiforA[i], inA[i]);
        bubbleSort(equiforB[i], inB[i]);
    }

    int transitontable[inrow[3]][2];

    // Matching with equifor
    for (i = 0; i < inrow[3]; i++)
    { // tablestore tabletomatch lenofrowofmatch  storeinrow havetostoreincolmoftransi
        match(transitontable, equiforA[i], inA[i], i, 0);
        match(transitontable, equiforB[i], inB[i], i, 1);
    }
  
    // final printing the transition table
    printf("\nFinal Transition table \n");

    printf("        a  |  b \n");
    for (i = 0; i < inrow[3]; i++)
    {
        printf("%c |    %c   |  %c\n", i + 'A', transitontable[i][0] + 'A', transitontable[i][1] + 'A');
    }

    return 0;
}
