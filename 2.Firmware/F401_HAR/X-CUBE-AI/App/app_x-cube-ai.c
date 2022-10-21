
/**
  ******************************************************************************
  * @file    app_x-cube-ai.c
  * @author  X-CUBE-AI C code generator
  * @brief   AI program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

 /*
  * Description
  *   v1.0 - Minimum template to show how to use the Embedded Client API
  *          model. Only one input and one output is supported. All
  *          memory resources are allocated statically (AI_NETWORK_XX, defines
  *          are used).
  *          Re-target of the printf function is out-of-scope.
  *   v2.0 - add multiple IO and/or multiple heap support
  *
  *   For more information, see the embeded documentation:
  *
  *       [1] %X_CUBE_AI_DIR%/Documentation/index.html
  *
  *   X_CUBE_AI_DIR indicates the location where the X-CUBE-AI pack is installed
  *   typical : C:\Users\<user_name>\STM32Cube\Repository\STMicroelectronics\X-CUBE-AI\7.1.0
  */

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#if defined ( __ICCARM__ )
#elif defined ( __CC_ARM ) || ( __GNUC__ )
#endif

/* System headers */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include "app_x-cube-ai.h"
#include "main.h"
#include "ai_datatypes_defines.h"
#include "network_har.h"
#include "network_har_data.h"

/* USER CODE BEGIN includes */




/* USER CODE END includes */

/* IO buffers ----------------------------------------------------------------*/

#if !defined(AI_NETWORK_HAR_INPUTS_IN_ACTIVATIONS)
AI_ALIGNED(4) ai_i8 data_in_1[AI_NETWORK_HAR_IN_1_SIZE_BYTES];
ai_i8* data_ins[AI_NETWORK_HAR_IN_NUM] = {
data_in_1
};
#else
ai_i8* data_ins[AI_NETWORK_HAR_IN_NUM] = {
NULL
};
#endif

#if !defined(AI_NETWORK_HAR_OUTPUTS_IN_ACTIVATIONS)
AI_ALIGNED(4) ai_i8 data_out_1[AI_NETWORK_HAR_OUT_1_SIZE_BYTES];
ai_i8* data_outs[AI_NETWORK_HAR_OUT_NUM] = {
data_out_1
};
#else
ai_i8* data_outs[AI_NETWORK_HAR_OUT_NUM] = {
NULL
};
#endif

/* Activations buffers -------------------------------------------------------*/

AI_ALIGNED(32)
static uint8_t pool0[AI_NETWORK_HAR_DATA_ACTIVATION_1_SIZE];

ai_handle data_activations0[] = {pool0};

/* AI objects ----------------------------------------------------------------*/

static ai_handle network_har = AI_HANDLE_NULL;

static ai_buffer* ai_input;
static ai_buffer* ai_output;

static void ai_log_err(const ai_error err, const char *fct)
{
  /* USER CODE BEGIN log */
  if (fct)
    printf("TEMPLATE - Error (%s) - type=0x%02x code=0x%02x\r\n", fct,
        err.type, err.code);
  else
    printf("TEMPLATE - Error - type=0x%02x code=0x%02x\r\n", err.type, err.code);

  do {} while (1);
  /* USER CODE END log */
}

static int ai_boostrap(ai_handle *act_addr)
{
  ai_error err;

  /* Create and initialize an instance of the model */
  err = ai_network_har_create_and_init(&network_har, act_addr, NULL);
  if (err.type != AI_ERROR_NONE) {
    ai_log_err(err, "ai_network_har_create_and_init");
    return -1;
  }

  ai_input = ai_network_har_inputs_get(network_har, NULL);
  ai_output = ai_network_har_outputs_get(network_har, NULL);

#if defined(AI_NETWORK_HAR_INPUTS_IN_ACTIVATIONS)
  /*  In the case where "--allocate-inputs" option is used, memory buffer can be
   *  used from the activations buffer. This is not mandatory.
   */
  for (int idx=0; idx < AI_NETWORK_HAR_IN_NUM; idx++) {
	data_ins[idx] = ai_input[idx].data;
  }
#else
  for (int idx=0; idx < AI_NETWORK_HAR_IN_NUM; idx++) {
	  ai_input[idx].data = data_ins[idx];
  }
#endif

#if defined(AI_NETWORK_HAR_OUTPUTS_IN_ACTIVATIONS)
  /*  In the case where "--allocate-outputs" option is used, memory buffer can be
   *  used from the activations buffer. This is no mandatory.
   */
  for (int idx=0; idx < AI_NETWORK_HAR_OUT_NUM; idx++) {
	data_outs[idx] = ai_output[idx].data;
  }
#else
  for (int idx=0; idx < AI_NETWORK_HAR_OUT_NUM; idx++) {
	ai_output[idx].data = data_outs[idx];
  }
#endif

  return 0;
}

static int ai_run(void)
{
  ai_i32 batch;

  batch = ai_network_har_run(network_har, ai_input, ai_output);
  if (batch != 1) {
    ai_log_err(ai_network_har_get_error(network_har),
        "ai_network_har_run");
    return -1;
  }

  return 0;
}

/* USER CODE BEGIN 2 */
bool ai_proc_flag = RESET;
float samples[270] = {0};



void acquire_and_process_data(void)
{
	ai_i8* ptr = data_in_1;

	for(uint16_t i = 0;i<270;i++)
	{
		memcpy(ptr, (ai_i8*)&samples[i],4);
		ptr += 4;
	}

}



void post_process(void)
{
	uint8_t buf[30];
	float possibility[6];
	const char* labels[] = {"Downstairs","Jogging","Sitting","Standing","Upstairs","Walking"};
	uint8_t max_possibility_index = 0;

	MY_PRINTF(buf,"\r\n-----------------------------------\r\n");

	for(uint8_t i = 0;i < 6;i++)
	{
		possibility[i] = *(float*)&data_out_1[i*4];

		MY_PRINTF(buf,"%.2f ",possibility[i]);
		if(possibility[max_possibility_index]<possibility[i])
			max_possibility_index = i;

	}

	MY_PRINTF(buf,"%s %.2f%%\r\n",labels[max_possibility_index],possibility[max_possibility_index]*100.0f);
	MY_PRINTF(buf,"-----------------------------------\r\n");

}










void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	float buf_acc[3];
	uint8_t buf[30];
	static uint16_t index;
	static uint16_t cnt;
	float ax,ay,az;

	LSM303DLHC_AccReadXYZ(buf_acc);
	ax = -buf_acc[1];
	ay = -buf_acc[0];
	az = buf_acc[2];

	if(ai_proc_flag==RESET)
	{
		samples[index++] = ax;
		samples[index++] = ay;
		samples[index++] = az;

		MY_PRINTF(buf,"%d %.1f  %.1f  %.1f\r\n",++cnt,ax,ay,az);

	}

	if(index==270)
	{
		ai_proc_flag = SET;
	}


}




/* USER CODE END 2 */

/* Entry points --------------------------------------------------------------*/

void MX_X_CUBE_AI_Init(void)
{
    /* USER CODE BEGIN 5 */
	ai_boostrap(data_activations0);
    /* USER CODE END 5 */
}

void MX_X_CUBE_AI_Process(void)
{
    /* USER CODE BEGIN 6 */

	if(ai_proc_flag==SET)
	{
		acquire_and_process_data();
		ai_run();
		post_process();

		while(1);
	}


    /* USER CODE END 6 */
}
#ifdef __cplusplus
}
#endif









