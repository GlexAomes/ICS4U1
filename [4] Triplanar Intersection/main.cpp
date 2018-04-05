//Final Version v12 - [Beta] v1 Test for Bugs
//C++14 (G++4.9.2) - www.codechef.com/ide
#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>

using namespace std;
class solver
{
	//here you have the data that your class stores
	double A[3], B[3], C[3], D[3]; //Holds matrix values
	double TA, TB, TC, TD, TSD; //temp values
	double N1XN2a, N1XN2b, N1XN2c, N2XN3a, N2XN3b, N2XN3c, N1XN3a, N1XN3b, N1XN3c, N1XN2Mag, N2XN3Mag, N1XN3Mag; //Normal cross products and magnitudes
	double OGD[3]; //original D values
    double D1nD2, D2nD3, D1nD3; //gcd of the 2 d values (based on var name)
	int Rc, Rd; //Ranks of the matrix
	bool intFound; //If or when a solution is found
	
	public: //methods
	solver() //constructor
	{
		for (int i=0; i<3; i++){
			A[i]=0;
			B[i]=0;
			C[i]=0;
			D[i]=0;
			OGD[i]=0;
		}
		TA=0;
		TB=0;
		TC=0;
		TD=0;
		TSD=0;
		N1XN2a=0;
		N1XN2b=0;
		N1XN2c=0;
		N2XN3a=0;
		N2XN3b=0;
		N2XN3c=0;
		N1XN3a=0;
		N1XN3b=0;
		N1XN3c=0;
		N1XN2Mag=0;
		N2XN3Mag=0;
		N1XN3Mag=0;
		D1nD2=0;
		D2nD3=0;
		D1nD3=0;
	    Rc=0;
	    Rd=0;
	    intFound=false;
	}
	int inputEquation0(int a, int b, int c, int d);
	int inputEquation1(int a, int b, int c, int d);
	int inputEquation2(int a, int b, int c, int d);
	int dispEquations();
	int fixCoefficient(); //Bug fix for dividing 0 by a negative number resulting in -0.00 for matrix
	double fixNumber(double n); //same as above but for any individual number
	int gcd(int x, int y); //Function to get gcd
	int calcNormals(); //calculates the normals
	int calcMatrix(); //calculates the matrix as far as possible
	int dispMatrix(); //displays the final form of the matrix
	int rankMatrix(); //ranks both coefficient and augmented matrices
	int solvePoint(); //returns point if case matches
	int solveOneLine(); //returns equation of line if case(s)[2] matches one line
	int getIntersection(); //returns the solution
};

int solver::inputEquation0(int aIn, int bIn, int cIn, int dIn){ //input data for equation 0
    A[0]=aIn;
    B[0]=bIn;
    C[0]=cIn;
    D[0]=dIn;
}

int solver::inputEquation1(int aIn, int bIn, int cIn, int dIn){ //input data for equation 1
    A[1]=aIn;
    B[1]=bIn;
    C[1]=cIn;
    D[1]=dIn;
}

int solver::inputEquation2(int aIn, int bIn, int cIn, int dIn){ //input data for equation 2
    A[2]=aIn;
    B[2]=bIn;
    C[2]=cIn;
    D[2]=dIn;
}

