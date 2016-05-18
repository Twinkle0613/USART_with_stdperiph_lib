#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include <stdint.h>

#define Input_Mode 0x0
#define USART_Enable ((uint16_t)0x2000)

void USART1_configuration(USART_InitTypeDef* usart, uint32_t BaudRate, uint16_t WordLength, uint16_t Parity)
{
  usart->USART_BaudRate = BaudRate;
  usart->USART_WordLength = WordLength;
  usart->USART_Parity = Parity ;
  usart->USART_StopBits = USART_StopBits_1;
  usart->USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  usart->USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_Init(USART1,usart);
}

void GPIOA_configuration(GPIO_InitTypeDef* gpio, uint16_t Pin, int Speed, int Mode){
    gpio->GPIO_Pin = Pin;
    gpio->GPIO_Speed = Speed;
    gpio->GPIO_Mode = Mode;
    GPIO_Init(GPIOA,gpio);
}

void enableUSART(USART_TypeDef* USARTx){
  USARTx->CR1 |= USART_Enable;
}

int main(void)
{

  /*******************GPIO configuration********************/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA,DISABLE);

  GPIO_InitTypeDef gpio;
  GPIOA_configuration(&gpio,GPIO_Pin_9,GPIO_Speed_50MHz,GPIO_Mode_AF_PP);   //TX
  GPIOA_configuration(&gpio,GPIO_Pin_10,Input_Mode,GPIO_Mode_IPU);  //RX

 // uint32_t checkGPIO_CRH = GPIOA->CRH;

  /*******************USART configuration*******************/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1,DISABLE);
  
  uint16_t data;
  USART_InitTypeDef usart;
  USART1_configuration(&usart,9600,USART_WordLength_8b,USART_Parity_No);
  enableUSART(USART1);

  //uint16_t checkUSART1_CR1= USART1->CR1;
  //uint16_t checkUSART1_CR2= USART1->CR2;
  //uint16_t checkUSART1_CR3= USART1->CR3;
  //uint16_t checkUSART1_BRR= USART1->BRR;


   
   while(1)
    {
      
	   if( USART_GetFlagStatus(USART1,USART_FLAG_TXE) ){
	    	  USART_SendData(USART1,'K');
	   }
     
	   if( USART_GetFlagStatus(USART1,USART_FLAG_RXNE) ){
	    	 data = USART_ReceiveData(USART1);
	   }
     
    }
}
