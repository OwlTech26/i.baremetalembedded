/**
 * Copyright (c) 2022 iSee
 *
 * \file main.c
 * \brief
 * \author iSee
 * \date 08.11.2022
 */

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "multidim_arr.h"


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define CAST_TO(target_type, expression) ((target_type)(expression))
#define FILE_RAW_MAX		(512u)
#define MAXTOKENS			(100u)
#define MAXTOKENLEN			(64u)


/******************************************************************************/
/*--------------------------Data Structures-----------------------------------*/
/******************************************************************************/
/** \brief Data Template */
	/**< Data 1. */
	//!< Data 2.
enum e_type_tag { e_identifier, e_qualifier, e_type };
typedef enum e_type_tag t_type_tag;

/** \brief Data Template */
	/**< Data 1. */
	//!< Data 2.
typedef struct {
	char type;
	char string[MAXTOKENLEN];
} t_token;

/** \brief Data Template */
	/**< Data 1. */
	//!< Data 2.
typedef struct {
	t_token * item;
	size_t size;
	int top;
} t_stack;


/******************************************************************************/
/*--------------------------Inline Function Prototypes------------------------*/
/******************************************************************************/
/** \brief
 *  \param
 *  \return
 *  	\retval
 */
static inline void basic_notes(void);

/** \brief
 *  \param
 *  \return
 *  	\retval
 */
static inline void decl_unscramble(void);

/******************************************************************************/
/*--------------------------Local Function Prototypes-------------------------*/
/******************************************************************************/
/** \brief 
 *  \param 
 *  \return 
 *  	\retval 
 */
static int stack_init(t_stack * p_stack, const size_t size);

/** \brief
 *  \param
 *  \return
 *  	\retval
 */
static int stack_push(t_stack * const p_stack, const t_token * const data);

/** \brief
 *  \param
 *  \return
 *  	\retval
 */
static int stack_pop(t_stack * const p_stack, t_token * const data);

/** \brief
 *  \param
 *  \return
 *  	\retval
 */
static _Bool stack_is_empty(const t_stack * const p_stack);

/** \brief
 *  \param
 *  \return
 *  	\retval
 */
static void stack_cleanup(t_stack * const p_stack);

/** \brief Look at the current token
 *  \param[in] p_str pointer to the token string
 *  \return t_type_tag
 */
static t_type_tag classify_string(const char * const p_str);

/** \brief Read the next token from the input
 * 			if it is alphanumeric, classify string
 * 			else it must be a single character token
 *  \param[inout] p_src pointer to the source
 *  \param[out] p_token pointer to the token output
 *  \return const char *
 *  	\retval The rest of the unprocessed string
 */
static const char * get_token(const char * p_src, t_token * const p_token);

/** \brief Get the tokens and push them onto the the stack until the first identifier is read.
 *  \param[inout] p_src pointer to the source
 *  \param[out] p_stack pointer to the stack
 *  \return int
 *  	\retval 0  SUCCESS
 *  	\retval -1 FAIL
 */
static int read_to_first_identifier(const char ** p_src, t_stack * const p_stack);

/** \brief Read past closing ')' print out "function returning" */
static const char * parse_function_args(const char * p_src);

/** \brief Read "[size]" print it out and read past it */
static const char * parse_arrays(const char * p_src);

/** \brief Selects the proper parser p */
static void parse_declarator(const char * p_src, t_stack * const p_stack);

/** \brief Passing by value vs reference */
static void func_array(int val, int arr[10]);

