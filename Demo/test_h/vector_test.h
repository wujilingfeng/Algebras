#include<Tensors/Al_Tensors.h>
#include<Tensors/Antisymmetric_Tensor.h>
#include<Tensors/Tensors_Operation.h>
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
void Tensor_mpf_div(void* p1,void*p2)
{
    __mpf_struct*q1=(__mpf_struct*)p1;
    __mpf_struct*q2=(__mpf_struct*)p2;
    mpf_div(q1,q1,q2);
}
void* Tensor_mpf_copy(void*p)
{ 
    __mpf_struct*q=(__mpf_struct*)p;
    __mpf_struct*re=(__mpf_struct*)malloc(sizeof(__mpf_struct));
    mpf_inits(re,NULL);
    mpf_set(re,q);
    return (void*)(re);
}
void Tensor_mpf_free(void*p)
{
    __mpf_struct* q=(__mpf_struct*)p;
    mpf_clear(q);
    free(q);
}
static void Tensor_mpf_set_copy(void *p1,void*p2)
{
	__mpf_struct*q1=(__mpf_struct*)p1,*q2=(__mpf_struct*)p2;
	mpf_set(q1,q2);

}
static int Tensor_mpf_cmp(void*p1,void*p2)
{
    __mpf_struct*q1=(__mpf_struct*)p1,*q2=(__mpf_struct*)p2;
    return mpf_cmp(q1,q2);

}
static int Tensor_mpf_cmp_d(void*p1,double d)
{
    __mpf_struct*q1=(__mpf_struct*)p1;
    return mpf_cmp_d(q1,d);

}
void* Tensor_double2_mpf(double d)
{    
    __mpf_struct*re=(__mpf_struct*)malloc(sizeof(__mpf_struct));
    mpf_inits(re,NULL);
    mpf_set_d(re,d);
    return (void*)re;
}
void tensor_double_print_self(Tensor*t)
{
    RB_Trav *it=t->value->begin(t->value);
    printf("kaishi\n");
    for(;it->it!=NULL;it->next(it))
    {
        gmp_printf("id:%Zd \n",(__mpz_struct*)it->first(it));
        Field_Mult_Struct_Ele* fmse=(Field_Mult_Struct_Ele*)it->second(it);
        printf("value:%lf\n",*((double*)(fmse->value)));
        for(Node* it1=fmse->base->els;it1!=NULL;it1=(Node*)it1->Next)
        {
        
            printf("%d  ",((Algebra_Basic_Element*)(it1->value))->id);
        }
        printf("\n");
    }
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

void test_vector()
{
	Tensors_Algebra_System* tas=(Tensors_Algebra_System*)malloc(sizeof(Tensors_Algebra_System));
    Tensors_Algebra_System_init(tas,7);
    tas->mult=Tensor_mpf_mult;
    tas->plus=Tensor_mpf_plus;
    tas->div=Tensor_mpf_div;
 //   tas->copy=Tensor_mpf_copy;
    tas->copy_from_double=Tensor_double2_mpf;
    tas->set_copy=Tensor_mpf_set_copy;
    tas->free_data=Tensor_mpf_free;
    tas->cmp=Tensor_mpf_cmp;
    tas->cmp_d=Tensor_mpf_cmp_d;
    int ids[]={0,5,4};
    double d=10.4;
    mpf_t f1;
    mpf_inits(f1,NULL);
    mpf_set_str(f1,"43.2",10);
    __mpf_struct*f2=(__mpf_struct*)Tensor_mpf_copy(f1);
    gmp_printf("%.Ff\n",f2);
    Tensor* t=tas->T_create();
    t->insert(tas->as,t,ids,3,Tensor_mpf_copy(f1));
    //t->insert(tas->as,t,ids,3,double_copy(&d));
    //tensor_double_print_self(t);  
    tensor_mpf_print_self(t);
    ids[0]=3;
    d=-0.3;
    mpf_set_d(f1,d);
    //t->insert(tas->as,t,ids,3,double_copy(&d));
    t->insert(tas->as,t,ids,3,Tensor_mpf_copy(f1));
    //tensor_double_print_self(t);    
    tensor_mpf_print_self(t);
    Tensor* t1=tas->T_create();
    int ids1[]={0,2,1};
    d=5.001;
    mpf_set_d(f1,-10.0003);
    t1->insert(tas->as,t1,ids1,3,Tensor_mpf_copy(f1));
    tensor_mpf_print_self(t1);
    tas->T_plus(tas,t,t1);
    tensor_mpf_print_self(t);
    gmp_printf("norm:%.Ff\n",(__mpf_struct*)tas->T_norm(tas,t));
    Tensor* t3=tas->T_create();
    int ids2=2;
    t3->insert(tas->as,t3,&ids2,1,Tensor_mpf_copy(f1));
    tensor_mpf_print_self(t3);
    Tensor* t4=Tensor_Wedge_(tas,t,t3);
    tensor_mpf_print_self(t4);
    printf("contraction\n");
    Tensor* tc=W_Tensor_Contraction(tas,t,t3,1,0);

    tensor_mpf_print_self(tc);
    printf("test inverse\n");
    Tensor* t_i=tas->T_create();
    ids[0]=0;ids[1]=0;
    t_i->insert(tas->as,t_i,ids,2,tas->copy_from_double(1));
    ids[1]=1;
    t_i->insert(tas->as,t_i,ids,2,tas->copy_from_double(1));
    ids[0]=1;ids[1]=0;
    t_i->insert(tas->as,t_i,ids,2,tas->copy_from_double(1)); 
    ids[0]=2;ids[1]=2;
    t_i->insert(tas->as,t_i,ids,2,tas->copy_from_double(9.4));

    Tensor*ts=Tensor_inverse(tas,t_i);
    //tensor_mpf_print_self(ts[0]);
    //tensor_mpf_print_self(ts[1]);
    Tensors_Algebra_System_free(tas);
    free(tas);

//    Algebra_Space_free(tas->as);
 //   Algebra_Space_free(tas->dual_as); 
   // tensor_double_print_self(tc);
        //tas->T

        //t->insert()
    //Vector *v=vas->create_v(vas->as,0,qua_copy(&d));

    //Vectors_Algebra_System_init(vas,10);
}
