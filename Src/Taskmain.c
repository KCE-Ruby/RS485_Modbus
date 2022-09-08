#include "main.h"
#include "iwdg.h"
#include "usart.h"
#include "gpio.h"
#include "common.h"

/******** to do list *********
1. inside
2. RS232
3. RS485
4. Uoi1.SendD[8] HAL_UART_Transmit 8bit once a time
5. Uoi1.SendD[8] HAL_UART_Transmit loop for 8 times
******* to do list *********/

/******* define function **********/
void Taskmain(void);
void Serial_main(void);

/********* define var **********/
uint8_t mainCnt,i;
ur Ur1,Ur2,Ur3;  //struct for Uart-> rx、tx、sendD[8]、recvD[8]
uint8_t TempArr[8];
uint32_t strTonum;

//temporary
//uint8_t Tnum,k;
/********* function codeing ************/
void Taskmain(void)
{      

  //HAL_GPIO_WritePin(RS485_CLK_GPIO_Port, RS485_CLK_Pin, GPIO_PIN_SET);   //RS485_CLK = 1
  //HAL_Delay(300); 
  //HAL_GPIO_WritePin(RS485_CLK_GPIO_Port, RS485_CLK_Pin, GPIO_PIN_RESET);   //RS485_CLK = 0
  
  //User_tx3_Once();
  i = 255;
  //Uart_PutNum(mainCnt);
    Serial_main();

    while(1){
        mainCnt++;
        HAL_IWDG_Refresh(&hiwdg);    //watchdog reset
    }
  
}
