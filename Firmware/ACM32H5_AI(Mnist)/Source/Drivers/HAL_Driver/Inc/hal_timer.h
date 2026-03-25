/***********************************************************************
 * Filename    : hal_timer.h
 * Description : timer driver header file
 * Author(s)   : Eric  
 * version     : V1.0
 * Modify date : 2016-03-24
 ***********************************************************************/
#ifndef __HAL_TIMER_H__
#define __HAL_TIMER_H__  

#include "hal.h" 


/****************** TIM Instances : supporting the break function *************/
#define IS_TIM_BREAK_INSTANCE(INSTANCE)    ( ((INSTANCE) == TIM1)    || \
                                             ((INSTANCE) == TIM8)    || \
                                              ((INSTANCE) == TIM15)  ||   \
                                             ((INSTANCE) == TIM16)    || \
                                              ((INSTANCE) == TIM17)   ||  \
                                              ((INSTANCE) == TIM18)  ||   \
                                              ((INSTANCE) == TIM19)  ||   \
                                              ((INSTANCE) == TIM20)  ||   \
                                              ((INSTANCE) == TIM25)     \
                                                                  )
                                                                  
#define IS_TIM_BREAKSOURCE_INSTANCE          ( ((INSTANCE) == TIM1)    || \
                                             ((INSTANCE) == TIM8)    || \
                                              ((INSTANCE) == TIM15)  ||   \
                                             ((INSTANCE) == TIM16)    || \
                                              ((INSTANCE) == TIM17)   ||  \
                                              ((INSTANCE) == TIM18)  ||   \
                                              ((INSTANCE) == TIM19)  ||   \
                                              ((INSTANCE) == TIM20)  ||   \
                                              ((INSTANCE) == TIM25)     \
                                                                  )                                                                  

/************** TIM Instances : supporting Break source selection *************/
 


/************* TIM Instances : at least 1 capture/compare channel *************/
#define IS_TIM_CC1_INSTANCE(INSTANCE)   ( ((INSTANCE) != TIM6)  && \
                                            ((INSTANCE) != TIM7)  && \
                                            ((INSTANCE) != TIM21)  && \
                                            ((INSTANCE) != TIM22) )   

/************ TIM Instances : at least 2 capture/compare channels *************/
#define IS_TIM_CC2_INSTANCE(INSTANCE)   (((INSTANCE) == TIM1)   || \
                                         ((INSTANCE) == TIM2)   || \
										 ((INSTANCE) == TIM3)   || \
										 ((INSTANCE) == TIM4)   || \
                                         ((INSTANCE) == TIM5)   || \
                                         ((INSTANCE) == TIM8)   || \
                                         ((INSTANCE) == TIM9)   || \
                                         ((INSTANCE) == TIM12)   || \
                                         ((INSTANCE) == TIM15)   || \
                                         ((INSTANCE) == TIM20)   || \
                                         ((INSTANCE) == TIM23)   || \
                                         ((INSTANCE) == TIM24)   || \
                                         ((INSTANCE) == TIM25) )  
                                         

/************ TIM Instances : at least 3 capture/compare channels *************/
#define IS_TIM_CC3_INSTANCE(INSTANCE)   (((INSTANCE) == TIM1)   || \
                                         ((INSTANCE) == TIM2)   || \
									     ((INSTANCE) == TIM3)   || \
                                         ((INSTANCE) == TIM4)   || \
                                         ((INSTANCE) == TIM5)   || \
                                         ((INSTANCE) == TIM8)   || \
                                         ((INSTANCE) == TIM20)   || \
                                         ((INSTANCE) == TIM23)   || \
                                         ((INSTANCE) == TIM24) ) 

/************ TIM Instances : at least 4 capture/compare channels *************/
#define IS_TIM_CC4_INSTANCE(INSTANCE)   (((INSTANCE) == TIM1)   || \
                                         ((INSTANCE) == TIM2)   || \
									     ((INSTANCE) == TIM3)   || \
                                         ((INSTANCE) == TIM4)   || \
                                         ((INSTANCE) == TIM5)   || \
                                         ((INSTANCE) == TIM8)   || \
                                         ((INSTANCE) == TIM20)   || \
                                         ((INSTANCE) == TIM23)   || \
                                         ((INSTANCE) == TIM24) )   



/*********** TIM Instances : Slave mode available (TIMx_SMCR available )*******/
#define IS_TIM_SLAVE_INSTANCE(INSTANCE)    ( ((INSTANCE) != TIM6)  && \
                                            ((INSTANCE) != TIM7)  && \
                                            ((INSTANCE) != TIM21)  && \
                                            ((INSTANCE) != TIM22) )    
                                            
