# HAR-ON-STM32F401C
## 概述
* 在STM32F401C-DISCO开发板上部署轻量级的卷积神经网络(CNN)，进行人体活动识别(HAR)，识别的姿态包括步行、慢跑、上楼、下楼、站姿、坐姿。开发板正面朝下放置在右前裤兜中进行测试，系统读取板载LSM303DLHC加速度计输出的三轴加速度数据（需要4.5s），通过网络模型推理出用户此时的活动状态（给出6种状态的可能性百分数）并且输出可能性最大的状态的标签作为系统最终预测结果。
 
* 数据集使用无线传感器数据挖掘（WISDM）实验室发布的Actitracker数据集[[链接]](http://www.cis.fordham.edu/wisdm/dataset.php)，该数据库中提供的数据是以20Hz的采样率的，从36个用户的口袋中使用智能手机收集的。数据包含x、y和z轴的加速度值，而用户在受控环境中执行六种不同的活动：步行、慢跑、上楼、下楼、站姿、坐姿。
 
* 网络模型参考了[Shahnawax/HAR-CNN-Keras](https://github.com/Shahnawax/HAR-CNN-Keras)的设计，将数据集按照窗口长度90，步长45进行分割，形成24141个样本和标签值，这些样本和标签被分为80%训练集和20%测试集。训练集进一步分成具有相同分布的训练和验证数据。这里为了适配板载资源减少了全连接层的神经元个数，使测试集上的准确率从92.1%降低为85%，准确率有待提高，后续会选择资源更丰富的MCU以及从板载加速度传感器搜集数据创建自己的运动数据集，模型的示意图和测试脚本生成的混淆矩阵如下：

<p align="center">
<img width="676" height="400" src="https://github.com/LiangZai-Embedded/HAR-ON-STM32F401C/blob/main/1.Modelfile/model/structure.png">
</p>

<p align="center">
<img width="640" height="480" src="https://github.com/LiangZai-Embedded/HAR-ON-STM32F401C/blob/main/1.Modelfile/evaluate/Confusion%20Matrix.png">
</p>

* 最终部署在STM32F401C-DISCO开发板上C-Model模型是原模型文件`model.h5`导入`X-CUBE-AI`插件后，经过8倍压缩后生成的。

## 文件
### 1.Modelfile
* `model` 文件夹包含`actitracter_raw.csv`数据集，人类活动识别（HAR）模型的Keras实现脚本`HAR.py`,数据集清洗处理之后生成的`segments.npy`,`labels.npy`（方便脚本直接导入)，脚本生成的测试集`testData.npy`,测试集的标签`groundTruth.npy`，`structure.png`模型结构示意图以及训练好的模型文件`model.h5`
 
* `evaluate`文件夹包含测试脚本`evaluate_model.py`，评估网络模型在testData上的性能，以及脚本生成的混淆矩阵`Confusion Matrix.png`

* `cubeai_validation`文件夹包含脚本`validation.py`,将测试集`testData.npy`,测试集的标签`groundTruth.npy`转换为用于验证STM32Cube.AI生成的C模型的csv文件`testx_cubeai.csv`,`testy_cubeai.csv`
### 2.Firmware
* 包括STM32F401C-DISCO开发板工程文件夹`F401_HAR`以及原理图`F401_DISCO.pdf`

### 3.SensorData
* WISDM官网数据和相关文章 [[链接]](http://www.cis.fordham.edu/wisdm/dataset.php)

## 工具
* `STM32CubeIDE V1.10.1`
* `STM32 X-CUBE-AI V7.1.0`
* `STM32CubeF4 V1.27.0
* `python3.8.13`
* `keras2.4.3`
* `scipy`
* `numpy`
* `matplotlib`
* `sklearn`
