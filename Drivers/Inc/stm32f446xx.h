
#ifndef DRIVERS_INC_STM32F446XX_H_
#define DRIVERS_INC_STM32F446XX_H_

#include <stdint.h>

#define HSE_FREQ	((uint32_t)8000000)
#define HSI_FREQ	((uint32_t)16000000)

void assert_failed(uint8_t *file, uint32_t line);

#define ASSERT_TRUE(expr)	((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
#define ASSERT_FALSE(expr)	(!(expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))


#define ENABLE		1
#define DISABLE		0

#define SET			1
#define RESET		0

#define AHB1PERIPH_BASEADDR			0x40020000UL
#define APB2PERIPH_BASEADDR			0x40010000UL
#define APB1PERIPH_BASEADDR			0x40000000UL

/* Perifericos AHB1 */
#define GPIOA_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0000)
#define GPIOB_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0400)
#define GPIOC_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0800)
#define GPIOD_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR			(AHB1PERIPH_BASEADDR + 0x1000)
#define GPIOF_BASEADDR			(AHB1PERIPH_BASEADDR + 0x1400)
#define GPIOG_BASEADDR			(AHB1PERIPH_BASEADDR + 0x1800)
#define GPIOH_BASEADDR			(AHB1PERIPH_BASEADDR + 0x1C00)

#define RCC_BASEADDR			(AHB1PERIPH_BASEADDR + 0x3800)

/* Perifericos APB2 */
#define SYSCFG_BASEADDR			(APB2PERIPH_BASEADDR + 0x3800)
#define EXTI_BASEADDR			(APB2PERIPH_BASEADDR + 0x3C00)

#define TIM1_BASEADDR           (APB2PERIPH_BASEADDR + 0x0000)
#define TIM8_BASEADDR           (APB2PERIPH_BASEADDR + 0x0400)
#define TIM9_BASEADDR           (APB2PERIPH_BASEADDR + 0x4000)
#define TIM10_BASEADDR          (APB2PERIPH_BASEADDR + 0x4400)
#define TIM11_BASEADDR          (APB2PERIPH_BASEADDR + 0x4800)

/* Perifericos APB1 */
#define TIM2_BASEADDR          	(APB1PERIPH_BASEADDR + 0x0000)
#define TIM3_BASEADDR         	(APB1PERIPH_BASEADDR + 0x0400)
#define TIM4_BASEADDR          	(APB1PERIPH_BASEADDR + 0x0800)
#define TIM5_BASEADDR          	(APB1PERIPH_BASEADDR + 0x0C00)
#define TIM6_BASEADDR          	(APB1PERIPH_BASEADDR + 0x1000)
#define TIM7_BASEADDR          	(APB1PERIPH_BASEADDR + 0x1400)
#define TIM12_BASEADDR         	(APB1PERIPH_BASEADDR + 0x1800)
#define TIM13_BASEADDR         	(APB1PERIPH_BASEADDR + 0x1C00)
#define TIM14_BASEADDR         	(APB1PERIPH_BASEADDR + 0x2000)

#define PWR_BASEADDR			(APB1PERIPH_BASEADDR + 0x7000)

/********************* CORTEX-M4 ************************/
/* NVIC */
#define NVIC_ISER0				(*((volatile uint32_t *)0xE000E100UL))
#define NVIC_ISER1				(*((volatile uint32_t *)0xE000E104UL))
#define NVIC_ISER2				(*((volatile uint32_t *)0xE000E108UL))

#define NVIC_ICER0				(*((volatile uint32_t *)0xE000E180UL))
#define NVIC_ICER1				(*((volatile uint32_t *)0xE000E184UL))
#define NVIC_ICER2				(*((volatile uint32_t *)0xE000E188UL))

#define NVIC_IPR_BASEADDR		0xE000E400UL


/* SYSTICK */
#define SYSTICK_BASEADDR		0xE000E010UL

typedef struct {
	volatile uint32_t CSR;
	volatile uint32_t RVR;
	volatile uint32_t CVR;
	volatile uint32_t CALIB;
}Systick_RegDef_t;

#define SYSTICK			((Systick_RegDef_t *)SYSTICK_BASEADDR)
/********************************************************/