/****************** TIM Instances : supporting complementary output(s) ********/
#define IS_TIM_CCXN_INSTANCE(INSTANCE, CHANNEL) \
   ((( (INSTANCE) == TIM1) &&                    \
     (((CHANNEL) == TIM_CHANNEL_1) ||           \
      ((CHANNEL) == TIM_CHANNEL_2) ||           \
      ((CHANNEL) == TIM_CHANNEL_3) ||           \
      ((CHANNEL) == TIM_CHANNEL_4)) )            \
    ||                                          \
    (((INSTANCE) == TIM8) &&                   \
     (((CHANNEL) == TIM_CHANNEL_1) ||           \
      ((CHANNEL) == TIM_CHANNEL_2) ||           \
      ((CHANNEL) == TIM_CHANNEL_3) ||           \
      ((CHANNEL) == TIM_CHANNEL_4)) )            \
          ||                                          \
    (((INSTANCE) == TIM20) &&                   \
     (((CHANNEL) == TIM_CHANNEL_1) ||           \
      ((CHANNEL) == TIM_CHANNEL_2) ||           \
      ((CHANNEL) == TIM_CHANNEL_3) ||           \
      ((CHANNEL) == TIM_CHANNEL_4)) )            \
    ||                                          \
    (((INSTANCE) == TIM15) &&                   \
     ((CHANNEL) == TIM_CHANNEL_1))              \
    ||                                          \
    (((INSTANCE) == TIM16) &&                   \
     ((CHANNEL) == TIM_CHANNEL_1))              \
    ||                                          \
    (((INSTANCE) == TIM17) &&                   \
     ((CHANNEL) == TIM_CHANNEL_1))              \
    ||                                          \
    (((INSTANCE) == TIM18) &&                   \
     ((CHANNEL) == TIM_CHANNEL_1))              \
    ||                                     \
    (((INSTANCE) == TIM19) &&                   \
     ((CHANNEL) == TIM_CHANNEL_1))              \
    ||                                          \
    (((INSTANCE) == TIM25) &&                   \
     ((CHANNEL) == TIM_CHANNEL_1)  ) )



/****** TIM Instances : supporting external clock mode 1 for ETRF input *******/
#define IS_TIM_CLOCKSOURCE_ETRMODE1_INSTANCE(INSTANCE) (((INSTANCE) == TIM1) || \
                                                        ((INSTANCE) == TIM8) || \
                                                        ((INSTANCE) == TIM2) || \
																												((INSTANCE) == TIM3) || \
																												((INSTANCE) == TIM4) )

/****** TIM Instances : supporting external clock mode 2 for ETRF input *******/
#define IS_TIM_CLOCKSOURCE_ETRMODE2_INSTANCE(INSTANCE) (((INSTANCE) == TIM1) || \
                                                        ((INSTANCE) == TIM8) || \
                                                        ((INSTANCE) == TIM2) || \
																												((INSTANCE) == TIM3) || \
																												((INSTANCE) == TIM4) ) 

/****************** TIM Instances : supporting combined 3-phase PWM mode ******/
#define IS_TIM_COMBINED3PHASEPWM_INSTANCE(INSTANCE)    (((INSTANCE) == TIM1) || \
                                                        ((INSTANCE) == TIM8) )

/****************** TIM Instances : supporting commutation event generation ***/
#define IS_TIM_COMMUTATION_EVENT_INSTANCE(INSTANCE) (((INSTANCE) == TIM1)   || \
                                                     ((INSTANCE) == TIM8)   || \
                                                     ((INSTANCE) == TIM15)  || \
                                                     ((INSTANCE) == TIM16)  || \
                                                     ((INSTANCE) == TIM17))

/****************** TIM Instances : supporting encoder interface **************/
#define IS_TIM_ENCODER_INTERFACE_INSTANCE(INSTANCE)  (((INSTANCE) == TIM1)  || \
                                                      ((INSTANCE) == TIM8)  || \
                                                      ((INSTANCE) == TIM2)  || \
																											((INSTANCE) == TIM3) || \
																											((INSTANCE) == TIM4) ) 

/****************** TIM Instances : supporting Hall sensor interface **********/
#define IS_TIM_HALL_SENSOR_INTERFACE_INSTANCE(INSTANCE) (((INSTANCE) == TIM1)   || \
                                                         ((INSTANCE) == TIM8)   || \
                                                         ((INSTANCE) == TIM2)   || \
																											((INSTANCE) == TIM3) || \
																											((INSTANCE) == TIM4) )  

/****************** TIM Instances : supporting repetition counter *************/
#define IS_TIM_REPETITION_COUNTER_INSTANCE(INSTANCE)  (((INSTANCE) == TIM1)  || \
                                                       ((INSTANCE) == TIM8) || \
                                                       ((INSTANCE) == TIM9) || \
                                                       ((INSTANCE) == TIM10) || \
                                                       ((INSTANCE) == TIM11) || \
                                                       ((INSTANCE) == TIM12) || \
                                                       ((INSTANCE) == TIM13) || \
                                                       ((INSTANCE) == TIM14) || \
                                                       ((INSTANCE) == TIM15) || \
                                                       ((INSTANCE) == TIM16) || \
                                                       ((INSTANCE) == TIM17) || \
                                                       ((INSTANCE) == TIM18) || \
                                                       ((INSTANCE) == TIM19) || \
                                                       ((INSTANCE) == TIM20) || \
                                                       ((INSTANCE) == TIM25) ) 
                                                       
/****************** TIM Instances : supporting repetition counter *************/
#define IS_TIM_32_BITS_INSTANCE(INSTANCE)  (((INSTANCE) == TIM2)  || \
                                                       ((INSTANCE) == TIM5) || \
                                                       ((INSTANCE) == TIM23) || \
                                                       ((INSTANCE) == TIM24) )  
                                                       
                                                       
/****************** TIM Instances : supporting ADC triggering through TRGO2 ***/
#define IS_TIM_TRGO2_INSTANCE(INSTANCE)    (((INSTANCE) == TIM1)    || \
                                            ((INSTANCE) == TIM8))


#define HAL_TIM_ENABLE_IT(__HANDLE__, __INTERRUPT__)    ((__HANDLE__)->Instance->DIER |= (__INTERRUPT__))   
#define HAL_TIM_DISABLE_IT(__HANDLE__, __INTERRUPT__)   ((__HANDLE__)->Instance->DIER &= ~(__INTERRUPT__)) 

