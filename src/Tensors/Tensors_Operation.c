#include <Tensors/Tensors_Operation.h>
//作用在zuo阶，交换l1和l2
void Tensor_tensors_exchange(Tensors_Algebra_System*tas,Tensor**ts,int zuo,int l1,int l2)
{
	Tensor* t1=tas->T_create(),*t2=tas->T_create();
	Field_Mult_Struct_Ele*fmse=NULL;
	RB_Trav*it=ts[l1]->value->begin(ts[l1]->value);
	RB_mpz rbm;
	RB_init_mpz(&rbm);
	for(;it->it!=NULL;it->next(it))
	{
		fmse=(Field_Mult_Struct_Ele*)(it->second(it));
		Node* n3=fmse->base->els;
		for(int i=0;i<zuo;i++)
		{
			n3=(Node*)(n3->Next);
		}	
		n3->value=(void*)(tas->as->get_kv(tas->as,l2));

		Tensor_Product_Struct_getid(tas->as,fmse->base);
		mpz_set(rbm.key,fmse->base->id);
		rbm.value=fmse;
		t1->value->insert(t1->value,&rbm);
	}
	free(it);
	it=ts[l2]->value->begin(ts[l2]->value);
	for(;it->it!=NULL;it->next(it))
	{
		fmse=(Field_Mult_Struct_Ele*)(it->second(it));
		Node* n3=fmse->base->els;
		for(int i=0;i<zuo;i++)
		{
			n3=(Node*)(n3->Next);
		}	
		n3->value=(void*)(tas->as->get_kv(tas->as,l1));

		Tensor_Product_Struct_getid(tas->as,fmse->base);
		mpz_set(rbm.key,fmse->base->id);
		rbm.value=fmse;
		t2->value->insert(t2->value,&rbm);
	}
	free(it);	
	RB_Tree_free(ts[l1]->value);
	free(ts[l1]);
	RB_Tree_free(ts[l2]->value);
	free(ts[l2]);
	ts[l1]=t2;
	ts[l2]=t1;
}
//l2行乘以value加到l1行上
void Tensor_tensors_plus_mult(Tensors_Algebra_System*tas,Tensor**ts,int zuo,int l1,int l2,void*value)
{
	Field_Mult_Struct_Ele* fmse=NULL,*fmse1=NULL;
	RB_Trav *it=ts[l2]->value->begin(ts[l2]->value);
	void* value1=tas->copy_from_double(1);
	//int size=tas->as->elements->size;
	//int *ids=(int*)malloc(sizeof(int)*size);
	for(;it->it!=NULL;it->next(it))
	{
		fmse=(Field_Mult_Struct_Ele*)(it->second(it));
		tas->set_copy(value1,value);
		tas->mult(value1,fmse->value);
		int i=0;
		Node* n=NULL;
		for(Node* n_it=fmse->base->els;n_it!=NULL;n_it=(Node*)(n_it->Next))
		{
			n=node_pushback(n,n_it->value);
			if(i==zuo)
			{
				n->value=tas->as->get_kv(tas->as,l1);
			}
			i++;
		}

		fmse1=(Field_Mult_Struct_Ele*)malloc(sizeof(Field_Mult_Struct_Ele));
		Field_Mult_Struct_Ele_init(fmse1);

		Tensor_Product_Struct* tps=(Tensor_Product_Struct*)malloc(sizeof(Tensor_Product_Struct));
		Tensor_Product_Struct_init(tps);
		//fmse1=create_field_mult_struct_ele(tas->as,value1);	
		fmse1->base=tps;
	
		fmse1->value=value1;
		fmse->order=i;
		tps->els=node_reverse(n);
		Tensor_Product_Struct_getid(tas->as,tps);
		plus_mult_struct(tas,ts[l1],&fmse1,1);
		Tensor_Product_Struct_free(tps);

		free(fmse1);


	}
	tas->free_data(value1);
	free(it);

}
//l2行除以value加到l1行
void Tensor_tensors_plus_div(Tensors_Algebra_System*tas,Tensor**ts,int zuo,int l1,int l2,void*value)
{

	Field_Mult_Struct_Ele* fmse=NULL,*fmse1=NULL;
	RB_Trav *it=ts[l2]->value->begin(ts[l2]->value);
	void* value1=tas->copy_from_double(1);
	//int size=tas->as->elements->size;
	//int *ids=(int*)malloc(sizeof(int)*size);
	for(;it->it!=NULL;it->next(it))
	{
		fmse=(Field_Mult_Struct_Ele*)(it->second(it));
		tas->set_copy(value1,fmse->value);
		tas->div(value1,value);
		int i=0;
		Node* n=NULL;
		for(Node* n_it=fmse->base->els;n_it!=NULL;n_it=(Node*)(n_it->Next))
		{
			n=node_pushback(n,n_it->value);
			if(i==zuo)
			{
				n->value=tas->as->get_kv(tas->as,l1);
			}
			i++;
		}

		fmse1=(Field_Mult_Struct_Ele*)malloc(sizeof(Field_Mult_Struct_Ele));
		Field_Mult_Struct_Ele_init(fmse1);

		Tensor_Product_Struct* tps=(Tensor_Product_Struct*)malloc(sizeof(Tensor_Product_Struct));
		Tensor_Product_Struct_init(tps);
		//fmse1=create_field_mult_struct_ele(tas->as,value1);	
		fmse1->base=tps;
	
		fmse1->value=value1;
		fmse->order=i;
		tps->els=node_reverse(n);
		Tensor_Product_Struct_getid(tas->as,tps);
		plus_mult_struct(tas,ts[l1],&fmse1,1);
		Tensor_Product_Struct_free(tps);
		free(fmse1);
	}
	tas->free_data(value1);
	free(it);

}
/*
//k l1
void Tensor_tensors_mult(Tensors_Algebra_System*tas,Tensor**ts,int zuo,int l1,void* value)
{
	Field_Mult_Struct_Ele* fmse=NULL;
	RB_Trav* it=ts[l1]->value->begin(ts[l1]->value);
	for(;it->it!=NULL;it->next(it))
	{
		fmse=(Field_Mult_Struct_Ele*)(it->second(it));
		tas->mult(fmse->value,value);
	}
	free(it);	
}
void Tensor_tensors_div(Tensors_Algebra_System*tas,Tensor**ts,int zuo,int l1,void*value)
{
	Field_Mult_Struct_Ele* fmse=NULL;
	RB_Trav* it=ts[l1]->value->begin(ts[l1]->value);
	for(;it->it!=NULL;it->next(it))
	{
		fmse=(Field_Mult_Struct_Ele*)(it->second(it));
		tas->div(fmse->value,value);
	}
	free(it);	
}*/
Tensor* Tensor_inverse(Tensors_Algebra_System*tas,Tensor*t)
{
    if(t->order(t)!=2)
    {
    	printf("order is not 2\n");
        return NULL;
    }

    int size=tas->as->elements->size;
    Tensor **re=(Tensor**)malloc(sizeof(Tensor*)*size);
    int ids[2];
    for(int i=0;i<size;i++)
    {
        ids[0]=ids[1]=i;
        re[i]=tas->T_create();
        re[i]->insert(tas->as,re[i],ids,2,tas->copy_from_double(1));
    }
    Tensor** ts=(Tensor**)malloc(sizeof(Tensor*)*size);


    int i=0;
    for(i=0;i<size;i++)
    {
        ts[i]=tas->T_create();
    }

    RB_Trav *it1=t->value->begin(t->value);
    Field_Mult_Struct_Ele* fmse=NULL;
    for(;it1->it!=NULL;it1->next(it1))
    {
        fmse=(Field_Mult_Struct_Ele*)(it1->second(it1));
        i=fmses_classi_dim(fmse,0);
        plus_mult_struct(tas,ts[i],&fmse,1);
    }
    free(it1);

    void *value=NULL,*value1=tas->copy_from_double(1),*value2=tas->copy_from_double(-1);
    for(i=0;i<size;i++)
    {
        ids[0]=i;ids[1]=i;
        int j=0;
        value=NULL;
        for(j=i;j<size;j++)
        {
            ids[0]=j;
            value=Tensor_get_value(tas->as,ts[j],ids,2);
            if(value!=NULL)
            {
                break;
            }   
        }
        if(value==NULL)
        {
      
            continue;
        }
        if(j!=i)
        {
            Tensor_tensors_exchange(tas,ts,0,i,j);
            Tensor_tensors_exchange(tas,re,0,i,j);
        }
      
        tas->set_copy(value1,value);
        Tensor_div_field_(tas,ts[i],value1);
        Tensor_div_field_(tas,re[i],value1);
        //Tensor_tensors_div(tas,ts,0,i,value1);
        //Tensor_tensors_div(tas,re,0,i,value1);
        for(j=0;j<size;j++)
        {
            if(j==i)
            {continue;}
            ids[0]=j;ids[1]=i;
            value=Tensor_get_value(tas->as,ts[j],ids,2);

            if(value==NULL)
            {
                continue;
            }
            tas->set_copy(value1,value);
            tas->mult(value1,value2);
            Tensor_tensors_plus_mult(tas,ts,0,j,i,value1);
            Tensor_tensors_plus_mult(tas,re,0,j,i,value1);
   
        }   
    }   
    tas->free_data(value1);
    tas->free_data(value2);
    
    Tensor*re1=tas->T_create();
    for(i=0;i<size;i++)
    {
        tas->T_plus(tas,re1,re[i]);
        tas->T_free(tas,ts[i]);
        tas->T_free(tas,re[i]);

    }
    free(re);free(ts);
    return re1;
}
