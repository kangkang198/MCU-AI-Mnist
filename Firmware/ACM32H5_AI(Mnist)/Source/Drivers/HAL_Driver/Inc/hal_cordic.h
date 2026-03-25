/******************************************************************************
*@file  : hal_fau.h
*@brief : Header file of FAU module.
*@ver   : 1.0.0
*@date  : 2022.10.20
******************************************************************************/

#ifndef __CORDIC_H_
#define __CORDIC_H_

#define RANGE        2147483648U  //2^31
#define CORDIC_F_31  0xD2C90A46   // CORDIC gain F
#define W_INV_Q31    0x6A012206

#define PI 3.1415926  

/******************************************************************************
*@brief : calculate the sin & cos value of the input angle(precision 1)
*         
*@param : angle_para: input angle data in radians, divided by ¦Ð,range[-1,1],Q31 format 
*@param : cos_data  : the cos value of the input angle,range[-1,1],Q31 format
*@param : sin_data  : the sin value of the input angle,range[-1,1],Q31 format
*@return: None
******************************************************************************/
void HAL_CORDIC_CosSin_1(int angle_para, int* cos_data, int* sin_data);

/******************************************************************************
*@brief : calculate the sin & cos value of the input angle(precision 2)
*         
*@param : angle_para: input angle data in radians, divided by ¦Ð,range[-1,1],Q31 format 
*@param : cos_data  : the cos value of the input angle,range[-1,1],Q31 format
*@param : sin_data  : the sin value of the input angle,range[-1,1],Q31 format
*@return: None
******************************************************************************/
void HAL_CORDIC_CosSin_2(int angle_para, int* cos_data, int* sin_data);

/******************************************************************************
*@brief : calculate the sin & cos value of the input angle(precision 3)
*         
*@param : angle_para: input angle data in radians, divided by ¦Ð,range[-1,1],Q31 format 
*@param : cos_data  : the cos value of the input angle,range[-1,1],Q31 format
*@param : sin_data  : the sin value of the input angle,range[-1,1],Q31 format
*@return: None
******************************************************************************/
void HAL_CORDIC_CosSin_3(int angle_para, int* cos_data, int* sin_data);

/******************************************************************************
*@brief : calculate the sin & cos value of the input angle(precision 4)
*         
*@param : angle_para: input angle data in radians, divided by ¦Ð,range[-1,1],Q31 format 
*@param : cos_data  : the cos value of the input angle,range[-1,1],Q31 format
*@param : sin_data  : the sin value of the input angle,range[-1,1],Q31 format
*@return: None
******************************************************************************/
void HAL_CORDIC_CosSin_4(int angle_para, int* cos_data, int* sin_data);

/******************************************************************************
*@brief : calculate the sin & cos value of the input angle(precision 5)
*         
*@param : angle_para: input angle data in radians, divided by ¦Ð,range[-1,1],Q31 format 
*@param : cos_data  : the cos value of the input angle,range[-1,1],Q31 format
*@param : sin_data  : the sin value of the input angle,range[-1,1],Q31 format
*@return: None
******************************************************************************/
void HAL_CORDIC_CosSin_5(int angle_para, int* cos_data, int* sin_data);

/******************************************************************************
*@brief : calculate the sin & cos value of the input angle(precision 6)
*         
*@param : angle_para: input angle data in radians, divided by ¦Ð,range[-1,1],Q31 format 
*@param : cos_data  : the cos value of the input angle,range[-1,1],Q31 format
*@param : sin_data  : the sin value of the input angle,range[-1,1],Q31 format
*@return: None
******************************************************************************/
void HAL_CORDIC_CosSin_6(int angle_para, int* cos_data, int* sin_data);

/******************************************************************************
*@brief : calculate the sin & cos value of the input angle(precision 7)
*         
*@param : angle_para: input angle data in radians, divided by ¦Ð,range[-1,1],Q31 format 
*@param : cos_data  : the cos value of the input angle,range[-1,1],Q31 format
*@param : sin_data  : the sin value of the input angle,range[-1,1],Q31 format
*@return: None
******************************************************************************/
void HAL_CORDIC_CosSin_7(int angle_para, int* cos_data, int* sin_data);

/******************************************************************************
*@brief : calculate the sin & cos value of the input angle(precision 8)
*         
*@param : angle_para: input angle data in radians, divided by ¦Ð,range[-1,1],Q31 format 
*@param : cos_data  : the cos value of the input angle,range[-1,1],Q31 format
*@param : sin_data  : the sin value of the input angle,range[-1,1],Q31 format
*@return: None
******************************************************************************/
void HAL_CORDIC_CosSin_8(int angle_para, int* cos_data, int* sin_data);

