#include <stdio.h>
#include <string.h>

#define DATA_SIZE 65536
#define COPY_RUN 10000
#define DUMBCOPY_TEST for (i=0; i<DATA_SIZE; ++i) \
	dest[i] = src[i]
	
#define SMARTCOPY_TEST memcpy(dest, src, DATA_SIZE)


int main(int argc, char *argv[]) 
{
	if (argv[1] != NULL) {
		int i, j;
		char src[DATA_SIZE], dest[DATA_SIZE];
				
		const char smart[] = "smart";
		if (strcmp(argv[1], smart) == 0) {
			printf("Executing SMART COPY TEST...\n");
			for (j=0; j<COPY_RUN; ++j) {
				SMARTCOPY_TEST;
			}
		} else {
			printf("Executing DUMB COPY TEST...\n");
			for (j=0; j<COPY_RUN; ++j) {
				DUMBCOPY_TEST;
			}
		}
	} else {
		printf("ERROR, missing argument. Use 'smart' for smart copy.\n");
	}
}
