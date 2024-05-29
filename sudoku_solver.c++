#include<bits/stdc++.h>

using namespace std;

//Function to check 3X3 box validity
bool traverse(int sr,int er,int sc,int ec,vector<vector<int>>& sudoku){
    
    for(int i=sr;i<=er;i++){
        unordered_set<int> st;
        for(int j=sc;j<=ec;j++){
            if(sudoku[i][j] == 0) continue;

            if(st.find(sudoku[i][j]) != st.end()) return false;

            st.insert(sudoku[i][j]);
        }
    }

    return true;
}

//Function to check validity of sudoku
bool is_valid(vector<vector<int>>& sudoku){

    for(int i=0;i<9;i++){
        unordered_set<int> st;
        for(int j=0;j<9;j++){
            if(sudoku[i][j] == 0) continue;

            if(st.find(sudoku[i][j]) != st.end()) return false;

            st.insert(sudoku[i][j]);
        }
    }

    for(int j=0;j<9;j++){
        unordered_set<int> st;
        for(int i=0;i<9;i++){
            if(sudoku[i][j] == 0) continue;

            if(st.find(sudoku[i][j]) != st.end()) return false;

            st.insert(sudoku[i][j]);
        }
    }

    for(int i=0;i<9;i+=3){
        unordered_set<int> st;
        int er = i+2;
        for(int j=0;j<9;j+=3){
            int ec = j+2;
            if(!traverse(i,er,j,ec,sudoku)) return false; 
        }
    }
    return true;
}

//Function to check whether a number n can be placed safely at empty location in sudoku
bool is_safe_to_place(vector<vector<int>>& sudoku,int row,int col, int n){
    //Checking for duplicate in column
    for(int i=0;i<9;i++){
        if(sudoku[i][col] == n){
            return false; // same number found in column
        }
    }

    //Checking for duplicate in row
    for(int j=0;j<9;j++){
        if(sudoku[row][j] == n){
            return false; // same number found in row
        }
    }

    //Checking for duplicate in 3X3 box
    int sr = 3*(row/3); //Starting row of 3X3 box
    int sc = 3*(col/3); //Starting column of 3X3 box
    int er = sr+2; //Ending row of 3X3 box
    int ec = sc+2; //Ending column of 3X3 box
    
    for(int i=sr;i<=er;i++){
        for(int j=sc;j<=ec;j++){
            if(sudoku[i][j] == n) return false;
        }
    }
    return true;
}

//function to find empty location in sudoku
bool findEmptyLocation(vector<vector<int>>& sudoku,int &row, int &col){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(sudoku[i][j] == 0){
                row = i;
                col = j;
                return true;
            }
        }
    }
    return false;
}

//Function to solve sudoku
bool sudoku_solver(vector<vector<int>>& sudoku){
    int row,col;
    if(!findEmptyLocation(sudoku,row,col)){
        return true;
    }
    for(int i =1;i<=9;i++){
        if(is_safe_to_place(sudoku,row,col,i)){
            sudoku[row][col] = i;
            if(sudoku_solver(sudoku)){
                return true;
            }
            sudoku[row][col] = 0;
        }
    }
    return false;
}

int main(){

    //take input from the user
    vector<vector<int>> sudoku(9,vector<int>(9));
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            cin >> sudoku[i][j];
        }
    }

    // print Sudoku
    cout << "--------------------SUDOKU--------------------\n";
    cout << "##############################################\n";

    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            cout << sudoku[i][j] << " ";
        }
        cout << endl;
    }

    if(!sudoku_solver(sudoku) || !is_valid(sudoku)) cout << "--------------------INVALID SUDOKU--------------------\n";
    
    else
    {
        cout << "--------------------SOLVED SUDOKU--------------------\n";
        cout << "#####################################################\n";


        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                cout << sudoku[i][j] << " ";
            }
            cout << endl;
        }
    }

    
}
