
void delay(unsigned int count)
{
	unsigned int i;
 
	for (i = 0; i < count; i++)
		asm volatile ("    nop");
}

void udelay(unsigned long usec)
{
	unsigned int i;

	for (i = 0; i < usec; i++)
		delay(10);
}
