#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

const int N = 9;
int chooseFigure();
void showField(char arr[N]);
bool checkWeCanWin(int step[N]);
void oneStep(int choicePlayer);
int randomStepCPU();

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


int main()
{
    /*string Player1, Player2;
	cout << "    " << "Game <<Tic-Tac-Toe>> " << endl;
    cout << endl;
    cout << "Enter name of the first player: " << endl;
    getline(cin, Player1);
    cout << "Enter name of the second player: " << endl;
    getline(cin, Player2);
    system("cls");*/

    int choicePlayer = chooseFigure();


    // вывод массива

    while(true) {
            if (choicePlayer == 1) {
                    oneStep(1);
                    oneStep(0);
            }
            else {
                    oneStep(0);
                    oneStep(1);
            }

            if (checkWeCanWin(stepFirst)) {
                    showField(fieldXO);
                    cout << "You is win";
                    break;
            }
            if (checkWeCanWin(stepSecond)) {
                    showField(fieldXO);
                    cout << "CPU is win";
                    break;
            }

            if(countAllStep == 9) {
                    cout << "Draw";
                    break;
            }

    }

    return 0;
}

void oneStep(int choicePlayer) {

        showField(fieldXO);
        if (choicePlayer == 1) {
                cout << "Make your move, please...";
                cin >> currentStep;
                stepFirst[countStepFirst] = currentStep;
                fieldXO[currentStep - 1] = 'X';
        }
        else {
                currentStep = randomStepCPU();
                stepSecond[countStepFirst] = currentStep;
                fieldXO[currentStep - 1] = 'O';
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
