
#ifndef __SYSTEN_MPU_ARMV8M_H__
#define __SYSTEN_MPU_ARMV8M_H__     

#include <stdint.h>

#include "system_acm32h5xx.h"

#define PRIVILEGED_DEFAULT_DISABLE 0
#define PRIVILEGED_DEFAULT_ENABLE  1   
#define HARDFAULT_NMI_DISABLE      0
#define HARDFAULT_NMI_ENABLE       1


#define MPU_ARMV8M_MAIR_ATTR_CODE_VAL        0xAA // code flash 
#define MPU_ARMV8M_MAIR_ATTR_CODE_IDX        0

#define MPU_ARMV8M_MAIR_ATTR_DATANOCACHE_VAL 0x44  // data non-cacheable, sram    
#define MPU_ARMV8M_MAIR_ATTR_DATANOCACHE_IDX 1   

#define MPU_ARMV8M_MAIR_ATTR_DATA_VAL        0xFF  // data cacheable 
#define MPU_ARMV8M_MAIR_ATTR_DATA_IDX        2

#define MPU_ARMV8M_MAIR_ATTR_FDATANOCACHE_VAL 0x44  // data non-cacheable, flash    
#define MPU_ARMV8M_MAIR_ATTR_FDATANOCACHE_IDX 3   

#define MPU_ARMV8M_MAIR_ATTR_DEVICE_VAL      0x00 //device, nGnRnE  
#define MPU_ARMV8M_MAIR_ATTR_DEVICE_IDX      4  


struct mpu_armv8m_dev_t {
    const uint32_t base;
};

enum mpu_armv8m_error_t {
    MPU_ARMV8M_OK,
    MPU_ARMV8M_ERROR
};

enum mpu_armv8m_attr_exec_t {
    MPU_ARMV8M_XN_EXEC_OK,
    MPU_ARMV8M_XN_EXEC_NEVER
};

enum mpu_armv8m_attr_access_t {
    MPU_ARMV8M_AP_RW_PRIV_ONLY,
    MPU_ARMV8M_AP_RW_PRIV_UNPRIV,
    MPU_ARMV8M_AP_RO_PRIV_ONLY,
    MPU_ARMV8M_AP_RO_PRIV_UNPRIV
};

enum mpu_armv8m_attr_shared_t {
    MPU_ARMV8M_SH_NONE,
    MPU_ARMV8M_SH_UNUSED,
    MPU_ARMV8M_SH_OUTER,
    MPU_ARMV8M_SH_INNER
};

struct mpu_armv8m_region_cfg_t {
    uint32_t region_nr;
    uint32_t region_base;
    uint32_t region_limit;
    uint32_t region_attridx;
    enum mpu_armv8m_attr_exec_t     attr_exec;
    enum mpu_armv8m_attr_access_t   attr_access;
    enum mpu_armv8m_attr_shared_t   attr_sh;
};

struct mpu_armv8m_region_cfg_raw_t {
    uint32_t region_nr;
    uint32_t region_base;
    uint32_t region_limit;
};


enum mpu_armv8m_error_t system_mpu_armv8m_enable(struct mpu_armv8m_dev_t *dev,
                                          uint32_t privdef_en,
                                          uint32_t hfnmi_en);


enum mpu_armv8m_error_t system_mpu_armv8m_disable(struct mpu_armv8m_dev_t *dev);


enum mpu_armv8m_error_t system_mpu_armv8m_clean(struct mpu_armv8m_dev_t *dev);


enum mpu_armv8m_error_t system_mpu_armv8m_region_enable(
                                struct mpu_armv8m_dev_t *dev,
                                struct mpu_armv8m_region_cfg_t *region_cfg);


enum mpu_armv8m_error_t system_mpu_armv8m_region_disable(
                                struct mpu_armv8m_dev_t *dev,
                                uint32_t region_nr);


                                
#endif /* __SYSTEN_MPU_ARMV8M_H__ */    