/******************************************************************************
*@brief : calculate the atan & sqrt value of the input x,y(precision 1)
*         
*@param : x          : input x, range[-1,1],Q31 format
*@param : y          : input y, range[-1,1],Q31 format
*@param : sqrt_data  : the sqrt value of the input x,y,Q31 format
*                      sqrt_data should devide (CORDIC_F_31>>4) to obtain the value in float
*@param : atan_data  : the atan value of the input y/x,Q31 format
*                      atan_value must be multiplied by ¦Ð to obtain the angle in radians
*@return: None
******************************************************************************/
void HAL_CORDIC_AtanSqrt_1(int x, int y, int*sqrt_data, int* atan_data);

/******************************************************************************
*@brief : calculate the atan & sqrt value of the input x,y(precision 2)
*         
*@param : x          : input x, range[-1,1],Q31 format
*@param : y          : input y, range[-1,1],Q31 format
*@param : sqrt_data  : the sqrt value of the input x,y,Q31 format
*                      sqrt_data should devide (CORDIC_F_31>>4) to obtain the value in float
*@param : atan_data  : the atan value of the input y/x,Q31 format
*                      atan_value must be multiplied by ¦Ð to obtain the angle in radians
*@return: None
******************************************************************************/
void HAL_CORDIC_AtanSqrt_2(int x, int y, int*sqrt_data, int* atan_data);

/******************************************************************************
*@brief : calculate the atan & sqrt value of the input x,y(precision 3)
*         
*@param : x          : input x, range[-1,1],Q31 format
*@param : y          : input y, range[-1,1],Q31 format
*@param : sqrt_data  : the sqrt value of the input x,y,Q31 format
*                      sqrt_data should devide (CORDIC_F_31>>4) to obtain the value in float
*@param : atan_data  : the atan value of the input y/x,Q31 format
*                      atan_value must be multiplied by ¦Ð to obtain the angle in radians
*@return: None
******************************************************************************/
void HAL_CORDIC_AtanSqrt_3(int x, int y, int*sqrt_data, int* atan_data);

/******************************************************************************
*@brief : calculate the atan & sqrt value of the input x,y(precision 4)
*         
*@param : x          : input x, range[-1,1],Q31 format
*@param : y          : input y, range[-1,1],Q31 format
*@param : sqrt_data  : the sqrt value of the input x,y,Q31 format
*                      sqrt_data should devide (CORDIC_F_31>>4) to obtain the value in float
*@param : atan_data  : the atan value of the input y/x,Q31 format
*                      atan_value must be multiplied by ¦Ð to obtain the angle in radians
*@return: None
******************************************************************************/
void HAL_CORDIC_AtanSqrt_4(int x, int y, int*sqrt_data, int* atan_data);

/******************************************************************************
*@brief : calculate the atan & sqrt value of the input x,y(precision 5)
*         
*@param : x          : input x, range[-1,1],Q31 format
*@param : y          : input y, range[-1,1],Q31 format
*@param : sqrt_data  :  the sqrt value of the input x,y,Q31 format
*                       sqrt_data should devide (CORDIC_F_31>>4) to obtain the value in float
*@param : atan_data  :  the atan value of the input y/x,Q31 format
*                       atan_value must be multiplied by ¦Ð to obtain the angle in radians
*@return: None
******************************************************************************/
void HAL_CORDIC_AtanSqrt_5(int x, int y, int*sqrt_data, int* atan_data);

/******************************************************************************
*@brief : calculate the atan & sqrt value of the input x,y(precision 6)
*         
*@param : x          : input x, range[-1,1],Q31 format
*@param : y          : input y, range[-1,1],Q31 format
*@param : sqrt_data  :  the sqrt value of the input x,y,Q31 format
*                       sqrt_data should devide (CORDIC_F_31>>4) to obtain the value in float
*@param : atan_data  :  the atan value of the input y/x,Q31 format
*                       atan_value must be multiplied by ¦Ð to obtain the angle in radians
*@return: None
******************************************************************************/
void HAL_CORDIC_AtanSqrt_6(int x, int y, int*sqrt_data, int* atan_data);

