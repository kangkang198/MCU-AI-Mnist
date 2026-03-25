/******************************************************************************
*@file  : hal_ethmac.h
*@brief : Header file of RCC HAL module.
******************************************************************************/


#ifndef __HAL_ETH_H__
#define __HAL_ETH_H__

#include "acm32h5xx_hal_conf.h"


/** @defgroup ETH_Buffs_setting ETH Buffs setting
  * @{
  */ 
#define ETH_MAX_PACKET_SIZE       1536U    /*!< ETH_HEADER + ETH_EXTRA + ETH_VLAN_TAG + ETH_MAX_ETH_PAYLOAD + ETH_CRC */
#define ETH_HEADER                14U      /*!< 6 byte Dest addr, 6 byte Src addr, 2 byte length/type */
#define ETH_CRC                   4U       /*!< Ethernet CRC */
#define ETH_EXTRA                 2U       /*!< Extra bytes in some cases */   
#define ETH_VLAN_TAG              4U       /*!< optional 802.1q VLAN Tag */
#define ETH_MIN_ETH_PAYLOAD       46U      /*!< Minimum Ethernet payload size */
#define ETH_MAX_ETH_PAYLOAD       1500U    /*!< Maximum Ethernet payload size */
#define ETH_JUMBO_FRAME_PAYLOAD   9000U    /*!< Jumbo frame payload size */      


#define ETH_PTP_TIMEOUT             0xffffu
/** 
  * @brief  HAL State structures definition  
  */ 
typedef enum
{
    HAL_ETH_STATE_RESET             = 0x00U,    /*!< Peripheral not yet Initialized or disabled         */
    HAL_ETH_STATE_READY             = 0x01U,    /*!< Peripheral Initialized and ready for use           */
    HAL_ETH_STATE_BUSY              = 0x02U,    /*!< an internal process is ongoing                     */
    HAL_ETH_STATE_BUSY_TX           = 0x12U,    /*!< Data Transmission process is ongoing               */
    HAL_ETH_STATE_BUSY_RX           = 0x22U,    /*!< Data Reception process is ongoing                  */
    HAL_ETH_STATE_BUSY_TX_RX        = 0x32U,    /*!< Data Transmission and Reception process is ongoing */
    HAL_ETH_STATE_BUSY_WR           = 0x42U,    /*!< Write process is ongoing                           */
    HAL_ETH_STATE_BUSY_RD           = 0x82U,    /*!< Read process is ongoing                            */
    HAL_ETH_STATE_TIMEOUT           = 0x03U,    /*!< Timeout state                                      */
    HAL_ETH_STATE_ERROR             = 0x04U     /*!< Reception process is ongoing                       */
}HAL_ETH_StateTypeDef;

 /**
  * @}
  */

/** @defgroup ETH_Error_Code ETH Error Code
  * @{
  */ 
#define HAL_ETH_ERROR_NONE         ((uint32_t)0x00000000U)   /*!< No error            */
#define HAL_ETH_ERROR_PARAM        ((uint32_t)0x00000001U)   /*!< Busy error          */
#define HAL_ETH_ERROR_BUSY         ((uint32_t)0x00000002U)   /*!< Parameter error     */
#define HAL_ETH_ERROR_TIMEOUT      ((uint32_t)0x00000004U)   /*!< Timeout error       */
#define HAL_ETH_ERROR_DMA          ((uint32_t)0x00000008U)   /*!< DMA transfer error  */
#define HAL_ETH_ERROR_MAC          ((uint32_t)0x00000010U)   /*!< MAC transfer error  */

/**
  * @}
  */

typedef enum
{
    ETH_MEDIA_INTERFACE_MII = 0,                // MII
    ETH_MEDIA_INTERFACE_RMII                    // RMII
}ETH_MediaInterfaceTypeDef;

typedef enum
{
    ETH_SPEED_100M = 0,                         // 100M
    ETH_SPEED_10M                               // 10M
}ETH_SpeedTypeDef;

typedef enum
{
    ETH_MODE_FULL_DUPLEX = 0,                   // 全双工
    ETH_MODE_HALF_DUPLEX                        // 半双工
}ETH_ModeTypeDef;

typedef enum
{
    ETH_DESC_LIST_MODE_RING = 0,                // 环形结构
    ETH_DESC_LIST_MODE_LIST                     // 链接结构
}ETH_DescListModeTypeDef;

#define ETH_TX_MODE_DATA_COPY               BIT0
#define ETH_TX_MODE_TIMESTAMP               BIT1
#define ETH_TX_MODE_WAIT_TX_COMPLETE        BIT2

/** 
  * 
  */

typedef struct __ETH_BufferTypeDef
{
  uint8_t *Buff;
  uint32_t Len;
  struct __ETH_BufferTypeDef *next;
} __attribute__((aligned(4))) ETH_BuffTypeDef;

/** 
  * @brief  ETH DMA Descriptors data structure definition
  */ 

typedef struct  
{
    __IO uint32_t   DESC0;
    __IO uint32_t   DESC1;
    __IO uint32_t   DESC2;
    __IO uint32_t   DESC3;
    __IO uint32_t   DESC4;
    __IO uint32_t   DESC5;
    __IO uint32_t   DESC6;
    __IO uint32_t   DESC7;
    __IO uint32_t   Buff1;
    __IO uint32_t   Buff2;
} __attribute__((aligned(4))) ETH_DMADescTypeDef;


/** 
  * @brief  DMA Transmit Descriptors Wrapper structure definition
  */
typedef struct
{
    ETH_DMADescTypeDef  *TxDescTab;  /*<! Tx DMA descriptors addresses */
  
    uint8_t             CurTxDesc;                /*<! Current Tx descriptor index for packet transmission */
    uint8_t             Rsv1[3];
    
} __attribute__((aligned(4))) ETH_TxDescListTypeDef;
/** 
  * 
  */
/** 
 * @brief  DMA Receive Descriptors Wrapper structure definition
 */
typedef struct
{
    ETH_DMADescTypeDef      *RxDescTab;   /*<! Rx DMA descriptors addresses. */
    
    uint8_t                 CurRxDesc;                 /*<! Current Rx descriptor, ready for next reception. */
    uint8_t                 FirstRxDesc;              /*<! First descriptor of last received packet. */
    uint8_t                 RxDescNbr;                /*<! Number of descriptors of last received packet. */
    uint8_t                 Rsv1;
    
} __attribute__((aligned(4))) ETH_RxDescListTypeDef;

typedef struct
{
    uint32_t                sec;                   // 时间戳高位为秒
    uint32_t                nsec;                  // 时间戳低位为纳秒
} __attribute__((aligned(4))) ETH_TimestampTypeDef;

typedef struct
{
    uint8_t                 AutoCRC;            // 自动将CRC附加到发送帧的尾部
    uint8_t                 AutoPad;            // 自动为不足64字节的帧添加补位项和CRC
    uint8_t                 AutoChecksum;       // 校验和插入控制
    uint8_t                 Rsv1;               // 
} __attribute__((aligned(4))) ETH_TxConfigTypeDef;

typedef struct
{
    uint8_t                 TimestampValid;     // 
    uint8_t                 Rsv1[3];
    uint32_t                Status0;            // 
    ETH_TimestampTypeDef    Timestamp;          // 时间戳
} __attribute__((aligned(4))) ETH_TxStatusTypeDef;

typedef struct
{
    uint8_t                 TimestampValid;     // 
    uint8_t                 Rsv1[3];
    uint32_t                Status0;            // 
    uint32_t                Status4;            // 
    ETH_TimestampTypeDef    Timestamp;          // 时间戳使能
} __attribute__((aligned(4))) ETH_RxStatusTypeDef;

/** 
  * 
  */
#define ETH_DLYB_CLOCK_SOURCE_HCLK          0
#define ETH_DLYB_CLOCK_SOURCE_PHY_RX        1

typedef struct
{
    uint32_t ClockSource;
    uint32_t Delayns;
    
    uint32_t Uint;
    uint32_t Len;
    
}ETH_DelayTypeDef;

/** 
  * @brief  ETH Init Structure definition  
  */

typedef struct
{
    uint8_t                         MACAddr[6];                  /*!< MAC Address of used Hardware: must be pointer on an array of 6 bytes */
    uint16_t                        MediaInterface;            /*!< Selects the MII interface or the RMII interface. */
    uint32_t                        AutoNegotiation;
    uint32_t                        Speed;
    uint32_t                        DuplexMode;
    uint16_t                         PhyAddress;
    uint16_t                         Delayns;
    
    uint8_t                         *TxBuff;                    // TxBuff必须连续
    uint16_t                        TxBuffNbr;
    uint16_t                        TxBuffLen;
    
    uint8_t                         *RxBuff;                    // RxBuff必须连续，必须有效
    uint16_t                        RxBuffNbr;
    uint16_t                        RxBuffLen;                 /*!< Provides the len of Rx buffs size */
    
    ETH_DMADescTypeDef              *TxDesc;                   /*!< Provides the address of the first DMA Tx descriptor in the list */
    ETH_DMADescTypeDef              *RxDesc;                   /*!< Provides the address of the first DMA Rx descriptor in the list */
    uint16_t                         TxDescNbr;
    uint16_t                         RxDescNbr;
    ETH_DescListModeTypeDef         TxDescListMode;
    ETH_DescListModeTypeDef         RxDescListMode;
    
    ETH_BuffTypeDef                 *TxBuffTab;
    ETH_BuffTypeDef                 *RxBuffTab;
    uint16_t                        TxBuffNodeNbr;
    uint16_t                        RxBuffNodeNbr;
    
    ETH_DelayTypeDef                Delay;
    
} __attribute__((aligned(4))) ETH_InitTypeDef;

/** 
 * @brief  DMA Receive Descriptors Wrapper structure definition
 */
typedef struct
{
    uint8_t     Tx;
    uint8_t     Rx;
    
    uint8_t     Rsv1[2];
    
} __attribute__((aligned(4))) ETH_IntTypeDef;



/** 
 * @brief  
 */
typedef struct
{
    uint8_t Enable;                         // 使能
    uint8_t GroupFilter;                    // 组过滤；     ENABLE：组过滤； DISABLE：完美过滤；
    uint8_t PerfectSourAddr;                // 完美过滤；    ENABLE：目标地址；    DISABLE：源地址；
    uint8_t GroupMask;                      // 组过滤；     屏蔽字节   bit0-5：屏蔽地址0-5
    uint8_t Addr[6];
    uint8_t Rsv[2];
} __attribute__((aligned(4))) ETH_MACAddrTypeDef;

/** 
  * 
  */
    
/** 
 * @brief  
 */