#define HAL_TIM_ENABLE_IT_EX(__INSTANCE__, __INTERRUPT__)    ((__INSTANCE__)->DIER |= (__INTERRUPT__))   
#define HAL_TIM_DISABLE_IT_EX(__INSTANCE__, __INTERRUPT__)   ((__INSTANCE__)->DIER &= ~(__INTERRUPT__)) 

#define HAL_TIM_ENABLE_DMA(__HANDLE__, __DMA_REQ__)    ((__HANDLE__)->Instance->DIER |= (__DMA_REQ__))   
#define HAL_TIM_DISABLE_DMA(__HANDLE__, __DMA_REQ__)   ((__HANDLE__)->Instance->DIER &= ~(__DMA_REQ__))  

#define __HAL_TIM_GET_FLAG(__HANDLE__, __FLAG__)          (((__HANDLE__)->Instance->SR &(__FLAG__)) == (__FLAG__))  
#define __HAL_TIM_CLEAR_FLAG(__HANDLE__, __FLAG__)        ((__HANDLE__)->Instance->SR = ~(__FLAG__))  

#define __HAL_TIM_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((((__HANDLE__)->Instance->DIER & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)  

#define TIM_CR2_CCPC_Pos          (0U)
#define TIM_CR2_CCPC_Msk          (0x1UL << TIM_CR2_CCPC_Pos)                  
#define TIM_CR2_CCPC              TIM_CR2_CCPC_Msk                             
#define TIM_CR2_CCUS_Pos          (2U)
#define TIM_CR2_CCUS_Msk          (0x1UL << TIM_CR2_CCUS_Pos)                
#define TIM_CR2_CCUS              TIM_CR2_CCUS_Msk                             
#define TIM_CR2_CCDS_Pos          (3U)
#define TIM_CR2_CCDS_Msk          (0x1UL << TIM_CR2_CCDS_Pos)                
#define TIM_CR2_CCDS              TIM_CR2_CCDS_Msk                         

#define TIM_COMMUTATION_TRGI              TIM_CR2_CCUS                    
#define TIM_COMMUTATION_SOFTWARE          0x00000000U  

#define TIM_IT_UPDATE                      BIT0                                    
#define TIM_IT_CC1                         BIT1                     
#define TIM_IT_CC2                         BIT2                      
#define TIM_IT_CC3                         BIT3                    
#define TIM_IT_CC4                         BIT4                      
#define TIM_IT_COM                         BIT5                   
#define TIM_IT_TRIGGER                     BIT6                           
#define TIM_IT_BREAK                       BIT7   

#define TIM_DMA_UPDATE                      BIT8                                      
#define TIM_DMA_CC1                         BIT9                    
#define TIM_DMA_CC2                         BIT10                      
#define TIM_DMA_CC3                         BIT11                   
#define TIM_DMA_CC4                         BIT12                     
#define TIM_DMA_COM                         BIT13                  
#define TIM_DMA_TRIGGER                     BIT14                          
#define TIM_DMA_BREAK                       BIT15     



#define TIM_EVENTSOURCE_UPDATE              BIT0     /*!< Reinitialize the counter and generates an update of the registers */
#define TIM_EVENTSOURCE_CC1                 BIT1     /*!< A capture/compare event is generated on channel 1 */
#define TIM_EVENTSOURCE_CC2                 BIT2     /*!< A capture/compare event is generated on channel 2 */
#define TIM_EVENTSOURCE_CC3                 BIT3     /*!< A capture/compare event is generated on channel 3 */
#define TIM_EVENTSOURCE_CC4                 BIT4     /*!< A capture/compare event is generated on channel 4 */
#define TIM_EVENTSOURCE_COM                 BIT5     /*!< A commutation event is generated */
#define TIM_EVENTSOURCE_TRIGGER             BIT6     /*!< A trigger event is generated */
#define TIM_EVENTSOURCE_BREAK               BIT7     /*!< A break event is generated */

#define TIM_ARR_PRELOAD_DISABLE   0  
#define TIM_ARR_PRELOAD_ENABLE    1    

#define TIM_COUNTERMODE_DIR_INDEX          4 
#define TIM_COUNTERMODE_UP                 (0 << TIM_COUNTERMODE_DIR_INDEX)                          
#define TIM_COUNTERMODE_DOWN               (1 << TIM_COUNTERMODE_DIR_INDEX)  

#define TIM_COUNTERMODE_CMS_INDEX          5     
#define TIM_COUNTERMODE_CENTERALIGNED1     (1 << TIM_COUNTERMODE_CMS_INDEX)                      
#define TIM_COUNTERMODE_CENTERALIGNED2     (2 << TIM_COUNTERMODE_CMS_INDEX)                        
#define TIM_COUNTERMODE_CENTERALIGNED3     (3 << TIM_COUNTERMODE_CMS_INDEX)                                       

#define TIM_CLKCK_DIV_INDEX                8   
#define TIM_CLOCKDIVISION_DIV1             0x00000000U                          /*!< Clock division: tDTS=tCK_INT   */
#define TIM_CLOCKDIVISION_DIV2             (1U << TIM_CLKCK_DIV_INDEX)          /*!< Clock division: tDTS=2*tCK_INT */
#define TIM_CLOCKDIVISION_DIV4             (2U << TIM_CLKCK_DIV_INDEX)          /*!< Clock division: tDTS=4*tCK_INT */     

