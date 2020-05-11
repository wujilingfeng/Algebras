#include<Tensors/Al_Tensors.h>
#ifndef ALGEBRA_QUATERNIONS_H
#define ALGEBRA_QUATERNIONS_H
#ifdef __cplusplus
extern "C"
{
#endif

#define Quaternion Plus_Struct_Ele


typedef struct Quaternion_Algebra_System
{

    Tensors_Algebra_System* tas;
//基本元素乘法结构
    Algebra_Operation* el_op;
	Quaternion*(*Q_create)(struct Quaternion_Algebra_System*,char*);
	Quaternion* (*Q_mult)(struct Quaternion_Algebra_System*,Quaternion*,Quaternion*);
    void* prop;
}Quaternion_Algebra_System;
void Quaternion_Algebra_System_init(Quaternion_Algebra_System*qas);
/*
//元素加法的实现

void plus_mult_struct(Plus_Struct_Ele*pse,Field_Mult_Struct_Ele**mses,int size,Quaternion_Algebra_System* qal);
void plus_plus_struct(Plus_Struct_Ele*pse,Plus_Struct_Ele*pse1,Quaternion_Algebra_System* qal);
//域乘法的实现
void field_mult_quaternion(Plus_Struct_Ele*,void*value,Quaternion_Algebra_System* qal);
*/

#ifdef __cplusplus
}
#endif

#endif
