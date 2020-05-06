#include<Space/Algebra_Fun_.h>
#ifndef ALGEBRA_TENSORS_H
#define ALGEBRA_TENSORS_H
#define Tensor Plus_Struct_Ele
#ifdef __cplusplus
extern "C"{
#endif
typedef struct Field_Mult_Struct_Ele{
//value指向单独申请的内存
    void * value;
	Tensor_Product_Struct *base;
	Node* iters;
	int order;
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
	int (*order)(struct Tensor*);
	void (*insert)(Algebra_Space*,struct Tensor*,int*,int,void*);
	void* (*get_value)(Algebra_Space*as,struct Tensor* t,int *ids,int size);
    void* prop;
}Plus_Struct_Ele;
//初始化为加法单位元(环的0元)
void Plus_Struct_Ele_init(Plus_Struct_Ele*);

//加法单位元化,但是不推荐使用
void zero_plus_struct_ele(Plus_Struct_Ele*);
void* Tensor_get_value(Algebra_Space*as,Tensor* t,int *ids,int size);

typedef struct Tensors_Algebra_System
{
    Algebra_Space* as,*dual_as;
	void* (*copy_from_double)(double);
	void (*set_copy)(void*,void*);
	
//域乘法和加法,改变第一个参数
	void(*mult)(void*,void*);
	void(*plus)(void*,void*);
	void(*div)(void*,void*);
	int(*cmp)(void*,void*);
	int(*cmp_d)(void*,double);
	void(*free_data)(void*);
	void (*T_plus)(struct Tensors_Algebra_System*,Tensor*,Tensor*);
	Tensor* (*Tensor_Product)(struct Tensors_Algebra_System*,Tensor*,Tensor*);
	Tensor*(*T_create)();
	void (*T_free)(struct Tensors_Algebra_System* ,Tensor*);
	void* (*T_norm)(struct Tensors_Algebra_System*,Tensor*);
	Tensor* (*T_product)(struct Tensors_Algebra_System*,Tensor*,Tensor*);
	void* (*T_inner_product)(struct Tensors_Algebra_System*,Tensor*,Tensor*);
	void (*T_mult_field)(struct Tensors_Algebra_System*,Tensor*,void*);
	void (*T_div_field)(struct Tensors_Algebra_System*,Tensor*,void*);
	void* prop;
}Tensors_Algebra_System;
void Tensors_Algebra_System_init(Tensors_Algebra_System*,int);
void Tensors_Algebra_System_free(Tensors_Algebra_System*);
void plus_mult_struct(Tensors_Algebra_System*tas,Plus_Struct_Ele*pse,Field_Mult_Struct_Ele**mses,int size);
void plus_plus_struct(Tensors_Algebra_System*tal,Plus_Struct_Ele*pse,Plus_Struct_Ele* pse1); 
//张量积运算
Tensor* W_Tensor_Product(struct Tensors_Algebra_System*,Tensor*,Tensor*);
//张量内积运算
void* W_Tensor_Inner_Product(struct Tensors_Algebra_System*,Tensor*,Tensor*);
//张量的缩并运算,可以等价于张量积运算
////缩并运算效率不高，带度量的内积运算效率比较高
int fmses_classi_dim(Field_Mult_Struct_Ele*fmse,int zuo1);
//zuo1 zuo2取值为0,1...
Tensor*W_Tensor_Contraction(struct Tensors_Algebra_System*,Tensor*,Tensor*,int zuo1,int zuo2);

//返回张量模长的平方
void* Tensor_norm(struct Tensors_Algebra_System*,Tensor*);

void Tensor_mult_field_(Tensors_Algebra_System*,Tensor* ,void* );
void Tensor_div_field_(Tensors_Algebra_System*, Tensor* ,void* );
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
