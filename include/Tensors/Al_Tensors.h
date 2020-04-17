#include<Space/Algebra_Fun_.h>
#ifndef ALGEBRA_VECTORS_H
#define ALGEBRA_VECTORS_H
#define Tensor Plus_Struct_Ele
#ifdef __cplusplus
extern "C"{
#endif
typedef struct Field_Mult_Struct_Ele{
//value指向单独申请的内存
    void * value;
	Tensor_Product_Struct *base;
	Node* iters;
    //Algebra_Basic_Element* base;
    void* prop;
}Field_Mult_Struct_Ele;

//初始化为关于域乘法0元
void Field_Mult_Struct_Ele_init(Field_Mult_Struct_Ele*);

//主要用来创建关于域乘法单位元，或其他非零元
Field_Mult_Struct_Ele* create_field_mult_struct_ele(Algebra_Space* as,int* ids,int size,void* value);

typedef struct Plus_Struct_Ele{
    RB_Tree* value;
	void (*zero)(struct Tensor*);
	void (*insert)(Algebra_Space*,struct Tensor*,int*,int,void*);
	void* (*get_value)(Algebra_Space*as,struct Tensor* t,int *ids,int size);
    void* prop;
}Plus_Struct_Ele;
//初始化为加法单位元(环的0元)
void Plus_Struct_Ele_init(Plus_Struct_Ele*);

//加法单位元化
void zero_plus_struct_ele(Plus_Struct_Ele*);


typedef struct Tensors_Algebra_System
{
    Algebra_Space* as,*dual_as;

	void *(*copy)(void*);
//域乘法和加法,改变第一个参数
	void(*mult)(void*,void*);
	void(*plus)(void*,void*);
	void (*T_plus)(struct Tensors_Algebra_System*,Tensor*,Tensor*);
	Tensor* (*Tensor_Product)(struct Tensors_Algebra_System*,Tensor*,Tensor*);
	Tensor*(*T_create)();

	void* prop;
}Tensors_Algebra_System;
void Tensors_Algebra_System_init(Tensors_Algebra_System*,int);
void plus_mult_struct(Tensors_Algebra_System*tas,Plus_Struct_Ele*pse,Field_Mult_Struct_Ele**mses,int size);
void plus_plus_struct(Tensors_Algebra_System*tal,Plus_Struct_Ele*pse,Plus_Struct_Ele* pse1); 
//张量积运算
Tensor* W_Tensor_Product(struct Tensors_Algebra_System*,Tensor*,Tensor*);

//张量的缩并运算
//Tensor*Tensor_Contraction

/*
typedef struct Vectors_Algebra_System
{

    Algebra_Space* as,*dual_as;
	int (*is_dual)(struct Vectors_Algebra_System* vas,Vector *);
//指向另一代数系统基的映射
    Algebra_Operation* el_op;
	void (*print_self)(Vector*);
	Vector*(*create_v)();
	void (*zero)(Vector*);
	void (*insert_v)(Algebra_Space*as,Vector*v,int id,void*value);
	void (*v_plus)(struct Vectors_Algebra_System*,Vector*,Vector*);
	void (*v_mult)(struct Vectors_Algebra_System*vas,void*,Vector* q1,Vector*q2);
	void* (*get_kv)(Vector*,int id);
//int (*is_equal)(Vector*,Vector*);
//
	void *(*copy)(void*);
//域乘法和加法,改变第一个参数
	void(*mult)(void*,void*);
	void(*plus)(void*,void*);
    void* prop;
}Vectors_Algebra_System;
void Vectors_Algebra_System_init(Vectors_Algebra_System*,int);
void plus_mult_struct(Plus_Struct_Ele*pse,Field_Mult_Struct_Ele**mses,int size,Vectors_Algebra_System*vas);
*/
#ifdef __cplusplus
}
#endif
#endif
