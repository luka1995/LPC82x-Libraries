/****************************************************************************
	Luka Penger 2015
	UART LPC82x
****************************************************************************/

#include <UART_LPC82x.h>

void UART_Enable(LPC_USART0_Type *pUART) {
	pUART->CFG = UART_CFG_ENABLE | (pUART->CFG & ~UART_CFG_RESERVED);
}

void UART_Disable(LPC_USART0_Type *pUART) {
	pUART->CFG &= ~(UART_CFG_RESERVED | UART_CFG_ENABLE);
}

void UART_TXEnable(LPC_USART0_Type *pUART) {
	pUART->CTL &= ~(UART_CTRL_RESERVED | UART_CTRL_TXDIS);
}

void UART_TXDisable(LPC_USART0_Type *pUART) {
	pUART->CTL = UART_CTRL_TXDIS | (pUART->CTL & ~UART_CTRL_RESERVED);
}

void UART_SendByte(LPC_USART0_Type *pUART, uint8_t data) {
	pUART->TXDAT = (uint32_t) data;
}

uint32_t UART_ReadByte(LPC_USART0_Type *pUART) {
	/* Strip off undefined reserved bits, keep 9 lower bits */
	return (uint32_t) (pUART->RXDAT & 0x000001FF);
}

void UART_IntEnable(LPC_USART0_Type *pUART, uint32_t intMask)
{
	pUART->INTENSET = intMask;
}

void UART_IntDisable(LPC_USART0_Type *pUART, uint32_t intMask) {
	pUART->INTENCLR = intMask;
}

uint32_t UART_GetIntsEnabled(LPC_USART0_Type *pUART) {
	return (pUART->INTENSET & ~UART_INTEN_RESERVED);
}

uint32_t UART_GetIntStatus(LPC_USART0_Type *pUART) {
	return (pUART->INTSTAT & ~UART_INTSTAT_RESERVED);
}

void UART_ConfigData(LPC_USART0_Type *pUART, uint32_t config) {
	uint32_t reg;

	reg = pUART->CFG & ~((0x3 << 2) | (0x3 << 4) | (0x1 << 6) | UART_CFG_RESERVED);
	pUART->CFG = reg | config;
}

uint32_t UART_GetStatus(LPC_USART0_Type *pUART) {
	return (pUART->STAT & ~UART_STAT_RESERVED);
}

void UART_ClearStatus(LPC_USART0_Type *pUART, uint32_t stsMask) {
	pUART->STAT = stsMask;
}

void UART_SetOSR(LPC_USART0_Type *pUART, uint32_t ovrVal) {
	pUART->OSR = ovrVal - 1;
}

void UART_SetAddr(LPC_USART0_Type *pUART, uint32_t addr) {
	pUART->ADDR = addr;
}

/* Return UART clock ID from the UART register address */
SYSCTL_CLOCK_T getUARTClockID(LPC_USART0_Type *pUART) {
	if (pUART == LPC_USART0) {
		return SYSCTL_CLOCK_UART0;
	}
	else if (pUART == LPC_USART1) {
		return SYSCTL_CLOCK_UART1;
	}

	return SYSCTL_CLOCK_UART2;
}

/* Initialize the UART peripheral */
void UART_Init(LPC_USART0_Type *pUART) {
	/* Enable USART clock */
	Clock_EnablePeriphClock(getUARTClockID(pUART));

	/* UART reset */
	if (pUART == LPC_USART0) {
		/* Peripheral reset control to USART0 */
		SYSCTL_PeriphReset(RESET_USART0);
	} else if (pUART == LPC_USART1) {
		/* Peripheral reset control to USART1 */
		SYSCTL_PeriphReset(RESET_USART1);
	} else {
		/* Peripheral reset control to USART2 */
		SYSCTL_PeriphReset(RESET_USART2);
	}
}

/* Initialize the UART peripheral */
void UART_DeInit(LPC_USART0_Type *pUART) {
	/* Disable USART clock */
	Clock_DisablePeriphClock(getUARTClockID(pUART));
}

/* Transmit a byte array through the UART peripheral (non-blocking) */
int UART_Send(LPC_USART0_Type *pUART, const void *data, int numBytes) {
	int sent = 0;
	uint8_t *p8 = (uint8_t *) data;

	/* Send until the transmit FIFO is full or out of bytes */
	while ((sent < numBytes) &&
		   ((UART_GetStatus(pUART) & UART_STAT_TXRDY) != 0)) {
		UART_SendByte(pUART, *p8);
		p8++;
		sent++;
	}

	return sent;
}

