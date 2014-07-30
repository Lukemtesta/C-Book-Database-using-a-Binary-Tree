
/* 

Luke Testa, 6119412.


Database3.c Initializes the database with an input file before use. 
I have created several functions to do this;
traversal, menu add, menu print, flush, find_book, print_book_details, get_book, delete_book, find_book_to_delete,
special_case__book_to_delete, position & read_book_database 

To test the program, the file Test.txt can be used as input to the database program, to simulate keyboard
input. Once you have adapted your program as above, and compiled it, run the command ./database1 < input file > 


Copyright (c) 2014 Luke Marcus Biagio Testa
All rights reserved.

Redistribution and use in source and binary forms are permitted
provided that the above copyright notice and this paragraph are
duplicated in all such forms and that any documentation,
advertising materials, and other materials related to such
distribution and use acknowledge that the software was developed
by the Luke Marcus Biagio Testa. The name of the
Luke Marcus Biagio Testa may not be used to endorse or promote products derived
from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* maximum number of books that can be stored at once (relevant only
   to storage using an array) */

#define MAX_TITLE_LENGTH  100
#define MAX_AUTHOR_LENGTH 100

/* Book structure
   */


struct Book 
{
   /* Book details */
   char title[MAX_TITLE_LENGTH+1];   /* name string */
   char author[MAX_AUTHOR_LENGTH+1]; /* job string */
   int  year;                        /* year of publication */
   
   /* pointers to left and right branches pointing down to next level in
      the binary tree (for if you use a binary tree instead of an array) */
   struct Book *left, *right;
};








/* tree of books, initialized to NULL. Ignore if using an array */
static struct Book *book_tree = NULL;

/* array of books, and number of books stored initialized to zero. Ignore
 * if using a binary tree */














/* read_line():
 *
 * Read line of characters from file pointer "fp", copying the characters
 * into the "line" string, up to a maximum of "max_length" characters, plus
 * one for the string termination character '\0'. Reading stops upon
 * encountering the end-of-line character '\n', for which '\0' is substituted
 * in the string. If the end of file character EOF is reached before the end
 * of the line, the failure condition (-1) is returned. If the line is longer
 * than the maximum length "max_length" of the string, the extra characters
 * are read but ignored. Success is returned (0) on successfully reading
 * a line.
 */
static int read_line ( FILE *fp, char *line, int max_length )
{
   int i;
   char ch;

   /* initialize index to string character */
   i = 0;

   /* read to end of line, filling in characters in string up to its
      maximum length, and ignoring the rest, if any */
   for(;;)
   {
      /* read next character */
      ch = fgetc(fp);

      /* check for end of file error */
      if ( ch == EOF )
	 return -1;

      /* check for end of line */
      if ( ch == '\n' )
      {
	 /* terminate string and return */
	 line[i] = '\0';
	 return 0;
      }

      /* fill character in string if it is not already full*/
      if ( i < max_length )
	 line[i++] = ch;
   }

   /* the program should never reach here */
   return -1;
}








/* read_string():
 *
 * Reads a line from the input file pointer "fp", starting with the "prefix"
 * string, and filling the string "string" with the remainder of the contents
 * of the line. If the start of the line does not match the "prefix" string,
 * the error condition (-1) is returned. Having read the prefix string,
 * read_string() calls read_line() to read the remainder of the line into
 * "string", up to a maximum length "max_length", and returns the result.
 */
static int read_string ( FILE *fp,
			 char *prefix, char *string, int max_length )
{
   int i;

   /* read prefix string */
   for ( i = 0; i < strlen(prefix); i++ )
      if ( fgetc(fp) != prefix[i] )
	 /* file input doesn't match prefix */
	 return -1;

   /* read remaining part of line of input into string */
   return ( read_line ( fp, string, max_length ) );
}







/* Prints book details toscreen */

void print_book_details(struct Book *details)
{
			fprintf(stdout,"Title: %s \n", details->title);
			fprintf(stdout,"Author: %s \n", details->author);
			fprintf(stdout,"Year: %i \n\n", details->year);
}





/*Function to flush buffer to protect against character errors for integers */

void flush(void)
{
	char data_we_dont_need;

	do
	{
		data_we_dont_need = getchar();
	}
	while(data_we_dont_need != '\n');
}