/******************************************************************************/
/*----------------------Inline Function Implementations-----------------------*/
/******************************************************************************/
/** \brief */
static inline void basic_notes(void)
{
	puts (" === BASIC NOTES === ");
	// 1. Const is just read-only
	puts ("--- 1. Const is just read-only ---");
	const int limit = 10;
	int * const p_limit = CAST_TO(int * const, &limit);
	printf("Limit: %d ", limit);
	*p_limit = 8;
	printf("Limit_new: %d \n", limit);

	// 2. ANSI or KnR semantics
	puts("--- 2. ANSI or KnR semantics ---");
	if (-1 < CAST_TO(unsigned char, 1)) {
		printf("-1 is less than (unsigned char) 1: ANSI semantics\n");
	} else {
		printf("-1 is NOT less than (unsigned char) 1: KnR semantics\n");
	}

	// 3. Switch-break issue
	puts("--- 3. Switch-break issue ---");
	const int select = 2;
	const int enable = 1;
	switch (select) {
		case 1:
			printf("%d. is selected!\n", select);
			break;
		case 2:
			printf("%d. is selected!\n", select);
			if (1 == enable) {
				printf(" ==> Enabling the SYSTEM...\n");
				break; // <-- BUG!!!
			}
			printf(" ==> SYSTEM INIT, but SKIPPED!!!\n"); // <-- This line will be skipped!!!
			break;
		case 3:
			printf("%d. is selected!\n", select);
			break;
		default:
			printf("%d. is DISABLED!!!\n", select);
	}

	// 4. Structs
	puts("4. Structs");
	struct s_tag { int a[10]; }; // Array inside a struct
	struct s_tag lime, lemon;
	for (int i=0; i<10; ++i) {
		lime.a[i] = (-1) * i;
	}
	lemon = lime; // Copy the entire array via assignment => burying it into a struct
	for (int i=0; i<10; ++i) {
		printf("LemonVal: %d, ", lemon.a[i]);
	}
	puts("");

	// 5. Unions
	puts("5. Unions");
	union bits32_tag {
		int word; // 32-bit word
		struct {char b0, b1, b2, b3;} byte;
	};
	union bits32_tag data;
	data.word= 0xDEADBEEF;
	printf("DATA: 0x%X, -> %X-%X-%X-%X\n", data.word, data.byte.b3 & 0xFF, data.byte.b2 & 0xFF, data.byte.b1 & 0xFF, data.byte.b0 & 0xFF);
}

/** \brief */
static inline void decl_unscramble(void)
{
	const char * const p_file_src = "sources/declarations/decl_sample.txt";
	FILE * const p_file = fopen(p_file_src, "r");

	static const char *res_exp[] = {
		"next is a pointer to a function returning a pointer to const a pointer to char",
		"c is an array[0..9] of a pointer to a function returning a pointer to char"
	};

	if (NULL == p_file) {
		printf("\n Unable to open : %s ", p_file_src);
		exit(EXIT_FAILURE);
	}

	char decl_src[FILE_RAW_MAX] = "";
	int row = 0;
	while (fgets(decl_src, sizeof(decl_src), p_file)) {
		puts("===");
		const char * p_src = strtok(decl_src, "\n");
		printf("Declaration: %s\n", p_src);
		printf("Actual result: \n");

		t_stack stack;
		stack_init(&stack, MAXTOKENS);
		read_to_first_identifier(&p_src, &stack);
		parse_declarator(p_src, &stack);
		stack_cleanup(&stack);

		printf(" => Expected result: \n");
		printf("%s", res_exp[row++]);

		puts("");
	}

	fclose(p_file);
}

/******************************************************************************/
/*----------------------Local Function Implementations------------------------*/
/******************************************************************************/
/** \brief */
static int stack_init(t_stack * p_stack, const size_t size)
{
	int ret_stat = -1;

	p_stack->item = CAST_TO(t_token *, calloc(size, sizeof(t_token)));
	if (NULL != p_stack->item) {
		p_stack->size = size;
		p_stack->top = -1;
		ret_stat = 0;
	} else {
		perror("Unable to allocate stack.\n");
	}

	return ret_stat;
}

/** \brief */
static int stack_push(t_stack * const p_stack, const t_token * const data)
{
	int ret_stat = -1;

	if (p_stack->top < ((int)p_stack->size - 1)) {
		p_stack->top++;
		p_stack->item[p_stack->top].type = data->type;
		strcpy(p_stack->item[p_stack->top].string, data->string);

		ret_stat = 0;
	} else {
		perror("Stack overflow.\n");
	}

	return ret_stat;
}

