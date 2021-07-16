#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

const int N = 9;
int chooseFigure();
void showField(char arr[N]);
bool checkWeWin(int step[N]);
int checkWeCanWinOrBlocked(char field[], char symb, char symbE);
int playsForX(char field[], int stepEnemy[], int allStep[], int allSteps);
void oneStep(int choicePlayer, char symbol);
int randomStepCPU();
bool checkWin();

int currentStep = 0;
int stepFirst[N] = {0};
int stepSecond[N] = {0};
int allStep[N] = {0};
int countStepFirst = 0;
int countStepSecond = 0;
int countAllStep = 0;
int forWin[8][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 4, 7}, {2, 5, 8}, {3, 6, 9}, {1, 5, 9}, {3, 5, 7}};
char fieldXO[N]  = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
int lastStepCPU = 0;


int main() {

        int choicePlayer = chooseFigure();
	srand(time(NULL));
        while(true) {
                currentStep = 0;
                for (int i = 0; i < N; i++) {
                        stepFirst[i] = 0;
                        stepSecond[i] = 0;
                        fieldXO[i] = 49 + i;
                        allStep[i] = 0;
                }
                countStepFirst = 0;
                countStepSecond = 0;
                countAllStep = 0;
                lastStepCPU = 0;

                while(true) {
                        if (choicePlayer == 1) {
                                oneStep(1, 'X');
                                if(checkWin())
                                        break;				
				Sleep(1000);
                                oneStep(0, 'O');
                                if(checkWin())
                                        break;
				Sleep(1000);
                        }
                        else {
                                oneStep(0, 'X');
                                if(checkWin())
                                        break;                                
				Sleep(1000);
				oneStep(1, 'O');
                                if(checkWin())
                                        break;				
				Sleep(1000);
                        }
                }

                cout << endl;
                int again = -1;
                cout << "Enter 0 - for exit OR press any key for restart";
                cin >> again;

                if (again == 0) {
                        again = 1;
                        break;
                }

        }

    return 0;
}

bool checkWin() {
        if (checkWeWin(stepFirst)) {
                showField(fieldXO);
                cout << "You is win";
                return true;
        }
        else if (checkWeWin(stepSecond)) {
                showField(fieldXO);
                cout << "CPU is win";
                return true;
        }
        else if(countAllStep == 9) {
                cout << "Draw";
                return true;
        }
        return false;
}

int playsForX(char field[], int stepEnemy[], int allStep[], int allSteps) {
	int stepX;
	int num;
	int check = 0;
	//åñëè õîä ïåðâûé, òî çàíèìàåì öåíòðàëüíóþ ÿ÷åéêó
	if (allSteps == 0)
	   	stepX = 5;	   	
	//если ход второй и противник занял ЧЕТНУЮ ячейку, занимаем дальнюю угловую ячейку
 	else if ((allSteps == 1) && (stepEnemy[0] % 2 == 0)) { 		
 		if (stepEnemy[0] == fieldXO[1]) {
 			do {
 				stepX = (1 + rand() % 9);
 			} while ((stepX = 7) || (stepX = 9));
 		}
 		if (stepEnemy[0] == fieldXO[3]) {                               
 			do {
 				stepX = (1 + rand() % 9);
 			} while ((stepX = 3) || (stepX = 9));
 		}
 		if (stepEnemy[0] == fieldXO[5]) {
 			do {
 				stepX = (1 + rand() % 9);
 			} while ((stepX = 1) || (stepX = 7));
 		}
 		if (stepEnemy[0] == fieldXO[7]) {
 			do {
 				stepX = (1 + rand() % 9);
 			} while ((stepX = 1) || (stepX = 3));
 		}
 	}//иначе занимаем любую угловую ячейку
 	else {
 		while (true) {
 			check = 0;
			 do {
 				stepX = (1 + rand() % 9);
			} while ((stepX != 1) && (stepX != 3) && (stepX != 7) && (stepX != 9));
		 	for (int i = 0; i < N; i++) {
			 	if (stepX == allStep[i]) {
                    check++;
                }		
 			}
			if (check == 0)
            	break; 		
 		}
	}
 	return stepX;
}

void oneStep(int choicePlayer, char symbol) {

        showField(fieldXO);
        if (choicePlayer == 1) {
                cout << "Make your move, please...";
                cin >> currentStep;
                stepFirst[countStepFirst] = currentStep;
                fieldXO[currentStep - 1] = symbol;
        }
        else {
                currentStep = randomStepCPU();
                stepSecond[countStepFirst] = currentStep;
                fieldXO[currentStep - 1] = symbol;
                lastStepCPU = currentStep;
        }
        allStep[countAllStep] = currentStep;
        countStepFirst++;
        countAllStep++;

}

int randomStepCPU() {
        int step = 0;
        int check = 0;
        while(true) {
                check = 0;
                srand ( time(NULL) );
                step = (1 + rand() % 9);
                for (int i = 0; i < N; i++) {
                        if (step == allStep[i]) {
                                check++;
                        }

                }

                if (check == 0)
                        break;
        }
        return step;
}

bool checkWeCanWin(int step[]) {
        int countInRow = 0;
        bool check = false;

        for (int i = 0; i < 8; i++) {
                countInRow = 0;
                for (int j = 0; j < 3; j++) {
                        for (int k = 0; k < N; k++) {
                                if (forWin[i][j] == step[k]) {
                                        countInRow++;
                                }
                        }
                }
                if (countInRow == 3) {
                        check = true;
                        break;
                }
        }

        return check;
}

void showField(char arr[N]) {
        system("cls");
        cout << "    " << "Game <<Tic-Tac-Toe>>" << endl;
        cout << endl;
        cout << "\t" << "   ";
	for (int i = 0; i < N; i++) {
		cout << arr[i] << " ";
                if ((i + 1) % 3 == 0) {
                        cout << endl;
                        cout << "\t" << "   ";
                }
    	}
        cout << endl;
        if (lastStepCPU != 0) {
                cout << "Last step CPU is " << lastStepCPU << endl;
        }
        cout << endl;
}

int chooseFigure() {
	int figure;

	cout << "    " << "Game <<Tic-Tac-Toe>>" << endl;
        cout << endl;
	cout << "Who is play first: " << endl;
	cout << "1 - Player step first" << endl;
	cout << "0 - Cpu step first" << endl;
	cout << "Your choice: ";
	cin >> figure;
	system("cls");

	return figure;
}

//void makeMove(int ) {
