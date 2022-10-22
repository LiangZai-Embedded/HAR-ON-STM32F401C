# HAR-ON-STM32F401C
## 概述
* 在STM32F401C-DISCO开发板上部署一个轻量级卷积神经网络(CNN)，进行人体活动识别(HAR)，识别姿态包括步行、慢跑、上楼、下楼、站姿、坐姿。开发板正面朝下放置在右前裤兜中，系统板载LSM303DLHC加速度计，通过读取三轴加速度数据和模型处理进行用户活动的识别。 
 
* 数据集使用无线传感器数据挖掘（WISDM）实验室发布的Actitracker数据集[[链接]](http://www.cis.fordham.edu/wisdm/dataset.php)，该数据库中提供的数据是以20Hz的采样率从36个用户的口袋中使用智能手机收集的。数据包含x、y和z轴的加速度值，而用户在受控环境中执行六种不同的活动：步行、慢跑、上楼、下楼、站姿、坐姿。
 
* 网络模型参考了[Shahnawax](https://github.com/Shahnawax/HAR-CNN-Keras)HAR-CNN-Keras的设计，将数据集进行窗口长度90，步长45，进行分割，形成24141个样本和标签值，这些样本和标签被分为两个子组，trainData和testData，比率分别为80%和20%。训练数据进一步分成具有相同分布的训练和验证数据。这里为了适配板载资源减少了全连接层的神经元个数，使测试集上的准确率从92.1%降低为85%。模型的示意图和测试脚本生成的混淆矩阵如下：

<p align="center">
<img width="971" height="574" src="https://github.com/LiangZai-Embedded/HAR-ON-STM32F401C/blob/main/1.Modelfile/model/structure.png">
</p>

<p align="center">
<img width="640" height="480" src="https://github.com/LiangZai-Embedded/HAR-ON-STM32F401C/blob/main/1.Modelfile/evaluate/Confusion%20Matrix.png">
</p>



## 文件
### 1.Modelfile
* `model` 文件夹包含`actitracter_raw.csv`数据集，人类活动识别（HAR）模型的Keras实现脚本`HAR.py`,数据集清洗处理之后生成的`segments.npy`,`labels.npy`（方便脚本直接导入)，脚本生成的测试集`testData.npy`,测试集的标签`groundTruth.npy`，`structure.png`模型结构示意图以及训练好的模型文件`model.h5`
 
* `evaluate`文件夹包含测试脚本`evaluate_model.py`，评估网络模型在testData上的性能，以及脚本生成的混淆矩阵`Confusion Matrix.png`

* `cubeai_validation`文件夹包含脚本`validation.py`,将测试集`testData.npy`,测试集的标签`groundTruth.npy`转换为用于验证STM32Cube.AI生成的C模型的csv文件`testx_cubeai.csv`,`testy_cubeai.csv`
### 2.Firmware
* 包括STM32F401C-DISCO开发板工程文件夹`F401_HAR`以及原理图`F401_DISCO.pdf`

### 3.SensorData
* WISDM官网数据和相关文章 [[链接]](http://www.cis.fordham.edu/wisdm/dataset.php)


