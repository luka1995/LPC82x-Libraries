/****************************************************************************
	Luka Penger 2015
	SCTPWM LPC82x
****************************************************************************/
#ifndef __SCTPWM_LPC82x_H 
#define __SCTPWM_LPC82x_H

#include <LPC82x.h>
#include <SCT_LPC82x.h>
#include <CLOCK_LPC82x.h>
#include <SYSCON_LPC82x.h>

/**
 * @brief	Get number of ticks per PWM cycle
 * @param	pSCT	: The base of SCT peripheral on the chip
 * @return	Number ot ticks that will be counted per cycle
 * @note	Return value of this function will be vaild only
 *          after calling SCTPWM_SetRate()
 */
uint32_t SCTPWM_GetTicksPerCycle(LPC_SCT_Type *pSCT);

/**
 * @brief	Converts a percentage to ticks
 * @param	pSCT	: The base of SCT peripheral on the chip
 * @param	percent	: Percentage to convert (0 - 100)
 * @return	Number ot ticks corresponding to given percentage
 * @note	Do not use this function when using very low
 *          pwm rate (like 100Hz or less), on a chip that has
 *          very high frequency as the calculation might
 *          cause integer overflow
 */
uint32_t SCTPWM_PercentageToTicks(LPC_SCT_Type *pSCT, uint8_t percent);

/**
 * @brief	Get number of ticks on per PWM cycle
 * @param	pSCT	: The base of SCT peripheral on the chip
 * @param	index	: Index of the PWM 1 to N (see notes)
 * @return	Number ot ticks for which the output will be ON per cycle
 * @note	@a index will be 1 to N where N is the "Number of
 *          match registers available in the SCT - 1" or
 *          "Number of OUTPUT pins available in the SCT" whichever
 *          is minimum.
 */
uint32_t SCTPWM_GetDutyCycle(LPC_SCT_Type *pSCT, uint8_t index);

/**
 * @brief	Get number of ticks on per PWM cycle
 * @param	pSCT	: The base of SCT peripheral on the chip
 * @param	index	: Index of the PWM 1 to N (see notes)
 * @param	ticks	: Number of ticks the output should say ON
 * @return	None
 * @note	@a index will be 1 to N where N is the "Number of
 *          match registers available in the SCT - 1" or
 *          "Number of OUTPUT pins available in the SCT" whichever
 *          is minimum. The new duty cycle will be effective only
 *          after completion of current PWM cycle.
 */
void SCTPWM_SetDutyCycle(LPC_SCT_Type *pSCT, uint8_t index, uint32_t ticks);

/**
 * @brief	Initialize the SCT/PWM clock and reset
 * @param	pSCT	: The base of SCT peripheral on the chip
 * @return	None
 */
void SCTPWM_Init(LPC_SCT_Type *pSCT);

/**
 * @brief	Start the SCT PWM
 * @param	pSCT	: The base of SCT peripheral on the chip
 * @return	None
 * @note	This function must be called after all the
 * 			configuration is completed. Do not call SCTPWM_SetRate()
 * 			or SCTPWM_SetOutPin() after the SCT/PWM is started. Use
 * 			SCTPWM_Stop() to stop the SCT/PWM before reconfiguring,
 * 			SCTPWM_SetDutyCycle() can be called when the SCT/PWM is
 * 			running to change the DutyCycle.
 */
void SCTPWM_Start(LPC_SCT_Type *pSCT);

/**
 * @brief	Stop the SCT PWM
 * @param	pSCT	: The base of SCT peripheral on the chip
 * @return	None
 */
void SCTPWM_Stop(LPC_SCT_Type *pSCT);

/**
 * @brief	Sets the frequency of the generated PWM wave
 * @param	pSCT	: The base of SCT peripheral on the chip
 * @param	freq	: Frequency in Hz
 * @return	None
 */
void SCTPWM_SetRate(LPC_SCT_Type *pSCT, uint32_t freq);

/**
 * @brief	Setup the OUTPUT pin and associate it with an index
 * @param	pSCT	: The base of the SCT peripheral on the chip
 * @param	index	: Index of PWM 1 to N (see notes)
 * @param	pin		: COUT pin to be associated with the index
 * @return	None
 * @note	@a index will be 1 to N where N is the "Number of
 *          match registers available in the SCT - 1" or
 *          "Number of OUTPUT pins available in the SCT" whichever
 *          is minimum.
 */
void SCTPWM_SetOutPin(LPC_SCT_Type *pSCT, uint8_t index, uint8_t pin);

#endif // end __SCTPWM_LPC82x_H
/****************************************************************************
                            End Of File
****************************************************************************/