/* Estructuras de periféricos */
typedef struct {
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFR[2];
}GPIO_RegDef_t;

typedef struct {
	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;
	volatile uint32_t AHB3RSTR;

	uint32_t RES0;

	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RSTR;

	uint32_t RES1[2];

    volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	volatile uint32_t AHB3ENR;

	uint32_t RES2;

    volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;

	uint32_t RES3[2];

	volatile uint32_t AHB1LPENR;
	volatile uint32_t AHB2LPENR;
	volatile uint32_t AHB3LPENR;

	uint32_t RES4;

	volatile uint32_t APB1LPENR;
	volatile uint32_t APB2LPENR;

	uint32_t RES5[2];

	volatile uint32_t BDCR;
	volatile uint32_t CSR;

	uint32_t RES6[2];

	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCFGR;
}RCC_RegDef_t;

typedef struct{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_RegDef_t;

typedef struct{
	volatile uint32_t MEMRMP;
	volatile uint32_t PMC;
	volatile uint32_t EXTICR[4];
	uint32_t RES0[2];
	volatile uint32_t CMPCR;
	uint32_t RES1[2];
	volatile uint32_t CFGR;
}SYSCFG_RegDef_t;

typedef struct{
	volatile uint32_t CR;
	volatile uint32_t CSR;
}PWR_RegDef_t;

typedef struct
{
  volatile uint32_t CR1;         /*!< TIM control register 1,              Address offset: 0x00 */
  volatile uint32_t CR2;         /*!< TIM control register 2,              Address offset: 0x04 */
  volatile uint32_t SMCR;        /*!< TIM slave mode control register,     Address offset: 0x08 */
  volatile uint32_t DIER;        /*!< TIM DMA/interrupt enable register,   Address offset: 0x0C */
  volatile uint32_t SR;          /*!< TIM status register,                 Address offset: 0x10 */
  volatile uint32_t EGR;         /*!< TIM event generation register,       Address offset: 0x14 */
  volatile uint32_t CCMR1;       /*!< TIM capture/compare mode register 1, Address offset: 0x18 */
  volatile uint32_t CCMR2;       /*!< TIM capture/compare mode register 2, Address offset: 0x1C */
  volatile uint32_t CCER;        /*!< TIM capture/compare enable register, Address offset: 0x20 */
  volatile uint32_t CNT;         /*!< TIM counter register,                Address offset: 0x24 */
  volatile uint32_t PSC;         /*!< TIM prescaler,                       Address offset: 0x28 */
  volatile uint32_t ARR;         /*!< TIM auto-reload register,            Address offset: 0x2C */
  volatile uint32_t RCR;         /*!< TIM repetition counter register,     Address offset: 0x30 */
  volatile uint32_t CCR1;        /*!< TIM capture/compare register 1,      Address offset: 0x34 */
  volatile uint32_t CCR2;        /*!< TIM capture/compare register 2,      Address offset: 0x38 */
  volatile uint32_t CCR3;        /*!< TIM capture/compare register 3,      Address offset: 0x3C */
  volatile uint32_t CCR4;        /*!< TIM capture/compare register 4,      Address offset: 0x40 */
  volatile uint32_t BDTR;        /*!< TIM break and dead-time register,    Address offset: 0x44 */
  volatile uint32_t DCR;         /*!< TIM DMA control register,            Address offset: 0x48 */
  volatile uint32_t DMAR;        /*!< TIM DMA address for full transfer,   Address offset: 0x4C */
  volatile uint32_t OR;          /*!< TIM option register,                 Address offset: 0x50 */
}TIM_RegDef_t;

/* Definición de periféricos */

#define GPIOA		((GPIO_RegDef_t *)GPIOA_BASEADDR)
#define GPIOB		((GPIO_RegDef_t *)GPIOB_BASEADDR)
#define GPIOC		((GPIO_RegDef_t *)GPIOC_BASEADDR)
#define GPIOD		((GPIO_RegDef_t *)GPIOD_BASEADDR)
#define GPIOE		((GPIO_RegDef_t *)GPIOE_BASEADDR)
#define GPIOF		((GPIO_RegDef_t *)GPIOF_BASEADDR)
#define GPIOG		((GPIO_RegDef_t *)GPIOG_BASEADDR)
#define GPIOH		((GPIO_RegDef_t *)GPIOH_BASEADDR)

#define RCC			((RCC_RegDef_t *)RCC_BASEADDR)

#define EXTI		((EXTI_RegDef_t *)EXTI_BASEADDR)
#define SYSCFG		((SYSCFG_RegDef_t *)SYSCFG_BASEADDR)

#define PWR			((PWR_RegDef_t *)PWR_BASEADDR)

#define TIM1		((TIM_RegDef_t *)TIM1_BASEADDR)
#define TIM2		((TIM_RegDef_t *)TIM2_BASEADDR)
#define TIM3		((TIM_RegDef_t *)TIM3_BASEADDR)
#define TIM4		((TIM_RegDef_t *)TIM4_BASEADDR)
#define TIM5		((TIM_RegDef_t *)TIM5_BASEADDR)
#define TIM6		((TIM_RegDef_t *)TIM6_BASEADDR)
#define TIM7		((TIM_RegDef_t *)TIM7_BASEADDR)
#define TIM8		((TIM_RegDef_t *)TIM8_BASEADDR)
#define TIM9		((TIM_RegDef_t *)TIM9_BASEADDR)
#define TIM10		((TIM_RegDef_t *)TIM10_BASEADDR)
#define TIM11		((TIM_RegDef_t *)TIM11_BASEADDR)
#define TIM12		((TIM_RegDef_t *)TIM12_BASEADDR)
#define TIM13		((TIM_RegDef_t *)TIM13_BASEADDR)
#define TIM14		((TIM_RegDef_t *)TIM14_BASEADDR)

/* Habilitar clock de perifericos */

#define GPIOA_EN_CLK()		(RCC->AHB1ENR |= (1 << 0))
#define GPIOB_EN_CLK()		(RCC->AHB1ENR |= (1 << 1))
#define GPIOC_EN_CLK()		(RCC->AHB1ENR |= (1 << 2))
#define GPIOD_EN_CLK()		(RCC->AHB1ENR |= (1 << 3))
#define GPIOE_EN_CLK()		(RCC->AHB1ENR |= (1 << 4))
#define GPIOF_EN_CLK()		(RCC->AHB1ENR |= (1 << 5))
#define GPIOG_EN_CLK()		(RCC->AHB1ENR |= (1 << 6))
#define GPIOH_EN_CLK()		(RCC->AHB1ENR |= (1 << 7))

#define SYSCFG_EN_CLK()		(RCC->APB2ENR |= (1 << 14))

#define PWR_EN_CLK()		(RCC->APB1ENR |= (1 << 28))

#define TIM1_EN_CLK()		(RCC->APB2ENR |= (1 << 0))
#define TIM8_EN_CLK()		(RCC->APB2ENR |= (1 << 1))
#define TIM9_EN_CLK()		(RCC->APB2ENR |= (1 << 16))
#define TIM10_EN_CLK()		(RCC->APB2ENR |= (1 << 17))
#define TIM11_EN_CLK()		(RCC->APB2ENR |= (1 << 18))

#define TIM2_EN_CLK()		(RCC->APB1ENR |= (1 << 0))
#define TIM3_EN_CLK()		(RCC->APB1ENR |= (1 << 1))
#define TIM4_EN_CLK()		(RCC->APB1ENR |= (1 << 2))
#define TIM5_EN_CLK()		(RCC->APB1ENR |= (1 << 3))
#define TIM6_EN_CLK()		(RCC->APB1ENR |= (1 << 4))
#define TIM7_EN_CLK()		(RCC->APB1ENR |= (1 << 5))
#define TIM12_EN_CLK()		(RCC->APB1ENR |= (1 << 6))
#define TIM13_EN_CLK()		(RCC->APB1ENR |= (1 << 7))
#define TIM14_EN_CLK()		(RCC->APB1ENR |= (1 << 8))

/* Deshabilitar clock de perifericos */

#define GPIOA_DIS_CLK()		(RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_DIS_CLK()		(RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_DIS_CLK()		(RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_DIS_CLK()		(RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_DIS_CLK()		(RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_DIS_CLK()		(RCC->AHB1ENR &= ~(1 << 5))
#define GPIOG_DIS_CLK()		(RCC->AHB1ENR &= ~(1 << 6))
#define GPIOH_DIS_CLK()		(RCC->AHB1ENR &= ~(1 << 7))

#define SYSCFG_DIS_CLK()	(RCC->APB2ENR &= ~(1 << 14))

#define PWR_DIS_CLK()		(RCC->APB1ENR &= ~(1 << 28))

#define TIM1_DIS_CLK()		(RCC->APB2ENR &= ~(1 << 0))
#define TIM8_DIS_CLK()		(RCC->APB2ENR &= ~(1 << 1))
#define TIM9_DIS_CLK()		(RCC->APB2ENR &= ~(1 << 16))
#define TIM10_DIS_CLK()		(RCC->APB2ENR &= ~(1 << 17))
#define TIM11_DIS_CLK()		(RCC->APB2ENR &= ~(1 << 18))

#define TIM2_DIS_CLK()		(RCC->APB1ENR &= ~(1 << 0))
#define TIM3_DIS_CLK()		(RCC->APB1ENR &= ~(1 << 1))
#define TIM4_DIS_CLK()		(RCC->APB1ENR &= ~(1 << 2))
#define TIM5_DIS_CLK()		(RCC->APB1ENR &= ~(1 << 3))
#define TIM6_DIS_CLK()		(RCC->APB1ENR &= ~(1 << 4))
#define TIM7_DIS_CLK()		(RCC->APB1ENR &= ~(1 << 5))
#define TIM12_DIS_CLK()		(RCC->APB1ENR &= ~(1 << 6))
#define TIM13_DIS_CLK()		(RCC->APB1ENR &= ~(1 << 7))
#define TIM14_DIS_CLK()		(RCC->APB1ENR &= ~(1 << 8))

/* Reset de periferico */

#define GPIOA_RESET()		do{ RCC->AHB1RSTR |= (1 << 0); RCC->AHB1RSTR &= ~(1 << 0);}while(0)
#define GPIOB_RESET()		do{ RCC->AHB1RSTR |= (1 << 1); RCC->AHB1RSTR &= ~(1 << 1);}while(0)
#define GPIOC_RESET()		do{ RCC->AHB1RSTR |= (1 << 2); RCC->AHB1RSTR &= ~(1 << 2);}while(0)
#define GPIOD_RESET()		do{ RCC->AHB1RSTR |= (1 << 3); RCC->AHB1RSTR &= ~(1 << 3);}while(0)
#define GPIOE_RESET()		do{ RCC->AHB1RSTR |= (1 << 4); RCC->AHB1RSTR &= ~(1 << 4);}while(0)
#define GPIOF_RESET()		do{ RCC->AHB1RSTR |= (1 << 5); RCC->AHB1RSTR &= ~(1 << 5);}while(0)
#define GPIOG_RESET()		do{ RCC->AHB1RSTR |= (1 << 6); RCC->AHB1RSTR &= ~(1 << 6);}while(0)
#define GPIOH_RESET()		do{ RCC->AHB1RSTR |= (1 << 7); RCC->AHB1RSTR &= ~(1 << 7);}while(0)

#define TIM1_RESET()		do{ RCC->APB2RSTR |= (1 << 0); RCC->APB2RSTR &= ~(1 << 0);}while(0)
#define TIM8_RESET()		do{ RCC->APB2RSTR |= (1 << 1); RCC->APB2RSTR &= ~(1 << 1);}while(0)
#define TIM9_RESET()		do{ RCC->APB2RSTR |= (1 << 16); RCC->APB2RSTR &= ~(1 << 16);}while(0)
#define TIM10_RESET()		do{ RCC->APB2RSTR |= (1 << 17); RCC->APB2RSTR &= ~(1 << 17);}while(0)
#define TIM11_RESET()		do{ RCC->APB2RSTR |= (1 << 18); RCC->APB2RSTR &= ~(1 << 18);}while(0)

#define TIM2_RESET()		do{ RCC->APB1RSTR |= (1 << 0); RCC->APB1RSTR &= ~(1 << 0);}while(0)
#define TIM3_RESET()		do{ RCC->APB1RSTR |= (1 << 1); RCC->APB1RSTR &= ~(1 << 1);}while(0)
#define TIM4_RESET()		do{ RCC->APB1RSTR |= (1 << 2); RCC->APB1RSTR &= ~(1 << 2);}while(0)
#define TIM5_RESET()		do{ RCC->APB1RSTR |= (1 << 3); RCC->APB1RSTR &= ~(1 << 3);}while(0)
#define TIM6_RESET()		do{ RCC->APB1RSTR |= (1 << 4); RCC->APB1RSTR &= ~(1 << 4);}while(0)
#define TIM7_RESET()		do{ RCC->APB1RSTR |= (1 << 5); RCC->APB1RSTR &= ~(1 << 5);}while(0)
#define TIM12_RESET()		do{ RCC->APB1RSTR |= (1 << 6); RCC->APB1RSTR &= ~(1 << 6);}while(0)
#define TIM13_RESET()		do{ RCC->APB1RSTR |= (1 << 7); RCC->APB1RSTR &= ~(1 << 7);}while(0)
#define TIM14_RESET()		do{ RCC->APB1RSTR |= (1 << 8); RCC->APB1RSTR &= ~(1 << 8);}while(0)

/* Macro para obtener el numero de puerto */
#define PORT_NUMBER(x)		((x == GPIOA) ? 0 : \
							 (x == GPIOB) ? 1 : \
							 (x == GPIOC) ? 2 : \
							 (x == GPIOD) ? 3 : \
							 (x == GPIOE) ? 4 : \
							 (x == GPIOF) ? 5 : \
							 (x == GPIOG) ? 6 : 7)


