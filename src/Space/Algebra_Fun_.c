#include<Space/Algebra_Fun_.h>
void Algebra_Basic_Element_init(Algebra_Basic_Element*ae)
{
    ae->name=NULL;
    ae->id=-1;
    ae->prop=NULL;
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

