//header guard
#ifndef _CONVERT
#define _CONVERT
//class define
class Converter{
public:
//Constructor
	Converter();
//Member Functions
	//Reset
	void Reset(bool seq);
	void And();
	void Or();
	//converts
	void DecFlip(bool seq);
	int  DecRand();

	void Dec2Bin(bool seq);
	void Dec2Hex(bool seq);
	
	void BinFlip(bool seq);
	void Bin2Dec(bool seq);
	void Bin2Hex(bool seq);

	void HexFlip(bool seq);
	void Hex2Dec(bool seq);
	void Hex2Bin(bool seq);
	char RandHexChar();
	//Shows
	void Show();
//Values
	bool Binary[32];
	bool Binary2[32];
	char Hex[8];
	char Hex2[8];
	int Decimal;
	int Decimal2;
};

#endif