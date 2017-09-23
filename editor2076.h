// Krishna Dwypayan Kota
// 20172076


#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <ctype.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>

//...............................................................................................................................................................

//STRUCTURE DEFINING TERMINAL CONFIGURATIONS
struct terminalConfig{
	struct termios initial_setting;
	int terminal_rows;
	int terminal_cols;
}config;


//...............................................................................................................................................................

//CURSOR COORDINATES FOR INSERT MODE AND NORMAL MODE
struct cursor{
	int cursor_x, cursor_y ;	
}curse;


struct normal_cursor{
	int norm_x, norm_y;
}norm_curse;

//...............................................................................................................................................................
//ROWS POINTERS
struct node* rows[ 200 ];
int row_no;
int row_init;
int row_last;

//...............................................................................................................................................................
//WINDOW BUFFER
void print_window_buffer( int , int );

// MAIN FILE
void printerror( const char* );
void normalModeStart( int , char** );
void normalModeEnd( void );


//...............................................................................................................................................................
//NORMAL MODE
void drawTildes( void );
char* printCoordinates( int , int );
char* append( int , int );
char* append_cursor( int , int );	//APPEND FOR CURSOR SHOW
int getWindowSize( int*, int* );
void signal_handling_sigwinch( int );
void screenClear_NormalMode( void );
void initNewTerminal( int , char** );
void NormalToInsertMode( struct termios , struct termios , int , char** );


//...............................................................................................................................................................
//INSERT MODE
char readKeyInsertMode( int , char** );


//void signal_handling_sigwinch( void );


//...............................................................................................................................................................

//COMMAND MODE

int commandParse( struct termios );
char commandModeStart( struct termios , int , char**);

//...............................................................................................................................................................
//DOUBLY LINKED LIST FILE
struct node
{
	char data;
	struct node* prev;
	struct node* next;
};
struct node* Insert_in_LL( struct node* , char );
struct node* Insert_at_posX( struct node* , char , int );
struct node* deleteAtPosX( struct node* , int );
void printCharLL( struct node* );
void shift_LL( int , int );

//...............................................................................................................................................................
//ARRAY FOR LL
void make_new_row( int , char* , int );