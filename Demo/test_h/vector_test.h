#include<Vectors/Al_Vectors.h>
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
void test_vector()
{
	
    Vectors_Algebra_System*vas=(Vectors_Algebra_System*)malloc(sizeof(Vectors_Algebra_System));
    Vectors_Algebra_System_init(vas,100);
    vas->copy=qua_copy;vas->plus=qua_plus;vas->mult=qua_mult;
	double d,*d1;
	d=8;d1=(double*)qua_copy(&d);
    printf("d1:%lf\n",*d1);
    d=-10.1232;
    Vector*v=vas->create_v();
    vas->insert_v(vas->as,v,0,qua_copy(&d));
    d=213.3;
    vas->insert_v(vas->as,v,0,qua_copy(&d));
    d=4;
    vas->insert_v(vas->as,v,99,qua_copy(&d));
    vas->print_self(v);

    d=9;
    Vector*v1=vas->create_v();
    vas->insert_v(vas->as,v1,0,qua_copy(&d));
    d=-0.3;
    vas->insert_v(vas->as,v1,0,qua_copy(&d));
    d=10;
    vas->insert_v(vas->as,v1,9,qua_copy(&d));
    vas->print_self(v1);
    vas->v_plus(vas,v,v1);
    vas->print_self(v);

    //Vector *v=vas->create_v(vas->as,0,qua_copy(&d));

    //Vectors_Algebra_System_init(vas,10);
}
