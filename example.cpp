/****************************************************************
**	OrangeBot Project
*****************************************************************
**        /
**       /
**      /
** ______ \
**         \
**          \
*****************************************************************
**	Project
*****************************************************************
**  Brief
****************************************************************/

/****************************************************************
**	DESCRIPTION
****************************************************************
**
****************************************************************/

/****************************************************************
**	HISTORY VERSION
****************************************************************
**
****************************************************************/

/****************************************************************
**	KNOWN BUGS
****************************************************************
**
****************************************************************/

/****************************************************************
**	TODO
****************************************************************
**
****************************************************************/

/****************************************************************
**	INCLUDES
****************************************************************/

//Standard C Libraries
//#include <cstdio>
//#include <cstdlib>

//Standard C++ libraries
#include <iostream>
//#include <array>
//#include <vector>
//#include <queue>
//#include <string>
//#include <fstream>
//#include <chrono>
//#include <thread>

//OS Libraries
//#define _WIN32_WINNT 0x0500	//Enable GetConsoleWindow
//#include <windows.h>

//User Libraries
//Include user log trace
#define ENABLE_DEBUG
#include "debug.h"
//Universal parser class
#include "uniparser.h"

/****************************************************************
**	NAMESPACES
****************************************************************/

//Never use a whole namespace. Use only what you need from it.
using std::cout;
using std::endl;

/****************************************************************
**	DEFINES
****************************************************************/

//#define TEST_SYNTAX

//#define TEST_ONECHAR
//#define TEST_ONECHAR_U8
//#define TEST_MULTICHAR

//#define TEST_LONG_ARG

//#define TEST_AFTER_ARG

//#define TEST_FOUR_ARGS

//#define TEST_FOUR_S8

//#define TEST_FOUR_S16

//#define TEST_FOUR_U16

#define TEST_ALL_FOUR

//#define TEST_TWO_S32

/****************************************************************
**	MACROS
****************************************************************/

/****************************************************************
**	PROTOTYPES
****************************************************************/

extern bool test_bench( void );

//Handler provided to a message with no arguments
extern void my_handler_noarg( void );
//Handler function that takes in input a U8
extern void my_handler_u8( uint8_t arg0 );
extern void my_handler_four_s8( int8_t a, int8_t b, int8_t c, int8_t d );
extern void my_handler_four_u8( uint8_t a, uint8_t b, uint8_t c, uint8_t d );
extern void my_handler_four_s16( int16_t a, int16_t b, int16_t c, int16_t d );
extern void my_handler_four_u16( uint16_t a, uint16_t b, uint16_t c, uint16_t d );
extern void my_handler_two_s32( int32_t a, int32_t b );

//Feed a string to the parser
extern void parser_executor( Orangebot::Uniparser &my_parser, uint8_t *ptr );

/****************************************************************
**	GLOBAL VARIABILES
****************************************************************/

//User::Dummy my_class;

/****************************************************************
**	FUNCTIONS
****************************************************************/

/****************************************************************************
**	Function
**	main |
****************************************************************************/
//! @return bool |
//! @brief dummy method to copy the code
//! @details verbose description
/***************************************************************************/

int main()
{
	//----------------------------------------------------------------
	//	STATIC VARIABILE
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//	LOCAL VARIABILE
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//	CHECK AND INITIALIZATIONS
	//----------------------------------------------------------------

	//Start Debugging. Show function nesting level 0 and above
	DSTART( 0 );
	//Trace Enter main
	DENTER();

	//----------------------------------------------------------------
	//	BODY
	//----------------------------------------------------------------

	cout << "OrangeBot Projects\n";
	//print in the 'debug.log' file. works just like a fully featured printf
	DPRINT("OrangeBot Projects\n");

	test_bench();

	//----------------------------------------------------------------
	//	FINALIZATIONS
	//----------------------------------------------------------------

	//Trace Return from main
	DRETURN();
	//Stop Debugging
	DSTOP();

    return 0;
}	//end function: main

