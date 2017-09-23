// Krishna Dwypayan Kota
// 20172076


#include "editor2076.h"


//PUSH BACK IN LL
struct node* Insert_in_LL( struct node* row , char data )
{
	//struct node* head = NULL;
	struct node* new_node = (struct node *) malloc(sizeof( struct node ));

	new_node -> data = data;
	new_node -> prev = NULL;
	new_node -> next = NULL;

	if( row == NULL)
	{
		row = new_node;
		//*row -> next = head;
	}
	else
	{
		struct node* temp = row;
		//int count = 0;
		while( temp -> next != NULL )
		{
			temp = temp -> next;
			//count ++ ;
		}

		new_node -> next = temp -> next;
		new_node -> prev = temp;
		temp -> next = new_node;
		//new_node -> next -> prev = new_node;
	}
	return row;
}

//INSERT AT POSITION X
struct node* Insert_at_posX( struct node* row , char data , int x )
{
	//struct node* head = NULL;
	struct node* new_node = (struct node *) malloc(sizeof( struct node ));

	new_node -> data = data;
	new_node -> prev = NULL;
	new_node -> next = NULL;

	int count = x;

	if( row == NULL)
	{
		row = new_node;
		//*row -> next = head;
	}
	else
	{
		struct node* temp = row;
		//int count = 0;
		if( temp -> data =='\n' )
		{
			new_node -> next = row;
			row = new_node;
		}
		else
		{	while( count-- )
			{
				temp = temp -> next;
				//count ++ ;
			}

			new_node -> next = temp -> next;
			new_node -> prev = temp;
			temp -> next = new_node;
			new_node -> next -> prev = new_node;
		//norm_curse.norm_x ++;
		}
	}
	return row;
}


struct node* deleteAtPosX( struct node* head , int x )
{
	struct node* temp = head;

	int count = 0;

	while( count < x )
	{
		temp = temp -> next;
		count ++ ;
	}
	if( temp -> next != NULL )
	{
		temp -> prev -> next = temp -> next;
		temp -> next -> prev = temp -> prev;
		temp -> next = temp -> prev = NULL;
	}

	return head;
}

void shift_LL( int row_start , int row_end )
{
	struct node* row_temp[ row_end - row_start ];

	int k = row_start - 1;
	for(int i = row_start; i <= row_end ; i++ )
	{
		row_temp[ i ] = rows[ k ];
		k++;
	}

	for( k = row_start; k <= row_end ; k++)
	{
		rows[ k ] = row_temp[ k ];
	}
	rows[ row_start - 1 ] = Insert_in_LL( rows[ row_start - 1 ] , '\n');

}


void printCharLL( struct node* head )
{
	char c;
	struct node* temp = head;

	//write( STDOUT_FILENO , " write se pehle..." , 18 );
	while( temp  != NULL )
	{
		c = temp -> data;
		temp = temp -> next;
		if( c != '\n')
			curse.cursor_y++;
		write( STDOUT_FILENO , &c , 1 );
	}
	//write( STDOUT_FILENO , " write ke baad..." , 17 );
}
