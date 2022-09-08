#include "usart.h"  //Uart1->RS485, Uart2->STLnk(inside),  Uart3->FT232R
#include "common.h"
#include <string.h>

/******* define function **********/
void Serial_main(void);
void User_Serial_init(void);
void User_tx1_Once(void); //Send once,    Uart1->RS485, 115200 N81  
void User_rx1_Once(void); //Receive once, Uart1->RS485, 115200 N81
void User_tx2_Once(void); //Send once,    Uart2->STLnk(inside), 115200 N81  
void User_rx2_Once(void); //Receive once, Uart2->STLnk(inside), 115200 N81
void User_tx3_Once(void); //Send once,    Uart3->FT232R, 115200 N81 
void User_rx3_Once(void); //Receive once, Uart3->FT232R, 115200 N81 
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);

/********* define var **********/
uint8_t seriCnt,uart2_isr_buf,uart2_ist_buf;

//temporary

/********* function codeing ************/
void Serial_main(void)  ///usually for test
{        
    User_Serial_init();    
		
    //User_rx1_Once();    //--ok RS232
    User_rx2_Once();    //--ok inside
    //User_rx3_Once();    //-- RS485


    while(1)
    {
        seriCnt++;
        HAL_IWDG_Refresh(&hiwdg);    //watchdog reset
    }
}

void User_Serial_init(void)
{
  //uart1_send array initial
  Ur1.SendD[0] = 0x02;
  Ur1.SendD[1] = 0x03;
  Ur1.SendD[2] = 0x00;
  Ur1.SendD[3] = 0x01;
  Ur1.SendD[4] = 0x00;
  Ur1.SendD[5] = 0x00;
  Ur1.SendD[6] = 0x00;
  Ur1.SendD[7] = 0x01;  
  Ur1.SendD[8] = 0x93;  
  Ur1.SendD[9] = 0x94;  
  //uart2_send array initial
  Ur2.SendD[0] = 0x02;
  Ur2.SendD[1] = 0x03;
  Ur2.SendD[2] = 0x00;
  Ur2.SendD[3] = 0x01;
  Ur2.SendD[4] = 0x00;
  Ur2.SendD[5] = 0x00;
  Ur2.SendD[6] = 0x00;
  Ur2.SendD[7] = 0x01;  
  Ur2.SendD[8] = 0x93;  
  Ur2.SendD[9] = 0x94;  
  //uart3_send array initial
  Ur3.SendD[0] = 0x31;
  Ur3.SendD[1] = 0x32;
  Ur3.SendD[2] = 0x33;
  Ur3.SendD[3] = 0x34;
  Ur3.SendD[4] = 0x35;
  Ur3.SendD[5] = 0x36;
  Ur3.SendD[6] = 0x37;
  Ur3.SendD[7] = 0x38;  
}

//Uart1 series 
void User_tx1_Once(void) //Send once, Uart1->RS485, 115200 N81  
{      
  HAL_GPIO_WritePin(RS485_CLK_GPIO_Port, RS485_CLK_Pin, GPIO_PIN_SET);   //RS485_CLK = 1
  //HAL_UART_Transmit_IT(&huart1,&Ur1.SendD[0],10);
	HAL_UART_Transmit(&huart1,&Ur1.SendD[0],10,2);
}
void User_rx1_Once(void)  //Receive once, Uart1->RS485, 115200 N81
{  
  HAL_GPIO_WritePin(RS485_CLK_GPIO_Port, RS485_CLK_Pin, GPIO_PIN_RESET); //RS485_CLK = 0
  HAL_UART_Receive_IT(&huart1,&Ur1.recvD[0],8);
}

//Uart2 series 
void User_tx2_Once(void) //Send once, Uart2->STLnk(inside), 115200 N81  
{        
  //HAL_UART_Transmit_IT(&huart2,&Ur2.SendD[0],10);
	HAL_UART_Transmit(&huart2,&Ur2.SendD[0],10,2);
}
void User_rx2_Once(void)  //Receive once, Uart2->STLnk(inside), 115200 N81
{  
  HAL_UART_Receive_IT(&huart2,&Ur2.recvD[0],8);
}

//Uart3 series
void User_tx3_Once(void) //Send once, Uart3->FT232R, 115200 N81  
{      
  HAL_GPIO_WritePin(RS485_CLK_GPIO_Port, RS485_CLK_Pin, GPIO_PIN_SET);   //RS485_CLK = 1
  //HAL_UART_Transmit_IT(&huart3,&Ur3.SendD[0],10);	
	HAL_UART_Transmit(&huart3,&Ur3.SendD[0],10,2);
}
void User_rx3_Once(void)  //Receive once, Uart3->FT232R, 115200 N81
{ 
  HAL_GPIO_WritePin(RS485_CLK_GPIO_Port, RS485_CLK_Pin, GPIO_PIN_RESET); //RS485_CLK = 0
  HAL_UART_Receive_IT(&huart3,&Ur3.recvD[0],8);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	
    if(huart == &huart1)  //undefine the receive funciton for uart2
	  {
      //User_tx1_Once();
      User_rx1_Once();
      Ur1.rxD++;
	  }
	  if(huart == &huart2)  //undefine the receive funciton for uart2
	  {
      //User_tx2_Once();
      User_rx2_Once();
      Ur2.rxD++;
	  }
	  else if(huart == &huart3)
	  {
      //User_tx3_Once();
      User_rx3_Once();
      Ur3.rxD++;
	  }  
	
}
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	/*
  	if(huart == &huart1)
	  {
      User_rx1_Once();
      Ur1.txD++;
	  }
	  if(huart == &huart2)
	  {
      User_rx2_Once();
      //HAL_UART_Receive_IT(&huart2,&Ur2.recvD[0],8);  //再開啓接收中斷
      Ur2.txD++;
	  }
	  else if(huart == &huart3)
	  {
      User_rx3_Once();
      Ur3.txD++;
	  }  
	*/
}
