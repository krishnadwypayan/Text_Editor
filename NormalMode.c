// Krishna Dwypayan Kota
// 20172076


#include "editor2076.h"

	struct winsize ws;
	//struct node* row;

//PRINT COORDINATES INSIDE THE STATUS BAR
char* printCoordinates( int x, int y)
{
	char* r = (char*) malloc( 3 );
	char* cl = (char*) malloc( 3 );

	sprintf( r , "%d" , x );
	sprintf( cl , "%d" , y );

	char* coordinates = malloc( strlen( r ) + strlen( cl ) );
	strcat( coordinates , r );
	char* colon = ":";
	strcat( coordinates , colon );
	strcat( coordinates , cl );

	return coordinates;
}

//MAKING ESCAPE SEQUENCES FOR THE CURSOR MOVEMENT
char* append( int rows , int cols)
{
	//   \x1b[97B
	char *s = "\x1b[";

	char* ans = (char*) malloc( 20 );
	sprintf( ans , "%d" , rows );

	char* colChar = (char*)malloc( 20 );
	sprintf( colChar , "%d" , cols );

	//write(STDOUT_FILENO , ans , strlen( ans ));

	//printf("%s\n", ans );

	char* B = "H";
	
	char* semiColon = ";";

	char *name_with_extention = malloc( strlen( s )+1+strlen( ans ) + strlen( B ) + strlen( colChar) + strlen( semiColon ) );
	strcpy( name_with_extention , s );

	strcat( name_with_extention , ans);
	strcat( name_with_extention , semiColon );
	strcat( name_with_extention , colChar );
	strcat( name_with_extention , B );
	//printf("%s\n", name_with_extention );
	write(STDOUT_FILENO , name_with_extention , strlen( name_with_extention ));

	return name_with_extention;

}



//APPEND FOR CURSOR SHOW
char* append_cursor( int rows , int cols)
{
	//   \x1b[97B
	char *s = "\033[";

	char* ans = (char*) malloc( 20 );
	sprintf( ans , "%d" , rows );

	char* colChar = (char*)malloc( 20 );
	sprintf( colChar , "%d" , cols );

	//write(STDOUT_FILENO , ans , strlen( ans ));

	//printf("%s\n", ans );

	char* B = "f";
	
	char* semiColon = ";";

	char *name_with_extention = malloc( strlen( s )+1+strlen( ans ) + strlen( B ) + strlen( colChar) + strlen( semiColon ) );
	strcpy( name_with_extention , s );

	strcat( name_with_extention , ans);
	strcat( name_with_extention , semiColon );
	strcat( name_with_extention , colChar );
	strcat( name_with_extention , B );
	

	printf("%s\n", name_with_extention );
	//write(STDOUT_FILENO , name_with_extention , strlen( name_with_extention ));

	return name_with_extention;

}




//GET WINDOW SIZE USING TIOGWINSZ
int getWindowSize( int* rows, int* cols )
{
	int val = ioctl(STDOUT_FILENO , TIOCGWINSZ , &ws);

	if(val != -1 || ws.ws_col != 0)
	{
		*cols = ws.ws_col;
		*rows = ws.ws_row;

		return 0;
	}
	else
		return -1;
}



//SIGNAL HANDLING WINCH
void signal_handling_sigwinch( int sig )
{
	//write(STDOUT_FILENO, "\x1b[2J", 4);

            append( config.terminal_rows - 2,  1 );
	//write( STDOUT_FILENO , &a , strlen( a ));
            write( STDOUT_FILENO, "\x1b[2K", 3 );

            getWindowSize( &config.terminal_rows , &config.terminal_cols );
            
	//write( STDOUT_FILENO , &a , strlen( a ));
            
            for( int i = 1; i <= config.terminal_rows - 4; i++)
            {
            	append( i ,  1 );
            	write( STDOUT_FILENO, "\x1b[K", 3 );
            }


            

            append( 1 , 1 );
            print_window_buffer( row_init , row_last );
	//write( STDOUT_FILENO , "NORMAL" , 6);

            append( config.terminal_rows - 2 , 11 );
            write( STDOUT_FILENO, "\x1b[K", 3 );
            //append( config.terminal_rows - 2 , config.terminal_cols - 10 );
	char* cursor_pos1 = printCoordinates( norm_curse.norm_x  , norm_curse.norm_y );
	
	//append( config.terminal_rows - 2,  1 );
	//write( STDOUT_FILENO, "\x1b[K", 3 );

	append( config.terminal_rows -2 , config.terminal_cols - 10 );
    	write( STDOUT_FILENO , cursor_pos1 , strlen( cursor_pos1 ) );
	
	append_cursor( norm_curse.norm_x, norm_curse.norm_y );
}