/* IRQs */

#define IRQ_TIM2			28
#define IRQ_EXTI15_10		40
#define IRQ_TIM6_DAC		54

/* Posiciones de bits de los registros */

#define RCC_CR_HSION			 0
#define RCC_CR_HSIRDY			 1
#define RCC_CR_HSITRIM			 3
#define RCC_CR_HSICAL			 8
#define RCC_CR_HSEON			16
#define RCC_CR_HSERDY			17
#define RCC_CR_HSEBYP			18
#define RCC_CR_CSSON			19
#define RCC_CR_PLLON			24
#define RCC_CR_PLLRDY			25
#define RCC_CR_PLLI2SON			26
#define RCC_CR_PLLI2SRDY		27
#define RCC_CR_PLLSAION			28
#define RCC_CR_PLLSAIRDY		29

#define RCC_PLLCFGR_PLLM		 0
#define RCC_PLLCFGR_PLLN		 6
#define RCC_PLLCFGR_PLLP		16
#define RCC_PLLCFGR_PLLSRC		22
#define RCC_PLLCFGR_PLLQ		24
#define RCC_PLLCFGR_PLLR		28

#define RCC_CFGR_SW				 0
#define RCC_CFGR_SWS			 2
#define RCC_CFGR_HPRE			 4
#define RCC_CFGR_PPRE1			10
#define RCC_CFGR_PPRE2			13
#define RCC_CFGR_RTCPRE			16
#define RCC_CFGR_MCO1			21
#define RCC_CFGR_MCO1PRE		24
#define RCC_CFGR_MCO2PRE		27
#define RCC_CFGR_MCO2			30

