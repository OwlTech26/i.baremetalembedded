/**
 * Copyright (c) 2022 iSee
 *
 * \file multidim_arr.h
 * \brief
 * \author iSee
 * \date 23.10.2023
 */

#ifndef MULTIDIM_ARR_H
#define MULTIDIM_ARR_H

void MULTI_DIMM_ARR_months(void);
void MULTI_DIMM_ARR_func_params_1(const int m_array[2][3][5], const _Bool verbose);
void MULTI_DIMM_ARR_func_params_2(const int m_array[][3][5], const _Bool verbose);
void MULTI_DIMM_ARR_func_params_3(const int (*m_array)[3][5], const _Bool verbose);
int (*MULTI_DIMM_ARR_create(void))[20];
void MULTI_DIMM_ARR_destroy(int (*p_array)[20]);


#endif /* MULTIDIM_ARR_H */
