#include<Quaternions/Al_Quaternions.h>

#include <tools/double_tools.h>
#define Quaternion Plus_Struct_Ele


static Quaternion*create_quaternion(Quaternion_Algebra_System*qas,char* s)
{   
    Tensors_Algebra_System*tas=qas->tas;
	Quaternion* q=(Quaternion*)malloc(sizeof(Quaternion));
	Plus_Struct_Ele_init(q);
    double re=0,flag=0,is_fu=1;
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
        //fmse=create_field_mult_struct_ele(tas->as,&wei,1,tas->copy_from_double(re));
        q->insert(tas->as,q,&wei,1,tas->copy_from_double(re)); 
        
        //plus_mult_struct(q,&fmse,1,qas);
        //free(fmse);
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

static Quaternion* qua_mult_(Quaternion_Algebra_System*qas,Quaternion* q1,Quaternion*q2)
{
   	Field_Mult_Struct_Ele*fmse=NULL;
    Quaternion* re=(Quaternion*)malloc(sizeof(Quaternion));
    Plus_Struct_Ele_init(re);
    RB_Trav *it1=q1->value->begin(q1->value);
    int i=0,j=0;
    for(;it1->it!=NULL;it1->next(it1))
    {
        
        i=mpz_get_ui((__mpz_struct*)(it1->first(it1)));
        RB_Trav* it2=q2->value->begin(q2->value);
        for(;it2->it!=NULL;it2->next(it2))
        {
            j=mpz_get_ui((__mpz_struct*)(it2->first(it2)));
    
            fmse=(Field_Mult_Struct_Ele*)qas->el_op->op_map[i][j];
            void* temp_value=fmse->value;
            void*value=qas->tas->copy_from_double(1);
            qas->tas->mult(value,temp_value);
            qas->tas->mult(value,((Field_Mult_Struct_Ele*)(it1->second(it1)))->value);
            qas->tas->mult(value,((Field_Mult_Struct_Ele*)(it2->second(it2)))->value);
            fmse->value=value;
            plus_mult_struct(qas->tas,re,&fmse,1);
            fmse->value=temp_value;
            qas->tas->free_data(value);
        }
        free(it2);
    }
    free(it1);
    return re;
}

/*static void* nei_copy(double src)
{
    double* re=(double*)malloc(sizeof(double));
    *re=src;
    return re;
}*/
void  Quaternion_Algebra_System_init(Quaternion_Algebra_System*qas)
{

    qas->tas=(Tensors_Algebra_System*)malloc(sizeof(Tensors_Algebra_System));
    Tensors_Algebra_System_double_init(qas->tas,4);
    Tensors_Algebra_System*tas=qas->tas;
    Algebra_Space*as=qas->tas->as;
    qas->el_op=(Algebra_Operation*)malloc(sizeof(Algebra_Operation));
    Algebra_Operation_init(qas->el_op);
    void*** a_map=(void***)malloc(sizeof(void**)*4);
    for(int i=0;i<4;i++)
    {
        a_map[i]=(void**)malloc(sizeof(void*)*4);
    }
    qas->el_op->op_map=a_map;
    int ids=0;
    Field_Mult_Struct_Ele*fmse=NULL;
    //默认域是double类型
    ids=0;fmse=create_field_mult_struct_ele(as,&ids,1,tas->copy_from_double(1));
    a_map[0][0]=(void*)fmse;
    ids=1;fmse=create_field_mult_struct_ele(as,&ids,1,tas->copy_from_double(1));
    a_map[0][1]=(void*)fmse;
    ids=2;fmse=create_field_mult_struct_ele(as,&ids,1,tas->copy_from_double(1));
    a_map[0][2]=(void*)fmse;
    ids=3;fmse=create_field_mult_struct_ele(as,&ids,1,tas->copy_from_double(1));
    a_map[0][3]=(void*)fmse;
//
    ids=1;fmse=create_field_mult_struct_ele(as,&ids,1,tas->copy_from_double(1));
    a_map[1][0]=(void*)fmse;
    ids=0;fmse=create_field_mult_struct_ele(as,&ids,1,tas->copy_from_double(-1));
    a_map[1][1]=(void*)fmse;
    ids=3;fmse=create_field_mult_struct_ele(as,&ids,1,tas->copy_from_double(1));
    a_map[1][2]=(void*)fmse;
    ids=2;fmse=create_field_mult_struct_ele(as,&ids,1,tas->copy_from_double(-1));
    a_map[1][3]=(void*)fmse;
//
    ids=2;fmse=create_field_mult_struct_ele(as,&ids,1,tas->copy_from_double(1));
    a_map[2][0]=(void*)fmse;
    ids=3;fmse=create_field_mult_struct_ele(as,&ids,1,tas->copy_from_double(-1));
    a_map[2][1]=(void*)fmse;
    ids=0;fmse=create_field_mult_struct_ele(as,&ids,1,tas->copy_from_double(-1));
    a_map[2][2]=(void*)fmse;
    ids=1;fmse=create_field_mult_struct_ele(as,&ids,1,tas->copy_from_double(1));
    a_map[2][3]=(void*)fmse;
//
    ids=3;fmse=create_field_mult_struct_ele(as,&ids,1,tas->copy_from_double(1));
    a_map[3][0]=(void*)fmse;
    ids=2;fmse=create_field_mult_struct_ele(as,&ids,1,tas->copy_from_double(1));
    a_map[3][1]=(void*)fmse;
    ids=1;fmse=create_field_mult_struct_ele(as,&ids,1,tas->copy_from_double(-1));
    a_map[3][2]=(void*)fmse;
    ids=0;fmse=create_field_mult_struct_ele(as,&ids,1,tas->copy_from_double(-1));
    a_map[3][3]=(void*)fmse;
    qas->Q_create=create_quaternion;
    qas->Q_mult=qua_mult_;

}
/*
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
	qas->mult=NULL;
	qas->plus=NULL;
    qas->copy=NULL;
    qas->get_str=create_quaternion;
    qas->q_plus=plus_plus_struct;
    qas->q_mult=qua_mult_;
    
	qas->prop=NULL;

}*/

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
