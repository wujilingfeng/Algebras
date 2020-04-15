#include<Vectors/Al_Vectors.h>

void Field_Mult_Struct_Ele_init(Field_Mult_Struct_Ele*mse)
{
    mse->value=NULL;
    mse->base=NULL;
    mse->prop=NULL;

}
Field_Mult_Struct_Ele* create_field_mult_struct_ele(Algebra_Space* as,int id,void* value)
{
    Field_Mult_Struct_Ele *mse=(Field_Mult_Struct_Ele*)malloc(sizeof(Field_Mult_Struct_Ele));
    Field_Mult_Struct_Ele_init(mse);
    mse->base=as->get_kv(as,id);
    mse->value=value;
    return mse;
    
}

void Plus_Struct_Ele_init(Plus_Struct_Ele*pse)
{
    pse->value=(RB_Tree*)malloc(sizeof(RB_Tree));
    RB_Tree_init_int(pse->value);
    pse->prop=NULL;
}
//
static void zero_plus_struct_ele(Plus_Struct_Ele*q)
{
    RB_Trav *it=q->value->begin(q->value);
    Field_Mult_Struct_Ele* fmse=NULL;
    for(;it->it!=NULL;it->next(it))
    {
        fmse=(Field_Mult_Struct_Ele*)it->second(it);
        free(fmse->value);
        free(fmse);    
    }
    free(it);
    RB_Tree_free(q->value);
	q->value=(RB_Tree*)malloc(sizeof(RB_Tree));
	RB_Tree_init_int(q->value);
}

static void vector_mult(struct Vectors_Algebra_System*vas,void* re,Vector* q1,Vector*q2)
{
   	Field_Mult_Struct_Ele*fmse=NULL,*fmse1=NULL;
    void* temp=NULL;
    RB_int rbt,*rbt1;
    RB_Trav* it1=q1->value->begin(q1->value);
    for(;it1->it!=NULL;it1->next(it1))
    {

        fmse=(Field_Mult_Struct_Ele*)it1->second(it1);
        temp=vas->copy(fmse->value); 
        rbt.key=*((int*)(it1->first(it1)));
        rbt1=q2->value->find(q2->value,&rbt);
        if(rbt1!=NULL)
        {
            fmse1=(Field_Mult_Struct_Ele*)rbt1->value;
            vas->mult(temp,fmse1->value);
            vas->plus(re,temp);
        }
        free(temp);
    } 
    free(it1);
}
static int Vector_is_dual(struct Vectors_Algebra_System*vas,Vector* v)
{
    RB_Trav* it1=v->value->begin(v->value);
    for(;it1->it!=NULL;it1->next(it1))
    {
	    Field_Mult_Struct_Ele*fmse=(Field_Mult_Struct_Ele*)it1->second(it1);
        	return vas->dual_as->is_exist(vas->dual_as,fmse->base);
    }
    free(it1);
    return 1;
}
static Vector* Vector_create_()
{
    Vector *re=(Vector*)malloc(sizeof(Vector));
    Plus_Struct_Ele_init(re);
    return re;

}
static void Vector_print_self(Vector*v)
{
	
	RB_Trav *it=v->value->begin(v->value);
    Field_Mult_Struct_Ele* fmse=NULL;
    for(;it->it!=NULL;it->next(it))
    {
        fmse=(Field_Mult_Struct_Ele*)it->second(it);
       	printf("Id: %d value:%lf ",*((int*)(it->first(it))),*((double*)fmse->value));   
    }
    free(it);
	printf("\n");
}
static void Vector_insert_v(Algebra_Space*as,Vector*v,int id,void*value)
{
	Field_Mult_Struct_Ele* fmse=create_field_mult_struct_ele(as,id,value);
	RB_int rbt,*rbt1;
	rbt.key=id;
	rbt1=v->value->find(v->value,&rbt);
	if(rbt1==NULL)
	{
		rbt.value=(void*)fmse;
		v->value->insert(v->value,&rbt);
	}
	else
	{
		Field_Mult_Struct_Ele* fmse1=(Field_Mult_Struct_Ele*)(rbt1->value);
		free(fmse1->value);
		free(fmse1);
		v->value->erase(v->value,&rbt);		
		rbt.value=fmse;
		v->value->insert(v->value,&rbt);
	}

}
static void* Vector_get_kv(Vector*v,int id)
{
	RB_int rbt,*rbt1;
	rbt.key=id;
	rbt1=v->value->find(v->value,&rbt);
	if(rbt1==NULL)
	{
		return NULL;
	}
	Field_Mult_Struct_Ele* fmse=(Field_Mult_Struct_Ele*)(rbt1->value);
	return fmse->value;
}
void Vectors_Algebra_System_init(Vectors_Algebra_System*qas,int size)
{
	qas->is_dual=Vector_is_dual;
	Algebra_Space*as=(Algebra_Space*)malloc(sizeof(Algebra_Space));
	Algebra_Space_init(as);
    for(int i=0;i<size;i++)
    { 
       as->create_element(as);
    }
	qas->as=as;
	as=(Algebra_Space*)malloc(sizeof(Algebra_Space));
	Algebra_Space_init(as);
    for(int i=0;i<size;i++)
    { 
        as->create_element(as);
    }
	qas->dual_as=as;
    qas->el_op=(Algebra_Operation*)malloc(sizeof(Algebra_Operation));
	Algebra_Operation_init(qas->el_op);
    qas->v_mult=vector_mult;
    qas->v_plus=plus_plus_struct;
    qas->create_v=Vector_create_;
	qas->insert_v=Vector_insert_v;
	qas->print_self=Vector_print_self;
	qas->zero=zero_plus_struct_ele;
	qas->get_kv=Vector_get_kv;
	qas->mult=NULL;
	qas->plus=NULL;
    qas->copy=NULL;
	qas->prop=NULL;
}

void plus_mult_struct(Plus_Struct_Ele*pse,Field_Mult_Struct_Ele**mses,int size,Vectors_Algebra_System* qal)
{
	RB_int rbt,*rbt1;
	for(int i=0;i<size;i++)
	{
		rbt.key=mses[i]->base->id;
		rbt1=(RB_int*)pse->value->find(pse->value,&rbt);
		if(rbt1==NULL)
		{
            void* re=malloc(sizeof(Field_Mult_Struct_Ele));
            memmove(re,mses[i],sizeof(Field_Mult_Struct_Ele));
            ((Field_Mult_Struct_Ele*)re)->value=qal->copy(mses[i]->value);
	        rbt.value=re;
		    pse->value->insert(pse->value,&rbt);
		}
		else
		{
            qal->plus(((Field_Mult_Struct_Ele*)(rbt1->value))->value,mses[i]->value);
		}
	}

}
void plus_plus_struct(Vectors_Algebra_System*qal,Plus_Struct_Ele*pse,Plus_Struct_Ele* pse1)
{
    RB_Trav*it=pse1->value->begin(pse1->value);
    Field_Mult_Struct_Ele* mse=NULL;
    for(;it->it!=NULL;it->next(it))
    {
        mse=(Field_Mult_Struct_Ele*)(it->second(it)) ;
        plus_mult_struct(pse,&mse,1,qal); 
    }
    free(it);
}
