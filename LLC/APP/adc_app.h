#ifndef _ADC_APP_H_
#define _ADC_APP_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "tae32g58xx_ll.h"


/*************ADC0*****************/
#define VOUT_SAMPLE_CHN7    					ADC_CH_7	
#define RSENSE1_SAMPLE_CHN3						ADC_CH_8
#define VP_SAMPLE_CHN1								ADC_CH_1
#define VN_SAMPLE_CHN2								ADC_CH_2

#define ADC_VOUT_RAW_VALUE()        ((uint16_t)__LL_ADC_ChDat_Read(ADC0, VOUT_SAMPLE_CHN7))
#define ADC_RSENSE1_RAW_VALUE()     ((uint16_t)__LL_ADC_ChDat_Read(ADC0, RSENSE1_SAMPLE_CHN3))
#define ADC_VP_RAW_VALUE()          ((uint16_t)__LL_ADC_ChDat_Read(ADC0, VP_SAMPLE_CHN1))
#define ADC_VN_RAW_VALUE()          ((uint16_t)__LL_ADC_ChDat_Read(ADC0, VN_SAMPLE_CHN2))

void adc0_initial_app(ADC_TypeDef *Instance);
void adc1_initial_app(ADC_TypeDef *Instance);
void get_adc_data(void);
void adc_all_init(void);
void adc_converter_start(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _MAIN_H_ */


