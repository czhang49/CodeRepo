// Shell
// CS 241 Fall 2015
#include "log.h"
// Create and test your log here
int main() { 

	Log* log = Log_create("cheninput.txt");

	char cm1[]="command1";
	char cm2[]="command2";
	char cm3[]="shita this is to see the reverse search";
	char cm4[]="command3";

	Log_add_command(log,cm1);
	Log_add_command(log,cm2);
	Log_add_command(log,cm3);
	Log_add_command(log,cm4);

	printf("The second command is %s\n",Log_get_command(log,1));

	char sr[] = "shit";
	printf("The reverse search result is %s\n",Log_reverse_search(log,sr));

	char* printable = Log_get_printable_history(log);
	printf("%s",printable);

	free(printable);
	Log_save(log,"chenoutput.txt");

	Log_destroy(log);

	return 0; 
}