/******************************************************************************
*@brief : calculate the atan & sqrt value of the input x,y(precision 7)
*         
*@param : x          : input x, range[-1,1],Q31 format
*@param : y          : input y, range[-1,1],Q31 format
*@param : sqrt_data  :  the sqrt value of the input x,y,Q31 format
*                       sqrt_data should devide (CORDIC_F_31>>4) to obtain the value in float
*@param : atan_data  :  the atan value of the input y/x,Q31 format
*                       atan_value must be multiplied by ¦Ð to obtain the angle in radians
*@return: None
******************************************************************************/
void HAL_CORDIC_AtanSqrt_7(int x, int y, int*sqrt_data, int* atan_data);

/******************************************************************************
*@brief : calculate the atan & sqrt value of the input x,y(precision 8)
*         
*@param : x          : input x, range[-1,1],Q31 format
*@param : y          : input y, range[-1,1],Q31 format
*@param : sqrt_data  :  the sqrt value of the input x,y,Q31 format
*                       sqrt_data should devide (CORDIC_F_31>>4) to obtain the value in float
*@param : atan_data  :  the atan value of the input y/x,Q31 format
*                       atan_value must be multiplied by ¦Ð to obtain the angle in radians
*@return: None
******************************************************************************/
void HAL_CORDIC_AtanSqrt_8(int x, int y, int*sqrt_data, int* atan_data);

/******************************************************************************
*@brief : calculate the sinh & cosh value of the input angle(precision 1)
*         
*@param : angle_para :  input hyperbolic angle data in radians, range [-0.559 ~0. 559]([-1.118 ~ 1.118]/2),Q31 format 
*@param : cosh_data  :  the hyperbolic cosh value of the input angle,,range[0.5 0.846],Q31 format
*                       cosh_data must be multiplied by 2 to obtain the correct result
*@param : sinh_data  :  the hyperbolic sinh value of the input angle,range[[-0.683 0.683],Q31 format
*                       sinh_data must be multiplied by 2 to obtain the correct result
*@return: None
******************************************************************************/
void HAL_CORDIC_CoshSinh_1(int angle_para, int* cosh_data, int* sinh_data);

/******************************************************************************
*@brief : calculate the sinh & cosh value of the input angle(precision 2)
*         
*@param : angle_para :  input hyperbolic angle data in radians, range [-0.559 ~0. 559]([-1.118 ~ 1.118]/2),Q31 format 
*@param : cosh_data  :  the hyperbolic cosh value of the input angle,,range[0.5 0.846],Q31 format
*                       cosh_data must be multiplied by 2 to obtain the correct result
*@param : sinh_data  :  the hyperbolic sinh value of the input angle,range[[-0.683 0.683],Q31 format
*                       sinh_data must be multiplied by 2 to obtain the correct result
*@return: None
******************************************************************************/
void HAL_CORDIC_CoshSinh_2(int angle_para, int* cosh_data, int* sinh_data);

/******************************************************************************
*@brief : calculate the sinh & cosh value of the input angle(precision 3)
*         
*@param : angle_para :  input hyperbolic angle data in radians, range [-0.559 ~0. 559]([-1.118 ~ 1.118]/2),Q31 format 
*@param : cosh_data  :  the hyperbolic cosh value of the input angle,,range[0.5 0.846],Q31 format
*                       cosh_data must be multiplied by 2 to obtain the correct result
*@param : sinh_data  :  the hyperbolic sinh value of the input angle,range[[-0.683 0.683],Q31 format
*                       sinh_data must be multiplied by 2 to obtain the correct result
*@return: None
******************************************************************************/
void HAL_CORDIC_CoshSinh_3(int angle_para, int* cosh_data, int* sinh_data);

/******************************************************************************
*@brief : calculate the sinh & cosh value of the input angle(precision 4)
*         
*@param : angle_para :  input hyperbolic angle data in radians, range [-0.559 ~0. 559]([-1.118 ~ 1.118]/2),Q31 format 
*@param : cosh_data  :  the hyperbolic cosh value of the input angle,,range[0.5 0.846],Q31 format
*                       cosh_data must be multiplied by 2 to obtain the correct result
*@param : sinh_data  :  the hyperbolic sinh value of the input angle,range[[-0.683 0.683],Q31 format
*                       sinh_data must be multiplied by 2 to obtain the correct result
*@return: None
******************************************************************************/
void HAL_CORDIC_CoshSinh_4(int angle_para, int* cosh_data, int* sinh_data);

