#include <vector>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <fstream>
#include <string>
#include <stdlib.h> 
#include <time.h>
#include <conio.h>
#include <cstdlib>
#include <windows.h>

using namespace std;




void clear() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) return;

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;

    DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;
    DWORD count;
    COORD homeCoords = { 0, 0 };

    // Fill the entire buffer with spaces
    if (!FillConsoleOutputCharacter(
        hConsole,
        (TCHAR)' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    // Fill the entire buffer with the current colors and attributes
    if (!FillConsoleOutputAttribute(
        hConsole,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    // Move the cursor to the top left corner
    SetConsoleCursorPosition(hConsole, homeCoords);
}

class Hangman {
public:
    string password;
    string clonePassword;
    int lives;
    vector<char> wrongLetters;

    Hangman() {
    }

    string makePassword() {
    
        string myText;

        int v1 = 0;
        
        ifstream MyReadFile("filename.txt");
        
        int random = rand() % 90;

        while (getline(MyReadFile, myText)) {
            if (random == v1) {
                break;
            }        
            v1++;
        }
        for(char& c : myText) {
            c = std::tolower(c);
        }
        cout << "Haslo to: " << myText << endl;
        MyReadFile.close();
        return myText;
    }

void showHangman() {
    
    switch (lives)
    {
        case 0:
                cout << endl
            << endl
            << endl
            << endl
            << endl
            << endl
            << endl;
        break;
    case 1:
        cout << endl
            << endl
            << endl
            << endl
            << endl
            << endl
            << "======== = " << endl;
        break;
    case 2:
        cout << endl
            << "|" << endl
            << "|" << endl
            << "|" << endl
            << "|" << endl
            << "|" << endl
            << "======== = " << endl;
        break;
    case 3:
        cout 
            << "+ -- - +" << endl
            << "|" << endl
            << "|" << endl
            << "|" << endl
            << "|" << endl
            << "|" << endl
            << "======== = " << endl;
        break;
    case 4:
        cout 
            << "+ -- - +" << endl
            << "|      |" << endl
            << "|" << endl
            << "|" << endl
            << "|" << endl
            << "|" << endl
            << "======== = " << endl;
        break;
    case 5:
        cout 
            << "+ -- - +" << endl
            << "|      |" << endl
            << "|      o" << endl
            << "|" << endl
            << "|" << endl
            << "|" << endl
            << "======== = " << endl;
        break;
    case 6:
        cout 
            << "+ -- - +" << endl
            << "|      |" << endl
            << "|      o" << endl
            << "|      |" << endl
            << "|" << endl
            << "|" << endl
            << "======== = " << endl;
        break;
    case 7:
        cout 
            << "+ -- - +" << endl
            << "|      |" << endl
            << "|      o" << endl
            << "|     /|" << endl
            << "|" << endl
            << "|" << endl
            << "======== = " << endl;
        break;
    case 8:
        cout 
            << "+ -- - +" << endl
            << "|      |" << endl
            << "|      o" << endl
            << "|     /|\\" << endl
            << "|" << endl
            << "|" << endl
            << "======== = " << endl;
        break;
    case 9:
        cout 
            << "+ -- - +" << endl
            << "|      |" << endl
            << "|      o" << endl
            << "|     /|\\" << endl
            << "|     /" << endl
            << "|" << endl
            << "======== = " << endl;
        break;
    case 10:
        
        cout 
            << "+ -- - +" << endl
            << "|      |" << endl
            << "|      o" << endl
            << "|     /|\\" << endl
            << "|     / \\" << endl
            << "|" << endl
            << "======== = " << endl;
        break;
    default:
        break;
    }
}

void addWrongLetter(char letter) {
    wrongLetters.push_back(letter);
    lives++;
}

void writePassword()
{
    for (int i = 0; i < password.size(); i++) {
        cout << clonePassword[i] << " ";
    }
    cout << endl;
}

void writeWrongLettres() {
    
    cout << "Niepoprawne litery: ";
    for (int i = 0; i < wrongLetters.size(); i++) {
        cout << wrongLetters[i] << " ";
        
    }
    
    cout << endl;
}

bool getChoice() {
    char arrow1 = '>';
    char arrow2 = ' ';
    
    while (true) {

        clear();

        showHangman();
        writePassword();
        writeWrongLettres();
        cout << arrow1 << "1. podaj literke" << endl << arrow2 << "2. zgadnij haslo" << endl << "Wcisnij literke e aby zatwierdzic   wcisnij w lub s aby wybrac opcje" << endl;

        char c = _getch();
        
        switch (c)
        {
        case 'w':
        case 'W':
        case 's': 
        case 'S':
            if (arrow1 == '>') {
                    arrow2 = '>';
                    arrow1 = ' ';
                }
            else
            {
                arrow2 = ' ';
                arrow1 = '>';
            }
            break;
        case 'e':
        case 'E':
            if (arrow1 == '>') {
                return true;
            }
            else
            {
                return false;
            }
            break;
        default:
            break;
        }  
    }
    
    
}

char askForLetter() {
    char letter;
    while (true) {
        cout << "Prosze podac litere" << endl;
        cin >> letter;
        clear();
        if (checkIfLetter(letter)) {
            return tolower(letter);
        }
        else
        {
            cout << "To nie jest litera" << endl;
        }   
    }
}

void fillPassword(char letter) {
    bool checkWrongLetter = false;

    for (int i = 0; i < password.size(); i++) {

        if (password[i] == letter) {
            clonePassword[i] = letter;
            cout << clonePassword[i] << " ";
            checkWrongLetter = true;
        }       
        else 
        {
            cout << clonePassword[i] << " ";
        }        
    }
    if (!(checkWrongLetter) && letter != ' ') {
        addWrongLetter(letter);
    }

    cout << endl;
}

    void win() {
        
        clear();
        showHangman();

        cout << "Wygrales" << endl;
        cout << "odgasles haslo: " << password << endl;

        return;
     
    }

    void loose() {
        clear();
        showHangman();

        cout << "Przegrales" << endl;
        cout << "haslo to: " << password << endl;

        return;
    }

    bool letterInWrong(char letter) {
        for (int i = 0; i < wrongLetters.size(); i++) {
            if (wrongLetters[i] == letter) {
                return true;
            }
        }
        return false;
    }


    bool guessLetter() {
        
        clear();
        while(true)
        {
            char letter = askForLetter();
            if(letterInWrong(letter))
            {
                clear();
                cout << "Juz podales te litere" << endl;
                continue;
            }

            fillPassword(letter);
            if (clonePassword == password) {
                win();
                return true;
            }
            return false;
        }
    }

    bool checkIfWin() {
        if (clonePassword == password) {
            return true;
        }
        else {
            return false;
        }
    }

    bool guessPassword() {
        string guess = "";
        cout << "zgadnij haslo" << endl;
        cin >> guess;
        for (char& c : guess) {
            c = std::tolower(c);
        }
        if (guess == password) {
            return true;
        }
        else
        {
            lives++;
            return false;
        }
    }

    void reset() {
        password = makePassword();
        wrongLetters.clear();
        lives = 0;
        clonePassword = password;
        for (int i = 0; i < password.size(); i++) {
            clonePassword[i] = '_';
        }
    }

    void play() {
        reset();
        while (true)
        {      
            if (lives >= 10) 
            {
                loose();
                break;
            }
            
            if (
                getChoice()) { 
                guessLetter();
                if (checkIfWin()) {
                    win();
                    break;
                }
                else {
                    loose();                    
                }
            }
            else {

                if (guessPassword()) {
                    win();
                    break;
                    
                }
                else {
                    loose();                    
                }
            }
            
        }
    }


    bool again() {

    char arrow1 = '>';
    char arrow2 = ' ';

    while (true) {
       
        cout << "chcialbys zagrac jeszcze raz?  " << endl;
        cout << arrow1 << "Tak :)" << endl << arrow2 << "Nie :(" << endl << "Wcisnij literke e aby zatwierdzic   wcisnij w lub s aby wybrac opcje" << endl;
        char c = _getch();
        clear();
        switch (c)
        {
        case 'w':
        case 'W':
        case 's':
        case 'S':
            if (arrow1 == '>') {
                arrow2 = '>';
                arrow1 = ' ';
            }
            else
            {
                arrow2 = ' ';
                arrow1 = '>';
            }
            break;
        case 'e':
        case 'E':
            if (arrow1 == '>') {
                return true;
            }
            else
            {
                return false;
            }
            break;
        default:
            break;
        }
    }
}

    int run() {
        do
        {
            play();
        } while (again());
        return 0;
    }



    bool checkIfLetter(char letter){
        if (isalpha(letter)) {     
            return true;
        }
        else {
            return false;
        }
    }
};


class GameBoard {
public:
    GameBoard(){

        }
    int moves = 0;
    int x = 0;
    int y = 0;
    int size = 5;
    

   
    bool table[5][5] = {
        {false,false,false,false,false},
        {false,false,false,false,false},
        {false,false,false,false,false},
        {false,false,false,false,false},
        {false,false,false,false,false},
    };

    

    void reset() {
        x = 0;
        y = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                table[i][j] = false;
            }
        }
    }

    void printTable() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
               
                if (i == x && j == y)
                {
                    cout << "$" << "|";
                }
                else if (table[i][j] == true) {
                    cout << "T" << "|";
                }
                else
                {
                    cout << " " << "|";
                }
            }
            cout << endl << "----------" << endl ;
        }
    }

    void ask() {
        

        

            printTable();
            char c = _getch();
            clear();
            switch (c)
            {
            case 'w':
            case 'W':
                if (x > 0) {
                    x--;
                }
                break;
            case 'a':
            case 'A':
                if (y > 0) {
                    y--;
                }
                break;
            case 'd':
            case 'D':
                if (y < (size - 1)) {
                    y++;
                }
                break;
            case 's':
            case 'S':
                if (x < (size - 1)) {
                    x++;
                }
                break;
            case 'e':
            case 'E':
                flip();
                
                break;
            default:
                break;
            }
        

    }
   

    void flip() {
       
        table[x][y] == false ? table[x][y] = true : table[x][y] = false;


       if (x > 0) {
           table[x - 1][y] = !table[x - 1][y];
            //table[x - 1][y] == false ? table[x - 1][y] = true : table[x - 1][y] = false;
        }
           
        

        if (( x + 1) < size){ 
            table[x + 1][y] == false ? table[ x+ 1][y] = true : table[x + 1][y] = false;
        }

        if (y  > 0) {
            table[x ][y - 1] == false ? table[x][y - 1] = true : table[x][y - 1] = false;
        }

        if ((y + 1) < size) {
            table[x][y + 1] == false ? table[x][y + 1] = true : table[x][y + 1] = false;
        }

        
        moves++;
    }
    

    bool checkWin() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (!(table[i][j])) {
                    return false;
                }
            }
        }
        return true;
    }
    
    void play() {
        reset();
        while (true) {
            if (checkWin()) {
                cout << "Gratulacje Wygrales!!!" << endl << "Liczba zrobionych przez ciebie ruchów " << moves << endl;
                break;
            }
            
                ask();
        }
    }

    bool again() {

        char arrow1 = '>';
        char arrow2 = ' ';

        while (true) {

            cout << "chcialbys zagrac jeszcze raz?  " << endl;
            cout << arrow1 << "Tak :)" << endl << arrow2 << "Nie :(" << endl << "Wcisnij literke e aby zatwierdzic   wcisnij w lub s aby wybrac opcje" << endl;
            char c = _getch();
            clear();
            switch (c)
            {
            case 'w':
            case 'W':
            case 's':
            case 'S':
                if (arrow1 == '>') {
                    arrow2 = '>';
                    arrow1 = ' ';
                }
                else
                {
                    arrow2 = ' ';
                    arrow1 = '>';
                }
                break;
            case 'e':
            case 'E':
                if (arrow1 == '>') {
                    return true;
                }
                else
                {
                    return false;
                }
                break;
            default:
                break;
            }
        }
    }

    int run() {
        do
        {
            play();
        } while (again());
        return 0;
    }
};