typedef struct
{
    ETH_MACAddrTypeDef Addr[3];         // 
    
    uint8_t ReceiveAll;                 //	接收所有MAC帧
                                        //	有效值：		使能：	ENABLE
                                        //				禁止：	DISABLE
                                        //	接收所有MAC帧，可选使能或禁用，它设定以太网MAC帧过滤寄存器(ETH_MACFFR)RA位的值。当设置为1时，MAC接收器将所有接收的帧传送到应用程序，不过滤地址。当设置为0是，MAC接收会自动过滤不与SA/DA匹配的帧。一般选择不接收所有。
													
    uint8_t HashPerfectFilter;          //	散列或完美过滤器  Hash  或者  Perfect or Hash
                                        //	有效值：		使能：	ENABLE
                                        //				禁止：	DISABLE
															
    uint8_t SourceAddrFilter;           //	源地址过滤
                                        //	有效值：		ENABLE
                                        //				DISABLE
													
    uint8_t SourceAddrInverseFilter;    //	源地址反向过滤
                                        //	有效值：		ENABLE
                                        //				DISABLE
													
    uint8_t PassControlPackets;         //	传送控制帧
                                        //	有效值：		ETH_PASS_CONTROL_BLOCK_ALL
                                        //				ETH_PASS_CONTROL_FORWARD_ALL_EXCEPT_PAUSE_FRAME
                                        //				ETH_PASS_CONTROL_FORWARD_ALL
                                        //				ETH_PASS_CONTROL_FORWARD_PASSED_ADDR_FILTER
                                        //	传送控制帧，控制所有控制帧的转发，可选阻止所有控制帧到达应用程序、转发所有控制帧、转发通过地址过滤的控制帧，它设定ETH_MACFFR寄存器PCF位的值。一般选择禁止转发控制帧。
													
    uint8_t BroadcastFramesReception;   //	广播帧接收
                                        //	有效值：		使能：	ENABLE
                                        //				禁止：	DISABLE
                                        //	广播帧接收，可选使能或禁止，它设定ETH_MACFFR寄存器BFD位的值。当设置为0时，使能广播帧接收，一般设置接收广播帧。
													
    uint8_t PassAllMulticast;           //	通过所有多播
                                        //	有效值：		ENABLE
                                        //				DISABLE
                                        //	通过所有多播，禁止时，多播数据包的过滤取决于 HMC 位。使能时，指示通过接收到的带多播目标地址（目标地址字段的第一位是“1”）的所有数据包。

    uint8_t DestAddrInverseFilter;      //	目标地址反向过滤
                                        //	有效值：		ENABLE
                                        //				DISABLE
                                        //	目标地址过滤功能选择，可选正常过滤或目标地址反向过滤，它设定ETH_MACFFR寄存器DAIF位的值。一般设置为正常过滤。
													
    uint8_t HushMulticastFramesFilter;  //	散列多播地址过滤
                                        //	有效值：		ENABLE
                                        //				DISABLE
                                        //	多播地址过滤，MAC 根据散列表对接收到的多播数据包执行目标地址过滤
													
    uint8_t HashUnicastFramesFilter;    //	单播地址过滤
                                        //	有效值：		ENABLE
                                        //				DISABLE
                                        //	单播地址过滤，MAC 根据散列表对单播数据包执行目标地址过滤。
															
    uint8_t PromiscuousMode;            //	混合模式
                                        //	有效值：		使能：	ENABLE
                                        //				禁止：	DISABLE
                                        //	混合模式，可选使能或禁用，它设定ETH_MACFFR寄存器PM位的值。当设置为1时，不论目标或源地址，地址过滤器都传送所有传入的帧。一般禁用混合模式。

    uint8_t Rsv1[1];                    // 保留
    
    uint32_t HashTable[2];              //	散列表
                                        //	有效值：		0 - 0xFFFFFFFFFFFFFFFFU
                                        //	散列表，64位散列表，用于组地址过滤，它设定以太网MAC散列表高位寄存器(ETH_MACHTHR)的值。
													
} __attribute__((aligned(4))) ETH_AddrFilterTypeDef;

/** 
  * 
  */

/** 
 * @brief  
 */
typedef struct
{
    uint8_t Enable;                     //	VLAN 标记过滤器使能
                                        //	有效值：		使能：	ENABLE
                                        //				禁止：	DISABLE
    
    uint8_t Hash;                       //	VLAN标志散列表匹配使能
                                        //	有效值：		ENABLE
                                        //				DISABLE
                                        //	VLAN 标记反向匹配使能。使能VLAN 标记完美匹配。含有匹配 VLAN 标记的数据包被标记为匹配。  使能VLAN 标记反向匹配。不含匹配 VLAN 标记的数据包被标记为匹配。

    uint8_t SVLAN;                      //	S-VLAN 使能
                                        //	有效值：		ENABLE
                                        //				DISABLE
                                        //	VLAN 标记反向匹配使能。使能VLAN 标记完美匹配。含有匹配 VLAN 标记的数据包被标记为匹配。  使能VLAN 标记反向匹配。不含匹配 VLAN 标记的数据包被标记为匹配。

    uint8_t InverseMatch;               //	VLAN 标记反向匹配使能
                                        //	有效值：		ENABLE
                                        //				DISABLE													
                                        //	VLAN 标记反向匹配使能。使能VLAN 标记完美匹配。含有匹配 VLAN 标记的数据包被标记为匹配。  使能VLAN 标记反向匹配。不含匹配 VLAN 标记的数据包被标记为匹配。

    uint8_t Comparison12Bits;           //	12位VLAN标记比较
                                        //	有效值：		ENABLE
                                        //				DISABLE
                                        //	VLAN标记比较，可选12位或16位，它设定以太网MAC VLAN标记寄存器(ETH_MACVLANTR)VLANTC位的值。当设置为1时，使用12位VLAN标识符而不是完整的16位VLAN标记进行比较和过滤；为0时，使用全部16位进行比较，一般选择16位。

    uint8_t Rsv1[3];
    
    uint16_t Tag;                       //	VLAN标记标识符
                                        //	有效值：		0 - 0xFFFFUL
                                        //	VLAN标记标识符，包含用于标识VLAN帧的802.1Q VLAN标记，并与正在接收的VLAN帧的第十五和第十六字节进行比较。位[15:13]是用户优先级，位[12]是标准格式指示符(CFI)，位[11:0]是VLAN标记的VLAN标识符(VID)字段。VLANTC位置1时，仅使用VID（位[11:0]）进行比较。

    uint16_t HashTable;                 //	散列表
    
} __attribute__((aligned(4))) ETH_VLANFilterTypeDef;

/** 
  * 
  */  
                  
/** 
 * @brief  
 */
typedef struct
{
    uint8_t ProtocolIPV6;               //  第3层 协议使能
                                        //	有效值：		使能： ENABLE      IPV6
                                        //				禁止： DISABLE     IPV4
    union
    {
        struct
        {
            uint8_t SourAddrMatchEnable;        //  第3层 IP源地址 匹配使能
                                                //	有效值：		IPV4：  0 - 31
                                                //				IPB6：  0-127
            
            uint8_t SourAddrInverseMatch;       //  第3层 IP源地址 反向匹配使能
                                                //	有效值：		IPV4：  0 - 31
                                                //				IPB6：  0-127
            
            uint8_t SourAddrMatch;              //  第3层 IP源地址 高位匹配
                                                //	有效值：		bit0-bit31 复位、置位
                                                
            uint8_t DestAddrMatchEnable;        //  第3层 IP目标地址 匹配使能
                                                //	有效值：		IPV4：  0 - 31
                                                //				IPB6：  0-127
            
            uint8_t DestAddrInverseMatch;       //  第3层 IP目标地址 反向匹配使能
                                                //	有效值：		IPV4：  0 - 31
                                                //				IPB6：  0-127
            
            uint8_t DestAddrMatch;              //  第3层 IP目标地址 高位匹配
                                                //	有效值：		bit0-bit31 复位、置位
                                                
            uint8_t Rsv1[2];                    //  
                                                
            uint32_t SourAddr;                  //  第3层 IP源端口号
            
            uint32_t DestAddr;                  //  第3层 IP目标端口号
                                                
            uint32_t Rsv2[2];                    //  
            
        }IPV4;
        
        struct
        {
            uint8_t SourAddrMatchEnable;        //  第3层 IP源地址 匹配使能
                                                //	有效值：		IPV4：  0 - 31
                                                //				IPB6：  0-127
            
            uint8_t SourAddrInverseMatch;       //  第3层 IP源地址 反向匹配使能
                                                //	有效值：		IPV4：  0 - 31
                                                //				IPB6：  0-127
            
            uint8_t DestAddrMatchEnable;        //  第3层 IP目标地址 匹配使能
                                                //	有效值：		IPV4：  0 - 31
                                                //				IPB6：  0-127
            
            uint8_t DestAddrInverseMatch;       //  第3层 IP目标地址 反向匹配使能
                                                //	有效值：		IPV4：  0 - 31
                                                //				IPB6：  0-127
            
            uint8_t AddrMatch;                  //  第3层 IP目标地址 高位匹配
                                                //	有效值：		bit0-bit127 复位、置位
                                                
            uint8_t Rsv1[3];                    //  
                                                
            uint32_t Addr[4];                   //  第3层 源端口号或目标端口号
            
        }IPV6;
    };
    
} __attribute__((aligned(4))) ETH_L3FilterTypeDef;

/** 
  * 
  */

/** 
 * @brief  
 */
typedef struct
{
    uint8_t ProtocolUDP;                //  第4层 协议使能
                                        //	有效值：		使能：	ENABLE      UDP
                                        //				禁止：	DISABLE     TCP
    
    uint8_t SourPortMatchEnable;        //  第4层 源端口匹配使能
                                        //	有效值：		使能：	ENABLE
                                        //				禁止：	DISABLE
    
    uint8_t SourPortInverseMatch;       //  第4层 源端口反向匹配使能
                                        //	有效值：		使能：	ENABLE
                                        //				禁止：	DISABLE
    
    uint8_t DestPortMatchEnable;        //  第4层 目标端口匹配使能
                                        //	有效值：		使能：	ENABLE
                                        //				禁止：	DISABLE
    
    uint8_t DestPortInverseMatch;       //  第4层 目标端口反向匹配使能
                                        //	有效值：		使能：	ENABLE
                                        //				禁止：	DISABLE
    
    uint8_t Rsv[3];                     //  
    
    uint16_t SourPort;                  //  第4层 源端口号
    
    uint16_t DestPort;                  //  第4层 目标端口号
    
} __attribute__((aligned(4))) ETH_L4FilterTypeDef;

/** 
  * 
  */

