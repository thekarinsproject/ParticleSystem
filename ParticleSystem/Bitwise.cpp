#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	unsigned char alpha = 0xFF;
	unsigned char red = 0x12;
	unsigned char green = 0x34;
	unsigned char blue = 0x56;

	unsigned int color = 0;

	color += alpha; // 000000ff
	//shifts the stored value by 1 byte
	color <<= 8; //0000ff00
	color += red; //0000ff12
	color <<= 8; //00ff1200
 	color += green; //00ff1234
	color <<= 8; //ff123400
	color += blue; //ff123456


	/* syntax:
		- setfill(char) allows to fill a variable with a character
		- setw(number) it will display a number of characters
		- hex: it will display the variable value as hexadecimal
	*/
	cout << setfill('0') << setw(8) << hex << color << endl;

	return 0;

}