#include<Tensors/Antisymmetric_Tensor.h>
#include<Tensors/Al_Tensors.h>

static void Tensor_double_mult(void* p1,void *p2)
{
    double*q1=(double*)p1;
    double*q2=(double*)p2;
    *q1=(*q1)*(*q2);
    
}
static void  Tensor_double_plus(void*p1,void*p2)
{
	double*q1=(double*)p1;
    double*q2=(double*)p2;
   	*q1=(*q1)+(*q2); 
}
void Tensor_double_div(void* p1,void*p2)
{
	double*q1=(double*)p1;
    double*q2=(double*)p2;
    *q1=(*q1)/(*q2);
}
static int Tensor_double_cmp(void*p1,void*p2)
{
	double*q1=(double*)p1;
    double*q2=(double*)p2;	
    if((*q1)>(*q2))
    {
    	return 1;
    }
    else if((*q1)<(*q2))
    {
    	return -1;
    }
    return 0;

}
static int Tensor_double_cmp_d(void*p1,double d)
{
    double*q1=(double*)p1;
    if((*q1)>d)
    {
    	return 1;
    }
    else if((*q1)<d)
    {
    	return -1;
    }
  //  mpf_t q2;
    //mpf_inits();
    return 0;

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
static void Tensor_double_set_copy(void *p1,void*p2)
{
	double*q1=(double*)p1;
    double*q2=(double*)p2;
	*q1=*q2;

}
static void Tensor_double_free(void*p)
{
 
    free(p);
}
static void* Tensor_double2_double(double d)
{    
    double*re=(double*)malloc(sizeof(double));
 	*re=d;
    return (void*)re;
}
/*
void tensor_double_print_self(Tensor* t)
{
    printf("************************************\n");
	printf("order:%d\n",t->order(t));
    RB_Trav *it=t->value->begin(t->value);
    for(;it->it!=NULL;it->next(it))
    {
        gmp_printf("id:%Zd \n",(__mpz_struct*)it->first(it));
        Field_Mult_Struct_Ele* fmse=(Field_Mult_Struct_Ele*)it->second(it);
        gmp_printf("value:%lf\n",*((double*)(fmse->value)));
        for(Node* it1=fmse->base->els;it1!=NULL;it1=(Node*)it1->Next)
        {
        
            printf("%d  ",((Algebra_Basic_Element*)(it1->value))->id);
        }
        printf("\n");
    }
    free(it);
 
   // printf("************************************\n");
    
}*/
void Tensors_Algebra_System_double_init(Tensors_Algebra_System*tas,int size)
{
    Tensors_Algebra_System_init(tas,size);
    tas->mult=Tensor_double_mult;
    tas->plus=Tensor_double_plus;
    tas->div=Tensor_double_div;
   // tas->copy=Tensor_mpf_copy;
    tas->copy_from_double=Tensor_double2_double;
	tas->set_copy=Tensor_double_set_copy;
    tas->free_data=Tensor_double_free;
    tas->cmp=Tensor_double_cmp;
    tas->cmp_d=Tensor_double_cmp_d;


}