/****************************************************************************
**	Function
**	test_bench | void
****************************************************************************/
//! @param f bool
//! @return bool |
//! @brief dummy method to copy the code
//! @details verbose description
/***************************************************************************/

bool test_bench( void )
{
	//Trace Enter with arguments
	DENTER();

	//----------------------------------------------------------------
	//	VARS
	//----------------------------------------------------------------

	//Create a new parser
	Orangebot::Uniparser my_parser;

	uint8_t *ptr = nullptr;

	//----------------------------------------------------------------
	//	INIT
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//	BODY
	//----------------------------------------------------------------
	//! @details algorithm:

	//Add a command to the parser. F\0 will automatically execute this handler when received
	my_parser.add_cmd( "P", (void *)&my_handler_noarg );
	my_parser.add_cmd( "A%uB%uC%uD%u\0", (void *)&my_handler_four_u8 );
	my_parser.add_cmd( "F", (void *)&my_handler_noarg );
	my_parser.add_cmd( "X%u", (void *)&my_handler_u8 );
	my_parser.add_cmd( "VEL%u", (void *)&my_handler_u8 );
	my_parser.add_cmd( "SA%sB%sC%sD%s\0", (void *)&my_handler_four_s8 );
	my_parser.add_cmd( "SSA%SB%SC%SD%S\0", (void *)&my_handler_four_s16 );
	my_parser.add_cmd( "VELX%uREI", (void *)&my_handler_u8 );
	my_parser.add_cmd( "XENOSCUM", (void *)&my_handler_noarg );
	my_parser.add_cmd( "UUA%UB%UC%UD%U\0", (void *)&my_handler_four_u16 );
	my_parser.add_cmd( "POS%dNEG%dSHAKA\0", (void *)&my_handler_two_s32 );

	//----------------------------------------------------------------
	//	TEST SYNTAX
	//----------------------------------------------------------------

    #ifdef TEST_SYNTAX

    //Bad handler function
    my_parser.add_cmd( "A", (void *)nullptr );
    printf("ERR: >%s<\n", my_parser.get_syntax_error());
    //Begins with a number
    my_parser.add_cmd( "1", (void *)&my_handler_noarg );
    printf("ERR: >%s<\n", my_parser.get_syntax_error());
    //bad descriptor type
    my_parser.add_cmd( "V%x", (void *)&my_handler_noarg );
    //two arguments back to back
	my_parser.add_cmd( "P%u%u", (void *)&my_handler_noarg );
	//arguments of different kind
	my_parser.add_cmd( "P%uR%U", (void *)&my_handler_noarg );
	//too many arguments
	my_parser.add_cmd( "uA%uB%uC%uD%uE%u", (void *)&my_handler_noarg );
	my_parser.add_cmd( "dA%dB%dC%d", (void *)&my_handler_noarg );


    #endif // TEST_SYNTAX

	//----------------------------------------------------------------
	//	TEST ONE CHAR COMMANDS
	//----------------------------------------------------------------

	#ifdef TEST_ONECHAR

	printf("---------------------------------------------------\n");
	//Good inputs
	ptr = (uint8_t *)"P\0";
	parser_executor( my_parser, ptr );
	ptr = (uint8_t *)"F\0";
	parser_executor( my_parser, ptr );
	//bad inputs
	ptr = (uint8_t *)"H\0";
	parser_executor( my_parser, ptr );

	#endif

	//----------------------------------------------------------------
	//	TEST ONE CHAR COMMANDS WITH U8 ARGUMENTS
	//----------------------------------------------------------------

	#ifdef TEST_ONECHAR_U8

	printf("---------------------------------------------------\n");
	//Bad inputs
	ptr = (uint8_t *)"X7T\0";
	parser_executor( my_parser, ptr );
	ptr = (uint8_t *)"VEL++255\0";
	parser_executor( my_parser, ptr );

	printf("---------------------------------------------------\n");
	//Good inputs
	ptr = (uint8_t *)"X7\0";
	parser_executor( my_parser, ptr );
	ptr = (uint8_t *)"VEL+255\0";
	parser_executor( my_parser, ptr );

	#endif

	//----------------------------------------------------------------
	//	TEST MULTICHAR COMMANDS
	//----------------------------------------------------------------

	#ifdef TEST_MULTICHAR

	//Bad inputs
	printf("---------------------------------------------------\n");
	ptr = (uint8_t *)"XENORCUM\0";
	parser_executor( my_parser, ptr );

	//Good inputs
	printf("---------------------------------------------------\n");
	ptr = (uint8_t *)"XENOSCUM\0";
	parser_executor( my_parser, ptr );


	#endif

	//----------------------------------------------------------------
	//	TEST LONG ARG
	//----------------------------------------------------------------

	#ifdef TEST_LONG_ARG
	{
		//Good input
		uint8_t *ptr = (uint8_t *)"X7\0X+255\0X+127\0";
		uint8_t t = 0;
		while ((t == 0) || ((t >= 1) && !((ptr[t] == '\0') && (ptr[t-1] == '\0'))))
		{
			my_parser.exe(ptr[t]);
			if ((ptr[t] < '0') || (ptr[t] > 'z'))
			{
				printf("feed: >0x%x<\n", ptr[t]);
			}
			else
			{
				printf("feed: >0x%x< >%c<\n", ptr[t], ptr[t]);
			}
			t++;
		}
		ptr = (uint8_t *)"X7R\0";
		t=0;
		while ((t == 0) || ((t >= 1) && !((ptr[t] == '\0') && (ptr[t-1] == '\0'))))
		{
			my_parser.exe(ptr[t]);
			if ((ptr[t] < '0') || (ptr[t] > 'z'))
			{
				printf("feed: >0x%x<\n", ptr[t]);
			}
			else
			{
				printf("feed: >0x%x< >%c<\n", ptr[t], ptr[t]);
			}
			t++;
		}
	}
	#endif // TEST_LONG_ARG

	//----------------------------------------------------------------
	//	TEST_AFTER_ARG
	//----------------------------------------------------------------
	//test a U8 command with text after argument iwth good and bad combinations
	#ifdef TEST_AFTER_ARG
	{
		//Good input
		uint8_t *ptr = (uint8_t *)"VELX+255\0VELX+255REIA\0VELX+255REI\0VELX+255R+2\0";
		uint8_t t = 0;
		while ((t == 0) || ((t >= 1) && !((ptr[t] == '\0') && (ptr[t-1] == '\0'))))
		{
			my_parser.exe(ptr[t]);
			if ((ptr[t] < '0') || (ptr[t] > 'z'))
			{
				printf("feed: >0x%x<\n", ptr[t]);
			}
			else
			{
				printf("feed: >0x%x< >%c<\n", ptr[t], ptr[t]);
			}
			t++;
		}
	}

	#endif

	//----------------------------------------------------------------
	//	TEST LONG ARG
	//----------------------------------------------------------------

	#ifdef TEST_FOUR_ARGS
	{
		//Good input
		uint8_t *ptr = (uint8_t *)"A+5B+200C0D+88\0";
		uint8_t t = 0;
		while ((t == 0) || ((t >= 1) && !((ptr[t] == '\0') && (ptr[t-1] == '\0'))))
		{
			my_parser.exe(ptr[t]);
			if ((ptr[t] < '0') || (ptr[t] > 'z'))
			{
				printf("feed: >0x%x<\n", ptr[t]);
			}
			else
			{
				printf("feed: >0x%x< >%c<\n", ptr[t], ptr[t]);
			}
			t++;
		}
	}

	#endif

	//----------------------------------------------------------------
	//	TEST 4 S8
	//----------------------------------------------------------------

	#ifdef TEST_FOUR_S8
	{
		//Good input
		uint8_t *ptr = (uint8_t *)"SA-5B+127C0D-128\0SA-5B+127C0D-128RA\0SA-5B+127C0DX\0SA-5B+127C0-128\0SA-5B+127C0D-128\0";
		uint8_t t = 0;
		while ((t == 0) || ((t >= 1) && !((ptr[t] == '\0') && (ptr[t-1] == '\0'))))
		{
			my_parser.exe(ptr[t]);
			if ((ptr[t] < '0') || (ptr[t] > 'z'))
			{
				printf("feed: >0x%x<\n", ptr[t]);
			}
			else
			{
				printf("feed: >0x%x< >%c<\n", ptr[t], ptr[t]);
			}
			t++;
		}
	}

	#endif

	//----------------------------------------------------------------
	//	TEST 4 S16
	//----------------------------------------------------------------

	#ifdef TEST_FOUR_S16
	{
		//Good input
		uint8_t *ptr = (uint8_t *)"SSA-32768B+32767C-0D-1\0SSA-32768B+32767C-0D\0SSA-32768B+32767C-0DR\0SSA-32768B+32767C-0D-1\0";
		uint8_t t = 0;
		while ((t == 0) || ((t >= 1) && !((ptr[t] == '\0') && (ptr[t-1] == '\0'))))
		{
			my_parser.exe(ptr[t]);
			if ((ptr[t] < '0') || (ptr[t] > 'z'))
			{
				printf("feed: >0x%x<\n", ptr[t]);
			}
			else
			{
				printf("feed: >0x%x< >%c<\n", ptr[t], ptr[t]);
			}
			t++;
		}
	}

	#endif

	//----------------------------------------------------------------
	//	TEST 4 U16
	//----------------------------------------------------------------

	#ifdef TEST_FOUR_U16
	{
		//Good input
		uint8_t *ptr = (uint8_t *)"XUUA+65535B65535C1D2\0XUA+65535B65535C1D2\0";
		uint8_t t = 0;
		while ((t == 0) || ((t >= 1) && !((ptr[t] == '\0') && (ptr[t-1] == '\0'))))
		{
			my_parser.exe(ptr[t]);
			if ((ptr[t] < '0') || (ptr[t] > 'z'))
			{
				printf("feed: >0x%x<\n", ptr[t]);
			}
			else
			{
				printf("feed: >0x%x< >%c<\n", ptr[t], ptr[t]);
			}
			t++;
		}
	}

	#endif

	//----------------------------------------------------------------
	//	TEST_TWO_S32
	//----------------------------------------------------------------

	#ifdef TEST_TWO_S32

	//@ test double sign

	//bad input
	printf("---------------------------------------------------\n");
	ptr = (uint8_t *)"POS-2147483648NEG++2147483647SHAKA\0";
	parser_executor( my_parser, ptr );
	//Good input
	printf("---------------------------------------------------\n");
	ptr = (uint8_t *)"POS-2147483648NEG+2147483647SHAKA\0";
	parser_executor( my_parser, ptr );

	#endif

	//----------------------------------------------------------------
	//	TEST_ALL_FOUR
	//----------------------------------------------------------------

	#ifdef TEST_ALL_FOUR

	printf("---------------------------------------------------\n");
	ptr = (uint8_t *)"SSA-32768B+32767C-0D-1\0";
	parser_executor( my_parser, ptr );
	ptr = (uint8_t *)"SA-5B+127C0D-128\0";
	parser_executor( my_parser, ptr );
	ptr = (uint8_t *)"A+5B+200C0D+88\0";
	parser_executor( my_parser, ptr );
	ptr = (uint8_t *)"POS+1NEG-1SHAKA\0";
	parser_executor( my_parser, ptr );

	#endif

	//----------------------------------------------------------------
	//	RETURN
	//----------------------------------------------------------------

	//Trace Return vith return value
	DRETURN_ARG("out: %d\n", 0);

	return true; //OK
}	//end function: Dummy | bool

