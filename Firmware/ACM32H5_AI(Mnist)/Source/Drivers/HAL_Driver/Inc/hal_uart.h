/******************************************************************************
* @file    hal_uart.h

* @brief   Header file of UART HAL module.
* @version V1.0.0
* @date    2020
******************************************************************************/
#ifndef __HAL_UART_H__
#define __HAL_UART_H__

#include "acm32h5xx_hal_conf.h"

typedef USART_TypeDef   UART_TypeDef;  

#define UART_DR_OE_Pos            USART_DR_OE_Pos                          
#define UART_DR_OE_Msk            USART_DR_OE_Msk                          
#define UART_DR_OE                USART_DR_OE                              
						          
#define UART_DR_BE_Pos            USART_DR_BE_Pos                          
#define UART_DR_BE_Msk            USART_DR_BE_Msk                          
#define UART_DR_BE                USART_DR_BE                              
						          
#define UART_DR_PE_Pos            USART_DR_PE_Pos                          
#define UART_DR_PE_Msk            USART_DR_PE_Msk                          
#define UART_DR_PE                USART_DR_PE                              
						          
#define UART_DR_FE_Pos            USART_DR_FE_Pos                          
#define UART_DR_FE_Msk            USART_DR_FE_Msk                          
#define UART_DR_FE                USART_DR_FE                              
						          
#define UART_DR_DATA_Pos          USART_DR_DATA_Pos                        
#define UART_DR_DATA_Msk          USART_DR_DATA_Msk                        
#define UART_DR_DATA              USART_DR_DATA                            
						          					          
#define UART_FR_BUSY_Pos          USART_FR_BUSY_Pos                        
#define UART_FR_BUSY_Msk          USART_FR_BUSY_Msk                        
#define UART_FR_BUSY              USART_FR_BUSY                            
						          
#define UART_FR_CTS_Pos           USART_FR_CTS_Pos                         
#define UART_FR_CTS_Msk           USART_FR_CTS_Msk                         
#define UART_FR_CTS               USART_FR_CTS                             
						          
#define UART_FR_TXFE_Pos          USART_FR_TXFE_Pos                        
#define UART_FR_TXFE_Msk          USART_FR_TXFE_Msk                        
#define UART_FR_TXFE              USART_FR_TXFE                            
						          
#define UART_FR_RXFF_Pos          USART_FR_RXFF_Pos                        
#define UART_FR_RXFF_Msk          USART_FR_RXFF_Msk                        
#define UART_FR_RXFF              USART_FR_RXFF                            
						          
#define UART_FR_TXFF_Pos          USART_FR_TXFF_Pos                        
#define UART_FR_TXFF_Msk          USART_FR_TXFF_Msk                        
#define UART_FR_TXFF              USART_FR_TXFF                            
						          
#define UART_FR_RXFE_Pos          USART_FR_RXFE_Pos                        
#define UART_FR_RXFE_Msk          USART_FR_RXFE_Msk                        
#define UART_FR_RXFE              USART_FR_RXFE                            
						          
#define UART_FR_OE_Pos            USART_FR_OE_Pos                          
#define UART_FR_OE_Msk            USART_FR_OE_Msk                          
#define UART_FR_OE                USART_FR_OE                              
						          
#define UART_FR_BE_Pos            USART_FR_BE_Pos                          
#define UART_FR_BE_Msk            USART_FR_BE_Msk                          
#define UART_FR_BE                USART_FR_BE                              
						          
#define UART_FR_PE_Pos            USART_FR_PE_Pos                          
#define UART_FR_PE_Msk            USART_FR_PE_Msk                          
#define UART_FR_PE                USART_FR_PE                              
						          
#define UART_FR_FE_Pos            USART_FR_FE_Pos                          
#define UART_FR_FE_Msk            USART_FR_FE_Msk                          
#define UART_FR_FE                USART_FR_FE                              

#define UART_BRR_IBAUD_Pos        USART_BRR_IBAUD_Pos                 
#define UART_BRR_IBAUD_Msk        USART_BRR_IBAUD_Msk                 
#define UART_BRR_IBAUD            USART_BRR_IBAUD                     
								  
#define UART_BRR_FBAUD_Pos        USART_BRR_FBAUD_Pos                 
#define UART_BRR_FBAUD_Msk        USART_BRR_FBAUD_Msk                 
#define UART_BRR_FBAUD            USART_BRR_FBAUD                     
								  
#define UART_IE_TCI_Pos           USART_IE_TCI_Pos 
#define UART_IE_TCI_Msk           USART_IE_TCI_Msk 
#define UART_IE_TCI               USART_IE_TCI                                       
                                    
