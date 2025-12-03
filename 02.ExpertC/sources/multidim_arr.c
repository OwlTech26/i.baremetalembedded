/**
 * Copyright (c) 2022 iSee
 *
 * \file multidim_arr.h
 * \brief
 * \author iSee
 * \date 23.10.2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "multidim_arr.h"

#define NUM_OF_MONTHS 12


void MULTI_DIMM_ARR_months(void)
{
	puts("\n---- Illife Vector for months table ---");

	static const char * MONTHS[NUM_OF_MONTHS + 1] = {
		[0]  = "*** This is the ORIG Table for Months in a Year ***",
		[1]  = "January",
		[2]  = "February",
		[3]  = "March",
		[4]  = "April",
		[5]  = "May",
		[6]  = "June",
		[7]  = "July",
		[8]  = "August",
		[9]  = "September",
		[10] = "October",
		[11] = "November",
		[12] = "December"
	};

	// Copy the string
	char * month_copy[NUM_OF_MONTHS + 1];
	for (int i=0; i<NUM_OF_MONTHS + 1; ++i) {
		printf("%s\n", MONTHS[i]);
		month_copy[i] = (char *)malloc(strlen(MONTHS[i]) + 1);
		strcpy(month_copy[i], MONTHS[i]);
	}

	// Replace and print copied string
	char * const copy_owr = strstr(month_copy[0], "ORIG");
	strcpy(copy_owr, "COPY Table for Months in a Year ***");
	for (int i=0; i<NUM_OF_MONTHS + 1; ++i) {
		printf("%s\n", month_copy[i]);
		free(month_copy[i]);
	}
}

void MULTI_DIMM_ARR_func_params_1(const int m_array[2][3][5], const _Bool verbose)
{
	puts(" --- Multi Dimension 3D Array 1. ---");

	if (verbose != 0) {
		for (int i=0; i<2; i++) {
			for (int j=0; j<3; j++) {
				for (int k=0; k<5; k++) {
					printf("m_array[%d][%d][%d] = %d (%#X)\n", i, j, k, m_array[i][j][k], (int)&m_array[i][j][k]);
				}
			}
		}
	}
}

void MULTI_DIMM_ARR_func_params_2(const int m_array[][3][5], const _Bool verbose)
{
	puts(" --- Multi Dimension 3D Array 2. ---");

	if (verbose != 0) {
		for (int i=0; i<2; i++) {
			for (int j=0; j<3; j++) {
				for (int k=0; k<5; k++) {
					printf("m_array[%d][%d][%d] = %d (%#X)\n", i, j, k, m_array[i][j][k], (int)&m_array[i][j][k]);
				}
			}
		}
	}
}

void MULTI_DIMM_ARR_func_params_3(const int (*m_array)[3][5], const _Bool verbose)
{
	puts(" --- Multi Dimension 3D Array 3. ---");

	if (verbose != 0) {
		for (int i=0; i<2; i++) {
			for (int j=0; j<3; j++) {
				for (int k=0; k<5; k++) {
					printf("m_array[%d][%d][%d] = %d (%#X)\n", i, j, k, m_array[i][j][k], (int)&m_array[i][j][k]);
				}
			}
		}
	}
}

// Returning a pointer to an array of 20 integers
// -> This can be wimp it out in a struct as well
int (*MULTI_DIMM_ARR_create(void))[20]
{
	int (*ret_val)[20]; // Pointer to a 20-int array
	ret_val = (int *)calloc(20, sizeof(int));

	if (ret_val == NULL) {
		printf("Unable to allocate array[20]\n");
	}

	return ret_val;
}

void MULTI_DIMM_ARR_destroy(int (*p_array)[20])
{
	free(p_array);
}
