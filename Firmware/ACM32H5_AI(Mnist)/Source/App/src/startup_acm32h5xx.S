   	.syntax unified
	.cpu cortex-m33
	.fpu softvfp
	.thumb

.global	g_pfnVectors
.global	Default_Handler

/* start address for the initialization values of the .data section.

.word	_sidata
/* start address for the .data section. defined in linker script */
.word	_sdata
/* end address for the .data section. defined in linker script */
.word	_edata
/* start address for the .bss section. defined in linker script */
.word	_sbss
/* end address for the .bss section. defined in linker script */
.word	_ebss
/* start address for the .psram section. defined in linker script */
.word	_spsram
/* end address for the .psram section. defined in linker script */
.word	_epsram

/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called. 
 * @param  None
 * @retval : None
*/

  .section  .text.Reset_Handler
  .weak  Reset_Handler
  .type  Reset_Handler, %function
Reset_Handler:  
  ldr   sp, =_estack      /* set stack pointer */

  /* Call the clock system initialization function.*/
  bl  SystemInit

/* Copy the data segment initializers from flash to SRAM */  
  ldr r0, =_sdata
  ldr r1, =_edata
  ldr r2, =_sidata
  movs r3, #0
  b LoopCopyDataInit

CopyDataInit:
  ldr r4, [r2, r3]
  str r4, [r0, r3]
  adds r3, r3, #4

LoopCopyDataInit:
  adds r4, r0, r3
  cmp r4, r1
  bcc CopyDataInit

/* Zero fill the bss segment. */
  ldr r2, =_sbss
  ldr r4, =_ebss
  movs r3, #0
  b LoopFillZerobss

FillZerobss:
  str  r3, [r2]
  adds r2, r2, #4

LoopFillZerobss:
  cmp r2, r4
  bcc FillZerobss

/* Zero fill the psram segment. */
  ldr r2, =_spsram
  ldr r4, =_epsram
  movs r3, #0
  b LoopFillZeroPsram

FillZeroPsram:
  str  r3, [r2]
  adds r2, r2, #4

LoopFillZeroPsram:
  cmp r2, r4
  bcc FillZeroPsram

/* Call static constructors */
  bl __libc_init_array
/* Call the application's entry point.*/
  bl  main

.size	Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * @param  None
 * @retval : None
*/
    .section	.text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
	b	Infinite_Loop
	.size	Default_Handler, .-Default_Handler