#define UART_IE_ABRI_Pos          USART_IE_ABRI_Pos                        
#define UART_IE_ABRI_Msk          USART_IE_ABRI_Msk                        
#define UART_IE_ABRI              USART_IE_ABRI                            
								  
#define UART_IE_IDLEI_Pos         USART_IE_IDLEI_Pos                       
#define UART_IE_IDLEI_Msk         USART_IE_IDLEI_Msk                       
#define UART_IE_IDLEI             USART_IE_IDLEI                           
								  
#define UART_IE_BCNTI_Pos         USART_IE_BCNTI_Pos                       
#define UART_IE_BCNTI_Msk         USART_IE_BCNTI_Msk                       
#define UART_IE_BCNTI             USART_IE_BCNTI                           
								  
#define UART_IE_LBDI_Pos          USART_IE_LBDI_Pos                        
#define UART_IE_LBDI_Msk          USART_IE_LBDI_Msk                        
#define UART_IE_LBDI              USART_IE_LBDI                            
								  
#define UART_IE_OEI_Pos           USART_IE_OEI_Pos                         
#define UART_IE_OEI_Msk           USART_IE_OEI_Msk                         
#define UART_IE_OEI               USART_IE_OEI                             
								  
#define UART_IE_BEI_Pos           USART_IE_BEI_Pos                         
#define UART_IE_BEI_Msk           USART_IE_BEI_Msk                         
#define UART_IE_BEI               USART_IE_BEI                             
								  
#define UART_IE_PEI_Pos           USART_IE_PEI_Pos                         
#define UART_IE_PEI_Msk           USART_IE_PEI_Msk                         
#define UART_IE_PEI               USART_IE_PEI                             
								  
#define UART_IE_FEI_Pos           USART_IE_FEI_Pos                         
#define UART_IE_FEI_Msk           USART_IE_FEI_Msk                         
#define UART_IE_FEI               USART_IE_FEI                             
								  
#define UART_IE_TXI_Pos           USART_IE_TXI_Pos                         
#define UART_IE_TXI_Msk           USART_IE_TXI_Msk                         
#define UART_IE_TXI               USART_IE_TXI                             
								  
#define UART_IE_RXI_Pos           USART_IE_RXI_Pos                         
#define UART_IE_RXI_Msk           USART_IE_RXI_Msk                         
#define UART_IE_RXI               USART_IE_RXI                             



#define UART_ISR_TCI_Pos          USART_ISR_TCI_Pos 
#define UART_ISR_TCI_Msk          USART_ISR_TCI_Msk 
#define UART_ISR_TCI              USART_ISR_TCI     
								  
#define UART_ISR_ABRI_Pos         USART_ISR_ABRI_Pos                       
#define UART_ISR_ABRI_Msk         USART_ISR_ABRI_Msk                       
#define UART_ISR_ABRI             USART_ISR_ABRI                           
								  
#define UART_ISR_IDLEI_Pos        USART_ISR_IDLEI_Pos                      
#define UART_ISR_IDLEI_Msk        USART_ISR_IDLEI_Msk                      
#define UART_ISR_IDLEI            USART_ISR_IDLEI                          
								  
#define UART_ISR_BCNTI_Pos        USART_ISR_BCNTI_Pos                      
#define UART_ISR_BCNTI_Msk        USART_ISR_BCNTI_Msk                      
#define UART_ISR_BCNTI            USART_ISR_BCNTI                          
								  
#define UART_ISR_LBDI_Pos         USART_ISR_LBDI_Pos                       
#define UART_ISR_LBDI_Msk         USART_ISR_LBDI_Msk                       
#define UART_ISR_LBDI             USART_ISR_LBDI                           
								  
#define UART_ISR_OEI_Pos          USART_ISR_OEI_Pos                        
#define UART_ISR_OEI_Msk          USART_ISR_OEI_Msk                        
#define UART_ISR_OEI              USART_ISR_OEI                            
								  
#define UART_ISR_BEI_Pos          USART_ISR_BEI_Pos                        
#define UART_ISR_BEI_Msk          USART_ISR_BEI_Msk                        
#define UART_ISR_BEI              USART_ISR_BEI                            
								  
#define UART_ISR_PEI_Pos          USART_ISR_PEI_Pos                        
#define UART_ISR_PEI_Msk          USART_ISR_PEI_Msk                        
#define UART_ISR_PEI              USART_ISR_PEI                            
								  
#define UART_ISR_FEI_Pos          USART_ISR_FEI_Pos                        
#define UART_ISR_FEI_Msk          USART_ISR_FEI_Msk                        
#define UART_ISR_FEI              USART_ISR_FEI                            
								  
#define UART_ISR_TXI_Pos          USART_ISR_TXI_Pos                        
#define UART_ISR_TXI_Msk          USART_ISR_TXI_Msk                        
#define UART_ISR_TXI              USART_ISR_TXI                            
								  
