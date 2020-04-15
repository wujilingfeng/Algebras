#include<Quaternions/Al_Quaternions.h>
#define Quaternion Plus_Struct_Ele


static Quaternion*create_quaternion(Quaternion_Algebra_System*qas,char* s)
{
	Quaternion* q=(Quaternion*)malloc(sizeof(Quaternion));
	Plus_Struct_Ele_init(q);
    double re=0,flag=0,is_fu=1;
    Field_Mult_Struct_Ele*fmse=NULL;
    int i=0,j=0,wei=0;
    while(s[i]!='\0')
    {
        
        re=0;flag=0;wei=0;
        while(s[j]!='+'&&s[j]!='\0'&&s[j]!='-')
        {
            
            if(s[j]>='0'&&s[j]<='9')
            {
                if(flag==0)
                {
                    re=re*10+(s[j]-'0');
                }
                else
                {   
                    flag=flag*10;
                    re=re+(double)(s[j]-'0')/flag;
                }
            }
            else if(s[j]=='.')
            {
                flag=1;
            }
            else
            {
                switch(s[j])
                {
                    case 'i':
                        wei=1;
                        break;
                    case 'j':
                        wei=2;
                        break;
                    case 'k':
                        wei=3;
                        break;
                    default:
                        break;
                        
                }
            }
            j++;
        }
        
      
        
        re=re*is_fu;
        fmse=create_field_mult_struct_ele(qas->as,wei,&re);
        
        plus_mult_struct(q,&fmse,1,qas);
        free(fmse);
        if(s[j]=='\0')
        {
            break;
        }

        if(s[j]=='-')
        {
            is_fu=-1;
        }
        else
        {
            is_fu=1;
        }
        j++;
        i=j;
    }	
    return q;
}
static void qua_mult_(Quaternion* q1,Quaternion*q2,Quaternion_Algebra_System*qas)
{
   	Field_Mult_Struct_Ele*fmse=NULL;
    Quaternion* re=(Quaternion*)malloc(sizeof(Quaternion));
    Plus_Struct_Ele_init(re);
    RB_Trav *it1=q1->value->begin(q1->value);
    int i=0,j=0;
    for(;it1->it!=NULL;it1->next(it1))
    {
        i=*((int*)(it1->first(it1)));
        RB_Trav* it2=q2->value->begin(q2->value);
        for(;it2->it!=NULL;it2->next(it2))
        {
            j=*((int*)(it2->first(it2)));
            fmse=(Field_Mult_Struct_Ele*)malloc(sizeof(Field_Mult_Struct_Ele));
            memmove(fmse,qas->el_op->op_map[i][j],sizeof(Field_Mult_Struct_Ele));
            fmse->value=qas->copy(fmse->value);
            qas->mult(fmse->value,((Field_Mult_Struct_Ele*)(it1->second(it1)))->value);
            qas->mult(fmse->value,((Field_Mult_Struct_Ele*)(it2->second(it2)))->value);
            plus_mult_struct(re,&fmse,1,qas);
            free(fmse->value);
            free(fmse); 
        }
        free(it2);
    }
    free(it1);
    zero_Quaternions(q1);
    free(q1->value);
    q1->value=NULL;
    memmove(q1,re,sizeof(Quaternion));
}

