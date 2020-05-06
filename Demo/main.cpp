#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<gmp.h>
//#include "tools_rbtree.h"
#include<Space/Algebra_Fun_.h>
#include "test_h/vector_test.h"
void test_void(void*p1)
{
    __mpz_struct* q=(__mpz_struct*)p1;
    
    //mpz_t *q=(mpz_t*) p1;
    gmp_printf("q=%Zd\n",q);

}
//#include<Quaternions/Al_Quaternions.h>
void test_gmp()
{
    mpf_set_default_prec(200);
    mpz_t a,b,c,d;
    mpz_inits(a,b,c,d,NULL);
    mpz_set_d(a,2.1);
    test_void((void*)a);
    //printf("a=%Zd\n",a);
    //mpz_set_ui()

    int tem_i=9;
    mpz_set_ui(b,tem_i);
    
  //  mpz_set_str(b,"9",10);
   
    gmp_printf("b=%Zd\n",b);
    // gmp_scanf("%Zd%Zd\n",a,b);
    mpz_pow_ui(c,b,0);
    //mpz_add(c,a,b);
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
    //mpf_mul(f1,f,f1);
    mpf_div(f1,f,f1);
    //mpf_set_d(f1,4);
    //mpf_sqrt_ui(f1,4);
    gmp_printf("f1=%.Ff,f=%.Ff\n",f1,f);
    mpf_cmp(f,f1);
    //
    //对double比较
   int re=mpf_cmp_d(f1,1);
   printf("lre:%d\n",re);
    //转化为double类型
    //mpf_get_d()
    //整除运算
//mpz_cdiv_q(mt1,fmse->base->id,mt2);
		
		//减法
		//mpz_sub_ui(mt1,mt1,1);
		//取余运算
//		mpz_cdiv_r(mt1,mt1,a);
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
void test_rb1()
{
    RB_Tree* tree=(RB_Tree*)malloc(sizeof(RB_Tree));
    RB_Tree_init_mpz(tree);
    RB_mpz rbm;
    RB_init_mpz(&rbm);
    mpz_set_ui(rbm.key,3);
    tree->insert(tree,&rbm);
    mpz_set_ui(rbm.key,6);
    tree->insert(tree,&rbm);
    mpz_set_ui(rbm.key,0);
    tree->insert(tree,&rbm);
    mpz_set_str(rbm.key,"234234789798",10);

    tree->insert(tree,&rbm);

    RB_Trav* it=tree->begin(tree);
    for(;it->it!=NULL;it->next(it))
    {
        gmp_printf("test_rb1:%Zd\n",(__mpz_struct*)(it->first(it)));
    }
    free(it);

    mpz_clear(rbm.key);


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
void test_inverse()
{

    Tensors_Algebra_System* tas=(Tensors_Algebra_System*)malloc(sizeof(Tensors_Algebra_System));
    Tensors_Algebra_System_init(tas,4);
    tas->mult=Tensor_mpf_mult;
    tas->plus=Tensor_mpf_plus;
    tas->div=Tensor_mpf_div;
 //   tas->copy=Tensor_mpf_copy;
    tas->copy_from_double=Tensor_double2_mpf;
    tas->set_copy=Tensor_mpf_set_copy;
    tas->free_data=Tensor_mpf_free;
    tas->cmp=Tensor_mpf_cmp;
    tas->cmp_d=Tensor_mpf_cmp_d;
    Tensor* t_i=tas->T_create();

    int ids[]={0,0};
    t_i->insert(tas->as,t_i,ids,2,tas->copy_from_double(1));
    ids[0]=0;ids[1]=2;
    t_i->insert(tas->as,t_i,ids,2,tas->copy_from_double(3));
    ids[0]=1;ids[1]=0;
    t_i->insert(tas->as,t_i,ids,2,tas->copy_from_double(1));
    ids[0]=1;ids[1]=1;
    t_i->insert(tas->as,t_i,ids,2,tas->copy_from_double(-5));
    ids[0]=1;ids[1]=2;
    t_i->insert(tas->as,t_i,ids,2,tas->copy_from_double(6));
    ids[0]=2;ids[1]=0;
    t_i->insert(tas->as,t_i,ids,2,tas->copy_from_double(11));
    ids[0]=2;ids[1]=2;
    t_i->insert(tas->as,t_i,ids,2,tas->copy_from_double(9));
    ids[0]=3;ids[1]=3;
    t_i->insert(tas->as,t_i,ids,2,tas->copy_from_double(1));
    tensor_mpf_print_self(t_i);
    Tensor* t=Tensor_inverse(tas,t_i);
    tensor_mpf_print_self(t); 

}
int main(int argc,char **argv)
{
    char s='0';
    printf("s:%c\n",s+3);
  //  test_rb1();
    //test_gmp();
    //int re[4];
   // test_vector();
    //test_rb();
        //mpf_out
    //mpf_set_
    //test_inverse();
    Tensors_Algebra_System* tas=(Tensors_Algebra_System*)malloc(sizeof(Tensors_Algebra_System));
    Tensors_Algebra_System_init(tas,2);
    tas->mult=Tensor_mpf_mult;
    tas->plus=Tensor_mpf_plus;
    tas->div=Tensor_mpf_div;
 //   tas->copy=Tensor_mpf_copy;
    tas->copy_from_double=Tensor_double2_mpf;
    tas->set_copy=Tensor_mpf_set_copy;
    tas->free_data=Tensor_mpf_free;
    tas->cmp=Tensor_mpf_cmp;
    tas->cmp_d=Tensor_mpf_cmp_d;
    Tensor* t_i=tas->T_create();
    int ids[2];
    ids[0]=0;ids[1]=1;
    t_i->insert(tas->as,t_i,ids,1,tas->copy_from_double(1));
    ids[0]=1;ids[1]=2;
    t_i->insert(tas->as,t_i,ids,1,tas->copy_from_double(1));
    //ids[0]=1;ids[1]=2;
    //t_i->insert(tas->as,t_i,ids,2,tas->copy_from_double(1));
    tensor_mpf_print_self(t_i);
    Tensor* t=Hodge_Anti_tensor_(tas,t_i);
    tensor_mpf_print_self(t);
    //t_i
    return 0;
}




