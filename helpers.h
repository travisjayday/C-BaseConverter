
/* PROTOTYPES */

int get_strlen(char* str);	// returns length of given char* 
int power(int base, int exp);	// returns result of base^exp
int str2dec(char* str);		// returns integer from char* representation
void print_hexdigit(int* d); 	// prints 1 hex digit, given a decimal digit
void input_failure(); 		// called when user gives wrong input, exits program


/* DEFINITIONS */ 

void input_failure() 
{
	char* out = "\nInput Failure!\n";
	write(stdout, out, 16);					// write "input failure!"
	_exit(-1); 						// defined in "unistd.h"
}

// prints hex digit to screen, given an integer address
void print_hexdigit(int* d) 
{
	if (*d > 9)
		*d += 'A' - 10; 
	else
		*d += '0';
	write(1, d, 1); 	// write( int fd, buf*, int num_chars)
}

// equivalent to atoi()
int str2dec(char* str) 
{
	int len = get_strlen(str); 
	int result = 0;
	for (int i = 0; i < len; i++)
		// result += b10 ^ digit position * digit value
		result += power(10, i) * (*(str+len-1-i) - '0');
	return result;
}

// equivalent to pow()
int power(int base, int exp) 
{
	int result = 1;
	for (; exp > 0; exp--) 
		result *= base; 
	return result;
}

// equivlaent to strlen()
int get_strlen(char* str)
{
	int c = 0;
	for (; *(str+c) != 0; c++);
	return c; 
}


