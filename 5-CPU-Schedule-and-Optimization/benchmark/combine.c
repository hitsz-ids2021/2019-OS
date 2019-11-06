#include <stdlib.h>
#include "combine.h"

/* Combining functions */

char combine1_descr[] = "combine1: Maximum use of data abstraction";
/* $begin combine1 */
/* Implementation with maximum use of data abstraction */
void combine1(vec_ptr v, data_t *dest)
{
    long i;

    *dest = IDENT;
    for (i = 0; i < vec_length(v); i++) {
	data_t val;
	get_vec_element(v, i, &val);
	/* $begin combineline */
	*dest = *dest OP val;
	/* $end combineline */
    }
}
/* $end combine1 */

char combine2_descr[] = "combine2: Take vec_length() out of loop";
/* $begin combine2 */
/* Move call to vec_length out of loop */
void combine2(vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(v);

    *dest = IDENT;
    for (i = 0; i < length; i++) {
	data_t val;
	get_vec_element(v, i, &val);
	*dest = *dest OP val;
    }
}
/* $end combine2 */

char combine3_descr[] = "combine3: Array reference to vector data";
/* $begin combine3 */
/* Direct access to vector data */
void combine3(vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(v);
    data_t *data = get_vec_start(v);

    *dest = IDENT;
    for (i = 0; i < length; i++) {
	*dest = *dest OP data[i];
    }
}
/* $end combine3 */

char combine4_descr[] = "combine4: Array reference, accumulate in temporary";
/* $begin combine4 */
/* Accumulate result in local variable */
void combine4(vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(v);
    data_t *data = get_vec_start(v);
    data_t x = IDENT;

    for (i = 0; i < length; i++) {
	x = x OP data[i];
    }
    *dest = x;
}
/* $end combine4 */

char unroll2a_combin_descr[] = "unroll2a_combine: Array code, unrolled by 2";
/* $begin combine5 */
/* 2 x 1 loop unrolling */
void unroll2a_combin(vec_ptr v, data_t *dest)
{

    long length = vec_length(v);
    long limit = length-1;
    data_t *data = get_vec_start(v);
    data_t x = IDENT;
    long i;
    /* Combine 2 elements at a time */
    for (i = 0; i < limit; i+=2) {
      /* $begin combine5-update */
	x = (x OP data[i]) OP data[i+1];
      /* $end combine5-update */
    }

    /* Finish any remaining elements */
    for (; i < length; i++) {
	x = x OP data[i];
    }
    *dest = x;
}
char unroll2aa_combine_descr[] = "unroll2aa_combine: Array code, unrolled by 2";
/* $begin combine5a */
/* 2 x 1 loop unrolling */
void unroll2aa_combine(vec_ptr v, data_t *dest)
{

    long length = vec_length(v);
    long limit = length-1;
    data_t *data = get_vec_start(v);
    data_t x = IDENT;
    long i;
    /* Combine 2 elements at a time */
    for (i = 0; i < limit; i+=2) {
      /* $begin combine5a-update */
	x = x OP (data[i] OP data[i+1]);
      /* $end combine5a-update */
    }

    /* Finish any remaining elements */
    for (; i < length; i++) {
	x = x OP data[i];
    }
    *dest = x;
}
/* $end combine5a */

char unroll2x2_combine_descr[] = "unroll2x2_combine: Array code, unrolled by 2, Superscalar x2";
/* $begin combine6 */
/* 2 x 2 loop unrolling */
void unroll2x2_combine(vec_ptr v, data_t *dest)
{
    long length = vec_length(v);
    long limit = length-1;
    data_t *data = get_vec_start(v);
    data_t x0 = IDENT;
    data_t x1 = IDENT;
    long i;
    /* Combine 2 elements at a time */
    for (i = 0; i < limit; i+=2) {
	x0 = x0 OP data[i]; 
	x1 = x1 OP data[i+1];
    }
    /* Finish any remaining elements */
    for (; i < length; i++) {
	x0 = x0 OP data[i];
    }
    *dest = x0 OP x1;
}
/* $end combine6 */

void register_combiners(void)
{
    add_combiner(combine1, combine1, combine1_descr);
    add_combiner(combine2, combine1, combine2_descr);
    add_combiner(combine3, combine1, combine3_descr);
    add_combiner(combine4, combine1, combine4_descr);
    add_combiner(unroll2a_combin, combine1, unroll2a_combin_descr);
    add_combiner(unroll2aa_combine, combine1, unroll2aa_combine_descr);
    add_combiner(unroll2x2_combine, combine1, unroll2x2_combine_descr);
 }