int solver::dispEquations(){
    cout << "Inputted Equation of Planes: " << endl;
    for (int i = 0; i < 3; i++){
    stringstream sA, sB, sC, sD;
    string ssA, ssB, ssC, ssD;
    if (A[i] == 0){
        sA << "";
    }
    else if (A[i] < 0 && abs(A[i]) != 1){
        sA << fixed << setprecision(1) << "-" << abs(A[i]) << "x ";
    }
    else if (A[i] == 1){
        sA << "x ";
    }
    else if (A[i] == -1 ){
        sA << "-x ";
    }
    else{
        sA << fixed << setprecision(1) << A[i] << "x ";
    }
    if (B[i] == 0){
        sB << "";
    }
    else if (B[i] < 0 && abs(B[i]) != 1){
        sB << fixed << setprecision(1) << "- " << abs(B[i]) << "y ";
    }
    else if (A[i] == 0){
        sB << "y ";
    }
    else if (B[i] == 1){
        sB << "+ y ";
    }
    else if (B[i] == -1 ){
        sB << "- y ";
    }
    else{
        sB << fixed << setprecision(1) << "+ " << B[i] << "y ";
    }
    if (C[i] == 0){
        sC << "";
    }
    else if (C[i] < 0 && abs(C[i]) != 1){
        sC << fixed << setprecision(1) << "- " << abs(C[i]) << "z ";
    }
    else if (A[i] == 0 && B[i] == 0){
        sC << "z ";
    }
    else if (C[i] == 1){
        sC << "+ z ";
    }
    else if (C[i] == -1 ){
        sC << "- z ";
    }
    else{
        sC << fixed << setprecision(1) << "+ " << C[i] << "z ";
    }
    if (D[i] == 0){
        sD << "= 0.0";
    }
    else if (D[i] < 0){
        sD << fixed << setprecision(1) << "- " << abs(D[i]) << " = 0.0";
    }
    else{
        sD << fixed << setprecision(1) << "+ " << D[i] << " = 0.0";
    }
    ssA = sA.str();
    ssB = sB.str();
    ssC = sC.str();
    ssD = sD.str();
    cout << ssA << ssB << ssC << ssD << endl;
    }
    calcNormals();
    return 0;
}


int solver::fixCoefficient(){
        for (int i = 0; i < 3; i++){
            if ((A[i] < 0.01 && A[i] > -0.01) || (to_string(A[i]) == "-nan") || (to_string(A[i]) == "nan") || (to_string(A[i]) == "-inf") || (to_string(A[i]) == "inf")){
            A[i] = 0;
            }
            if ((B[i] < 0.01 && B[i] > -0.01) || (to_string(B[i]) == "-nan") || (to_string(B[i]) == "nan") || (to_string(B[i]) == "-inf") || (to_string(B[i]) == "inf")){
            B[i] = 0;
            }
            if ((C[i] < 0.01 && C[i] > -0.01) || (to_string(C[i]) == "-nan") || (to_string(C[i]) == "nan") || (to_string(C[i]) == "-inf") || (to_string(C[i]) == "inf")){
            C[i] = 0;
            }
            if ((D[i] < 0.01 && D[i] > -0.01) || (to_string(D[i]) == "-nan") || (to_string(D[i]) == "nan") || (to_string(D[i]) == "-inf") || (to_string(D[i]) == "inf")){
            D[i] = 0;
            }
        }
        return 0;
    }
    
double solver::fixNumber(double n){
    if ((n < 0.01 && n > -0.01) || (to_string(n) == "-nan") || (to_string(n) == "nan") || (to_string(n) == "-inf") || (to_string(n) == "inf")){
        n = 0;
    }
    return n;
}
    
int solver::gcd(int x, int y){
	while (x %= y){
		int t = x;
		x = y;
		y = t;
	}
	return y;
    }
    
