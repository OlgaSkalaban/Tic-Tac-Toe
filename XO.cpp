#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

const int N = 9;
int chooseFigure();
void showField(char arr[N]);
bool checkWeCanWin(int step[N]);
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
                                oneStep(0, 'O');
                                if(checkWin())
                                        break;
                        }
                        else {
                                oneStep(0, 'X');
                                if(checkWin())
                                        break;
                                oneStep(1, 'O');
                                if(checkWin())
                                        break;
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
        if (checkWeCanWin(stepFirst)) {
                showField(fieldXO);
                cout << "You is win";
                return true;
        }
        else if (checkWeCanWin(stepSecond)) {
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
