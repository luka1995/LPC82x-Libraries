/****************************************************************************
	Luka Penger 2015
	SCTPWM LPC82x
****************************************************************************/

#include <SCTPWM_LPC82x.h>

uint32_t SCTPWM_GetTicksPerCycle(LPC_SCT_Type *pSCT) {
	return pSCT->MATCHREL0;
}

uint32_t SCTPWM_PercentageToTicks(LPC_SCT_Type *pSCT, uint8_t percent) {
	return (SCTPWM_GetTicksPerCycle(pSCT) * percent) / 100;
}

uint32_t SCTPWM_GetDutyCycle(LPC_SCT_Type *pSCT, uint8_t index) {
	switch (index) {
		case 0: pSCT->MATCHREL0; break;
		case 1: pSCT->MATCHREL1; break;
		case 2: pSCT->MATCHREL2; break;
		case 3: pSCT->MATCHREL3; break;
		case 4: pSCT->MATCHREL4; break;
		case 5: pSCT->MATCHREL5; break;
		case 6: pSCT->MATCHREL6; break;
		case 7: pSCT->MATCHREL7; break;
	}
	
	return 0;
}

void SCTPWM_SetDutyCycle(LPC_SCT_Type *pSCT, uint8_t index, uint32_t ticks) {
	SCT_SetMatchReload(pSCT, (SCT_MATCH_REG_T)index, ticks);
}

void SCTPWM_Init(LPC_SCT_Type *pSCT) {
	SCT_Init(pSCT);
}

void SCTPWM_Start(LPC_SCT_Type *pSCT) {
	SCT_ClearControl(pSCT, SCT_CTRL_HALT_L | SCT_CTRL_HALT_H);
}

void SCTPWM_Stop(LPC_SCT_Type *pSCT) {
	/* Stop SCT */
	SCT_SetControl(pSCT, SCT_CTRL_HALT_L | SCT_CTRL_HALT_H);

	/* Clear the counter */
	SCT_SetControl(pSCT, SCT_CTRL_CLRCTR_L | SCT_CTRL_CLRCTR_H);
}

/* Setup the OUTPUT pin corresponding to the PWM index */
void SCTPWM_SetOutPin(LPC_SCT_Type *pSCT, uint8_t index, uint8_t pin) {
	int ix = (int) index;
	
	switch (index) {
		case 0: pSCT->EV0_CTRL = index | (1 << 12); pSCT->EV0_STATE = 1; break;
		case 1: pSCT->EV1_CTRL = index | (1 << 12); pSCT->EV1_STATE = 1; break;
		case 2: pSCT->EV2_CTRL = index | (1 << 12); pSCT->EV2_STATE = 1; break;
		case 3: pSCT->EV3_CTRL = index | (1 << 12); pSCT->EV3_STATE = 1; break;
		case 4: pSCT->EV4_CTRL = index | (1 << 12); pSCT->EV4_STATE = 1; break;
		case 5: pSCT->EV5_CTRL = index | (1 << 12); pSCT->EV5_STATE = 1; break;
		case 6: pSCT->EV6_CTRL = index | (1 << 12); pSCT->EV6_STATE = 1; break;
		case 7: pSCT->EV7_CTRL = index | (1 << 12); pSCT->EV7_STATE = 1; break;
	}

	switch (pin) {
		case 0: pSCT->OUT0_SET = 1; pSCT->OUT0_CLR = 1 << ix; break;
		case 1: pSCT->OUT1_SET = 1; pSCT->OUT1_CLR = 1 << ix; break;
		case 2: pSCT->OUT2_SET = 1; pSCT->OUT2_CLR = 1 << ix; break;
		case 3: pSCT->OUT3_SET = 1; pSCT->OUT3_CLR = 1 << ix; break;
		case 4: pSCT->OUT4_SET = 1; pSCT->OUT4_CLR = 1 << ix; break;
		case 5: pSCT->OUT5_SET = 1; pSCT->OUT5_CLR = 1 << ix; break;
	}

	/* Clear the output in-case of conflict */
	pSCT->RES = (pSCT->RES & ~(3 << (pin << 1))) | (0x01 << (pin << 1));

	/* Set and Clear do not depend on direction */
	pSCT->OUTPUTDIRCTRL = (pSCT->OUTPUTDIRCTRL & ~((3 << (pin << 1))|SCT_OUTPUTDIRCTRL_RESERVED));
}

/* Set the PWM frequency */
void SCTPWM_SetRate(LPC_SCT_Type *pSCT, uint32_t freq) {
	uint32_t rate;

	rate = Clock_GetSystemClockRate() / freq;;

	/* Stop the SCT before configuration */
	SCTPWM_Stop(pSCT);

	/* Set MATCH0 for max limit */
	pSCT->REGMODE = 0;
	SCT_SetMatchCount(pSCT, SCT_MATCH_0, 0);
	SCT_SetMatchReload(pSCT, SCT_MATCH_0, rate);
	
	pSCT->EV0_CTRL = 1 << 12;
	pSCT->EV0_STATE = 1;

	/* Set SCT Counter to count 32-bits and reset to 0 after reaching MATCH0 */
	SCT_Config(pSCT, SCT_CONFIG_32BIT_COUNTER | SCT_CONFIG_AUTOLIMIT_L);
}

/****************************************************************************
                            End Of File
****************************************************************************/