//RankC
int solver::calcNormals(){
    N1XN2a = B[0]*C[1]-B[1]*C[0];
    N1XN2b = C[0]*A[1]-C[1]*A[0];
    N1XN2c = A[0]*B[1]-A[1]*B[0];
    N2XN3a = B[1]*C[2]-B[2]*C[1];
    N2XN3b = C[1]*A[2]-C[2]*A[1];
    N2XN3c = A[1]*B[2]-A[2]*B[1];
    N1XN3a = B[0]*C[2]-B[2]*C[0];
    N1XN3b = C[0]*A[2]-C[2]*A[0];
    N1XN3c = A[0]*B[2]-A[2]*B[0];

//FACTOR N1XN2
    int i;
    if (N1XN2a != 0 && N1XN2b != 0 && N1XN2c != 0){
    i = gcd(gcd(abs(N1XN2a), abs(N1XN2b)), abs(N1XN2c));
    }
    else if (N1XN2a != 0 && N1XN2b != 0){
    i = gcd(abs(N1XN2a), abs(N1XN2b));
    }
    else if (N1XN2a != 0 && N1XN2c != 0){
    i = gcd(abs(N1XN2a), abs(N1XN2c));
    }
    else if (N1XN2b != 0 && N1XN2c){
    i = gcd(abs(N1XN2b), abs(N1XN2c));
    }
    N1XN2a /= i;
    N1XN2b /= i;
    N1XN2c /= i;
    //FACTOR N1XN2
    
    //FACTOR N2XN3
    int j;
    if (N2XN3a != 0 && N2XN3b != 0 && N2XN3c != 0){
    j = gcd(gcd(abs(N2XN3a), abs(N2XN3b)), abs(N2XN3c));
    }
    else if (N2XN3a != 0 && N2XN3b != 0){
    j = gcd(abs(N2XN3a), abs(N2XN3b));
    }
    else if (N2XN3a != 0 && N2XN3c != 0){
    j = gcd(abs(N2XN3a), abs(N2XN3c));
    }
    else if (N2XN3b != 0 && N2XN3c){
    j = gcd(abs(N2XN3b), abs(N2XN3c));
    }
    N2XN3a /= j;
    N2XN3b /= j;
    N2XN3c /= j;
    //FACTOR N2XN3
    
     //FACTOR N1XN3
    int k;
    if (N1XN3a != 0 && N1XN3b != 0 && N1XN3c != 0){
    k = gcd(gcd(abs(N1XN3a), abs(N1XN3b)), abs(N1XN3c));
    }
    else if (N1XN3a != 0 && N1XN3b != 0){
    k = gcd(abs(N1XN3a), abs(N1XN3b));
    }
    else if (N1XN3a != 0 && N1XN3c != 0){
    k = gcd(abs(N1XN3a), abs(N1XN3c));
    }
    else if (N1XN3b != 0 && N1XN3c){
    k = gcd(abs(N1XN3b), abs(N1XN3c));
    }
    N1XN3a /= k;
    N1XN3b /= k;
    N1XN3c /= k;
    //FACTOR N1XN3
    
            //Fix the stupid -0.00 & "nan"
            if ((N1XN2a < 0.01 && N1XN2a > -0.01) || (to_string(N1XN2a) == "-nan") || (to_string(N1XN2a) == "nan")){
            N1XN2a = 0;
            }
            if ((N1XN2b < 0.01 && N1XN2b > -0.01) || (to_string(N1XN2b) == "-nan") || (to_string(N1XN2b) == "nan")){
            N1XN2b = 0;
            }
            if ((N1XN2c < 0.01 && N1XN2c > -0.01) || (to_string(N1XN2c) == "-nan") || (to_string(N1XN2c) == "nan")){
            N1XN2c = 0;
            }
            if ((N2XN3a < 0.01 && N2XN3a > -0.01) || (to_string(N2XN3a) == "-nan") || (to_string(N2XN3a) == "nan")){
            N2XN3a = 0;
            }
            if ((N2XN3b < 0.01 && N2XN3b > -0.01) || (to_string(N2XN3b) == "-nan") || (to_string(N2XN3b) == "nan")){
            N2XN3b = 0;
            }
            if ((N2XN3c < 0.01 && N2XN3c > -0.01) || (to_string(N2XN3c) == "-nan") || (to_string(N2XN3c) == "nan")){
            N2XN3c = 0;
            }
            if ((N1XN3a < 0.01 && N1XN3a > -0.01) || (to_string(N1XN3a) == "-nan") || (to_string(N1XN3a) == "nan")){
            N1XN3a = 0;
            }
            if ((N1XN3b < 0.01 && N1XN3b > -0.01) || (to_string(N1XN3b) == "-nan") || (to_string(N1XN3b) == "nan")){
            N1XN3b = 0;
            }
            if ((N1XN3c < 0.01 && N1XN3c > -0.01) || (to_string(N1XN3c) == "-nan") || (to_string(N1XN3c) == "nan")){
            N1XN3c = 0;
            }
            
    
    N1XN2Mag = sqrt(pow(N1XN2a,2) + pow(N1XN2b,2) + pow(N1XN2c,2));
    N2XN3Mag = sqrt(pow(N2XN3a,2) + pow(N2XN3b,2) + pow(N2XN3c,2));
    N1XN3Mag = sqrt(pow(N1XN3a,2) + pow(N1XN3b,2) + pow(N1XN3c,2));
    
    cout << "--------------------------------------------------" << endl;
    cout << fixed << setprecision(2) << "N1XN2 = (" << N1XN2a << ", " << N1XN2b << ", " << N1XN2c << ") " << "| Magnitude: " << N1XN2Mag << endl;
    cout << fixed << setprecision(2) << "N2XN3 = (" << N2XN3a << ", " << N2XN3b << ", " << N2XN3c << ") " << "| Magnitude: " << N2XN3Mag << endl;
    cout << fixed << setprecision(2) << "N1XN3 = (" << N1XN3a << ", " << N1XN3b << ", " << N1XN3c << ") " << "| Magnitude: " << N1XN3Mag << endl;
    
    calcMatrix();
    return 0;
}

