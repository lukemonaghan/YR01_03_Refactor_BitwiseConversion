//Luke Monaghan - 11/05/2013 - Base 2,10,16 conversion
#include "stdafx.h"
#include "Convert.h"

#include <string.h>
#include <iostream>
#include <climits>
#include <time.h>

#define MAXBITS 32

using namespace std;

bool running = true;
char buffer[48] = {'h','e','l','p'};

Converter ConManager;

void getinput(){
////////////////////////////////////////////////////////////////////////////////////////////////////// Extra Commands
	if (_strcmpi(buffer, "Exit") == 0){
		running = false;
		return;
	}
	if (_strcmpi(buffer, "help") == 0 ){
		cout << endl << "Commands" << endl 
			 << endl << "     - Exit              - Closes program"
			 << endl << "     - Help              - Displays this Help Window"
			 << endl << "     - seed              - Enter a seed to be used for random functions"
			 << endl << "     - Show              - Shows the current values saved for both sets"
			 << endl
			 << endl << "     - BinFlip           - Flips the Current Binary and converts to Hex/Decimal"
			 << endl << "     - DecFlip           - Flips the Current Decimal and converts to Hex/Binary"
			 << endl << "     - HexRand           - Chooses random Hex sequence and converts."
			 << endl << "     - DecRand           - Chooses random Decimal number and converts."
			 << endl << "     - BinRand           - Chooses random Binary Sequence and converts."
			 << endl
			 << endl << "     - BitShift          - Shift the binary bits and converts to hex/decimal."
			 << endl << "                         - <N or >N  where N is the shift distance."
			 << endl
			 << endl << "     - Decimal     / Dec - Input Decimal Number and converts."
			 << endl << "     - HexaDecimal / Hex - Input Hexadecimal sequence and converts."
			 << endl << "     - Binary      / Bin - Input Binary Sequence and converts."
			 << endl << "                         - Input all 32 bits or \"Nx0000\""
			 << endl << "                         - where N = Position(from left) and 0 is bits"
			 << endl;
		return;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////// Key codes (debugging)
	if (_strcmpi(buffer, "keycode") == 0 ){
			char temp = ' '; 
			cout << "KEY : ";cin >> temp; 
			cout << (unsigned int)temp;
			return;
	}
	if (_strcmpi(buffer, "ASCII") == 0 ){
		int temp = 0; 
			cout << "ASCII CODE : ";cin >> temp; 
			cout << char(temp);	
			return;
	}
	if (_strcmpi(buffer, "seed") == 0 ){
			int temp = 0; 
			cout << "Seed Value : ";cin >> temp; 
			srand(temp);
			return;
	}
	if (_strcmpi(buffer, "genrand") == 0 ){
			int temp = 0; 
			cout << "Loops : ";cin >> temp; 
			for (int i = 0; i < temp; i++){
				cout << ConManager.DecRand() << endl; 
			}
			return;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	if (_strcmpi(buffer, "Show") == 0 ){
		ConManager.Show();
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	if (_strcmpi(buffer, "And") == 0 ){
		cout << "Checking First Binary sequence and Second Binary sequence" << endl;
		ConManager.And();
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	if (_strcmpi(buffer, "Or") == 0 ){
		cout << "Checking First Binary sequence Second Binary sequence" << endl;
		ConManager.Or();
	}
////////////////////////////////////////////////////////////////////////////////////////////////////// bit Shifting
		if (_strcmpi(buffer, "BitShift") == 0 ){
			bool shifter;
			cout << "Binary Sequence to shift - 0 or 1 : "; cin >> shifter;
			cout << "direction and amount : "; cin >> buffer;

			if (buffer[0] == '<' || buffer[0] == '>'){
				for (int i = 1; i < strlen(buffer); i++){
					if (buffer[i] >= '9' || buffer[i] <= '0'){
						cout << "Error with command at index " << i << " with char " << buffer[i] << endl;
						return;
					}
				}
			}

			int base = 1;
			int decimal = 0;
			for (int i = strlen(buffer)-1; i > 0; i--){
				decimal += (buffer[i] - '0')*base;
				base*=10;
			}
			cout << decimal << endl;
			bool BinaryTemp[MAXBITS];

			for (int i = 0; i <MAXBITS ; i++){
				if (!shifter) {
					BinaryTemp[i] = ConManager.Binary[i];
				}else{
					BinaryTemp[i] = ConManager.Binary2[i];
				}
			}

			if (buffer[0] == '>'){
				int j;
				for (int i = 31; i >=0 ; i--){
					j = i-decimal;
					if (j < 0 || j > MAXBITS-1){
						j = 0;
					}else{
						j = BinaryTemp[j];
					}
					if (!shifter) {
						ConManager.Binary[i] = j;
					}else{
						ConManager.Binary2[i] = j;
					}
				}
			}else if (buffer[0] == '<'){
				int j;
				for (int i = 31; i >=0 ; i--){
					j = i+decimal;
					if (j < 0 || j > MAXBITS-1){
						j = 0;
					}else{
						j = BinaryTemp[j];
					}
					if (!shifter) {
						ConManager.Binary[i] = j;
					}else{
						ConManager.Binary2[i] = j;
					}
				}
			}
			//Convert to Decimal and hex
			ConManager.Bin2Dec(shifter);
			ConManager.Bin2Hex(shifter);
			//Show
			ConManager.Show();
		return;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////// Fliping
	if (_strcmpi(buffer, "BinFlip") == 0 ){
		bool shifter;
		cout << "Binary Sequence to flip - 0 or 1 : "; cin >> shifter;
		//Flip the binary
		ConManager.BinFlip(shifter);
		//Convert to Decimal and hex
		ConManager.Bin2Dec(shifter);
		ConManager.Bin2Hex(shifter);
		//Show
		ConManager.Show();
		return;
	}
	if (_strcmpi(buffer, "DecFlip") == 0 ){
		bool shifter;
			cout << "Use on - 0 or 1 : "; cin >> shifter;
		//Flip the binary
		ConManager.DecFlip(shifter);
		//Check if its below 0 and do required tasks
		ConManager.Dec2Bin(shifter);
		ConManager.Dec2Hex(shifter);
		//Show
		ConManager.Show();
		return;
	}
	if (_strcmpi(buffer, "HexFlip") == 0 ){
		bool shifter;
		cout << "Hexadecial Sequence to use - 0 or 1 : "; cin >> shifter;
		//Flip the binary
		ConManager.HexFlip(shifter);
		//Check if its below 0 and do required tasks
		ConManager.Hex2Dec(shifter);
		ConManager.Hex2Bin(shifter);
		//Show
		ConManager.Show();
		return;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////// Random sequence Functions
	if (_strcmpi(buffer, "BinRand") == 0 ){
		bool shifter;
		cout << "Binary Sequence to use - 0 or 1 : "; cin >> shifter;
		//reset
		ConManager.Reset(shifter);
		//Generate the binary sequence
		if (!shifter){
			for (int i = 0; i < 32; i++){
				ConManager.Binary[i] = bool(rand()%2);
			}
		}else{
			for (int i = 0; i < 32; i++){
				ConManager.Binary2[i] = bool(rand()%2);
			}
		}
		//Convert to Decimal and Hex
		ConManager.Bin2Dec(shifter);
		ConManager.Bin2Hex(shifter);
		//Display the 3 outputs
		ConManager.Show();
		return;
	}
	if (_strcmpi(buffer, "DecRand") == 0 ){
		bool shifter;
		cout << "Binary Sequence to use - 0 or 1 : "; cin >> shifter;
		//reset
		ConManager.Reset(shifter);
		//Create random decimal number
		if (!shifter){
			ConManager.Decimal = ConManager.DecRand();
		}else{
			ConManager.Decimal2 = ConManager.DecRand();
		}
		ConManager.Dec2Hex(shifter);
		ConManager.Dec2Bin(shifter);
		//Display the 3 outputs
		ConManager.Show();
		return;
	}
	if (_strcmpi(buffer, "HexRand") == 0 ){
		bool shifter;
		cout << "Binary Sequence to use - 0 or 1 : "; cin >> shifter;
		//reset
		ConManager.Reset(shifter);
		//Generate random hex sequence
		if (!shifter){
			for (int i = 0; i < 8; i++){
				ConManager.Hex[i] = ConManager.RandHexChar();
			}
		}else{
			for (int i = 0; i < 8; i++){
				ConManager.Hex2[i] = ConManager.RandHexChar();
			}
		}
		//Convert to Decimal and Binary
		ConManager.Hex2Dec(shifter);
		ConManager.Hex2Bin(shifter);
		//Display the 3 outputs
		ConManager.Show();
		return;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////// Decimal input
	if (_strcmpi(buffer, "Decimal") == 0 || _strcmpi(buffer, "Dec") == 0){
		bool shifter;
		cout << "Binary Sequence to use - 0 or 1 : "; cin >> shifter;
		//reset
		ConManager.Reset(shifter);
		//setup temp bools for error and negative
		bool error = false;
		bool neg   = false;
		//get input
		cout << endl << "Decimal Number : "; cin >> buffer;
		//check if its negative
		if (buffer[0] == '-'){
			neg = true;
			for (int i = 0; i < strlen(buffer); i++){
				buffer[i] = buffer[i+1];
			}
		}
		//check for weird chars (not numbers)
		for (int i = 0; i < strlen(buffer); i++){
			if (buffer[i] < '0' || buffer[i] > '9'){
				error = true;
				cout << int(buffer[i]) << " : error with decimal number of " << buffer[i] << " at index " << i << endl;
				return;
			}
		}
		//if there is no weird chars, run the converter to int
		if (error == false){
			int base = 1;
			if (!shifter){
				ConManager.Decimal = 0;
				for (int i = strlen(buffer)-1; i > -1; i--){
					ConManager.Decimal += (buffer[i] - '0')*base;
					base*=10;
				}
			}else{
				ConManager.Decimal2 = 0;
				for (int i = strlen(buffer)-1; i > -1; i--){
					ConManager.Decimal2 += (buffer[i] - '0')*base;
					base*=10;
				}
			}
			
			//finally convert the decimal to binary and hex
			if (neg == true){
				if (!shifter){
				ConManager.Decimal *= -1;
				}else{
				ConManager.Decimal2 *= -1;
				}
			}
			ConManager.Dec2Hex(shifter);
			ConManager.Dec2Bin(shifter);
		}
		//show the results
		ConManager.Show();
		return;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////// Binary Input
	if (_strcmpi(buffer, "Binary") == 0 || _strcmpi(buffer, "Bin") == 0){
		bool shifter;
		cout << "Binary Sequence to use - 0 or 1 : "; cin >> shifter;
		//reset the 3 values
		ConManager.Reset(shifter);
		//setup the error bool
		bool error = false;
		//get input
		cout << endl << "32 Digit Binary Number : "; cin >> buffer;
		//error check
		for (int i = 0; i < strlen(buffer); i++){
			if (buffer[i] < '0' || buffer[i] > '9'){
				if (buffer[i]=='x' && (i == 1 || i == 2) && strlen(buffer)<MAXBITS){
					continue;
				}
				error = true;
				cout << "error with binary section at index " << i << endl;
				return;
			}
		}
		//complete 32 bit binary sequence
		if (strlen(buffer)==32){
			for (int i = 0; i < 32; i++){
				if (!shifter){
					ConManager.Binary[i] = buffer[i] - '0';
				}else{
					ConManager.Binary2[i] = buffer[i] - '0';
				}
			}
		//binary chunk
		}else if(strlen(buffer)<32 && (buffer[1]=='x' || buffer[2]=='x')){
			int offset = 0;
			int off2 = 0;
			//check if the offset is greater than 10
			if (buffer[1]=='x'){
				offset = buffer[0] - '0';
				off2 = 2;
			}
			if (buffer[2]=='x'){
				offset = (buffer[0] - '0')*10;
				offset += buffer[1] - '0';
				off2 = 3;
			}
			//check its not going past the end of the array
			if (offset+(strlen(buffer)-off2)>MAXBITS){
				error = true;
				cout << "Binary goes outside the 32 bits" << endl;
				ConManager.Show();
				return;
			}
			//finally do its thing
			for (int i = offset; i < offset+(strlen(buffer)-off2); i++){
				if (buffer[i+off2-offset] - '0' != 0){
					if (!shifter){
						ConManager.Binary[i] = true;
					}else{
						ConManager.Binary2[i] = true;
					}
				}else{
					if (!shifter){
						ConManager.Binary[i] = false;
					}else{
						ConManager.Binary2[i] = false;
					}				
				}
			}
		}else{
			//display error
			cout << "error with input" << endl;
		}
		//Convert to Decimal and Hexadecimal
		ConManager.Bin2Dec(shifter);
		ConManager.Bin2Hex(shifter);
		//Display the 3 outputs
		ConManager.Show();
		return;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////// hexadecimal Input
	if (_strcmpi(buffer, "Hexadecimal") == 0 || _strcmpi(buffer, "Hex") == 0){
		bool shifter;
		cout << "Binary Sequence to use - 0 or 1 : "; cin >> shifter;
		//Reset Hex Bin and Dec
		ConManager.Reset(shifter);
		//setup the error bool
		bool error = false;
		//get the input
		cout << endl << "8 Digit Hex Number : "; cin >> buffer;
		//check its than 8 digits
		if (strlen(buffer)==8){
			for (int i = 0; i < 8; i++){
				//convert caps to lowercase
				if ( buffer[i] <= 'z' && buffer[i] >= 'a'){buffer[i]-=MAXBITS;}
				//check its not from 0-9 or from A-F
				if ((buffer[i] > 'F' || buffer[i] < 'A') && (buffer[i] > '9' || buffer[i] < '0')){
					error = true;
					cout << "Error with Hex Value of " << buffer << " at index " << i << endl;
					return;
				}
			}
			//If no errors in input, convert to char array
			if (error == false){
				for (int i = 0; i < 8; i++){
					if (!shifter){
						ConManager.Hex[i] = buffer[i];
					}else{
						ConManager.Hex2[i] = buffer[i];
					}
				}
			}
			//display error
		}else{
			cout << "Error with input, you need 8 digits, you had " << strlen(buffer) << endl;
		}
		//Convert hex to decimal and binary
		ConManager.Hex2Dec(shifter);
		ConManager.Hex2Bin(shifter);
		//display the 3 outputs
		ConManager.Show();
		return;	
	}
}

int main()
{
	//Set time to random
	srand(time(NULL));
	cout << "------------------------------- BitWise Conversions ---------------------------" << endl
		 << "--------------------------------- Luke Monaghan -------------------------------" << endl;
	//Get input (this just displays help as its set by default)
	getinput();
	do{
		//Get command
		cout << endl << "Command : "; cin >> buffer;
		//Run command
		getinput();
	//if not running close
	}while(running==true);
	return 1+1-1-1;
}