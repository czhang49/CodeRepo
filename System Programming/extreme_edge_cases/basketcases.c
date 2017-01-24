#include "basketcases.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

/**
 * You should allocate memory for the `basket_report_t` struct that you return, and set its members as described in the MP specification.
 *
 * @param   baskets     An array of `basket_t` structs
 * @param   length      The length of the array `baskets`
 * @return              A `basket_report_t` struct with fields set as described in the MP specification
 */
basket_report_t * handle_baskets (basket_t baskets[], size_t length) {
    
    basket_report_t* report = (basket_report_t*) malloc (sizeof(basket_report_t));

    if (length%2==0){
	report->target_basket = NULL;
    }else{
	report->target_basket = (&baskets[(length+1)/2-1]);
    }

    uint32_t i;
    char interim[6];
    strcpy(interim,baskets[length-1].label);
    for(i=0;i<length-1;i++){
	strcpy(baskets[length-1-i].label,baskets[length-2-i].label);   
    }
    strcpy(baskets[0].label,interim);

    size_t j;
    uint32_t k;
    report->triples_summed=0;
    if (length>=3){
	j=length-3;
	for(k=0;k<=j;k++){
	    report->triples_summed=baskets[k].offset+baskets[k+1].offset+baskets[k+2].offset;
  	}
    }

    if (report->triples_summed==0 && baskets!=NULL){
	report->bad_batch=baskets;
    }else{
	report->bad_batch=NULL;
    }

    uint32_t l;
    for (l=0;l<length;l++){
	printf("%s\n",baskets[l].label);   
    }
    for (l=0;l<length;l++){
	printf("%p\n",&(baskets[l]));   
    }
    printf("The report triples_summed is %d\n",report->triples_summed);
    printf("The report target_basket is %p\n",report->target_basket);


    return report;
}
