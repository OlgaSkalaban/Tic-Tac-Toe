#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
//#include <windows.h>

using namespace std;

const int N = 9;
int chooseFigure();
void showField(char arr[N]);
bool checkWeWin(int step[N]);
int checkWeCanWinOrBlocked(char field[], char symb, char symbE);
int playsForX(char field[], int stepEnemy[], int allStep[], int allSteps);
void oneStep(char symbol);
int randomStepCPU();
bool checkWin();
bool containInArray(int array[N], int numForCheck);
void stepZero();
int hasFreeEven();
int hasFreeOdd();
int checkForWinOnNextStep(int step[N], int countStep);
void doStepCPU(int step);
void stepMen(char symbol, int choicePlayer);

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
int choicePlayer = -1;

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
                                stepMen('X', 1);//человек
                                if(checkWin())
                                        break;
				//Sleep(1000);

                                stepZero();//компьютер
                                fieldXO[lastStepCPU - 1] = 'O';

                                if(checkWin())
                                        break;
				//Sleep(1000);
                        }
                        else {
                                oneStep('X');//компьютер
                                if(checkWin())
                                        break;
				//Sleep(1000);
				                stepMen('O',0);//человек
                                if(checkWin())
                                        break;
				//Sleep(1000);
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
                if (choicePlayer == 1)
                        cout << "You is win";
                else
                        cout << "CPU is win";
                return true;
        }
        else if (checkWeWin(stepSecond)) {
                showField(fieldXO);
                if (choicePlayer == 0)
                        cout << "You is win";
                else
                        cout << "CPU is win";
                return true;
        }
        else if(countAllStep == 9) {
                showField(fieldXO);
                cout << "Draw";
                return true;
        }
        return false;
}

int playsForX(char field[], int stepEnemy[], int allStep[], int allSteps) {
	int stepX = 0;
	int check = 0;
	//если ход первый, то занимаем центральную ячейку
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
                /*if ((hasFreeOdd() != 0)) {
                                stepX = hasFreeOdd();
                }
                else {
                                stepX = hasFreeEven();
                }*/
                for(int i = 1; i <= N; i++) {
                        if (i % 2 ==1 && !containInArray(allStep,i)) {
                                if (stepSecond[0] % 2 == 0 && (abs(stepSecond[0] - i) != 1 || abs(stepSecond[0] - i) != 3)) {
                                        stepX = i;
                                }
                                else if (stepSecond[1] % 2 == 0 && (abs(stepSecond[1] - i) != 1 || abs(stepSecond[1] - i) != 3)) {
                                        stepX = i;
                                }
                        }
                }

        if(stepX == 0) {
                for(int i = 1; i <= N; i++) {
                        if (i % 2 ==1 && !containInArray(allStep,i)) {
                                stepX = i;
                        }
                }

        }
        if(stepX == 0) {
                stepX = hasFreeEven();
        }

 		/*while (true) {
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
 		}*/
	}

 	return stepX;
}

int checkWeCanWinOrBlocked(char field[], char symb, char symbE)
{
	// horizontal check
	for (int i = 0; i < 9; i = i+3) {
		if ( (field[i] == symb) && (field[i+1] == symb) && (field[i+2] != symbE) && (field[i+2] != symb) )
            return i+2;
        else if ( (field[i] == symb) && (field[i+1] != symbE) && (field[i+1] != symb) && (field[i+2] == symb) )
            return i+1;
        else if ( (field[i] != symbE) && (field[i] != symb) && (field[i+1] == symb) && (field[i+2] == symb) )
            return i;
	}
	//vertical check
	for (int i = 0; i < 3; i++) {
		if ( (field[i] == symb) && (field[i+3] == symb) && (field[i+6] != symbE) && (field[i+6] != symb))
            return i+6;
        else if ( (field[i] == symb) && (field[i+3] != symbE) && (field[i+3] != symb) && (field[i+6] == symb))
            return i+3;
        else if ( (field[i] != symbE) && (field[i] != symb) && (field[i+3] == symb) && (field[i+6] == symb))
            return i;
	}
	//diagonal check
	if ( (field[0] == symb) && (field[4] == symb) && (field[8] != symbE) && (field[8] != symb) )
		return 8;
    if ( (field[0] == symb) && (field[4] != symbE) && (field[4] != symb) && (field[8] == symb) )
		return 4;
    if ( (field[0] != symbE) && (field[0] != symb) && (field[4] == symb) && (field[8] == symb) )
		return 0;

    if ( (field[2] == symb) && (field[4] == symb) && (field[6] != symbE) && (field[6] != symb) )
		return 6;
    if ( (field[2] == symb) && (field[4] != symbE) && (field[4] != symb) && (field[6] == symb) )
		return 4;
    if ( (field[2] != symbE) && (field[2] != symb) && (field[4] == symb) && (field[6] == symb) )
		return 2;
		// if all cells are taken
	return -2;
}

