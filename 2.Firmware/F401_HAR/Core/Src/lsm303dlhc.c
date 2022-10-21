/**
  ******************************************************************************
  * @file    lsm303dlhc.c
  * @author  MCD Application Team
  * @brief   This file provides a set of functions needed to manage the lsm303dlhc
  *          MEMS accelerometer.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2015 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "lsm303dlhc.h"

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup Components
  * @{
  */ 

/** @addtogroup LSM303DLHC
  * @{
  */

/** @defgroup LSM303DLHC_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup LSM303DLHC_Private_Defines
  * @{
  */

/**
  * @}
  */

/** @defgroup LSM303DLHC_Private_Macros
  * @{
  */

/**
  * @}
  */ 
  
/** @defgroup LSM303DLHC_Private_Variables
  * @{
  */ 
//ACCELERO_DrvTypeDef Lsm303dlhcDrv =
//{
//  LSM303DLHC_AccInit,
//  LSM303DLHC_AccDeInit,
//  LSM303DLHC_AccReadID,
//  LSM303DLHC_AccRebootCmd,
//  0,
//  LSM303DLHC_AccZClickITConfig,
//  0,
//  0,
//  0,
//  0,
//  LSM303DLHC_AccFilterConfig,
//  LSM303DLHC_AccFilterCmd,
//  LSM303DLHC_AccReadXYZ
//};

/**
  * @}
  */

/** @defgroup LSM303DLHC_Private_Functions
  * @{
  */



void COMPASSACCELERO_IO_Init(void)
{

}


void COMPASSACCELERO_IO_ITConfig(void)
{

}


void COMPASSACCELERO_IO_Write(uint16_t DeviceAddr, uint8_t RegisterAddr, uint8_t Value)
{
	HAL_I2C_Mem_Write(&LSM303DLHC_I2C_HANDLE, DeviceAddr, RegisterAddr, I2C_MEMADD_SIZE_8BIT, &Value, 1, 100);

}


uint8_t COMPASSACCELERO_IO_Read(uint16_t DeviceAddr, uint8_t RegisterAddr)
{
    uint8_t ret;

    HAL_I2C_Mem_Read(&LSM303DLHC_I2C_HANDLE, DeviceAddr, RegisterAddr, I2C_MEMADD_SIZE_8BIT, &ret, 1, 100);

    return ret;

}

uint8_t COMPASSACCELERO_IO_ReadLen(uint8_t dev_addr,uint8_t reg,uint8_t *buf,uint16_t cnt)
{
	HAL_I2C_Mem_Read(&LSM303DLHC_I2C_HANDLE, dev_addr, reg, I2C_MEMADD_SIZE_8BIT, buf, cnt, 100);


	return 0;
}



void LSM303DLHC_MagInit( void )
{
	COMPASSACCELERO_IO_Write(MAG_I2C_ADDRESS, LSM303DLHC_CRB_REG_M, 0xa0);

	COMPASSACCELERO_IO_Write(MAG_I2C_ADDRESS, LSM303DLHC_MR_REG_M, 0x00);
}




/**
  * @brief  Set LSM303DLHC Initialization.
  * @param  InitStruct: Init parameters
  * @retval None
  */
void LSM303DLHC_AccInit(void)
{  
  /* Write value to ACC MEMS CTRL_REG1 register */
  COMPASSACCELERO_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG1_A, LSM303DLHC_ODR_25_HZ|LSM303DLHC_AXES_ENABLE);
  
  /* Write value to ACC MEMS CTRL_REG4 register */
  COMPASSACCELERO_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG4_A, LSM303DLHC_FULLSCALE_4G);
}

/**
  * @brief  LSM303DLHC De-initialization.
  * @param  None
  * @retval None
  */
void LSM303DLHC_AccDeInit(void)
{  
}

/**
  * @brief  Read LSM303DLHC ID.
  * @param  None
  * @retval ID 
  */
