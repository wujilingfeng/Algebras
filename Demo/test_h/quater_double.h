#include<Quaternions/Al_Quaternions.h>
//适用于域为double类型
static void q_print_self(Quaternion* q)
{
    Field_Mult_Struct_Ele*fmse=NULL;
    RB_Trav* it=q->value->begin(q->value);
    char na[]=" ijk";
    int id=0;
    for(;it->it!=NULL;it->next(it))
    {
        fmse=(Field_Mult_Struct_Ele*)it->second(it);
        id=*((int*)(it->first(it)));
        printf("%lf%c",*((double*)(fmse->value)),na[id]);
    }
    printf("\n");
    free(it);
}
void qua_mult(void*p1,void*p2)
{
    double*q1=(double*)p1,*q2=(double*)p2;
    *q1=(*q1)*(*q2);
}
void qua_plus(void*p1,void*p2)
{
    double*q1=(double*)p1,*q2=(double*)p2;
    *q1=(*q1)+(*q2);

}
void *qua_copy(void*tar)
{
    void* re=malloc(sizeof(double));
    memmove(re,tar,sizeof(double));
    return re;

}
void test_quaternion()
{
    Quaternion_Algebra_System* qas=(Quaternion_Algebra_System*)malloc(sizeof(Quaternion_Algebra_System));
    Quaternion_Algebra_System_init(qas);
    qas->mult=qua_mult;
    qas->plus=qua_plus;
    qas->copy=qua_copy;
    Quaternion* q=qas->get_str(qas,(char*)"-2.0-8.9i-93.09k+8i");
    Quaternion* q1=qas->get_str(qas,(char*)"-2.0+0.9i+93.09k");
    qas->print_self(q); 
    qas->print_self(q1);
    qas->q_mult(q,q1,qas);
    qas->print_self(q);
    
}