#define UART_ISR_RXI_Pos          USART_ISR_RXI_Pos                        
#define UART_ISR_RXI_Msk          USART_ISR_RXI_Msk                        
#define UART_ISR_RXI              USART_ISR_RXI                            
								  
								  
#define UART_CR1_CTSEN_Pos        USART_CR1_CTSEN_Pos                      
#define UART_CR1_CTSEN_Msk        USART_CR1_CTSEN_Msk                      
#define UART_CR1_CTSEN            USART_CR1_CTSEN                          
								  
#define UART_CR1_RTSEN_Pos        USART_CR1_RTSEN_Pos                      
#define UART_CR1_RTSEN_Msk        USART_CR1_RTSEN_Msk                      
#define UART_CR1_RTSEN            USART_CR1_RTSEN                          
								  
#define UART_CR1_RTS_Pos          USART_CR1_RTS_Pos                        
#define UART_CR1_RTS_Msk          USART_CR1_RTS_Msk                        
#define UART_CR1_RTS              USART_CR1_RTS                            
								  
#define UART_CR1_RXE_Pos          USART_CR1_RXE_Pos                        
#define UART_CR1_RXE_Msk          USART_CR1_RXE_Msk                        
#define UART_CR1_RXE              USART_CR1_RXE                            
								  
#define UART_CR1_TXE_Pos          USART_CR1_TXE_Pos                        
#define UART_CR1_TXE_Msk          USART_CR1_TXE_Msk                        
#define UART_CR1_TXE              USART_CR1_TXE                            
								  
#define UART_CR1_DMAONERR_Pos     USART_CR1_DMAONERR_Pos                   
#define UART_CR1_DMAONERR_Msk     USART_CR1_DMAONERR_Msk                   
#define UART_CR1_DMAONERR         USART_CR1_DMAONERR                       
								  
#define UART_CR1_TXDMAE_Pos       USART_CR1_TXDMAE_Pos                     
#define UART_CR1_TXDMAE_Msk       USART_CR1_TXDMAE_Msk                     
#define UART_CR1_TXDMAE           USART_CR1_TXDMAE                         
								  
#define UART_CR1_RXDMAE_Pos       USART_CR1_RXDMAE_Pos                     
#define UART_CR1_RXDMAE_Msk       USART_CR1_RXDMAE_Msk                     
#define UART_CR1_RXDMAE           USART_CR1_RXDMAE                         
								  
#define UART_CR1_SIRLP_Pos        USART_CR1_SIRLP_Pos                      
#define UART_CR1_SIRLP_Msk        USART_CR1_SIRLP_Msk                      
#define UART_CR1_SIRLP            USART_CR1_SIRLP                          
								  
#define UART_CR1_SIREN_Pos        USART_CR1_SIREN_Pos                      
#define UART_CR1_SIREN_Msk        USART_CR1_SIREN_Msk                      
#define UART_CR1_SIREN            USART_CR1_SIREN                          
								  
#define UART_CR1_UARTEN_Pos       USART_CR1_USARTEN_Pos                    
#define UART_CR1_UARTEN_Msk       USART_CR1_USARTEN_Msk                    
#define UART_CR1_UARTEN           USART_CR1_USARTEN                        
								  
								  
#define UART_CR2_ADDM7_Pos        USART_CR2_ADDM7_Pos                      
#define UART_CR2_ADDM7_Msk        USART_CR2_ADDM7_Msk                      
#define UART_CR2_ADDM7            USART_CR2_ADDM7                          
								  
#define UART_CR2_ADDR_Pos         USART_CR2_ADDR_Pos                       
#define UART_CR2_ADDR_Msk         USART_CR2_ADDR_Msk                       
#define UART_CR2_ADDR             USART_CR2_ADDR                           
								  
#define UART_CR2_CLKEN_Pos        USART_CR2_CLKEN_Pos                      
#define UART_CR2_CLKEN_Msk        USART_CR2_CLKEN_Msk                      
#define UART_CR2_CLKEN            USART_CR2_CLKEN                          
								  
#define UART_CR2_NACK_Pos         USART_CR2_NACK_Pos                       
#define UART_CR2_NACK_Msk         USART_CR2_NACK_Msk                       
#define UART_CR2_NACK             USART_CR2_NACK                           
								  
#define UART_CR2_SCEN_Pos         USART_CR2_SCEN_Pos                       
#define UART_CR2_SCEN_Msk         USART_CR2_SCEN_Msk                       
#define UART_CR2_SCEN             USART_CR2_SCEN                           
								  
