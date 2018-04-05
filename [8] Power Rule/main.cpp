#include <iostream>
#include <string>
#include <deque>

using namespace std;

class DerivativeCalculator{
    public:
    int parse(string input);
    int powerRule(int a, int n);
    int ssplitter(string input, string delimiters);
    int output();
    
    string original;
    deque<string> terms;
    deque<char> operators;
    deque<string> derived;
};

int DerivativeCalculator::ssplitter(string input, string delimiters){
	size_t prev_pos = 0, pos;
    DerivativeCalculator::original = input;
    
    for(int i = 0; i < input.length(); i++){
        if(input[i] == '+' || input[i] == '-'){
        operators.push_back(input[i]);
        }
    }

    while ((pos = input.find_first_of(delimiters, prev_pos)) != string::npos){
        if (pos > prev_pos)
            terms.push_back(input.substr(prev_pos, pos-prev_pos));
        prev_pos= pos+1;
    }
    if (prev_pos< input.length())
        terms.push_back(input.substr(prev_pos, string::npos));

	for (int i = 0; i < terms.size(); i++){
		parse(terms.at(i));
	}
	return 0;
}

int DerivativeCalculator::parse(string input){
    int length = input.length();
    int index;
    string buffer;
    int a=0;
    int n=0;
    //if (input.find("+") == std::string::npos || input.find("-") == std::string::npos){ //!= means found, == means not found
    for (int i = 1; i < length - 1; i++){//Find a
        if (input[i] != '*'){
            buffer += to_string(input[i]-48); //48 is where numbers begin in ASCII
            index = i+4; //Skip the * and ^ **NOTE** VERY SUBJECTIVE, IF EXAMPLE IS x^3 THEN THE INPUT MUST BE "(1*X*3)"
        }
        else{
            a = stoi(buffer);
            break;
            }
    }
    //a is found, now find n
    buffer = "";
    for (int i = index; i < length - 1; i++){//Find a
        if (input[i] != ')'){
        buffer += to_string(input[i]-48); //48 is where numbers begin in ASCII
        }
        n = stoi(buffer);
    }
    //cout << "Sending to power rule" << endl << "a: " << a << endl << "n: " << n << endl;
    powerRule(a, n);
    return 0;
}

int DerivativeCalculator::powerRule(int a, int n){
    //if f(x) = ax^n
    //then f(x) = anx^(n-1)
    a *= n;
    n --;
    string derivative = to_string(a) + "*x^" + to_string(n);
    if (a != 0 && n != 0){
        //cout << "f'(x) = " << derivative << endl;
        derived.push_back(derivative);
    }
    else if(n == 0){
        //cout << "f'(x) = " << a << endl;
        derived.push_back(to_string(a));
    }
    else if (a == 0){
        //cout << "f'(x) = 0" << endl;
        derived.push_back("0");
    }
    return 0; //In the future, return make function string instead of int and return derivative
}

int DerivativeCalculator::output(){
    
    //cout << terms.size() << endl << terms.at(0) << endl << terms.at(1);
    
    cout << "f(x) = " << original << endl;
    cout << "f'(x) = (";
    for (int i = 0; i < derived.size(); i++){                    
        cout << derived.at(i) << ")";
        if (i < derived.size()-1){
            cout << operators.at(i) << "(";
        }
    }
    cout << endl;
    return 0;
}

int main(){
    DerivativeCalculator Derivator;
	Derivator.ssplitter("(5*x^2)+(4*x^3)-(6*x^2)+(7*x^5)", "+-");
    Derivator.output();
    cout << "Application successful, press Enter to exit...";
    cin.get();
    return 0;
}