uint8_t LSM303DLHC_AccReadID(void)
{  
  uint8_t ctrl = 0x00;
  
  /* Low level init */
  COMPASSACCELERO_IO_Init();
  
  /* Read value at Who am I register address */
  ctrl = COMPASSACCELERO_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_WHO_AM_I_ADDR);
  
  return ctrl;
}

/**
  * @brief  Reboot memory content of LSM303DLHC
  * @param  None
  * @retval None
  */
void LSM303DLHC_AccRebootCmd(void)
{
  uint8_t tmpreg;
  
  /* Read CTRL_REG5 register */
  tmpreg = COMPASSACCELERO_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG5_A);
  
  /* Enable or Disable the reboot memory */
  tmpreg |= LSM303DLHC_BOOT_REBOOTMEMORY;
  
  /* Write value to ACC MEMS CTRL_REG5 register */
  COMPASSACCELERO_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG5_A, tmpreg);
}

/**
  * @brief  Set High Pass Filter Modality
  * @param  FilterStruct: contains data for filter config
  * @retval None
  */
void LSM303DLHC_AccFilterConfig(uint8_t FilterStruct) 
{
  uint8_t tmpreg;
  
  /* Read CTRL_REG2 register */
  tmpreg = COMPASSACCELERO_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG2_A);
  
  tmpreg &= 0x0C;
  tmpreg |= FilterStruct;
  
  /* Write value to ACC MEMS CTRL_REG2 register */
  COMPASSACCELERO_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG2_A, tmpreg);
}

/**
  * @brief  Enable or Disable High Pass Filter
  * @param  HighPassFilterState: new state of the High Pass Filter feature.
  *      This parameter can be: 
  *         @arg: LSM303DLHC_HIGHPASSFILTER_DISABLE 
  *         @arg: LSM303DLHC_HIGHPASSFILTER_ENABLE
  * @retval None
  */
void LSM303DLHC_AccFilterCmd(uint8_t HighPassFilterState)
{
  uint8_t tmpreg;
  
  /* Read CTRL_REG2 register */
  tmpreg = COMPASSACCELERO_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG2_A);
  
  tmpreg &= 0xF7;
  
  tmpreg |= HighPassFilterState;
  
  /* Write value to ACC MEMS CTRL_REG2 register */
  COMPASSACCELERO_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG2_A, tmpreg);
}


void LSM303DLHC_AccReadXYZ(float* pData)
{
  uint8_t buffer[6]={0}, ctrlx[2],i;
  uint8_t cDivider;
  int16_t pnRawData[3];

  float sensitivity = LSM303DLHC_ACC_SENSITIVITY_2G;

  int16_t cen;
  /* Read the acceleration control register content */

  COMPASSACCELERO_IO_ReadLen(ACC_I2C_ADDRESS,LSM303DLHC_CTRL_REG4_A|0x80,ctrlx,2);

  /* Read output register X, Y & Z acceleration */
  COMPASSACCELERO_IO_ReadLen(ACC_I2C_ADDRESS,LSM303DLHC_OUT_X_L_A|0x80,buffer,6);



  if(ctrlx[1]&0x40)
      cDivider=64;
    else
      cDivider=16;

  /* check in the control register4 the data alignment*/
  if(!(ctrlx[0] & 0x40) || (ctrlx[1] & 0x40)) /* Little Endian Mode or FIFO mode */
  {
    for(i=0; i<3; i++)
    {
 		cen=(int16_t)((uint16_t)buffer[2*i+1] << 8) + buffer[2*i];
      pnRawData[i]=(int16_t)(cen)/cDivider;

    }
  }
  else /* Big Endian Mode */
  {
    for(i=0; i<3; i++)
      pnRawData[i]=((int16_t)((uint16_t)buffer[2*i] << 8) + buffer[2*i+1])/cDivider;
  }

  if(ctrlx[1]&0x40)
    {
      /* FIFO mode */
      sensitivity = 0.25;
    }
    else
    {
    	/* Normal mode */
  /* Switch the sensitivity value set in the CRTL4 */
       switch(ctrlx[0] & LSM303DLHC_FULLSCALE_16G)
       {
       case LSM303DLHC_FULLSCALE_2G:
         sensitivity = LSM303DLHC_ACC_SENSITIVITY_2G;
         break;
       case LSM303DLHC_FULLSCALE_4G:
         sensitivity = LSM303DLHC_ACC_SENSITIVITY_4G;
         break;
       case LSM303DLHC_FULLSCALE_8G:
         sensitivity = LSM303DLHC_ACC_SENSITIVITY_8G;
         break;
       case LSM303DLHC_FULLSCALE_16G:
         sensitivity = LSM303DLHC_ACC_SENSITIVITY_16G;
         break;
       }
    }

  /* Obtain the mg value for the three axis */
  for(i=0; i<3; i++)
  {
    pData[i]=(float)pnRawData[i]*sensitivity/100.0f;
  }
}


