//
// Created by 张力文 on 2020/9/30.
//
#include<stdio.h>
#include<stdlib.h>


int state;//1 is win and 0 is false
int count = 0;
char player[][10];
int width = 7;
int height = 6;
int flag = 0;
char board[6][7];

void initia_connect_four()
{
    printf("Setting up the game:\n");
    printf("Please input Player1's name:\n");
    scanf("%s", player[0]);

    printf("Please input Player2's name:\n");
    scanf("%s", player[1]);
    return ;
}

void teardown()
{
    printf("Desdroying the game.\n");
    exit(0);
}

char accept_input_connect_four(void)
{
    char letter;

    if(flag == 0)
    {
        printf("please input your move: %s\n",player[0]);
        flag++;
    }
    else
    {
        printf("please input your move: %s\n",player[1]);
        flag--;
    }
    scanf(" %c", &letter);
    if(letter == 'X')
    {
        teardown();
    }
    else if(letter >= 'A' && letter <= 'G')
    {
        printf("%c\n", letter);//testing
        return letter;
    }
    else
    {
        printf("error!\n");
        teardown();
    }
}

int update_state_connect_four(char ch)
{
    //ch = accept_input_connect_four();
    //state = ch;
    if(ch == 'A')
    {
        state = 1;
        printf("win!\n");
        teardown();
    }
    else{
        count++;
        printf("count:%d\n",count);
        accept_input_connect_four();

    }
    return state;
}

void display_state_connect_four()
{

    printf("state:%d\n",state);
//    for(int i = 0; i < 7; i ++)
//    {
//        for(int j = 0; j < 6; j++)
//        {
//            if(i == 0 && j == 0)
//            {
//                board[i][j] = '*';
//            }
//            else
//            {
//                board[i][j] = '-';
//            }
//
//        }
//        printf("\n");
//    }

}

int main(void)
{
    initia_connect_four();
    state = update_state_connect_four(accept_input_connect_four());
    display_state_connect_four();
    teardown();


    return 0;

}