/* Recursive function for arranging the data entered as less than or equl to the root node, and storing in the furthest node that
has branches equal to NULL (no informationstored) */

 void position(struct Book *new, struct Book *current)
 {
			if(strcmp(new->title, (*current).title)<0)
			{
				if ((*current).left == NULL) 
				{
					(*current).left = new;
				}
				else
				{
					position(new, (*current).left);
				}
			}
			else 
			{
				if ((*current).right == NULL) 
				{
					(*current).right = new;
				}
				else
				{
					position(new, (*current).right);
				}
			}
}








/* menu_add_book():
 *
 * Add new book to database
 * On first call, read_line string is saved into the data variables contained in the new book structure. The first data inputs are saved as the root of
 * the tree under the conditions that there is no stems stored to this root. Validation checks are done on each input according to the tender
 */

 
 


static void menu_add_book(void)
{

/* Sets a memory allocation to the data currently being enterred */

	struct Book *new;
	new=(struct Book*)malloc(sizeof(struct Book));
	new->left = new->right = NULL;

	char title[MAX_TITLE_LENGTH+1], author[MAX_AUTHOR_LENGTH+1];
	int year, errorcheck, x;
	static int iterations=0;
	char *new_start_of_string;

	fprintf(stderr, "Please Enter the Title, Author and Publication Date pf the book respectively\n\n");
	iterations++;

/* Reads title's string which is stored in stdin using the read_in function. This is then placed into the memory allocation for later use (takes from stdin, called title of length n). Includes validation check against no enterred strings (if compares are false, they are greater greater than 0) */

	do
	{
		errorcheck=0;

		read_line(stdin, title, MAX_TITLE_LENGTH);
		errorcheck = strcmp("\n",title);
	}
	while(errorcheck>0);

/* check The, An and A against the title and rearranging name before saving the book titles into the data variable inside the new structure */

	if(strncmp(title, "The ",4)==0)
	{
		strcat(title,", The");
		new_start_of_string = &title[4];
		strcpy(new->title, new_start_of_string);
	}

	else if (strncmp(title, "A ",2)==0)
	{
		strcat(title,", A");
		new_start_of_string = &title[2];
		strcpy(new->title, new_start_of_string);
	}

	else if (strncmp(title, "An ",3)==0)
	{
		strcat(title,", An");
		new_start_of_string = &title[3];
		strcpy(new->title, new_start_of_string);
	}
	
	else 
		strcpy(new->title, title);

/* takes in strings enterred from keyboard and assigns them to a data variable inside the book structure called new. New contains all variables with respect to its mother structure, book. Includes validation checks*/

	do
	{
		errorcheck=0;
		read_line(stdin, author, MAX_AUTHOR_LENGTH);
		errorcheck = strcmp("\n",author);
	}
	while(errorcheck>0);

	strcpy(new->author, author);

/* validation checks/copying year input into the new book data structure */

	do
	{
		x = scanf("%i", &year);
		if(x!= 1)
		{
			flush();	
			fprintf(stderr,"\nInput Error, Please correct enter the year\n");
			continue;
		}
		if(year<0)
		{
			x++;
		}
	}
	while(x!=1);

	new->year=year;

/* The first data input will be stored as the root of the binary tree. Next data will be saved in a location depending
on if it's greater, equal or less than the root, and the order it was entered in */

	if(iterations==1)
	{
		book_tree = new;
	}
	
	if(iterations>1)
	{
		position(new, book_tree);
	}

}








/* level order traversal for printing data */

void traversal(struct Book *current)
 {
				if ((*current).left != NULL) 
				{
					traversal((*current).left);
				}
				
				print_book_details(current);
				
				if ((*current).right != NULL) 
				{
					traversal((*current).right);
				}

}






/* menu_print_database():
 * Uses level order traversal to print and sort book data stored in the binary tree
 * Print database of books to standard output in alphabetical order of title.
 */
static void menu_print_database(void)
{
	if(book_tree!=NULL)
	{
		traversal(book_tree);
	}
	else
	{
		fprintf(stderr,"Tree Empty\n");
		fprintf(stdout,"NULL\n");
	}
}	    





