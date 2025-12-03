/** @file morse.c
*
* @brief Morse encoder / decoder.
*
*/

#include "morse.h"


// === Protected Functions ===
//
/*!
* @brief Initializes the morse root
*        Inserts the starting node       root
*                                          |
*                                        START
*                                        /   \
*                                DASH <-       -> DOT
* @param[in] **pp_root The root address of the morse code
* @param[in] value The character to be inserted
* @param[in] *p_symbol The encoded morse token
*
* @return void
*/
static void InitializeMorseTree (morse_t **pp_root)
{
    morse_t *p_startNode = (morse_t *)malloc(sizeof(morse_t));
    if (NULL == p_startNode)
    {
        perror("Insufficient memory fatal error.\n");
        exit(-1);
    }

    p_startNode->key = '\0';
    p_startNode->dash = NULL;
    p_startNode->dot = NULL;
    *pp_root = p_startNode;
}

/*!
* @brief Morse character inserter
*
* @param[in] **pp_root Pointer to the morse tree root address pointer
* @param[in] value The character to be inserted
* @param[in] *p_symbol The encoded morse token
*
* @return void
*/
static void InsertMorseTreeNode (morse_t **pp_root, const char value, char *p_symbol)
{
    if (NULL == *pp_root)
    {
        *pp_root = (morse_t *)malloc(sizeof(morse_t));
        if (NULL == *pp_root)
        {
            perror("Insufficient memory fatal error.\n");
            exit(-1);
        }

        (*pp_root)->key = value;
        (*pp_root)->dash = NULL;
        (*pp_root)->dot = NULL;
    }
    else if (DASH == *p_symbol)
    {
        p_symbol++;
        InsertMorseTreeNode( &((*pp_root)->dash), value, p_symbol);
    }
    else    // DOT Symbol
    {
        p_symbol++;
        InsertMorseTreeNode( &((*pp_root)->dot), value, p_symbol);
    }
}

// === Public API Functions ===
//
/*!
* @brief Simple Morse Encoder
*
* @param[in] *p_source String to be encoded
* @param[out] *p_result The encoded string
* @param[out] resultLimit Limitation of the result length
*
* @return void
*/
void EncodeMorse (const char *p_source, char *p_result, size_t resultLimit)
{
    bool b_addSpace;
    bool b_skipChar;
    int currentAlphaNum;

    while (*p_source)
    {
        b_addSpace = false;
        b_skipChar = false;

        currentAlphaNum = (int)(*p_source);
        if (isalpha(currentAlphaNum))
        {
            currentAlphaNum = tolower(currentAlphaNum) - 'a';
        }
        else if (isdigit(currentAlphaNum))
        {
            currentAlphaNum -= '0' - ALPHA_NUM;
        }
        else if (' ' == *p_source)
        {
            b_addSpace = true;
        }
        else    // Special characters
        {
            switch (*p_source)
            {
                case '?':
                    currentAlphaNum = ALPHA_NUM + DIGIT_NUM;
                    break;
                case '.':
                    currentAlphaNum = ALPHA_NUM + DIGIT_NUM + 1;
                    break;
                case '-':
                    currentAlphaNum = ALPHA_NUM + DIGIT_NUM + 2;
                    break;
                default:    // Not acceptable characters, skipped
                    b_skipChar = true;
                    break;
            }
        }

        if (!b_skipChar)
        {
            snprintf(p_result, resultLimit, "%s%s%s", p_result, (b_addSpace) ? SPACE_WORDS : MORSE_LUT[currentAlphaNum], (b_addSpace) ? "" : SPACE_LETTERS);
        }

        p_source++;
    }
}

/*!
* @brief Simple Morse Encoder
*
* @param[in] **pp_root The root address of the morse tree
*
* @return void
*/
void BuildMorseTree (morse_t **pp_root)
{
    InitializeMorseTree(pp_root);
    char *p_symbol;
    int value;

    for (int i = 0; i < NUM_OF(TRAVERSAL); ++i)
    {
        value = tolower(TRAVERSAL[i]);
        p_symbol = (isalpha(value)) ? MORSE_LUT[value - 'a'] :
                   (isdigit(value)) ? MORSE_LUT[value - '0' + ALPHA_NUM] :
                   ('?' == value)   ? MORSE_LUT[ALPHA_NUM + DIGIT_NUM] :
                   ('.' == value)   ? MORSE_LUT[ALPHA_NUM + DIGIT_NUM + 1] : MORSE_LUT[ALPHA_NUM + DIGIT_NUM + 2];

        InsertMorseTreeNode(pp_root, (char)value, p_symbol);
    }
}

/*!
* @brief Morse Decoder
*
* @param[in] *p_source String to be decoded
* @param[in] *p_root The root of the morse tree
*
* @return The decoded character
*/
char DecodeMorseKey (const char *p_source, morse_t *p_root)
{
    if (NULL == p_source)
    {
        return '\0';
    }

    char key = '/';
    while (*p_source)
    {
        if (NULL == p_root)
        {
            return key;
        }

        if (DASH == *p_source)
        {
            p_root = p_root->dash;
        }
        else if (DOT == *p_source)
        {
            p_root = p_root->dot;
        }
        else  // Invalid morse key is detected
        {
            return key;
        }

        p_source++;
    }

    return p_root->key;
}

/*!
* @brief Postorder Traversal of the whole Morse Tree
*
* @param[in] *p_root The root address of the morse tree
*
* @return void
*/
void MorseTreePostorderTraversal (morse_t *p_root)
{
    if (NULL != p_root)
    {
        MorseTreePostorderTraversal(p_root->dash);
        MorseTreePostorderTraversal(p_root->dot);
        printf("%c, ", p_root->key);
    }
    else
    {
        return;
    }
}

/*!
* @brief Morse Tree Cleanup with Postorder Traversal
*
* @param[in] *p_root The root address of the morse tree
*
* @return void
*/
void MorseTreeDestroy (morse_t *p_root)
{
    if (NULL != p_root)
    {
        MorseTreeDestroy(p_root->dash);
        MorseTreeDestroy(p_root->dot);
        free(p_root);
    }
    else
    {
        return;
    }
}

/*** EOF ***/