/****************************************************************************
**	Function
**	my_handler_noarg | void
****************************************************************************/
//! @param f bool
//! @return bool |
//! @brief dummy method to copy the code
//! @details verbose description
/***************************************************************************/

void my_handler_noarg( void )
{
	//Trace Enter with arguments
	DENTER_ARG("in: %d\n", 0);

	//----------------------------------------------------------------
	//	VARS
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//	INIT
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//	BODY
	//----------------------------------------------------------------
	//! @details algorithm:

	printf("handler with no argument has been called\n");

	//----------------------------------------------------------------
	//	FINALIZATIONS
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//	RETURN
	//----------------------------------------------------------------

	//Trace Return vith return value
	DRETURN_ARG("out: %d\n", 0);
	return;
}	//end function: my_handler_noarg | void

//Handler function that takes in input a U8


/****************************************************************************
**	Function
**	my_handler_u8 | uint8_t
****************************************************************************/
//! @param f bool
//! @return bool |
//! @brief dummy method to copy the code
//! @details verbose description
/***************************************************************************/

void my_handler_u8( uint8_t arg0 )
{
	//Trace Enter with arguments
	DENTER_ARG("in: %d\n", arg0);

	//----------------------------------------------------------------
	//	VARS
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//	INIT
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//	BODY
	//----------------------------------------------------------------
	//! @details algorithm:

	printf("handler for U8 called with argument: %d\n", arg0);

	//----------------------------------------------------------------
	//	FINALIZATIONS
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//	RETURN
	//----------------------------------------------------------------

	//Trace Return vith return value
	DRETURN_ARG("out: %d\n", 0);
	return;
}	//end function: my_handler_u8 | uint8_t

