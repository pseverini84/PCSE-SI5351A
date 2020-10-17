#include "sapi_software_i2c.h"
#include "si5351a.h"

uint8_t i2cSendRegister(uint8_t reg, uint8_t data)
{
	 uint8_t newData[2];
	 newData[0]=reg;
	 newData[1]=data;
	 i2cSoftwareWrite(0,0x60,newData,2,1);
}

void si5351aInit(void)
{
	i2cSoftwareInit(0,100000);
}

void setStage1(uint8_t pll, uint8_t a, uint32_t b, uint32_t c)
{
	uint32_t P1;
	uint32_t P2;
	uint32_t P3;

	P1 = (uint32_t)(128 * (uint32_t)(a) + (uint32_t)(128 * ((float)b / (float)c)) - 512);
	P2 = (uint32_t)(128 * b - c * (uint32_t)(128 * ((float)b / (float)c)));
	P3 = c;

	i2cSendRegister(pll + 0, (P3 & 0x0000FF00) >> 8);
	i2cSendRegister(pll + 1, (P3 & 0x000000FF));
	i2cSendRegister(pll + 2, (P1 & 0x00030000) >> 16);
	i2cSendRegister(pll + 3, (P1 & 0x0000FF00) >> 8);
	i2cSendRegister(pll + 4, (P1 & 0x000000FF));
	i2cSendRegister(pll + 5, ((P3 & 0x000F0000) >> 12) | ((P2 & 0x000F0000) >> 16));
	i2cSendRegister(pll + 6, (P2 & 0x0000FF00) >> 8);
	i2cSendRegister(pll + 7, (P2 & 0x000000FF));
}

void setStage2(uint8_t synth, uint8_t a, uint32_t b, uint32_t c)
{
	uint32_t P1;
	uint32_t P2;
	uint32_t P3;

	P1 = (uint32_t)(128 * (uint32_t)(a) + (uint32_t)(128 * ((float)b / (float)c)) - 512);
	P2 = (uint32_t)(128 * b - c * (uint32_t)(128 * ((float)b / (float)c)));
	P3 = c;

	i2cSendRegister(synth + 0,   (P3 & 0x0000FF00) >> 8);
	i2cSendRegister(synth + 1,   (P3 & 0x000000FF));
	i2cSendRegister(synth + 2,   (P1 & 0x00030000) >> 16);
	i2cSendRegister(synth + 3,   (P1 & 0x0000FF00) >> 8);
	i2cSendRegister(synth + 4,   (P1 & 0x000000FF));
	i2cSendRegister(synth + 5,   ((P3 & 0x000F0000) >> 12) | ((P2 & 0x000F0000) >> 16));
	i2cSendRegister(synth + 6,   (P2 & 0x0000FF00) >> 8);
	i2cSendRegister(synth + 7,   (P2 & 0x000000FF));
}

void si5351aSetFrequency(uint32_t frequency)
{
	uint32_t xtalFreq = XTAL_FREQ;
	uint8_t a;
	uint32_t b;
	uint32_t c;

	a = FPLL / xtalFreq;
	b = (uint32_t)((float)((float)(FPLL % xtalFreq)*1048575)/(float)xtalFreq);
	c = 1048575;

	setStage1(SI_SYNTH_PLL_A, a, b, c);

	a = FPLL / frequency;
	b = (uint32_t)((float)((float)(FPLL % frequency)*1048575)/(float)frequency);
	c = 1048575;

	setStage2(SI_SYNTH_MS_0, a, b, c);

	i2cSendRegister(SI_PLL_RESET, 0xA0);	
	i2cSendRegister(SI_CLK0_CONTROL, 0x4F | SI_CLK_SRC_PLL_A);
}

