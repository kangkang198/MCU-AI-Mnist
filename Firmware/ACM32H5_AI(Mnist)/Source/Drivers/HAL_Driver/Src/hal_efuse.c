/******************************************************************************
*@file  : hal_efuse.c
*@brief : EFUSE HAL module driver.
******************************************************************************/

#include "hal.h"

#ifdef HAL_EFUSE_MODULE_ENABLED

/******************************************************************************
*@brief : Initializes the EFUSEx peripheral according to the specified parameters
*         in the EFUSE_Init.
*@param : EFUSEx: where x can be (A..F) to select the EFUSE peripheral.
*@param : EFUSE_Init: pointer to an EFUSE_InitTypeDef structure that contains
*         the configuration information for the specified EFUSE peripheral.
*@return: None
******************************************************************************/
HAL_StatusTypeDef HAL_EFUSE_Init(EFUSE_TypeDef *EFUSEx)
{

    /* Check the parameters */
    assert_param(IS_EFUSE_ALL_INSTANCE(EFUSEx));

    if(EFUSEx == EFUSE1)
    {
        __HAL_RCC_EFUSE1_CLK_ENABLE();

    }
    else if(EFUSEx == EFUSE2)
    {
        __HAL_RCC_EFUSE2_CLK_ENABLE();

    }
    if ((RCC->RCHCR & (RCC_RCHCR_RCHEN | RCC_RCHCR_RCHRDY)) != (RCC_RCHCR_RCHEN | RCC_RCHCR_RCHRDY))
		return HAL_ERROR;

    HAL_EFUSE_PowerUpSpTimeCfg(EFUSEx,11*EFUSE_1US_TIMES);
    HAL_EFUSE_PowerDownHdCfg(EFUSEx,2*EFUSE_1US_TIMES);
    HAL_EFUSE_ProWaitTimeCfg(EFUSEx,2*EFUSE_1US_TIMES);
    HAL_EFUSE_ProTimeCfg(EFUSEx,4*EFUSE_1US_TIMES);
    //wtim:4*4+3*2+1+11=34us(0x55),实测36us
    //pt*bit+pw*(bit-1)+st+pu
	
	return HAL_OK;
}

/******************************************************************************
*@brief : De-initializes the EFUSEx peripheral registers to their default reset values.
*@param : EFUSEx: where x can be (A..F) to select the EFUSE peripheral.
*@param : EFUSE_Pin: specifies the port bit to be written.
*@return: None
******************************************************************************/
void HAL_EFUSE_DeInit(EFUSE_TypeDef *EFUSEx)
{

    /* Check the parameters */
    assert_param(IS_EFUSE_ALL_INSTANCE(EFUSEx));

    if(EFUSEx == EFUSE1)
    {
        __HAL_RCC_EFUSE1_RESET();
        __HAL_RCC_EFUSE1_CLK_DISABLE();
    }
    else if(EFUSEx == EFUSE2)
    {
        __HAL_RCC_EFUSE2_RESET();
        __HAL_RCC_EFUSE2_CLK_DISABLE();
    }

}

