/**
  ******************************************************************************
  * @file    APP/pid_app.c
  * @author  004 
  * @version V1.0.0
  * @date    17-04-2020
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2020 Tai-Micro</center></h2>
  *
  *
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/**
* @function int16_t pid_calculation_app(TW_PID_TypeDef * pid)
* @brief    Description: app pid calculation
* @return   return pi_out
*/
__SECTION(RAMCODE)
void calc_PI( TW_PID_TypeDef *pi,float err)
{
	pi->p_part = (pi->kp) * err;//Q15*Q15 = Q30
	pi->i_part += (pi->ki) * err;//Q15*Q15 = Q30
	pi->d_part = (err - pi->last_err) *pi->kd;
	if(pi->i_part > pi->upper_limit)
	{
		pi->i_part = pi->upper_limit;
	}
	else if(pi->i_part <(float)(0.0))
	{
		pi->i_part = (float)(0.0);
	}
	pi->output = ((pi->p_part) + (pi->i_part)+(pi->d_part));
	if(pi->output > (float)(1.0))
	{
		pi->output = ((float)(1.0));
	}	
	else if(pi->output < (float)(0.0))
	{
		pi->output = ((float)(0.0));
	}
	pi->last_err = err;
}


__SECTION(RAMCODE)
void calc_shared_current( TW_PID_TypeDef *pi,float err)
{
	pi->p_part = (pi->kp) * err;//Q15*Q15 = Q30
	pi->i_part += (pi->ki) * err;//Q15*Q15 = Q30
	pi->d_part = (err - pi->last_err) *pi->kd;
	if(pi->i_part > pi->upper_limit)
	{
		pi->i_part = pi->upper_limit;
	}
	else if(pi->i_part <(-pi->upper_limit))
	{
		pi->i_part = (-pi->upper_limit);
	}
	pi->output = ((pi->p_part) + (pi->i_part)+(pi->d_part));
	if(pi->output > (float)(1.0))
	{
		pi->output = ((float)(1.0));
	}	
	else if(pi->output < (float)(-1.0))
	{
		pi->output = ((float)(-1.0));
	}
	pi->last_err = err;
}


__SECTION(RAMCODE)
void iir_calculation (cIIR_TypeDef *iir,float x)
{
	float B0,B1,B2,B3,B4;
	float A1,A2,A3,A4;
	iir->X[0] = x;
	B0 = iir->X[0] *iir->B[0];
	B1 = iir->X[1] *iir->B[1];
	B2 = iir->X[2] *iir->B[2];
	B3 = iir->X[3] *iir->B[3];
	B4 = iir->X[4] *iir->B[4];
	iir->B_part = B0+B1+B2+B3+B4;
	A1 = iir->Y[1] *iir->A[1];
	A2 = iir->Y[2] *iir->A[2];
	A3 = iir->Y[3] *iir->A[3];
	A4 = iir->Y[4] *iir->A[4];
	iir->A_part = A1+A2+A3+A4;
	if(iir->A_part<(float)-1.0)
	{
		iir->A_part = (float)-1.0;
	}
	if(iir->A_part>(float)1.0)
	{
		iir->A_part = (float)1.0;
	}
	iir->Y[0] = iir->A_part+iir->B_part;
	iir->X[4] = iir->X[3];
	iir->X[3] = iir->X[2];
	iir->X[2] = iir->X[1];
	iir->X[1] = iir->X[0];
	
	iir->Y[4] = iir->Y[3];
	iir->Y[3] = iir->Y[2];
	iir->Y[2] = iir->Y[1];
	iir->Y[1] = iir->Y[0];
	
	iir->result = iir->Y[0] ;
	if(iir->result>1)
	{
		iir->result =1;
	}
	if(iir->result<-1)
	{
		iir->result =-1;
	}
}
