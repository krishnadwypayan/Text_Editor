// Krishna Dwypayan Kota
// 20172076


#include "editor2076.h"


//READ INPUT IN INSERT MODE
char readKeyInsertMode( int argc , char* argv[ ])
{
	int readKey;
	char ch = ' ';

	struct winsize ws;
	ioctl( STDOUT_FILENO , TIOCGWINSZ , &ws );

            int row_num = curse.cursor_x;
            int col_num = curse.cursor_y;
            col_num = curse.cursor_y;
            row_num = curse.cursor_x;

//OPENING THE FILE HERE
            if( argc > 1 )
            {
                        FILE* file = fopen( argv[ 1 ] , "a");
                        //row = NULL;
                        if( file == 0 )
                        {
                                    printerror( "No such file exists " );
                                    exit(0);
                        }
                        else
                        {
                                    while( 1 )
                                    {   
                                                
                                    	readKey = read(STDIN_FILENO, &ch, 1);
                                    	
                                        	if(readKey == -1 && errno != EAGAIN) 
                                        	{
                                       		printerror("ERROR IN READING");
                                        	}	
                                        	if( ch == 27 )
                                        		return ch;
                                        	//ENTER KEY PRESSED
                                        	if( ch == 13 )
                                        	{
                                    		if( curse.cursor_x != ws.ws_row )
                                    		{
                                    			curse.cursor_x++;
                                    			curse.cursor_y = 1;
                                                                        row_num = curse.cursor_x ;

                                                                        //INSERTION INTO THE LINKED LIST
                                                                        rows[ row_num ] = Insert_in_LL(rows[ row_num ] , '\n');

                                                                        //SYSTEM DISPLAY 
                                                                        screenClear_NormalMode();
						append( config.terminal_rows - 2,  3 );
						write( STDOUT_FILENO , "INSERT" , 6);
						append( 1 , 1 );
						print_window_buffer( row_init , row_last );
						norm_curse.norm_x = row_last;
						norm_curse.norm_y = 1;
						append( config.terminal_rows - 2 , config.terminal_cols - 10 );
						char* cursor_pos_g = printCoordinates( curse.cursor_x  , curse.cursor_y );
						write( STDOUT_FILENO , cursor_pos_g , 6 );
						append( curse.cursor_x , curse.cursor_y );

	                                                            // Insert_at_posX( rows[ row_num ] , '\r' , col_num );
	                                                            // Insert_at_posX( rows[ row_num ] , '\n' , col_num );
	                                                            //printCharLL( rows[ row_num ] );
	                                                            row_num++;
	                                                            fputc( '\n' , file );

                                    		}
                                    		else
                                        		{
                                        			curse.cursor_x = ws.ws_row;		
                                        		}


                                        		char* cursor_pos_enter = append( config.terminal_rows -2 , config.terminal_cols - 10 );
                                        		write( STDOUT_FILENO , cursor_pos_enter , strlen( cursor_pos_enter ) );
                                        		write( STDOUT_FILENO , "\x1b[K" , 3 );
                                                            append( config.terminal_rows -2 , config.terminal_cols - 10 );
                                        		char* coordinates_enter = printCoordinates( curse.cursor_x , curse.cursor_y );

                                        		write( STDOUT_FILENO , coordinates_enter , strlen( coordinates_enter ) );
                                        		append( curse.cursor_x , curse.cursor_y );
                                        	}
                                        	//ESCAPE KEY
                                                if( ch == 127 )
                                                {
                                                            write( STDOUT_FILENO , "\b", 1 );
                                                            //write( STDOUT_FILENO , " " , 1 );
                                                            rows[ row_init + row_num - 1 ] = deleteAtPosX( rows[ row_init + row_num - 1 ] , norm_curse.norm_y ) ;
                                                            if( norm_curse.norm_y != 1)
                                                            	norm_curse.norm_y--;
                                                            else
                                                            {
                                                            	if( norm_curse.norm_x != 1)
                                                            	{
                                                            		norm_curse.norm_x --;
                                                            	}
                                                            	else
                                                            	{
                                                            		norm_curse.norm_x = 1;
                                                             	}
                                                            }

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
					
					append( norm_curse.norm_x , norm_curse.norm_y );
					//append( 1 , 1 );

                                                }
                                                //INSERT THE CHAR INSIDE THE LINKED LIST
                                        	else
                                        	{           
                                        		if( rows[ row_init + row_num - 1 ] == NULL )
                                        		{
                                        			rows[ row_init + row_num - 1 ] = Insert_in_LL( rows[ row_init + row_num - 1 ] , ch );	
                                        		}
                                                            else
                                                            	rows[ row_init + row_num - 1 ] = Insert_at_posX( rows[ row_init + row_num - 1 ] , ch , norm_curse.norm_y );

                                                            for( int i = 1; i <= config.terminal_rows - 4; i++)
				            {
				            	append( i ,  1 );
				            	write( STDOUT_FILENO, "\x1b[K", 3 );
				            }


                                                            if( norm_curse.norm_y == config.terminal_cols )
                                                            {
                                                                        write( STDOUT_FILENO , "\n\r" , 2 );
                                                            }
                                        		append( norm_curse.norm_x , norm_curse.norm_y );
                                        		write( STDOUT_FILENO, &ch, 1);
                                                            
                                        		if( norm_curse.norm_y != ws.ws_col )
                                        		{
                                                                        norm_curse.norm_y++;
                                        		}
                                                            else
                                        		{
                                        			norm_curse.norm_y = 1;
                                        			if( norm_curse.norm_x != ws.ws_row )
                                        				norm_curse.norm_x++;
                                        		}

					append( config.terminal_rows - 2,  3 );
					write( STDOUT_FILENO , "INSERT" , 6);
					append( 1 , 1 );
					print_window_buffer( row_init , row_last );
					// norm_curse.norm_x = row_last;
					// norm_curse.norm_y = 1;
					append( config.terminal_rows - 2 , config.terminal_cols - 10 );
					char* cursor_pos_g = printCoordinates( norm_curse.norm_x, norm_curse.norm_y );
					write( STDOUT_FILENO , cursor_pos_g , 6 );
					append( norm_curse.norm_x , norm_curse.norm_y );
                                        	}

                                    }
                        }
                        fclose( file );
            }

 	return ch;
}
