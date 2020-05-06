#include<Tensors/Antisymmetric_Tensor.h>
#include<Tensors/Al_Tensors.h>

static void Tensor_mpf_mult(void* p1,void *p2)
{
    __mpf_struct*q1=(__mpf_struct*)p1;
    __mpf_struct*q2=(__mpf_struct*)p2;
    mpf_mul(q1,q1,q2);
    
}
static void  Tensor_mpf_plus(void*p1,void*p2)
{
    __mpf_struct*q1=(__mpf_struct*)p1;
    __mpf_struct*q2=(__mpf_struct*)p2;
    mpf_add(q1,q2,q1);
}
void Tensor_mpf_div(void* p1,void*p2)
{
    __mpf_struct*q1=(__mpf_struct*)p1;
    __mpf_struct*q2=(__mpf_struct*)p2;
    mpf_div(q1,q1,q2);
}
static int Tensor_mpf_cmp(void*p1,void*p2)
{
    __mpf_struct*q1=(__mpf_struct*)p1,*q2=(__mpf_struct*)p2;
    return mpf_cmp(q1,q2);

}
static int Tensor_mpf_cmp_d(void*p1,double d)
{
    __mpf_struct*q1=(__mpf_struct*)p1;
    mpf_t q2;
    //mpf_inits();
    return mpf_cmp_d(q1,d);

}
/*
static void* Tensor_mpf_copy(void*p)
{ 
    __mpf_struct*q=(__mpf_struct*)p;
    __mpf_struct*re=(__mpf_struct*)malloc(sizeof(__mpf_struct));
    mpf_inits(re,NULL);
    mpf_set(re,q);
    return (void*)(re);
}*/
static void Tensor_mpf_set_copy(void *p1,void*p2)
{
	__mpf_struct*q1=(__mpf_struct*)p1,*q2=(__mpf_struct*)p2;
	mpf_set(q1,q2);

}
static void Tensor_mpf_free(void*p)
{
    __mpf_struct* q=(__mpf_struct*)p;
    mpf_clear(q);
    free(q);
}
static void* Tensor_double2_mpf(double d)
{    
    __mpf_struct*re=(__mpf_struct*)malloc(sizeof(__mpf_struct));
    mpf_inits(re,NULL);
    mpf_set_d(re,d);
    return (void*)re;
}
void tensor_mpf_print_self(Tensor* t)
{
    printf("************************************\n");
	printf("order:%d\n",t->order(t));
    RB_Trav *it=t->value->begin(t->value);
    for(;it->it!=NULL;it->next(it))
    {
        gmp_printf("id:%Zd \n",(__mpz_struct*)it->first(it));
        Field_Mult_Struct_Ele* fmse=(Field_Mult_Struct_Ele*)it->second(it);
        gmp_printf("value:%.Ff\n",(__mpf_struct*)(fmse->value));
        for(Node* it1=fmse->base->els;it1!=NULL;it1=(Node*)it1->Next)
        {
        
            printf("%d  ",((Algebra_Basic_Element*)(it1->value))->id);
        }
        printf("\n");
    }
    free(it);
    printf("************************************\n");
    
}
void Tensors_Algebra_System_mpf_init(Tensors_Algebra_System*tas,int size)
{
    Tensors_Algebra_System_init(tas,size);
    tas->mult=Tensor_mpf_mult;
    tas->plus=Tensor_mpf_plus;
    tas->div=Tensor_mpf_div;
   // tas->copy=Tensor_mpf_copy;
    tas->copy_from_double=Tensor_double2_mpf;
	tas->set_copy=Tensor_mpf_set_copy;
    tas->free_data=Tensor_mpf_free;
    tas->cmp=Tensor_mpf_cmp;
    tas->cmp_d=Tensor_mpf_cmp_d;


}
