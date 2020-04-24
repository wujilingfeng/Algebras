#include<Tensors/Al_Tensors.h>

void Field_Mult_Struct_Ele_init(Field_Mult_Struct_Ele*mse)
{
    mse->value=NULL;
    mse->base=NULL;
	mse->iters=NULL;
    mse->prop=NULL;
}
Field_Mult_Struct_Ele* create_field_mult_struct_ele(Algebra_Space* as,int* ids,int size,void* value)
{
    Field_Mult_Struct_Ele *mse=(Field_Mult_Struct_Ele*)malloc(sizeof(Field_Mult_Struct_Ele));
    Field_Mult_Struct_Ele_init(mse);
	Tensor_Product_Struct* tps=(Tensor_Product_Struct*)malloc(sizeof(Tensor_Product_Struct));
	Tensor_Product_Struct_init(tps);
	Algebra_Basic_Element*base=NULL;
	for(int i=0;i<size;i++)
	{
		base=as->get_kv(as,ids[i]);
		tps->els=node_pushback(tps->els,base);
	}
    tps->els=node_reverse(tps->els);
	Tensor_Product_Struct_getid(as,tps);
	mse->base=tps;
    mse->value=value;
    return mse;
}

//加法单位元化
void zero_plus_struct_ele(struct Plus_Struct_Ele*q)
{

    RB_Trav *it=q->value->begin(q->value);
    Field_Mult_Struct_Ele* fmse=NULL;
    for(;it->it!=NULL;it->next(it))
    {
        fmse=(Field_Mult_Struct_Ele*)it->second(it);
//fmse->value有内存泄漏
        free(fmse->value);
	Tensor_Product_Struct_free(fmse->base);
	//mpz_clear(fmse->base->id);
	//free_node(fmse->base->els);
        free(fmse);    
    }

    free(it);

    RB_Tree_free(q->value);
	q->value=(RB_Tree*)malloc(sizeof(RB_Tree));
	RB_Tree_init_mpz(q->value);
}

static void Tensor_insert_ele(Algebra_Space*as,struct Tensor*t,int* ids,int size,void*value)
{

	Field_Mult_Struct_Ele* fmse=create_field_mult_struct_ele(as,ids,size,value);
	
	RB_mpz rbm,*rbm1;
	RB_init_mpz(&rbm);
	mpz_set(rbm.key,fmse->base->id);
	rbm1=(RB_mpz*)t->value->find(t->value,&rbm);
	if(rbm1==NULL)
	{
		rbm.value=(void*)fmse;
		t->value->insert(t->value,&rbm);
	}
	else
	{
		Field_Mult_Struct_Ele* fmse1=(Field_Mult_Struct_Ele*)(rbm1->value);
		free(fmse1->value);
		Tensor_Product_Struct_free(fmse1->base);
		free(fmse1);
		t->value->erase(t->value,&rbm);		
		rbm.value=fmse;
		t->value->insert(t->value,&rbm);
	}
	mpz_clear(rbm.key);

}
static void* Tensor_get_value(Algebra_Space*as,Tensor* t,int *ids,int size)
{
	int size1=as->elements->size;
	mpz_t a,b,c;
	mpz_inits(a,b,c,NULL);
	mpz_set_ui(a,size1);
	for(int i=0;i<size;i++)
	{
		mpz_pow_ui(b,a,size-i-1);
		mpz_mul_ui(b,b,ids[i]);
		mpz_add(c,c,b);
	}
	
	RB_mpz rbm,*rbm1;
	RB_init_mpz(&rbm);
	mpz_set(rbm.key,c);
	rbm1=(RB_mpz*)t->value->find(t->value,&rbm);
	if(rbm1==NULL)
	{return NULL;}
	else
	{
		return ((Field_Mult_Struct_Ele*)(rbm1->value))->value;
	}

	mpz_clear(rbm.key);
	mpz_clear(a);mpz_clear(b);mpz_clear(c);
}
void Plus_Struct_Ele_init(Plus_Struct_Ele*pse)
{
    pse->value=(RB_Tree*)malloc(sizeof(RB_Tree));
    RB_Tree_init_mpz(pse->value);
	pse->zero=zero_plus_struct_ele;
	pse->insert=Tensor_insert_ele;
	pse->get_value=Tensor_get_value;
    pse->prop=NULL;
}