/******************************************************************************
*@brief : calculate the sinh & cosh value of the input angle(precision 5)
*         
*@param : angle_para :  input hyperbolic angle data in radians, range [-0.559 ~0. 559]([-1.118 ~ 1.118]/2),Q31 format 
*@param : cosh_data  :  the hyperbolic cosh value of the input angle,,range[0.5 0.846],Q31 format
*                       cosh_data must be multiplied by 2 to obtain the correct result
*@param : sinh_data  :  the hyperbolic sinh value of the input angle,range[[-0.683 0.683],Q31 format
*                       sinh_data must be multiplied by 2 to obtain the correct result
*@return: None
******************************************************************************/
void HAL_CORDIC_CoshSinh_5(int angle_para, int* cosh_data, int* sinh_data);

/******************************************************************************
*@brief : calculate the sinh & cosh value of the input angle(precision 6)
*         
*@param : angle_para :  input hyperbolic angle data in radians, range [-0.559 ~0. 559]([-1.118 ~ 1.118]/2),Q31 format 
*@param : cosh_data  :  the hyperbolic cosh value of the input angle,,range[0.5 0.846],Q31 format
*                       cosh_data must be multiplied by 2 to obtain the correct result
*@param : sinh_data  :  the hyperbolic sinh value of the input angle,range[[-0.683 0.683],Q31 format
*                       sinh_data must be multiplied by 2 to obtain the correct result
*@return: None
******************************************************************************/
void HAL_CORDIC_CoshSinh_6(int angle_para, int* cosh_data, int* sinh_data);

/******************************************************************************
*@brief : calculate the sinh & cosh value of the input angle(precision 7)
*         
*@param : angle_para :  input hyperbolic angle data in radians, range [-0.559 ~0. 559]([-1.118 ~ 1.118]/2),Q31 format 
*@param : cosh_data  :  the hyperbolic cosh value of the input angle,,range[0.5 0.846],Q31 format
*                       cosh_data must be multiplied by 2 to obtain the correct result
*@param : sinh_data  :  the hyperbolic sinh value of the input angle,range[[-0.683 0.683],Q31 format
*                       sinh_data must be multiplied by 2 to obtain the correct result
*@return: None
******************************************************************************/
void HAL_CORDIC_CoshSinh_7(int angle_para, int* cosh_data, int* sinh_data);

/******************************************************************************
*@brief : calculate the sinh & cosh value of the input angle(precision 8)
*         
*@param : angle_para :  input hyperbolic angle data in radians, range [-0.559 ~0. 559]([-1.118 ~ 1.118]/2),Q31 format 
*@param : cosh_data  :  the hyperbolic cosh value of the input angle,,range[0.5 0.846],Q31 format
*                       cosh_data must be multiplied by 2 to obtain the correct result
*@param : sinh_data  :  the hyperbolic sinh value of the input angle,range[[-0.683 0.683],Q31 format
*                       sinh_data must be multiplied by 2 to obtain the correct result
*@return: None
******************************************************************************/
void HAL_CORDIC_CoshSinh_8(int angle_para, int* cosh_data, int* sinh_data);

/******************************************************************************
*@brief : calculate the hyperbolic arctangent of the input argument(precision 1)
*         
*@param : angle_para :  input hyperbolic angle data,range [-0.403 0.403]([-0.806 ~ 0.806]/2),Q31 format;
*@param : atanh_value:  the atanh value of the input argument,Q31 format
                        atanh_value must be multiplied by 2 to obtain the correct result
*@return: None
******************************************************************************/
void HAL_CORDIC_Atanh_1(int angle_para, int *atanh_value);

/******************************************************************************
*@brief : calculate the hyperbolic arctangent of the input argument(precision 27)
*         
*@param : angle_para :  input hyperbolic angle data,range [-0.403 0.403]([-0.806 ~ 0.806]/2),Q31 format;
*@param : atanh_value:  the atanh value of the input argument,Q31 format
                        atanh_value must be multiplied by 2 to obtain the correct result
*@return: None
******************************************************************************/
void HAL_CORDIC_Atanh_2(int angle_para, int *atanh_value);

/******************************************************************************
*@brief : calculate the hyperbolic arctangent of the input argument(precision 3)
*         
*@param : angle_para :  input hyperbolic angle data,range [-0.403 0.403]([-0.806 ~ 0.806]/2),Q31 format;
*@param : atanh_value:  the atanh value of the input argument,Q31 format
                        atanh_value must be multiplied by 2 to obtain the correct result
*@return: None
******************************************************************************/
void HAL_CORDIC_Atanh_3(int angle_para, int *atanh_value);

