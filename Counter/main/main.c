/* 
    Autor : Halysson Junior
    Data: 01/04/21
    Descrição:
    Neste exemplo utilizou-se dois botões táctis (entradas digitais) para realizar a contagem para cima e para baixo uma váriavel
    
*/
    
    

// Inclusão arquivos de cabeçalho

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"



// Definições de Pinos
#define BTN_UP   15
#define BTN_DOWN 14

// Definição de habilitação (PULLUP / PULLDOWN)
#define PULLUP
// #define PULLDOWN (Para habilitar pulldown descomente aqui e comente -> " #define PULLUP ")

// Definições de estado lógico (caso altere para pulldown, deve-se inverter os estado lógicos)
#define ON 1
#define OFF 0

void app_main(void){  // Main

 gpio_pad_select_gpio(BTN_UP);  
 gpio_set_direction(BTN_UP,GPIO_MODE_INPUT); // Configura botão up como entrada digital

 
 
 gpio_pad_select_gpio(BTN_DOWN);  
 gpio_set_direction(BTN_DOWN,GPIO_MODE_INPUT); // Configura botão down como entrada digital
 
  #ifdef PULLDOWN // Habilita pulldown 
  
   gpio_pulldown_en(BTN_UP);
   gpio_pullup_dis(BTN_UP);  
   
   gpio_pulldown_en(BTN_DOWN);
   gpio_pullup_dis(BTN_DOWN);
  #endif
  
  #ifdef PULLUP  // Habilita pullup
  
  gpio_pullup_en(BTN_UP);
  gpio_pulldown_dis(BTN_UP); 
  
   gpio_pullup_en(BTN_DOWN);
  gpio_pulldown_dis(BTN_DOWN);

  #endif

// Váriavel Local
bool last_state_btn_up = 0; // Armazena o último estado do botão  up     
bool last_state_btn_down = 0; // Armazena o último estado do botão down       
unsigned int counter  = 0;  // Armazena o valor da contagem
   
    while (1) { // Loop
     
    // Váriavel Local  
     bool state_btn_up = gpio_get_level(BTN_UP); // Leitura do botão up
     bool state_btn_down = gpio_get_level(BTN_DOWN); // Leitura botão down


    if(!state_btn_up && state_btn_up != last_state_btn_up) {
        counter ++;
        printf("Counter: %d\n", counter);             // Mostra informação no monitor "LED LIGADO"
          
      }
      
      last_state_btn_up = state_btn_up;

    if(!state_btn_down && state_btn_down != last_state_btn_down) {
        counter --;
        printf("Counter: %d\n", counter);             // Mostra informação no monitor "LED LIGADO"
          
      }
      last_state_btn_down = state_btn_down;
          
      vTaskDelay(10/ portTICK_PERIOD_MS);    // Rotina de Delay de 1 segundo
      fflush(stdout);                       // Descarrega os buffers de saída de dados   

    }// endLoop

}// endMain