/****************************************************************************
**	Function
**	my_handler_u8 | uint8_t, uint8_t, uint8_t, uint8_t,
****************************************************************************/
//! @param f bool
//! @return bool |
//! @brief dummy method to copy the code
//! @details verbose description
/***************************************************************************/

void my_handler_four_u8( uint8_t a, uint8_t b, uint8_t c, uint8_t d )
{
	//Trace Enter with arguments
	DENTER_ARG("in: %d %d %d %d\n", a, b,c ,d);

	//----------------------------------------------------------------
	//	VARS
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//	INIT
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//	BODY
	//----------------------------------------------------------------
	//! @details algorithm:

	printf("handler for U8 called with arguments: %d %d %d %d\n", a, b, c ,d);

	//----------------------------------------------------------------
	//	FINALIZATIONS
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//	RETURN
	//----------------------------------------------------------------

	//Trace Return vith return value
	DRETURN();
	return;
}	//end function: my_handler_u8_u8 | uint8_t, uint8_t,uint8_t, uint8_t

/****************************************************************************
**	Function
**	my_handler_s8 | int8_t, int8_t, int8_t, int8_t,
****************************************************************************/
//! @param f bool
//! @return bool |
//! @brief dummy method to copy the code
//! @details verbose description
/***************************************************************************/

