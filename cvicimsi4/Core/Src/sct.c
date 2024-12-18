
#include "sct.h"


static const uint32_t reg_values[8][10] = {
		{
				//PCDE--------GFAB @ DIS1 bez
				0b0111000000000111 << 16,
				0b0100000000000001 << 16,
				0b0011000000001011 << 16,
				0b0110000000001011 << 16,
				0b0100000000001101 << 16,
				0b0110000000001110 << 16,
				0b0111000000001110 << 16,
				0b0100000000000011 << 16,
				0b0111000000001111 << 16,
				0b0110000000001111 << 16,
		},
		{
				//----PCDEGFAB---- @ DIS2 bez
				0b0000011101110000 << 0,
				0b0000010000010000 << 0,
				0b0000001110110000 << 0,
				0b0000011010110000 << 0,
				0b0000010011010000 << 0,
				0b0000011011100000 << 0,
				0b0000011111100000 << 0,
				0b0000010000110000 << 0,
				0b0000011111110000 << 0,
				0b0000011011110000 << 0,
		},
		{
				//PCDE--------GFAB @ DIS3 bez
				0b0111000000000111 << 0,
				0b0100000000000001 << 0,
				0b0011000000001011 << 0,
				0b0110000000001011 << 0,
				0b0100000000001101 << 0,
				0b0110000000001110 << 0,
				0b0111000000001110 << 0,
				0b0100000000000011 << 0,
				0b0111000000001111 << 0,
				0b0110000000001111 << 0,
		},

		{
				//PCDE--------GFAB @ DIS1 D
				0b1111000000000111 << 16,
				0b1100000000000001 << 16,
				0b1011000000001011 << 16,
				0b1110000000001011 << 16,
				0b1100000000001101 << 16,
				0b1110000000001110 << 16,
				0b1111000000001110 << 16,
				0b1100000000000011 << 16,
				0b1111000000001111 << 16,
				0b1110000000001111 << 16,
		},
		{
				//----PCDEGFAB---- @ DIS2 D
				0b0000111101110000 << 0,
				0b0000110000010000 << 0,
				0b0000101110110000 << 0,
				0b0000111010110000 << 0,
				0b0000110011010000 << 0,
				0b0000111011100000 << 0,
				0b0000111111100000 << 0,
				0b0000110000110000 << 0,
				0b0000111111110000 << 0,
				0b0000111011110000 << 0,
		},
		{
				//PCDE--------GFAB @ DIS3 D
				0b1111000000000111 << 0,
				0b1100000000000001 << 0,
				0b1011000000001011 << 0,
				0b1110000000001011 << 0,
				0b1100000000001101 << 0,
				0b1110000000001110 << 0,
				0b1111000000001110 << 0,
				0b1100000000000011 << 0,
				0b1111000000001111 << 0,
				0b1110000000001111 << 0,
		},
		{
				//----43215678---- @ LED
				0b0000000000000000 << 16,
				0b0000000100000000 << 16,
				0b0000001100000000 << 16,
				0b0000011100000000 << 16,
				0b0000111100000000 << 16,
				0b0000111110000000 << 16,
				0b0000111111000000 << 16,
				0b0000111111100000 << 16,
				0b0000111111110000 << 16,
		},
		{
				//----43215678---- @ single LED
				0b0000000000000000 << 16,
				0b0000000100000000 << 16,
				0b0000001000000000 << 16,
				0b0000010000000000 << 16,
				0b0000100000000000 << 16,
				0b0000000010000000 << 16,
				0b0000000001000000 << 16,
				0b0000000000100000 << 16,
				0b0000000000010000 << 16,
		}
};


void sct_init(void){
	sct_led(0);
}

void sct_led(uint32_t value){
	for(uint8_t i = 0; i < 32; i++){
		HAL_GPIO_WritePin(SCT_SDI_GPIO_Port, SCT_SDI_Pin, value & 1);
		value >>= 1;
		HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin,1);
		HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin,0);

	}

	HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin,1);
	HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin,0);

	//HAL_GPIO_WritePin(SCT_NOE_GPIO_Port, SCT_NOE_Pin,0);
}

void sct_value(uint16_t value, uint8_t led, uint8_t dot){

	uint32_t reg = 0;
	if(dot == 0){
		reg |= reg_values[0][value / 100 % 10];
		reg |= reg_values[1][value / 10 % 10];
		reg |= reg_values[2][value / 1 % 10];
	}else if (dot == 1) {
		reg |= reg_values[3][value / 100 % 10];
		reg |= reg_values[1][value / 10 % 10];
		reg |= reg_values[2][value / 1 % 10];
	}else if(dot == 2){
		reg |= reg_values[0][value / 100 % 10];
		reg |= reg_values[4][value / 10 % 10];
		reg |= reg_values[2][value / 1 % 10];
	}else if(dot == 3){
		reg |= reg_values[0][value / 100 % 10];
		reg |= reg_values[1][value / 10 % 10];
		reg |= reg_values[5][value / 1 % 10];
	}


	reg |= reg_values[6][led];

	sct_led(reg);

}


void sct_universal_baragraph(uint8_t led_binary_index){
	uint32_t reg = 0;
	for (uint8_t i = 1; i < 9; ++i) {
		if (led_binary_index & 0b1) {
			reg |= reg_values[7][i];
		}

		led_binary_index >>= 1;
	}

	sct_led(reg);

}


void sct_baragraph_value(uint8_t led_binary_index, uint16_t value, uint8_t dot){
	uint32_t reg = 0;
	for (uint8_t i = 1; i < 9; ++i) {
		if (led_binary_index & 0b1) {
			reg |= reg_values[7][i];
		}

		led_binary_index >>= 1;
	}
	if(dot == 0){
		reg |= reg_values[0][value / 100 % 10];
		reg |= reg_values[1][value / 10 % 10];
		reg |= reg_values[2][value / 1 % 10];
	}else if (dot == 1) {
		reg |= reg_values[3][value / 100 % 10];
		reg |= reg_values[1][value / 10 % 10];
		reg |= reg_values[2][value / 1 % 10];
	}else if(dot == 2){
		reg |= reg_values[0][value / 100 % 10];
		reg |= reg_values[4][value / 10 % 10];
		reg |= reg_values[2][value / 1 % 10];
	}else if(dot == 3){
		reg |= reg_values[0][value / 100 % 10];
		reg |= reg_values[1][value / 10 % 10];
		reg |= reg_values[5][value / 1 % 10];
	}


	sct_led(reg);

}