#define RCC_BDCR_LSEON			 0
#define RCC_BDCR_LSERDY			 1
#define RCC_BDCR_LSEBYP			 2
#define RCC_BDCR_LSEMOD			 3
#define RCC_BDCR_RTCSEL			 8
#define RCC_BDCR_RTCEN			15
#define RCC_BDCR_BDRST			16

#define RCC_CSR_LSION			 0
#define RCC_CSR_LSIRDY			 1

#define PWR_CR_DBP				 8

#define TIM_CR1_CEN              0
#define TIM_CR1_UDIS             1
#define TIM_CR1_URS              2
#define TIM_CR1_OPM              3
#define TIM_CR1_DIR              4
#define TIM_CR1_CMS              5
#define TIM_CR1_ARPE             7
#define TIM_CR1_CKD              8

#define TIM_CCER_CC1E			 0
#define TIM_CCER_CC1P			 1
#define TIM_CCER_CC1NE			 2
#define TIM_CCER_CC1NP			 3
#define TIM_CCER_CC2E			 4
#define TIM_CCER_CC2P			 5
#define TIM_CCER_CC2NE			 6
#define TIM_CCER_CC2NP			 7
#define TIM_CCER_CC3E			 8
#define TIM_CCER_CC3P			 9
#define TIM_CCER_CC3NE			10
#define TIM_CCER_CC3NP			11
#define TIM_CCER_CC4E			12
#define TIM_CCER_CC4P			13
#define TIM_CCER_CC4NP			15