int solver::calcMatrix(){
        fixCoefficient();
        for (int i = 0; i < 3; i++){
            OGD[i] = D[i];
        }
        D1nD2 = abs(gcd(OGD[0], OGD[1]));
        D2nD3 = abs(gcd(OGD[1], OGD[2]));
        D1nD3 = abs(gcd(OGD[0], OGD[2]));
        //Divide row 1 by first element
        if (A[0] != 0){
        TA = A[0];
        A[0] /= TA;
        B[0] /= TA;
        C[0] /= TA;
        D[0] /= TA;
        }
        else if (A[0] == 0 && A[1] != 0) {
            TA = A[1]; //Swap R1 and R2
            TB = B[1];
            TC = C[1];
            TD = D[1];
            A[1] = A[0];
            B[1] = B[0];
            C[1] = C[0];
            D[1] = D[0];
            A[0] = TA;
            B[0] = TB;
            C[0] = TC;
            D[0] = TD;
            TA = A[0]; //Divide R1 by first element
            A[0] /= TA;
            B[0] /= TA;
            C[0] /= TA;
            D[0] /= TA;
        }
        else if (A[0] == 0 && A[1] == 0 && A[2] != 0) {
            TA = A[2]; //Swap R1 and R3
            TB = B[2];
            TC = C[2];
            TD = D[2];
            A[2] = A[0];
            B[2] = B[0];
            C[2] = C[0];
            D[2] = D[0];
            A[0] = TA;
            B[0] = TB;
            C[0] = TC;
            D[0] = TD;
            TA = A[0]; //Divide R1 by first element
            A[0] /= TA;
            B[0] /= TA;
            C[0] /= TA;
            D[0] /= TA;
        }
        
        if (A[0] == 0 && A[1] == 0){ //Make first element of R2 = 0
            TA = A[1]*A[0];
            TB = A[1]*B[0];
            TC = A[1]*C[0];
            TD = A[1]*D[0];
            A[1] -= TA;
            B[1] -= TB;
            C[1] -= TC;
            D[1] -= TD;
        }
        //Swap any 0 rows
        if (A[1] == 0 && B[1] == 0 && C[1] == 0){
            A[1] = A[2];
            B[1] = B[2];
            C[1] = C[2];
            TSD = D[1];
            D[1] = D[2];
            A[2] = 0;
            B[2] = 0;
            C[2] = 0;
            D[2] = TSD;
        }
        if (A[1] != 0){ //Make first element of R2 = 0
            TA = A[1]*A[0];
            TB = A[1]*B[0];
            TC = A[1]*C[0];
            TD = A[1]*D[0];
            A[1] -= TA;
            B[1] -= TB;
            C[1] -= TC;
            D[1] -= TD;
        }
        
        if (A[2] != 0){ //Make first element of R3 = 0
            TA = A[2]*A[0];
            TB = A[2]*B[0];
            TC = A[2]*C[0];
            TD = A[2]*D[0];
            A[2] -= TA;
            B[2] -= TB;
            C[2] -= TC;
            D[2] -= TD;
        }
        
        //Swap any 0 rows
        if (A[1] == 0 && B[1] == 0 && C[1] == 0 && A[2] != 0 && B[2] != 0 && C[2] != 0){
            A[1] = A[2];
            B[1] = B[2];
            C[1] = C[2];
            TSD = D[1];
            D[1] = D[2];
            A[2] = 0;
            B[2] = 0;
            C[2] = 0;
            D[2] = TSD;
        }
        
        //Divide row 2 by second element
        if (B[1] != 0){
        TA = B[1];
        B[1] /= TA;
        C[1] /= TA;
        D[1] /= TA;
        }
        
        if (B[0] != 0 && B[1] != 0){ //R1 * second element R2
        TA = B[0]*A[1];
        TB = B[0]*B[1];
        TC = B[0]*C[1];
        TD = B[0]*D[1];
        A[0] -= TA;
        B[0] -= TB;
        C[0] -= TC;
        D[0] -= TD;
        }
        
        if (B[2] != 0 && B[1] != 0){
        TB = B[2]*B[1];
        TC = B[2]*C[1];
        TD = B[2]*D[1];
        B[2] -= TB;
        C[2] -= TC;
        D[2] -= TD;
        }
        if (A[1] == 0 && B[1] == 0 && C[1] == 0 && A[2] == 0 && B[2] == 0 && C[2] == 0 && D[1] != 0 && D[2] != 0){
            TA = D[1];
            D[1] /= TA;
            TA = D[1]*D[2];
            D[2] -= TA;
        }
        fixCoefficient();
        if ((A[1] == 0 && B[1] == 0 && C[1] == 0) || (A[2] == 0 && B[2] == 0 && C[2] == 0)){
            //Case 2-8 detected
            rankMatrix();
            intFound = true; //may not need
            dispMatrix();
            return 0;
        }
        
        if (!intFound){ //CASE 1
            //Point int detected, solve matrix
            TA = C[2];
            C[2] /= TA;
            D[2] /= TA;
            //Made the third element of the third row = 1
            if (C[0] != 0){
                TC = C[0]*C[2];
                TD = C[0]*D[2];
                C[0] -= TC;
                D[0] -= TD;
                //Made the third element of the first row = 0
            }
            if (C[1] != 0){
                TC = C[1]*C[2];
                TD = C[1]*D[2];
                C[1] -= TC;
                D[1] -= TD;
                //Made the third element of the second row = 0
            }
            //solvePoint(); //move to getIntersection
            Rd=3;
            Rc=3;
            intFound = true; //may not need
            dispMatrix();
            return 1;
        }
    return -1; //error
}

