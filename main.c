#include <stdio.h>
#include<stdlib.h>

char state;

void initia_connect_four()
{
    char player1[] = "zlw";
    char player2[] = "jyx";

    //*player1 = "zlw";
    //*player2 = "jyx";

    printf("Setting up the game:\n");
    printf("Please input Player1's name:\n");
    scanf("%s", player1);

    printf("Please input Player2's name:\n");
    scanf("%s", player2);

    //printf("%s %s", player1, player2);

    return ;
}
void teardown_connect_four()
{
    printf("Desdroying the game.\n");
}

char accept_input_connect_four()
{
    char letter;

    scanf("%c", &letter);

    if(letter == 'X')
    {
        printf("quit the game successfully!\n");
        return 0;
    }
    if(letter >= 'A' && letter <= 'G')
    {
        printf("%c", letter);
        return letter;
    }
    else
    {
        printf("error!\n");
        return -1;
    }
}

int main(void) {



    return 0;
}
