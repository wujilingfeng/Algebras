#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<gmp.h>
//#include "tools_rbtree.h"
#include<Space/Algebra_Fun_.h>
#include "test_h/vector_test.h"
//#include<Quaternions/Al_Quaternions.h>
void test_gmp()
{
    mpf_set_default_prec(64);
mpz_t a,b,c;
    mpz_inits(a,b,c,NULL);
    mpz_set_d(a,2.1);
    mpz_set_str(b,"2.03",10);
   // gmp_scanf("%Zd%Zd",a,b);
    mpz_add(c,a,b);
    gmp_printf("c=%Zd\n",c);
    mpq_t p;
    mpq_inits(p,NULL);
    mpq_set_str(p,"3/5",10);
    gmp_printf("p=%Qd\n",p);
    mpf_t f,f1,f2;
    mpf_inits(f,f1,f2,NULL);
    mpf_set_str(f,"0.33423534663241215465476987808796754523132435477978089096785",10);
    mpf_set_d(f1,2);
    //mpf_add(f1,f,f);
    mpf_mul(f1,f,f1);
    //mpf_set_d(f1,4);
    //mpf_sqrt_ui(f1,4);
    gmp_printf("f=%.Ff\n",f1);
    mpf_cmp(f,f1);
    //
    //对double比较
    mpf_cmp_d(f,0);
    //转化为double类型
    //mpf_get_d()
}
typedef struct  rb_t
{
int key;
void *data;
}rb_t;
static void*t_copy(void* p)
{
    void* dup_p=malloc(sizeof(rb_t));
    memmove(dup_p,p,sizeof(rb_t));
    return dup_p;
}
static int t_cmp(const void* p1,const void* p2)
{
   rb_t* q1=(rb_t*)p1,*q2=(rb_t*)p2;
   if(q1->key>q2->key)
   {
        return 1;
   }
   else if(q1->key<q2->key)
   {
        return -1;
   }
   return 0;
}

void test_rb()
{
    RB_Tree* tree=(RB_Tree*)malloc(sizeof(RB_Tree));
    RB_Tree_init(tree);
    printf("size:%ld\n",tree->size);
    tree->cmp=t_cmp;
    tree->copy=t_copy;
    rb_t t1;
    t1.key=1;
    tree->insert(tree,&t1);
    printf("size:%ld\n",tree->size);

    t1.key=9;
    tree->insert(tree,&t1);
    printf("size:%ld\n",tree->size);

    t1.key=5;
    tree->insert(tree,&t1);
    t1.key=100;
    tree->insert(tree,&t1);
    printf("size:%ld\n",tree->size);
    t1.key=5;
    tree->erase(tree,&t1);
    printf("size:%ld\n",tree->size);

    for(auto iter=tree->begin(tree);iter->it!=NULL;iter->next(iter))
    {
        printf("key:%d \n",((rb_t*)(iter->it->data))->key); 
    }
    for(auto iter=tree->rbegin(tree);iter->it!=NULL;iter->prev(iter))
    {
        printf("key:%d \n",((rb_t*)(iter->it->data))->key); 
    }


    /*jsw_rbtree_t *tree=jsw_rbnew(t_cmp,t_dup,t_rel);
    rb_t t1;
    t1.key=1;
    jsw_rbinsert(tree,&t1); 
    t1.key=9;
    jsw_rbinsert(tree,&t1);
    void *re=NULL;
        re=jsw_rbfind(tree,&t1);
    if(re!=NULL)
    {
        printf("shi\n");
        printf("re:%d\n",((rb_t*)(re))->key);
    }
    jsw_rbtrav_t* iter=jsw_rbtnew();

    void* re1=NULL;
    re1=jsw_rbtfirst(iter,tree);
    printf("key:%d\n",((rb_t*)(re1))->key);
*/
   // tree=jsw_rbnew(t_cmp,t_dup,t_rel);
    //jsw_rbinsert();
}
int main(int argc,char **argv)
{
    char s='0';
    printf("s:%c",s+3);

    test_gmp();
    test_vector();
    //test_rb();
        //mpf_out
    //mpf_set_
    return 0;
}