void LSM303DLHC_MagReadXYZ(float* pData)
{
  static unsigned char buffer[6]={0};
  unsigned char f;
  unsigned int Magn_Sensitivity_XY = 0, Magn_Sensitivity_Z = 0;
  uint16_t cen=0;


  COMPASSACCELERO_IO_ReadLen(MAG_I2C_ADDRESS,LSM303DLHC_OUT_X_H_M,buffer,6);
  COMPASSACCELERO_IO_ReadLen(MAG_I2C_ADDRESS,LSM303DLHC_CRB_REG_M,&f,1);

  switch(f & 0xE0)
  {
  case LSM303DLHC_FS_1_3_GA:
    Magn_Sensitivity_XY = LSM303DLHC_M_SENSITIVITY_XY_1_3Ga;
    Magn_Sensitivity_Z = LSM303DLHC_M_SENSITIVITY_Z_1_3Ga;
    break;
  case LSM303DLHC_FS_1_9_GA:
    Magn_Sensitivity_XY = LSM303DLHC_M_SENSITIVITY_XY_1_9Ga;
    Magn_Sensitivity_Z = LSM303DLHC_M_SENSITIVITY_Z_1_9Ga;
    break;
  case LSM303DLHC_FS_2_5_GA:
    Magn_Sensitivity_XY = LSM303DLHC_M_SENSITIVITY_XY_2_5Ga;
    Magn_Sensitivity_Z = LSM303DLHC_M_SENSITIVITY_Z_2_5Ga;
    break;
  case LSM303DLHC_FS_4_0_GA:
    Magn_Sensitivity_XY = LSM303DLHC_M_SENSITIVITY_XY_4Ga;
    Magn_Sensitivity_Z = LSM303DLHC_M_SENSITIVITY_Z_4Ga;
    break;
  case LSM303DLHC_FS_4_7_GA:
    Magn_Sensitivity_XY = LSM303DLHC_M_SENSITIVITY_XY_4_7Ga;
    Magn_Sensitivity_Z = LSM303DLHC_M_SENSITIVITY_Z_4_7Ga;
    break;
  case LSM303DLHC_FS_5_6_GA:
    Magn_Sensitivity_XY = LSM303DLHC_M_SENSITIVITY_XY_5_6Ga;
    Magn_Sensitivity_Z = LSM303DLHC_M_SENSITIVITY_Z_5_6Ga;
    break;
  case LSM303DLHC_FS_8_1_GA:
    Magn_Sensitivity_XY = LSM303DLHC_M_SENSITIVITY_XY_8_1Ga;
    Magn_Sensitivity_Z = LSM303DLHC_M_SENSITIVITY_Z_8_1Ga;
    break;
  }
 /*
  for(i=0; i<2; i++)
  {
		cen=(int16_t)(((int16_t)buffer[2*i] << 8) + buffer[2*i+1]) ;
    Data[i]=(float)(cen)*1000/Magn_Sensitivity_XY;

  }
	*/
	cen=(int16_t)(((uint16_t)buffer[0] << 8) + buffer[1]);
	pData[0]=(float)((int16_t)cen)*1000/Magn_Sensitivity_Z;

  cen=(int16_t)(((uint16_t)buffer[2] << 8) + buffer[3]);
  pData[2]=(float)((int16_t)cen)*1000/Magn_Sensitivity_Z;

	cen=(int16_t)(((uint16_t)buffer[4] << 8) + buffer[5]);
	pData[1]=(float)((int16_t)cen)*1000/Magn_Sensitivity_Z;
  /*
	cen=Data[1];
	Data[1]=Data[2];
	Data[2]=cen;
	*/
}


