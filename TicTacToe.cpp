#include <iostream>  
#include <string>  
#include <fstream>  
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

void saveBoard(char board[3][3], int currentPlayer) {  
   ofstream outFile("savefile.txt");  
   if (!outFile)  
       return;  

   outFile << currentPlayer << '\n';  
   cout << "Current player SAVE: " << currentPlayer << '\n';  
   for (int i = 0; i < 3; i++) {  
       for (int j = 0; j < 3; j++) {  
           string mark = board[i][j] == ' ' ? to_string(i * 3 + j + 1) : string(1, board[i][j]);  
           outFile << mark << " ";  
       }  
       outFile << '\n';  
   }  
   outFile.close();  
}  

bool loadBoard(char board[3][3], int& currentPlayer) {  
   ifstream inFile("savefile.txt");  
   if (!inFile)  
       return false;  

   inFile >> currentPlayer;  
   cout << "Current player LOAD: " << currentPlayer << '\n';  
   for (int i = 0; i < 3; i++) {  
       for (int j = 0; j < 3; j++) {  
           inFile >> board[i][j];  
       }  
   }  
   inFile.close();  
   return true;  
}  

void deleteSavedBoard() {  
   remove("savefile.txt");  
}  

int main()  
{  
   char board[3][3] = { { '1', '2', '3' },  
                            { '4', '5', '6' },  
                            { '7', '8', '9' } };  
   int savedPlayer = 0;  

   if (!loadBoard(board, savedPlayer)) {  
       cout << "Welcome to Tic Tac Toe!\n";  
       cout << "Player 1 is X and Player 2 is O\n";  
       cout << "To make a move, enter the number of the cell you want to place your mark in.\n";  
       cout << "The board is numbered as follows:\n";  
       cout << "Do you want to play a game? ([Y]/N)\n";  
       string input;  
       if (getline(cin, input) && input == "N")  
           return 0;  
   }  

   string input;  
   do  
   {  
       system("cls");  
       for (int i = 0; i < 3; i++) {  
           for (int j = 0; j < 3; j++) {  
               board[i][j] = ' ';  
           }  
       }  

       if (loadBoard(board, savedPlayer))  
           cout << "Loaded a previous saved game\n";  

       for (int i = 0; i < 9; i++)  
       {  
           drawBoard(board);  
           string currentPlayer = (i + savedPlayer) % 2 == 0 ? "X" : "O";  
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
           if (board[row][col] != 'X' && board[row][col] != 'O')  
           {  
               system("cls");  
               board[row][col] = (i + savedPlayer) % 2 == 0 ? 'X' : 'O';  
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

           saveBoard(board, (i + savedPlayer) % 2 == 0 ? 1 : 0);  
       }  
       cin.clear();  
       cin.ignore(numeric_limits<streamsize>::max(), '\n');  
       deleteSavedBoard();  
       cout << "Do you want to play again([Y]/N)\n";  
   } while (getline(cin, input) && input != "N");  
}