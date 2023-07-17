/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */
/* i2c - Example

   For other examples please check:
   https://github.com/espressif/esp-idf/tree/master/examples

   See README.md file to get detailed usage of this example.

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "QMA.h"

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