/**
  * @brief  Enable or Disable High Pass Filter on CLick
  * @param  HighPassFilterState: new state of the High Pass Filter feature.
  *      This parameter can be: 
  *         @arg: LSM303DLHC_HPF_CLICK_DISABLE 
  *         @arg: LSM303DLHC_HPF_CLICK_ENABLE
  * @retval None
  */
void LSM303DLHC_AccFilterClickCmd(uint8_t HighPassFilterClickState)
{
  uint8_t tmpreg = 0x00;
  
  /* Read CTRL_REG2 register */
  tmpreg = COMPASSACCELERO_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG2_A);
  
  tmpreg &= ~(LSM303DLHC_HPF_CLICK_ENABLE);
  
  tmpreg |= HighPassFilterClickState;
  
  /* Write value to ACC MEMS CTRL_REG2 regsister */
  COMPASSACCELERO_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG2_A, tmpreg);
}

/**
  * @brief Enable LSM303DLHC Interrupt1
  * @param  LSM303DLHC_IT: specifies the LSM303DLHC interrupt source to be enabled.
  *           This parameter can be any combination of the following values: 
  *         @arg   LSM303DLHC_IT1_CLICK
  *         @arg   LSM303DLHC_IT1_AOI1
  *         @arg   LSM303DLHC_IT1_AOI2
  *         @arg   LSM303DLHC_IT1_DRY1
  *         @arg   LSM303DLHC_IT1_DRY2
  *         @arg   LSM303DLHC_IT1_WTM
  *         @arg   LSM303DLHC_IT1_OVERRUN
  * @retval None
  */
void LSM303DLHC_AccIT1Enable(uint8_t LSM303DLHC_IT)
{
  uint8_t tmpval = 0x00;
  
  /* Read CTRL_REG3 register */
  tmpval = COMPASSACCELERO_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG3_A);
  
  /* Enable IT1 */
  tmpval |= LSM303DLHC_IT;
  
  /* Write value to MEMS CTRL_REG3 register */
  COMPASSACCELERO_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG3_A, tmpval);
}

/**
  * @brief Disable LSM303DLHC Interrupt1
  * @param  LSM303DLHC_IT: specifies the LSM303DLHC interrupt source to be disabled.
  *           This parameter can be any combination of the following values: 
  *         @arg   LSM303DLHC_IT1_CLICK
  *         @arg   LSM303DLHC_IT1_AOI1
  *         @arg   LSM303DLHC_IT1_AOI2
  *         @arg   LSM303DLHC_IT1_DRY1
  *         @arg   LSM303DLHC_IT1_DRY2
  *         @arg   LSM303DLHC_IT1_WTM
  *         @arg   LSM303DLHC_IT1_OVERRUN
  * @retval None
  */
void LSM303DLHC_AccIT1Disable(uint8_t LSM303DLHC_IT)
{
  uint8_t tmpval = 0x00;
  
  /* Read CTRL_REG3 register */
  tmpval = COMPASSACCELERO_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG3_A);
  
  /* Disable IT1 */
  tmpval &= ~LSM303DLHC_IT;
  
  /* Write value to MEMS CTRL_REG3 register */
  COMPASSACCELERO_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG3_A, tmpval);
}

