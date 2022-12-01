#include <EloquentTinyML.h>
#include "nn_model.h"
#include "math.h"

#define NUMBER_OF_INPUTS 1
#define NUMBER_OF_OUTPUTS 1
#define TENSOR_ARENA_SIZE 2*1024

// 生成Eloquent对象
Eloquent::TinyML::TfLite<NUMBER_OF_INPUTS, NUMBER_OF_OUTPUTS, TENSOR_ARENA_SIZE> ml;

// 设置led的引脚为2
static const uint8_t LED_BUILTIN = 2;
static const uint8_t x_num = 500;
float x[x_num];

// 初始化串口，led引脚，加载神经网络模型以及0-pi上等间隔采样500个x的值
void setup() {
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    ml.begin(model_data);
    for(int i = 0; i <= x_num -1; i++){
      x[i] = 3.14 * i / x_num;
     }
}

// 主循环，for循环中循环读取数组中x的值并使用神经网络推理预测值，使用串口输出x以及对应的真实值和预测值，同时将预测值输出PWM波到led引脚
void loop() {
    for(int i = 0; i <= x_num-1; i++){
      float input[1] = { x[i] };
      float predicted = ml.predict(input);
      float y = sin(x[i]);
            
      Serial.print("sin(");
      Serial.print(x[i]);
      Serial.print(") = ");
      Serial.print(y);
      Serial.print("\t predicted: ");
      Serial.println(predicted);

      analogWrite(LED_BUILTIN, predicted * 255);
      delay(10);
    }
}
