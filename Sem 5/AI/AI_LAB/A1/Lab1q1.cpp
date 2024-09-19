#include<bits/stdc++.h>
using namespace std;

#define size 3

void printBoard(char board[size][size]){
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            cout<<board[i][j];
            if(j<size-1) cout<<" | ";
        }
        cout<<endl;
        if(i<size-1) cout<<"--+---+--"<<endl;
    }
}

bool isWin(char board[size][size], char move){
    for(int i=0; i<size; i++){
        if((board[i][0]==move && board[i][1]==move && board[i][2]==move) || (board[0][i]==move && board[1][i]==move && board[2][i]==move))
        return true;
        
        if(board[0][0]==move && board[1][1]==move && board[2][2]==move)
        return true;
    }
    return false;
}

bool isDraw(char board[size][size]){
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(board[i][j]==' ')
            return false;
        }
    }
    return true;
}

int main(){
    char board[size][size] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    
    char move = 'X';
    int row, col;
    while(true){
        printBoard(board);
        cout<<"Player "<<move<<" enter row and col"<<endl;
        cin>>row>>col;
        
        if(row<1 || col<1 || row>3 || col>3 || board[row-1][col-1]!=' '){
            cout<<"Invalid move! Try again"<<endl;
            continue;
        }
        board[row-1][col-1] = move;
        
        if(isWin(board, move)){
            printBoard(board);
            cout<<"Player "<<move<<" wins!"<<endl;
            break;
        }
        
        if(isDraw(board)){
            printBoard(board);
            cout<<"Game is a draw!"<<endl;
            break;
        }
        
        move = (move=='X') ? 'O' : 'X';
    }
    return 0;
}