/** 
 * @brief  
 */
typedef struct
{
    uint8_t Enable;
    uint8_t Rsv[3];
    ETH_L3FilterTypeDef L3[2];
    ETH_L4FilterTypeDef L4[2];
} __attribute__((aligned(4))) ETH_L3L4FilterTypeDef;

/** 
  * 
  */
/** 
 * @brief  
 */
typedef struct
{
    ETH_AddrFilterTypeDef           Addr;
    
    ETH_VLANFilterTypeDef           VLAN;
    
    ETH_L3L4FilterTypeDef           L3L4;
    
    uint8_t DropNonTCPUDP;              //	丢弃IP帧上非TCP/UDP帧
                                        //	有效值：		使能：	ENABLE
                                        //				禁止：	DISABLE
    uint8_t Rsv1[3];
} __attribute__((aligned(4))) ETH_FilterTypeDef;

/** 
  * 
  */



/** 
 * @brief  
 */
typedef struct
{
    uint8_t Enable;
    uint8_t Rsv1[1];
    uint16_t Timeout;
} __attribute__((aligned(4))) ETH_WatchTypeDef;

/** 
  * 
  */

/** 
 * @brief  
 */
typedef struct
{                               
    uint8_t Enable;                   // VLAN优先级控制
    
    uint8_t Mode;                       // VLAN优先级控制
    
    uint8_t SVLAN;                       // 插入或替换 S-VLAN/C-VLAN
    
    uint8_t Rsv1;
    
    uint16_t Tag;                       //	VLAN标记标识符
    
    uint8_t Rsv2[2];
    
} __attribute__((aligned(4))) ETH_VLANTypeDef;
/** 
  * 
  */

 /** 
  * @brief  ETH MAC Configuration Structure definition  
  */

typedef struct
{
  uint32_t				SourceAddrControl;					//	源地址插入或替换控制
															//	ETH_SOURCE_ADDRESS_DISABLE
															//	ETH_SOURCE_ADDRESS_INSERT_ADDR0
															//	ETH_SOURCE_ADDRESS_INSERT_ADDR1
															//	ETH_SOURCE_ADDRESS_REPLACE_ADDR0
															//	ETH_SOURCE_ADDRESS_REPLACE_ADDR1
	
	
  uint32_t				Support2KPacket;					//	2K数据包的IEEE 802.3as 支持
															//	使能：	ENABLE
															//	禁止：	DISABLE

  uint32_t				CRCStripTypePacket;					//	类型帧的 CRC 去除
															//	使能：	ENABLE
															//	禁止：	DISABLE


  uint32_t             Watchdog;							//	名称：	MAC接收看门狗
															//	
															//	选项：	使能：	ENABLE			使能看门狗，接收超过2K字节的帧会被切断。
															//			禁止：	DISABLE		禁止看门狗，接收超过16K字节的帧会被切断。
															//	
															//	说明：	以太网看门狗功能选择，可选使能或禁止，它设定以太网MAC配置寄存器(ETH_MACCR)的WD位的值。
															//			如果设置为1，使能看门狗，在接收MAC帧超过2048字节时自动切断后面数据，一般选择使能看门狗。
															//			如果设置为0，禁用看门狗，最长可接收16384字节的帧。
  uint32_t              WatchdogTimeout;


  uint32_t             Jabber;								//	名称：	发送Jabber定时器
															//	选项：	使能：	ENABLE			使能定时器，发送超过2K字节的帧会被切断。
															//			禁止：	DISABLE			禁止定时器，发送超过16K字节的帧会被切断。
															//	
															//	说明：	jabber定时器功能选择，可选使能或禁止，与看门狗功能类似，只是看门狗用于接收MAC帧，jabber定时器用于发送MAC帧，它设定ETH_MACCR寄存器的JD位的值。
															//			如果设置为1，使能jabber定时器，在发送MAC帧超过2048字节时自动切断后面数据，一般选择使能jabber定时器。
	
  uint32_t             JumboPacket;							//	名称：	巨型数据包使能
															//	选项：	使能：	ENABLE			使能定时器，发送超过2K字节的帧会被切断。
															//			禁止：	DISABLE		禁止定时器，发送超过16K字节的帧会被切断。
															//	
															//	说明：	巨型数据包使能。使能，MAC 允许 9,018 字节的巨型数据包（对于带 VLAN 标记的数据包，为 9,022 字节），且不会在 Rx 数据包状态中报告大型数据包错误。
	
	
  uint32_t              InterFrameGap;						//	发送帧间间隔
															//	40bit - 96bit，半双工最小配置为64bit
															//	ETH_INTERFRAME_GAP_96BIT
															//	ETH_INTERFRAME_GAP_88BIT
															//	ETH_INTERFRAME_GAP_80BIT
															//	ETH_INTERFRAME_GAP_72BIT
															//	ETH_INTERFRAME_GAP_64BIT
															//	ETH_INTERFRAME_GAP_56BIT
															//	ETH_INTERFRAME_GAP_48BIT
															//	ETH_INTERFRAME_GAP_40BIT
													
															//	控制发送帧间的最小间隙，可选96bit时间、88bit时间、…、40bit时间，他设定ETH_MACCR寄存器的IFG[2:0]位的值，一般设置96bit时间。

  uint32_t             CarrierSense;						//	载波侦听
															//	使能：	ENABLE
															//	禁止：	DISABLE
													
															//	载波侦听功能选择，可选使能或禁止，它设定ETH_MACCR寄存器的CSD位的值。当被设置为低电平时，MAC发送器会生成载波侦听错误，一般使能载波侦听功能。
													
//  uint32_t             Speed;								//	速度
															//	10Mbps：	ETH_SPEED_10M
															//	100Mbps：	ETH_SPEED_100M
															//	以太网速度选择，可选10Mbps或100Mbit/s，它设定ETH_MACCR寄存器的FES位的值，一般设置100Mbit/s，但在使能自适应功能之后该位设置无效。
	
  uint32_t             ReceiveOwn;							//	接收自身		MAC接收发送时PHY提供的包		仅适用于半双工
															//	使能：	ENABLE
															//	禁止：	DISABLE
													
															//	接收自身帧功能选择，可选使能或禁止，它设定ETH_MACCR寄存器的ROD位的值，当设置为0时，MAC接收发送时PHY提供的所有MAC包，如果设置为1，MAC禁止在半双工模式下接收帧。一般使能接收。
												
  uint32_t             LoopbackMode;						//	回送模式		对发送到其接收器的帧进行回送
															//	使能：	ENABLE
															//	禁止：	DISABLE
													
//  uint32_t             Mode;								//	全双工模式
															//	半双工：		ETH_MODE_HALF_DUPLEX
															//	全双工：		ETH_MODE_FULL_DUPLEX
	
  uint32_t             ChecksumOffload;						//	校验和减荷	使能接收帧 TCP/UDP/ICMP 标头的 IPv4 校验和检查	TCP/UDP/ICMP
															//	使能：	ENABLE
															//	禁止：	DISABLE
													
															//	IPv4校验和减荷功能选择，可选使能或禁止，它设定ETH_MACCR寄存器IPCO位的值，当该位被置1时使能接收的帧有效载荷的TCP/UDP/ICMP标头的IPv4校验和检查。一般选择禁用，此时PCE和IP HCE状态位总是为0。

  uint32_t             RetryTransmission;					//	传输重试
															//	使能：	ENABLE
															//	禁止：	DISABLE
													
															//	传输重试功能，可选使能或禁止，它设定ETH_MACCR寄存器RD位的值，当被设置为1时，MAC仅尝试发送一次，设置为0时，MAC会尝试根据BL的设置进行重试。一般选择使能重试。
													
  uint32_t             AutoPadCRCStrip;				        //	自动去除PAD和FCS字段
															//	
															//	有效值：		使能：	ENABLE
															//				禁止：	DISABLE
													
															//	自动去除PAD和FCS字段功能，可选使能或禁用，它设定ETH_MACCR寄存器APCS位的值。当设置为1时，MAC在长度字段值小于或等于1500自己是去除传入帧上的PAD和FCS字段。一般禁止自动去除PAD和FCS字段功能。
													
  uint32_t             BackOffLimit;						//	后退限制
															//	
															//	有效值：		ETH_BACK_OFF_LIMIT_10
															//				ETH_BACK_OFF_LIMIT_8
															//				ETH_BACK_OFF_LIMIT_4
															//				ETH_BACK_OFF_LIMIT_1
															//	后退限制，在发送冲突后重新安排发送的延迟时间，可选10、8、4、1，它设定ETH_MACCR寄存器BL位的值。一般设置为10。
													
  uint32_t             DeferralCheck;						//	检查延迟
															//	
															//	有效值：		使能：	ENABLE
															//				禁止：	DISABLE
													
															//	检查延迟，可选使能或禁止，它设定ETH_MACCR寄存器DC位的值，当设置为0时，禁止延迟检查功能，MAC发送延迟，直到CRS信号变成无效信号。
													
  uint32_t             PreambleLen;							//	发送数据包的报头长度
															//	
															//	有效值：		ETH_PREAMBLE_LEN_7B
															//				ETH_PREAMBLE_LEN_5B
															//				ETH_PREAMBLE_LEN_3B
															
															//	这些位控制被添加到每个 Tx 数据包的开头的报头字节数。仅当 MAC 工作在全双工模式下时，才可缩短报头。
													
  ETH_WatchTypeDef     WatchDog;                            //看门狗
  
    ETH_VLANTypeDef     VLAN;
} __attribute__((aligned(4))) ETH_MACInitTypeDef;

/** 
  * @brief  ETH DMA Configuration Structure definition  
  */

