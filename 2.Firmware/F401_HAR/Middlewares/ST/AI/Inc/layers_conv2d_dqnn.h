/**
  ******************************************************************************
  * @file    layers_conv2d_dqnn.h
  * @author  AIS
  * @brief   header file of AI platform DQNN conv datatypes
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
#ifndef LAYERS_CONV2D_DQNN_H
#define LAYERS_CONV2D_DQNN_H
#pragma once

#include "layers_common.h"
#include "layers_conv2d.h"

/*!
 * @defgroup layers_conv2d_dqnn Layers Definitions
 * @brief definition 
 *
 */

AI_API_DECLARE_BEGIN


#define AI_DQNN_PAD_1_KEY     (1)
#define AI_DQNN_PAD_M1_KEY    (-1)
#define AI_DQNN_PAD_0_KEY     (0)
#define AI_DQNN_PAD_1_VALUE   (0x0)
#define AI_DQNN_PAD_M1_VALUE  (0xFFFFFFFF)
#define AI_DQNN_PAD_0_VALUE   (0x2)


/*!
 * @struct ai_layer_conv2d_dqnn
 * @ingroup layers_conv2d_dqnn
 * @brief conv2d_dqnn layer
 *
 * @ref forward_conv2d_i1o1w1
 */
typedef AI_ALIGNED_TYPE(struct, 4) ai_layer_conv2d_dqnn_ {
  AI_LAYER_CONV2D_FIELDS_DECLARE
  ai_i32  pad_value;
} ai_layer_conv2d_dqnn;


ai_u32 *
st_i8o1w8_mat_mult_kernel_dorefa(const ai_u8 *pA,
                                 const ai_i16 *pInBuffer,
                                 const ai_i32 *pBufferWtRank1, 
                                 const ai_u32 ch_im_out,
                                 const ai_i32 numCol_A,
                                 const ai_i32 *pThreshold, 
                                 ai_u32 *pOut);

ai_u32 *
st_i8o1w8_mat_mult_kernel(const ai_i8 *pA,
                          const ai_i16 *pInBuffer,
                          const ai_i32 *pBufferWtRank1, 
                          const ai_u32 ch_im_out,
                          const ai_i32 numCol_A,
                          const ai_i32 *pThreshold, 
                          ai_u32 *pOut);


/******************************************************************************/
/*  Forward Functions Section                                                 */
/******************************************************************************/

/*!
 * @brief Handles point wise convolution with binary input, binary output and 
 *        binary weights
 * @ingroup layers_conv2d_dqnn
 * @param layer conv2d_dqnn layer
 */
AI_INTERNAL_API
void forward_pw_i1o1w1(ai_layer *pLayer);


/*!
 * @brief Handles point-wise convolution with binary input, float32 output 
 *        and binary weights
 * @ingroup layers_conv2d_dqnn
 * @param layer conv2d_dqnn layer
 */
AI_INTERNAL_API
void forward_pw_i1of32w1(ai_layer *pLayer);


/*!
 * @brief Handles 2D convolution with binary input, binary output and 
 *        binary weights
 * @ingroup layers_conv2d_dqnn
 * @param layer conv2d_dqnn layer
 */
AI_INTERNAL_API
void forward_conv2d_i1o1w1(ai_layer *pLayer);

/*!
 * @brief Handles 2D convolution with binary input, binary output and 
 *        binary weights - with 0 padding (QKeras like)
 * @ingroup layers_conv2d_dqnn
 * @param layer conv2d_dqnn layer
 */
AI_INTERNAL_API
void forward_conv2d_i1o1w1_pad0(ai_layer *pLayer);

/*!
 * @brief Handles 2D convolution with binary input, binary output and 
 *        binary weights - with +1/-1 padding (Larq like)
 * @ingroup layers_conv2d_dqnn
 * @param layer conv2d_dqnn layer
 */
AI_INTERNAL_API
void forward_conv2d_i1o1w1_pad1(ai_layer *pLayer);


/*!
 * @brief Handles 2D convolution with 8-bits quantized Input and weights and 
 *        binary output
 * @ingroup layers_conv2d_dqnn
 * @param layer conv2d_dqnn layer
 */
AI_INTERNAL_API
void forward_conv2d_i8o1w8(ai_layer *pLayer);

/*!
 * @brief Handles 2D convolution with 8-bits quantized Input and weights and 
 *        binary output - quantized with DoReFa SotA quantizer
 * @ingroup layers_conv2d_dqnn
 * @param layer conv2d_dqnn layer
 */
AI_INTERNAL_API
void forward_conv2d_i8o1w8_dorefa(ai_layer *pLayer);

/*!
 * @brief Handles depth-wise convolution with binary input, binary output and 
 *        binary weights
 * @ingroup layers_conv2d_dqnn
 * @param layer conv2d_dqnn layer
 */
AI_INTERNAL_API
void forward_dw_i1o1w1(ai_layer *pLayer);

/*!
 * @brief Handles depth-wise convolution with binary input, binary output and 
 *        binary weights - with 0 padding (QKeras like)
 * @ingroup layers_conv2d_dqnn
 * @param layer conv2d_dqnn layer
 */
AI_INTERNAL_API
void forward_dw_i1o1w1_pad0(ai_layer *pLayer);

/*!
 * @brief Handles depth-wise convolution with binary input, binary output and 
 *        binary weights - with +1/-1 padding (Larq like)
 * @ingroup layers_conv2d_dqnn
 * @param layer conv2d_dqnn layer
 */
AI_INTERNAL_API
void forward_dw_i1o1w1_pad1(ai_layer *pLayer);

/*!
 * @brief Handles 2D convolution with 8-bits quantized Input and output and 
 *        binary weights
 * @ingroup layers_conv2d_dqnn
 * @param layer conv2d_dqnn layer
 */
AI_INTERNAL_API
void forward_conv2d_i8o8w1(ai_layer *pLayer);



AI_API_DECLARE_END

#endif    /*LAYERS_CONV2D_DQNN_H*/