/******************************************************************************
*@brief : calculate the hyperbolic arctangent of the input argument(precision 4)
*         
*@param : angle_para :  input hyperbolic angle data,range [-0.403 0.403]([-0.806 ~ 0.806]/2),Q31 format;
*@param : atanh_value:  the atanh value of the input argument,Q31 format
                        atanh_value must be multiplied by 2 to obtain the correct result
*@return: None
******************************************************************************/
void HAL_CORDIC_Atanh_4(int angle_para, int *atanh_value);

/******************************************************************************
*@brief : calculate the hyperbolic arctangent of the input argument(precision 5)
*         
*@param : angle_para :  input hyperbolic angle data,range [-0.403 0.403]([-0.806 ~ 0.806]/2),Q31 format;
*@param : atanh_value:  the atanh value of the input argument,Q31 format
                        atanh_value must be multiplied by 2 to obtain the correct result
*@return: None
******************************************************************************/
void HAL_CORDIC_Atanh_5(int angle_para, int *atanh_value);

/******************************************************************************
*@brief : calculate the hyperbolic arctangent of the input argument(precision 6)
*         
*@param : angle_para :  input hyperbolic angle data,range [-0.403 0.403]([-0.806 ~ 0.806]/2),Q31 format;
*@param : atanh_value:  the atanh value of the input argument,Q31 format
                        atanh_value must be multiplied by 2 to obtain the correct result
*@return: None
******************************************************************************/
void HAL_CORDIC_Atanh_6(int angle_para, int *atanh_value);

/******************************************************************************
*@brief : calculate the hyperbolic arctangent of the input argument(precision 7)
*         
*@param : angle_para :  input hyperbolic angle data,range [-0.403 0.403]([-0.806 ~ 0.806]/2),Q31 format;
*@param : atanh_value:  the atanh value of the input argument,Q31 format
                        atanh_value must be multiplied by 2 to obtain the correct result
*@return: None
******************************************************************************/
void HAL_CORDIC_Atanh_7(int angle_para, int *atanh_value);

/******************************************************************************
*@brief : calculate the hyperbolic arctangent of the input argument(precision 8)
*         
*@param : angle_para :  input hyperbolic angle data,range [-0.403 0.403]([-0.806 ~ 0.806]/2),Q31 format;
*@param : atanh_value:  the atanh value of the input argument,Q31 format
                        atanh_value must be multiplied by 2 to obtain the correct result
*@return: None
******************************************************************************/
void HAL_CORDIC_Atanh_8(int angle_para, int *atanh_value);

/******************************************************************************
*@brief : calculate the natural logarithm of the input argument(precision 1)
*         
*@param : arg    :   input argument,range [0.054 0.875],Q31 format;
*@param : scale  :   scaling factor
*                    ORIGIN RANGE         SCALE       ARG RANGE
*                    0.107 ¡Ü x < 1          1         0.0535 ¡Ü ARG1 < 0.5
*                    1 ¡Ü x < 3              2         0.25 ¡Ü ARG1 < 0.75
*                    3 ¡Ü x < 7              3         0.375 ¡Ü ARG1 < 0.875
*                    7 ¡Ü x ¡Ü 9.35           4         0.4375 ¡Ü ARG1 < 0.584
*@param : ln_value:  the natural logarithm value of the input argument,Q31 format
*                    ln_value must be multiplied by 4 to obtain the correct result.
*@return: None
******************************************************************************/
void HAL_CORDIC_Ln_1(int arg, int scale, int *ln_value);

/******************************************************************************
*@brief : calculate the natural logarithm of the input argument(precision 2)
*         
*@param : arg    :   input argument,range [0.054 0.875],Q31 format;
*@param : scale  :   scaling factor
*                    ORIGIN RANGE         SCALE       ARG RANGE
*                    0.107 ¡Ü x < 1          1         0.0535 ¡Ü ARG1 < 0.5
*                    1 ¡Ü x < 3              2         0.25 ¡Ü ARG1 < 0.75
*                    3 ¡Ü x < 7              3         0.375 ¡Ü ARG1 < 0.875
*                    7 ¡Ü x ¡Ü 9.35           4         0.4375 ¡Ü ARG1 < 0.584
*@param : ln_value:  the natural logarithm value of the input argument,Q31 format
*                    ln_value must be multiplied by 4 to obtain the correct result.
*@return: None
******************************************************************************/
void HAL_CORDIC_Ln_2(int arg, int scale, int *ln_value);