//
static Tensor* Tensor_create_()
{
    Tensor *re=(Tensor*)malloc(sizeof(Tensor));
    Plus_Struct_Ele_init(re);
    return re;

}
/*
static int Tensor_is_dual(struct Tensors_Algebra_System*tas,Tensor* t)
{
    RB_Trav* it1=t->value->begin(t->value);
	int re=0;
    for(;it1->it!=NULL;it1->next(it1))
    {
	    Field_Mult_Struct_Ele*fmse=(Field_Mult_Struct_Ele*)it1->second(it1);
		re=tas->dual_as->is_exist(tas->dual_as,fmse->base);
    }
    free(it1);
    return re;
}*/
static void Tensor_free(struct Tensors_Algebra_System*tas ,Tensor*t)
{
	 RB_Trav *it=t->value->begin(t->value);
	Field_Mult_Struct_Ele* fmse=NULL;
	for(;it->it!=NULL;it->next(it))
	{
		fmse=(Field_Mult_Struct_Ele*)it->second(it);
		tas->free_data(fmse->value);
       
		Tensor_Product_Struct_free(fmse->base);
		free(fmse);    
	}

	free(it);

	RB_Tree_free(t->value);
	free(t);
	

}
void Tensors_Algebra_System_init(Tensors_Algebra_System*tas,int size)
{
	Algebra_Space*as=(Algebra_Space*)malloc(sizeof(Algebra_Space));
	Algebra_Space_init(as);
	for(int i=0;i<size;i++)
	{ 
		as->create_element(as);
	}
	tas->as=as;
	as=(Algebra_Space*)malloc(sizeof(Algebra_Space));
	Algebra_Space_init(as);
	for(int i=0;i<size;i++)
	{ 
		as->create_element(as);
	}
	tas->dual_as=as;
	//tas->copy=NULL;
	tas->mult=NULL;
	tas->plus=NULL;
	tas->copy_from_double=NULL;
	tas->set_copy=NULL;
	tas->T_plus=plus_plus_struct;
	tas->T_create=Tensor_create_;
	tas->T_free=Tensor_free;
	tas->T_norm=Tensor_norm;
	tas->T_product=W_Tensor_Product;
	tas->T_inner_product=W_Tensor_Inner_Product;
	tas->prop=NULL;
}
void plus_mult_struct(Tensors_Algebra_System* tal,Plus_Struct_Ele*pse,Field_Mult_Struct_Ele**mses,int size)
{
	RB_mpz rbm,*rbm1;
	RB_init_mpz(&rbm);
	for(int i=0;i<size;i++)
	{
		mpz_set(rbm.key,mses[i]->base->id);
		rbm1=(RB_mpz*)pse->value->find(pse->value,&rbm);
		if(rbm1==NULL)
		{
            		Field_Mult_Struct_Ele* re=malloc(sizeof(Field_Mult_Struct_Ele));
			Field_Mult_Struct_Ele_init(re);
			re->value=tal->copy_from_double(1);
			tal->set_copy(re->value,mses[i]->value);
            		//re->value=tal->copy(mses[i]->value);
			Tensor_Product_Struct* tps=(Tensor_Product_Struct*)malloc(sizeof(Tensor_Product_Struct));
			Tensor_Product_Struct_init(tps);
			tps->els=node_copy(mses[i]->base->els);
			mpz_set(tps->id,mses[i]->base->id);
			//Tensor_Product_Struct_getid(tal->as,tps);
			re->base=tps;
	        	rbm.value=re;
		    	pse->value->insert(pse->value,&rbm);
		}
		else
		{
            		tal->plus(((Field_Mult_Struct_Ele*)(rbm1->value))->value,mses[i]->value);
		}
	}
	mpz_clear(rbm.key);

}