typedef struct
{
   uint32_t			   DropTCPIPChecksumErrorFrame;			//	丢弃TCP/IP校验错误帧
															//	使能：	ENABLE
															//	禁止：	DISABLE
	
															//	说明：	丢弃TCP/IP校验错误帧，可选使能或禁止，它设定以太网DMA工作模式寄存器(ETH_DMAOMR)DTCEFD位的值，当设置为 1时，如果帧中仅存在由接收校验和减荷引擎检测出来的错误，则内核不会丢弃它；为0时，如果FEF为进行了复位，则会丢弃所有错误帧。
	
  uint32_t             ReceiveStoreForward;					//	接收存储并转发
															//	使能：	ENABLE
															//	禁止：	DISABLE
	
															//	说明：	接收存储并转发，可选使能或禁止，它设定以太网DMA工作模式寄存器(ETH_DMAOMR)RSF位的值，当设置为1时，向RX FIFO写入完整帧后可以从中读取一帧，同时忽略接收阈值控制(RTC)位；当设置为0时，RX FIFO在直通模式下工作，取决于RTC位的阈值。一般选择使能。
	
  uint32_t             FlushReceivedFrame;			        //	刷新接收帧
															//	使能：	ENABLE
															//	禁止：	DISABLE
	
															//	说明：	禁止刷新接收帧，可选使能或禁止，它设定ETH_DMAOMR寄存器FTF位的值。
	
  uint32_t             TransmitStoreForward;				//	发送存储并并转发
															//	使能：	ENABLE
															//	禁止：	DISABLE
	
															//	说明：	发送存储并并转发，可选使能或禁止，它设定ETH_DMAOMR寄存器TSF位的值，当设置为1时，如果TX FIFO有一个完整的帧则发送会启动，会忽略TTC值；为0时，TTC值才会有效。一般选择使能。
															
  uint32_t             TransmitThresholdControl;			//	发送阈值控制
															//	ETH_TRANSMIT_THRESHOLD_CONTROL_64BYTES
															//	ETH_TRANSMIT_THRESHOLD_CONTROL_128BYTES
															//	ETH_TRANSMIT_THRESHOLD_CONTROL_192BYTES
															//	ETH_TRANSMIT_THRESHOLD_CONTROL_256BYTES
															//	ETH_TRANSMIT_THRESHOLD_CONTROL_40BYTES
															//	ETH_TRANSMIT_THRESHOLD_CONTROL_32BYTES
															//	ETH_TRANSMIT_THRESHOLD_CONTROL_24BYTES
															//	ETH_TRANSMIT_THRESHOLD_CONTROL_16BYTES
	
															//	说明：	发送阈值控制，有多个阈值可选，它设定ETH_DMAOMR寄存器TTC位的值，当TX FIFO中帧大小大于该阈值时发送会自动，对于小于阈值的全帧也会发送。
															
  uint32_t             ForwardErrorFrames;					//	转发错误帧
															//	使能：	ENABLE
															//	禁止：	DISABLE
	
															//	说明：	转发错误帧，可选使能或禁止，它设定ETH_DMAOMR寄存器FEF位的值，当设置为1时，除了段错误帧之外所有帧都会转发到DMA；为0时，RX FIFO会丢弃滴啊有错误状态的帧。一般选择禁止。
															
  uint32_t             ForwardUndersizedGoodFrames;			//	转发过小的好帧
															//	使能：	ENABLE
															//	禁止：	DISABLE
	
															//	说明：	转发过小的好帧，可选使能或禁止，它设定ETH_DMAOMR寄存器FUGF位的值，当设置为1时，RX FIFO会转发包括PAD和FCS字段的过小帧；为0时，会丢弃小于64字节的帧，除非接收阈值被设置为更低。
															
  uint32_t             ReceiveThresholdControl;				//	接收阈值控制
															//	ETH_RECEIVED_THRESHOLD_CONTROL_64BYTES
															//	ETH_RECEIVED_THRESHOLD_CONTROL_32BYTES
															//	ETH_RECEIVED_THRESHOLD_CONTROL_96BYTES
															//	ETH_RECEIVED_THRESHOLD_CONTROL_128BYTES
	
															//	说明：	接收阈值控制，当RX FIFO中的帧大小大于阈值时启动DMA传输请求，可选64字节、32字节、96字节或128字节，它设定ETH_DMAOMR寄存器RTC位的值。
															
  uint32_t             SecondFrameOperate;					//	处理第二个帧
															//	使能：	ENABLE
															//	禁止：	DISABLE
	
															//	说明：	处理第二个帧，可选使能或禁止，它设定ETH_DMAOMR寄存器OSF位的值，当设置为1时会命令DMA处理第二个发送数据帧。
															
  uint32_t             MixedBurst;							//	混合突发
															//	使能：	ENABLE
															//	禁止：	DISABLE
	
															//	说明：	该位置为高电平且 FB 位置为低电平时， AHB 主接口将以 INCR（未定义突发）启动所有长度大于 16 的突发传输。该位清零时，对于长度等于或小于 16 的突发，将恢复为固定突发传输（ INCRx 和 SINGLE）。
															
															
  uint32_t             AddressAlignedBeats;					//	地址对齐节拍
															//	使能：	ENABLE
															//	禁止：	DISABLE
	
															//	说明：	地址对齐节拍，可选使能或禁止，它设定以太网DMA总线模式寄存器(ETH_DMABMR)AAB位的值，当设置为1并且固定突发位(FB)也为1时，AHB接口会生成与起始地址LS位对齐的所有突发；如果FB位为0，则第一个突发不对齐，但后续的突发与地址对齐。一般选择使能。
															
  uint32_t             PBL8xMode;							//	8xPBL 模式
															//	使能：	ENABLE
															//	禁止：	DISABLE
	
															//	说明：	当设置为高电平时，该位会将编程的 PBL 值（位 [22:17] 和位 [13:8]）乘以八倍。因此，DMA 根据 PBL 值以最大 8、 16、 32、 64 、128 和256个节拍传输数据。
															
  uint32_t             UseSeparatePBL;						//	使用单独的 PBL
															//	使能：	ENABLE
															//	禁止：	DISABLE
	
															//	说明：	设置为高电平时，它会配置 RxDMA，将位 [22:17] 中配置的值用作 PBL，而位 [13:8] 中的PBL 值仅适用于 TxDMA 操作。当该位清零时，位 [13:8] 中的 PBL 值同时适用于两个 DMA引擎。
															
  uint32_t             RxDMABurstLen;					//	DMA突发接收长度
															//	ETH_RX_DMA_BURST_LEN_1BEAT
															//	ETH_RX_DMA_BURST_LEN_2BEAT
															//	ETH_RX_DMA_BURST_LEN_4BEAT
															//	ETH_RX_DMA_BURST_LEN_8BEAT
															//	ETH_RX_DMA_BURST_LEN_16BEAT
															//	ETH_RX_DMA_BURST_LEN_32BEAT
	
															//	说明：	DMA突发接收长度，有多个值可选，一般选择32Beat，可实现32*32bits突发长度，它设定ETH_DMABMR寄存器FPM位和RDP位的值。
															
  uint32_t             FixedBurst;							//	固定突发
															//	使能：	ENABLE
															//	禁止：	DISABLE
	
															//	说明：	固定突发，控制AHB主接口是否执行固定突发传输，可选使能或禁止，它设定ETH_DMABMR寄存器FB位的值，当设置为1时，AHB在正常突发传输开始期间使用SINGLE、INCR4、INCR8或INCR16；为0时，AHB使用SINGLE和INCR突发传输操作。
															
  uint32_t             RxTxPriorityRatio;					//	Rx Tx 优先级比
															//	
															//	ETH_RX_TX_PRIORITY_RATIO_1_1
															//	ETH_RX_TX_PRIORITY_RATIO_2_1
															//	ETH_RX_TX_PRIORITY_RATIO_3_1
															//	ETH_RX_TX_PRIORITY_RATIO_4_1
															//	
	
															//	说明：	固定突发，控制AHB主接口是否执行固定突发传输，可选使能或禁止，它设定ETH_DMABMR寄存器FB位的值，当设置为1时，AHB在正常突发传输开始期间使用SINGLE、INCR4、INCR8或INCR16；为0时，AHB使用SINGLE和INCR突发传输操作。
															
  uint32_t             TxDMABurstLen;					//	DMA突发发送长度
															//	ETH_TX_DMA_BURST_LEN_1BEAT
															//	ETH_TX_DMA_BURST_LEN_2BEAT
															//	ETH_TX_DMA_BURST_LEN_4BEAT
															//	ETH_TX_DMA_BURST_LEN_8BEAT
															//	ETH_TX_DMA_BURST_LEN_16BEAT
															//	ETH_TX_DMA_BURST_LEN_32BEAT
	
															//	说明：	DMA突发发送长度，有多个值可选，一般选择32Beat，可实现32*32bits突发长度，它设定ETH_DMABMR寄存器FPM位和PBL位的值。
															
  uint32_t             EnhancedDescriptorFormat;			//	增强描述符格式
															//	使能：	ENABLE
															//	禁止：	DISABLE
	
															//	说明：	
															
  uint32_t             DescriptorSkipLen;				//	描述符跳过长度
															//	该位指定两个未链接描述符之间跳过的字数
															//	有效值：0-31
	
															//	说明：	描述符跳过长度，指定两个未链接描述符之间跳过的字数，地址从当前描述符结束处开始跳到下一个描述符起始处，可选0~7，它设定ETH_DMABMR寄存器DSL位的值。
															
  uint32_t             DMAArbitration;						//	DMA仲裁
															//	ETH_DMA_ARBITRATION_ROUNDROBIN
															//	ETH_DMA_ARBITRATION_RX_PRIOR_TX
	
															//	说明：	DMA仲裁，控制RX和TX优先级，可选RX TX优先级比为1:1、2:1、3:1、4:1或者RX优先于TX，它设定ETH_DMABMR寄存器PM位和DA位的值，当设置为1时，RX优先于TX；为0时，循环调度，RX TX优先级比由PM位给出。
	

} __attribute__((aligned(4))) ETH_DMAInitTypeDef;


typedef struct
{
    uint8_t                 UpdateForDroppedBroadcast;      // 针对所丢弃广播数据包更新 MMC 计数器
    uint8_t                 FullHalfPreset;                 // 全-半预设置
    uint8_t                 Preset;                         // 计数器预设
    uint8_t                 ResetOnRead;                    // 读取时复位
    uint8_t                 StopRollover;                   // 计数器停止翻转
    uint8_t                 Rsv1[3];                           // 
} __attribute__((aligned(4))) ETH_MMCInitTypeDef;

typedef struct
{
    uint32_t                TxGoodFrameSingleCollision;     // 发送的单个冲突后良好帧计数器
    uint32_t                TxGoodFrameMultipleCollision;   // 发送的多个冲突后良好帧计数器
    uint32_t                TxGoodFrame;                    // 发送的良好帧计数器
    uint32_t                RxCRCErr;                       // 接收的帧 CRC 错误计数器
    uint32_t                RxAlignmentErr;                 // 接收的帧对齐错误计数器
    uint32_t                RxGoodUnicast;                  // 接收的良好单播帧计数器
} __attribute__((aligned(4))) ETH_MMCCounterTypeDef;

typedef struct
{
    uint32_t                Mask;                           // 字节屏蔽
    uint8_t                 Cmd;                            // 命令
    uint8_t                 Offset;                         // 偏移
    uint16_t                CRC16;                          // CRC16
} __attribute__((aligned(4))) ETH_PMTFilterTypeDef;

