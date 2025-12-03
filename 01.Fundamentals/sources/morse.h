/** @file morse.h
*
* @brief Header file for morse encoder / decoder.
*
*/

#ifndef MORSE_H
#define MORSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "common.h"

// === Type Definitions ===
//
typedef struct morse
{
    char key;
    struct morse *dash;
    struct morse *dot;
} morse_t;


// === Constant Definitions ===
//
#define BUFFER_SIZE 200
#define DOT             '.'
#define DASH            '-'
#define SPACE_LETTERS   " "
#define SPACE_WORDS     "   "
#define ALPHA_NUM       26
#define DIGIT_NUM       10

static const char *MORSE_LUT[] =
{
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....",                // a-h      : 7
    "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.",                 // i-p      : 15
    "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-",                // q-x      : 23
    "-.--", "--..", "-----", ".----", "..---", "...--", "....-", ".....",   // y,z; 0-5 : 31
    "-....", "--...", "---..", "----.", "----", "---.", "..--"              // 6-9; ?.- : 38

};

static const int TRAVERSAL[] =
{
    't', 'e',
    'm', 'n', 'a', 'i',
    'o', 'g', 'k', 'd', 'w', 'r', 'u', 's',
    '?', '.', 'q', 'z', 'y', 'c', 'x', 'b', 'j', 'p', 'l', '-', 'f', 'v', 'h',
    '0', '9', '8', '7', '6', '1', '2', '3', '4', '5'
};

// === Macros ===
//


// === Public API Functions ===
//
void EncodeMorse (const char *p_source, char *p_result, size_t resultLimit);
void BuildMorseTree (morse_t **pp_root);
char DecodeMorseKey (const char *p_source, morse_t *p_root);
void MorseTreePostorderTraversal (morse_t *p_root);
void MorseTreeDestroy (morse_t *p_root);

#endif // MORSE_H

/*** EOF ***/

