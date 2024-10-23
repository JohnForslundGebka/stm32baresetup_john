#include <stdint.h>

#define PERIPH_BASE 		(0x40000000UL)
#define AHB1PERIPH_OFFSET   (0x00020000UL)
#define AHB1PERIPH_BASE		(PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOA_OFFSET		(0x0UL)
#define GPIOC_OFFSET		(0x0800UL)

#define RCC_OFFSET			(0x3800UL)

#define AHB1ENR_OFFSET		(0x30UL)

#define GPIOA_BASE			(AHB1PERIPH_BASE + GPIOA_OFFSET)
#define GPIOC_BASE			(AHB1PERIPH_BASE + GPIOC_OFFSET)
#define RCC_BASE			(AHB1PERIPH_BASE + RCC_OFFSET)

#define OD_R_OFFSET			(0x14UL)
#define ID_R_OFFSET			(0x10UL)
#define PUPD_R_OFFSET       (0x0CUL)  // Offset for PUPDR register


#define RCC_AHB1ENR_R	    (*(volatile unsigned int *)(RCC_BASE + AHB1ENR_OFFSET))

#define MODE_R_OFFSET		(0x00UL)
#define GPIOA_MODE_R		(*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET))
#define GPIOC_MODE_R		(*(volatile unsigned int *)(GPIOC_BASE + MODE_R_OFFSET))
#define GPIOC_PUPD_R        (*(volatile unsigned int *)(GPIOC_BASE + PUPD_R_OFFSET))  // Access pull-up/down register

#define GPIOA_OD_R			(*(volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET))
#define GPIOC_ID_R			(*(volatile unsigned int *)(GPIOC_BASE + ID_R_OFFSET))



#define GPIOAEN				(1UL<<0)
#define GPIOCEN				(1UL<<2)
#define GPIO5_OUTPUT_MODE	(1UL<<10)



#define PIN5_HIGH			(1UL<<5)
#define LED_ON				(PIN5_HIGH)

#define BUTTON_PIN_13_MASK	(1U<<13)





int main(void){

	//Enable clock to GPIOA
	RCC_AHB1ENR_R |= GPIOAEN;
	//enable clock to GPIOC
	RCC_AHB1ENR_R |= GPIOCEN;


	//Set PINA5 as output
	GPIOA_MODE_R |=  GPIO5_OUTPUT_MODE; //set bit10 to 1
	GPIOA_MODE_R &=~ (1UL<<11);          //set bit11 to 0

	//Set pin 13 in port C to input
	GPIOC_MODE_R &=~ (1UL << 26);  //set bit 26 to 0
	GPIOC_MODE_R &=~ (1UL << 27);  //set bit 26 to 0



	while(1){

		 // Check if button is pressed (PC13 active-low)
		        if(GPIOC_ID_R & BUTTON_PIN_13_MASK)
		        {
		            // Button pressed, turn on LED (PA5 high)
		            GPIOA_OD_R |= PIN5_HIGH;
		        }else
		        {
		            // Button not pressed, turn off LED (PA5 low)
		            GPIOA_OD_R &= ~PIN5_HIGH;
		        }
	}
}
