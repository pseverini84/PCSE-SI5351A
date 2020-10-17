#ifndef SI5351A_H
#define SI5351A_H


#define SI_CLK0_CONTROL	16
#define SI_SYNTH_PLL_A	26
#define SI_SYNTH_MS_0		42
#define SI_PLL_RESET		177

#define SI_CLK_SRC_PLL_A	0b00000000
#define SI_CLK_SRC_PLL_B	0b00100000

#define XTAL_FREQ	25000000
#define FPLL 900000000

void si5351aInit(void);
void si5351aSetFrequency(uint32_t frequency);

#endif //SI5351A_H
