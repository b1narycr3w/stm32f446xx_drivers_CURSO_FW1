
#ifndef INC_STM32F446XX_TIM_H_
#define INC_STM32F446XX_TIM_H_

#include "stm32f446xx.h"


#define TIM_UIF_FLAG			((uint16_t)0x0001)
#define TIM_CC1IF_FLAG			((uint16_t)0x0002)
#define TIM_CC2IF_FLAG			((uint16_t)0x0004)
#define TIM_CC3IF_FLAG			((uint16_t)0x0008)
#define TIM_CC4IF_FLAG			((uint16_t)0x0010)
#define TIM_COMIF_FLAG			((uint16_t)0x0020)
#define TIM_TIF_FLAG			((uint16_t)0x0040)
#define TIM_BIF_FLAG			((uint16_t)0x0080)
#define TIM_CC1OF_FLAG			((uint16_t)0x0200)
#define TIM_CC2OF_FLAG			((uint16_t)0x0400)
#define TIM_CC3OF_FLAG			((uint16_t)0x0800)
#define TIM_CC4OF_FLAG			((uint16_t)0x1000)

#define TIM_IT_UI				((uint16_t)0x0001)
#define TIM_IT_CC1I				((uint16_t)0x0002)
#define TIM_IT_CC2I				((uint16_t)0x0004)
#define TIM_IT_CC3I	 			((uint16_t)0x0008)
#define TIM_IT_CC4I	 			((uint16_t)0x0010)
#define TIM_IT_COMI 			((uint16_t)0x0020)
#define TIM_IT_TI				((uint16_t)0x0040)
#define TIM_IT_BI				((uint16_t)0x0080)
#define TIM_IT_UD				((uint16_t)0x0100)
#define TIM_IT_CC1D 			((uint16_t)0x0200)
#define TIM_IT_CC2D 			((uint16_t)0x0400)
#define TIM_IT_CC3D 			((uint16_t)0x0800)
#define TIM_IT_CC4D 			((uint16_t)0x1000)

#define TIM_IS_BASIC_TIMER(x)	(((x) == TIM6) || ((x) == TIM7))

#define TIM_IS_GP_TIMER(x)		(((x) == TIM2) || ((x) == TIM3)  || ((x) == TIM4)  || ((x) == TIM5)  || \
								 ((x) == TIM9) || ((x) == TIM10) || ((x) == TIM11) || ((x) == TIM12) || \
								 ((x) == TIM13)|| ((x) == TIM14) \
								)

#define TIM_IS_ADV_TIMER(x)		(((x) == TIM1) || ((x) == TIM8))

#define TIM_HAS_MS_FUNCTIONALITY(x)		(((x) == TIM2) || ((x) == TIM3)  || ((x) == TIM4)  || ((x) == TIM5)  || \
										 ((x) == TIM1) || ((x) == TIM8) \
										)
/*
 * No channels:
 *  - Basic Timers: TIM6 y TIM7
 *
 * CH1:
 * 	- GP Timers (16bits): TIM10/11/13/14
 *
 * CH1/2:
 * 	- GP Timers (16bits): TIM9 y TIM12 / TIM 3 y TIM4
 * 	- GP Timers (32bits): TIM2 y TIM5
 * 	- ADV Timers (16bits): TIM1 y TIM8
 *
 * CH1/2/3:
 * 	- GP Timers (16bits): TIM3 y TIM4
 * 	- GP Timers (32bits): TIM2 y TIM5
 * 	- ADV Timers (16bits): TIM1 y TIM8
 *
 * CH1/2/3/4:
 * 	- GP Timers (16bits): TIM  y TIM4
 * 	- GP Timers (32bits): TIM2 y TIM5
 * 	- ADV Timers (16bits): TIM1 y TIM8
 */
#define TIM_HAS_CH1(x)			(((x) != TIM6) && ((x) != TIM7))
#define TIM_HAS_CH2(x)			(((x) == TIM1) || ((x) == TIM8) || \
								((x) == TIM2) || ((x) == TIM3)  || ((x) == TIM4)  || ((x) == TIM5)  || \
								((x) == TIM9) || ((x) == TIM12) \
								)

#define TIM_HAS_CH3(x)			(((x) == TIM1) || ((x) == TIM8) || \
								((x) == TIM2) || ((x) == TIM3)  || ((x) == TIM4)  || ((x) == TIM5) \
								)

