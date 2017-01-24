#include "camelCaser_tests.h"
#include "camelCaser.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
/*
 * Testing function for various implementations of camelCaser.
 *
 * @param  camelCaser   A pointer to the target camelCaser function.
 * @return              Correctness of the program (0 for wrong, 1 for correct).
 */
extern uint32_t Num_string ;
extern uint32_t Size_string ;
int test_camelCaser (char ** (* camelCaser)(char *))
{

    uint32_t i;
    char test_string[] = "aaaaa";   
    char** result_string = camelCaser(test_string);

    for (i=0;i<Num_string;i++){
	
	free(result_string[i]);
 
    }
   free (result_string);
    
    return 1;
}
