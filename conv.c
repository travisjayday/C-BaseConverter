#include <unistd.h>
#define stdout 1
#define stdin 0

#include "helpers.h"

/*
 * Defined in "helpers.h" 
 *
 * int get_strlen(char* str);		// returns length of given char* 
 * int power(int base, int exp);	// returns result of base^exp
 * int str2dec(char* str);		// returns integer from char* representation
 * void print_hexdigit(int* d); 	// prints a digit ranging from 0 - Z (for higher bases like hex) 
 * void input_failure()			// prints "input failure" and exits program
*/


// converts given character string to integer when given base in which string is written
// example: base2base(number_string, 16, 2) converts number_string from base 16 to base 2 
void base2base(char* num, int frombase, int tobase);

/// determines which conversions to do based on second char of input string
// Example: if input is 0x12, it will auto convert from hex to bin and dec
void implicit_conversion(char* input);

// array of all possible output strings
char* output[9] = {
	"dec: ", 								// 0
	"hex: ", 								// 1
	"bin: ", 								// 2
	"\n",    								// 3
	"Usage:\n\
	  conv [0x123]\t\t\tImplicitly converts hex # to decimal and binary\n\
	  conv [0b1010]\t\t\tImplicitly converts bin # to decimal and hex\n\
	  conv [20]  \t\t\tImplicitly converts dec # to hex and binary\n\
	  conv -c    \t\t\tContinuously converts implicit input until EOF\n\
	  conv -e [16] [2] [num]\tExplicitly converts [num] from base [16] to base [2]\n",		// 4
	"Converting ", 								// 5
	" from base ", 								// 6
	" to base " 								// 7
	}; 

int main(int argc, char* args[])
{
	// check if any args were supplied
	if (argc <= 1) 
	{
		write(stdout, output[4], 342);	 			// write usage
		return -2;
	}

	// check for explicit arguments
	if (*args[1] == '-')
	{
		
		switch (*(++args[1])) 
		{
			case 'c': 					// continuous input case
				; 
				char input[20] = {0}; 			// input buffer
				while (1) 
				{
					int numc = read(stdin, input, 20); 
					input[numc-1] = '\0';		// replace newline with '\0'
					implicit_conversion(input); 	// convert input
					write(stdout, output[3], 1);	// write newline
				}
				break;
			case 'e':					// explicit input case
				if (argc != 5) input_failure(); 	// must provide 4 args (+1) 
				write(stdout, output[5], 11); 		// write "Converting " 
				write(stdout, args[4], get_strlen(args[4])); // write given num
			     	write(stdout, output[6], 11);  		// write " from base " 
				write(stdout, args[2], get_strlen(args[2]));  // write given base
				write(stdout, output[7], 9); 		// write " to base "
				write(stdout, args[3], get_strlen(args[3])); 
				write(stdout, output[3], 1); 		// newline
				base2base(args[4], str2dec(args[2]), str2dec(args[3]));
			        write(stdout, output[3], 1); 
				break;
			case 'h':
			default: 
				write(stdout, output[4], 342);
				return -2;
		}
	}
	else 								// implicit input case
		// determine which implicit conversions to do based on input (ex. "0x1A", "0b1010", "20");
		implicit_conversion(args[1]); 
	

	return 0;
}

// determines which conversions to do based on second char of input string
// Example: if input is 0x12, it will auto convert from hex to bin and dec
void implicit_conversion(char* input)
{
	switch(*(input+1))
	{
		case 'x':
			input += 2; 				// offset "0x" of input
			write(stdout, output[1], 5);		// write "hex: " 
		       	base2base(input, 16, 10); 		// write from hex decimal num
			write(stdout, output[3], 1);		// write newline	
			write(stdout, output[2], 5);		// write "bin: " 
			base2base(input, 16, 2);		// convert from hex to binary and write to scrn
			write(stdout, output[3], 1);		// newline
			break;
		case 'b': 
			input += 2;				// offset "0b" of input
			write(stdout, output[0], 5); 		// write "dec: "
			base2base(input, 2, 10);		// convert bin to decimal and output result
			write(stdout, output[3], 1);		// write newline
			write(stdout, output[1], 5);		// write "hex: "
			base2base(input, 2, 16);		// convert bin to hex and output result
			write(stdout, output[3], 1);		// write newline
			break;
		default: 					// assume input is decimal
			write(stdout, output[1], 5);		// print "hex: " 
			base2base(input, 10, 16);		// from base 10 write hex
			write(stdout, output[3], 1);		// write newline
			write(stdout, output[2], 5);		// print "bin: "
			base2base(input, 10, 2);		// from base 10, write binary 
			write(stdout, output[3], 1);		// write newline
	}
}



// prints a given number to screen in a specific base format (recursively) 
void print_base(unsigned int dec, int base, char root) 
{
	int div = dec / base;					// divide to get larger digit
	int rem = dec % base;					// provide to get smaller
	
	if (div > base -1) 					// if larger digit is too big
		print_base(div, base, 0);			// subdivide larger digit by recursion
	else
	{
		print_hexdigit(&div);				// else just print larger digit
		print_hexdigit(&rem);				// and smaller digit
		return; 		
	}
	print_hexdigit(&rem);					// in recursion, if larger digit was too big,
								// just print remainder because the recursive 
								// functions already printed subdivided version 
								// of larger digit
	return;
}

// converts given character string to integer when given base in which string is written
// example: base2dec("14", 16) converts 14 to 20 because base = 16
void base2base(char* num, int inbase, int outbase)
{
	int len = get_strlen(num);				// get string len for looping
	unsigned int result = 0;						// result number 
	for (int i = 0; i < len; i++) 
	{
		char val = *(num+len-1-i);			// get temp of char value
		if (val > '9') 					// if its and alpha char, convert it to 
		{
			if (val >= 'a')
				val -= 'a' - 10; 
			else 
				val -= 'A' - 10;		// regular integer
		}
		else
			val -= '0';				

		if (val > inbase -1)				// test if input char is in base range (i.e.  
			input_failure();			// can't have #4 in binary num. So call, in_failure();
	
		result += power(inbase, i) * val; 		// accumulate in result the digit value times its position
	}
	print_base(result, outbase, 1); 			// then print it in given format
}
