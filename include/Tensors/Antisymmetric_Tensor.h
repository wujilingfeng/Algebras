#include<Tensors/Al_Tensors.h>
#ifndef ALGEBRA_ANTISYMMETRIC_TENSOR_H
#define ALGEBRA_ANTISYMMETRIC_TENSOR_H
#ifdef __cplusplus
extern "C"{
#endif
Tensor* Tensor_Wedge_(struct Tensors_Algebra_System*,Tensor*,Tensor*);
void* Anti_Tensor_norm(struct Tensors_Algebra_System*,Tensor*);
#ifdef __cplusplus
}
#endif
#endif