class field {
public:
    int x = 0;
    int y = 0;
    bool isBomb = false;
    bool isSweeped = false;
    int bombsAround = 0;

    void countBombs(const vector<vector<field>>& board) {
        if (isBomb) {
            return;
        }
        bombsAround = 0;
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if (
                    x + j < 0 || 
                    x + j >= board.size() || 
                    y + i < 0 || 
                    y + i >= board.size())
                {
                    continue;
                }
                if (board[y + i][x + j].isBomb)
                {
                    bombsAround++;
                }
            
            }
        }
    }
    char render() {
        if (!isSweeped)
        {
            return ' ';
        }
        else {
            if (isBomb)
            {
                return 'B';
            }
            else
            {
                if(bombsAround == 0)
                {
                    return '.';
                }
                else
                {
                    return '0' + bombsAround;
                }
            }
        }
    }
    int sweep(vector<vector<field>>& board)
    {
        int sweaped = 1;
        this->isSweeped = true;

        if(bombsAround == 0)
        {
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    if (
                        x + j < 0 || 
                        x + j >= board.size() || 
                        y + i < 0 || 
                        y + i >= board.size())
                    {
                        continue;
                    }
                    if (!board[y + i][x + j].isSweeped)
                    {
                        sweaped += board[y + i][x + j].sweep(board);
                    }
                }
            }
        }
        return sweaped;    
    }
};

