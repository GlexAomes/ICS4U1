//Pseudo Stack
#include <iostream>
#include <sstream>
#include <limits>

using namespace std;

#define maxVal 10000 //allocating mem

int Stack[maxVal];
int Size = 0;
string input;
string intCheck;
int buffer;
char quit = 'n';

int Push (int pushValue){ //Push number into the stack
    if (Size == maxVal){
        cout << "Error: Limit of " << maxVal << " stacks have been reached" << endl;
        return 1; //not 0 return means error
    }
    else{
        Stack[Size] = pushValue;
        Size++;
     }
    return 0; //return 0 means success
}

int Pop(){ //Pop a number out of the stack
    if (Size == 0){
        cout << "Error: Stack is empty." << endl;
    }
    else{
        cout << Stack[Size - 1] << " has been popped." << endl;
        Stack[Size - 1] = 0;
        Size--;
    }
    return 0;
}

int SizeCheck(){
    cout << "Your stack has a size of " << to_string(Size) << "." << endl;
    return 0;
}

int TopCheck(){
    if (Size == 0){
        cout << "Error: Stack is empty." << endl;
    }
    else if (Size == 1){
        cout << "Stack only contains one value: " << Stack[0] << "." << endl;
    }
    else{
        cout << "The top of the stack is: " << Stack[Size - 1] << "." << endl;
    }
    return 0;
}

int BotCheck(){
    if (Size == 0){
        cout << "Error: Stack is empty." << endl;
    }
    else if (Size == 1){
        cout << "Stack only contains one value: " << Stack[0] << "." << endl;
    }
    else{
        cout << "The bottom of the stack is: " << Stack[0] << "." << endl;
    }
    return 0;
}

int Empty(){
    if (Size == 0){
                cout << "Your stack is empty." << endl;
    }
    else if (Size > 0){
        cout << "Your stack is not empty... Would you like to empty it? <y/n>" << endl;
        cin >> input;
            if (input == "y" || input == "Y"){
                fill_n(Stack, Size, 0);
                Size = 0;
                cout << "Your stack has been emptied." << endl;
            }
    }
    return 0;
}

int Disp (){ //Display the stack from top to bottom
    if (Size == 0){
        cout << "Error: Stack is empty." << endl;
    }
    else if (Size == 1){
        cout << "Stack only contains one value: " << Stack[0] << "." << endl;
    }
    else{
    cout << endl << "--Top of Stack--" << endl;
    for (int i = Size; i > 0; i--){
    cout << Stack[i - 1] << endl;
    }
    cout << "--Bottom of Stack--" << endl << endl;
    }
    return 0;
}

int Help(){
    cout << "-----------------------------------------------------------------------" << endl;
    cout << "'Push #' -> Adds your # to the stack. Limit of 10,000 stacks." << endl;
    cout << "'Pop' -> Removes the last # (top) from the stack." << endl;
    cout << "'Display' -> Shows your stack from top to bottom." << endl;
    cout << "'Top' -> Shows the # at the top of your stack." << endl;
    cout << "'Bottom' -> Shows the # at the bottom of your stack." << endl;
    cout << "'Empty' -> Shows if your stack is empty. If not, allow you to empty it." << endl;
    cout << "'Size' -> Shows the size of your stack." << endl;
    cout << "'Quit' -> Terminates the program." << endl << endl;
    cout << "                         Made by Alex Gomes :)" << endl;
    cout << "-----------------------------------------------------------------------" << endl;
    return 0;
}

int main(){ //Ask user for inputs here
    cout << "Welcome to Pseudo Stack. What would you like to do?" << endl;
    cout << "Syntax: Push #, Pop, Display, Top, Bottom, Empty, Size, Help, Quit." << endl; //Note: Enter "Push 10" -> It will push an int of 10.    
    while (quit == 'n' || quit == 'N'){
        cin >> input;
        if (input == "Quit" || input == "quit"){
            cout << "Are you sure you wish to quit? <y/n>" << endl;
            cin >> quit;
        }
        else if (input == "Size" || input == "size"){
            SizeCheck();
        }
        else if (input == "Empty" || input == "empty"){
            Empty();
        }
        else if (input == "Pop" || input == "pop"){
            Pop();
        }
        else if (input == "Push" || input == "push"){
            while (getline(cin, intCheck)){
                stringstream ss(intCheck);
                    if (ss >> buffer){
                        if (ss.eof()){   // Success
                            break;
                        }
                    }
            cout << "Enter the NUMBER you want to push into your stack:" << endl;
            }
        Push(buffer);
        }
        else if (input == "Display" || input == "display" || input == "Disp" || input == "disp"){
            Disp();
        }
        else if (input == "Top" || input == "top"){
            TopCheck();
        }
        else if (input == "Bottom" || input == "bottom" || input == "bot" || input == "Bot"){
            BotCheck();
        }
        else if (input == "Help" || input == "help"){
            Help();
        }
        else{
            cout << "Error: Unrecognized syntax." << endl;
        }
    }
    cout << "See you later!";
    return 0;
}
