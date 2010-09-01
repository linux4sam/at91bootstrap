#include	<stdlib.h>
#include	<stdio.h>

#ifdef	MACRO
#define	high_bit	0x80000000
#endif

#define	left_shift_64(hi,lo) 	hi <<= 1;\
		if(lo	& 0x80000000) hi |= 0x00000001; \
		lo <<= 1;

#ifdef	DEBUG
static unsigned int error;
#endif

div_t udiv(unsigned int dividend, unsigned int divisor)
// udiv is performing unsigned division 
// returns dividend/divisor in a divt_t structure (quot and rem)
// It is the same as div, except div accepts signed integers
// result = numerator/denominator
/*
	Remainder is a 64 bit register:    {Rem:Quot}.
	The Lower 32 bit is reused as the Quotient

	Place Dividend in Remainder (the lower 32 bit)
	Shift Remainder left 1 bit
	loop 32 times
		signed substract the divisor from the left half of the remainder
			
		if(result < 0) {
			Shift the remainder register left
			remainder.lsb = 0
		}  else {
			Store the result in the left half of the remainder register
			Shift the remainder register left
			remainder.lsb = 1
		}
	end loop
	Shift left half of remainder right 1 bit

*/
{
    div_t result;

    unsigned int Quot, Rem;

    int srem, i;

    unsigned int positive;

#ifdef	DEBUG
    result = div(dividend, divisor);
    if (error) {
        printf("Result = Dividend (%d) /  Divisor (%d)\n", dividend, divisor);
        printf("Expected: Quot = %08d, Rem = %08d\n", result.quot, result.rem);
    }
#endif
    Rem = (dividend & 0x80000000) ? 1 : 0;
    Quot = dividend << 1;

    for (i = 32; i > 0; i--) {
        srem = (int)Rem - (int)divisor;
        positive = (srem >= 0) ? 1 : 0;
        if (positive)
            Rem = (unsigned int)srem;

        left_shift_64(Rem, Quot)
            // Set rightmost bit to "1" if positive or "0" otherwise;
            Quot |= positive;
    }
    Rem >>= 1;
    result.rem = Rem;
    result.quot = Quot;
#ifdef	DEBUG
    if (error) {
        printf("Result:   Quot = %08d, Rem = %08d\n", result.quot, result.rem);
    }
    error = 0;
#endif
    return result;
}

#ifdef	TEST
int main()
{
    unsigned int numerator;

    unsigned int denominator;

    unsigned int error, i;

    div_t valid, test, test2;

    printf("Divide Test!\n");
    for (i = 0; i < 100; i++) {
        printf("i=%d\n", i);
        numerator = (random() % 100) + 1;       // (8192 * 4 * 1056)) + 1;       // Memory Size
        denominator = (random() % 10) + 1;      //(65536)) + 1;                  // Possible Page Size
        valid = div(numerator, denominator);
        test = udiv(numerator, denominator);
        if (valid.rem != test.rem) {
            error = 1;
        }
        if (valid.quot != test.quot) {
            error = 1;
        }
        if (error) {
/*
			printf("%4d:",i);
			printf("Numerator = %d,  Denominator = %d\n", numerator, denominator);	
			printf("\tREM:	%8d\t%08x,\t%8x\t%8x\n",valid.rem,	valid.rem,		test.rem,	test2.rem);
			printf("\tQUOT:	%8d\t%08x,\t%8x\t%8x\n",valid.quot,	valid.quot,	test.quot,	test2.rem);
*/
            test = udiv(numerator, denominator);
        }
    }
    return 0;
}
#endif