#define TIM_HAS_CH4(x)			(((x) == TIM1) || ((x) == TIM8) || \
								((x) == TIM2) || ((x) == TIM3)  || ((x) == TIM4)  || ((x) == TIM5) \
								)

typedef enum{
	TIM_EVENT_UI,
	TIM_EVENT_CC1I,
	TIM_EVENT_CC2I,
	TIM_EVENT_CC3I,
	TIM_EVENT_CC4I,
	TIM_EVENT_COMI,
	TIM_EVENT_TI,
	TIM_EVENT_BI,
	TIM_EVENT_CC1O,
	TIM_EVENT_CC2O,
	TIM_EVENT_CC3O,
	TIM_EVENT_CC4O
}TIM_Event_t;

/*
 * @TIM_CouterMode
 */
typedef enum{
	TIM_CouterMode_CenterAlign1 = 1,
	TIM_CouterMode_CenterAlign2,
	TIM_CouterMode_CenterAlign3,
	TIM_CouterMode_UP,
	TIM_CouterMode_DOWN

}TIM_CouterMode_t;

/*
 * @TIM_CHANNELS
 */
typedef enum{
	TIM_CH1,
	TIM_CH2,
	TIM_CH3,
	TIM_CH4,
}TIM_Channels_t;

/*
 * @TIM_ICPolarity
 */
typedef enum{
	TIM_ICPolarity_RE,
	TIM_ICPolarity_FE,
	TIM_ICPolarity_RFE
}TIM_ICPolarity_t;

/*
 * @TIM_ICSelection
 */
typedef enum{
	TIM_ICSelection_Direct = 1,
	TIM_ICSelection_Indirect,
	TIM_ICSelection_TRC
}TIM_ICSelection_t;

typedef struct{
	  uint16_t TIM_Prescaler;         /*!< Prescaler para dividir el TIM clock.Valores entre 0x0000 y 0xFFFF */
	  uint32_t TIM_Period;            /*!< Valor con el que cargar el Auto-Reload Register (ARR) en cada update event. */
	  TIM_CouterMode_t TIM_CounterMode;
}TIM_TimeBase_t;

/*
 * @TIM_ICPrescaler
 */
typedef enum{
	TIM_ICPrescaler_NONE,
	TIM_ICPrescaler_2,
	TIM_ICPrescaler_4,
	TIM_ICPrescaler_8
}TIM_ICPrescaler_t;

/*
 * @TIM_ICFilter
 */
typedef enum{
	TIM_ICFilter_NONE,
	TIM_ICFilter_Fck_int_2,
	TIM_ICFilter_Fck_int_4,
	TIM_ICFilter_Fck_int_8,
	TIM_ICFilter_Fdts_div2_6,
	TIM_ICFilter_Fdts_div2_8,
	TIM_ICFilter_Fdts_div4_6,
	TIM_ICFilter_Fdts_div4_8,
	TIM_ICFilter_Fdts_div8_6,
	TIM_ICFilter_Fdts_div8_8,
	TIM_ICFilter_Fdts_div16_5,
	TIM_ICFilter_Fdts_div16_6,
	TIM_ICFilter_Fdts_div16_8,
	TIM_ICFilter_Fdts_div32_5,
	TIM_ICFilter_Fdts_div32_6,
	TIM_ICFilter_Fdts_div32_8
}TIM_ICFilter_t;

/*
 * @TIM_OCModes
 */
typedef enum
{
	TIM_OCMode_Frozen,
	TIM_OCMode_Active,
	TIM_OCMode_Inactive,
	TIM_OCMode_Toggle,
	TIM_OCMode_Force_Inactive,
	TIM_OCMode_Force_Active,
	TIM_OCMode_PWM1,
	TIM_OCMode_PWM2
}TIM_OCModes_t;

/*
 * @TIM_OCPolarity
 */
typedef enum
{
	TIM_OCPolarity_Active_HIGH,
	TIM_OCPolarity_Active_LOW
}TIM_OCPolarity_t;

/*
 * @TIM_Trigger
 */
typedef enum
{
	TIM_Trigger_Internal_0,
	TIM_Trigger_Internal_1,
	TIM_Trigger_Internal_2,
	TIM_Trigger_Internal_3,
	TIM_Trigger_Edge_Detector_TI1,
	TIM_Trigger_Filtered_Timer_Input_1,
	TIM_Trigger_Filtered_Timer_Input_2,
	TIM_Trigger_External
}TIM_Trigger_t;

