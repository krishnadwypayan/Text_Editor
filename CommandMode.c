// Krishna Dwypayan Kota
// 20172076


#include "editor2076.h"


int commandParse( struct termios current_setting )
{
	//char line[ 1024 ];
	
	char *li = (char*) malloc( 20* sizeof(char));
	char ins = ' ';
	int i = 0;

	do{
		read( STDIN_FILENO , &ins , 1 );
		write( STDOUT_FILENO , &ins , 1 );
		li[i] = ins;
		i = i+1;
	}while( ins != 13 );

	li[i-1] = '\0';
	
	normalModeEnd();
 //   	system( "tput rmcup" );

	// system( li );
	// read( STDIN_FILENO , &ins , 1 );
	//system( "tput smcup" );
	//tcgetattr ( STDIN_FILENO, &current_setting);

	int pid = 0;
	pid = fork();

	//CHILD PROCESS
	if( pid == 0 )
	{
		system( "tput rmcup" );	
		for( int i = 1; i <= config.terminal_rows; i++)
	            {
	            	append( i ,  1 );
	            	write( STDOUT_FILENO, "\x1b[K", 3 );
	            }

	            append( 1 , 1 );
		execl( "/bin/bash", "bash" , "-c" , li , (char*) NULL);
	}
	//PARENT PROCESS
	else
	{
		wait( &pid );
		read( STDIN_FILENO , &ins , 1 );
		system( "tput smcup" );
		for( int i = 1; i <= config.terminal_rows - 4; i++)
	            {
	            	append( i ,  1 );
	            	write( STDOUT_FILENO, "\x1b[K", 3 );
	            }
	            tcgetattr ( STDIN_FILENO, &current_setting);	
	            append( 1 , 1 );
	            print_window_buffer( row_init , row_last );
		
	}

	
	return 0;

}

char commandModeStart( struct termios current_setting , int argc , char* argv[ ] )
{
	int readKey;
	char ch;

	struct winsize ws;
	ioctl( STDOUT_FILENO , TIOCGWINSZ , &ws );

	readKey = read(STDIN_FILENO, &ch, 1);

    	if(readKey == -1 && errno != EAGAIN) 
	{
		printerror("read mein galti hui...");
	}	

	char q_next;
	int read_qnext;

	char* cursor_pos_enter;

	int fl;

	switch( ch )
	{
		case 'q':
			
			read_qnext = read(STDIN_FILENO, &q_next, 1);
			write( STDOUT_FILENO , "q" , 1);
			

			if( q_next == 13 )
			{
				//flag check after DS implementation
				cursor_pos_enter = append( config.terminal_rows -1 , 1);
				write( STDOUT_FILENO , "No write since last change (add ! to override)" , 56 );
				//return ch;
			}
			else if( q_next == '!')
			{
				write( STDOUT_FILENO , "!" , 1);
				exit( 1 );
			}

			break;

		case '!':
			write( STDOUT_FILENO , "!" , 1);
			fl = commandParse( current_setting );
			break;
		
		case 'w':
			//cursor_pos_enter = append( config.terminal_rows -1 , 1);
			write( STDOUT_FILENO , "w" , 1);
			read_qnext = read(STDIN_FILENO, &q_next, 1);
			if( q_next == 13 )
			{
				// if( argc > 1 )
			 //            {
			 //                        FILE* file = fopen( argv[ 1 ] , "a");
			 //                        //row = NULL;
			 //                        if( file == 0 )
			 //                        {
			 //                                    printerror( "No such file exists " );
			 //                        }
			 //                        else
			 //                        {
			                        	
			 //                        	int i = 0;
			 //                        	while( i <= row_no )
			 //                        	{
			 //                        		struct node* temp = rows[ row_no ];
			 //                        		while( temp != NULL )
			 //                        		{
			 //                        			fputc( temp -> data , file );
			 //                        		}
			 //                        	}
			 //                        }
			 //                        fclose( file );
			 //            }
			            // exit(1);

				//flag check after DS implementation
				// cursor_pos_enter = append( config.terminal_rows -1 , 1);
				// write( STDOUT_FILENO , "written" , 8 );
				//return ch;
			}
			else 
			{
				write( STDOUT_FILENO , "No such command" , 1);
			}			
			//write( STDOUT_FILENO , "DS PENDING" , 10 );
			break;
		
	}
	return ch;
}