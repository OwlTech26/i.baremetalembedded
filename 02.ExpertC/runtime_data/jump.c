#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;

void jump_test(void)
{
	printf("...in jump_test()\n");
	longjmp(buf, 1);
	/* NOT REACHED */
	printf("Should not reach this point because of JMP.\n");
}

int main(void)
{
	if (setjmp(buf)) {
		printf("...Back in the main.\n");
	} else {
		printf("First jump into the jump_test()...\n");
		jump_test();
	}
	
	return 0;
}