/* Transmit a byte array through the UART peripheral (blocking) */
int UART_SendBlocking(LPC_USART0_Type *pUART, const void *data, int numBytes) {
	int pass, sent = 0;
	uint8_t *p8 = (uint8_t *) data;

	while (numBytes > 0) {
		pass = UART_Send(pUART, p8, numBytes);
		numBytes -= pass;
		sent += pass;
		p8 += pass;
	}

	return sent;
}

/* Read data through the UART peripheral (non-blocking) */
int UART_Read(LPC_USART0_Type *pUART, void *data, int numBytes) {
	int readBytes = 0;
	uint8_t *p8 = (uint8_t *) data;

	/* Send until the transmit FIFO is full or out of bytes */
	while ((readBytes < numBytes) &&
		   ((UART_GetStatus(pUART) & UART_STAT_RXRDY) != 0)) {
		*p8 = UART_ReadByte(pUART);
		p8++;
		readBytes++;
	}

	return readBytes;
}

/* Read data through the UART peripheral (blocking) */
int UART_ReadBlocking(LPC_USART0_Type *pUART, void *data, int numBytes) {
	int pass, readBytes = 0;
	uint8_t *p8 = (uint8_t *) data;

	while (readBytes < numBytes) {
		pass = UART_Read(pUART, p8, numBytes);
		numBytes -= pass;
		readBytes += pass;
		p8 += pass;
	}

	return readBytes;
}

/* Set baud rate for UART */
void UART_SetBaud(LPC_USART0_Type *pUART, uint32_t baudrate) {
	uint32_t baudRateGenerator;
	baudRateGenerator = Clock_GetUSARTNBaseClockRate() / (16 * baudrate);
	pUART->BRG = baudRateGenerator - 1;	/* baud rate */
}

/* UART receive-only interrupt handler for ring buffers */
void UART_RXIntHandlerRB(LPC_USART0_Type *pUART, RINGBUFF_T *pRB) {
	/* New data will be ignored if data not popped in time */
	while ((UART_GetStatus(pUART) & UART_STAT_RXRDY) != 0) {
		uint8_t ch = UART_ReadByte(pUART);
		RingBuffer_Insert(pRB, &ch);
	}
}

/* UART transmit-only interrupt handler for ring buffers */
void UART_TXIntHandlerRB(LPC_USART0_Type *pUART, RINGBUFF_T *pRB) {
	uint8_t ch;

	/* Fill FIFO until full or until TX ring buffer is empty */
	while (((UART_GetStatus(pUART) & UART_STAT_TXRDY) != 0) &&
		   RingBuffer_Pop(pRB, &ch)) {
		UART_SendByte(pUART, ch);
	}
}

/* Populate a transmit ring buffer and start UART transmit */
uint32_t UART_SendRB(LPC_USART0_Type *pUART, RINGBUFF_T *pRB, const void *data, int count) {
	uint32_t ret;
	uint8_t *p8 = (uint8_t *) data;

	/* Don't let UART transmit ring buffer change in the UART IRQ handler */
	UART_IntDisable(pUART, UART_INTEN_TXRDY);

	/* Move as much data as possible into transmit ring buffer */
	ret = RingBuffer_InsertMult(pRB, p8, count);
	UART_TXIntHandlerRB(pUART, pRB);

	/* Add additional data to transmit ring buffer if possible */
	ret += RingBuffer_InsertMult(pRB, (p8 + ret), (count - ret));

	/* Enable UART transmit interrupt */
	UART_IntEnable(pUART, UART_INTEN_TXRDY);

	return ret;
}

/* Copy data from a receive ring buffer */
int UART_ReadRB(LPC_USART0_Type *pUART, RINGBUFF_T *pRB, void *data, int bytes) {
	(void) pUART;

	return RingBuffer_PopMult(pRB, (uint8_t *) data, bytes);
}

/* UART receive/transmit interrupt handler for ring buffers */
void UART_IRQRBHandler(LPC_USART0_Type *pUART, RINGBUFF_T *pRXRB, RINGBUFF_T *pTXRB) {
	/* Handle transmit interrupt if enabled */
	if ((UART_GetStatus(pUART) & UART_STAT_TXRDY) != 0) {
		UART_TXIntHandlerRB(pUART, pTXRB);

		/* Disable transmit interrupt if the ring buffer is empty */
		if (RingBuffer_IsEmpty(pTXRB)) {
			UART_IntDisable(pUART, UART_INTEN_TXRDY);
		}
	}

	/* Handle receive interrupt */
	UART_RXIntHandlerRB(pUART, pRXRB);
}

/****************************************************************************
                            End Of File
****************************************************************************/