void plus_plus_struct(Tensors_Algebra_System*tal,Plus_Struct_Ele*pse,Plus_Struct_Ele* pse1)
{
    RB_Trav*it=pse1->value->begin(pse1->value);
    Field_Mult_Struct_Ele* mse=NULL;
    for(;it->it!=NULL;it->next(it))
    {
        mse=(Field_Mult_Struct_Ele*)(it->second(it)) ;
        plus_mult_struct(tal,pse,&mse,1); 
    }
    free(it);
}
Tensor* W_Tensor_Product(struct Tensors_Algebra_System*tas,Tensor*t1,Tensor*t2)
{
	Tensor*re=tas->T_create();
	RB_Trav *it1=t1->value->begin(t1->value);
	Field_Mult_Struct_Ele* fmse=NULL,*fmse1=NULL;
	Field_Mult_Struct_Ele *mse=NULL;
	for(;it1->it!=NULL;it1->next(it1))
	{
		fmse=(Field_Mult_Struct_Ele*)(it1->second(it1));
		RB_Trav* it2=t2->value->begin(t2->value);
		for(;it2->it!=NULL;it2->next(it2))
		{

			fmse1=(Field_Mult_Struct_Ele*)(it2->second(it2));
			void*value=tas->copy_from_double(1);
			tas->set_copy(value,fmse->value);
			//void* value=tas->copy(fmse->value);
			tas->mult(value,fmse1->value);
			mse=(Field_Mult_Struct_Ele*)malloc(sizeof(Field_Mult_Struct_Ele));
    			Field_Mult_Struct_Ele_init(mse);
			Tensor_Product_Struct* tps=(Tensor_Product_Struct*)malloc(sizeof(Tensor_Product_Struct));
			Tensor_Product_Struct_init(tps);
			mse->value=value;mse->base=tps;

			tps->els=node_splicing(fmse->base->els,fmse1->base->els);
			Tensor_Product_Struct_getid(tas->as,tps);
			plus_mult_struct(tas,re,&mse,1);		
		}  
		free(it2);
	}
	free(it1);

	return re;
}
//张量内积运算
void* W_Tensor_Inner_Product(struct Tensors_Algebra_System*tas,Tensor*t1,Tensor*t2)
{
	void*value=tas->copy_from_double(0),*value1=tas->copy_from_double(1);
	RB_mpz rbm,*rbm1=NULL;
	RB_init_mpz(&rbm);
	Field_Mult_Struct_Ele* fmse=NULL;
	RB_Trav* it=t1->value->begin(t1->value);
	for(;it->it!=NULL;it->next(it))
	{
		fmse=(Field_Mult_Struct_Ele*)(it->second(it));
		mpz_set(rbm.key,fmse->value);
		tas->set_copy(value1,fmse->value);
		rbm1=(RB_mpz*)t2->value->find(t2->value,&rbm); 
		if(rbm1!=NULL)
		{
			fmse=(Field_Mult_Struct_Ele*)(rbm1->value);
			tas->mult(value1,fmse->value);
			tas->plus(value,value1);
			
		}  
		//rbm1=t2->find(t2,);
	}    
	free(it);
	mpz_clear(rbm.key);
	tas->free_data(value1);	
	return value;
}

