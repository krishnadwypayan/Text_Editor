// Krishna Dwypayan Kota
// 20172076



#include "editor2076.h"

//PRINT ERROR MESSAGE FOR WRONG INPUTS
void printerror( const char* error)
{
	perror( error );
	exit (1);
}


//END RAW MODE
void normalModeEnd()
{
	int val = tcsetattr(STDIN_FILENO , TCSAFLUSH , &config.initial_setting);
	if( val == -1)
		printerror( "tcsetattr : normal mode se exit karne mein dik'kat" );
	system("clear");
}


//START RAW / NORMAL MODE
void normalModeStart( int argc , char* argv[ ] )
{

	int val = tcgetattr( STDIN_FILENO, &config.initial_setting );

	if(val == -1)
		printerror( "tcgetattr : normal mode shuru hone mein dikkat" );

	atexit( normalModeEnd );
	
	//Flags settings
	struct termios current_setting = config.initial_setting;

	current_setting.c_lflag &= ~( ECHO | ICANON  | ISIG | IEXTEN);
	current_setting.c_iflag &= ~( BRKINT | ICRNL | INPCK | ISTRIP | IXON );
	current_setting.c_oflag &= ~(OPOST );
	current_setting.c_cflag |= ( CS8 );


	val = tcsetattr ( STDIN_FILENO, TCSAFLUSH, &current_setting);
	if( val == -1)
		printerror ( "tcsetattr : normal mode se setting restore karne mein dikkat" );

	screenClear_NormalMode();
	initNewTerminal( argc , argv );

	while( 1 )
	{
		//current_setting.c_lflag &= ~( ECHO );
		struct termios setting_forInsertMode = config.initial_setting;
		setting_forInsertMode.c_lflag |= ( ECHO | ICANON );
		// setting_forInsertMode.c_iflag |= ( ICRNL );
		// setting_forInsertMode.c_oflag |= (OPOST);
		NormalToInsertMode( current_setting , setting_forInsertMode , argc , argv );
	}
}



int main( int argc , char* argv[ ] )
{

	signal( SIGWINCH , signal_handling_sigwinch);
	
	system( "tput smcup" );
	
	if( argc != 2 )
	{
		printf("File name%s\n", argv[ 1 ] );
		fflush( stdout );
	}


	curse.cursor_x = 1;
	curse.cursor_y = 1;

	norm_curse.norm_x = curse.cursor_x;
	norm_curse.norm_y = curse.cursor_y;

	normalModeStart( argc , argv );
	
	system( "tput rmcup" );

	return 0;
}