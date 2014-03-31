//include the header
#include "Convert.h" 
//we use the following
#include<iostream>
#include <iomanip>
//because im lazy plus this is small, speed isnt a high priority
using namespace std;

//Constructor
Converter::Converter(){
	Reset(true);
	Reset(false);
}
//reset
void Converter::Reset(bool seq){
	if (!seq){
		//reset each binary bit
		for (int i = 0; i < 32; i++){
			Binary[i] = 0;
		}
		//reset each hex bit
		for (int i = 0; i < 8; i++){
			Hex[i] = '0';
		}
		//reset decimal int
		Decimal = 0;
	}else{
		//reset each binary bit
		for (int i = 0; i < 32; i++){
			Binary2[i] = 0;
		}
		//reset each hex bit
		for (int i = 0; i < 8; i++){
			Hex2[i] = '0';
		}
		//reset decimal int
		Decimal2 = 0;
	}
}
void Converter::And(){
	bool BinaryR[32];
	for (int i = 0; i < 32; i ++){
		//binary = not binary, aka 0 = 1, 1 = 0;
		if ((Binary[i] == Binary2[i]) && Binary[i] == 1){
			BinaryR[i] = true;
		}else{
			BinaryR[i] = false;
		}
	}
	cout << "Binary     = ";
	for (int i = 0; i < 32; i++){
		cout << Binary[i];
	}
	cout << endl << "Binary2    = ";
	for (int i = 0; i < 32; i++){
		cout << Binary2[i];
	}
	cout << endl << "Binary And = ";
	for (int i = 0; i < 32; i++){
		cout << BinaryR[i];
	}
}
void Converter::Or(){
	bool BinaryR[32];
	for (int i = 0; i < 32; i ++){
		//binary = not binary, aka 0 = 1, 1 = 0;
		if (Binary[i] == true || Binary2[i]== true){
			BinaryR[i] = true;
		}else{
			BinaryR[i] = false;
		}
	}
	cout << "Binary    = ";
	for (int i = 0; i < 32; i++){
		cout << Binary[i];
	}
	cout << endl << "Binary2   = ";
	for (int i = 0; i < 32; i++){
		cout << Binary2[i];
	}
	cout << endl << "Binary or = ";
	for (int i = 0; i < 32; i++){
		cout << BinaryR[i];
	}
}
//Decimal
void Converter::DecFlip(bool seq){
	if (!seq){
		Decimal *= -1;
		if (Decimal < 0){
		}
	}else{
		Decimal2 *= -1;
		if (Decimal2 < 0){
		}
	}
}
int  Converter::DecRand(){
	//32767 RAND_MAX
	return ((rand()%RAND_MAX) - (RAND_MAX*0.5));
}
void Converter::Dec2Bin(bool seq){
	//temps
	int rem = 0,dec = 0,i = 31;
	if (!seq){
		dec = Decimal;
	}else{
		dec = Decimal2;
	}
	bool flipback = false;
	//if its negative, flip it
	if (dec<0){
		dec*=-1;
		dec--;
		flipback = true;
	}
	//reset binary
	for (int i = 0; i < 32; i++){
		if (!seq){
			Binary[i] = 0;
		}else{
			Binary2[i] = 0;
		}
	}
	//while decimal is not 0
    while(dec!=0){
		//remainder = decimal divide base of 2
        rem=dec%2;
		//if remainder = 1 set the bit to on
		if (!seq){
			if ((rem)>0){Binary[i]=true;}else{Binary[i]=false;}
		}else{
			if ((rem)>0){Binary2[i]=true;}else{Binary2[i]=false;}
		}
		//devide decimal by base of 2
        dec/=2;
		//goto previous binary bit (right to left)
		i--;
    };
	if (flipback){BinFlip(seq);}
}
void Converter::Dec2Hex(bool seq){
	//temps
	int dec;
	double drem;
	bool flipback = false;
	int i = 7;
	//check what decimal we are using
	if (!seq){
	dec  = Decimal;
	drem = Decimal;
	}else{
	dec  = Decimal2;
	drem = Decimal2;
	}
	//check if its negative
	if (dec<0){
		dec*=-1;
		dec--;
		flipback = true;
	}
	//while Decimal is larger than 0
	while (dec>0){
		drem = dec/16.0;   // get remainder for current value
		dec /= 16.0;                 // divide actual decimal for each hex
		drem -= (int)drem;         // take away the full numbers
		drem *= 16;                // times by 16 to get a value between 0-1
		if (drem>9){               // if above 9
			                       // hex of index = 0 to 15 + the char 'A's value - 10
			if (!seq){
				Hex[i] = drem + 'A' - 10;
			}else{
				Hex2[i] = drem + 'A' - 10;
			}
		}else{
			//hex of index = 0 to 15 + the char '0's value
			if (!seq){
				Hex[i] = drem + '0';
			}else{
				Hex2[i] = drem + '0';
			}
		}
		//goto previous hex value
		i--;
	}
	while (i>=0){
		if (!seq){
			Hex[i] = '0';
		}else{
			Hex2[i] = '0';
		}
		i--;
	}
	if (flipback){
		HexFlip(seq);
	}
}
//Binary
void Converter::BinFlip(bool seq){
	//flipping the binary sequence
	for (int i = 0; i < 32; i ++){
		//binary = not binary, aka 0 = 1 or 1 = 0;
		if (!seq){
			Binary[i] = !Binary[i];
		}else{
			Binary2[i] = !Binary2[i];
		}
	}
}
void Converter::Bin2Dec(bool seq){
	//Decimal to binary is as simple as follows
	for (int i = 0; i < 32; i++){
		//decimal = decimal * 2 + binary; for each binary value
		if (!seq){
			Decimal = (Decimal *2) + Binary[i];
		}else{
			Decimal2 = (Decimal2 *2) + Binary2[i];
		}
		//-16711936
	}
}
void Converter::Bin2Hex(bool seq){
	//temps
	int a = 0;
	int temp = 0;
	//itterate through binary bools
	for (int i = 0; i < 32; i+=4){
		//temp binary section
		if (!seq){
			temp = ((Binary[i]*8) + (Binary[i+1]*4) + (Binary[i+2]*2) + (Binary[i+3]));
		}else{
			temp = ((Binary2[i]*8) + (Binary2[i+1]*4) + (Binary2[i+2]*2) + (Binary2[i+3]));
		}
		//check if its above numbers
		if (temp>9){
			if (!seq){
				Hex[a] = temp + 'A' - 10;
			}else{
				Hex2[a] = temp + 'A' - 10;
			}
		}else{
			if (!seq){
				Hex[a] = temp + '0';
			}else{
				Hex2[a] = temp + '0';
			}
		}
		//add to a for each 8 hex values
		a++;	
	}
}
//Hex
void Converter::Hex2Dec(bool seq){
	//Temps
	int base = 1;
	if (!seq){
		Decimal = 0;
	}else{
		Decimal2 = 0;
	}
	int tempint;
	//itterate through hex
	for( int i = 7; i >= 0; i--){
		tempint = 0;
		if (!seq){
			if (Hex[i]>='A'){
				//between A-F
				tempint = Hex[i] - 'A';
				tempint += 10;
			}else{
				//between 0-9
				tempint = Hex[i] - '0';
			}
		
		}else{
			if (Hex2[i]>='A'){
				//between A-F
				tempint = Hex2[i] - 'A';
				tempint += 10;
			}else{
				//between 0-9
				tempint = Hex2[i] - '0';
			}
		}
		//add tempint multiplyed by the base to decimal
		if (!seq){
			Decimal+=tempint*base;
		}else{
			Decimal2+=tempint*base;
		}
		//times the base by 16
		base*=16;
	}
}
void Converter::Hex2Bin(bool seq){
	//setup temps
	int number = 0;
	int j = 0;
	int a;
	//convert the chunk to decimal
	for( int i = 0; i < 8; i++){
		//above 9
		if (!seq){
			if (Hex[i]>='A'){
				//between A-F
				number = 10;
				number += Hex[i] - 'A';
			}else{
				//between 0-9
				number = Hex[i] - '0';
			}
		}else{
			if (Hex2[i]>='A'){
				//between A-F
				number = 10;
				number += Hex2[i] - 'A';
			}else{
				//between 0-9
				number = Hex2[i] - '0';
			}
		}
		//convert the decimal chunk to binary
		int rem = 0;
		a = 3;
		while(number!=0 || a>=0){
			rem=number%2;
			if (!seq){
				if ((rem)>0){Binary[j+a]=true;}else{Binary[j+a]=false;}
			}else{
				if ((rem)>0){Binary2[j+a]=true;}else{Binary2[j+a]=false;}
			}
			number/=2;
			a--;
		};
		j+=4;
	}
}
void Converter::HexFlip(bool seq){
	int tempint;
	if (!seq){
		for (int i = 0; i < 8; i ++){
			tempint = 0;
			if (Hex[i]>='A'){
				//between A-F
				tempint = abs((Hex[i] - 'A') + -5);
			}else{
				//between 0-9
				tempint = abs(15 - (Hex[i] - '0'));
			}
			if (tempint>=10){
				tempint-=10;
				Hex[i] = tempint + 'A';
			}else{
				Hex[i] = tempint + '0';
			}
		}
	}else{
		for (int i = 0; i < 8; i++){
			tempint = 0;
			if (Hex2[i]>='A'){
				//between A-F
				tempint = abs((Hex2[i] - 'A') + -5);
			}else{
				//between 0-9
				tempint = abs(15 - (Hex2[i] - '0'));
			}
			if (tempint>=10){
				tempint-=10;
				Hex2[i] = tempint + 'A';
			}else{
				Hex2[i] = tempint + '0';
			}
		}
	}	
}

char Converter::RandHexChar(){
	//setup temps
	char temp[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	//pick a number between 0-15
	int	 iReturn = rand()%16;
	//return the char at index iRandom
	return temp[iReturn];
}
void Converter::Show(){
	//Decimal
	cout << "Decimal  = " << Decimal << endl;
	//Binary
	cout << "Bin      = ";
	for (int i = 0; i < 32; i++){
		cout << Binary[i];
	}
	cout << endl;
	//Hex
	cout << "Hex      = 0x";
	for (int i = 0; i < 8; i++){
		cout << Hex[i];
	}cout << endl << endl;
	//Decimal
	cout << "Decimal2 = " << Decimal2 << endl;
	//Binary
	cout << "Bin2     = ";
	for (int i = 0; i < 32; i++){
		cout << Binary2[i];
	}
	cout << endl;
	//Hex
	cout << "Hex2     = 0x";
	for (int i = 0; i < 8; i++){
		cout << Hex2[i];
	}cout << endl;

}