void my_handler_four_s8( int8_t a, int8_t b, int8_t c, int8_t d )
{
	//Trace Enter with arguments
	DENTER_ARG("in: %d %d %d %d\n", a, b,c ,d);

	//----------------------------------------------------------------
	//	VARS
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//	INIT
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//	BODY
	//----------------------------------------------------------------
	//! @details algorithm:

	printf("handler for S8 called with arguments: %d %d %d %d\n", a, b, c ,d);

	//----------------------------------------------------------------
	//	FINALIZATIONS
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//	RETURN
	//----------------------------------------------------------------

	//Trace Return vith return value
	DRETURN();
	return;
}	//end function: my_handler_s8 | int8_t, int8_t, int8_t, int8_t,

/****************************************************************************
**	Function
**	my_handler_s16
****************************************************************************/
//! @param f bool
//! @return bool |
//! @brief dummy method to copy the code
//! @details verbose description
/***************************************************************************/

void my_handler_four_s16( int16_t a, int16_t b, int16_t c, int16_t d )
{
	//Trace Enter with arguments
	DENTER_ARG("in: %d %d %d %d\n", a, b,c ,d);

	//----------------------------------------------------------------
	//	VARS
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//	INIT
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//	BODY
	//----------------------------------------------------------------
	//! @details algorithm:

	printf("handler for S16 called with arguments: %d %d %d %d\n", a, b, c ,d);

	//----------------------------------------------------------------
	//	FINALIZATIONS
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//	RETURN
	//----------------------------------------------------------------

	//Trace Return vith return value
	DRETURN();
	return;
}	//end function: my_handler_s16