#define TIM_CCMR1_CC1S			 0
#define TIM_CCMR1_IC1PSC		 2
#define TIM_CCMR1_IC1F			 4
#define TIM_CCMR1_CC2S			 8
#define TIM_CCMR1_IC2PSC		10
#define TIM_CCMR1_IC2F			12

#define TIM_CCMR1_OC1FE			 2
#define TIM_CCMR1_OC1PE			 3
#define TIM_CCMR1_OC1M			 4
#define TIM_CCMR1_OC1CE			 7
#define TIM_CCMR1_OC2FE			10
#define TIM_CCMR1_OC2PE			11
#define TIM_CCMR1_OC2M			12
#define TIM_CCMR1_OC2CE			15

#define TIM_CCMR2_CC3S			 0
#define TIM_CCMR2_IC3PSC		 2
#define TIM_CCMR2_IC3F			 4
#define TIM_CCMR2_CC4S			 8
#define TIM_CCMR2_IC4PSC		10
#define TIM_CCMR2_IC4F			12

#define TIM_CCMR2_OC3FE			 2
#define TIM_CCMR2_OC3PE			 3
#define TIM_CCMR2_OC3M			 4
#define TIM_CCMR2_OC3CE			 7
#define TIM_CCMR2_OC4FE			10
#define TIM_CCMR2_OC4PE			11
#define TIM_CCMR2_OC4M			12
#define TIM_CCMR2_OC4CE			15