//CLEAR SCREEN IN NORMAL MODE
void screenClear_NormalMode() {
	write(STDOUT_FILENO, "\x1b[2J", 4);
}



//MAIN FUNCTION CALL TO IMPORT THE FILE ON THE NEW TERMINAL AFTER CALLING NORMAL MODE
void initNewTerminal( int argc , char* argv[ ] )
{
	int val = getWindowSize( &config.terminal_rows , &config.terminal_cols );

	row_init = 1;
	row_last = config.terminal_rows - 4;

	if( val == -1)
		printerror( "Window size nahi le paaye " );

	//drawTildes();
	for( int r = 0; r < 200 ; r++)
		rows [ r ] = NULL;

	write(STDOUT_FILENO, "\x1b[H", 3);
	if( argc > 1 )
	{
		FILE* file = fopen( argv[ 1 ] , "r");
		//row = NULL;
		if( file == 0 )
		{
			printerror( "No such file exists " );
		}
		else
		{
			int count = 0;
			char str[ config.terminal_cols];
			//str[ config.terminal_cols - 1] = '\n';
			row_no = 0;
			row_init = 0;
			while( 1 )
			{	
				//c = fgetc (file);
				fgets( str , config.terminal_cols , file );
				count = strlen( str );

				if( feof( file ) )
					break; 	
				int i = 0;
				while( str[ i ] != '\n' && i <= count )
				{
					rows[ row_no ] = Insert_in_LL( rows[ row_no ] , str[ i ] );
					i++;
				}
				rows[ row_no ] = Insert_in_LL( rows[ row_no ] , '\r' );
		 		rows[ row_no ] = Insert_in_LL( rows[ row_no ] , '\n' );
				row_no++;
			}
			print_window_buffer( row_init , config.terminal_rows - 4 );
			append_cursor( norm_curse.norm_x , norm_curse.norm_y );	
		}
		fclose( file );
	}


	
}