#define UART_CR2_ABREN_Pos        USART_CR2_ABREN_Pos                      
#define UART_CR2_ABREN_Msk        USART_CR2_ABREN_Msk                      
#define UART_CR2_ABREN            USART_CR2_ABREN                          
								  
#define UART_CR2_WAKE_Pos         USART_CR2_WAKE_Pos                       
#define UART_CR2_WAKE_Msk         USART_CR2_WAKE_Msk                       
#define UART_CR2_WAKE             USART_CR2_WAKE                           
								  
#define UART_CR2_RWU_Pos          USART_CR2_RWU_Pos                        
#define UART_CR2_RWU_Msk          USART_CR2_RWU_Msk                        
#define UART_CR2_RWU              USART_CR2_RWU                            
								  
#define UART_CR2_HDSEL_Pos        USART_CR2_HDSEL_Pos                      
#define UART_CR2_HDSEL_Msk        USART_CR2_HDSEL_Msk                      
#define UART_CR2_HDSEL            USART_CR2_HDSEL                          
								  
								  
#define UART_CR3_RXIFLSEL_Pos     USART_CR3_RXIFLSEL_Pos                   
#define UART_CR3_RXIFLSEL_Msk     USART_CR3_RXIFLSEL_Msk                   
#define UART_CR3_RXIFLSEL         USART_CR3_RXIFLSEL                       
								  
#define UART_CR3_TXIFLSEL_Pos     USART_CR3_TXIFLSEL_Pos                   
#define UART_CR3_TXIFLSEL_Msk     USART_CR3_TXIFLSEL_Msk                   
#define UART_CR3_TXIFLSEL         USART_CR3_TXIFLSEL                       
								  
#define UART_CR3_SPS_Pos          USART_CR3_SPS_Pos                        
#define UART_CR3_SPS_Msk          USART_CR3_SPS_Msk                        
#define UART_CR3_SPS              USART_CR3_SPS                            
								  
#define UART_CR3_WLEN_Pos         USART_CR3_WLEN_Pos                       
#define UART_CR3_WLEN_Msk         USART_CR3_WLEN_Msk                       
#define UART_CR3_WLEN             USART_CR3_WLEN                           
								  
#define UART_CR3_FEN_Pos          USART_CR3_FEN_Pos                        
#define UART_CR3_FEN_Msk          USART_CR3_FEN_Msk                        
#define UART_CR3_FEN              USART_CR3_FEN                            
								  
#define UART_CR3_STP2_Pos         USART_CR3_STP2_Pos                       
#define UART_CR3_STP2_Msk         USART_CR3_STP2_Msk                       
#define UART_CR3_STP2             USART_CR3_STP2                           
								  
#define UART_CR3_EPS_Pos          USART_CR3_EPS_Pos                        
#define UART_CR3_EPS_Msk          USART_CR3_EPS_Msk                        
#define UART_CR3_EPS              USART_CR3_EPS                            
								  
#define UART_CR3_PEN_Pos          USART_CR3_PEN_Pos                        
#define UART_CR3_PEN_Msk          USART_CR3_PEN_Msk                        
#define UART_CR3_PEN              USART_CR3_PEN                            
								  
#define UART_CR3_BRK_Pos          USART_CR3_BRK_Pos                        
#define UART_CR3_BRK_Msk          USART_CR3_BRK_Msk                        
#define UART_CR3_BRK              USART_CR3_BRK                            
								  
#define UART_GTPR_GT_Pos          USART_GTPR_GT_Pos                        
#define UART_GTPR_GT_Msk          USART_GTPR_GT_Msk                        
#define UART_GTPR_GT              USART_GTPR_GT                            
								  
#define UART_GTPR_PSC_Pos         USART_GTPR_PSC_Pos                       
#define UART_GTPR_PSC_Msk         USART_GTPR_PSC_Msk                       
#define UART_GTPR_PSC             USART_GTPR_PSC                           
								  
								  
#define UART_BCNT_DEM_Pos         USART_BCNT_DEM_Pos                       
#define UART_BCNT_DEM_Msk         USART_BCNT_DEM_Msk                       
#define UART_BCNT_DEM             USART_BCNT_DEM                           
								  
#define UART_BCNT_DEP_Pos         USART_BCNT_DEP_Pos                       
#define UART_BCNT_DEP_Msk         USART_BCNT_DEP_Msk                       
#define UART_BCNT_DEP             USART_BCNT_DEP                           
								  
#define UART_BCNT_AUTO_START_EN_Pos USART_BCNT_AUTO_START_EN_Pos               
#define UART_BCNT_AUTO_START_EN_Msk USART_BCNT_AUTO_START_EN_Msk               
#define UART_BCNT_AUTO_START_EN     USART_BCNT_AUTO_START_EN                   
								  