static Node* Contraction_chuli_splicing(Node*n1,Node* n2,int zuo1,int zuo2)
{
	Node* re=n1;
	Node* nit=n1;
	for(int i=0;i<zuo1;i++)
	{
		nit=(Node*)(nit->Next);
	}
	Node* nit1=NULL;
	if(nit->Prev!=NULL)
	{
		nit1=(Node*)(nit->Prev);
		nit1->Next=(void*)(nit->Next);
		
	}
	else
	{
		re=(Node*)(nit->Next);
	}
	if(nit->Next!=NULL)
	{
		nit1=(Node*)(nit->Next);
		nit1->Prev=(void*)(nit->Prev);
	}
	free(nit);
	Node* re1=n2;
	nit=n2;
	for(int i=0;i<zuo2;i++)
	{
		nit=(Node*)(nit->Next);
	}
	nit1=NULL;
	if(nit->Prev!=NULL)
	{
		nit1=(Node*)(nit->Prev);
		nit1->Next=(void*)(nit->Next);
	}
	else
	{
		re1=(Node*)(nit->Next);
	}
	if(nit->Next!=NULL)
	{
		nit1=(Node*)(nit->Next);
		nit1->Prev=(void*)(nit->Prev);
	}
	free(nit);
	
	if(re==NULL)
	{return re1;}
	else if(re1==NULL)
	{
		return re;
	}
	else
	{
		Node* l3=node_reverse(re);
		l3->Next=(void*)re1;
		re1->Prev=(void*)l3;
		return re;
	}
	return re;
}
static void fmses_tensor_plus_node(struct Tensors_Algebra_System*tas,Tensor* t,Node*n1,Node* n2,int zuo1,int zuo2)
{
	if(n1==NULL||n2==NULL)
	{	
		return;
	}
	RB_mpz rbm,*rbm1;
	RB_init_mpz(&rbm);
	Field_Mult_Struct_Ele *fmse1=NULL,*fmse2=NULL;

	for(Node*nit1=n1;nit1!=NULL;nit1=(Node*)(nit1->Next))
	{
		fmse1=(Field_Mult_Struct_Ele*)(nit1->value);
		for(Node* nit2=n2;nit2!=NULL;nit2=(Node*)(nit2->Next))
		{
			fmse2=(Field_Mult_Struct_Ele*)(nit2->value);
			Tensor_Product_Struct* tps=(Tensor_Product_Struct*)malloc(sizeof(Tensor_Product_Struct));
			Tensor_Product_Struct_init(tps);
			tps->els=Contraction_chuli_splicing(node_copy(fmse1->base->els),node_copy(fmse2->base->els),zuo1,zuo2);
			Tensor_Product_Struct_getid(tas->as,tps);
			mpz_set(rbm.key,tps->id);
			rbm1=(RB_mpz*)t->value->find(t->value,&rbm);
			if(rbm1==NULL)
			{
				Field_Mult_Struct_Ele* fmse=malloc(sizeof(Field_Mult_Struct_Ele));
				Field_Mult_Struct_Ele_init(fmse);
				void* value=tas->copy_from_double(1);
				tas->set_copy(value,fmse1->value);
				//void *value=tas->copy(fmse1->value);
				tas->mult(value,fmse2->value);

				fmse->value=value;

				fmse->base=tps;
				mpz_set(rbm.key,tps->id);

				rbm.value=(void*)fmse;
				fmse=(Field_Mult_Struct_Ele*)(rbm.value);

				t->value->insert(t->value,&rbm);
			}
			else
			{
				Tensor_Product_Struct_free(tps);
				void*value=tas->copy_from_double(1);
				tas->set_copy(value,fmse1->value);
				//void *value=tas->copy(fmse1->value);
				tas->mult(value,fmse2->value);
				tas->plus(((Field_Mult_Struct_Ele*)(rbm1->value))->value,value);
				tas->free_data(value);
			}
		}
	}
	
	mpz_clear(rbm.key);
}
static int fmses_classi_dim(Field_Mult_Struct_Ele*fmse,int zuo1)
{
	Node* nit=fmse->base->els;
	for(int i=0;i<zuo1;i++)
	{
		nit=(Node*)(nit->Next);
	}
	return ((Algebra_Basic_Element*)(nit->value))->id;

}
/*
static Field_Mult_Struct_Ele*fmses_sub_dim(Tensors_Algebra_System*tas,Field_Mult_Struct_Ele*fmse,int zuo1,int *i)
{
	Field_Mult_Struct_Ele*re=(Field_Mult_Struct_Ele*)malloc(sizeof(Field_Mult_Struct_Ele));
	Field_Mult_Struct_Ele_init(re);
	re->value=tas->copy(fmse->value);
	Tensor_Product_Struct*tps=(Tensor_Product_Struct*)malloc(sizeof(Tensor_Product_Struct));
	Tensor_Product_Struct_init(tps);
	tps->els=node_copy(fmse->base->els);
	re->base=tps;
	Node* nit=tps->els;
	for(int i=0;i<zuo1;i++)
	{
		
		
		nit=(Node*)(nit->Next);
	}
	*i=((Algebra_Basic_Element*)(nit->value))->id;
	Node* nit1=NULL;
	if(nit->Prev!=NULL)
	{
		nit1=(Node*)(nit->Prev);
		nit1->Next=(void*)(nit->Next);
		
	}
	if(nit->Next!=NULL)
	{
		nit1=(Node*)(nit->Next);
		nit1->Prev=(void*)(nit->Prev);
	}
	free(nit);
	
	return re;
}*/