//edit mode + exit terminal
void NormalToInsertMode( struct termios current_setting , struct termios new_setting , int argc , char* argv[ ] )
{
	int reading;
	char input , output;
	//char up[ ]="\033[A", down[ ]="\033[B", right[ ]="\033[C", left[ ]="\033[D";
	int column_number = 3;
	append( config.terminal_rows - 2,  column_number );
	//write( STDOUT_FILENO , &a , strlen( a ));
	write( STDOUT_FILENO , "NORMAL" , 6);
	append( norm_curse.norm_x , norm_curse.norm_y );

	reading = read( STDIN_FILENO , &input , 1);

	ioctl(STDOUT_FILENO , TIOCGWINSZ , &ws);

	int g;
	char gt;

	if( reading == -1)
		printerror( "Wrong input" );
	else if( reading == 0 )
	{
		output = ' ';
		write( STDOUT_FILENO , &output , 1);
	}
	else
	{
		// if( input == 'q' )
		// 	exit( 0 );

		switch( input )
		{
			case 'k' :
				if( norm_curse.norm_x >= 2)
				{
				 	norm_curse.norm_x --;
				 // 	printf("%d  %d\n", row_init, row_last );
					// fflush(stdout);
				}
				else if( norm_curse.norm_x == 1 &&  row_init >= 1 )
			 	{
			 		row_init--;
			 		row_last--;
			 		screenClear_NormalMode();
			 		//write( STDOUT_FILENO , "hello" , 5);
			 		//write( STDOUT_FILENO , "\x1b[2J" , 3 );
			 		append( config.terminal_rows - 2,  3 );
					write( STDOUT_FILENO , "NORMAL" , 6);

					// printf("%d  %d\n", row_init, row_last );
					// fflush(stdout);
					append( 1 , 1 );
			 		print_window_buffer( row_init , row_last  );
			 		append( 1 , norm_curse.norm_y );
			 	}		
				else
					norm_curse.norm_x = 1;

				
				append_cursor( norm_curse.norm_x , norm_curse.norm_y );
				append( config.terminal_rows -2 , config.terminal_cols - 10 );

				write( STDOUT_FILENO , "\x1b[K" , 3 );
    				//write( STDOUT_FILENO , append2 , strlen( append2 ) );
				append( config.terminal_rows -2 , config.terminal_cols - 10 );
    				char* cursor_pos1 = printCoordinates( norm_curse.norm_x  , norm_curse.norm_y );
    				write( STDOUT_FILENO , cursor_pos1 , strlen( cursor_pos1 ) );
				
				append_cursor( norm_curse.norm_x  , norm_curse.norm_y );

				//write(STDOUT_FILENO, "\033[A", 3);  /* write 3 bytes from string */
            			
            			break;

		            case 'j':
			            //write(STDOUT_FILENO, down, 3);  /* write 3 bytes from string */

		            	
		            	if( norm_curse.norm_x < config.terminal_rows - 3 )
		            		if(norm_curse.norm_x <= curse.cursor_x )
		            		{
		            			if( norm_curse.norm_x == config.terminal_rows - 4 &&  row_last <= row_no )
				 		{
				 			row_init++;
				 			row_last++;
				 			screenClear_NormalMode();
				 			append( 1, 1 );
				 			print_window_buffer( row_init , row_last );	
				 			append( config.terminal_rows - 3, norm_curse.norm_y);
				 		}
				 		norm_curse.norm_x++;
				 		// if( norm_curse.norm_x == config.terminal_rows - 2 )
				 		// 	append( config.terminal_rows - 3 , norm_curse.norm_y );
				 		//printf("%d  %d\n", row_init, row_last );
						//fflush(stdout);
		            		}
		            		else
		            			norm_curse.norm_x = curse.cursor_x;
		            	else
		            		norm_curse.norm_x = config.terminal_rows - 4;
		            	append_cursor( norm_curse.norm_x , norm_curse.norm_y );
				append( config.terminal_rows -2 , 11 );
				//append( config.terminal_rows -2 , config.terminal_cols - 10 );
				write( STDOUT_FILENO , "\x1b[K" , 3 );
				//write( STDOUT_FILENO , append1 , strlen( append1 ) );
				append( config.terminal_rows -2 , config.terminal_cols - 10 );
				char* cursor_pos2 = printCoordinates( norm_curse.norm_x  , norm_curse.norm_y );
    				write( STDOUT_FILENO , cursor_pos2 , strlen( cursor_pos2) );
				

				append_cursor( norm_curse.norm_x  , norm_curse.norm_y );
            	            	

			            break;

		            case 'h':
			            //write(STDOUT_FILENO, left, 3);  /* write 3 bytes from string */

		            	if( norm_curse.norm_y != 1)
		            		if( norm_curse.norm_y > 1 )
		            			norm_curse.norm_y--;
		            		else
		            			norm_curse.norm_y = 1 ;
		            	else
		            		norm_curse.norm_y = 1;
			            
		            	append_cursor(norm_curse.norm_x  , norm_curse.norm_y);

			            append( config.terminal_rows -2 , config.terminal_cols - 10 );
			            write( STDOUT_FILENO , "\x1b[K" , 3 );
			            //write( STDOUT_FILENO , append3 , strlen( append3 ) );
			            append( config.terminal_rows -2 , config.terminal_cols - 10 );
			            char* cursor_pos3 = printCoordinates( norm_curse.norm_x  , norm_curse.norm_y );
    				write( STDOUT_FILENO , cursor_pos3 , strlen( cursor_pos3) );
				
				append_cursor( norm_curse.norm_x  , norm_curse.norm_y );

			            break;

		            case 'l' :
		             	//write(STDOUT_FILENO, right, 3);  /* write 3 bytes from string *

		            	if( norm_curse.norm_y != ws.ws_col )
		            		if( norm_curse.norm_y < curse.cursor_y )
		            			norm_curse.norm_y++;
		            		else
		            			norm_curse.norm_y = curse.cursor_y;
		            	else
		            		norm_curse.norm_y = ws.ws_col;

		            	//printf("%s", move_l);
		             	
		             	//write( STDOUT_FILENO , move_l , 3);
		            	append_cursor (norm_curse.norm_x  , norm_curse.norm_y);
		             	append( config.terminal_rows -2 , 11 );
		             	write( STDOUT_FILENO , "\x1b[K" , 3 );
		             	append( config.terminal_rows -2 , config.terminal_cols - 10 );
		             	char* cursor_pos4 = printCoordinates( norm_curse.norm_x  , norm_curse.norm_y );
    				write( STDOUT_FILENO , cursor_pos4 , strlen( cursor_pos4 ) );
				append_cursor( norm_curse.norm_x  , norm_curse.norm_y );
		             	break;

	             	case 'i':
				//printf("--INSERT--\n");
				tcgetattr( STDIN_FILENO, &new_setting );
				//struct termios setting_forInsertMode = config.initial_setting;
				//setting_forInsertMode.c_lflag &= ~( ECHO );
				//printf("Insert mode banaya abhi...\n");
				
				append( config.terminal_rows - 2, column_number );
				//write( STDOUT_FILENO , &a , strlen( a ));
				write( STDOUT_FILENO , "INSERT" , 6);
				//write( STDOUT_FILENO , "\x1b[H" , 3);
				curse.cursor_x = norm_curse.norm_x ;
				curse.cursor_y = norm_curse.norm_y ;
				append( curse.cursor_x , curse.cursor_y );

				while( 1 )
				{
					//int cursor = getCursorPosition( &config.terminal_rows , &config.terminal_cols );
					char ch = readKeyInsertMode( argc , argv );
					if( ch == 27 )
					{
						tcsetattr ( STDIN_FILENO, TCSAFLUSH, &current_setting);
						append( curse.cursor_x , curse.cursor_y );
						break;
					}
					else
						continue;
				}
				NormalToInsertMode( new_setting , current_setting , argc , argv );
				break;

			case ':':
				tcgetattr( STDIN_FILENO, &current_setting );
				append( config.terminal_rows - 2, column_number );
				//write( STDOUT_FILENO , &a , strlen( a ));
				write( STDOUT_FILENO , "COMMAND" , 7);
				append( config.terminal_rows - 1, 1);
				write( STDOUT_FILENO , ":" , 1);
				//int cursor = getCursorPosition( &config.terminal_rows , &config.terminal_cols );
				write( STDOUT_FILENO, "\x1b[s" , 3 );
				commandModeStart( current_setting , argc , argv );
				//tcsetattr ( STDIN_FILENO, TCSAFLUSH, &current_setting);
				write( STDOUT_FILENO , "\x1b[u" , 3 );
				tcsetattr( STDIN_FILENO , TCSAFLUSH , &current_setting );
				append( curse.cursor_x , curse.cursor_y );
				append( 1 , 1 );
				print_window_buffer( row_init , row_last );
				append( norm_curse.norm_x , norm_curse.norm_y );
				NormalToInsertMode( new_setting , current_setting , argc , argv );
				break;


			case 'g':
				g = read( STDIN_FILENO , &gt , 1 );
				if( gt == 'g' )
				{
					row_init = 0;
					row_last = config.terminal_rows - 4;
					screenClear_NormalMode();
					append( config.terminal_rows - 2,  3 );
					write( STDOUT_FILENO , "NORMAL" , 6);
					append( 1 , 1 );
					print_window_buffer( row_init , row_last );
					norm_curse.norm_x = 1;
					norm_curse.norm_y = 1;
					append( config.terminal_rows - 2 , config.terminal_cols - 10 );
					char* cursor_pos_g = printCoordinates( norm_curse.norm_x  , norm_curse.norm_y );
					write( STDOUT_FILENO , cursor_pos_g , 6 );
					append( norm_curse.norm_x , norm_curse.norm_y );
				}
				break;
			
			case 'G':
				row_last = row_no;
				row_init = row_last - config.terminal_rows - 4;
				screenClear_NormalMode();
				append( config.terminal_rows - 2,  3 );
				write( STDOUT_FILENO , "NORMAL" , 6);
				append( 1 , 1 );
				print_window_buffer( row_init , row_last );
				norm_curse.norm_x = row_last;
				norm_curse.norm_y = 1;
				append( config.terminal_rows - 2 , config.terminal_cols - 10 );
				char* cursor_pos_g = printCoordinates( norm_curse.norm_x  , norm_curse.norm_y );
				write( STDOUT_FILENO , cursor_pos_g , 6 );
				append( norm_curse.norm_x , norm_curse.norm_y );
				break;

		            // case '^[[A' :
		            // 	write(STDOUT_FILENO, up, 3);  /* write 3 bytes from string */


			case 'r':
				g = read( STDIN_FILENO , &gt , 1 );
				char space = ' ';
				write( STDOUT_FILENO , &space , 1 );
				rows[ row_init + norm_curse.norm_x - 1 ] = Insert_at_posX( rows[ row_init + norm_curse.norm_x - 1] , gt , norm_curse.norm_y - 1);
				write( STDOUT_FILENO , &gt , 1 );

				//print_window_buffer( row_init , row_last );

				for( int i = 1; i <= config.terminal_rows - 4; i++)
			            {
			            	append( i ,  1 );
			            	write( STDOUT_FILENO, "\x1b[K", 3 );
			            }

			            append( 1 , 1 );
			            print_window_buffer( row_init , row_last );
				//write( STDOUT_FILENO , "NORMAL" , 6);

			            append( config.terminal_rows - 2 , 11 );
			            write( STDOUT_FILENO, "\x1b[K", 3 );
			            //append( config.terminal_rows - 2 , config.terminal_cols - 10 );
				char* cursor_pos_x = printCoordinates( norm_curse.norm_x  , norm_curse.norm_y );
				
				//append( config.terminal_rows - 2,  1 );
				//write( STDOUT_FILENO, "\x1b[K", 3 );

				append( config.terminal_rows -2 , config.terminal_cols - 10 );
			    	write( STDOUT_FILENO , cursor_pos_x , strlen( cursor_pos_x ) );
				
				append_cursor( norm_curse.norm_x, norm_curse.norm_y );

            			break;
		}
	}
}