/**
  * @brief Enable LSM303DLHC Interrupt2 
  * @param  LSM303DLHC_IT: specifies the LSM303DLHC interrupt source to be enabled.
  *           This parameter can be any combination of the following values: 
  *         @arg   LSM303DLHC_IT2_CLICK
  *         @arg   LSM303DLHC_IT2_INT1
  *         @arg   LSM303DLHC_IT2_INT2
  *         @arg   LSM303DLHC_IT2_BOOT
  *         @arg   LSM303DLHC_IT2_ACT
  *         @arg   LSM303DLHC_IT2_HLACTIVE
  * @retval None
  */
void LSM303DLHC_AccIT2Enable(uint8_t LSM303DLHC_IT)
{
  uint8_t tmpval = 0x00;
  
  /* Read CTRL_REG3 register */
  tmpval = COMPASSACCELERO_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG6_A);
  
  /* Enable IT2 */
  tmpval |= LSM303DLHC_IT;
  
  /* Write value to MEMS CTRL_REG3 register */
  COMPASSACCELERO_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG6_A, tmpval);
}

/**
  * @brief Disable LSM303DLHC Interrupt2
  * @param  LSM303DLHC_IT: specifies the LSM303DLHC interrupt source to be disabled.
  *           This parameter can be any combination of the following values: 
  *         @arg   LSM303DLHC_IT2_CLICK
  *         @arg   LSM303DLHC_IT2_INT1
  *         @arg   LSM303DLHC_IT2_INT2
  *         @arg   LSM303DLHC_IT2_BOOT
  *         @arg   LSM303DLHC_IT2_ACT
  *         @arg   LSM303DLHC_IT2_HLACTIVE
  * @retval None
  */
void LSM303DLHC_AccIT2Disable(uint8_t LSM303DLHC_IT)
{
  uint8_t tmpval = 0x00;
  
  /* Read CTRL_REG3 register */
  tmpval = COMPASSACCELERO_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG6_A);
  
  /* Disable IT2 */
  tmpval &= ~LSM303DLHC_IT;
  
  /* Write value to MEMS CTRL_REG3 register */
  COMPASSACCELERO_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG6_A, tmpval);
}

/**
  * @brief  INT1 interrupt enable
  * @param  ITCombination: Or or And combination
  *         ITAxes: Axes to be enabled 
  * @retval None
  */
void LSM303DLHC_AccINT1InterruptEnable(uint8_t ITCombination, uint8_t ITAxes)
{  
  uint8_t tmpval = 0x00;
  
  /* Read INT1_CFR register */
  tmpval = COMPASSACCELERO_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_INT1_CFG_A);
  
  /* Enable the selected interrupt */
  tmpval |= (ITAxes | ITCombination);
  
  /* Write value to MEMS INT1_CFR register */
  COMPASSACCELERO_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_INT1_CFG_A, tmpval);  
}

/**
  * @brief  INT1 interrupt disable
  * @param  ITCombination: Or or And combination
  *         ITAxes: Axes to be enabled 
  * @retval None
  */
void LSM303DLHC_AccINT1InterruptDisable(uint8_t ITCombination, uint8_t ITAxes)
{  
  uint8_t tmpval = 0x00;
  
  /* Read INT1_CFR register */
  tmpval = COMPASSACCELERO_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_INT1_CFG_A);
  
  /* Disable the selected interrupt */
  tmpval &= ~(ITAxes | ITCombination);
  
  /* Write value to MEMS INT1_CFR register */
  COMPASSACCELERO_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_INT1_CFG_A, tmpval);
}

/**
  * @brief  INT2 interrupt enable
  * @param  ITCombination: Or or And combination
  *         ITAxes: axes to be enabled 
  * @retval None
  */