/** \brief */
static int stack_pop(t_stack * const p_stack, t_token * const data)
{
	int ret_stat = -1;

	if (p_stack->top > -1) {
		data->type = p_stack->item[p_stack->top].type;
		strcpy(data->string, p_stack->item[p_stack->top].string);
		p_stack->top--;

		ret_stat = 0;
	} else {
		perror("Stack underflow.\n");
	}

	return ret_stat;
}

/** \brief */
static _Bool stack_is_empty(const t_stack * const p_stack)
{
	return (-1 == p_stack->top) ? 1 : 0;
}

/** \brief */
static void stack_cleanup(t_stack * const p_stack)
{
	if (NULL != p_stack->item) {
		free(p_stack->item);
	}
}

/** \brief Look at the current token */
static t_type_tag classify_string(const char * const p_str)
{
	t_type_tag ret_stat = e_identifier;

	const int type_ofs = 3;
	static const char * const p_token_map[] = {
		"const", // QUALIFIER
		"read-only", // QUALIFIER
		"volatile", // QUALIFIER
		"void", // TYPE
		"char", // TYPE
		"signed", // TYPE
		"unsigned", // TYPE
		"short", // TYPE
		"int", // TYPE
		"long", // TYPE
		"float", // TYPE
		"double", // TYPE
		"struct", // TYPE
		"union", // TYPE
		"enum" // TYPE
	};

	int match = -1;
	int i=0;
	while((i < (sizeof(p_token_map) / sizeof(p_token_map[0]))) && (match != 0)) {
		if ((match = strcmp(p_str, p_token_map[i])) == 0) {
			if (i >= type_ofs) {
				ret_stat = e_type;
			} else {
				ret_stat = e_qualifier;
			}
		}
		i++;
	}


	return ret_stat;
}

/** \brief Read the next token from the input */
static const char * get_token(const char * p_src, t_token * const p_token)
{
	// Skip white spaces
	while (*p_src == ' ') { p_src++; }

	if (isalnum(*p_src)) { // Alphanumeric A-Z and/or 0-9
		int i = 0;
		while((isalnum(*p_src)) && (*p_src != '\0')) {
			p_token->string[i] = *p_src;
			p_src++;
			i++;
		}
		p_token->string[i] = '\0';
		p_token->type = (char)classify_string(p_token->string);
	} else { // Single character token
		p_token->string[0] = *p_src;
		p_token->string[1] = '\0';
		p_token->type = *p_src;
		p_src++;
	}

	return p_src;
}

/** \brief Get the tokens and push them onto the the stack until the first identifier is read. */
static int read_to_first_identifier(const char **p_src, t_stack * const p_stack)
{
	int ret_stat = -1;

	t_token token = {'0', ""};
	*p_src = get_token(*p_src, &token);
	while(token.type != (char)e_identifier) {
		stack_push(p_stack, &token);
		*p_src = get_token(*p_src, &token);
	}

	if (token.type == (char)e_identifier) {
		printf("%s is ", token.string);

		ret_stat = 0;
	} else {
		perror("Unable to find any identifier\n");
	}

	return ret_stat;
}

/** \brief Read past closing ')' print out "function returning" */
static const char * parse_function_args(const char * p_src)
{
	t_token token;
	while (*p_src != ')') {
		p_src = get_token(p_src, &token);
	}

	p_src = get_token(p_src, &token);
	printf("a function returning ");

	return p_src;
}

/** \brief Read "[size]" print it out and read past it */
static const char * parse_arrays(const char * p_src)
{
	while (*p_src == '[') {
		printf("an array");
		t_token token;
		p_src++;
		p_src = get_token(p_src, &token); // A number or ']'
		if (isdigit(token.string[0])) {
			printf("[0..%d] ", atoi(token.string) - 1);
		}
		printf("of ");
	}
	p_src++; // Read next past the ']'

	return p_src;
}