/******************************************************************************
*@brief : Write data(in byte) of byteaddr.
*@param : EFUSEx: where x can be (1..2) to select the EFUSE peripheral.
*@param : byteaddr: specifies the byteaddr to be write.
*@param : data: specifies the data written to byteaddr.
*@param : timeout: specifies the time wait for write byte to complete
*@return: None
******************************************************************************/
HAL_StatusTypeDef HAL_EFUSE_WriteByte(EFUSE_TypeDef *EFUSEx,uint16_t byteaddr,uint8_t data,uint32_t timeout)
{

    /* Check the parameters */
    assert_param(IS_EFUSE_ALL_INSTANCE(EFUSEx));
    assert_param(IS_EFUSE_BYTE_ADDR(byteaddr));

    if (RCC->RCHCR & RCC_RCHCR_RCHDIV)
        return HAL_ERROR;//不支持RCH 16分频
	
    if ((RCC->RCHCR & (RCC_RCHCR_RCHEN | RCC_RCHCR_RCHRDY)) != (RCC_RCHCR_RCHEN | RCC_RCHCR_RCHRDY))
		return HAL_ERROR;

    while((!(EFUSEx->SR & EFUSE_SR_PREREAD_DONE)) && timeout--);
    if(timeout == 0)
    {
        return HAL_TIMEOUT;
    }

    EFUSEx->AR = byteaddr;

    EFUSEx->DWR = data;

    EFUSEx->CTRL = EFUSE_WBYTE;

    EFUSEx->CTRL |= EFUSE_CTRL_TRIG;

    while( (!(EFUSEx->SR&EFUSE_SR_UNPG)) && (!(EFUSEx->SR&EFUSE_SR_DONE)) && timeout--);
    EFUSEx->CLR |=EFUSE_CLR_CDONE|EFUSE_CLR_CUNPG;


    if(timeout == 0)
    {
        return HAL_TIMEOUT;
    }
    else
    {
        return HAL_OK;
    }

}
/******************************************************************************
*@brief : Write multiple data(in byte) of byteaddr.
*@param : EFUSEx: where x can be (1..2) to select the EFUSE peripheral.
*@param : byteaddr: specifies the byteaddr to be write.
*@param : data: specifies the data written to byteaddr.
*@param : timeout: specifies the time wait for write byte to complete
*@return: None
******************************************************************************/
HAL_StatusTypeDef HAL_EFUSE_WriteBytes(EFUSE_TypeDef *EFUSEx,uint16_t byteaddr,uint8_t* data,uint32_t len,uint32_t timeout)
{
    uint32_t time_byte = timeout;

    /* Check the parameters */
    assert_param(IS_EFUSE_ALL_INSTANCE(EFUSEx));
    assert_param(IS_EFUSE_BYTE_ADDR(byteaddr));

    if (RCC->RCHCR & RCC_RCHCR_RCHDIV)
        return HAL_ERROR;//不支持RCH 16分频
	
    if ((RCC->RCHCR & (RCC_RCHCR_RCHEN | RCC_RCHCR_RCHRDY)) != (RCC_RCHCR_RCHEN | RCC_RCHCR_RCHRDY))
		return HAL_ERROR;

    while((!(EFUSEx->SR & EFUSE_SR_PREREAD_DONE)) && timeout--);
    if(timeout == 0)
    {
        return HAL_TIMEOUT;
    }


    EFUSEx->CTRL = EFUSE_WBYTE;

    for(uint32_t i=0; i<len; i++)
    {
        assert_param(IS_EFUSE_BYTE_ADDR(byteaddr+i));

        EFUSEx->AR = byteaddr+i;

        EFUSEx->DWR = *(data+i);

        EFUSEx->CTRL |= EFUSE_CTRL_TRIG;

        while( (!(EFUSEx->SR&EFUSE_SR_UNPG)) && (!(EFUSEx->SR&EFUSE_SR_DONE)) && time_byte--);
        EFUSEx->CLR |=EFUSE_CLR_CDONE|EFUSE_CLR_CUNPG;

        if(time_byte == 0)
        {
            return HAL_TIMEOUT;
        }

        time_byte = timeout;
    }

    return HAL_OK;

}
/******************************************************************************
*@brief : Read data(in byte) of byteaddr.
*@param : EFUSEx: where x can be (1..2) to select the EFUSE peripheral.
*@param : byteaddr: specifies the byteaddr to be read.
*@param : data: the data read from byteaddr.
*@param : timeout: specifies the time wait for read byte to complete
*@return: None
******************************************************************************/
HAL_StatusTypeDef HAL_EFUSE_ReadByte(EFUSE_TypeDef *EFUSEx,uint16_t byteaddr,uint8_t* data,uint32_t timeout)
{

    /* Check the parameters */
    assert_param(IS_EFUSE_ALL_INSTANCE(EFUSEx));
    assert_param(IS_EFUSE_BYTE_ADDR(byteaddr));

    while((!(EFUSEx->SR & EFUSE_SR_PREREAD_DONE)) && timeout--);
    if(timeout == 0)
    {
        return HAL_TIMEOUT;
    }


    EFUSEx->AR = byteaddr;

    EFUSEx->CTRL = EFUSE_RBYTE;

    EFUSEx->CTRL |= EFUSE_CTRL_TRIG;

    while( (!(EFUSEx->SR&EFUSE_SR_DONE)) && timeout--);

    *data = EFUSEx->DR;

    EFUSEx->CLR |=EFUSE_CLR_CDONE;

    if(timeout == 0)
    {
        return HAL_TIMEOUT;
    }
    else
    {
        return HAL_OK;
    }

}