/* Recursive function that compares the title to the current node which begins at root, and 
searches the tree in alphabetical order. When title is found, book detials are printed to screen via
another traversal printing function */

 void find_book(char title[MAX_TITLE_LENGTH+1], struct Book *current)
 {
			int x;
			
			x=strcmp(title, (*current).title);
			
			if (x==0)
			{
				print_book_details(current);
			}
			
			else if(x<0)
			{
				if ((*current).left != NULL) 
				{
					find_book(title, current->left);
				}
				else
				{
					fprintf(stderr,"Book not found\n");
				}
			}

			else if(x>0)
			{
				if ((*current).right != NULL) 
				{
					find_book(title, current->right);
				}
				else
				{
					fprintf(stderr,"Book not found\n");
				}
			}
}






/* menu_get_book_details():
 *
 * Get details of book from database.
 */
static void menu_get_book_details(void)
{
	int errorcheck;
	char title[MAX_TITLE_LENGTH+1];
	
	do
	{
		errorcheck=0;

		read_line(stdin, title, MAX_TITLE_LENGTH);
		errorcheck = strcmp("\n",title);
	}
	while(errorcheck>0);
		
	find_book(title, book_tree);
}





/* Deletes book and rearranges binary tree for non-special cases depending on empty node locations. This
moves the left or right pointers of the tree accordingly to the pointer of the deleted book then free's its memory
once pointers from the current node to the node containing the search keyword are rearranged*/

 void find_book_to_delete(char title[MAX_TITLE_LENGTH+1], struct Book *current)
 {
			struct Book *nextbook;

			if(strcmp(title, (*current).title)<0)
			{
				if ((*current).left != NULL) 
				{
					if(strcmp(title, current->left->title)==0)
					{
						nextbook=current->left;
						if(nextbook->left!=NULL)
						{
							current->left=nextbook->left;
							if(nextbook->right!=NULL)
							{
								position(nextbook->right, book_tree);
							}
						}
						else 
						{
							if(nextbook->right!=NULL)
							{
							current->left=nextbook->right;
							}
							else {
								current->left=NULL;
							}
						}
						free(nextbook);
					}
					else
					{
						find_book_to_delete(title,current->left);
					}
				}
				else
				{
					fprintf(stderr,"Book not found\n");
				}
			}
				
			else
			{
				if ((*current).right != NULL) 
				{
					if(strcmp(title, current->right->title)==0)
					{
						nextbook=current->right;
						if(nextbook->left!=NULL)
						{
							current->right=nextbook->left;
							if(nextbook->right!=NULL)
							{
								position(nextbook->right, book_tree);
							}
						}
						else 
						{
							if(nextbook->right!=NULL)
							{
							current->right=nextbook->right;
							}
							else {
								current->right=NULL;
							}
						}
						free(nextbook);
					}
					else
					{
						find_book_to_delete(title,current->right);
					}
				}
				else
				{
					fprintf(stderr,"Book not found\n");
				}
			}
}



 struct Book special_case__book_to_delete(char title[MAX_TITLE_LENGTH+1], struct Book *current)
 {
 
	if(current->left!=NULL)
	{
		book_tree=current->left;
		if(current->right!=NULL)
		{
			position(current->right, book_tree);
		}
		free(current);
	}
	else
	{
		if(current->right!=NULL)
		{
			book_tree=current->right;
			free(current);
		}
		else
		{
			fprintf(stderr,"Root has been deleted. No data in tree");
			free(current);
			book_tree=book_tree->left=book_tree->right=NULL;
		}
	}
 }

/* menu_delete_book():
 *
 * Delete new book from database. Books Beginning with AN, A and The are also treated similarly 
to the add function. Thus searching for The Adventures would find a book named Adventure, The
 */
static void menu_delete_book(void)
{

	int errorcheck;
	char title[MAX_TITLE_LENGTH+1];
	static int iteration=0;
	iteration++;
	
	do
	{
		errorcheck=0;

		read_line(stdin, title, MAX_TITLE_LENGTH);
		errorcheck = strcmp("\n",title);
	}
	while(errorcheck>0);
	
	if(strcmp(title, book_tree->title)==0)
	{
		special_case__book_to_delete(title, book_tree);
	}
	else
	{
		find_book_to_delete(title, book_tree);
	}
}








