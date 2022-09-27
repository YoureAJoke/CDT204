#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//exercise 1 a find if the least significant bit is set or not
int findLSB(int num) {
	//if the return is 1 means that lsb is set if 0 its not set.
	return num & 1;
}

//exercise 1 b find if the most significant bit is set or not
int findMSB(int num) {

	//2^31 x 1 = 2147483648 which is the highest value in an signed integer
	//move the first bit of 1 to the highest (moving it from least significant bit to the most significant), it will return 1 if it is set or 0 if it is not set.
	return (1 << 31) & num;
}

//exercise 1 c find the i-th bit of a 32bit int variable
int findIBIT(int num, int bit_check) {
	//shift right bit_check amount of times the number to right and see if value is 0 or 1, 1 means it is set 0 not set. num/bitcheck^(x) x = a value between 0-31
	//check with AND-operand if it is active or not if not return 0 if it is active return 1.
	return (num >> bit_check) & 1;
}
//exercise 1 d set the i-th bit of a 32-bit int variable
int setIBIT(int num, int bit_to_set) {
	//shift left bit_to_set amount to num will give new num value being num x 2^i, i being the bit_to_set value entered.
	return (1 << bit_to_set) * num;
}

//exercise 1 e reset the i-th bit of a 32-bit int variable
int resetIBIT(int num, int bit_to_reset) {
	//do a NOT-operation with bit to reset bit being the only one as 0 do AND-operation to compare number with bit-to-reset only keeping what they have in common being left returning then a new value. 
	// where it is 1 for the first and 0 for the other it wont be stored it has to be 1 to 1 in both
	return (~(1 << bit_to_reset) & num);
}

//exercise 1 f flip the i-th bit of a 32-bit int variable
int flipIBIT(int num, int bit_to_flip) {
	//bitwise XOR between number and the bit to flip, flipping the bit_to_flip into 1 or 0 depending on its initial value in num whethher its being user or not.
	return (1 << bit_to_flip) ^ num;
}

//exercise 1 g to count trailing zeros in a 32-bit int variable
int count_zeros(int num) {
	
	//do a loop to iterate through bits until 1 is found break and return count of the entered number.
	int amount_zero = 0;
	int i = 0;

	while (i < 32) {
		//check if bit is set if its set break
		if ((num >> i) & 1) {
			break;
		}
		amount_zero = amount_zero + 1;
		i++;
	}

	return amount_zero;
}

//exercise 1 h to count leading zeros in a 32 bit int variable
int count_zeros_leading(int num) {
	int amount_zero = 0, msb = 1 << 31;
	int i = 0;
	//do a loop to iterate thgouh bits from msb to backwards until bit that is set is found break and end return the count of zeros
	while (i < 32) {

		if ((num >> i ) & msb) {
			break;
		}

		amount_zero = amount_zero + 1;
		i++;
	}

	return amount_zero;
}

//exercise 1 i To check whether a 32 bit int variable is even or odd
int odd_or_even(int num) {
	// if return is 1 its odd if its 0 its even.
	return num & 1; //checking if bit 0 = 1 if it is that means value is going to be odd bit 0 = 0 is then even.
}

//exercise 1 j to multiply a 32-bit int variable by 16 (the variable stays the same in case of overflow)
int multiply_int(int num) {
	//shift to the left by 4 bits, it will be equal to 2^4 = 16. that means new num will be the number entered multiplied 2^4.
	int new_num = num << 4;

	if (new_num < num) {
		return num;
	}
	else {
		return new_num;
	}
}

//exercise 1 k to calculate the reminder of dividing a 32 bit int variable by 128
int remainder_calc(int num) {
	return num % 128;
}

//exercise 1 l to print the bit representation of a 32bit int variable lsb must be shown on the right

void dec_to_bin(int num) {

	//create a loop to look through every bit starting with msb to lsb, check if the bit is active or not, if active return 1 if not return 0.
	for (int i = 31; i >= 0; i--) {

		if (num >> i & 1) {
			printf("1");
		}
		else {
			printf("0");
		}
	}
}

int main(void) {

	//enter any value to be sent to findlsb also findmsb to see if it is set or not.
	int num;
	printf("Enter a number: ");
	scanf("%d", &num);

	/*
	//check if lsb is set or not.
	int value = findLSB(num);
	if (value == 1) {
		printf("LSB IS SET\n");
	}
	else if (value == 0) {
		printf("LSB IS NOT SET\n");
	}
	*/

	/*
	//check if msb is set or not.
	int value = findMSB(num);
	if (value == 1) {
		printf("MSB IS SET\n");
	}
	else if (value == 0) {
		printf("MSB IS NOT SET\n");
	}
	*/

	/*
	//check (get) the i-th bit of a 32 bit int variable is set or not of an entered number
	printf("number sent %d\n", num);
	//enter the bit pos to check
	printf("Enter a value to check a bit between 0-31, if it is set or not: ");
	int bit_check;
	scanf("%d", &bit_check);
	int value = findIBIT(num,bit_check);
	if (value == 1) {
		printf("Bit is set");
	}
	else if (value == 0) {
		printf("Bit is not set");
	}
	*/
	/*
	//set i-th bit of a 32 bit int variable
	int bit_to_set;
	printf("Enter bit to set between 0-31: ");
	scanf("%d", &bit_to_set);
	int new_num = setIBIT(num, bit_to_set);
	printf("old num %d\nNew num %d", num, new_num);
	*/

	/*
	//reset i-th bit of a 32 bit int variable
	int bit_to_reset;
	printf("Enter the bit to reset between 0-31: ");
	scanf("%d", &bit_to_reset);
	int new_num = resetIBIT(num, bit_to_reset);
	printf("old num %d\nNew num %d", num, new_num);
	*/

	/*
	//flip the i-th bit of a 32 bit int variable
	int bit_to_flip;
	printf("Enter a bit to flip between 0-31: ");
	scanf("%d", &bit_to_flip);
	int new_num = flipIBIT(num, bit_to_flip);
	printf("Old num %d\nNew num %d", num, new_num);
	*/

	/*
	//count trailing zeros in a 32 bit int variable
	int count = count_zeros(num);
	printf("Trailing Count of Zeros %d for the num %d", count, num);
	*/

	/*
	//count leading zeros in a 32 bit int variable
	int count = count_zeros_leading(num);
	printf("Leading Count of Zeros %d for the num %d", count, num);
	*/

	/*
	//to check whether a 32 bit int variable is even or odd
	int value = odd_or_even(num);
	if (value == 1) {
		printf("Number is Odd");
	}
	else if (value == 0) {
		printf("Number is Even");
	}
	*/

	/*
	//To multiply a 32-bit int variable by 16 (the variable stays the same in case of overflow)
	int new_num = multiply_int(num);
	printf("The number: %d ", new_num);
	*/

	/*
	//To calculate the remainder of dividing a 32 bit int variable by 128
	int remainder = remainder_calc(num);
	printf("remainder: %d %% 128 = %d", num, remainder);
	*/

	//To print the bit representation of a 32-bit int variable (LSB must be shown on the right)
	dec_to_bin(num);
	

	return 0;
}