typedef struct
{
    ETH_PMTFilterTypeDef    Filter[4];                      // 过滤
    uint32_t                GlobalUnicast;                  // 全局单播
} __attribute__((aligned(4))) ETH_PMTInitTypeDef;

#define ETH_PTP_PPS_OUTPUT_MODE_CTRL    0
#define ETH_PTP_PPS_OUTPUT_MODE_CMD     1

typedef struct
{
    uint8_t                 TargetTimeFunc;
    uint8_t                 Mode;
    union
    {
        uint8_t             Freq;
        uint8_t             Cmd;
    } Output;
    uint8_t                 Rsv1;
    
    uint32_t                Interval;
    uint32_t                Width;
} __attribute__((aligned(4))) ETH_PPSInitTypeDef;

typedef struct
{
    uint8_t                 Auxi[4];       // 辅助快照使能
    
    uint8_t                 Clock;
    uint8_t                 AllFrames;
    uint8_t                 EthernetFrame;
    uint8_t                 MACAddrFilter;
    uint8_t                 MasterMessage;
    uint8_t                 EventMessage;
    uint8_t                 IPV4Message;
    uint8_t                 IPV6Message;
    
    uint8_t                 Ver2;
    uint8_t                 DigitalRollover;
    uint8_t                 FineUpdate;
    uint8_t                 Rsv1[1];
    
    ETH_PPSInitTypeDef      PPS;
} __attribute__((aligned(4))) ETH_PTPInitTypeDef;


typedef struct
{
    uint8_t                 AuxiNbr;
    uint8_t                 AuxiTriggerMissed;
    uint8_t                 Rsv1[2];
    uint8_t                 AuxiTrigger[4];
} __attribute__((aligned(4))) ETH_PTPAuxiTimeStatusTypeDef;

//typedef struct
//{
//    double                  InitValue;
//    double                  UnitValue;
//} __attribute__((aligned(4))) ETH_DelayTypeDef;

typedef struct
{
    uint8_t                 TxAuto;
    uint8_t                 TxClockGateCtrlInvalid;
    uint8_t                 Rsv1[2];
    uint16_t                EntryTime;
    uint16_t                ExtiTime;
} __attribute__((aligned(4))) ETH_LPITypeDef;

/** 
  * @brief  ETH Handle Structure definition  
  */
  
typedef struct
{
    ETH_TypeDef                     *Instance;     /*!< Register base address       */
  
    ETH_InitTypeDef                 Init;          /*!< Ethernet Init Configuration */
    
    ETH_MACInitTypeDef              MACConfig;
    ETH_DMAInitTypeDef              DMAConfig;
    ETH_FilterTypeDef               FilterConfig;
    ETH_MMCInitTypeDef              MMCConfig;
    ETH_MMCCounterTypeDef           MMCCounter;
    ETH_LPITypeDef                  LPIConfig;
    ETH_PMTInitTypeDef              PMTConfig;
    ETH_PTPInitTypeDef              PTPConfig;
    
    ETH_IntTypeDef                  Int;
    
    ETH_TxConfigTypeDef             TxConfig;
    
    ETH_TxDescListTypeDef           TxDescList;
    ETH_RxDescListTypeDef           RxDescList;
    
//    ETH_DelayTypeDef                Delay;
    
    uint32_t                        LinkStatus;     /*!< Ethernet link status        */
    
    
    __IO uint32_t                   State;           /*!< ETH communication state     */

    __IO uint32_t                   ErrorCode;       /*!< Holds the global Error code of the ETH HAL status machine 
                                                        This parameter can be a value of of @ref ETH_Error_Code */

    __IO uint32_t                   DMAErrorCode;    /*!< Holds the DMA Rx Tx Error code when a DMA AIS interrupt occurs
                                                        This parameter can be a combination of @ref ETH_DMA_Status_Flags */

    __IO uint32_t                   MACErrorCode;    /*!< Holds the MAC Rx Tx Error code when a MAC Rx or Tx status interrupt occurs
                                                        This parameter can be a combination of @ref ETH_MAC_Rx_Tx_Status */ 
    
    
    
} __attribute__((aligned(4))) ETH_HandleTypeDef;

#define ETH_DMA_TX_DESC0_OWN                    ( BIT31 )
#define ETH_DMA_TX_DESC0_IC                     ( BIT30 )
#define ETH_DMA_TX_DESC0_LS                     ( BIT29 )
#define ETH_DMA_TX_DESC0_FS                     ( BIT28 )
#define ETH_DMA_TX_DESC0_DC                     ( BIT27 )
#define ETH_DMA_TX_DESC0_DP                     ( BIT26 )
#define ETH_DMA_TX_DESC0_TTSE                   ( BIT25 )
#define ETH_DMA_TX_DESC0_CIC_Pos                ( 22U )
#define ETH_DMA_TX_DESC0_CIC_Msk                ( 0x3UL << ETH_DMA_TX_DESC0_CIC_Pos )
#define ETH_DMA_TX_DESC0_CIC                    ( ETH_DMA_TX_DESC0_CIC_Msk )
#define ETH_DMA_TX_DESC0_CIC_0                  ( 0x1UL << ETH_DMA_TX_DESC0_CIC_Pos )
#define ETH_DMA_TX_DESC0_CIC_1                  ( 0x2UL << ETH_DMA_TX_DESC0_CIC_Pos )
#define ETH_DMA_TX_DESC0_TER                    ( BIT21 )
#define ETH_DMA_TX_DESC0_TCH                    ( BIT20 )
#define ETH_DMA_TX_DESC0_TTSS                   ( BIT17 )
#define ETH_DMA_TX_DESC0_IHE                    ( BIT16 )
#define ETH_DMA_TX_DESC0_ES                     ( BIT15 )
#define ETH_DMA_TX_DESC0_JT                     ( BIT14 )
#define ETH_DMA_TX_DESC0_FF                     ( BIT13 )
#define ETH_DMA_TX_DESC0_IPE                    ( BIT12 )
#define ETH_DMA_TX_DESC0_LCA                    ( BIT11 )
#define ETH_DMA_TX_DESC0_NC                     ( BIT10 )
#define ETH_DMA_TX_DESC0_LCO                    ( BIT9 )
#define ETH_DMA_TX_DESC0_EC                     ( BIT8 )
#define ETH_DMA_TX_DESC0_VF                     ( BIT7 )
#define ETH_DMA_TX_DESC0_CC                     ( BIT6 | BIT5 | BIT4 | BIT3 )
#define ETH_DMA_TX_DESC0_ED                     ( BIT2 )
#define ETH_DMA_TX_DESC0_UF                     ( BIT1 )
#define ETH_DMA_TX_DESC0_DB                     ( BIT0 )


#define ETH_DMA_TX_DESC1_TBS2_Pos               ( 16U )
#define ETH_DMA_TX_DESC1_TBS2                   ( 0x1fff0000U )
#define ETH_DMA_TX_DESC1_TBS1_Pos               ( 0U )
#define ETH_DMA_TX_DESC1_TBS1                   ( 0x00001fffU )


#define ETH_CHECKSUM_INSERTION_CTRL_DISABLE             ( 0U )
#define ETH_CHECKSUM_INSERTION_CTRL_IP_HEAD             ( 1U )
#define ETH_CHECKSUM_INSERTION_CTRL_IP_HEAD_PAYLOAD     ( 2U )
#define ETH_CHECKSUM_INSERTION_CTRL_FULL                ( 3U )


#define ETH_DMA_RX_DESC0_OWN                    ( BIT31 )
#define ETH_DMA_RX_DESC0_AFM                    ( BIT30 )
#define ETH_DMA_RX_DESC0_FL_Pos                 ( 16U )
#define ETH_DMA_RX_DESC0_FL                     ( 0x3FFF0000U )
#define ETH_DMA_RX_DESC0_ES                     ( BIT15 )
#define ETH_DMA_RX_DESC0_DE                     ( BIT14 )
#define ETH_DMA_RX_DESC0_SAF                    ( BIT13 )
#define ETH_DMA_RX_DESC0_LE                     ( BIT12 )
#define ETH_DMA_RX_DESC0_OE                     ( BIT11 )
#define ETH_DMA_RX_DESC0_VLAN                   ( BIT10 )
#define ETH_DMA_RX_DESC0_FS                     ( BIT9 )
#define ETH_DMA_RX_DESC0_LS                     ( BIT8 )
#define ETH_DMA_RX_DESC0_IPHCE                  ( BIT7 )
#define ETH_DMA_RX_DESC0_TSV                    ( BIT7 )
#define ETH_DMA_RX_DESC0_LCO                    ( BIT6 )
#define ETH_DMA_RX_DESC0_FT                     ( BIT5 )
#define ETH_DMA_RX_DESC0_RWT                    ( BIT4 )
#define ETH_DMA_RX_DESC0_RE                     ( BIT3 )
#define ETH_DMA_RX_DESC0_DBE                    ( BIT2 )
#define ETH_DMA_RX_DESC0_CE                     ( BIT1 )
#define ETH_DMA_RX_DESC0_PCE_ESA                ( BIT0 )

#define ETH_DMA_RX_DESC0_ERRORS_MASK            ( BIT14 | BIT11 | BIT7 | BIT6 | BIT4 | BIT3 | BIT1 | BIT0 )

#define ETH_DMA_RX_DESC1_DIC                    ( BIT31 )
#define ETH_DMA_RX_DESC1_RBS2_Pos               ( 16U )
#define ETH_DMA_RX_DESC1_RBS2                   ( 0x1FFF0000U )
#define ETH_DMA_RX_DESC1_RER                    ( BIT15 )
#define ETH_DMA_RX_DESC1_RCH                    ( BIT14 )
#define ETH_DMA_RX_DESC1_RBS1_Pos               ( 0U )
#define ETH_DMA_RX_DESC1_RBS1                   ( 0x00001FFFU )




#define ETH_TIMEOUT_SWRESET                                 ( 500U )
#define ETH_TIMEOUT_LINKED_STATE                            ( 5000U )
#define ETH_TIMEOUT_AUTONEGO_COMPLETED                      ( 5000U )
#define ETH_TIMEOUT_PHY_READ                                ( 0xFFFFU )
#define ETH_TIMEOUT_PHY_WRITE                               ( 0xFFFFU )



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 源地址插入或替换控制
#define ETH_SOURCE_ADDRESS_DISABLE							( 0U )
#define ETH_SOURCE_ADDRESS_INSERT_ADDR0						( 1U )
#define ETH_SOURCE_ADDRESS_INSERT_ADDR1						( 2U )
#define ETH_SOURCE_ADDRESS_REPLACE_ADDR0					( 3U )
#define ETH_SOURCE_ADDRESS_REPLACE_ADDR1					( 4U )

