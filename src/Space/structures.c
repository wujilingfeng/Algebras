#include<Space/structures.h>
void RB_init_mpz(RB_mpz* r)
{
    mpz_inits(r->key,NULL);
    r->value=NULL;
    r->prop=NULL;
}
int RB_cmp_mpz(const void* p1,const void*p2)
{
    int re=0;
    __mpz_struct* q1=(__mpz_struct*)p1,*q2=(__mpz_struct*)p2;
    int re1=mpz_cmp(q1,q2);
    if(re1>0)
    {
        re=1;
    }
    else if(re1<0)
    {
        re=-1;
    }

    return re;
}
void* RB_copy_mpz(void*p)
{ 
    RB_mpz* re1=(RB_mpz*)malloc(sizeof(RB_mpz));
    RB_init_mpz(re1);
    RB_mpz*q=(RB_mpz*)p;
    mpz_set(re1->key,q->key);
    re1->value=q->value;
    return (void*)(re1);
}
static void* get_key_mpz(RB_Trav*trav)
{

    return (void*)((((RB_mpz*)(trav->it->data))->key));
}
static void* get_value_mpz(RB_Trav*trav)
{

    return ((RB_mpz*)(trav->it->data))->value;
}
static void iter_init_mpz(RB_Trav*trav)
{
    trav->first=get_key_mpz;
    trav->second=get_value_mpz;

}
void RB_Tree_init_mpz(RB_Tree*tree)
{
    RB_Tree_init(tree);
    tree->copy=RB_copy_mpz;
    tree->cmp=RB_cmp_mpz;
    tree->iterator_init=iter_init_mpz;
}