/** @defgroup TIM_Master_Mode_Selection TIM Master Mode Selection
  * @{
  */
#define TIM_TRGO_RESET                      (0U << 4) 
#define TIM_TRGO_ENABLE                     (1U << 4)    
#define TIM_TRGO_UPDATE                     (2U << 4) 
#define TIM_TRGO_CMP_PULSE                  (3U << 4)  
#define TIM_TRGO_OC1REF                     (4U << 4) 
#define TIM_TRGO_OC2REF                     (5U << 4)    
#define TIM_TRGO_OC3REF                     (6U << 4)  
#define TIM_TRGO_OC4REF                     (7U << 4)     
/**
  * @}
  */

/** @defgroup TIM_Master_Mode_Selection_2 TIM Master Mode Selection 2 (TRGO2)
  * @{
  */
#define TIM_TRGO2_RESET                         (0U << 20) 
#define TIM_TRGO2_ENABLE                        (1U << 20)    
#define TIM_TRGO2_UPDATE                        (2U << 20) 
#define TIM_TRGO2_CMP_PULSE                     (3U << 20)  
#define TIM_TRGO2_OC1REF                        (4U << 20) 
#define TIM_TRGO2_OC2REF                        (5U << 20)    
#define TIM_TRGO2_OC3REF                        (6U << 20)  
#define TIM_TRGO2_OC4REF                        (7U << 20)     
#define TIM_TRGO2_OC5REF                        (8U << 20)     
#define TIM_TRGO2_OC6REF                        (9U << 20)     
#define TIM_TRGO2_OC4REF_RISINGFALLING          (10U << 20)     
#define TIM_TRGO2_OC6REF_RISINGFALLING          (11U << 20)     
#define TIM_TRGO2_OC4REF_RISING_OC6REF_RISING   (12U << 20)     
#define TIM_TRGO2_OC4REF_RISING_OC6REF_FALLING  (13U << 20)     
#define TIM_TRGO2_OC5REF_RISING_OC6REF_RISING   (14U << 20)     
#define TIM_TRGO2_OC5REF_RISING_OC6REF_FALLING  (15U << 20)     
/**
  * @}
  */

#define TIM_MASTERSLAVEMODE_DISABLE  0       
#define TIM_MASTERSLAVEMODE_ENABLE   BIT7  


#define TIM_SLAVE_MODE_INDEX     0 
#define TIM_SLAVE_MODE_DIS       (0U << TIM_SLAVE_MODE_INDEX) 
#define TIM_SLAVE_MODE_ENC1      (1U << TIM_SLAVE_MODE_INDEX) 
#define TIM_SLAVE_MODE_ENC2      (2U << TIM_SLAVE_MODE_INDEX) 
#define TIM_SLAVE_MODE_ENC3      (3U << TIM_SLAVE_MODE_INDEX) 
#define TIM_SLAVE_MODE_RST       (4U << TIM_SLAVE_MODE_INDEX) 
#define TIM_SLAVE_MODE_GATE      (5U << TIM_SLAVE_MODE_INDEX) 
#define TIM_SLAVE_MODE_TRIG      (6U << TIM_SLAVE_MODE_INDEX) 
#define TIM_SLAVE_MODE_EXT1      (7U << TIM_SLAVE_MODE_INDEX)   

#define TIM_SMCR_OCCS_Pos        (3U)
#define TIM_SMCR_OCCS_Msk        (0x1UL << TIM_SMCR_OCCS_Pos)                 /*!< 0x00000008 */
#define TIM_SMCR_OCCS            TIM_SMCR_OCCS_Msk                            /*!< OCREF clear selection */

#define TIM_SMCR_TS_Pos          (4U)
#define TIM_SMCR_TS_Msk          (0x30007UL << TIM_SMCR_TS_Pos)               /*!< 0x00300070 */
#define TIM_SMCR_TS              TIM_SMCR_TS_Msk                              /*!<TS[2:0] bits (Trigger selection) */
#define TIM_SMCR_TS_0            (0x00001UL << TIM_SMCR_TS_Pos)               /*!< 0x00000010 */
#define TIM_SMCR_TS_1            (0x00002UL << TIM_SMCR_TS_Pos)               /*!< 0x00000020 */
#define TIM_SMCR_TS_2            (0x00004UL << TIM_SMCR_TS_Pos)               /*!< 0x00000040 */
#define TIM_SMCR_TS_3            (0x10000UL << TIM_SMCR_TS_Pos)               /*!< 0x00100000 */
#define TIM_SMCR_TS_4            (0x20000UL << TIM_SMCR_TS_Pos)               /*!< 0x00200000 */