/******************************************************************************
*@brief : calculate the natural logarithm of the input argument(precision 3)
*         
*@param : arg    :   input argument,range [0.054 0.875],Q31 format;
*@param : scale  :   scaling factor
*                    ORIGIN RANGE         SCALE       ARG RANGE
*                    0.107 ¡Ü x < 1          1         0.0535 ¡Ü ARG1 < 0.5
*                    1 ¡Ü x < 3              2         0.25 ¡Ü ARG1 < 0.75
*                    3 ¡Ü x < 7              3         0.375 ¡Ü ARG1 < 0.875
*                    7 ¡Ü x ¡Ü 9.35           4         0.4375 ¡Ü ARG1 < 0.584
*@param : ln_value:  the natural logarithm value of the input argument,Q31 format
*                    ln_value must be multiplied by 4 to obtain the correct result.
*@return: None
******************************************************************************/
void HAL_CORDIC_Ln_3(int arg, int scale, int *ln_value);

/******************************************************************************
*@brief : calculate the natural logarithm of the input argument(precision 4)
*         
*@param : arg    :   input argument,range [0.054 0.875],Q31 format;
*@param : scale  :   scaling factor
*                    ORIGIN RANGE         SCALE       ARG RANGE
*                    0.107 ¡Ü x < 1          1         0.0535 ¡Ü ARG1 < 0.5
*                    1 ¡Ü x < 3              2         0.25 ¡Ü ARG1 < 0.75
*                    3 ¡Ü x < 7              3         0.375 ¡Ü ARG1 < 0.875
*                    7 ¡Ü x ¡Ü 9.35           4         0.4375 ¡Ü ARG1 < 0.584
*@param : ln_value:  the natural logarithm value of the input argument,Q31 format
*                    ln_value must be multiplied by 4 to obtain the correct result.
*@return: None
******************************************************************************/
void HAL_CORDIC_Ln_4(int arg, int scale, int *ln_value);

/******************************************************************************
*@brief : calculate the natural logarithm of the input argument(precision 5)
*         
*@param : arg    :   input argument,range [0.054 0.875],Q31 format;
*@param : scale  :   scaling factor
*                    ORIGIN RANGE         SCALE       ARG RANGE
*                    0.107 ¡Ü x < 1          1         0.0535 ¡Ü ARG1 < 0.5
*                    1 ¡Ü x < 3              2         0.25 ¡Ü ARG1 < 0.75
*                    3 ¡Ü x < 7              3         0.375 ¡Ü ARG1 < 0.875
*                    7 ¡Ü x ¡Ü 9.35           4         0.4375 ¡Ü ARG1 < 0.584
*@param : ln_value:  the natural logarithm value of the input argument,Q31 format
*                    ln_value must be multiplied by 4 to obtain the correct result.
*@return: None
******************************************************************************/
void HAL_CORDIC_Ln_5(int arg, int scale, int *ln_value);

/******************************************************************************
*@brief : calculate the natural logarithm of the input argument(precision 6)
*         
*@param : arg    :   input argument,range [0.054 0.875],Q31 format;
*@param : scale  :   scaling factor
*                    ORIGIN RANGE         SCALE       ARG RANGE
*                    0.107 ¡Ü x < 1          1         0.0535 ¡Ü ARG1 < 0.5
*                    1 ¡Ü x < 3              2         0.25 ¡Ü ARG1 < 0.75
*                    3 ¡Ü x < 7              3         0.375 ¡Ü ARG1 < 0.875
*                    7 ¡Ü x ¡Ü 9.35           4         0.4375 ¡Ü ARG1 < 0.584
*@param : ln_value:  the natural logarithm value of the input argument,Q31 format
*                    ln_value must be multiplied by 4 to obtain the correct result.
*@return: None
******************************************************************************/
void HAL_CORDIC_Ln_6(int arg, int scale, int *ln_value);