int solver::rankMatrix(){
    //Rank
        if (A[0] != 0.00){
            Rd++;
            Rc++;
        }
        if (B[1] != 0.00){
            Rd++;
            Rc++;
        }
        else if (B[1] == 0 && C[1] != 0){
            Rd++;
        }
        else if (B[1] == 0 && C[1] == 0 && D[1] != 0){
            Rd++;
        }
        if (C[2] != 0.00){
            Rd++;
            Rc++;
        }
        else if (C[2] == 0 && D[2] != 0){
            Rd++;
        }
        cout << "--------------------------------------------------" << endl;
        cout << "Coefficient Rank is: " << Rc << endl;
        cout << "Augmented Rank is: " << Rd << endl;
        
        return 0;
    }

int solver::dispMatrix(){
    cout << "--------------------------------------------------" << endl << "Row Reduced Echelon Form: " << endl;
    for (int i = 0; i < 3; i++){
        cout << fixed << setprecision(2) << A[i] << " " << B[i] << " " << C[i] << " " << D[i] << endl; 
    }
    return 0;
    }

int solver::solvePoint(){
        cout << "--------------------------------------------------" << endl;
    cout << "Point of Intersection: " << endl;
        cout << fixed << setprecision(2) << "(" << fixNumber(D[0]*-1) << ", " << fixNumber(D[1]*-1) << ", " << fixNumber(D[2]*-1) << ")" << endl;
        return 0;
    }
    
    int solver::solveOneLine(){
    cout << "--------------------------------------------------" << endl;
    cout << "Parametric Equation of the Line of Intersection: " << endl;
    double x, y, Tx, Ty;
    y = (-1)*D[1]/B[1];
    Ty = (-1*C[1])/B[1];
    x = (-1*D[0]) + (-1*B[0])*((-1*D[1])/B[1]);
    Tx = (-1*C[0]) + (-1*B[0])*Ty;
    if (Tx < 0){
        cout << fixed << setprecision(2) << "x = " << x << Tx << "t" << endl;
    }
    else if (Tx >= 1){
        cout << fixed << setprecision(2) << "x = " << x << "+" << Tx << "t" << endl;
    }
    else if (Tx == 0){
        cout << fixed << setprecision(2) << "x = " << x << endl;
    }
    if (Ty < 0){
        cout << fixed << setprecision(2) << "y = " << y << Ty << "t" << endl;
    }
    else if (Ty >= 0){
        cout << fixed << setprecision(2) << "y = " << y << "+" << Ty << "t" << endl;
    }
    else if (Ty == 0){
        cout << fixed << setprecision(2) << "y = " << y << endl;
    }
    cout << "z = t" << endl;
    return 0;
    }