#define TIM_TS_ITR0              (0x00000000U)                                     /*!< Internal Trigger 0 (ITR0)              */
#define TIM_TS_ITR1              (TIM_SMCR_TS_0)                                   /*!< Internal Trigger 1 (ITR1)              */
#define TIM_TS_ITR2              (TIM_SMCR_TS_1)                                   /*!< Internal Trigger 2 (ITR2)              */
#define TIM_TS_ITR3              (TIM_SMCR_TS_0 | TIM_SMCR_TS_1)                   /*!< Internal Trigger 3 (ITR3)              */
#define TIM_TS_TI1F_ED           (TIM_SMCR_TS_2)                                   /*!< TI1 Edge Detector (TI1F_ED)            */
#define TIM_TS_TI1FP1            (TIM_SMCR_TS_0 | TIM_SMCR_TS_2)                   /*!< Filtered Timer Input 1 (TI1FP1)        */
#define TIM_TS_TI2FP2            (TIM_SMCR_TS_1 | TIM_SMCR_TS_2)                   /*!< Filtered Timer Input 2 (TI2FP2)        */
#define TIM_TS_ETRF              (TIM_SMCR_TS_0 | TIM_SMCR_TS_1 | TIM_SMCR_TS_2)   /*!< Filtered External Trigger input (ETRF) */
#define TIM_TS_ITR4              (TIM_SMCR_TS_3)                                   /*!< Internal Trigger 4 (ITR4)              */
#define TIM_TS_ITR5              (TIM_SMCR_TS_0 | TIM_SMCR_TS_3)                   /*!< Internal Trigger 5 (ITR5)              */
#define TIM_TS_ITR6              (TIM_SMCR_TS_1 | TIM_SMCR_TS_3)                   /*!< Internal Trigger 6 (ITR6)              */
#define TIM_TS_ITR7              (TIM_SMCR_TS_0 | TIM_SMCR_TS_1 | TIM_SMCR_TS_3)   /*!< Internal Trigger 7 (ITR7)              */
#define TIM_TS_ITR8              (TIM_SMCR_TS_2 | TIM_SMCR_TS_3)                   /*!< Internal Trigger 8 (ITR8)              */
#define TIM_TS_ITR9              (TIM_SMCR_TS_0 | TIM_SMCR_TS_2 | TIM_SMCR_TS_3)   /*!< Internal Trigger 9 (ITR9)              */
#define TIM_TS_ITR10             (TIM_SMCR_TS_1 | TIM_SMCR_TS_2 | TIM_SMCR_TS_3)   /*!< Internal Trigger 10(ITR10)              */
#define TIM_TS_NONE              0x0000FFFFU                                       /*!< No trigger selected                    */

#define TIMER_SR_UIF    BIT0 
#define TIMER_SR_CC1IF  BIT1
#define TIMER_SR_CC2IF  BIT2
#define TIMER_SR_CC3IF  BIT3
#define TIMER_SR_CC4IF  BIT4
#define TIMER_SR_COMIF  BIT5
#define TIMER_SR_TIF    BIT6
#define TIMER_SR_BIF    BIT7
#define TIMER_SR_CC1OF  BIT9
#define TIMER_SR_CC2OF  BIT10
#define TIMER_SR_CC3OF  BIT11
#define TIMER_SR_CC4OF  BIT12     
#define TIMER_SR_CC5IF  BIT16
#define TIMER_SR_CC6IF  BIT17

#define TIMER_INT_EN_UPD       BIT0    
#define TIMER_INT_EN_CC1       BIT1
#define TIMER_INT_EN_CC2       BIT2
#define TIMER_INT_EN_CC3       BIT3
#define TIMER_INT_EN_CC4       BIT4
#define TIMER_INT_EN_COM       BIT5
#define TIMER_INT_EN_TRI       BIT6
#define TIMER_INT_EN_BRK       BIT7   

#define TIMER_DMA_EN_UPD       BIT8    
#define TIMER_DMA_EN_CC1       BIT9
#define TIMER_DMA_EN_CC2       BIT10
#define TIMER_DMA_EN_CC3       BIT11
#define TIMER_DMA_EN_CC4       BIT12
#define TIMER_DMA_EN_COM       BIT13
#define TIMER_DMA_EN_TRI       BIT14   

#define TIM_CHANNEL_1                      0                       
#define TIM_CHANNEL_2                      1                       
#define TIM_CHANNEL_3                      2                         
#define TIM_CHANNEL_4                      3      
#define TIM_CHANNEL_5                      4      
#define TIM_CHANNEL_6                      5      

#define OUTPUT_FAST_MODE_DISABLE  0  
#define OUTPUT_FAST_MODE_ENABLE   1    

#define OUTPUT_POL_ACTIVE_HIGH  0  
#define OUTPUT_POL_ACTIVE_LOW   1      

#define OUTPUT_DISABLE_IDLE_STATE  0 
#define OUTPUT_ENABLE_IDLE_STATE   1 

#define OUTPUT_IDLE_STATE_0     0  
#define OUTPUT_IDLE_STATE_1     1  

#define OUTPUT_MODE_FROZEN          0
#define OUTPUT_MODE_MATCH_HIGH      1
#define OUTPUT_MODE_MATCH_LOW       2 
#define OUTPUT_MODE_MATCH_TOGGLE    3 
#define OUTPUT_MODE_FORCE_LOW       4
#define OUTPUT_MODE_FORCE_HIGH      5   
#define OUTPUT_MODE_PWM1            6  
#define OUTPUT_MODE_PWM2            7     

#define INPUT_ACTIVE_RISING  0 
#define INPUT_ACTIVE_FALLING   1    
#define INPUT_ACTIVE_RISING_FALLING   2   

#define INPUT_FILTER_LEVEL_0           0  // No Filter 
#define INPUT_FILTER_LEVEL_1           1 
#define INPUT_FILTER_LEVEL_2           2   
#define INPUT_FILTER_LEVEL_3           3  
#define INPUT_FILTER_LEVEL_4           4  
#define INPUT_FILTER_LEVEL_5           5  
#define INPUT_FILTER_LEVEL_6           6 
#define INPUT_FILTER_LEVEL_7           7 
#define INPUT_FILTER_LEVEL_8           8  
#define INPUT_FILTER_LEVEL_9           9 
#define INPUT_FILTER_LEVEL_10          10   
#define INPUT_FILTER_LEVEL_11          11  
#define INPUT_FILTER_LEVEL_12          12  
#define INPUT_FILTER_LEVEL_13          13  
#define INPUT_FILTER_LEVEL_14          14  
#define INPUT_FILTER_LEVEL_15          15    
            