/* read file containing database of books from a file for intialization. Uses similar approach
to the menu_add function but reads strings using the read_string function from an opened input file*/

int read_book_database (char *file_name[20000] )
{

	char title[MAX_TITLE_LENGTH+1], author[MAX_AUTHOR_LENGTH+1], year_as_string[5], free_line[100];
	int year, errorcheck, validinput;
	static int iterations=0;
	char *new_start_of_string;
	struct Book *new;
	
	FILE* fp;
	fp = fopen(file_name,"r");
do
{

	new=(struct Book*)malloc(sizeof(struct Book));
	new->left = new->right = NULL;
	
	iterations++;
	
/* Reads book details from the initial database using read_string and converts years into integers as 
required. Exit_Failure integer values are returned if one book entry is incorrect */

		errorcheck=0;

		validinput = read_string ( fp, "Title: ", title, 70 );
		if(validinput==-1)
		{
			continue;
		}
	
/* check The, An and A against the title and rearranging name before saving the book titles into the data variable inside the new structure */

	if(strncmp(title, "The ",4)==0)
	{
		strcat(title,", The");
		new_start_of_string = &title[4];
		strcpy(new->title, new_start_of_string);
	}
	
	else if (strncmp(title, "A ",2)==0)
	{
		strcat(title,", A");
		new_start_of_string = &title[2];
		strcpy(new->title, new_start_of_string);
	}
	
	else if (strncmp(title, "An ",3)==0)
	{
		strcat(title,", An");
		new_start_of_string = &title[3];
		strcpy(new->title, new_start_of_string);
	}
	
	else 
		strcpy(new->title, title);

	validinput = read_string ( fp, "Author: ", author, 70 );
	if(validinput==-1)
	{
		fprintf(stderr,"Missing Author Information\n");
		return -1;
	}
	strcpy(new->author, author);
	
/* validation checks/copying year input into the new book data structure */

	validinput = read_string ( fp, "Year: ", year_as_string, 70 );
	if(validinput==-1)
	{
		fprintf(stderr,"Missing Year Information\n");
		return -1;
	}
	year=atoi(year_as_string);
	new->year=year;	

	if(year<0 || year > 10000)
	{
		fprintf(stderr,"Incorrect Year Entry\n");
		return -1;
	}
	
	/*Clears new line after each book data entry from file if a menu integer is not enterred*/
	
	read_string ( fp, "", free_line, 70 );
	
	
/* The first data input will be stored as the root of the binary tree. Next data will be saved in a location depending
on if it's greater, equal or less than the root, and the order it was entered in */

	if(iterations==1)
	{
		book_tree = new;
	}
	
/*	printf("%s\n",book_tree->title);
	printf("%s\n",book_tree->author);
	printf("%i\n",book_tree->year); */
	
	if(iterations>1)
	{
		position(new, book_tree);
	}

}
while(validinput==0);
	
}





/* get_tree_depth():
 *
 * Recursive function to compute the number of levels in a binary tree.
 */
static int get_tree_depth ( struct Book *book, int level )
{
   int level1, level2;

   /* return with the current level if we've reached the bottom of this
      branch */
   if ( book == NULL ) return level;

   /* we need to go to the next level down */
   level++;

   /* count the number of levels down both branches */
   level1 = get_tree_depth ( book->left,  level );
   level2 = get_tree_depth ( book->right, level );

   /* return the depth of the deepest branch */
   if ( level1 > level2 ) return level1;
   else return level2;
}











/* menu_print_tree():
 *
 * Print tree to standard output. You can use this function to print out the
 * tree structure for debugging purposes. It is also used by the testing
 * software to check that the tree is being built correctly.
 *
 * The first letter of the title of each book is printed.
 */