/****************************************************************************
**	Function
**	my_handler_u16
****************************************************************************/
//! @param f bool
//! @return bool |
//! @brief dummy method to copy the code
//! @details verbose description
/***************************************************************************/

void my_handler_four_u16( uint16_t a, uint16_t b, uint16_t c, uint16_t d )
{
	//Trace Enter with arguments
	DENTER_ARG("in: %d %d %d %d\n", a, b,c ,d);

	//----------------------------------------------------------------
	//	VARS
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//	INIT
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//	BODY
	//----------------------------------------------------------------
	//! @details algorithm:

	printf("handler for U16 called with arguments: %d %d %d %d\n", a, b, c ,d);

	//----------------------------------------------------------------
	//	FINALIZATIONS
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//	RETURN
	//----------------------------------------------------------------

	//Trace Return vith return value
	DRETURN();
	return;
}	//end function: my_handler_u16

/****************************************************************************
**	Function
**	my_handler_two_s32
****************************************************************************/
//! @param f bool
//! @return bool |
//! @brief dummy method to copy the code
//! @details verbose description
/***************************************************************************/

void my_handler_two_s32( int32_t a, int32_t b )
{
	//Trace Enter with arguments
	DENTER_ARG("in: %d %d\n", a, b );

	//----------------------------------------------------------------
	//	VARS
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//	INIT
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//	BODY
	//----------------------------------------------------------------
	//! @details algorithm:

	printf("handler for S32 called with arguments: %d %d\n", a, b);

	//----------------------------------------------------------------
	//	FINALIZATIONS
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//	RETURN
	//----------------------------------------------------------------

	//Trace Return vith return value
	DRETURN();
	return;
}	//end function: my_handler_two_s32

/****************************************************************************
**	Function
**	parser_executor | Orangebot::Uniparser &, uint8_t *
****************************************************************************/
//! @param parser |
//! @param str |
//! @brief dummy method to copy the code
//! @details Feed a string to the parser
/***************************************************************************/

void parser_executor( Orangebot::Uniparser &my_parser, uint8_t *ptr )
{
	//Trace Enter with arguments
	DENTER_ARG("in: %d\n", 0);

	//----------------------------------------------------------------
	//	VARS
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//	INIT
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//	BODY
	//----------------------------------------------------------------

	uint8_t t = 0;
	while ((t == 0) || ((t >= 1) && !((ptr[t] == '\0') && (ptr[t-1] == '\0'))))
	{
		my_parser.exe(ptr[t]);
		if ((ptr[t] < '0') || (ptr[t] > 'z'))
		{
			printf("feed: >0x%x<\n", ptr[t]);
		}
		else
		{
			printf("feed: >0x%x< >%c<\n", ptr[t], ptr[t]);
		}
		t++;

		if (t> 128)
		{
			printf("infinite loop detected. Maybe you forgot \\0 at end of string?\n");
			exit(0);
		}
	}

	//----------------------------------------------------------------
	//	RETURN
	//----------------------------------------------------------------

	//Trace Return vith return value
	DRETURN();

	return; //OK
}	//end function: Dummy | bool