#define TIM_CLOCKSOURCE_ITR0      TIM_TS_ITR0                        
#define TIM_CLOCKSOURCE_ITR1      TIM_TS_ITR1                   
#define TIM_CLOCKSOURCE_ITR2      TIM_TS_ITR2                        
#define TIM_CLOCKSOURCE_ITR3      TIM_TS_ITR3                         
#define TIM_CLOCKSOURCE_TI1F_ED   TIM_TS_TI1F_ED
#define TIM_CLOCKSOURCE_TI1FP1    TIM_TS_TI1FP1                    
#define TIM_CLOCKSOURCE_TI2FP2    TIM_TS_TI2FP2                    
#define TIM_CLOCKSOURCE_ETR       TIM_TS_ETRF     
#define TIM_CLOCKSOURCE_ITR4      TIM_TS_ITR4
#define TIM_CLOCKSOURCE_ITR5      TIM_TS_ITR5
#define TIM_CLOCKSOURCE_ITR6      TIM_TS_ITR6
#define TIM_CLOCKSOURCE_ITR7      TIM_TS_ITR7
#define TIM_CLOCKSOURCE_ITR8      TIM_TS_ITR8
#define TIM_CLOCKSOURCE_ITR9      TIM_TS_ITR9
#define TIM_CLOCKSOURCE_ITR10     TIM_TS_ITR10

#define TIM_ETR_POLAIRTY_HIGH     0    
#define TIM_ETR_POLAIRTY_LOW      (BIT15)       
#define TIM_ETR_FILTER_LVL(x)     (x << 8)   //BIT8-BIT11  

#define TIM_ETR_PRESCALER_1    0  
#define TIM_ETR_PRESCALER_2    (BIT12)
#define TIM_ETR_PRESCALER_4    (BIT13) 
#define TIM_ETR_PRESCALER_8    (BIT12|BIT13)  

#define ETR_SELECT_GPIO        0  
#define ETR_SELECT_IN1         BIT14   
#define ETR_SELECT_IN2         BIT15  
#define ETR_SELECT_IN3        (BIT14|BIT15)    
#define ETR_SELECT_IN4         BIT16    
#define ETR_SELECT_IN5        (BIT14|BIT16)    
#define ETR_SELECT_IN6        (BIT15|BIT16)    
#define ETR_SELECT_IN7        (BIT14|BIT15|BIT16)   
#define ETR_SELECT_IN8        (BIT17)    
#define ETR_SELECT_IN9        (BIT14|BIT17)  
#define ETR_SELECT_IN10       (BIT17|BIT15)    
#define ETR_SELECT_IN11       (BIT17|BIT15|BIT14)  
#define ETR_SELECT_IN12       (BIT17|BIT16) 
#define ETR_SELECT_IN13       (BIT17|BIT16|BIT14) 
#define ETR_SELECT_IN14       (BIT17|BIT16|BIT15) 
#define ETR_SELECT_IN15       (BIT17|BIT16|BIT15|BIT14) 
#define ETR_SELECT_MASK       (BIT14|BIT15|BIT16|BIT17)    

#define TIM_TI1_FILTER_LVL(x)     (x << 4)          
#define TIM_TI2_FILTER_LVL(x)     (x << 12)     
#define TIM_TI3_FILTER_LVL(x)     (x << 4) 
#define TIM_TI4_FILTER_LVL(x)     (x << 12)    

#define TIM_IC1_PRESCALER_1    0  
#define TIM_IC1_PRESCALER_2    (BIT2)
#define TIM_IC1_PRESCALER_4    (BIT3) 
#define TIM_IC1_PRESCALER_8    (BIT2|BIT3)  

#define TIM_IC2_PRESCALER_1    0  
#define TIM_IC2_PRESCALER_2    (BIT10)
#define TIM_IC2_PRESCALER_4    (BIT11) 
#define TIM_IC2_PRESCALER_8    (BIT10|BIT11)    

#define TIM_IC3_PRESCALER_1    0  
#define TIM_IC3_PRESCALER_2    (BIT2)
#define TIM_IC3_PRESCALER_4    (BIT3) 
#define TIM_IC3_PRESCALER_8    (BIT2|BIT3)  

#define TIM_IC4_PRESCALER_1    0  
#define TIM_IC4_PRESCALER_2    (BIT10)
#define TIM_IC4_PRESCALER_4    (BIT11) 
#define TIM_IC4_PRESCALER_8    (BIT10|BIT11)    

typedef struct
{
  uint32_t ClockSource;     //TIMER clock sources                              
  uint32_t ClockPolarity;   //TIMER clock polarity                               
  uint32_t ClockPrescaler;  //TIMER clock prescaler                                
  uint32_t ClockFilter;     //TIMER clock filter          
} TIM_ClockConfigTypeDef;

