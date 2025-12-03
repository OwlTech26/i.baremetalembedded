/** @file process.c
*
* @brief Collection of the execution process
*
*/

#include "common.h"
#include "process.h"


// === Protected Functions ===
//
/*!
* @brief Searching for element in the array
*
* @param[in] *p_source The input character array
* @param[in] element The element to be searched
* @param[in] size Size of the array
*
* @return -1: Not Found, >0: Found at index
*/
static inline int SearchCharArray (const char *p_source, const char element, size_t size)
{
    for (int i = 0; i < size; i++)
    {
        if (p_source[i] == element)
        {
            return i;
        }
    }

    return -1;
}

/*!
* @brief Power of Integer
*
* @param[in] b Base
* @param[in] e Exponent
*
* @return b^e
*/
static int PowerInt (int b, int e)
{
    if (e > 1)
    {
        return (b * PowerInt(b, --e));
    }
    else return b;
}

/*!
* @brief Detects if the Input is Operator
*
* @param[in] token Input token
*
* @return true: operator, false: non operator
*/
static bool IsOperator (const char token)
{
    const char operators[] = {'+', '-', '*', '/', '$', '(', ')'};

    for (int i = 0; i < NUM_OF(operators); ++i)
    {
        if (operators[i] == token)
        {
            return true;
        }
    }

    return false;
}

/*!
* @brief Precedence Checker
*
* @param[in] tokenHigh Higher precedence token (guessed)
* @param[in] tokenLow Lower precedence token (guessed)
*
* @return 0: false, tokenHigh has no higher precedence
*         1: true, tokenHigh has higher precedence
*         2: discard, '(' and ')' is detected
*/
static int PrecedenceChecker (char tokenHigh, char tokenLow)
{
    const char precedenceOrder[] = {'+', '-', '*', '/', '$'};

    if (( '(' == tokenHigh ) && ( ')' == tokenLow))
    {
        return 2;
    }
    if (( '(' == tokenHigh ) || ( '(' == tokenLow))
    {
        return 0;
    }
    if (')' == tokenLow)
    {
        return 1;
    }

    for (int i = 0; i < NUM_OF(precedenceOrder); ++i)
    {
        if (precedenceOrder[i] == tokenHigh)
        {
            tokenHigh = (char) (i >> 1);
        }
        if (precedenceOrder[i] == tokenLow)
        {
            tokenLow = (char) (i >> 1);
        }
    }

    return (tokenHigh >= tokenLow) ? 1 : 0;
}

/*!
* @brief Postfix evaluation (Reverse Polish Notation)
*
* @param[in] *p_source The source string
*
* @return The Integer Result
*/
int PostfixCalc (char *p_source)
{
    t_stack s1;
    InitializeStack(&s1, 10);

    int result = 0;
    int i = 0;

    while (*p_source)
    {
        if ( isdigit(result = (int) *p_source) )
        {
            result -= '0';
            PushStack(&s1, result);
        }
        else
        {
            result = PopStack(&s1);
            switch (*p_source)
            {
                case '+':
                    result += PopStack(&s1);
                    break;
                case '-':
                    result = PopStack(&s1) - result;
                    break;
                case '*':
                    result *= PopStack(&s1);
                    break;
                case '/':
                    result = PopStack(&s1) / result;
                    break;
                case '$':
                    result = PowerInt(PopStack(&s1), result);
                    break;
                default:
                    printf("Unidentified operand in the expression: %c", *p_source);
                    break;
            }

            PushStack(&s1, result);
        }

        p_source++;
    }

    result = PopStack(&s1);
    if ( (i = GetStackTop(&s1)) > -1 )
    {
        printf("Wrong calculation, items in the stack: %d\n", i);
    }

    CleanupStack(&s1);

    return result;
}