#define UART_BCNT_BCNTSTART_Pos   USART_BCNT_BCNTSTART_Pos                 
#define UART_BCNT_BCNTSTART_Msk   USART_BCNT_BCNTSTART_Msk                 
#define UART_BCNT_BCNTSTART       USART_BCNT_BCNTSTART                     
								  
#define UART_BCNT_BCNTVALUE_Pos   USART_BCNT_BCNTVALUE_Pos                 
#define UART_BCNT_BCNTVALUE_Msk   USART_BCNT_BCNTVALUE_Msk                 
#define UART_BCNT_BCNTVALUE       USART_BCNT_BCNTVALUE                     
								  
								  
#define UART_BCNT_DEAT_Pos        USART_BCNT_DEAT_Pos                      
#define UART_BCNT_DEAT_Msk        USART_BCNT_DEAT_Msk                      
#define UART_BCNT_DEAT            USART_BCNT_DEAT                          
								  
#define UART_BCNT_DEDT_Pos        USART_BCNT_DEDT_Pos                      
#define UART_BCNT_DEDT_Msk        USART_BCNT_DEDT_Msk                      
#define UART_BCNT_DEDT            USART_BCNT_DEDT                          

/** @defgroup UARTEx_Word_Length UARTEx Word Length
  * @{
  */
#if 0  
#define UART_WORDLENGTH_5B                  (0x00000000U)    /*!< 5-bit Word Length */
#define UART_WORDLENGTH_6B                  (0x00000040U)    /*!< 6-bit Word Length */
#define UART_WORDLENGTH_7B                  (0x00000080U)    /*!< 7-bit Word Length */
#define UART_WORDLENGTH_8B                  (0x000000C0U)    /*!< 8-bit Word Length */
#define UART_WORDLENGTH_9B                  (0x00000100U)    /*!< 9-bit Word Length */
#else
#define UART_WORDLENGTH_5B                  (USART_WORDLENGTH_5B)
#define UART_WORDLENGTH_6B                  (USART_WORDLENGTH_6B)
#define UART_WORDLENGTH_7B                  (USART_WORDLENGTH_7B)
#define UART_WORDLENGTH_8B                  (USART_WORDLENGTH_8B)
#define UART_WORDLENGTH_9B                  (USART_WORDLENGTH_9B)
#endif
/**
  * @}
  */


/** @defgroup UART_Parity  UART Parity
  * @{
  */
#if 0  
#define UART_PARITY_NONE                    (0x00000000U)    /*!< No parity   */
#define UART_PARITY_EVEN                    (0x00000006U)    /*!< Even parity */
#define UART_PARITY_ODD                     (0x00000002U)    /*!< Odd parity  */
#define UART_PARITY_0                       (0x00000206U)    /*!< 0 parity  */
#define UART_PARITY_1                       (0x00000202U)    /*!< 1 parity  */
#else
#define UART_PARITY_NONE                    (USART_PARITY_NONE) 
#define UART_PARITY_EVEN                    (USART_PARITY_EVEN) 
#define UART_PARITY_ODD                     (USART_PARITY_ODD)  
#define UART_PARITY_0                       (USART_PARITY_0)    
#define UART_PARITY_1                       (USART_PARITY_1)    
#endif
/**
  * @}
  */


/** @defgroup UART_Stop_Bits   UART Number of Stop Bits
  * @{
  */
#if 0  
#define UART_STOPBITS_1                     (0x00000000U)    /*!< UART frame with 1 stop bit    */
#define UART_STOPBITS_2                     (0x00000008U)    /*!< UART frame with 2 stop bits   */
#else
#define UART_STOPBITS_1                     (USART_STOPBITS_1)
#define UART_STOPBITS_2                     (USART_STOPBITS_2)
#endif
/**
  * @}
  */


/** @defgroup UART_Hardware_Flow_Control UART Hardware Flow Control
  * @{
  */
#define UART_HWCONTROL_NONE                  (0x00000000U)                          /*!< No hardware control       */
#define UART_HWCONTROL_CTS                   (USART_CR1_CTSEN)                      /*!< Clear To Send             */
#define UART_HWCONTROL_RTS                   (USART_CR1_RTSEN)                      /*!< Request To Send           */
#define UART_HWCONTROL_CTS_RTS               (USART_CR1_CTSEN | USART_CR1_RTSEN)    /*!< Request and Clear To Send */
/**
  * @}
  */


/** @defgroup UART_Mode UART Transfer Mode
  * @{
  */
#define UART_MODE_RX                        (USART_MODE_RX)         /*!< RX mode        */
#define UART_MODE_TX                        (USART_MODE_TX)         /*!< TX mode        */
#define UART_MODE_TX_RX                     (USART_MODE_TX_RX)      /*!< RX and TX mode */
#define UART_MODE_HALF_DUPLEX               (0x20000300)            /*!< Single half duplex */
/**
  * @}
  */


