#include<stdio.h>
#include<stdlib.h>
#ifndef SpaceManager_H
#define SpaceManager_H
#define SpaceManager Tensor_Space_Mana
#define Base Tensor_Base
#ifdef __cplusplus
extern "C"{
#endif
typedef struct Basic_element
{
    int id;
}Basic_element;
typedef struct Base
{
    char* algebra;
    //Basic_element* ei;
    //

}Base;
typedef struct SpaceManager
{



}SpaceManager;
#endif

#ifdef __cplusplus
}
#endif