// === Public API Functions ===
//
/*!
* @brief Printing Decimal Number to Binary Format
*
* @param[in] n The decimal value
*
* @return 0: Success, 1: Fail
*/
int PrintToBinary (int n)
{
    t_stack binStack;

    if (-1 == InitializeStack(&binStack, 32))
    {
        return -1;
    }

    printf("%d to binary: ", n);

    do
    {
        PushStack(&binStack, (n & 0x1) + '0');
    } while (n >>= 1);

    while (-1 != GetStackTop(&binStack))
    {
        printf("%c", PopStack(&binStack));
    }

    CleanupStack(&binStack);

    return 0;
}

/*!
* @brief Reverse a simple text
*
* @param[in] x N/A
*
* @return 0
*/
int ReverseText (int x)
{
    t_stack binStack;

    if (-1 == InitializeStack(&binStack, 100))
    {
        return -1;
    }

    const char *inputText = "This is a beginning of a beautiful friendship.";
    printf("Input Text:    %s\n", inputText);
    printf("Reversed Text: ");

    while (*inputText)
    {
        PushStack(&binStack, (int)(*inputText));
        inputText++;
    }

    for (int i = binStack.top; i > -1; i--)
    {
        printf("%c", PopStack(&binStack));
    }

    CleanupStack(&binStack);

    return 0;
}

/*!
* @brief Bracket Checking Using Stack
*
* @param[in] x N/A
*
* @return 0
*/
int BracketCheck (int x)
{
    const char expression[] = "[2 * {(3 - 1) / (5 + 7)} - 4]";
    const char brackets[] = {'(', ')', '[', ']', '{', '}'};

    t_stack stack1;
    InitializeStack(&stack1, 20);

    int i;
    char *p_seek = expression;
    while (*p_seek)
    {
        if ( (i = SearchCharArray(brackets, *p_seek, NUM_OF(brackets))) > -1 )
        {
            if (i & 0x1)                                                // Odd number: closing bracket
            {
                if ( (int) brackets[i-1] == GetStackItem(&stack1) )     // Similar brackets are neighbors
                {
                    PopStack(&stack1);
                }
            }
            else                                                        // Even number: opening bracket
            {
                PushStack(&stack1, (int) (*p_seek));
            }
        }
        p_seek++;
    }

    printf("Expression %s -> %s", expression, (GetStackTop(&stack1) == -1) ? "is VALID.\n" : "is INVALID.\n");

    return 0;
}

/*!
* @brief Infix to Postfix Converter
*
* @param[in] x N/A
*
* @return 0
*/
int InfixToPostfix (int x)
{
    const char infix[] = "2+(3+((5-4)*(8+4)))$(1+2)*3";
    char buffer[strlen(infix) + 1];
    char top;
    t_stack operatorStack;
    bool moveHead;

    buffer[0] = '\0';
    InitializeStack(&operatorStack, 20);

    int i = 0;
    while (infix[i])
    {
        moveHead = true;
        if (IsOperator(infix[i]))
        {
            if (-1 == GetStackTop(&operatorStack))
            {
                PushStack(&operatorStack, (int) infix[i]);
            }
            else
            {
                top = (char) PopStack(&operatorStack);
                switch (PrecedenceChecker(top, infix[i]))
                {
                    case 0: // No precedence
                        PushStack(&operatorStack, top);
                        PushStack(&operatorStack, infix[i]);
                        break;
                    case 1: // The top of the stack has higher precedence
                        strncat(buffer, &top, 1);
                        moveHead = false;
                        break;
                    break;
                    default:   // Discard: "()" is detected
                        break;
                }
            }
        }
        else
        {
            strncat(buffer, &infix[i], 1);
        }

        if (moveHead)
        {
            i++;
        }
    }

    // Obtain final elements from the stack
    while (!StackIsEmpty(&operatorStack))
    {
        top = (char) PopStack(&operatorStack);
        strncat(buffer, &top, 1);
    }
    strncat(buffer, "\0", 1);

    printf("Infix: %s\nPostfix: %s = %d\n", infix, buffer, PostfixCalc(buffer));

    CleanupStack(&operatorStack);

    return 0;
}

/*** EOF ***/
