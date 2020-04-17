#include "tools_rbtree.h"
#include<gmp.h>
#ifndef AL_STRUCTURES_H
#define AL_STRUCTURES_H
#ifdef __cplusplus
extern "C"{
#endif
typedef struct RB_mpz 
{
    mpz_t key;
    void* value;
    void *prop;
}RB_mpz;
void RB_init_mpz(RB_mpz* r);
int RB_cmp_mpz(const void* p1,const void*p2);
void* RB_copy_mpz(void*p);
void RB_Tree_init_mpz(RB_Tree*tree);
#ifdef __cplusplus
}
#endif
#endif
