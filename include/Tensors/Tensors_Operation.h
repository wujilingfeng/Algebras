#include "Antisymmetric_Tensor.h"
#ifndef TENSORS_OPERATION_H
#define TENSORS_OPERATION_H
#ifdef __cplusplus
extern "C"{
#endif

//作用在zuo阶，交换l1和l2
void Tensor_tensors_exchange(Tensors_Algebra_System*tas,Tensor**ts,int zuo,int l1,int l2);

/*
void Tensor_Node_excahnge(Tensors_Algebra_System* tas,Tensor*t,Node** n,int zuo,int l1,int l2)
{
	Node* n1=n[l1],*n2=n[l2];

	Field_Mult_Struct_Ele* fmse=NULL;
	RB_mpz rbm;
	RB_init_mpz(&rbm);
	for(Node* it=n1;it!=NULL;it=(Node*)(it->Next))
	{
			fmse=(Field_Mult_Struct_Ele*)(it->value);
			mpz_set(rbm.key,fmse->base->id);
			t->value->erase(t->value,&rbm);
			Node* n3=fmse->base->els;
			for(int i=0;i<zuo;i++)
			{
				n3=(Node*)(n3->Next);
			}	
			n3->value=(void*)(tas->as->get_kv(tas->as,l2));
			Tensor_Product_Struct_getid(tas->as,fmse->base);
	}
	for(Node* it=n2;it!=NULL;it=(Node*)(it->Next))
	{
			fmse=(Field_Mult_Struct_Ele*)(it->value);
			mpz_set(rbm.key,fmse->base->id);
			t->value->erase(t->value,&rbm);
			Node* n3=fmse->base->els;
			for(int i=0;i<zuo;i++)
			{
				n3=(Node*)(n3->Next);
			}	
			n3->value=(void*)(tas->as->get_kv(tas->as,l1));
			Tensor_Product_Struct_getid(tas->as,fmse->base);
	}
	n[l1]=n2;
	n[l2]=n1;
	for(Node* it=n1;it!=NULL;it=(Node*)(it->Next))
	{
			fmse=(Field_Mult_Struct_Ele*)(it->value);
			mpz_set(rbm.key,fmse->base->id);

			rbm.value=(void*)fmse;
			t->value->insert(t->value,&rbm);
	}
	for(Node* it=n2;it!=NULL;it=(Node*)(it->Next))
	{
			fmse=(Field_Mult_Struct_Ele*)(it->value);
			mpz_set(rbm.key,fmse->base->id);
			rbm.value=(void*)fmse;
			t->value->insert(t->value,&rbm);
	}
	mpz_clear(rbm.key);

}*/
//l2行乘以value加到l1行上
void Tensor_tensors_plus_mult(Tensors_Algebra_System*tas,Tensor**ts,int zuo,int l1,int l2,void*value);

//l2行除以value加到l1行
void Tensor_tensors_plus_div(Tensors_Algebra_System*tas,Tensor**ts,int zuo,int l1,int l2,void*value);

/*
void Tensor_Node_plus(Tensors_Algebra_System*tas,Tensor*t,Node**n,int zuo,int l1,int l2)
{
	Node* n1=n[l1],*n2=n[l2];
	Field_Mult_Struct_Ele* fmse=NULL,*fmse1=NULL;
	int size=t->order(t);
	int *ids=(int*)malloc(sizeof(int)*size);
	for(Node*it=n2;it!=NULL;it=(Node*)(it->Next))
	{
		fmse=(Field_Mult_Struct_Ele*)(it->value);
		Node* it1=fmse->base->els;
		for(int j=0;j<size;j++)
		{
			ids[j]=((Algebra_Basic_Element*)(it1->value))->id;
			it1=(Node*)(it1->Next);

		}
		ids[zuo]=l1;
		void* value=tas->copy_from_double(1);
		tas->set_copy(value,fmse->value);
		if(tas->cmp_d(value,0)==0)
		{
			continue;
		}

		fmse1=create_field_mult_struct_ele(tas->as,ids,size,value);
		plus_mult_struct(tas,t,&fmse1,1);
		tas->free_data(value);
		Tensor_Product_Struct_free(fmse1->base);
		free(fmse1);

		//fmse=(Field_Mult_Struct_Ele*)malloc(sizeof(Field_Mult_Struct_Ele));
		//Field_Mult_Struct_Ele_init(fmse);
		//Tensor_Product_Struct *tps=(Tensor_Product_Struct*)		


	}
	free_node(n1);



}*/
//k l1
void Tensor_tensors_mult(Tensors_Algebra_System*tas,Tensor**ts,int zuo,int l1,void* value);
void Tensor_tensors_div(Tensors_Algebra_System*tas,Tensor**ts,int zuo,int l1,void*value);

/*
void Tensor_Cholesky(Tensors_Algebra_System*tas,Tensor*t,Tensor*L,Tensor*D)
{
    if(t->order(t)!=2)
    {
        return ;
    }

	int size=tas->as->elements->size;

	for(int i=0;i<size;i++)
	{

	}
	Node** n1=(Node**)malloc(sizeof(Node*)*size);
	//Node** n2=(Node**)malloc(sizeof(Node*)*size);
	memset(n1,0,sizeof(Node*)*size);
	//memset(n2,0,sizeof(Node*)*size);
	//mpz_t mt1,mt2,mt3,a;mpz_inits(mt1,mt2,mt3,a,NULL);
	int i=0;
	//mpz_set_ui(a,size);
	RB_Trav *it1=t->value->begin(t->value);
	Field_Mult_Struct_Ele* fmse=NULL;
	for(;it1->it!=NULL;it1->next(it1))
	{
		fmse=(Field_Mult_Struct_Ele*)(it1->second(it1));
		i=fmses_classi_dim(fmse,0);
	
		n1[i]=node_overlying(n1[i],fmse);
	}
	free(it1);


	//mpz_clear(mt1);mpz_clear(mt2);mpz_clear(a);mpz_clear(mt3);
	free(n1);
	//free(n2);	
}*/
Tensor* Tensor_inverse(Tensors_Algebra_System*tas,Tensor*t);


#ifdef __cplusplus
}
#endif


#endif