#define ETH_INTERFRAME_GAP_96BIT							( 0U )
#define ETH_INTERFRAME_GAP_88BIT							( 1U )
#define ETH_INTERFRAME_GAP_80BIT							( 2U )
#define ETH_INTERFRAME_GAP_72BIT							( 3U )
#define ETH_INTERFRAME_GAP_64BIT							( 4U )
#define ETH_INTERFRAME_GAP_56BIT							( 5U )
#define ETH_INTERFRAME_GAP_48BIT							( 6U )
#define ETH_INTERFRAME_GAP_40BIT							( 7U )

#define ETH_SPEED_10M									    ( 0U )
#define ETH_SPEED_100M									    ( 1U )

#define ETH_MODE_HALF_DUPLEX							    ( 0U )
#define ETH_MODE_FULL_DUPLEX							    ( 1u )

#define ETH_BACK_OFF_LIMIT_10								( 0U )
#define ETH_BACK_OFF_LIMIT_8								( ETH_MACCR_BL_0 )
#define ETH_BACK_OFF_LIMIT_4								( ETH_MACCR_BL_1 )
#define ETH_BACK_OFF_LIMIT_1								( ETH_MACCR_BL_1 | ETH_MACCR_BL_0 )

#define ETH_PREAMBLE_LEN_7B									( 0U )
#define ETH_PREAMBLE_LEN_5B									( ETH_MACCR_PRELEN_0 )
#define ETH_PREAMBLE_LEN_3B									( ETH_MACCR_PRELEN_1 )

#define ETH_PASS_CONTROL_BLOCK_ALL                          ( 0U )
#define ETH_PASS_CONTROL_FORWARD_ALL_EXCEPT_PAUSE_FRAME     ( ETH_MACFFR_PCF_0 )
#define ETH_PASS_CONTROL_FORWARD_ALL                        ( ETH_MACFFR_PCF_1 )
#define ETH_PASS_CONTROL_FORWARD_PASSED_ADDR_FILTER         ( ETH_MACFFR_PCF_1 | ETH_MACFFR_PCF_0 )

#define ETH_PAUSE_LOW_THRESHOLD_MINUS_4					    ( 0U )
#define ETH_PAUSE_LOW_THRESHOLD_MINUS_28				    ( ETH_MACFCR_PLT_0 )
#define ETH_PAUSE_LOW_THRESHOLD_MINUS_144                   ( ETH_MACFCR_PLT_1 )
#define ETH_PAUSE_LOW_THRESHOLD_MINUS_256                   ( ETH_MACFCR_PLT_1 | ETH_MACFCR_PLT_0 )


#define ETH_VLAN_MODE_NONE                                  ( 0U )
#define ETH_VLAN_MODE_DELETE                                ( 1U )
#define ETH_VLAN_MODE_INSERT                                ( 2U )
#define ETH_VLAN_MODE_REPLACE                               ( 3U )

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
#define ETH_TRANSMIT_THRESHOLD_CONTROL_64BYTES				( 0U )
#define ETH_TRANSMIT_THRESHOLD_CONTROL_128BYTES				( ETH_DMAOMR_TTC_0 )
#define ETH_TRANSMIT_THRESHOLD_CONTROL_192BYTES				( ETH_DMAOMR_TTC_1 )
#define ETH_TRANSMIT_THRESHOLD_CONTROL_256BYTES				( ETH_DMAOMR_TTC_1 | ETH_DMAOMR_TTC_0 )
#define ETH_TRANSMIT_THRESHOLD_CONTROL_40BYTES				( ETH_DMAOMR_TTC_2 )
#define ETH_TRANSMIT_THRESHOLD_CONTROL_32BYTES				( ETH_DMAOMR_TTC_2 | ETH_DMAOMR_TTC_0 )
#define ETH_TRANSMIT_THRESHOLD_CONTROL_24BYTES				( ETH_DMAOMR_TTC_2 | ETH_DMAOMR_TTC_1 )
#define ETH_TRANSMIT_THRESHOLD_CONTROL_16BYTES				( ETH_DMAOMR_TTC_2 | ETH_DMAOMR_TTC_1 | ETH_DMAOMR_TTC_0 )

#define ETH_RECEIVED_THRESHOLD_CONTROL_64BYTES				( 0U )
#define ETH_RECEIVED_THRESHOLD_CONTROL_32BYTES				( ETH_DMAOMR_RTC_0 )
#define ETH_RECEIVED_THRESHOLD_CONTROL_96BYTES				( ETH_DMAOMR_RTC_1 )
#define ETH_RECEIVED_THRESHOLD_CONTROL_128BYTES				( ETH_DMAOMR_RTC_1 | ETH_DMAOMR_RTC_0 )

#define ETH_RX_DMA_BURST_LEN_1BEAT						( ETH_DMABMR_RDP_0 )
#define ETH_RX_DMA_BURST_LEN_2BEAT						( ETH_DMABMR_RDP_1 )
#define ETH_RX_DMA_BURST_LEN_4BEAT						( ETH_DMABMR_RDP_2 )
#define ETH_RX_DMA_BURST_LEN_8BEAT						( ETH_DMABMR_RDP_3 )
#define ETH_RX_DMA_BURST_LEN_16BEAT						( ETH_DMABMR_RDP_4 )
#define ETH_RX_DMA_BURST_LEN_32BEAT						( ETH_DMABMR_RDP_5 )

#define ETH_RX_TX_PRIORITY_RATIO_1_1						( 0U )
#define ETH_RX_TX_PRIORITY_RATIO_2_1						( ETH_DMABMR_PM_0 )
#define ETH_RX_TX_PRIORITY_RATIO_3_1						( ETH_DMABMR_PM_1 )
#define ETH_RX_TX_PRIORITY_RATIO_4_1						( ETH_DMABMR_PM_1 | ETH_DMABMR_PM_0 )

#define ETH_TX_DMA_BURST_LEN_1BEAT						( ETH_DMABMR_PBL_0 )
#define ETH_TX_DMA_BURST_LEN_2BEAT						( ETH_DMABMR_PBL_1 )
#define ETH_TX_DMA_BURST_LEN_4BEAT						( ETH_DMABMR_PBL_2 )
#define ETH_TX_DMA_BURST_LEN_8BEAT						( ETH_DMABMR_PBL_3 )
#define ETH_TX_DMA_BURST_LEN_16BEAT						( ETH_DMABMR_PBL_4 )
#define ETH_TX_DMA_BURST_LEN_32BEAT						( ETH_DMABMR_PBL_5 )

#define ETH_DMA_ARBITRATION_ROUNDROBIN						( 0U )
#define ETH_DMA_ARBITRATION_RX_PRIOR_TX						( ETH_DMABMR_DA )

/**
  * @}
  */

 /** 
  * @brief  ETH interrupt flag
  */
  
#define ETH_INT_FLAG_TX                                     ( 0 )
#define ETH_INT_FLAG_TX_BUF_UNAVAILABLE                     ( 1 )
#define ETH_INT_FLAG_EARLY_RX                               ( 2 )
#define ETH_INT_FLAG_RX                                     ( 3 )
#define ETH_INT_FLAG_FATAL_BUS_ERR                          ( 4 )
#define ETH_INT_FLAG_EARLY_TX                               ( 5 )
#define ETH_INT_FLAG_RX_WATCHDOG_TIMEOUT                    ( 6 )
#define ETH_INT_FLAG_RX_STOP                                ( 7 )
#define ETH_INT_FLAG_RX_BUF_UNAVAILABLE                     ( 8 )
#define ETH_INT_FLAG_UNDERFLOW                              ( 9 )
#define ETH_INT_FLAG_OVERFLOW                               ( 10 )
#define ETH_INT_FLAG_JABBER                                 ( 11 )
#define ETH_INT_FLAG_TX_STOP                                ( 12 )
#define ETH_INT_FLAG_LPI                                    ( 13 )
#define ETH_INT_FLAG_TIMESTAMP                              ( 14 )
#define ETH_INT_FLAG_PMT                                    ( 15 )
#define ETH_INT_FLAG_MMC                                    ( 16 )
#define ETH_INT_FLAG_MMC_TX                                 ( 17 )
#define ETH_INT_FLAG_MMC_TX_GOOD_FRAME                      ( 18 )
#define ETH_INT_FLAG_MMC_TX_SINGLE_COLLIDION                ( 19 )
#define ETH_INT_FLAG_MMC_TX_MULTIPLE_COLLIDION              ( 20 )
#define ETH_INT_FLAG_MMC_RX                                 ( 21 )
#define ETH_INT_FLAG_MMC_RX_UNICAST                         ( 22 )
#define ETH_INT_FLAG_MMC_RX_ALIGNMENT_ERR                   ( 23 )
#define ETH_INT_FLAG_MMC_RX_CRC_ERR                         ( 24 )
#define ETH_INT_FLAG_MAX                                    ( 25 )

/**
  * @}
  */

 /** 
  * @brief  ETH interrupt
  */
  
#define ETH_INT_TX                                          ( 0 )
#define ETH_INT_TX_BUF_UNAVAILABLE                          ( 1 )
#define ETH_INT_EARLY_RX                                    ( 2 )
#define ETH_INT_RX                                          ( 3 )
#define ETH_INT_FATAL_BUS_ERR                               ( 4 )
#define ETH_INT_EARLY_TX                                    ( 5 )
#define ETH_INT_RX_WATCHDOG_TIMEOUT                         ( 6 )
#define ETH_INT_RX_STOP                                     ( 7 )
#define ETH_INT_RX_BUF_UNAVAILABLE                          ( 8 )
#define ETH_INT_UNDERFLOW                                   ( 9 )
#define ETH_INT_OVERFLOW                                    ( 10 )
#define ETH_INT_JABBER                                      ( 11 )
#define ETH_INT_TX_STOP                                     ( 12 )
#define ETH_INT_LPI                                         ( 13 )
#define ETH_INT_TIMESTAMP                                   ( 14 )
#define ETH_INT_PMT                                         ( 15 )
#define ETH_INT_MMC_TX_GOOD_FRAME                           ( 18 )
#define ETH_INT_MMC_TX_SINGLE_COLLIDION                     ( 19 )
#define ETH_INT_MMC_TX_MULTIPLE_COLLIDION                   ( 20 )
#define ETH_INT_MMC_RX_UNICAST                              ( 22 )
#define ETH_INT_MMC_RX_ALIGNMENT_ERR                        ( 23 )
#define ETH_INT_MMC_RX_CRC_ERR                              ( 24 )
#define ETH_INT_MAX                                         ( 25 )

/**
  * @}
  */

/**
  * @}
  */


/**
  * @}
  */


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/