//张量的缩并（二阶张量等价矩阵相乘）
Tensor*W_Tensor_Contraction(struct Tensors_Algebra_System*tas,Tensor*t1,Tensor*t2,int zuo1,int zuo2)
{
	int size=tas->as->elements->size;
	Node** n1=(Node**)malloc(sizeof(Node*)*size);
	Node** n2=(Node**)malloc(sizeof(Node*)*size);
	memset(n1,0,sizeof(Node*)*size);memset(n2,0,sizeof(Node*)*size);
	Tensor *re=tas->T_create();
	mpz_t mt1,mt2,mt3,a;mpz_inits(mt1,mt2,mt3,a,NULL);int i=0;
	mpz_set_ui(a,size);
	RB_Trav *it1=t1->value->begin(t1->value);
	Field_Mult_Struct_Ele* fmse=NULL;
	for(;it1->it!=NULL;it1->next(it1))
	{
		fmse=(Field_Mult_Struct_Ele*)(it1->second(it1));
		i=fmses_classi_dim(fmse,zuo1);
		/*for(Node* nit=fmse->base->els;nit!=NULL;nit=(Node*)(nit->Next))
		{
			printf("%d  ",((Algebra_Basic_Element*)(nit->value))->id);
		}
		printf("id:%d\n",i);*/
		n1[i]=node_overlying(n1[i],fmse);
	}
	free(it1);
	RB_Trav *it2=t2->value->begin(t2->value);
	for(;it2->it!=NULL;it2->next(it2))
	{
		fmse=(Field_Mult_Struct_Ele*)(it2->second(it2));
		i=fmses_classi_dim(fmse,zuo2);

		n2[i]=node_overlying(n2[i],fmse);
	}
	free(it2);
	for(int i=0;i<size;i++)
	{

		fmses_tensor_plus_node(tas,re,n1[i],n2[i],zuo1,zuo2);
	}
	mpz_clear(mt1);mpz_clear(mt2);mpz_clear(a);mpz_clear(mt3);
	

	
	return re;
}
void* Tensor_norm(struct Tensors_Algebra_System*tas,Tensor*t)
{
	void* value=tas->copy_from_double(0);
	void* value1=tas->copy_from_double(1);
RB_Trav*it=t->value->begin(t->value);
    Field_Mult_Struct_Ele* mse=NULL;
    for(;it->it!=NULL;it->next(it))
    {
        mse=(Field_Mult_Struct_Ele*)(it->second(it));
	tas->set_copy(value1,mse->value);
	tas->mult(value1,value1);
	
	tas->plus(value,value1);
	//tas->mult(v)
	//mpf_pow_ui(value1,mse->value,2);
	//mpf_add(value,value,value1);

    }
    free(it);
	tas->free_data(value1);
	return value;
}
/*
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


*/