/******************************************************************************
*@brief : calculate the natural logarithm of the input argument(precision 7)
*         
*@param : arg    :   input argument,range [0.054 0.875],Q31 format;
*@param : scale  :   scaling factor
*                    ORIGIN RANGE         SCALE       ARG RANGE
*                    0.107 ¡Ü x < 1          1         0.0535 ¡Ü ARG1 < 0.5
*                    1 ¡Ü x < 3              2         0.25 ¡Ü ARG1 < 0.75
*                    3 ¡Ü x < 7              3         0.375 ¡Ü ARG1 < 0.875
*                    7 ¡Ü x ¡Ü 9.35           4         0.4375 ¡Ü ARG1 < 0.584
*@param : ln_value:  the natural logarithm value of the input argument,Q31 format
*                    ln_value must be multiplied by 4 to obtain the correct result.
*@return: None
******************************************************************************/
void HAL_CORDIC_Ln_7(int arg, int scale, int *ln_value);

/******************************************************************************
*@brief : calculate the natural logarithm of the input argument(precision 8)
*         
*@param : arg    :   input argument,range [0.054 0.875],Q31 format;
*@param : scale  :   scaling factor
*                    ORIGIN RANGE         SCALE       ARG RANGE
*                    0.107 ¡Ü x < 1          1         0.0535 ¡Ü ARG1 < 0.5
*                    1 ¡Ü x < 3              2         0.25 ¡Ü ARG1 < 0.75
*                    3 ¡Ü x < 7              3         0.375 ¡Ü ARG1 < 0.875
*                    7 ¡Ü x ¡Ü 9.35           4         0.4375 ¡Ü ARG1 < 0.584
*@param : ln_value:  the natural logarithm value of the input argument,Q31 format
*                    ln_value must be multiplied by 4 to obtain the correct result.
*@return: None
******************************************************************************/
void HAL_CORDIC_Ln_8(int arg, int scale, int *ln_value);

/******************************************************************************
*@brief : calculate the square root value of the input argument(precision 1)
*         
*@param : arg    :     input argument,range [0.027 0.875],Q31 format;
*@param : scale  :     scaling factor
*                      ORIGIN RANGE         SCALE       ARG RANGE
*                      0.027 ¡Ü x < 0.75       0         0.027 ¡Ü ARG1 < 0.75
*                      0.75 ¡Ü x < 1.75        1         0.375 ¡Ü ARG1 < 0.875
*                      1.75 ¡Ü x ¡Ü 2.341       2         0.4375 ¡Ü ARG1 ¡Ü 0.585
*@param : sqrt_value:  the squart root value of the input argument,Q31 format
*                      sqrt_value must be multiplied by 2^scale/W_INV_Q31 to obtain the correct result
*@return: None
******************************************************************************/
void HAL_CORDIC_Sqrt_1(int arg, int scale, int *sqrt_value);

/******************************************************************************
*@brief : calculate the square root value of the input argument(precision 2)
*         
*@param : arg    :     input argument,range [0.027 0.875],Q31 format;
*@param : scale  :     scaling factor
*                      ORIGIN RANGE         SCALE       ARG RANGE
*                      0.027 ¡Ü x < 0.75       0         0.027 ¡Ü ARG1 < 0.75
*                      0.75 ¡Ü x < 1.75        1         0.375 ¡Ü ARG1 < 0.875
*                      1.75 ¡Ü x ¡Ü 2.341       2         0.4375 ¡Ü ARG1 ¡Ü 0.585
*@param : sqrt_value:  the squart root value of the input argument,Q31 format
*                      sqrt_value must be multiplied by 2^scale/W_INV_Q31 to obtain the correct result
*@return: None
******************************************************************************/
void HAL_CORDIC_Sqrt_2(int arg, int scale, int *sqrt_value);

/******************************************************************************
*@brief : calculate the square root value of the input argument(precision 3)
*         
*@param : arg    :     input argument,range [0.027 0.875],Q31 format;
*@param : scale  :     scaling factor
*                      ORIGIN RANGE         SCALE       ARG RANGE
*                      0.027 ¡Ü x < 0.75       0         0.027 ¡Ü ARG1 < 0.75
*                      0.75 ¡Ü x < 1.75        1         0.375 ¡Ü ARG1 < 0.875
*                      1.75 ¡Ü x ¡Ü 2.341       2         0.4375 ¡Ü ARG1 ¡Ü 0.585
*@param : sqrt_value:  the squart root value of the input argument,Q31 format
*                      sqrt_value must be multiplied by 2^scale/W_INV_Q31 to obtain the correct result
*@return: None
******************************************************************************/
void HAL_CORDIC_Sqrt_3(int arg, int scale, int *sqrt_value);