/******************************************************************************
*@brief : Read multiple data(in byte) of byteaddr.
*@param : EFUSEx: where x can be (1..2) to select the EFUSE peripheral.
*@param : byteaddr: specifies the byteaddr to be read.
*@param : data: the data read from byteaddr.
*@param : timeout: specifies the time wait for read byte to complete
*@return: None
******************************************************************************/
HAL_StatusTypeDef HAL_EFUSE_ReadBytes(EFUSE_TypeDef *EFUSEx,uint16_t byteaddr,uint8_t* data,uint32_t len,uint32_t timeout)
{
    uint32_t time_byte = timeout;

    /* Check the parameters */
    assert_param(IS_EFUSE_ALL_INSTANCE(EFUSEx));
    assert_param(IS_EFUSE_BYTE_ADDR(byteaddr));

    while((!(EFUSEx->SR & EFUSE_SR_PREREAD_DONE)) && timeout--);
    if(timeout == 0)
    {
        return HAL_TIMEOUT;
    }

    EFUSEx->CTRL = EFUSE_RBYTE;

    for(uint32_t i=0; i<len; i++)
    {
        assert_param(IS_EFUSE_BYTE_ADDR(byteaddr+i));

        EFUSEx->AR = byteaddr+i;

        EFUSEx->CTRL |= EFUSE_CTRL_TRIG;

        while( (!(EFUSEx->SR&EFUSE_SR_DONE)) && time_byte--);

        if(time_byte == 0)
        {
            return HAL_TIMEOUT;
        }

        *(data+i) = EFUSEx->DR;
        EFUSEx->CLR |=EFUSE_CLR_CDONE;
        time_byte = timeout;
    }

    return HAL_OK;

}

/******************************************************************************
*@brief : Config EFUSE write protection.
*@param : EFUSEx: where x can be (1..2) to select the EFUSE peripheral.
*@return: None
******************************************************************************/
void HAL_EFUSE_WpEnable(EFUSE_TypeDef *EFUSEx)
{
    assert_param(IS_EFUSE_ALL_INSTANCE(EFUSEx));
    EFUSEx->WP = 0xEF59A6CB;

}

/******************************************************************************
*@brief : Config EFUSE read protection(0~15 byte).
*@param : EFUSEx: where x can be (1..2) to select the EFUSE peripheral.
*@return: None
******************************************************************************/
void HAL_EFUSE_RpEnable(EFUSE_TypeDef *EFUSEx)
{
    assert_param(IS_EFUSE_ALL_INSTANCE(EFUSEx));
    EFUSEx->DSDP = 0xACF56B49;

}

/******************************************************************************
*@brief : Read data from data shadow register.
*@param : EFUSEx: where x can be (1..2) to select the EFUSE peripheral.
*@param : str_addr:where x can be (0..15), specifies the first data shadow register to be read.
*@param : len: specifies the number of data shadow register to be read.
*@param : data: the data read from of data shadow register.
*@return: None
******************************************************************************/
void HAL_EFUSE_ReadDsr(EFUSE_TypeDef *EFUSEx,uint8_t str_addr,uint8_t len,uint8_t* data)
{
    assert_param(IS_EFUSE_ALL_INSTANCE(EFUSEx));

    if(str_addr+len >16)
        return;
    if(len==0)
        return;

    for(uint8_t i=0; i<len; i++)
    {
        *(data+i)=(EFUSEx->DSR[str_addr+i])&0xff;
    }

}