void LSM303DLHC_AccINT2InterruptEnable(uint8_t ITCombination, uint8_t ITAxes)
{  
  uint8_t tmpval = 0x00;
  
  /* Read INT2_CFR register */
  tmpval = COMPASSACCELERO_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_INT2_CFG_A);
  
  /* Enable the selected interrupt */
  tmpval |= (ITAxes | ITCombination);
  
  /* Write value to MEMS INT2_CFR register */
  COMPASSACCELERO_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_INT2_CFG_A, tmpval);
}

/**
  * @brief  INT2 interrupt config
  * @param  ITCombination: Or or And combination
  *         ITAxes: axes to be enabled 
  * @retval None
  */
void LSM303DLHC_AccINT2InterruptDisable(uint8_t ITCombination, uint8_t ITAxes)
{  
  uint8_t tmpval = 0x00;
  
  /* Read INT2_CFR register */
  tmpval = COMPASSACCELERO_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_INT2_CFG_A);
  
  /* Disable the selected interrupt */
  tmpval &= ~(ITAxes | ITCombination);
  
  /* Write value to MEMS INT2_CFR register */
  COMPASSACCELERO_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_INT2_CFG_A, tmpval);
}

/**
  * @brief  Click interrupt enable
  * @param  ITClick: the selected interrupt to enable
  * @retval None
  */
void LSM303DLHC_AccClickITEnable(uint8_t ITClick)
{  
  uint8_t tmpval = 0x00;
  
  /* Read CLICK_CFR register */
  tmpval = COMPASSACCELERO_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_CLICK_CFG_A);
  
  /* Enable the selected interrupt */
  tmpval |= ITClick;
  
  /* Write value to MEMS CLICK CFG register */
  COMPASSACCELERO_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_CLICK_CFG_A, tmpval);
  
  /* Configure Click Threshold on Z axis */
  tmpval = 30;
  COMPASSACCELERO_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_CLICK_THS_A, tmpval);
  
  /* Configure Time Limit */
  tmpval = 0xAA;
  COMPASSACCELERO_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_TIME_LIMIT_A, tmpval);
  
  /* Configure Latency */
  COMPASSACCELERO_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_TIME_LATENCY_A, tmpval);
  
  /* Configure Click Window */
  tmpval = 0x32;
  COMPASSACCELERO_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_TIME_WINDOW_A, tmpval);
}

/**
  * @brief  Click interrupt disable
  * @param  ITClick: the selected click interrupt to disable
  * @retval None
  */
void LSM303DLHC_AccClickITDisable(uint8_t ITClick)
{  
  uint8_t tmpval = 0x00;
  
  /* Read CLICK_CFR register */
  tmpval = COMPASSACCELERO_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_CLICK_CFG_A);
  
  /* Disable the selected interrupt */
  tmpval &= ~ITClick;
  
  /* Write value to MEMS CLICK_CFR register */
  COMPASSACCELERO_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_CLICK_CFG_A, tmpval);
}

/**
  * @brief  Click on Z axis interrupt config
  * @param  None
  * @retval None
  */
void LSM303DLHC_AccZClickITConfig(void)
{  
  /* Configure low level IT config */
  COMPASSACCELERO_IO_ITConfig();
  
  /* Select click IT as INT1 interrupt */
  LSM303DLHC_AccIT1Enable(LSM303DLHC_IT1_CLICK);
  
  /* Enable High pass filter for click IT */
  LSM303DLHC_AccFilterClickCmd(LSM303DLHC_HPF_CLICK_ENABLE);
  
  /* Enable simple click IT on Z axis, */
  LSM303DLHC_AccClickITEnable(LSM303DLHC_Z_SINGLE_CLICK);
}






void LSM303DLHC_Init(void)
{
	LSM303DLHC_AccInit();
	//LSM303DLHC_MagInit();
	//LSM303DLHC_AccZClickITConfig();
}
/**0x1
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
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/     
