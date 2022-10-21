/**
  ******************************************************************************
  * @file    ai_dqnn_helpers.h
  * @author  AIS
  * @brief   Dqnn helpers routines header file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @verbatim
  @endverbatim
  ******************************************************************************
  */ 
#ifndef AI_DQNN_HELPERS_H
#define AI_DQNN_HELPERS_H
#pragma once


#include "ai_platform.h"
#include "ai_platform_interface.h"


#define AI_POPCNT_METHOD_VANILLA      (0)
#define AI_POPCNT_METHOD_SW_EMUL1     (1)
#define AI_POPCNT_METHOD_LUT          (3)
#define AI_POPCNT_METHOD_32           (AI_POPCNT_METHOD_SW_EMUL1)
#define AI_POPCNT_METHOD_8            (AI_POPCNT_METHOD_SW_EMUL1)
    
#define AI_DQNN_MSK_0001              (0x11111111)
#define AI_DQNN_MSK_00000001          (0x01010101)

extern ai_u8 AI_POPCNT_LUT[256];


AI_DECLARE_STATIC
ai_u32 popcnt_32_odd(ai_u32 v) {
   AI_ASSERT(v==(v & 0x55555555U))
   v = (v & 0x33333333U) + ((v >> 2) & 0x33333333U);
   v = ((v + (v >> 4)) & 0x0f0f0f0fU);
   return (v * 0x01010101U) >> 24;
}


//AI_INTERFACE_ENTRY
AI_DECLARE_STATIC
ai_u32 popcnt_32(ai_u32 v) 
{
  ai_u32 out = 0;
  
#if (AI_POPCNT_METHOD_32 == AI_POPCNT_METHOD_VANILLA)    
  for (ai_u32 i_pop = 0; i_pop < 32; i_pop++) 
  {
    if ((v >> i_pop) & (ai_u32) 1) 
    {
      out++;
    }
  }
#elif (AI_POPCNT_METHOD_32 == AI_POPCNT_METHOD_SW_EMUL1)   
  v = v - ((v >> 1) & 0x55555555U);
  v = (v & 0x33333333U) + ((v >> 2) & 0x33333333U);
  v = (v + (v >> 4)) & 0x0f0f0f0fU;
  out = (v * 0x01010101U) >> 24;
#elif (AI_POPCNT_METHOD_32 == AI_POPCNT_METHOD_LUT)
  ai_u8 *pv8 = (ai_u8 *)&v;
  out = AI_POPCNT_LUT[*pv8++];
  out += AI_POPCNT_LUT[*pv8++];
  out += AI_POPCNT_LUT[*pv8++];
  out += AI_POPCNT_LUT[*pv8];
#else
  v = v - ((v >> 1) & 0x55555555U);
  v = (v & 0x33333333U) + ((v >> 2) & 0x33333333U);
  v = (v + (v >> 4)) & 0x0f0f0f0fU;
  out = (v * 0x01010101U) >> 24;
#endif
  
  return out;
}


AI_DECLARE_STATIC
ai_u32 popcnt_8(ai_u8 v) 
{
  ai_u32 out = 0;
  
#if (AI_POPCNT_METHOD_8 == AI_POPCNT_METHOD_VANILLA)    
  for (ai_u32 i_pop = 0; i_pop < 8; i_pop++) 
  {
    if ((v >> i_pop) & (ai_u8) 1) 
    {
      out++;
    }
  }
#elif (AI_POPCNT_METHOD_8 == AI_POPCNT_METHOD_SW_EMUL1)   
  v = v - ((v >> 1) & 0x55U);
  v = (v & 0x33U) + ((v >> 2) & 0x33U);
  out = (v + (v >> 4)) & 0x0fU;
#elif (AI_POPCNT_METHOD_8 == AI_POPCNT_METHOD_LUT)
  ai_u8 *pv8 = &v;
  out = AI_POPCNT_LUT[*pv8++];
#else
  ai_u8 *pv8 = &v;
  out = AI_POPCNT_LUT[*pv8++];
#endif
  
  return out;
}


AI_API_DECLARE_BEGIN





AI_API_DECLARE_END

#endif /*AI_DQNN_HELPERS_H*/
