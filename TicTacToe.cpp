#include <iostream>
#include <string>
using namespace std;

void drawBoard(char board[3][3])
{
    cout << "|---|---|---|\n";
    int num = 0;
    for (int i = 0; i < 3; i++) {
        cout << "| ";
        for (int j = 0; j < 3; j++) {
			++num;
			string mark = board[i][j] == ' ' ? to_string(num) : string(1, board[i][j]);
            cout << mark << " | ";
        }
        cout << "\n|---|---|---|\n";
    }
}

bool WinCheck(char board[3][3]) {  
   return (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') ||  
          (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') ||  
          (board[0][0] == board[0][1] && board[0][1] == board[0][2] && board[0][0] != ' ') ||  
          (board[1][0] == board[1][1] && board[1][1] == board[1][2] && board[1][0] != ' ') ||  
          (board[2][0] == board[2][1] && board[2][1] == board[2][2] && board[2][0] != ' ') ||  
          (board[0][0] == board[1][0] && board[1][0] == board[2][0] && board[0][0] != ' ') ||  
          (board[0][1] == board[1][1] && board[1][1] == board[2][1] && board[0][1] != ' ') ||  
          (board[0][2] == board[1][2] && board[1][2] == board[2][2] && board[0][2] != ' ');  
}

int main()  
{  
   cout << "Do you want start Tic Tac Toe([Y]/N)\n";
   string input;  
   while (getline(cin, input) && input != "N")  
   {
	   system("cls");
       char board[3][3] = { { ' ', ' ', ' ' },  
                        { ' ', ' ', ' ' },  
                        { ' ', ' ', ' ' } };  
       
       for (int i = 0; i < 9; i++)
       {
           drawBoard(board);
           string currentPlayer = i % 2 == 0 ? "X" : "O";
           cout << "Player " + currentPlayer + ": ";
           int num;
           if (!(cin >> num))
           {
               system("cls");
               cout << "Invalid input. Please enter a number.\n";
               cin.clear();
               cin.ignore(numeric_limits<streamsize>::max(), '\n');
               i--;
               continue;
           }
           num--;
           int row = num / 3;
           int col = num % 3;
           if (board[row][col] == ' ')
           {  
               system("cls");
               board[row][col] = i % 2 == 0 ? 'X' : 'O';
           }
           else
           {
               system("cls");
               cout << "Invalid move\n";
               i--;
           }

		   if (WinCheck(board))
		   {
			   drawBoard(board);
			   cout << "Player " + currentPlayer + " wins!\n";
			   break;
		   }
       }
	   cin.clear();
	   cin.ignore(numeric_limits<streamsize>::max(), '\n');
	   cout << "Do you want to play again([Y]/N)\n";
   }
}