void stepZero() {
    showField(fieldXO);
        int step = -1;
        if (!containInArray(allStep, 5)) {
                step = 5;
                doStepCPU(step);
        }
        else if (countStepSecond == 0 && containInArray(allStep, 5)) {
                step = 1;
                doStepCPU(step);
        }
        else if (checkForWinOnNextStep(stepSecond, countStepSecond) != 0) {
                step = checkForWinOnNextStep(stepSecond, countStepSecond);
                doStepCPU(step);
        }
        else if (checkForWinOnNextStep(stepFirst, countStepFirst) != 0) {
                step = checkForWinOnNextStep(stepFirst, countStepFirst);
                doStepCPU(step);
        }
        else if (countStepSecond == 1 && containInArray(stepSecond, 5)) {
                if (stepFirst[0] % 2 == 1 && stepFirst[1] % 2 == 1) {
                        if ((stepFirst[0] + 1) != 9)
                                step = stepFirst[0] - 1;
                        else
                                step = stepFirst[0] + 1;
                        doStepCPU(step);
                }
                else if ((stepFirst[0] % 2 == 1 && (stepFirst[1] % 2 == 0 && (abs(stepFirst[1] - stepFirst[0]) == 1 || abs(stepFirst[1] - stepFirst[0]) == 3)))
                 || ((stepFirst[0] % 2 == 0 && (abs(stepFirst[1] - stepFirst[0]) == 1 || abs(stepFirst[1] - stepFirst[0]) == 3)) && stepFirst[1] % 2 == 0)) {
                                        if (stepFirst[0] % 2 == 0) {
                                                if (abs(5 - stepFirst[0]) == 1) {
                                                        if (!containInArray(allStep, (stepFirst[0] - 3)))
                                                                step = stepFirst[0] - 3;
                                                        else
                                                                step = stepFirst[0] + 3;
                                                }
                                                if (abs(5 - stepFirst[0]) == 3) {
                                                        if (!containInArray(allStep, (stepFirst[0] - 1)))
                                                                step = stepFirst[0] - 1;
                                                        else
                                                                step = stepFirst[0] + 1;
                                                }
                                        }
                                        else if (stepFirst[1] % 2 == 0) {
                                                if (abs(5 - stepFirst[1]) == 1) {
                                                        if (!containInArray(allStep, (stepFirst[1] - 3)))
                                                                step = stepFirst[1] - 3;
                                                        else
                                                                step = stepFirst[1] + 3;
                                                }
                                                if (abs(5 - stepFirst[1]) == 3) {
                                                        if (!containInArray(allStep, (stepFirst[1] - 1)))
                                                                step = stepFirst[1] - 1;
                                                        else
                                                                step = stepFirst[1] + 1;
                                                }
                                        }
                                        doStepCPU(step);
                        }
                        else {
                                step = hasFreeOdd();
                        }
                }
                else if (hasFreeOdd() != 0) {
                                step = hasFreeOdd();
                                doStepCPU(step);

                }
                else {
                                step = hasFreeEven();
                                doStepCPU(step);
                }
        lastStepCPU = step;
}

void doStepCPU(int step) {
        stepSecond[countStepSecond] = step;
        allStep[countAllStep] = step;
        countAllStep++;
        countStepSecond++;
}

int hasFreeOdd() {
        for (int i = 0; i <= N; i++)
                if (i % 2 == 1 && !containInArray(allStep, i))
                        return i;
        return 0;
}

int hasFreeEven() {
        for (int i = 0; i <= N; i++)
                if (i % 2 == 0 && !containInArray(allStep, i))
                        return i;
        return 0;
}

int checkForWinOnNextStep(int step[N], int countStep) {
        for (int i = 1; i <= N; i++) {
                if (!containInArray(allStep, i)) {
                        step[countStep] = i;
                        if (checkWeWin(step)) {
                                step[countStep] = 0;
                                return i;
                        }
                        step[countStep] = 0;
                }
        }

        return 0;
}

void oneStep(char symbol) {
        showField(fieldXO);
                currentStep = 1 + checkWeCanWinOrBlocked(fieldXO, 'X', 'O');// проверяем на проигрыш
                if (currentStep == -1) {
                        currentStep = 1 + checkWeCanWinOrBlocked(fieldXO, 'O', 'X');// проверяем на победу
                        if (currentStep == -1)
                            currentStep = playsForX(fieldXO, stepSecond, allStep, countAllStep);
                }
                fieldXO[currentStep - 1] = symbol;


        allStep[countAllStep] = currentStep;
        stepFirst[countStepFirst] = currentStep;
        countStepFirst++;
        countAllStep++;

}

void stepMen(char symbol, int choicePlayer) {
    while(true){
            showField(fieldXO);
            cout << "Make your move, please...";
            cin >> currentStep;
            if (!containInArray(allStep, currentStep)) {
                    fieldXO[currentStep - 1] = symbol;

                    if (choicePlayer == 1) {
                            stepFirst[countStepFirst] = currentStep;
                            countStepFirst++;
                    }
                    else {
                            stepSecond[countStepSecond] = currentStep;
                            countStepSecond++;
                    }
                    allStep[countAllStep] = currentStep;
                    countAllStep++;
                    break;
            }
            else {
                    continue;
            }
    }
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

bool checkWeWin(int step[]) {
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


bool containInArray(int array[N], int numForCheck) {
        for (int i = 0; i < N; i++)
                if (array[i] == numForCheck)
                        return true;
        return false;
}