class minesweeper {
public:
    vector<vector<field>> board;
    int size = 5;
    int bombs = 5;
    int sweeped = 0;

    int x = 0;
    int y = 0;

    minesweeper() {

    }

    void render() {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if(i == y && j == x)
                {
                    cout << "$|";
                }
                else
                {
                    cout << board[i][j].render() << "|";
                }
            }
            cout << endl;
        }
    }

    void reset() {
        string input;
        while(true)
        {
            cout<<"Jaki rozmiar: ";
            cin>>input;
            try
            {
                size = stoi(input);
                if(size < 1)
                {
                    cout<<"Nieprawidlowa liczba!"<<endl;
                    continue;
                }
                break;
            }
            catch(const std::exception& e)
            {
                cout<<"To nie jest liczba"<<endl;
            }
        }

        while(true)
        {
            cout<<"Ile bomb: ";
            cin>>input;
            try
            {
                bombs = stoi(input);
                if(bombs>size*size)
                {
                    cout<<"Za duzo bomb"<<endl;
                    continue;
                }
                break;
            }
            catch(const std::exception& e)
            {
                cout<<"To nie jest liczba"<<endl;
            }
        }

        board = vector<vector<field>>(size, vector<field>(size));

        for(int i = 0; i < bombs; i++)
        {
            int bx = rand() % size;
            int by = rand() % size;
            if(board[by][bx].isBomb)
            {
                i--;
                continue;
            }
            board[by][bx].isBomb = true;
        }

        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {   
                board[i][j].y = i;
                board[i][j].x = j;
                board[i][j].countBombs(board);
            }
        }

        sweeped = 0;
        x = 0;
        y = 0;  
    }

    int run() {
        reset();

        do{
            render();
            char c = _getch();

            switch (c)
            {
            case 'w':
            case 'W':
                if(y > 0)
                {
                    y--;
                }
                break;
            case 'a':
            case 'A':
                if(x > 0)
                {
                    x--;
                }
                break;
            case 's':
            case 'S':
                if(y < size - 1)
                {
                    y++;
                }
                break;
            case 'd':
            case 'D':
                if(x < size - 1)
                {
                    x++;
                }
                break;
            case 'e':
            case 'E':
                if(board[y][x].isSweeped)
                {
                   
                    continue;
                }
                sweeped += board[y][x].sweep(board);
                
                if(board[y][x].isBomb)
                {
                    cout<<"Przegrales!"<<endl;
                    return 0;
                }
                break;
            default:
                break;
            }
            clear();

        } while(sweeped < size*size - bombs);


    }
};





bool choice() {

    int index = 0;
    int iloscPozycji = 3;

    while (true) {

        cout << "Wybierz gre  " << endl;
        cout 
        << (index == 0 ? '>' : ' ') << "wisielec" << endl 
        << (index == 1 ? '>' : ' ') << "druga gra" << endl 
        << (index == 2 ? '>' : ' ') << "saper" << endl 
        << "Wcisnij literke e aby zatwierdzic   wcisnij w lub s aby wybrac opcje" << endl;
        char c = _getch();
        clear();
        switch (c)
        {
        case 'w':
        case 'W':
            index = ( index-1 < 0 ? iloscPozycji - 1 : index - 1 );
            break;
        case 's':
        case 'S':
            index = (index++ % iloscPozycji);
            break;
        case 'e':
        case 'E':
            switch(index)
            {
                case 0:
                {
                    Hangman ha;
                    return ha.run();
                }
                break;
                case 1:
                {
                    GameBoard ga;
                    return ga.run();
                }
                break;
                case 2:
                {
                    minesweeper ms;
                    return ms.run();
                }
                break;
                default:
                    cout<<"nie ma takiej pozycji"<<endl;
                break;
            }
        }
    }
}


int main()
{
    srand(time(nullptr));

    return choice();
}
