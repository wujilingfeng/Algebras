#include<Tensors/Al_Tensors.h>
void double_mult(void*p1,void*p2)
{
    double*q1=(double*)p1,*q2=(double*)p2;
    *q1=(*q1)*(*q2);
}
void double_plus(void*p1,void*p2)
{
    double*q1=(double*)p1,*q2=(double*)p2;
    *q1=(*q1)+(*q2);

}
void *double_copy(void*tar)
{
    void* re=malloc(sizeof(double));
    memmove(re,tar,sizeof(double));
    return re;

}
void Tensor_mpf_mult(void* p1,void *p2)
{
    __mpf_struct*q1=(__mpf_struct*)p1;
    __mpf_struct*q2=(__mpf_struct*)p2;
    mpf_mul(q1,q1,q2);
    
}
void Tensor_mpf_plus(void*p1,void*p2)
{
    __mpf_struct*q1=(__mpf_struct*)p1;
    __mpf_struct*q2=(__mpf_struct*)p2;
    mpf_add(q1,q2,q1);


}
void* Tensor_mpf_copy(void*p)
{ 
    __mpf_struct*q=(__mpf_struct*)p;
    __mpf_struct*re=(__mpf_struct*)malloc(sizeof(__mpf_struct));
    mpf_inits(re,NULL);
    mpf_set(re,q);
    return (void*)(re);
}
void tensor_print_self(Tensor*t)
{
    RB_Trav *it=t->value->begin(t->value);
    printf("kaishi\n");
    for(;it->it!=NULL;it->next(it))
    {
        gmp_printf("id:%Zd \n",(__mpz_struct*)it->first(it));
        Field_Mult_Struct_Ele* fmse=(Field_Mult_Struct_Ele*)it->second(it);
        for(Node* it1=fmse->base->els;it1!=NULL;it1=(Node*)it1->Next)
        {
        
            printf("%d  ",((Algebra_Basic_Element*)(it1->value))->id);
        }
        printf("\n");
    }
}
void test_vector()
{
	Tensors_Algebra_System* tas=(Tensors_Algebra_System*)malloc(sizeof(Tensors_Algebra_System));
    Tensors_Algebra_System_init(tas,7);
    tas->mult=Tensor_mpf_mult;
    tas->plus=Tensor_mpf_plus;
    tas->copy=Tensor_mpf_copy;

    Tensor* t=(Tensor*)malloc(sizeof(Tensor));
    int ids[]={0,5,4};
    double d=10.4;
    Plus_Struct_Ele_init(t);
    t->insert(tas->as,t,ids,3,double_copy(&d));
    tensor_print_self(t);    

    ids[0]=3;
    t->insert(tas->as,t,ids,3,double_copy(&d));
    t->zero(t);
    tensor_print_self(t);    


    //t->insert()
    //Vector *v=vas->create_v(vas->as,0,qua_copy(&d));

    //Vectors_Algebra_System_init(vas,10);
}