/** \brief Selects the proper parser p */
static void parse_declarator(const char * p_src, t_stack * const p_stack)
{
	// Skip white spaces
	while (*p_src == ' ') { p_src++; }

	switch (*p_src) {
		case '[':
			p_src = parse_arrays(p_src);
			break;
		case '(':
			p_src = parse_function_args(p_src);
			break;
		default:
			break;
	}

	// Process tokens from the stack
	while (stack_is_empty(p_stack) == 0) {
		t_token token;
		stack_pop(p_stack, &token);

		if (token.type == '(') {
			p_src = get_token(p_src, &token); // Read past ')'
			parse_declarator(p_src, p_stack);
		} else if (token.type == '*') {
			printf("a pointer to ");
		} else {
			printf("%s ", token.string);
		}
	}
}

static void func_array(int val, int arr[10])
{
	val = 0xBEEFDEAD;
	printf("[func_array] Val: 0x%X\n", val);
	for (int i=0; i<10; ++i) {
		arr[i] = 0xDEADBEEF;
		printf("[func_array] Arr[%d]: 0x%X\n", i, arr[i]);
	}
}


/******************************************************************************/
/*-----------------------API Function Implementations-------------------------*/
/******************************************************************************/
/** \brief */
int main(const int argc, const char ** const pp_argv)
{
	if (argc == 2) {
		printf("Hello from C-expert! <%s, %s>\n", pp_argv[0], pp_argv[1]);
	}

	basic_notes();

	decl_unscramble();

	puts("\n--- Function Value / Reference Passing ---");
	int val = 0;
	int arr[10] = {0};
	func_array(val, arr);

	printf("[main] Val: 0x%X\n", val);
	for (int i=0; i<sizeof(arr) / sizeof(arr[0]); ++i) {
		printf("[main] Arr[%d]: 0x%X\n", i, arr[i]);
	}

	printf("Addr arr[0]: %#X\n", (unsigned int)(&arr[0]));

	MULTI_DIMM_ARR_months();

	puts("\n === 3D ARRAY VALID USAGE 1. ===");
	int arr_3d[2][3][5];
	for (int i=0; i<2; i++) {
		for (int j=0; j<3; j++) {
			for (int k=0; k<5; k++) {
				arr_3d[i][j][k] = i+j+k;
			}
		}
	}

	MULTI_DIMM_ARR_func_params_1(arr_3d, 1);
	MULTI_DIMM_ARR_func_params_2(arr_3d, 0);
	MULTI_DIMM_ARR_func_params_3(arr_3d, 0);

	puts("\n === 3D ARRAY VALID USAGE 2. ===");
	const int (* const arr_3d_ptr_1)[3][5] = arr_3d;
	MULTI_DIMM_ARR_func_params_1(arr_3d_ptr_1, 1);
	MULTI_DIMM_ARR_func_params_2(arr_3d_ptr_1, 0);
	MULTI_DIMM_ARR_func_params_3(arr_3d_ptr_1, 0);

	puts("\n === 3D ARRAY VALID USAGE 3. ===");
	const int (* const arr_3d_ptr_2)[2][3][5] = &arr_3d;
	MULTI_DIMM_ARR_func_params_1(*arr_3d_ptr_2, 1);
	MULTI_DIMM_ARR_func_params_2(*arr_3d_ptr_2, 0);
	MULTI_DIMM_ARR_func_params_3(*arr_3d_ptr_2, 0);

	puts("\n === FUNCTION RETURN TO POINTER TO ARRAY ===");
	int (* const p_res)[20] = MULTI_DIMM_ARR_create();
	if (NULL != p_res) {
		for (int i=0; i<20; ++i) {
			(*p_res)[i] = i+20;
		}
		for (int i=0; i<20; ++i) {
			printf("%d, ", (*p_res)[i]);
		}
		MULTI_DIMM_ARR_destroy(p_res);
	}

	return 0;
}

/*** EOF ***/