static void* nei_copy(double src)
{
    double* re=(double*)malloc(sizeof(double));
    *re=src;
    return re;
}
void Quaternion_Algebra_System_init(Quaternion_Algebra_System*qas)
{
	Field_Mult_Struct_Ele*fmse=NULL;
	Algebra_Space*as=(Algebra_Space*)malloc(sizeof(Algebra_Space));
	Algebra_Space_init(as);
    for(int i=0;i<4;i++)
    { 
        as->create_element(as);
    }
	qas->as=as;
    qas->el_op=(Algebra_Operation*)malloc(sizeof(Algebra_Operation));
	Algebra_Operation_init(qas->el_op);
    void*** a_map=(void***)malloc(sizeof(void**)*4);
    for(int i=0;i<4;i++)
    {
        a_map[i]=(void**)malloc(sizeof(void*)*4);
    }
    qas->el_op->op_map=a_map;
    //默认域是double类型
    fmse=create_field_mult_struct_ele(as,0,nei_copy(1));
    a_map[0][0]=(void*)fmse;
    fmse=create_field_mult_struct_ele(as,1,nei_copy(1));
    a_map[0][1]=(void*)fmse;
    fmse=create_field_mult_struct_ele(as,2,nei_copy(1));
    a_map[0][2]=(void*)fmse;
    fmse=create_field_mult_struct_ele(as,3,nei_copy(1));
    a_map[0][3]=(void*)fmse;
//
    fmse=create_field_mult_struct_ele(as,1,nei_copy(1));
    a_map[1][0]=(void*)fmse;
    fmse=create_field_mult_struct_ele(as,0,nei_copy(-1));
    a_map[1][1]=(void*)fmse;
    fmse=create_field_mult_struct_ele(as,3,nei_copy(1));
    a_map[1][2]=(void*)fmse;
    fmse=create_field_mult_struct_ele(as,2,nei_copy(-1));
    a_map[1][3]=(void*)fmse;
//
    fmse=create_field_mult_struct_ele(as,2,nei_copy(1));
    a_map[2][0]=(void*)fmse;
    fmse=create_field_mult_struct_ele(as,3,nei_copy(-1));
    a_map[2][1]=(void*)fmse;
    fmse=create_field_mult_struct_ele(as,0,nei_copy(-1));
    a_map[2][2]=(void*)fmse;
    fmse=create_field_mult_struct_ele(as,1,nei_copy(1));
    a_map[2][3]=(void*)fmse;
//
    fmse=create_field_mult_struct_ele(as,3,nei_copy(1));
    a_map[3][0]=(void*)fmse;
    fmse=create_field_mult_struct_ele(as,2,nei_copy(1));
    a_map[3][1]=(void*)fmse;
    fmse=create_field_mult_struct_ele(as,1,nei_copy(-1));
    a_map[3][2]=(void*)fmse;
    fmse=create_field_mult_struct_ele(as,0,nei_copy(-1));
    a_map[3][3]=(void*)fmse;
//以上默认域是double类型.你在初始化一个四元代数后，要手动把value值换成你需要的结构类型。
////比如GMP的结构类型
    /*for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            fmse=(Field_Mult_Struct_Ele*)a_map[i][j];
            printf("id:%d value:%lf   ",fmse->base->id,*((double*)(fmse->value))); 
        }
        printf("\n");
        
    }*/
    
	qas->mult=NULL;
	qas->plus=NULL;
    qas->copy=NULL;
    qas->get_str=create_quaternion;
    qas->q_plus=plus_plus_struct;
    qas->q_mult=qua_mult_;
    
	qas->prop=NULL;

}

void plus_mult_struct(Plus_Struct_Ele*pse,Field_Mult_Struct_Ele**mses,int size,Quaternion_Algebra_System* qal)
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
void plus_plus_struct(Plus_Struct_Ele*pse,Plus_Struct_Ele* pse1,Quaternion_Algebra_System*qal)
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
void field_mult_quaternion(Plus_Struct_Ele* pse,void*value,Quaternion_Algebra_System*qal)
{
    RB_Trav*it=pse->value->begin(pse->value);
    Field_Mult_Struct_Ele* mse=NULL;
    for(;it->it!=NULL;it->next(it))
    {
        mse=(Field_Mult_Struct_Ele*)(it->second(it)) ;
        qal->mult(mse->value,value);
    }
    free(it);
}
/*
static Quaternion* create_one_quaternion(Algebra_Space*as,int id)
{

}
Algebra_Space* Algebra_Create_Quaternions()
{
    Algebra_Space* as=(Algebra_Space*)malloc(sizeof(Algebra_Space));
    Algebra_Space_init(as);
    Algebra_Element*ae=NULL;
    for(int i=0;i<4;i++)
    { 
        ae=as->create_element(as);
    }
    void*** a_map=(void***)malloc(sizeof(void**)*4);
    for(int i=0;i<4;i++)
    {
        a_map[i]=(void**)malloc(sizeof(void*)*4);
    }
    RB_int rbt,*rbt1;
    Plus_Struct_Ele *pse=(Plus_Struct_Ele*)malloc(sizeof(Plus_Struct_Ele));
    Plus_Struct_Ele_init(pse);
    Mult_Struct_Ele *mse=(Mult_Struct_Ele*)malloc(sizeof(Mult_Struct_Ele));
    Mult_struct_Ele_init(mse);
    double *d=(double*)malloc(sieof(double));
    *d=1;
    mse->value=(void*)d;
    rbt.key=0;
    mse->base=(Algebra_Basic_Element*)(((RB_int*)as->elements->find(as->elements,&rbt))->value);



    return as;

}
*/
