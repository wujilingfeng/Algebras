#include<Space/Algebra_Fun_.h>
#ifndef ALGEBRA_VECTORS_H
#define ALGEBRA_VECTORS_H
#define Vector Plus_Struct_Ele
#ifdef __cplusplus
extern "C"{
#endif
typedef struct Field_Mult_Struct_Ele{
//value指向单独申请的内存
    void * value;
    Algebra_Basic_Element* base;
    void* prop;
}Field_Mult_Struct_Ele;
//初始化为关于域乘法0元
void Field_Mult_Struct_Ele_init(Field_Mult_Struct_Ele*);
//主要用来创建关于域乘法单位元，或其他非零元
Field_Mult_Struct_Ele* create_field_mult_struct_ele(Algebra_Space* as,int id,void* value);

typedef struct Plus_Struct_Ele{
    RB_Tree* value;
    void* prop;
}Plus_Struct_Ele;
//初始化为加法单位元(环的0元)
void Plus_Struct_Ele_init(Plus_Struct_Ele*);
//加法单位元化
//void zero_plus_struct_ele(Plus_Struct_Ele*);
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
void plus_plus_struct(Vectors_Algebra_System*qal,Plus_Struct_Ele*pse,Plus_Struct_Ele* pse1);
#ifdef __cplusplus
}
#endif
#endif
