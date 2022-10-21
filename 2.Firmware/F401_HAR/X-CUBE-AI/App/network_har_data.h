
/**
  ******************************************************************************
  * @file    network_har_data.h
  * @author  AST Embedded Analytics Research Platform
  * @date    Fri Oct 21 15:29:32 2022
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

#ifndef NETWORK_HAR_DATA_H
#define NETWORK_HAR_DATA_H
#pragma once

#include "network_har_config.h"
#include "ai_platform.h"

#define AI_NETWORK_HAR_DATA_CONFIG               (NULL)


#define AI_NETWORK_HAR_DATA_ACTIVATIONS_SIZES \
  { 24576, }
#define AI_NETWORK_HAR_DATA_ACTIVATIONS_SIZE     (24576)
#define AI_NETWORK_HAR_DATA_ACTIVATIONS_COUNT    (1)
#define AI_NETWORK_HAR_DATA_ACTIVATION_1_SIZE    (24576)



#define AI_NETWORK_HAR_DATA_WEIGHTS_SIZES \
  { 201304, }
#define AI_NETWORK_HAR_DATA_WEIGHTS_SIZE         (201304)
#define AI_NETWORK_HAR_DATA_WEIGHTS_COUNT        (1)
#define AI_NETWORK_HAR_DATA_WEIGHT_1_SIZE        (201304)



AI_DEPRECATED
#define AI_NETWORK_HAR_DATA_ACTIVATIONS(ptr_)  \
  ai_network_har_data_activations_buffer_get(AI_HANDLE_PTR(ptr_))

AI_DEPRECATED
#define AI_NETWORK_HAR_DATA_WEIGHTS(ptr_)  \
  ai_network_har_data_weights_buffer_get(AI_HANDLE_PTR(ptr_))


AI_API_DECLARE_BEGIN

/*!
 * @brief Get network activations buffer initialized struct.
 * @ingroup network_har_data
 * @param[in] ptr a pointer to the activations array storage area
 * @return an ai_buffer initialized struct
 */
AI_DEPRECATED
AI_API_ENTRY
ai_buffer ai_network_har_data_activations_buffer_get(const ai_handle ptr);

/*!
 * @brief Get network weights buffer initialized struct.
 * @ingroup network_har_data
 * @param[in] ptr a pointer to the weights array storage area
 * @return an ai_buffer initialized struct
 */
AI_DEPRECATED
AI_API_ENTRY
ai_buffer ai_network_har_data_weights_buffer_get(const ai_handle ptr);

/*!
 * @brief Get network weights array pointer as a handle ptr.
 * @ingroup network_har_data
 * @return a ai_handle pointer to the weights array
 */
AI_DEPRECATED
AI_API_ENTRY
ai_handle ai_network_har_data_weights_get(void);


/*!
 * @brief Get network params configuration data structure.
 * @ingroup network_har_data
 * @return true if a valid configuration is present, false otherwise
 */
AI_API_ENTRY
ai_bool ai_network_har_data_params_get(ai_network_params* params);


AI_API_DECLARE_END

#endif /* NETWORK_HAR_DATA_H */

