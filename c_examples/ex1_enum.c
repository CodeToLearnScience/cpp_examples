#include <stdio.h>

typedef enum {
  /* converged */
  KSP_CONVERGED_RTOL_NORMAL        =  1,
  KSP_CONVERGED_ATOL_NORMAL        =  9,
  KSP_CONVERGED_RTOL               =  2,
  KSP_CONVERGED_ATOL               =  3,
  KSP_CONVERGED_ITS                =  4,
  KSP_CONVERGED_CG_NEG_CURVE       =  5,
  KSP_CONVERGED_CG_CONSTRAINED     =  6,
  KSP_CONVERGED_STEP_LENGTH        =  7,
  KSP_CONVERGED_HAPPY_BREAKDOWN    =  8,
  /* diverged */
  KSP_DIVERGED_NULL                = -2,
  KSP_DIVERGED_ITS                 = -3,
  KSP_DIVERGED_DTOL                = -4,
  KSP_DIVERGED_BREAKDOWN           = -5,
  KSP_DIVERGED_BREAKDOWN_BICG      = -6,
  KSP_DIVERGED_NONSYMMETRIC        = -7,
  KSP_DIVERGED_INDEFINITE_PC       = -8,
  KSP_DIVERGED_NANORINF            = -9,
  KSP_DIVERGED_INDEFINITE_MAT      = -10,
  KSP_DIVERGED_PC_FAILED           = -11,
  KSP_DIVERGED_PCSETUP_FAILED_DEPRECATED  = -11,

  KSP_CONVERGED_ITERATING          =  0} KSPConvergedReason;

void use_enum_in_func(KSPConvergedReason *flag){
  printf("Using KSPConvergedReason enum in func: %d\n", *flag);
}

//int *my_func(int *a){
//  *a+=1;
//}

//void use_func_ptr(int a, int (*f)(int *b)){
//  printf("the value directly passed %d\n", a);
//  printf("the value from func pointer %d\n", (*f)(b));
//}

int main()
{

  KSPConvergedReason flag=KSP_CONVERGED_RTOL;
  use_enum_in_func(&flag);



  //flag=0;
  //printf("Reason: %d\n", flag);

  //int j=2;
  //use_func_ptr(2, 2);
  


  return 0;
}