/** @defgroup FIFO interrupt Config
  * @{
  */
#if 0  
#define UART_TX_FIFO_1_16             (0x00001400)        /*!< Transfer 1 Data  */
#define UART_TX_FIFO_1_8              (0x00000000)        /*!< Transfer 2 Data  */
#define UART_TX_FIFO_1_4              (0x00000400)        /*!< Transfer 4 Data  */
#define UART_TX_FIFO_1_2              (0x00000800)        /*!< Transfer 8 Data  */
#define UART_TX_FIFO_3_4              (0x00000C00)        /*!< Transfer 12 Data */
#define UART_TX_FIFO_7_8              (0x00001000)        /*!< Transfer 14 Data */

#define UART_RX_FIFO_1_16             (0x0000A000)        /*!< Receive  1 Data  */
#define UART_RX_FIFO_1_8              (0x00000000)        /*!< Receive  2 Data  */
#define UART_RX_FIFO_1_4              (0x00002000)        /*!< Receive  4 Data  */
#define UART_RX_FIFO_1_2              (0x00004000)        /*!< Receive  8 Data  */
#define UART_RX_FIFO_3_4              (0x00006000)        /*!< Receive  12 Data */
#define UART_RX_FIFO_7_8              (0x00008000)        /*!< Receive  14 Data */
#else
#define UART_TX_FIFO_1_16              (USART_TX_FIFO_1_16)
#define UART_TX_FIFO_1_8               (USART_TX_FIFO_1_8 )
#define UART_TX_FIFO_1_4               (USART_TX_FIFO_1_4 )
#define UART_TX_FIFO_1_2               (USART_TX_FIFO_1_2 )
#define UART_TX_FIFO_3_4               (USART_TX_FIFO_3_4 )
#define UART_TX_FIFO_7_8               (USART_TX_FIFO_7_8 )

#define UART_RX_FIFO_1_16              (USART_RX_FIFO_1_16)
#define UART_RX_FIFO_1_8               (USART_RX_FIFO_1_8 )
#define UART_RX_FIFO_1_4               (USART_RX_FIFO_1_4 )
#define UART_RX_FIFO_1_2               (USART_RX_FIFO_1_2 )
#define UART_RX_FIFO_3_4               (USART_RX_FIFO_3_4 )
#define UART_RX_FIFO_7_8               (USART_RX_FIFO_7_8 )
#endif
/**
  * @}
  */

/** @defgroup UART_Error_Code UART Error Code
  * @{
  */
#define HAL_UART_ERROR_NONE              0x00000000U   /*!< No error            */
#define HAL_UART_ERROR_PE                0x00000001U   /*!< Parity error        */
#define HAL_UART_ERROR_NE                0x00000002U   /*!< Noise error         */
#define HAL_UART_ERROR_FE                0x00000004U   /*!< Frame error         */
#define HAL_UART_ERROR_ORE               0x00000008U   /*!< Overrun error       */
#define HAL_UART_ERROR_DMA               0x00000010U   /*!< DMA transfer error  */
/**
  * @}
  */


/*
 * @brief UART Init Structure definition
 */
typedef struct
{
    uint32_t BaudRate;                  /*!< This member configures the UART communication baud rate. */

    uint32_t WordLength;                /*!< Specifies the number of data bits transmitted or received in a frame.
                                             This parameter can be a value of @ref UARTEx_Word_Length. */

    uint32_t StopBits;                  /*!< Specifies the number of stop bits transmitted.
                                             This parameter can be a value of @ref UART_Stop_Bits. */

    uint32_t Parity;                    /*!< Specifies the parity mode. 
                                             This parameter can be a value of @ref UART_Parity. */

    uint32_t Mode;                      /*!< Specifies whether the Receive or Transmit mode is enabled or disabled.
                                             This parameter can be a value of @ref UART_Mode. */

    uint32_t HwFlowCtl;                 /*!< Specifies whether the hardware flow control mode is enabled or disabled.
                                             This parameter can be a value of @ref UART_Hardware_Flow_Control. */

}UART_InitTypeDef;

/*
 * @brief  UART handle Structure definition
 */