/*
 * @TIM_Slave
 */
typedef enum
{
	TIM_Slave_Mode_Disabled,
	TIM_Slave_Encoder_Mode_1,
	TIM_Slave_Encoder_Mode_2,
	TIM_Slave_Encoder_Mode_3,
	TIM_Slave_Reset_Mode,
	TIM_Slave_Gated_Mode,
	TIM_Slave_Trigger_Mode,
	TIM_Slave_External_Mode1
}TIM_Slave_t;

/*
 * @TIM_MasterOutput
 */
typedef enum
{
	TIM_MasterOutput_Reset,
	TIM_MasterOutput_Enable,
	TIM_MasterOutput_Update,
	TIM_MasterOutput_Compare_Pulse,
	TIM_MasterOutput_OC1REF,
	TIM_MasterOutput_OC2REF,
	TIM_MasterOutput_OC3REF,
	TIM_MasterOutput_OC4REF
}TIM_MasterOutput_t;

typedef struct
{
	TIM_Channels_t TIM_Channel;        	/*!< Channel. @TIM_CHANNELS */
	TIM_ICPolarity_t TIM_ICPolarity;   	/*!< Polaridad de la deteccion. @TIM_ICPolarity */
	TIM_ICSelection_t TIM_ICSelection;  /*!< Tipo de entrada. @TIM_ICSelection */
	TIM_ICPrescaler_t TIM_ICPrescaler;  /*!< Prescaler. @TIM_ICPrescaler */
	TIM_ICFilter_t TIM_ICFilter;     	/*!< Filtrado. @TIM_ICFilter_t */
}TIM_IC_t;

typedef struct
{
	TIM_Channels_t TIM_Channel;        	/*!< Channel. @TIM_CHANNELS */
	TIM_OCModes_t TIM_OCMode;        	/*!< Modo de salida. @TIM_OCModes */
	TIM_OCPolarity_t TIM_OCPolarity;	/*!< Polaridad. @TIM_OCPolarity */
	uint32_t TIM_Pulse;					/*!< Ancho de pulso en CCRx (0x0000-0xFFFF) */
}TIM_OC_t;

typedef struct{
	TIM_RegDef_t *pTIMx;
	TIM_TimeBase_t TIM_TimeBase;
	TIM_IC_t TIM_InputCapture;
	TIM_OC_t TIM_OutputCompare;
}TIM_handle_t;


/************************** APIs ***********************************/
/* Comunes */
void TIM_ClkCtrl(TIM_RegDef_t *pTIMx, uint8_t status);
void TIM_ITConfig(TIM_RegDef_t *pTIMx, uint16_t IT_type, uint8_t status);
void TIM_EventCallback(TIM_handle_t *pTIMHandle, TIM_Event_t event);

void TIM_IRQHandler(TIM_handle_t *pTIMHandle);
uint8_t TIM_GetITStatus(TIM_RegDef_t *pTIMx, uint16_t TIM_IT);
void TIM_ClearITPendingBit(TIM_RegDef_t *pTIMx, uint16_t TIM_IT);

uint32_t TIM_GetCounter(TIM_RegDef_t *pTIMx);
void TIM_SetCounter(TIM_RegDef_t *pTIMx, uint32_t counter);
uint32_t TIM_GetCapture(TIM_RegDef_t *pTIMx, TIM_Channels_t TIM_Channel);
void TIM_SetCompare(TIM_RegDef_t *pTIMx, TIM_Channels_t TIM_Channel, uint32_t value);

/* TimeBase */
void TIM_TimeBaseInit(TIM_handle_t *pTIMHandle);
void TIM_DeInit(TIM_RegDef_t *pTIMx);
void TIM_Cmd(TIM_RegDef_t *pTIMx, uint8_t status);

/* Input Capture */
void TIM_ICInit(TIM_handle_t *pTIMHandle);

/* Output Compare */
void TIM_OCInit(TIM_handle_t *pTIMHandle);

/* Configurar esclavo */
void TIM_InputTrigger(TIM_RegDef_t *pTIMx, TIM_Trigger_t trigger);
void TIM_SlaveMode(TIM_RegDef_t *pTIMx, TIM_Slave_t mode);

/* Configurar maestro */
void TIM_MasterTriggerOutput(TIM_RegDef_t *pTIMx, TIM_MasterOutput_t output);
#endif /* INC_STM32F446XX_TIM_H_ */