/******************************************************************************
*
* The minimal vector table for a Cortex-M33.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
 	.section	.isr_vector,"a",%progbits
	.type	g_pfnVectors, %object
	.size	g_pfnVectors, .-g_pfnVectors


g_pfnVectors:
	.word	_estack
	.word	Reset_Handler
	.word	NMI_Handler
	.word	HardFault_Handler
	.word	MemManage_Handler
	.word	BusFault_Handler
	.word	UsageFault_Handler
	.word	0
	.word	0
	.word	0
	.word	0
	.word	SVC_Handler
	.word	DebugMon_Handler
	.word	0
	.word	PendSV_Handler
	.word	SysTick_Handler

    /* External Interrupts */
	.word	WDT_IRQHandler
	.word	LVD_IRQHandler
	.word	RTC_IRQHandler
	.word	RSV3_IRQHandler
	.word	RSV4_IRQHandler
	.word	RSV5_IRQHandler
	.word	CLKRDY_IRQHandler
	.word	EXTI0_IRQHandler
	.word	EXTI1_IRQHandler
	.word	EXTI2_IRQHandler
	.word	EXTI3_IRQHandler
	.word	EXTI4_IRQHandler
	.word	RSV12_IRQHandler
	.word	RSV13_IRQHandler
	.word	ADC12_IRQHandler
	.word	ADC3_IRQHandler
    .word	DAC1_IRQHandler
	.word	COMP1_IRQHandler
	.word	USBOTG1_IRQHandler
	.word	FDCAN1_IRQHandler
	.word	FDCAN2_IRQHandler
	.word	EXTI9_5_IRQHandler
	.word	TIM1_BRK_UP_TRG_COM_IRQHandler
	.word	TIM1_CC_IRQHandler
	.word	TIM2_IRQHandler
	.word	TIM3_IRQHandler
	.word	TIM6_IRQHandler
	.word	TIM7_IRQHandler
	.word	TIM8_BRK_UP_TRG_COM_IRQHandler
	.word	TIM8_CC_IRQHandler
	.word	TIM15_IRQHandler
	.word	TIM16_IRQHandler
	.word	TIM17_IRQHandler
	.word	I2C1_IRQHandler
	.word	I2C2_IRQHandler
	.word	SPI1_IRQHandler
	.word	SPI2_IRQHandler
	.word	SPI3_IRQHandler
	.word	I2S1_IRQHandler
	.word	I2S2_IRQHandler
	.word	USART1_IRQHandler
	.word	USART2_IRQHandler
	.word	USART3_IRQHandler
	.word	USART4_IRQHandler
	.word	EXTI15_10_IRQHandler
	.word	USBOTG1_WKUP_IRQHandler
	.word	LPUART1_IRQHandler
	.word	LPTIM1_IRQHandler
	.word	USBOTG2_WKUP_IRQHandler
	.word	AES_IRQHandler
	.word	FPU_IRQHandler
	.word	USBOTG2_IRQHandler
	.word	DCMI_IRQHandler
	.word	TIM4_IRQHandler
	.word	RSV54_IRQHandler
	.word	IWDT_WKUP_IRQHandler
	.word	LTDC_IRQHandler
	.word	LTDC_ERR_IRQHandler
	.word	DMA2D_IRQHandler
	.word	LPTIM2_IRQHandler
	.word	LPTIM3_IRQHandler
	.word	LPTIM4_IRQHandler
	.word	LPTIM5_IRQHandler
	.word	LPTIM6_IRQHandler
	.word	AES_SPI1_IRQHandler
	.word	I2S3_IRQHandler
	.word	SPI4_IRQHandler
	.word	SPI5_IRQHandler
	.word	SPI6_IRQHandler
	.word	I2C3_IRQHandler
	.word	I2C4_IRQHandler
	.word	FDCAN3_IRQHandler
    .word	RSV72_IRQHandler
	.word	ETH_IRQHandler
	.word	ETH_WKUP_IRQHandler
	.word	SDMMC_IRQHandler
	.word	USART5_IRQHandler
	.word	USART6_IRQHandler
	.word	USART7_IRQHandler
	.word	USART8_IRQHandler
	.word	USART9_IRQHandler
	.word	USART10_IRQHandler
	.word	DAC2_IRQHandler
	.word	TIM5_IRQHandler
	.word	TIM9_IRQHandler
	.word	TIM10_IRQHandler
	.word	TIM11_IRQHandler
	.word	TIM12_IRQHandler
	.word	TIM13_IRQHandler
	.word	TIM14_IRQHandler
	.word	TIM18_IRQHandler
	.word	TIM19_IRQHandler
	.word	TIM20_BRK_UP_TRG_COM_IRQHandler
	.word	TIM20_CC_IRQHandler
	.word	TIM21_IRQHandler
	.word	TIM22_IRQHandler
	.word	TIM23_IRQHandler
	.word	TIM24_IRQHandler
	.word	TIM25_IRQHandler
	.word	TIM26_IRQHandler
	.word	SPI7_IRQHandler
	.word	SPI8_IRQHandler
	.word	OSPI1_IRQHandler
	.word	OSPI2_IRQHandler
	.word	AES_SPI2_IRQHandler
	.word	TKEY_IRQHandler
	.word	LPT_IRQHandler
	.word	RSV107_IRQHandler
	.word	OTG1_HS_EP_OUT_IRQHandler
	.word	OTG1_HS_EP_IN_IRQHandler
	.word	OTG2_HS_EP_OUT_IRQHandler
	.word	OTG2_HS_EP_IN_IRQHandler
	.word	NDL_IRQHandler
	.word	THM_IRQHandler
 	.word	STM1_PWM_IRQHandler
	.word	STM2_PWM_IRQHandler
	.word	DCM1_PWM_IRQHandler
	.word	DCM2_PWM_IRQHandler
	.word	DCM3_PWM_IRQHandler
	.word	DCM4_PWM_IRQHandler
	.word	STM3_PWM_IRQHandler
	.word	STM4_PWM_IRQHandler
	.word	STM5_PWM_IRQHandler
	.word	STM6_PWM_IRQHandler
	.word	DCM5_PWM_IRQHandler
    .word	DCM6_PWM_IRQHandler
	.word	NAND_IRQHandler
	.word	BCH_IRQHandler
	.word	SDRAM_IRQHandler
	.word	DMA1_CH0_IRQHandler
	.word	DMA1_CH1_IRQHandler
    .word	DMA1_CH2_IRQHandler
	.word	DMA1_CH3_IRQHandler
	.word	DMA1_CH4_IRQHandler
	.word	DMA1_CH5_IRQHandler
    .word	DMA1_CH6_IRQHandler
	.word	DMA1_CH7_IRQHandler
	.word	DMA2_CH0_IRQHandler
	.word	DMA2_CH1_IRQHandler
	.word	DMA2_CH2_IRQHandler
    .word	DMA2_CH3_IRQHandler
	.word	DMA2_CH4_IRQHandler
	.word	DMA2_CH5_IRQHandler
	.word	DMA2_CH6_IRQHandler
	.word	DMA2_CH7_IRQHandler
    .word	SRAM1_SEC_IRQHandler
    .word	SRAM1_DED_IRQHandler
	.word	RSV147_IRQHandler
	.word	RSV148_IRQHandler
	.word	BKPSRAM_SEC_IRQHandler
	.word	BKPSRAM_CH7_IRQHandler

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/

	.weak	NMI_Handler
	.thumb_set NMI_Handler,Default_Handler

	.weak	HardFault_Handler
	.thumb_set HardFault_Handler,Default_Handler

	.weak	MemManage_Handler
	.thumb_set MemManage_Handler,Default_Handler

	.weak	BusFault_Handler
	.thumb_set BusFault_Handler,Default_Handler

	.weak	UsageFault_Handler
	.thumb_set UsageFault_Handler,Default_Handler

	.weak	SVC_Handler
	.thumb_set SVC_Handler,Default_Handler

	.weak	DebugMon_Handler
	.thumb_set DebugMon_Handler,Default_Handler

	.weak	PendSV_Handler
	.thumb_set PendSV_Handler,Default_Handler

	.weak	SysTick_Handler
	.thumb_set SysTick_Handler,Default_Handler

	.weak	WDT_IRQHandler
	.thumb_set WDT_IRQHandler,Default_Handler

	.weak	LVD_IRQHandler
	.thumb_set LVD_IRQHandler,Default_Handler

	.weak	RTC_IRQHandler
	.thumb_set RTC_IRQHandler,Default_Handler

	.weak	RSV3_IRQHandler
	.thumb_set RSV3_IRQHandler,Default_Handler

	.weak	RSV4_IRQHandler
	.thumb_set RSV4_IRQHandler,Default_Handler

	.weak	RSV5_IRQHandler
	.thumb_set RSV5_IRQHandler,Default_Handler

	.weak	CLKRDY_IRQHandler
	.thumb_set CLKRDY_IRQHandler,Default_Handler

	.weak	EXTI0_IRQHandler
	.thumb_set EXTI0_IRQHandler,Default_Handler

	.weak	EXTI1_IRQHandler
	.thumb_set EXTI1_IRQHandler,Default_Handler

	.weak	EXTI2_IRQHandler
	.thumb_set EXTI2_IRQHandler,Default_Handler

	.weak	EXTI3_IRQHandler
	.thumb_set EXTI3_IRQHandler,Default_Handler

	.weak	EXTI4_IRQHandler
	.thumb_set EXTI4_IRQHandler,Default_Handler

	.weak	RSV12_IRQHandler
	.thumb_set RSV12_IRQHandler,Default_Handler

	.weak	RSV13_IRQHandler
	.thumb_set RSV13_IRQHandler,Default_Handler

	.weak	ADC12_IRQHandler
	.thumb_set ADC12_IRQHandler,Default_Handler

	.weak	ADC3_IRQHandler
	.thumb_set ADC3_IRQHandler,Default_Handler

	.weak	DAC1_IRQHandler
	.thumb_set DAC1_IRQHandler,Default_Handler

	.weak	COMP1_IRQHandler
	.thumb_set COMP1_IRQHandler,Default_Handler

	.weak	USBOTG1_IRQHandler
	.thumb_set USBOTG1_IRQHandler,Default_Handler

	.weak	FDCAN1_IRQHandler
	.thumb_set FDCAN1_IRQHandler,Default_Handler

	.weak	FDCAN2_IRQHandler
	.thumb_set FDCAN2_IRQHandler,Default_Handler

	.weak	EXTI9_5_IRQHandler
	.thumb_set EXTI9_5_IRQHandler,Default_Handler

	.weak	TIM1_BRK_UP_TRG_COM_IRQHandler
	.thumb_set TIM1_BRK_UP_TRG_COM_IRQHandler,Default_Handler

	.weak	TIM1_CC_IRQHandler
	.thumb_set TIM1_CC_IRQHandler,Default_Handler

	.weak	TIM2_IRQHandler
	.thumb_set TIM2_IRQHandler,Default_Handler

	.weak	TIM3_IRQHandler
	.thumb_set TIM3_IRQHandler,Default_Handler

	.weak	TIM6_IRQHandler
	.thumb_set TIM6_IRQHandler,Default_Handler

	.weak	TIM7_IRQHandler
	.thumb_set TIM7_IRQHandler,Default_Handler

	.weak	TIM8_BRK_UP_TRG_COM_IRQHandler
	.thumb_set TIM8_BRK_UP_TRG_COM_IRQHandler,Default_Handler

	.weak	TIM8_CC_IRQHandler
	.thumb_set TIM8_CC_IRQHandler,Default_Handler

	.weak	TIM15_IRQHandler
	.thumb_set TIM15_IRQHandler,Default_Handler

	.weak	TIM16_IRQHandler
	.thumb_set TIM16_IRQHandler,Default_Handler

	.weak	TIM17_IRQHandler
	.thumb_set TIM17_IRQHandler,Default_Handler

	.weak	I2C1_IRQHandler
	.thumb_set I2C1_IRQHandler,Default_Handler

	.weak	I2C2_IRQHandler
	.thumb_set I2C2_IRQHandler,Default_Handler

	.weak	SPI1_IRQHandler
	.thumb_set SPI1_IRQHandler,Default_Handler

	.weak	SPI2_IRQHandler
	.thumb_set SPI2_IRQHandler,Default_Handler

	.weak	SPI3_IRQHandler
	.thumb_set SPI3_IRQHandler,Default_Handler

	.weak	I2S1_IRQHandler
	.thumb_set I2S1_IRQHandler,Default_Handler

	.weak	I2S2_IRQHandler
	.thumb_set I2S2_IRQHandler,Default_Handler

	.weak	USART1_IRQHandler
	.thumb_set USART1_IRQHandler,Default_Handler

	.weak	USART2_IRQHandler
	.thumb_set USART2_IRQHandler,Default_Handler

	.weak	USART3_IRQHandler
	.thumb_set USART3_IRQHandler,Default_Handler

	.weak	USART4_IRQHandler
	.thumb_set USART4_IRQHandler,Default_Handler

	.weak	EXTI15_10_IRQHandler
	.thumb_set EXTI15_10_IRQHandler,Default_Handler

	.weak	USBOTG1_WKUP_IRQHandler
	.thumb_set USBOTG1_WKUP_IRQHandler,Default_Handler

	.weak	LPUART1_IRQHandler
	.thumb_set LPUART1_IRQHandler,Default_Handler

	.weak	LPTIM1_IRQHandler
	.thumb_set LPTIM1_IRQHandler,Default_Handler

	.weak	USBOTG2_WKUP_IRQHandler
	.thumb_set USBOTG2_WKUP_IRQHandler,Default_Handler

	.weak	AES_IRQHandler
	.thumb_set AES_IRQHandler,Default_Handler

	.weak	FPU_IRQHandler
	.thumb_set FPU_IRQHandler,Default_Handler

	.weak	USBOTG2_IRQHandler
	.thumb_set USBOTG2_IRQHandler,Default_Handler

	.weak	DCMI_IRQHandler
	.thumb_set DCMI_IRQHandler,Default_Handler

	.weak	TIM4_IRQHandler
	.thumb_set TIM4_IRQHandler,Default_Handler

	.weak	RSV54_IRQHandler
	.thumb_set RSV54_IRQHandler,Default_Handler

	.weak	IWDT_WKUP_IRQHandler
	.thumb_set IWDT_WKUP_IRQHandler,Default_Handler

	.weak	LTDC_IRQHandler
	.thumb_set LTDC_IRQHandler,Default_Handler

	.weak	LTDC_ERR_IRQHandler
	.thumb_set LTDC_ERR_IRQHandler,Default_Handler

	.weak	DMA2D_IRQHandler
	.thumb_set DMA2D_IRQHandler,Default_Handler

	.weak	LPTIM2_IRQHandler
	.thumb_set LPTIM2_IRQHandler,Default_Handler

	.weak	LPTIM3_IRQHandler
	.thumb_set LPTIM3_IRQHandler,Default_Handler

	.weak	LPTIM4_IRQHandler
	.thumb_set LPTIM4_IRQHandler,Default_Handler

	.weak	LPTIM5_IRQHandler
	.thumb_set LPTIM5_IRQHandler,Default_Handler

	.weak	LPTIM6_IRQHandler
	.thumb_set LPTIM6_IRQHandler,Default_Handler

	.weak	AES_SPI1_IRQHandler
	.thumb_set AES_SPI1_IRQHandler,Default_Handler

	.weak	I2S3_IRQHandler
	.thumb_set I2S3_IRQHandler,Default_Handler

	.weak	SPI4_IRQHandler
	.thumb_set SPI4_IRQHandler,Default_Handler

	.weak	SPI5_IRQHandler
	.thumb_set SPI5_IRQHandler,Default_Handler

	.weak	SPI6_IRQHandler
	.thumb_set SPI6_IRQHandler,Default_Handler

	.weak	I2C3_IRQHandler
	.thumb_set I2C3_IRQHandler,Default_Handler

	.weak	I2C4_IRQHandler
	.thumb_set I2C4_IRQHandler,Default_Handler

	.weak	FDCAN3_IRQHandler
	.thumb_set FDCAN3_IRQHandler,Default_Handler

	.weak	RSV72_IRQHandler
	.thumb_set RSV72_IRQHandler,Default_Handler

	.weak	ETH_IRQHandler
	.thumb_set ETH_IRQHandler,Default_Handler

	.weak	ETH_WKUP_IRQHandler
	.thumb_set ETH_WKUP_IRQHandler,Default_Handler

	.weak	SDMMC_IRQHandler
	.thumb_set SDMMC_IRQHandler,Default_Handler

	.weak	USART5_IRQHandler
	.thumb_set USART5_IRQHandler,Default_Handler

	.weak	USART6_IRQHandler
	.thumb_set USART6_IRQHandler,Default_Handler

	.weak	USART7_IRQHandler
	.thumb_set USART7_IRQHandler,Default_Handler

	.weak	USART8_IRQHandler
	.thumb_set USART8_IRQHandler,Default_Handler

	.weak	USART9_IRQHandler
	.thumb_set USART9_IRQHandler,Default_Handler

	.weak	USART10_IRQHandler
	.thumb_set USART10_IRQHandler,Default_Handler

	.weak	DAC2_IRQHandler
	.thumb_set DAC2_IRQHandler,Default_Handler

	.weak	TIM5_IRQHandler
	.thumb_set TIM5_IRQHandler,Default_Handler

	.weak	TIM9_IRQHandler
	.thumb_set TIM9_IRQHandler,Default_Handler

	.weak	TIM10_IRQHandler
	.thumb_set TIM10_IRQHandler,Default_Handler

	.weak	TIM11_IRQHandler
	.thumb_set TIM11_IRQHandler,Default_Handler

	.weak	TIM12_IRQHandler
	.thumb_set TIM12_IRQHandler,Default_Handler

	.weak	TIM13_IRQHandler
	.thumb_set TIM13_IRQHandler,Default_Handler

	.weak	TIM14_IRQHandler
	.thumb_set TIM14_IRQHandler,Default_Handler

	.weak	TIM18_IRQHandler
	.thumb_set TIM18_IRQHandler,Default_Handler

	.weak	TIM19_IRQHandler
	.thumb_set TIM19_IRQHandler,Default_Handler

	.weak	TIM20_BRK_UP_TRG_COM_IRQHandler
	.thumb_set TIM20_BRK_UP_TRG_COM_IRQHandler,Default_Handler

	.weak	TIM20_CC_IRQHandler
	.thumb_set TIM20_CC_IRQHandler,Default_Handler

	.weak	TIM21_IRQHandler
	.thumb_set TIM21_IRQHandler,Default_Handler

	.weak	TIM22_IRQHandler
	.thumb_set TIM22_IRQHandler,Default_Handler

	.weak	TIM23_IRQHandler
	.thumb_set TIM23_IRQHandler,Default_Handler

	.weak	TIM24_IRQHandler
	.thumb_set TIM24_IRQHandler,Default_Handler

	.weak	TIM25_IRQHandler
	.thumb_set TIM25_IRQHandler,Default_Handler

	.weak	TIM26_IRQHandler
	.thumb_set TIM26_IRQHandler,Default_Handler

	.weak	SPI7_IRQHandler
	.thumb_set SPI7_IRQHandler,Default_Handler

	.weak	SPI8_IRQHandler
	.thumb_set SPI8_IRQHandler,Default_Handler

	.weak	OSPI1_IRQHandler
	.thumb_set OSPI1_IRQHandler,Default_Handler

	.weak	OSPI2_IRQHandler
	.thumb_set OSPI2_IRQHandler,Default_Handler

	.weak	AES_SPI2_IRQHandler
	.thumb_set AES_SPI2_IRQHandler,Default_Handler

	.weak	TKEY_IRQHandler
	.thumb_set TKEY_IRQHandler,Default_Handler

	.weak	LPT_IRQHandler
	.thumb_set LPT_IRQHandler,Default_Handler

	.weak	RSV107_IRQHandler
	.thumb_set RSV107_IRQHandler,Default_Handler

	.weak	OTG1_HS_EP_OUT_IRQHandler
	.thumb_set OTG1_HS_EP_OUT_IRQHandler,Default_Handler

	.weak	OTG1_HS_EP_IN_IRQHandler
	.thumb_set OTG1_HS_EP_IN_IRQHandler,Default_Handler

	.weak	OTG2_HS_EP_OUT_IRQHandler
	.thumb_set OTG2_HS_EP_OUT_IRQHandler,Default_Handler

	.weak	OTG2_HS_EP_IN_IRQHandler
	.thumb_set OTG2_HS_EP_IN_IRQHandler,Default_Handler

	.weak	NDL_IRQHandler
	.thumb_set NDL_IRQHandler,Default_Handler

	.weak	THM_IRQHandler
	.thumb_set THM_IRQHandler,Default_Handler

	.weak	STM1_PWM_IRQHandler
	.thumb_set STM1_PWM_IRQHandler,Default_Handler

	.weak	STM2_PWM_IRQHandler
	.thumb_set STM2_PWM_IRQHandler,Default_Handler

	.weak	DCM1_PWM_IRQHandler
	.thumb_set DCM1_PWM_IRQHandler,Default_Handler

	.weak	DCM2_PWM_IRQHandler
	.thumb_set DCM2_PWM_IRQHandler,Default_Handler

	.weak	DCM3_PWM_IRQHandler
	.thumb_set DCM3_PWM_IRQHandler,Default_Handler

	.weak	DCM4_PWM_IRQHandler
	.thumb_set DCM4_PWM_IRQHandler,Default_Handler

    .weak	STM3_PWM_IRQHandler
	.thumb_set STM3_PWM_IRQHandler,Default_Handler

    .weak	STM4_PWM_IRQHandler
	.thumb_set STM4_PWM_IRQHandler,Default_Handler

	.weak	STM5_PWM_IRQHandler
	.thumb_set STM5_PWM_IRQHandler,Default_Handler

	.weak	STM6_PWM_IRQHandler
	.thumb_set STM6_PWM_IRQHandler,Default_Handler

    .weak	DCM5_PWM_IRQHandler
	.thumb_set DCM5_PWM_IRQHandler,Default_Handler

	.weak	DCM6_PWM_IRQHandler
	.thumb_set DCM6_PWM_IRQHandler,Default_Handler

	.weak	NAND_IRQHandler
	.thumb_set NAND_IRQHandler,Default_Handler

	.weak	BCH_IRQHandler
	.thumb_set BCH_IRQHandler,Default_Handler

	.weak	SDRAM_IRQHandler
	.thumb_set SDRAM_IRQHandler,Default_Handler

    .weak	DMA1_CH0_IRQHandler
	.thumb_set DMA1_CH0_IRQHandler,Default_Handler

    .weak	DMA1_CH1_IRQHandler
	.thumb_set DMA1_CH1_IRQHandler,Default_Handler

	.weak	DMA1_CH2_IRQHandler
	.thumb_set DMA1_CH2_IRQHandler,Default_Handler

	.weak	DMA1_CH3_IRQHandler
	.thumb_set DMA1_CH3_IRQHandler,Default_Handler

	.weak	DMA1_CH4_IRQHandler
	.thumb_set DMA1_CH4_IRQHandler,Default_Handler

	.weak	DMA1_CH5_IRQHandler
	.thumb_set DMA1_CH5_IRQHandler,Default_Handler

    .weak	DMA1_CH6_IRQHandler
	.thumb_set DMA1_CH6_IRQHandler,Default_Handler

    .weak	DMA1_CH7_IRQHandler
	.thumb_set DMA1_CH7_IRQHandler,Default_Handler

	.weak	DMA2_CH0_IRQHandler
	.thumb_set DMA2_CH0_IRQHandler,Default_Handler

	.weak	DMA2_CH1_IRQHandler
	.thumb_set DMA2_CH1_IRQHandler,Default_Handler

	.weak	DMA2_CH2_IRQHandler
	.thumb_set DMA2_CH2_IRQHandler,Default_Handler

	.weak	DMA2_CH3_IRQHandler
	.thumb_set DMA2_CH3_IRQHandler,Default_Handler

    .weak	DMA2_CH4_IRQHandler
	.thumb_set DMA2_CH4_IRQHandler,Default_Handler

	.weak	DMA2_CH5_IRQHandler
	.thumb_set DMA2_CH5_IRQHandler,Default_Handler

	.weak	DMA2_CH6_IRQHandler
	.thumb_set DMA2_CH6_IRQHandler,Default_Handler

	.weak	DMA2_CH7_IRQHandler
	.thumb_set DMA2_CH7_IRQHandler,Default_Handler

    .weak	SRAM1_SEC_IRQHandler
	.thumb_set SRAM1_SEC_IRQHandler,Default_Handler

	.weak	SRAM1_DED_IRQHandler
	.thumb_set SRAM1_DED_IRQHandler,Default_Handler

	.weak	RSV147_IRQHandler
	.thumb_set RSV147_IRQHandler,Default_Handler

	.weak	RSV148_IRQHandler
	.thumb_set RSV148_IRQHandler,Default_Handler

    .weak	BKPSRAM_SEC_IRQHandler
	.thumb_set BKPSRAM_SEC_IRQHandler,Default_Handler

	.weak	BKPSRAM_CH7_IRQHandler
	.thumb_set BKPSRAM_CH7_IRQHandler,Default_Handler