typedef struct
{
    USART_TypeDef            *Instance;                /*!< UART registers base address        */

    UART_InitTypeDef         Init;                    /*!< UART communication parameters      */

    uint32_t                 TxSize;                  /*!< UART Transmit parameters in interrupt  */
    __IO uint32_t            TxCount;
    uint8_t                 *TxData;
    
    uint32_t                 RxSize;                  /*!< UART Receive parameters in interrupt  */
    __IO uint32_t            RxCount; 
    uint8_t                 *RxData;  
    
    
    __IO uint8_t             TxBusy;  
    __IO uint8_t             RxBusy;  
#ifdef HAL_DMA_MODULE_ENABLED    
    DMA_HandleTypeDef       *HDMA_Tx;                 /*!< UART Tx DMA handle parameters */
    DMA_HandleTypeDef       *HDMA_Rx;                 /*!< UART Rx DMA handle parameters */ 
#endif
	__IO uint32_t           ErrorCode;                /*!<UART Error Code */

}UART_HandleTypeDef;

/******************************************************************************
*@brief : RS485 DE Pin polarity enum
*         
*@note : 
******************************************************************************/
typedef enum
{
    RS485_DE_POLARITY_HIGH = 0,     /*!< RS485 DE Pin, High active*/
    RS485_DE_POLARITY_LOW,          /*!< RS485 DE Pin, Low active*/
    
}UART_RS485_DE_POL_Enum;

/******************************************************************************
*@brief : UART wake up method enum
*         
*@note : 
******************************************************************************/
typedef enum
{
    UART_WKUP_BY_IDLELINE = 0,      /*!< UART is waked up by idle line */
    UART_WKUP_BY_ADDR,              /*!< UART is waked up by address mark */
    
}UART_WakeupMode_Enum;


/******************************************************************************
*@brief : UART receive mode enum
*         
*@note : the enum is used in UART LOOP receive function: HAL_UART_Receive_To_Idle_BCNT
******************************************************************************/
typedef enum
{
    RECEIVE_TOIDLE,                 /*!< end of receiving data by idle line checked */
    RECEIVE_TOBCNT,                 /*!< end of receiving data by bit count value reached */
}UART_Receive_Mode_Enum;

/** @defgroup  GPIO Private Macros
  * @{
  */
#define IS_UART_ALL_INSTANCE(INSTANCE)    (((INSTANCE) == USART1) || \
                                            ((INSTANCE) == USART2) || \
                                            ((INSTANCE) == USART3) || \
                                           ((INSTANCE) == USART4) )  

#define IS_UART_HALFDUPLEX_INSTANCE(INSTANCE) (((INSTANCE) == USART1) || \
                                               ((INSTANCE) == USART2))

#define IS_RS485_INSTANCE(INSTANCE)       (((INSTANCE) == USART1) || \
                                           ((INSTANCE) == USART2) )  

#define IS_IRDA_INSTANCE(INSTANCE)        (((INSTANCE) == USART1) || \
                                           ((INSTANCE) == USART2) )

#define IS_SMARTCARD_INSTANCE(INSTANCE)   (((INSTANCE) == USART1) || \
                                           ((INSTANCE) == USART2) )
                                           
#define IS_UART_LIN_INSTANCE(INSTANCE)    (((INSTANCE) == USART1) || \
                                           ((INSTANCE) == USART2) )  

#define IS_UART_WORDLENGTH(__WORDLENGTH__)    (((__WORDLENGTH__) == UART_WORDLENGTH_5B) || \
                                               ((__WORDLENGTH__) == UART_WORDLENGTH_6B) || \
                                               ((__WORDLENGTH__) == UART_WORDLENGTH_7B) || \
                                               ((__WORDLENGTH__) == UART_WORDLENGTH_8B) || \
                                               ((__WORDLENGTH__) == UART_WORDLENGTH_9B))

#define IS_UART_STOPBITS(__STOPBITS__)    (((__STOPBITS__) == UART_STOPBITS_1) || \
                                           ((__STOPBITS__) == UART_STOPBITS_2))

#define IS_UART_PARITY(__PARITY__)        (((__PARITY__) == UART_PARITY_NONE) || \
                                           ((__PARITY__) == UART_PARITY_EVEN) || \
                                           ((__PARITY__) == UART_PARITY_ODD)  || \
                                           ((__PARITY__) == UART_PARITY_0)    || \
                                           ((__PARITY__) == UART_PARITY_1))

#define IS_UART_MODE(__MODE__)            (((__MODE__) == UART_MODE_RX)          || \
                                           ((__MODE__) == UART_MODE_TX)          || \
                                           ((__MODE__) == UART_MODE_TX_RX)       || \
                                           ((__MODE__) == UART_MODE_HALF_DUPLEX))
                                           
#define IS_UART_HARDWARE_FLOW_CONTROL(__CONTROL__)    (((__CONTROL__) == UART_HWCONTROL_NONE) || \
                                                       ((__CONTROL__) == UART_HWCONTROL_RTS)  || \
                                                       ((__CONTROL__) == UART_HWCONTROL_CTS)  || \
                                                       ((__CONTROL__) == UART_HWCONTROL_CTS_RTS))
                                                       
