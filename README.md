# QMA I2C驱动

## 基本配置

esp-idf 是最新的分支

开发板型号为esp32c3



## 重要参数

```c
I2C_MASTER_SCL_IO    //i2c时钟引脚
    
I2C_MASTER_SDA_IO    //i2c数据引脚
    
QMA7981_ADDR    	//QMA7981地址
    
QMA7981_DXM_ADDR    //X轴寄存器地址

QMA7981_MODE_ADDR   //模式地址 设置成活动状态 以及两种相关的通信速率

QMA7981_RANGE_ADDR   //量程地址   设置不同的量程  可以有5种不同的情况

QMA7981_MODE_100K_cmd      //模式命令  设置成活动状态 速率100k
    
QMA7981_RAG_2g_cmd      //量程命令  设置成2g的量程 
```





## 重要函数

```c
esp_err_t i2c_master_init(void);  //I2c初始化函数

esp_err_t QMA7981_setMode(uint8_t cmd) //模式设置函数 里面是模式命令

esp_err_t QMA7981_setAcc(uint8_t cmd)  //量程设置函数 里面是量程命令    
    
float QMA7981_read_DXM();   //读取X轴加速度    

float QMA7981_read_DYM();   //读取Y轴加速度   

float QMA7981_read_DZM();   //读取Z轴加速度   

esp_err_t QMA7981_register_write_byte(uint8_t reg_addr, uint8_t cmd); //I2C写入命令函数

esp_err_t QMA7981_register_read(uint8_t reg_addr, uint8_t *data, size_t len);//i2c从特定寄存器读取数据函数
```





## 测试流程

首先初始化i2c ,然后设置相关模型以及量程

```c
ESP_ERROR_CHECK(i2c_master_init());

ESP_ERROR_CHECK(QMA7981_setMode(QMA7981_MODE_100K_cmd));//设置为active模式
ESP_ERROR_CHECK(QMA7981_setAcc(QMA7981_RAG_2g_cmd));
```



然后读取 X，Y，Z三个轴的加速度

```c
float X_AXIS_A;
float Y_AXIS_A;
float Z_AXIS_A;
X_AXIS_A = QMA7981_read_DXM() ;
Y_AXIS_A = QMA7981_read_DYM() ;
Z_AXIS_A = QMA7981_read_DZM() ;
```





### 测试代码如下

```c
void app_main(void)
{

    float X_AXIS_A;
    float Y_AXIS_A;
    float Z_AXIS_A;

    ESP_ERROR_CHECK(i2c_master_init());

    ESP_ERROR_CHECK(QMA7981_setMode(QMA7981_MODE_100K_cmd));	//设置为active模式
    ESP_ERROR_CHECK(QMA7981_setAcc(QMA7981_RAG_2g_cmd));

    while(1)
    {	   
        X_AXIS_A = QMA7981_read_DXM() ;
        Y_AXIS_A = QMA7981_read_DYM() ;
        Z_AXIS_A = QMA7981_read_DZM() ;
        printf("X_A = %.3f g, Y_A = %.3f g, Z_A = %.3f g. \n", X_AXIS_A, Y_AXIS_A, Z_AXIS_A);
        printf("\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

```

