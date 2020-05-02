#include<stdio.h>
#include<stdlib.h>
#ifndef ALGEBRA_FUN__H
#define ALGEBRA_FUN__H
#include "tools_rbtree.h"
#include "tools_node.h"
#include "structures.h"
#include<gmp.h>

#ifdef __cplusplus
extern "C"{
#endif
//此代数结构只使用于有有限代数基的代数体系
typedef struct Algebra_Basic_Element{
    char *name;
    int id;
    void *prop;
}Algebra_Basic_Element;
void Algebra_Basic_Element_init(Algebra_Basic_Element* ae);
typedef struct Tensor_Product_Struct
{
	mpz_t id;
	Node*els;
	void* prop;
}Tensor_Product_Struct;

void Tensor_Product_Struct_init(Tensor_Product_Struct*);
void Tensor_Product_Struct_free(Tensor_Product_Struct*);
int Tensor_Product_Struct_Rank(Tensor_Product_Struct*);

//一般运算的表示结构
typedef struct Algebra_Operation{
    void*** op_map;
    //关键的是operation函数
    void* (*operation)(struct Algebra_Operation*,void*,void*);
    void* prop;
}Algebra_Operation;
void Algebra_Operation_init(Algebra_Operation*);
typedef struct Algebra_Space{
    RB_Tree* elements;
    Algebra_Basic_Element* (*create_element)(struct Algebra_Space*);
    Algebra_Basic_Element* (*get_kv)(struct Algebra_Space*,int);
	int (*is_exist)(struct Algebra_Space*,Algebra_Basic_Element*);
    void* prop;
}Algebra_Space;
void Algebra_Space_init(Algebra_Space* as);
Algebra_Basic_Element* Algebra_Space_Create_Element(Algebra_Space*);
Algebra_Basic_Element* Algebra_Space_get_kv(struct Algebra_Space*,int); 
void Algebra_Space_free(Algebra_Space* as);
void Tensor_Product_Struct_getid(struct Algebra_Space*as,Tensor_Product_Struct*);


#ifdef __cplusplus
}
#endif

#endif
