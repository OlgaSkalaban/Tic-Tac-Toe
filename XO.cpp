#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

const int N = 3;
int chooseFigure();
void showField(int arr[N][N]);

int main()
{
    string Player1, Player2;
	cout << "    " << "Game <<Tic-Tac-Toe>>" << endl;
    cout << endl;
    cout << "Enter name of the first player: " << endl;
    getline(cin, Player1);
    cout << "Enter name of the second player: " << endl;
    getline(cin, Player2);
    system("cls");
    
    chooseFigure();
    
	// заполняем массив элементами 1...9
	int fieldXO[N][N];
    int cellValue = 1;
    for (int i = 0; i < N; i++) {
    	for (int j = 0; j < N; j++) {
    		fieldXO[i][j] = cellValue;
    		cellValue++;
    	}
    }
    // вывод массива
    showField(fieldXO);    
    cout << "Make your move, please...";
    //makeMove();
	//checkWin();
    
    return 0;
}

void showField(int arr[N][N]) {
	cout << "    " << "Game <<Tic-Tac-Toe>>" << endl;
    cout << endl;
    
	for (int i = 0; i < N; i++) {
		cout << "\t" << "   ";
    	for (int j = 0; j < N; j++) {
    		cout << arr[i][j] << " ";
    	}
		cout << endl;	
    }
    cout << endl;
}

int chooseFigure() {
	int figure;	
	
	cout << "    " << "Game <<Tic-Tac-Toe>>" << endl;
    cout << endl;
	cout << "Choose your figure -  X or O: " << endl;
	cout << "X - 1" << endl;
	cout << "O - 0" << endl;
	cout << "Your choice: ";
	cin >> figure;
	system("cls");
	
	return figure;
}

//void makeMove(int ) {
	