typedef struct
{
  uint32_t OCMode;        // Specifies the TIM mode. 
  uint32_t Pulse;         // Specifies the pulse value to be loaded into the Capture Compare Register.
  uint32_t OCPolarity;    // Specifies the output polarity. 
  uint32_t OCNPolarity;   // Specifies the complementary output polarity.   
  uint32_t OCFastMode;    // Specifies the Fast mode state.
  uint32_t OCIdleState;   // Specifies the TIM Output Compare pin state during Idle state.   
  uint32_t OCNIdleState;  // Specifies the TIM Output Compare complementary pin state during Idle state. 
} TIM_OC_InitTypeDef; 
      


#define TIM_SLAVE_CAPTURE_ACTIVE_RISING          0    
#define TIM_SLAVE_CAPTURE_ACTIVE_FALLING         1    
#define TIM_SLAVE_CAPTURE_ACTIVE_RISING_FALLING  2               

#define TIM_ICSELECTION_DIRECTTI    0  
#define TIM_ICSELECTION_INDIRECTTI  1        

#define TIM_CC1_SLAVE_CAPTURE_POL_RISING    (0)    
#define TIM_CC1_SLAVE_CAPTURE_POL_FALLING   (BIT1)    
#define TIM_CC1_SLAVE_CAPTURE_POL_BOTH      (BIT1 | BIT3)    

#define TIM_CC2_SLAVE_CAPTURE_POL_RISING    (0)    
#define TIM_CC2_SLAVE_CAPTURE_POL_FALLING   (BIT5)    
#define TIM_CC2_SLAVE_CAPTURE_POL_BOTH      (BIT5 | BIT7)   

#define TIM_CC3_SLAVE_CAPTURE_POL_RISING    (0)  
#define TIM_CC3_SLAVE_CAPTURE_POL_FALLING   (BIT9)   
#define TIM_CC3_SLAVE_CAPTURE_POL_BOTH      (BIT9 | BIT11)   

#define TIM_CC4_SLAVE_CAPTURE_POL_RISING    (0)  
#define TIM_CC4_SLAVE_CAPTURE_POL_FALLING   (BIT13)   
#define TIM_CC4_SLAVE_CAPTURE_POL_BOTH      (BIT13 | BIT15)     

#define TIM_64_FREE_RUNNING_MODE   0  
#define TIM_64_ARR_MODE            1    

typedef struct
{
    uint32_t  SlaveMode;         // Slave mode selection
    uint32_t  InputTrigger;      // Input Trigger source
    uint32_t  TriggerPolarity;   // Input Trigger polarity 
    uint32_t  TriggerPrescaler;  // input prescaler, only for ETR input 
    uint32_t  TriggerFilter;     // Input trigger filter  
} TIM_SlaveConfigTypeDef;

typedef struct
{
    uint32_t ICPolarity;   // Specifies the active edge of the input signal.
    uint32_t ICSelection;  // Specifies the input  
    uint32_t ICPrescaler;  // Specifies the Input Capture Prescaler. 
    uint32_t TIFilter;     // Specifies the input capture filter.
} TIM_IC_InitTypeDef;         

typedef struct   
{
    uint32_t  MasterOutputTrigger;   // Trigger output (TRGO) selection
                                   // This parameter can be a value of @ref TIM_Master_Mode_Selection
    uint32_t  MasterOutputTrigger2;  // Trigger output2 (TRGO2) selection
                                   // This parameter can be a value of @ref TIM_Master_Mode_Selection_2
    uint32_t  MasterSlaveMode;       // Master/slave mode selection  
} TIM_MasterConfigTypeDef;     

#define TIM_DMA_UPDATE_INDEX    0  
#define TIM_DMA_CC1_INDEX       1   
#define TIM_DMA_CC2_INDEX       2  
#define TIM_DMA_CC3_INDEX       3  
#define TIM_DMA_CC4_INDEX       4  
#define TIM_DMA_COM_INDEX       5  
#define TIM_DMA_TRIG_INDEX      6          

#define MAX_DMA_REQ_ONE_TIMER   7  

typedef struct
{
    uint32_t Prescaler;         // Specifies the prescaler value used to divide the TIM clock.   
    uint32_t Period;            // Specifies the ARR value  	
    uint32_t ARRPreLoadEn;      // Specifies the preload enable or disable 
    uint32_t RepetitionCounter; // Specifies the repetition counter value     
    uint32_t CounterMode;       // Specifies the counter mode.Up/Down/Center    
    uint32_t ClockDivision;     // Specifies the clock division, used for deadtime or sampling      
} TIM_Base_InitTypeDef; 


typedef struct
{
    uint32_t Prescaler;         // Specifies the prescaler value used to divide the TIM clock.   
    uint32_t Period_Low;        // Specifies the ARR low value  
    uint32_t Period_High;       // Specifies the ARR high value 
 	uint32_t Count_Low;         // Specifies the Count low value  
    uint32_t Count_High;        // Specifies the Count high value 
    uint32_t Cnt_Mode;          // Count mode, free running or to ARR value   
    uint32_t ARR_Preload_En;   
} TIM_64_Base_InitTypeDef; 

typedef enum
{
  HAL_TIM_ACTIVE_CHANNEL_1        = 0x01U,    /*!< The active channel is 1     */
  HAL_TIM_ACTIVE_CHANNEL_2        = 0x02U,    /*!< The active channel is 2     */
  HAL_TIM_ACTIVE_CHANNEL_3        = 0x04U,    /*!< The active channel is 3     */
  HAL_TIM_ACTIVE_CHANNEL_4        = 0x08U,    /*!< The active channel is 4     */
  HAL_TIM_ACTIVE_CHANNEL_5        = 0x10U,    /*!< The active channel is 5     */
  HAL_TIM_ACTIVE_CHANNEL_6        = 0x20U,    /*!< The active channel is 6     */
  HAL_TIM_ACTIVE_CHANNEL_CLEARED  = 0x00U    /*!< All active channels cleared */
} HAL_TIM_ActiveChannel;