/** 
 * @brief  Enables the specified ETHERNET MAC interrupts.
  * @param  __HANDLE__    ETH Handle
  * @param  __INTERRUPT__ specifies the ETHERNET MAC interrupt sources to be
  *   enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg ETH_MAC_IT_TST : Time stamp trigger interrupt 
  *     @arg ETH_MAC_IT_PMT : PMT interrupt 
  * @retval None
  */
#define __HAL_ETH_MAC_ENABLE_IT(__HANDLE__, __INTERRUPT__)                 ((__HANDLE__)->Instance->MACIMR |= (__INTERRUPT__))

/**
  * @brief  Disables the specified ETHERNET MAC interrupts.
  * @param  __HANDLE__    ETH Handle
  * @param  __INTERRUPT__ specifies the ETHERNET MAC interrupt sources to be
  *   enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg ETH_MAC_IT_TST : Time stamp trigger interrupt 
  *     @arg ETH_MAC_IT_PMT : PMT interrupt
  * @retval None
  */
#define __HAL_ETH_MAC_DISABLE_IT(__HANDLE__, __INTERRUPT__)                ((__HANDLE__)->Instance->MACIMR &= ~(__INTERRUPT__))
#define __HAL_ETH_MAC_GET_IT(__HANDLE__, __INTERRUPT__)                   (((__HANDLE__)->Instance->MACIMR &( __INTERRUPT__)) == ( __INTERRUPT__))

/**
  * @brief  Checks whether the specified ETHERNET MAC flag is set or not.
  * @param  __HANDLE__ ETH Handle
  * @param  __FLAG__ specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg ETH_MAC_FLAG_TST  : Time stamp trigger flag   
  *     @arg ETH_MAC_FLAG_MMCT : MMC transmit flag  
  *     @arg ETH_MAC_FLAG_MMCR : MMC receive flag   
  *     @arg ETH_MAC_FLAG_MMC  : MMC flag  
  *     @arg ETH_MAC_FLAG_PMT  : PMT flag  
  * @retval The state of ETHERNET MAC flag.
  */
#define __HAL_ETH_MAC_GET_FLAG(__HANDLE__, __FLAG__)                   (((__HANDLE__)->Instance->MACSR &( __FLAG__)) == ( __FLAG__))

/** 
  * @brief  Enables the specified ETHERNET DMA interrupts.
  * @param  __HANDLE__    ETH Handle
  * @param  __INTERRUPT__ specifies the ETHERNET DMA interrupt sources to be
  *   enabled @ref ETH_DMA_Interrupts
  * @retval None
  */
#define __HAL_ETH_DMA_ENABLE_IT(__HANDLE__, __INTERRUPT__)                 ((__HANDLE__)->Instance->DMAIER |= (__INTERRUPT__))

/**
  * @brief  Disables the specified ETHERNET DMA interrupts.
  * @param  __HANDLE__    ETH Handle
  * @param  __INTERRUPT__ specifies the ETHERNET DMA interrupt sources to be
  *   disabled. @ref ETH_DMA_Interrupts
  * @retval None
  */
#define __HAL_ETH_DMA_DISABLE_IT(__HANDLE__, __INTERRUPT__)                ((__HANDLE__)->Instance->DMAIER &= ~(__INTERRUPT__))

#define __HAL_ETH_DMA_GET_IT(__HANDLE__, __INTERRUPT__)                (((__HANDLE__)->Instance->DMAIER & (__INTERRUPT__)) == (__INTERRUPT__))

/**
  * @brief  Clears the ETHERNET DMA IT pending bit.
  * @param  __HANDLE__    ETH Handle
  * @param  __INTERRUPT__ specifies the interrupt pending bit to clear. @ref ETH_DMA_Interrupts
  * @retval None
  */
//#define __HAL_ETH_DMA_CLEAR_FLAG(__HANDLE__, __FLAG__)      ((__HANDLE__)->Instance->DMASR =(__FLAG__))

/**
  * @brief  Checks whether the specified ETHERNET DMA flag is set or not.
* @param  __HANDLE__ ETH Handle
  * @param  __FLAG__ specifies the flag to check. @ref ETH_DMA_Flags
  * @retval The new state of ETH_DMA_FLAG (SET or RESET).
  */
#define __HAL_ETH_DMA_GET_FLAG(__HANDLE__, __FLAG__)                   (((__HANDLE__)->Instance->DMASR &( __FLAG__)) == ( __FLAG__))

/**
  * @brief  Checks whether the specified ETHERNET DMA flag is set or not.
  * @param  __HANDLE__ ETH Handle
  * @param  __FLAG__ specifies the flag to clear. @ref ETH_DMA_Flags
  * @retval The new state of ETH_DMA_FLAG (SET or RESET).
  */
#define __HAL_ETH_DMA_CLEAR_FLAG(__HANDLE__, __FLAG__)                 ((__HANDLE__)->Instance->DMASR = (__FLAG__))





#define IS_ETH_SOURCE_ADDR_CONTROL(para)					(((para) == ETH_SOURCE_ADDRESS_DISABLE) || \
															 ((para) == ETH_SOURCE_ADDRESS_INSERT_ADDR0) || \
															 ((para) == ETH_SOURCE_ADDRESS_INSERT_ADDR1) || \
															 ((para) == ETH_SOURCE_ADDRESS_REPLACE_ADDR0) || \
															 ((para) == ETH_SOURCE_ADDRESS_REPLACE_ADDR1))
  
#define IS_ETH_INTERFRAME_GAP(para)							(((para) == ETH_INTERFRAME_GAP_96BIT) || \
															 ((para) == ETH_INTERFRAME_GAP_88BIT) || \
															 ((para) == ETH_INTERFRAME_GAP_80BIT) || \
															 ((para) == ETH_INTERFRAME_GAP_72BIT) || \
															 ((para) == ETH_INTERFRAME_GAP_64BIT) || \
															 ((para) == ETH_INTERFRAME_GAP_56BIT) || \
															 ((para) == ETH_INTERFRAME_GAP_48BIT) || \
															 ((para) == ETH_INTERFRAME_GAP_40BIT))
  
#define IS_ETH_SPEED(para)                                  (((para) == ETH_SPEED_10M) || \
                                                             ((para) == ETH_SPEED_100M))
                                                             
#define IS_ETH_DUPLEX_MODE(para)                            (((para) == ETH_MODE_FULL_DUPLEX) || \
                                                             ((para) == ETH_MODE_HALF_DUPLEX))
                                                             
#define IS_ETH_MAC_SPEED(para) 								(((para) == ETH_MAC_SPEED_10M) || \
															 ((para) == ETH_MAC_SPEED_100M))
  
#define IS_ETH_MODE(para) 									(((para) == ETH_MODE_HALF_DUPLEX) || \
															 ((para) == ETH_MODE_FULL_DUPLEX))
  
#define IS_ETH_BACK_OFF_LIMIT(para)							(((para) == ETH_BACK_OFF_LIMIT_10) || \
															 ((para) == ETH_BACK_OFF_LIMIT_8) || \
															 ((para) == ETH_BACK_OFF_LIMIT_4) || \
															 ((para) == ETH_BACK_OFF_LIMIT_1))

#define IS_ETH_PREAMBLE_LEN(para)							(((para) == ETH_PREAMBLE_LEN_7B) || \
															 ((para) == ETH_PREAMBLE_LEN_5B) || \
															 ((para) == ETH_PREAMBLE_LEN_3B))
  
#define IS_ETH_PASS_CONTROL_PACKETS(para)					(((para) == ETH_PASS_CONTROL_BLOCK_ALL) || \
															 ((para) == ETH_PASS_CONTROL_FORWARD_ALL_EXCEPT_PAUSE_FRAME) || \
															 ((para) == ETH_PASS_CONTROL_FORWARD_ALL) || \
															 ((para) == ETH_PASS_CONTROL_FORWARD_PASSED_ADDR_FILTER))
  
#define IS_ETH_PAUSE_TIME(para)								((para) <= 0xFFFFUL)
  
#define IS_ETH_PAUSE_LOW_THRESHOLD(para)					(((para) == ETH_PAUSE_LOW_THRESHOLD_MINUS_4) || \
															 ((para) == ETH_PAUSE_LOW_THRESHOLD_MINUS_28) || \
															 ((para) == ETH_PAUSE_LOW_THRESHOLD_MINUS_144) || \
															 ((para) == ETH_PAUSE_LOW_THRESHOLD_MINUS_256))
  
#define IS_ETH_VLAN_TAG(para)					            ((para) <= 0x0000FFFFUL)
  
  
#define IS_ETH_TRANSMIT_THRESHOLD_CONTROL(para)				(((para) == ETH_TRANSMIT_THRESHOLD_CONTROL_64BYTES) || \
															 ((para) == ETH_TRANSMIT_THRESHOLD_CONTROL_128BYTES) || \
															 ((para) == ETH_TRANSMIT_THRESHOLD_CONTROL_192BYTES) || \
															 ((para) == ETH_TRANSMIT_THRESHOLD_CONTROL_256BYTES) || \
															 ((para) == ETH_TRANSMIT_THRESHOLD_CONTROL_40BYTES) || \
															 ((para) == ETH_TRANSMIT_THRESHOLD_CONTROL_32BYTES) || \
															 ((para) == ETH_TRANSMIT_THRESHOLD_CONTROL_24BYTES) || \
															 ((para) == ETH_TRANSMIT_THRESHOLD_CONTROL_16BYTES))
															
#define IS_ETH_RECEIVED_THRESHOLD_CONTROL(para)				(((para) == ETH_RECEIVED_THRESHOLD_CONTROL_64BYTES) || \
															 ((para) == ETH_RECEIVED_THRESHOLD_CONTROL_32BYTES) || \
															 ((para) == ETH_RECEIVED_THRESHOLD_CONTROL_96BYTES) || \
															 ((para) == ETH_RECEIVED_THRESHOLD_CONTROL_128BYTES))
															
#define IS_ETH_RX_DMA_BURST_LEN(para)					(((para) == ETH_RX_DMA_BURST_LEN_1BEAT) || \
															 ((para) == ETH_RX_DMA_BURST_LEN_2BEAT) || \
															 ((para) == ETH_RX_DMA_BURST_LEN_4BEAT) || \
															 ((para) == ETH_RX_DMA_BURST_LEN_8BEAT) || \
															 ((para) == ETH_RX_DMA_BURST_LEN_16BEAT) || \
															 ((para) == ETH_RX_DMA_BURST_LEN_32BEAT))
															
