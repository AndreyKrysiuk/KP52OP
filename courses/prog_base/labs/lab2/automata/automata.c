#include<stdio.h>
#include<stdlib.h>

int run(int moves[], int movesLen, int res[], int resLen){

    enum Moves {continuos,repeat,breaking,pop};

    struct Automat
    {
        enum Moves move;
        int state;
    };

        struct Automat act[4][4];
            act[0][0].move = continuos;
            act[0][0].state = 0;
            act[0][1].move = repeat;
            act[0][1].state = 2;
            act[0][2].move = continuos;
            act[0][2].state = 1;
            act[0][3].move = 777;
            act[0][3].state = 3;
            act[1][0].move = 7;
            act[1][0].state = 2;
            act[1][1].move = breaking;
            act[1][2].move = breaking;
            act[1][3].move = breaking;
            act[2][0].move = breaking;
            act[2][1].move = pop;
            act[2][1].state = 3;
            act[2][2].move = pop;
            act[2][2].state = 3;
            act[2][3].move = 77;
            act[2][3].state = 1;
            act[3][0].move = breaking;
            act[3][1].move = 13;
            act[3][1].state = 0;
            act[3][2].move = breaking;
            act[3][3].move = 7777;
            act[3][3].state = 0;

        int currentState = 0;
        int currentMove;
        int k=0;
        int i=0;
        int checkbreak;
        int resNumbers=0;

    while(1){
            switch(moves[k]){
                case 7:
                    currentMove = 0;
                    break;
                case 11:
                    currentMove = 1;
                    break;
                case 16:
                    currentMove = 2;
                    break;
                case 106:
                    currentMove = 3;
                    break;
                default:
                    checkbreak = 1;
                    break;
                    }
            if(checkbreak == 1){
                break;
            }

            switch(act[currentState][currentMove].move){
                    case breaking:
                        checkbreak = 1;
                        break;
                    case pop:
                        if(i>0){
                        res[i-1]=0;
                        i--;
                        k++;
                        currentState = act[currentState][currentMove].state;
                        break;
                            } else {
                                checkbreak = 1;
                                break;
                                }
                    case repeat:
                        currentState = act[currentState][currentMove].state;
                        break;
                    case continuos:
                        k++;
                        currentState = act[currentState][currentMove].state;
                        break;
                    default:
                        res[i] = act[currentState][currentMove].move;
                        i++;
                        k++;
                        currentState = act[currentState][currentMove].state;
                        break;
                    }

            if(checkbreak == 1)
                break;
        }
        for(i=0;i<resLen;i++){
            if(res[i]!=0)
                resNumbers++;
            }
    return resNumbers;
}

