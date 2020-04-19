#include<Space/Algebra_Fun_.h>
void Algebra_Basic_Element_init(Algebra_Basic_Element*ae)
{
    ae->name=NULL;
    ae->id=-1;
    ae->prop=NULL;
}
void Tensor_Product_Struct_init(Tensor_Product_Struct*tps)
{
	mpz_inits(tps->id,NULL);
	tps->els=NULL;
	tps->prop=NULL;
}
void Tensor_Product_Struct_free(Tensor_Product_Struct*tps)
{
	mpz_clear(tps->id);
	free_node(tps->els);
	free(tps);
}
int Tensor_Product_Struct_Rank(Tensor_Product_Struct*tps)
{
	return node_size(tps->els);
}
void Algebra_Operation_init(Algebra_Operation* ao)
{
   
	ao->op_map=NULL;
    ao->operation=NULL;
    ao->prop=NULL;
}
static int Algebra_is_exist(struct Algebra_Space*as,Algebra_Basic_Element*abe)
{
	RB_int rbt,*rbt1;
	rbt.key=abe->id;
	rbt1=as->elements->find(as->elements,&rbt);
	if(rbt1!=NULL)
	{
		if(rbt1->value==abe)
		{	
			return 1;
		}
	}
	return 0;
}
void Algebra_Space_init(Algebra_Space* as)
{
    as->elements=(RB_Tree*)malloc(sizeof(RB_Tree));
    RB_Tree_init_int(as->elements);
    as->create_element=Algebra_Space_Create_Element;
as->get_kv=Algebra_Space_get_kv;
   	as->is_exist=Algebra_is_exist;
    as->prop=NULL;

}
Algebra_Basic_Element* Algebra_Space_Create_Element(Algebra_Space*as)
{
    Algebra_Basic_Element* ae=(Algebra_Basic_Element*)malloc(sizeof(Algebra_Basic_Element));
    Algebra_Basic_Element_init(ae);
    ae->id=as->elements->size;
    RB_int rbt;
    rbt.key=ae->id;
    rbt.value=(void*)ae;
    as->elements->insert(as->elements,&rbt);
    return ae;
}
Algebra_Basic_Element* Algebra_Space_get_kv(struct Algebra_Space* as,int id)
{
	RB_int rbt,*rbt1;
	rbt.key=id;
	rbt1=(RB_int*)as->elements->find(as->elements,&rbt);	
	return (Algebra_Basic_Element*)(rbt1->value);
}
void Tensor_Product_Struct_getid(struct Algebra_Space*as,Tensor_Product_Struct*tps)
{
	int size=as->elements->size,size1=node_size(tps->els);

	mpz_t a,b,c;
	mpz_inits(a,b,c,NULL);
	mpz_set_ui(a,size);

	for(Node* it=tps->els;it!=NULL;it=(Node*)(it->Next))
	{
		Algebra_Basic_Element* abe=(Algebra_Basic_Element*)(it->value);
				
		mpz_pow_ui(b,a,size1-1);

		mpz_mul_ui(b,b,abe->id);

		mpz_add(c,c,b);
		size1--;
	}

	mpz_set(tps->id,c);
	mpz_clear(a);mpz_clear(b);mpz_clear(c);
}