static void menu_print_tree(void)
{
   int no_levels, level, size, i, j, k;
   struct Book **row;

   /* find level of lowest node on the tree */
   no_levels = get_tree_depth ( book_tree, 0 );

   /* abort if database is empty */
   if ( no_levels == 0 ) return;

   /* compute initial indentation */
   assert ( no_levels < 31 );

   row = (struct Book **) malloc((1 << (no_levels-1))*sizeof(struct Book *));
   row[0] = book_tree;
   printf ( "\n" );
   for ( size = 1, level = 0; level < no_levels; level++, size *= 2 )
   {
      /* print books at this level */
      for ( i = 0; i < size; i++ )
      {
	 if ( i == 0 )
	    for ( j = (1 << (no_levels - level - 1)) - 2; j >= 0; j-- )
	       printf ( " " );
	 else
	    for ( j = (1 << (no_levels - level)) - 2; j >= 0; j-- )
	       printf ( " " );

	 if ( row[i] == NULL )
	    printf ( " " );
         else
	    printf ( "%c", row[i]->title[0] );
      }

      printf ( "\n" );

      if ( level != no_levels-1 )
      {
	 /* print connecting branches */
	 for ( k = 0; k < ((1 << (no_levels - level - 2)) - 1); k++ )
	 {
	    for ( i = 0; i < size; i++ )
	    {
	       if ( i == 0 )
		  for ( j = (1 << (no_levels - level - 1))-3-k; j >= 0; j-- )
		     printf ( " " );
	       else
		  for ( j = (1 << (no_levels - level)) - 4 - 2*k; j >= 0; j-- )
		     printf ( " " );

	       if ( row[i] == NULL || row[i]->left == NULL )
		  printf ( " " );
	       else
		  printf ( "/" );

	       for ( j = 0; j < 2*k+1; j++ )
		  printf ( " " );

	       if ( row[i] == NULL || row[i]->right == NULL )
		  printf ( " " );
	       else
		  printf ( "\\" );
	    }

	    printf ( "\n" );
	 }

	 /* adjust row of books */
	 for ( i = size-1; i >= 0; i-- )
	 {
	    row[2*i+1] = (row[i] == NULL) ? NULL : row[i]->right;
	    row[2*i]   = (row[i] == NULL) ? NULL : row[i]->left;
	 }
      }
   }

   free(row);
}	    

/* codes for menu */
#define ADD_CODE     0
#define DETAILS_CODE 1
#define DELETE_CODE  2
#define PRINT_CODE   3
#define TREE_CODE    4
#define EXIT_CODE    5




















int main ( int argc, char *argv[] )
{
   /* check arguments */
   if ( argc != 1 && argc != 2 )
   {
      fprintf ( stderr, "Usage: %s [<database-file>]\n", argv[0] );
      exit(-1);
   }

   /* read database file if provided, or start with empty database */
   int x;
   if ( argc == 2 )
     x = read_book_database ( argv[1] );
	
   for(;;)
   {
      int choice, result;
      char line[301];

      /* print menu to standard error */
      fprintf ( stderr, "\nOptions:\n" );
      fprintf ( stderr, "%d: Add new book to database\n",      ADD_CODE );
      fprintf ( stderr, "%d: Get details of book\n",       DETAILS_CODE );
      fprintf ( stderr, "%d: Delete book from database\n",  DELETE_CODE );
      fprintf ( stderr, "%d: Print database to screen\n",    PRINT_CODE );
      fprintf ( stderr, "%d: Print tree\n",                   TREE_CODE );
      fprintf ( stderr, "%d: Exit database program\n",        EXIT_CODE );
      fprintf ( stderr, "\nEnter option: " );

      if ( read_line ( stdin, line, 300 ) != 0 ) continue;

      result = sscanf ( line, "%d", &choice );
      if ( result != 1 )
      {
	 fprintf ( stderr, "corrupted menu choice\n" );
	 continue;
      }

      switch ( choice )
      {
         case ADD_CODE: /* add book to database */
	 menu_add_book();
	 break;

         case DETAILS_CODE: /* get book details from database */
	 menu_get_book_details();
	 break;

         case DELETE_CODE: /* delete book from database */
	 menu_delete_book();
	 break;

         case PRINT_CODE: /* print database contents to screen
			     (standard output) */
	 menu_print_database();
	 break;

         case TREE_CODE: /* print tree to screen (standard output) */
	 menu_print_tree();
	 break;

	 /* exit */
         case EXIT_CODE:
	 break;

         default:
	 fprintf ( stderr, "illegal choice %d\n", choice );
	 break;
      }

      /* check for exit menu choice */
      if ( choice == EXIT_CODE )
	 break;
   }

   return 0;   
}