#define UART_7BIT_ADDR_MSK                  £¨0x80£©
#define IS_UART_7BIT_ADDR_MODE(addr)        ((addr & 0x80) == 0x80)
                                                       
                                                       
/** @brief  Enable UART
  * @param  __HANDLE__ specifies the UART Handle.
  * @retval None
  */
#define __HAL_UART_ENABLE(__HANDLE__)               ((__HANDLE__)->Instance->CR1 |=  UART_CR1_UARTEN)
/**
  * @}
  */

/** @brief  Disable UART
  * @param  __HANDLE__ specifies the UART Handle.
  * @retval None
  */
#define __HAL_UART_DISABLE(__HANDLE__)              ((__HANDLE__)->Instance->CR1 &=  ~UART_CR1_UARTEN)
/**
  * @}
  */


#define CLEAR_STATUS(reg, flag)     WRITE_REG(reg, flag)


#define __HAL_UART_TXI_FIFO_LEVEL_SET(uartx, fifo_level)      MODIFY_REG(uartx->CR3, UART_CR3_TXIFLSEL_Msk, fifo_level); 

#define __HAL_UART_RXI_FIFO_LEVEL_SET(uartx, fifo_level)      MODIFY_REG(uartx->CR3, UART_CR3_RXIFLSEL_Msk, fifo_level); 


/** @brief  Resume receiving data in IT mode.
  * @param  __HANDLE__ specifies the UART Handle.
  * @retval None
  * @note This macro is currently only used in idle call back function @HAL_UART_IdleCallback.
*/
#define __HAL_UART_Resume_Receive_IT(__HANDLE__) do {\
    (__HANDLE__)->RxBusy  = true;	\
    (__HANDLE__)->Instance->IE |= UART_IE_OEI | UART_IE_BEI | UART_IE_PEI | UART_IE_FEI | UART_IE_RXI | UART_IE_IDLEI;\
}while(0);  
/**
  * @}
  */  


/** @brief  Clear data in UART FIFO.
  * @param  __HANDLE__ specifies the UART Handle.
  * @retval None
  * @note __HAL_UART_FIFO_FLUSH will keep the UART FIFO in enabled state.
*/
#define __HAL_UART_FIFO_FLUSH(__HANDLE__)   do{\
    CLEAR_BIT((__HANDLE__)->Instance->CR3, UART_CR3_FEN); \
    SET_BIT((__HANDLE__)->Instance->CR3, UART_CR3_FEN);   \
}while(0);
/**
  * @}
  */  

void HAL_UART_IRQHandler(UART_HandleTypeDef *huart);

void HAL_UART_MspInit(UART_HandleTypeDef *huart);

HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_DeInit(UART_HandleTypeDef *huart);

HAL_StatusTypeDef HAL_UART_RS485_Init(UART_HandleTypeDef *huart, UART_RS485_DE_POL_Enum de_polarity, uint8_t deat_time, uint8_t dedt_time);

HAL_StatusTypeDef HAL_UART_IRDA_Init(UART_HandleTypeDef *huart, bool is_lowpwr);

HAL_StatusTypeDef HAL_UART_GetState(UART_HandleTypeDef *huart);

uint32_t HAL_UART_GetError(UART_HandleTypeDef *huart);

HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *buf, uint32_t size, uint32_t timeout);
HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *buf, uint32_t size, uint32_t timeout);
HAL_StatusTypeDef HAL_UART_Receive_To_IDLEorBCNT(UART_HandleTypeDef *huart, uint8_t *buf, uint32_t size, 
                                                UART_Receive_Mode_Enum rece_mode, uint32_t timeout);

HAL_StatusTypeDef HAL_UART_Transmit_IT(UART_HandleTypeDef *huart, uint8_t *buf, uint32_t size);
HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *buf, uint32_t size);

#ifdef HAL_DMA_MODULE_ENABLED
HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart, uint8_t *buf, uint32_t size);
HAL_StatusTypeDef HAL_UART_Receive_DMA(UART_HandleTypeDef *huart, uint8_t *buf, uint32_t size);
HAL_StatusTypeDef HAL_UART_Abort(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_DMAPause(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_DMAResume(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_DMAStop(UART_HandleTypeDef *huart);
#endif

HAL_StatusTypeDef HAL_UART_MultiProcessor_Init(UART_HandleTypeDef *huart, uint8_t addr, UART_WakeupMode_Enum wakeupMode);
HAL_StatusTypeDef HAL_UART_MultiProcessor_EnterMuteMode(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_MultiProcessor_ExitMuteMode(UART_HandleTypeDef *huart);

void HAL_UART_SetDebugUart(UART_TypeDef *UARTx);

#endif
