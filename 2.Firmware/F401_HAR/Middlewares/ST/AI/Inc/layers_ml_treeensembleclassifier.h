/**
  ******************************************************************************
  * @file    layers_svmregressor.h
  * @author  AIS
  * @brief   header file of AI platform SVM Regressor datatypes
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

#ifndef LAYERS_TREE_ENSEMBLE_CLASSIFIER_H
#define LAYERS_TREE_ENSEMBLE_CLASSIFIER_H
#pragma once

#include "layers_common.h"
#include "layers_nl.h"

/*!
 * @defgroup layers_svmreg Layers Definitions
 * @brief definition 
 *
 */

AI_API_DECLARE_BEGIN

/* Type of condition in the TreeEnsembleClassifier*/
typedef enum
{
  AI_TREE_ENSEMBLE_CLASSIFIER_BRANCH_LT_IDX = 0,
  AI_TREE_ENSEMBLE_CLASSIFIER_BRANCH_LEQ_IDX,
  AI_TREE_ENSEMBLE_CLASSIFIER_BRANCH_EQ_IDX,
  AI_TREE_ENSEMBLE_CLASSIFIER_BRANCH_END,
} ai_tree_ensenble_classifier_branch_e;

typedef AI_ALIGNED_TYPE(struct, 4) ai_layer_tree_ensemble_classifier_ {
    AI_LAYER_COMMON_FIELDS_DECLARE
    func_nl nl_func;
    uint8_t all_weights_are_positive;
    ai_float nodes_values_scale;
    ai_float nodes_values_offset;
    ai_float class_weights_scale;
    ai_float class_weights_offset;
} ai_layer_tree_ensemble_classifier;



/******************************************************************************/
/*  Forward Functions Section                                                 */
/******************************************************************************/

/*!
 * @brief Decodes the TreeEnsembleClassifier ML operator.
 * @ingroup layers_svmreg
 * @param layer tree ensemble classifier layer
 */
AI_INTERNAL_API
void forward_tree_ensemble_classifier(ai_layer *pLayer);


AI_API_DECLARE_END

#endif    /*LAYERS_SVMREGRESSOR_H*/