//type of the intersection
int solver::getIntersection()
{
	cout << "--------------------------------------------------" << endl;
	    if (Rc == 3 && Rd == 3){
	        cout << "Intersection Type: Single Point of Intersection" << endl;
            solvePoint();
            return 1;
	    }
	    else if (Rc == 2 && Rd == 2 && (N1XN2Mag == 0 || N2XN3Mag == 0 || N1XN3Mag == 0)){
            cout << "Intersection Type: One Line Intersection (Two Planes Are Coplanar & Coincident)" << endl;
            solveOneLine();
            return 2;
        }
        else if (Rc == 2 && Rd == 2){
            cout << "Intersection Type: One Line Intersection (None of the Planes Are Coplanar)" << endl;
            solveOneLine();
            return 3;
        }
        else if (Rc == 2 && Rd == 3 && N1XN2Mag == N2XN3Mag && N1XN2Mag == N1XN3Mag && N2XN3Mag == N1XN3Mag && N1XN2Mag != 0 && N2XN3Mag != 0 && N1XN3Mag != 0){
            cout << "Intersection Type: Three Line Intersection" << endl;
            cout << "Prismatic surface, therefore no common intersection." << endl;
            return 5;
        }
        else if (Rc == 2 && Rd == 3){
            cout << "Intersection Type: Two Line Intersection (Two Planes Are Parallel)" << endl;
            cout << "No common intersection." << endl;
            return 4;
        }
        else if (Rc == 1 && Rd == 2 && (D1nD2 == 1 && D2nD3 == 1 && D1nD3 == 1)){ //USE GCD to check if original D values are different (scalar multiples)
            cout << "Intersection Type: No Intersection (All Planes Are Coplanar and Never Touch)" << endl;
            return 6;
        }
        else if (Rc == 1 && Rd == 2){
            cout << "Intersection Type: No Intersection (All Planes Are Coplanar & 2 Coincide)" << endl;
            return 7;
        }
        else if (Rc == 1 && Rd == 1){ //Like Rc1, Rc3 but check if same
            cout << "Intersection Type: No Intersection (All Planes Are Coplanar & Coincide)" << endl;
            return 8;
        }
        cout << "--------------------------------------------------" << endl;
	return -1;
}

int main()
{
	solver mySolver;
	mySolver.inputEquation0(0,1,2,3);
	mySolver.inputEquation1(0,2,3,4);
	mySolver.inputEquation2(2,3,4,5);
	mySolver.dispEquations();
	mySolver.getIntersection();
	return 0;
}