#define TIM_DIER_UIE			 0
#define TIM_DIER_CC1IE			 1
#define TIM_DIER_CC2IE			 2
#define TIM_DIER_CC3IE			 3
#define TIM_DIER_CC4IE			 4
#define TIM_DIER_COMIE			 5
#define TIM_DIER_TIE			 6
#define TIM_DIER_BIE			 7
#define TIM_DIER_UDE			 8
#define TIM_DIER_CC1DE			 9
#define TIM_DIER_CC2DE			10
#define TIM_DIER_CC3DE			11
#define TIM_DIER_CC4DE			12
#define TIM_DIER_COMDE			13
#define TIM_DIER_TDE			14

#define TIM_SR_UIF			 	 0
#define TIM_SR_CC1IF			 1
#define TIM_SR_CC2IF			 2
#define TIM_SR_CC3IF			 3
#define TIM_SR_CC4IF			 4
#define TIM_SR_COMIF			 5
#define TIM_SR_TIF			 	 6
#define TIM_SR_BIF			 	 7
#define TIM_SR_CC1OF			 9
#define TIM_SR_CC2OF			10
#define TIM_SR_CC3OF			11
#define TIM_SR_CC4OF			12

#define TIM_SMCR_SMS			 0
#define TIM_SMCR_TS				 4
#define TIM_SMCR_MSM			 7
#define TIM_SMCR_ETF			 8
#define TIM_SMCR_ETPS			12
#define TIM_SMCR_ECE			14
#define TIM_SMCR_ETP			15

#define TIM_CR2_CCDS             3
#define TIM_CR2_MMS              4
#define TIM_CR2_TI1S             7

#define SYSTICK_CSR_ENABLE		 0
#define SYSTICK_CSR_TICKINT		 1
#define SYSTICK_CSR_CLKSOURCE	 2
#define SYSTICK_CSR_COUNTFLAG	16

#define SYSTICK_CALIB_TENMS		 0
#define SYSTICK_CALIB_SKEW		30
#define SYSTICK_CALIB_NOREF		31

/* Mascara de bits */
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


#endif /* DRIVERS_INC_STM32F446XX_H_ */
