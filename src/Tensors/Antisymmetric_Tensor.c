#include<Tensors/Antisymmetric_Tensor.h>
static int Tensor_fac_(Node* n1,Node*n2)
{
    Node*re=NULL;
    for(Node*it=n1;it!=NULL;it=(Node*)(it->Next))
    {
        re=node_find(n2,it->value);
        if(re!=NULL)
        {
            return 0;
        }
    
    }
    return 1;
}
static Node* Tensor_wedge_chuli_(Node*n,int *nixu)
{
    int size=node_size(n);
    if(size==0)
    {return NULL;}
    Algebra_Basic_Element* abe=NULL,*abe1=NULL;
    void** re1=(void**)malloc(sizeof(void*)*size);
    Node* it=n;
    for(int i=0;i<size;i++)
    {
        re1[i]=it->value;
        abe=(Algebra_Basic_Element*)re1[i];

        it=(Node*)(it->Next);
    }
    *nixu=0;
    for(int i=size-1;i>=0;i--)
    {
        abe=(Algebra_Basic_Element*)re1[i];
        int k=0;
        for(int j=i+1;j<size;j++)
        { 
            abe1=(Algebra_Basic_Element*)re1[j];
            if(abe1->id>abe->id)
            {
                break;
            }
            else
            {
                k++;
            }
        }
        for(int l=0;l<k;l++)
        {
            void* temp=re1[l+i];
            re1[l+i]=re1[l+i+1];
            re1[l+i+1]=temp;        
        }

        *nixu=*nixu+k;
    }
    Node* n1=NULL;
    for(int i=0;i<size;i++)
    {
        n1=node_pushback(n1,re1[i]);
    }

    free(re1);
    return node_reverse(n1);

}
Tensor* Tensor_Wedge_(struct Tensors_Algebra_System*tas,Tensor*t1,Tensor*t2)
{
    Tensor* re=tas->T_create();
    RB_Trav *it1=t1->value->begin(t1->value);
	Field_Mult_Struct_Ele* fmse=NULL,*fmse1=NULL,*mse=NULL;
	for(;it1->it!=NULL;it1->next(it1))
	{
		fmse=(Field_Mult_Struct_Ele*)(it1->second(it1));
		RB_Trav* it2=t2->value->begin(t2->value);
		for(;it2->it!=NULL;it2->next(it2))
		{
			fmse1=(Field_Mult_Struct_Ele*)(it2->second(it2));
			int fac=Tensor_fac_(fmse->base->els,fmse1->base->els);
			if(fac==0)
			{continue;}
			void*value=tas->copy_from_double(1);
			tas->set_copy(value,fmse->value);
			//void* value=tas->copy(fmse->value);
			tas->mult(value,fmse1->value);
			mse=(Field_Mult_Struct_Ele*)malloc(sizeof(Field_Mult_Struct_Ele));
    		Field_Mult_Struct_Ele_init(mse);
			Tensor_Product_Struct* tps=(Tensor_Product_Struct*)malloc(sizeof(Tensor_Product_Struct));
			Tensor_Product_Struct_init(tps);
			mse->value=value;mse->base=tps;
            int flag;Node* nit=node_splicing(fmse->base->els,fmse1->base->els);
            mse->order=fmse->order+fmse1->order;
            tps->els=Tensor_wedge_chuli_(nit,&flag);
            if(flag%2==1)
            {
                void* value1=tas->copy_from_double(-1);
                tas->mult(value,value1);
                tas->free_data(value1);
            }
            free_node(nit);
			Tensor_Product_Struct_getid(tas->as,tps);

			plus_mult_struct(tas,re,&mse,1);
            Tensor_Product_Struct_free(mse->base);
            tas->free_data(mse->value);		

		}  
		free(it2);
	}
	free(it1);    
    return re;
}