/******************************************************************************
*@brief : Config EFUSE byte write protection.
*@param : EFUSEx: where x can be (1..2) to select the EFUSE peripheral.
*@return: None
******************************************************************************/
void HAL_EFUSE_ByteWpEnable(EFUSE_TypeDef *EFUSEx)
{
    assert_param(IS_EFUSE_ALL_INSTANCE(EFUSEx));
    EFUSEx->BYTEWP = 0xC98E1A6D;

}
/******************************************************************************
*@brief : Config EFUSE Power Up Set Up Time
*@param : EFUSEx: where x can be (1..2) to select the EFUSE peripheral.
*@param : us: 1000 times Power Up Time in microsecond mode.
*@return: None
******************************************************************************/
void HAL_EFUSE_PowerUpSpTimeCfg(EFUSE_TypeDef *EFUSEx, uint32_t us)
{
    assert_param(IS_EFUSE_ALL_INSTANCE(EFUSEx));
    assert_param(us>=1*EFUSE_1US_TIMES);
    uint16_t avdd_sp;
    uint32_t rch_freq,goal_freq;
    rch_freq=(64000000/8);
    goal_freq=(1000000*EFUSE_1US_TIMES/us);
    if(rch_freq<=goal_freq)
        avdd_sp=0;
    else
        avdd_sp=rch_freq/goal_freq-1;
    MODIFY_REG(EFUSEx->PGCFG,EFUSE_PGCFG_AVDD_SP,avdd_sp<<EFUSE_PGCFG_AVDD_SP_Pos);
}
/******************************************************************************
*@brief : Config EFUSE Power Down hold Time
*@param : EFUSEx: where x can be (1..2) to select the EFUSE peripheral.
*@param : us: 1000 times Power Down Time in microsecond mode.
*@return: None
******************************************************************************/
void HAL_EFUSE_PowerDownHdCfg(EFUSE_TypeDef *EFUSEx, uint32_t us)
{
    assert_param(IS_EFUSE_ALL_INSTANCE(EFUSEx));
    assert_param(us>=1*EFUSE_1US_TIMES);
    uint16_t avdd_hd;
    uint32_t rch_freq,goal_freq;
    rch_freq=(64000000/8);
    goal_freq=(1000000*EFUSE_1US_TIMES/us);
    if(rch_freq<=goal_freq)
        avdd_hd=0;
    else
        avdd_hd=rch_freq/goal_freq-1;
    MODIFY_REG(EFUSEx->PGCFG,EFUSE_PGCFG_AVDD_HD,avdd_hd<<EFUSE_PGCFG_AVDD_HD_Pos);
}
/******************************************************************************
*@brief : Config EFUSE Programm Wait Time
*@param : EFUSEx: where x can be (1..2) to select the EFUSE peripheral.
*@param : us: 1000 times Programm Wait Time in microsecond mode.
*@return: None
******************************************************************************/
void HAL_EFUSE_ProWaitTimeCfg(EFUSE_TypeDef *EFUSEx, uint32_t us)
{
    assert_param(IS_EFUSE_ALL_INSTANCE(EFUSEx));
    assert_param(us>=1*EFUSE_1US_TIMES);
    uint16_t pgwt;
    uint32_t rch_freq,goal_freq;
    rch_freq=(64000000/8);
    goal_freq=(1000000*EFUSE_1US_TIMES/us);
    if(rch_freq<=goal_freq)
        pgwt=0;
    else
        pgwt=rch_freq/goal_freq-1;
    MODIFY_REG(EFUSEx->PGCFG,EFUSE_PGCFG_PGWT,pgwt<<EFUSE_PGCFG_PGWT_Pos);
}

/******************************************************************************
*@brief : Config EFUSE Programm  Time
*@param : EFUSEx: where x can be (1..2) to select the EFUSE peripheral.
*@param : us: 1000 times Programm  Time in microsecond mode.
*@return: None
******************************************************************************/
void HAL_EFUSE_ProTimeCfg(EFUSE_TypeDef *EFUSEx, uint32_t us)
{
    assert_param(IS_EFUSE_ALL_INSTANCE(EFUSEx));
    assert_param(us>=3*EFUSE_1US_TIMES && us<=5*EFUSE_1US_TIMES);
    uint16_t pgt;
    uint32_t rch_freq,goal_freq;
    rch_freq=(64000000/8);
    goal_freq=(1000000*EFUSE_1US_TIMES/us);
    if(rch_freq<=goal_freq)
        pgt=0;
    else
        pgt=rch_freq/goal_freq-1;
    MODIFY_REG(EFUSEx->PGCFG,EFUSE_PGCFG_PGT,pgt<<EFUSE_PGCFG_PGT_Pos);
}

/******************************************************************************
*@brief : Get state of flag in EFUSE SR register
*@param : EFUSEx: where x can be (1..2) to select the EFUSE peripheral.
*@param : flag: This parameter can be a value of @ref EFUSE FLAG
*@return: None
******************************************************************************/
FlagStatus HAL_EFUSE_GetState(EFUSE_TypeDef *EFUSEx, uint32_t flag)
{
    assert_param(IS_EFUSE_ALL_INSTANCE(EFUSEx));
    assert_param(IS_EFUSE_FLAG(flag));
    if(EFUSEx->SR & flag)
        return SET;
    else
        return RESET;

}
/******************************************************************************
*@brief : Clear state of flag in EFUSE SR register
*@param : EFUSEx: where x can be (1..2) to select the EFUSE peripheral.
*@param : flag: EFUSE_UNPG_FLAG/EFUSE_DONE_FLAG
*@return: None
******************************************************************************/
void HAL_EFUSE_ClrState(EFUSE_TypeDef *EFUSEx, uint32_t flag)
{
    assert_param(IS_EFUSE_ALL_INSTANCE(EFUSEx));
    assert_param(IS_EFUSE_CLR_FLAG(flag));
    EFUSEx->CLR = flag;

}
#endif /* HAL_EFUSE_MODULE_ENABLED */


