#include <iostream>
#include <stdio.h>

//a) To check if the Least Significant Bit(LSB) of a 32 - bit int variable is set or not.
int LSB(int x);

//b) To check if the Most Significant Bit (MSB) of a 32-bit int variable is set or not. 
int MSB(int x);

//c) To get the i - th bit of a 32 - bit int variable.
int GNB(int x, int n);

//d) To set the i - th bit of a 32 - bit int variable.
int SNB(int x, int n);

//e) To reset the i-th bit of a 32-bit int variable. 
int RNB(int x, int n);


//f) To flip the i-th bit of a 32-bit int variable. 
int FNB(int x, int n);

int main()
{
	
} 

int LSB(int x) {
	return x & 1;
}

int MSB(int x) {
	return x & (1 << 31);
}

int GNB(int x, int n) {
	return x & (1 << (n - 1));
}

int SNB(int x, int n) {
	return x | 1 << (n-1);
}

int RNB(int x, int n) {
	return x & ~(1 << (n-1));
}

int FNB(int x, int n) {
	return x ^ 1UL << (n-1);
}