typedef struct
{
    TIM_TypeDef *Instance;         
    TIM_Base_InitTypeDef     Init;          /*!< TIM Time Base required parameters */  
#ifdef HAL_DMA_MODULE_ENABLED    
    DMA_HandleTypeDef        *hdma[MAX_DMA_REQ_ONE_TIMER];   
#endif    
    HAL_TIM_ActiveChannel    activeChannel;   
}TIM_HandleTypeDef;   

typedef struct
{
    TIM_64BIT_TypeDef *Instance;         
    TIM_64_Base_InitTypeDef     Init;          /*!< TIM 64BIT Time Base required parameters */    
}TIM_64_HandleTypeDef;   

/* HAL_TIM_IRQHandler */  
void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim); 
/* HAL_TIMER_MSP_Init */  
extern uint32_t HAL_TIMER_MSP_Init(TIM_HandleTypeDef * htim);  
/* HAL_TIMER_Slave_Mode_Config */  
extern uint32_t HAL_TIMER_Slave_Mode_Config(TIM_HandleTypeDef *htim, TIM_SlaveConfigTypeDef *sSlaveConfig);   
/* HAL_TIMER_Base_Init */ 
extern uint32_t HAL_TIMER_Base_Init(TIM_HandleTypeDef * htim);   
/* HAL_TIMER_Output_Config */ 
extern uint32_t HAL_TIMER_Output_Config(TIM_TypeDef *TIMx, TIM_OC_InitTypeDef * Output_Config, uint32_t Channel);     
/* HAL_TIMER_Base_Start */ 
extern void HAL_TIMER_Base_Start(TIM_TypeDef *TIMx);    
/* HAL_TIMER_Base_Stop */ 
extern HAL_StatusTypeDef HAL_TIMER_Base_Stop(TIM_TypeDef *TIMx);  
/* HAL_TIMER_Base_Start_DMA */   
extern HAL_StatusTypeDef HAL_TIMER_Base_Start_DMA(TIM_HandleTypeDef *htim, uint32_t start_addr, uint32_t transfer_size);  

/* HAL_TIM_PWM_Output_Start */ 
extern uint32_t HAL_TIM_PWM_Output_Start(TIM_TypeDef *TIMx, uint32_t Channel);   
/* HAL_TIM_PWM_Output_Stop */    
extern HAL_StatusTypeDef HAL_TIM_PWM_Output_Stop(TIM_TypeDef *TIMx, uint32_t Channel);     
/* HAL_TIMER_OC_Start */ 
extern uint32_t HAL_TIMER_OC_Start(TIM_TypeDef *TIMx, uint32_t Channel);  
/* HAL_TIMER_OCxN_Start */    
extern uint32_t HAL_TIMER_OCxN_Start(TIM_TypeDef *TIMx, uint32_t Channel);      
/* HAL_TIMER_OC_Stop */ 
extern HAL_StatusTypeDef HAL_TIM_OC_Stop(TIM_TypeDef *TIMx, uint32_t Channel);      
/* HAL_TIM_Capture_Start */ 
extern uint32_t HAL_TIM_Capture_Start(TIM_TypeDef *TIMx, uint32_t Channel);       
/* HAL_TIM_Capture_Stop */   
extern uint32_t HAL_TIM_Capture_Stop(TIM_TypeDef *TIMx, uint32_t Channel);    
/* HAL_TIMER_Capture_Config */
extern uint32_t HAL_TIMER_Capture_Config(TIM_TypeDef *TIMx, TIM_IC_InitTypeDef * Capture_Config, uint32_t Channel);    
/* HAL_TIMER_Master_Mode_Config */   
extern uint32_t HAL_TIMER_Master_Mode_Config(TIM_TypeDef *TIMx, TIM_MasterConfigTypeDef * sMasterConfig);  
/* HAL_TIMER_SelectClockSource */  
extern HAL_StatusTypeDef HAL_TIMER_SelectClockSource(TIM_HandleTypeDef *htim, TIM_ClockConfigTypeDef * sClockSourceConfig);  
/* HAL_TIMER_ReadCapturedValue */   
extern uint32_t HAL_TIMER_ReadCapturedValue(TIM_HandleTypeDef *htim, uint32_t Channel);   
/* HAL_TIMER_Clear_Capture_Flag */     
extern void HAL_TIMER_Clear_Capture_Flag(TIM_HandleTypeDef *htim, uint32_t Channel);   

extern uint32_t HAL_TIMER_Base_MspDeInit(TIM_HandleTypeDef * htim);     

extern HAL_StatusTypeDef HAL_TIMER_OnePulse_Init(TIM_HandleTypeDef *htim, uint32_t mode); 

HAL_StatusTypeDef  HAL_TIMEx_ETRSelection(TIM_HandleTypeDef *htim, uint32_t ETRSelection); 

void HAL_TIMER_64_Base_Init(TIM_64_HandleTypeDef *htim);           
void HAL_TIMER_64_Base_Start(TIM_64BIT_TypeDef *TIMx);   
void HAL_TIMER_64_Enable_Interrupt(TIM_64BIT_TypeDef *TIMx);   
long long HAL_TIMER_64_Base_Read_Count(TIM_64BIT_TypeDef *TIMx); 

#endif  