#define IS_ETH_RX_TX_PRIORITY_RATIO(para)					(((para) == ETH_RX_TX_PRIORITY_RATIO_1_1) || \
															 ((para) == ETH_RX_TX_PRIORITY_RATIO_2_1) || \
															 ((para) == ETH_RX_TX_PRIORITY_RATIO_3_1) || \
															 ((para) == ETH_RX_TX_PRIORITY_RATIO_4_1))
  
#define IS_ETH_TX_DMA_BURST_LEN(para)					(((para) == ETH_TX_DMA_BURST_LEN_1BEAT) || \
															 ((para) == ETH_TX_DMA_BURST_LEN_2BEAT) || \
															 ((para) == ETH_TX_DMA_BURST_LEN_4BEAT) || \
															 ((para) == ETH_TX_DMA_BURST_LEN_8BEAT) || \
															 ((para) == ETH_TX_DMA_BURST_LEN_16BEAT) || \
															 ((para) == ETH_TX_DMA_BURST_LEN_32BEAT))
															
#define IS_ETH_DESCRIPTOR_SKIP_LEN(para)				    ((para) <= 31U)
															
#define IS_ETH_DMA_ARBITRATION(para)						(((para) == ETH_DMA_ARBITRATION_ROUNDROBIN) || \
															 ((para) == ETH_DMA_ARBITRATION_RX_PRIOR_TX))
                                                             
                                                             
                                                             
                                                             
                                                             
#define IS_ETH_ADDR_FILTER_GROUP_MASK(para)                 (((para) & ~(ETH_MACA1HR_MBC >> ETH_MACA1HR_MBC_Pos)) == 0)

#define IS_ETH_VLAN_HASH_TABLE(para)                        ((para) <= 0xFFFFU)

#define IS_ETH_VLAN_MODE(para)					            (((para) == ETH_VLAN_MODE_NONE) || \
                                                             ((para) == ETH_VLAN_MODE_DELETE) || \
                                                             ((para) == ETH_VLAN_MODE_INSERT) || \
                                                             ((para) == ETH_VLAN_MODE_REPLACE))

#define IS_ETH_IPV6_ADDR_MASK(para)                         ((para) <= 127U)

#define IS_ETH_IPV4_SOUR_ADDR_MASK(para)                    ((para) <= 31U)

#define IS_ETH_IPV4_DEST_ADDR_MASK(para)                    ((para) <= 31U)

#define IS_ETH_SOUR_PORT(para)                              ((para) <= 0xFFFFU)

#define IS_ETH_DEST_PORT(para)                              ((para) <= 0xFFFFU)



  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


HAL_StatusTypeDef HAL_ETH_Init(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_DeInit(ETH_HandleTypeDef *heth);
void HAL_ETH_MspInit(ETH_HandleTypeDef *heth);
void HAL_ETH_MspDeInit(ETH_HandleTypeDef *heth);

HAL_StatusTypeDef HAL_ETH_InitDefaultParamter(ETH_HandleTypeDef *heth);

HAL_StatusTypeDef HAL_ETH_InitSpeedDefaultParamter(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_GetSpeedConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_SetSpeedConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_SetSpeedDefaultConfig(ETH_HandleTypeDef *heth);

HAL_StatusTypeDef HAL_ETH_InitDuplexModeDefaultParamter(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_GetDuplexModeConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_SetDuplexModeConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_SetDuplexModeDefaultConfig(ETH_HandleTypeDef *heth);

HAL_StatusTypeDef HAL_ETH_InitMACAddrDefaultParamter(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_GetMACAddrConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_SetMACAddrConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_SetMACAddrDefaultConfig(ETH_HandleTypeDef *heth);


void HAL_ETH_TxCpltCallback(ETH_HandleTypeDef *heth);
void HAL_ETH_RxCpltCallback(ETH_HandleTypeDef *heth);
void HAL_ETH_DMAErrorCallback(ETH_HandleTypeDef *heth);
void HAL_ETH_IRQHandler(ETH_HandleTypeDef *heth);
void HAL_ETH_WakeupIRQHandler(ETH_HandleTypeDef *heth);
void HAL_ETH_LPISendEntryCallback(ETH_HandleTypeDef *heth);
void HAL_ETH_LPISendExitCallback(ETH_HandleTypeDef *heth);
void HAL_ETH_LPIRecvEntryCallback(ETH_HandleTypeDef *heth);
void HAL_ETH_LPIRecvExitCallback(ETH_HandleTypeDef *heth);
void HAL_ETH_WakeupCallback(ETH_HandleTypeDef *heth);

HAL_StatusTypeDef HAL_ETH_GetTxBuff(ETH_HandleTypeDef *heth, ETH_BuffTypeDef **buff);
HAL_StatusTypeDef HAL_ETH_Transmit(ETH_HandleTypeDef *heth, ETH_BuffTypeDef *buff, uint32_t mode, ETH_TxStatusTypeDef *pStatus);
HAL_StatusTypeDef HAL_ETH_Receive(ETH_HandleTypeDef *heth, ETH_BuffTypeDef **buff, ETH_RxStatusTypeDef *pStatus);
HAL_StatusTypeDef HAL_ETH_ReleaseRxDescriptors(ETH_HandleTypeDef *heth);

HAL_StatusTypeDef HAL_ETH_Start(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_Stop(ETH_HandleTypeDef *heth);
HAL_ETH_StateTypeDef HAL_ETH_GetState(ETH_HandleTypeDef *heth);

HAL_StatusTypeDef HAL_ETH_InitAddrFilterDefaultParamter(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_GetAddrFilterConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_SetAddrFilterConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_SetAddrFilterDefaultConfig(ETH_HandleTypeDef *heth);

HAL_StatusTypeDef HAL_ETH_InitVLANFilterDefaultParamter(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_GetVLANFilterConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_SetVLANFilterConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_SetVLANFilterDefaultConfig(ETH_HandleTypeDef *heth);

HAL_StatusTypeDef HAL_ETH_InitL3L4FilterDefaultParamter(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_GetL3L4FilterConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_SetL3L4FilterConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_SetL3L4FilterDefaultConfig(ETH_HandleTypeDef *heth);

HAL_StatusTypeDef HAL_ETH_InitFilterDefaultParamter(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_GetFilterConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_SetFilterConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_SetFilterDefaultConfig(ETH_HandleTypeDef *heth);

HAL_StatusTypeDef HAL_ETH_InitVLANDefaultParamter(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_GetVLANConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_SetVLANConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_SetVLANDefaultConfig(ETH_HandleTypeDef *heth);

HAL_StatusTypeDef HAL_ETH_InitMACDefaultParamter(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_GetMACConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_SetMACConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_SetMACDefaultConfig(ETH_HandleTypeDef *heth);

HAL_StatusTypeDef HAL_ETH_InitDMADefaultParamter(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_GetDMAConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_SetDMAConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_SetDMADefaultConfig(ETH_HandleTypeDef *heth);

uint32_t HAL_ETH_GetFlowCtrlStatus(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_RecvFlowCtrlEnable(ETH_HandleTypeDef *heth, uint32_t pausetime);
HAL_StatusTypeDef HAL_ETH_RecvFlowCtrlDisable(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_SendFlowCtrlEnable(ETH_HandleTypeDef *heth, uint32_t unicast_pause_frame_detect);
HAL_StatusTypeDef HAL_ETH_SendFlowCtrlDisable(ETH_HandleTypeDef *heth);
uint32_t HAL_ETH_GetBackPressureStatus(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_BackPressureEnable(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_BackPressureDisable(ETH_HandleTypeDef *heth);

HAL_StatusTypeDef HAL_ETH_InitMMCDefaultParamter(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_GetMMCCounter(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_GetMMCConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_SetMMCConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_SetMMCDefaultConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_MMCFreezeCounter(ETH_HandleTypeDef *heth, FunctionalState cmd);
HAL_StatusTypeDef HAL_ETH_MMCResetCounter(ETH_HandleTypeDef *heth);

HAL_StatusTypeDef HAL_ETH_InitLPIDefaultParamter(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_GetLPIConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_SetLPIConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_SetLPIDefaultConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_EnterLPIMode(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_ExitLPIMode(ETH_HandleTypeDef *heth);

HAL_StatusTypeDef HAL_ETH_InitPMTDefaultParamter(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_GetPMTConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_SetPMTConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_SetPMTDefaultConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_EnterPowerDownMode(ETH_HandleTypeDef *heth, uint32_t WakeupMode, uint32_t WakeupFrameEnable, uint32_t MagicPacketEnable);

HAL_StatusTypeDef HAL_ETH_InitPTPDefaultParamter(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_GetPTPConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_SetPTPConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_SetPTPDefaultConfig(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_PTPStart(ETH_HandleTypeDef *heth, ETH_TimestampTypeDef *timestamp);
HAL_StatusTypeDef HAL_ETH_PTPStop(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_PTPAdjFreq(ETH_HandleTypeDef *heth, int32_t freq);
HAL_StatusTypeDef HAL_ETH_PTPUpdateOffset(ETH_HandleTypeDef *heth, ETH_TimestampTypeDef *timestamp);
HAL_StatusTypeDef HAL_ETH_PTPTimeSetTime(ETH_HandleTypeDef *heth, ETH_TimestampTypeDef *timestamp);
HAL_StatusTypeDef HAL_ETH_PTPGetSystemTime(ETH_HandleTypeDef *heth, ETH_TimestampTypeDef *timestamp);
HAL_StatusTypeDef HAL_ETH_PTPGetTargetTime(ETH_HandleTypeDef *heth, ETH_TimestampTypeDef *timestamp);
HAL_StatusTypeDef HAL_ETH_PTPSetTargetTime(ETH_HandleTypeDef *heth, ETH_TimestampTypeDef *timestamp);
HAL_StatusTypeDef HAL_ETH_PTPGetAuxiliaryTime(ETH_HandleTypeDef *heth, ETH_TimestampTypeDef *timestamp);
uint32_t HAL_ETH_PTPGetAuxiTimeStatus(ETH_HandleTypeDef *heth, ETH_PTPAuxiTimeStatusTypeDef *status);



HAL_StatusTypeDef HAL_ETH_ConfigSMI(ETH_HandleTypeDef *heth);
HAL_StatusTypeDef HAL_ETH_ReadPHYRegister(ETH_HandleTypeDef *heth, uint32_t PHYAddr, uint32_t PHYReg, uint32_t *RegValue);
HAL_StatusTypeDef HAL_ETH_WritePHYRegister(ETH_HandleTypeDef *heth, uint32_t PHYAddr, uint32_t PHYReg, uint32_t RegValue);

HAL_StatusTypeDef HAL_ETH_RxClockDelayConfig(ETH_HandleTypeDef *heth, uint32_t uint, uint32_t len);


#endif

