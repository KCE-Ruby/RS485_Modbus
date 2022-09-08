#ifndef COMMON_H
#define COMMON_H
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "iwdg.h"
#include "usart.h"
#include "gpio.h"


//------------------------- define functions --------------------------/*
void Serial_main(void);
void User_tx3_Once(void); //Send once, Uart3->FT232R, 115200 N81 
void User_rx3_Once(void);  //Receive once, Uart3->FT232R, 115200 N81 
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);

//------------------------- define functions --------------------------*/
//---------------------------- define ---------------------------------/*

//---------------------------- define ---------------------------------*/
//------------------------ typedef struct -----------------------------//
typedef struct	{
  uint8_t recvD[20],SendD[20];
  uint8_t rxD,txD;
}ur;
extern ur Ur1,Ur2,Ur3;

#endif