/******************************************************************************
*@brief : calculate the square root value of the input argument(precision 4)
*         
*@param : arg    :     input argument,range [0.027 0.875],Q31 format;
*@param : scale  :     scaling factor
*                      ORIGIN RANGE         SCALE       ARG RANGE
*                      0.027 ¡Ü x < 0.75       0         0.027 ¡Ü ARG1 < 0.75
*                      0.75 ¡Ü x < 1.75        1         0.375 ¡Ü ARG1 < 0.875
*                      1.75 ¡Ü x ¡Ü 2.341       2         0.4375 ¡Ü ARG1 ¡Ü 0.585
*@param : sqrt_value:  the squart root value of the input argument,Q31 format
*                      sqrt_value must be multiplied by 2^scale/W_INV_Q31 to obtain the correct result
*@return: None
******************************************************************************/
void HAL_CORDIC_Sqrt_4(int arg, int scale, int *sqrt_value);

/******************************************************************************
*@brief : calculate the square root value of the input argument(precision 5)
*         
*@param : arg    :     input argument,range [0.027 0.875],Q31 format;
*@param : scale  :     scaling factor
*                      ORIGIN RANGE         SCALE       ARG RANGE
*                      0.027 ¡Ü x < 0.75       0         0.027 ¡Ü ARG1 < 0.75
*                      0.75 ¡Ü x < 1.75        1         0.375 ¡Ü ARG1 < 0.875
*                      1.75 ¡Ü x ¡Ü 2.341       2         0.4375 ¡Ü ARG1 ¡Ü 0.585
*@param : sqrt_value:  the squart root value of the input argument,Q31 format
*                      sqrt_value must be multiplied by 2^scale/W_INV_Q31 to obtain the correct result
*@return: None
******************************************************************************/
void HAL_CORDIC_Sqrt_5(int arg, int scale, int *sqrt_value);

/******************************************************************************
*@brief : calculate the square root value of the input argument(precision 6)
*         
*@param : arg    :     input argument,range [0.027 0.875],Q31 format;
*@param : scale  :     scaling factor
*                      ORIGIN RANGE         SCALE       ARG RANGE
*                      0.027 ¡Ü x < 0.75       0         0.027 ¡Ü ARG1 < 0.75
*                      0.75 ¡Ü x < 1.75        1         0.375 ¡Ü ARG1 < 0.875
*                      1.75 ¡Ü x ¡Ü 2.341       2         0.4375 ¡Ü ARG1 ¡Ü 0.585
*@param : sqrt_value:  the squart root value of the input argument,Q31 format
*                      sqrt_value must be multiplied by 2^scale/W_INV_Q31 to obtain the correct result
*@return: None
******************************************************************************/
void HAL_CORDIC_Sqrt_6(int arg, int scale, int *sqrt_value);

/******************************************************************************
*@brief : calculate the square root value of the input argument(precision 7)
*         
*@param : arg    :     input argument,range [0.027 0.875],Q31 format;
*@param : scale  :     scaling factor
*                      ORIGIN RANGE         SCALE       ARG RANGE
*                      0.027 ¡Ü x < 0.75       0         0.027 ¡Ü ARG1 < 0.75
*                      0.75 ¡Ü x < 1.75        1         0.375 ¡Ü ARG1 < 0.875
*                      1.75 ¡Ü x ¡Ü 2.341       2         0.4375 ¡Ü ARG1 ¡Ü 0.585
*@param : sqrt_value:  the squart root value of the input argument,Q31 format
*                      sqrt_value must be multiplied by 2^scale/W_INV_Q31 to obtain the correct result
*@return: None
******************************************************************************/
void HAL_CORDIC_Sqrt_7(int arg, int scale, int *sqrt_value);

/******************************************************************************
*@brief : calculate the square root value of the input argument(precision 8)
*         
*@param : arg    :     input argument,range [0.027 0.875],Q31 format;
*@param : scale  :     scaling factor
*                      ORIGIN RANGE         SCALE       ARG RANGE
*                      0.027 ¡Ü x < 0.75       0         0.027 ¡Ü ARG1 < 0.75
*                      0.75 ¡Ü x < 1.75        1         0.375 ¡Ü ARG1 < 0.875
*                      1.75 ¡Ü x ¡Ü 2.341       2         0.4375 ¡Ü ARG1 ¡Ü 0.585
*@param : sqrt_value:  the squart root value of the input argument,Q31 format
*                      sqrt_value must be multiplied by 2^scale/W_INV_Q31 to obtain the correct result
*@return: None
******************************************************************************/
void HAL_CORDIC_Sqrt_8(int arg, int scale, int *sqrt_value);


#endif