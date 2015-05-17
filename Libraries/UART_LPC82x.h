/****************************************************************************
	Luka Penger 2015
	UART LPC82x
****************************************************************************/
#ifndef __UART_LPC82x_H 
#define __UART_LPC82x_H

#include <LPC82x.h>
#include <stdbool.h>
#include <RING_BUFFER.h>
#include <CLOCK_LPC82x.h>

/**
 * @brief UART CFG register definitions
 */
#define UART_CFG_ENABLE         (0x01 << 0)
#define UART_CFG_DATALEN_7      (0x00 << 2)		/*!< UART 7 bit length mode */
#define UART_CFG_DATALEN_8      (0x01 << 2)		/*!< UART 8 bit length mode */
#define UART_CFG_DATALEN_9      (0x02 << 2)		/*!< UART 9 bit length mode */
#define UART_CFG_PARITY_NONE    (0x00 << 4)		/*!< No parity */
#define UART_CFG_PARITY_EVEN    (0x02 << 4)		/*!< Even parity */
#define UART_CFG_PARITY_ODD     (0x03 << 4)		/*!< Odd parity */
#define UART_CFG_STOPLEN_1      (0x00 << 6)		/*!< UART One Stop Bit Select */
#define UART_CFG_STOPLEN_2      (0x01 << 6)		/*!< UART Two Stop Bits Select */
#define UART_CFG_CTSEN          (0x01 << 9)		/*!< CTS enable bit */
#define UART_CFG_SYNCEN         (0x01 << 11)	/*!< Synchronous mode enable bit */
#define UART_CFG_CLKPOL         (0x01 << 12)	/*!< Un_RXD rising edge sample enable bit */
#define UART_CFG_SYNCMST        (0x01 << 14)	/*!< Select master mode (synchronous mode) enable bit */
#define UART_CFG_LOOP           (0x01 << 15)	/*!< Loopback mode enable bit */

#define UART_CFG_OETA           (0x01 << 18)    /*!< Output Enable Turnaround time for RS485 */
#define UART_CFG_AUTOADDR       (0x01 << 19)    /*!< Automatic address matching enable */
#define UART_CFG_OESEL          (0x01 << 20)    /*!< Output enable select */
#define UART_CFG_OEPOL          (0x01 << 21)    /*!< Output enable polarity */
#define UART_CFG_RXPOL          (0x01 << 22)    /*!< Receive data polarity */
#define UART_CFG_TXPOL          (0x01 << 22)    /*!< Transmit data polarity */
#define UART_CFG_RESERVED       ((1<<1)|(1<<7)|(1<<8)|(1<<10)|(1<<13)|(3 << 16)|(0xffu<<24))

/**
 * @brief UART CTRL register definitions
 */
#define UART_CTRL_TXBRKEN       (0x01 << 1)		/*!< Continuous break enable bit */
#define UART_CTRL_ADDRDET       (0x01 << 2)		/*!< Address detect mode enable bit */
#define UART_CTRL_TXDIS         (0x01 << 6)		/*!< Transmit disable bit */
#define UART_CTRL_CC            (0x01 << 8)		/*!< Continuous Clock mode enable bit */
#define UART_CTRL_CLRCC         (0x01 << 9)		/*!< Clear Continuous Clock bit */
#define UART_CTRL_AUTOBAUD      (1 << 16)       /*!< Enable UART Autobaud */
#define UART_CTRL_RESERVED      (0xFFFEFCB9U)

/**
 * @brief UART STAT register definitions
 */
#define UART_STAT_RXRDY         (0x01 << 0)			/*!< Receiver ready */
#define UART_STAT_RXIDLE        (0x01 << 1)			/*!< Receiver idle */
#define UART_STAT_TXRDY         (0x01 << 2)			/*!< Transmitter ready for data */
#define UART_STAT_TXIDLE        (0x01 << 3)			/*!< Transmitter idle */
#define UART_STAT_CTS           (0x01 << 4)			/*!< Status of CTS signal */
#define UART_STAT_DELTACTS      (0x01 << 5)			/*!< Change in CTS state */
#define UART_STAT_TXDISINT      (0x01 << 6)			/*!< Transmitter disabled */
#define UART_STAT_OVERRUNINT    (0x01 << 8)			/*!< Overrun Error interrupt flag. */
#define UART_STAT_RXBRK         (0x01 << 10)		/*!< Received break */
#define UART_STAT_DELTARXBRK    (0x01 << 11)		/*!< Change in receive break detection */
#define UART_STAT_START         (0x01 << 12)		/*!< Start detected */
#define UART_STAT_FRM_ERRINT    (0x01 << 13)		/*!< Framing Error interrupt flag */
#define UART_STAT_PAR_ERRINT    (0x01 << 14)		/*!< Parity Error interrupt flag */
#define UART_STAT_RXNOISEINT    (0x01 << 15)		/*!< Received Noise interrupt flag */
#define UART_STAT_ABERR         (0x01 << 16)        /*!< Auto baud error */
#define UART_STAT_RESERVED      ((1<<7)|(1<<9)|(0xFFFEU<<16))

/**
 * @brief UART INTENSET/INTENCLR register definitions
 */
#define UART_INTEN_RXRDY        (0x01 << 0)			/*!< Receive Ready interrupt */
#define UART_INTEN_TXRDY        (0x01 << 2)			/*!< Transmit Ready interrupt */
#define UART_INTEN_DELTACTS     (0x01 << 5)			/*!< Change in CTS state interrupt */
#define UART_INTEN_TXDIS        (0x01 << 6)			/*!< Transmitter disable interrupt */
#define UART_INTEN_OVERRUN      (0x01 << 8)			/*!< Overrun error interrupt */
#define UART_INTEN_DELTARXBRK   (0x01 << 11)		/*!< Change in receiver break detection interrupt */
#define UART_INTEN_START        (0x01 << 12)		/*!< Start detect interrupt */
#define UART_INTEN_FRAMERR      (0x01 << 13)		/*!< Frame error interrupt */
#define UART_INTEN_PARITYERR    (0x01 << 14)		/*!< Parity error interrupt */
#define UART_INTEN_RXNOISE      (0x01 << 15)		/*!< Received noise interrupt */
#define UART_INTEN_TXIDLE       (0x01 << 3)         /*!< TX Idle enable/clear */
#define UART_INTEN_ABERR        (0x01 << 16)        /*!< Auto baud error */
#define UART_INTEN_RESERVED     ((1<<1)|(1<<4)|(1<<7)|(3<<9)|(0xfffeu<<16))
#define UART_INTSTAT_RESERVED   ((1<<1)|(1<<4)|(1<<7)|(3<<9)|(0xfffeu<<16))

/**
 * @brief	Enable the UART
 * @param	pUART		: Pointer to selected UARTx peripheral
 * @return	Nothing
 */
void UART_Enable(LPC_USART0_Type *pUART);

/**
 * @brief	Disable the UART
 * @param	pUART	: Pointer to selected UARTx peripheral
 * @return	Nothing
 */
void UART_Disable(LPC_USART0_Type *pUART);

/**
 * @brief	Enable transmission on UART TxD pin
 * @param	pUART	: Pointer to selected pUART peripheral
 * @return Nothing
 */
void UART_TXEnable(LPC_USART0_Type *pUART);

/**
 * @brief	Disable transmission on UART TxD pin
 * @param	pUART	: Pointer to selected pUART peripheral
 * @return Nothing
 */
void UART_TXDisable(LPC_USART0_Type *pUART);

/**
 * @brief	Transmit a single data byte through the UART peripheral
 * @param	pUART	: Pointer to selected UART peripheral
 * @param	data	: Byte to transmit
 * @return	Nothing
 * @note	This function attempts to place a byte into the UART transmit
 *			holding register regard regardless of UART state.
 */
void UART_SendByte(LPC_USART0_Type *pUART, uint8_t data);

/**
 * @brief	Read a single byte data from the UART peripheral
 * @param	pUART	: Pointer to selected UART peripheral
 * @return	A single byte of data read
 * @note	This function reads a byte from the UART receive FIFO or
 *			receive hold register regard regardless of UART state. The
 *			FIFO status should be read first prior to using this function
 */
uint32_t UART_ReadByte(LPC_USART0_Type *pUART);

/**
 * @brief	Enable UART interrupts
 * @param	pUART	: Pointer to selected UART peripheral
 * @param	intMask	: OR'ed Interrupts to enable
 * @return	Nothing
 * @note	Use an OR'ed value of UART_INTEN_* definitions with this function
 *			to enable specific UART interrupts.
 */
void UART_IntEnable(LPC_USART0_Type *pUART, uint32_t intMask);

/**
 * @brief	Disable UART interrupts
 * @param	pUART	: Pointer to selected UART peripheral
 * @param	intMask	: OR'ed Interrupts to disable
 * @return	Nothing
 * @note	Use an OR'ed value of UART_INTEN_* definitions with this function
 *			to disable specific UART interrupts.
 */
void UART_IntDisable(LPC_USART0_Type *pUART, uint32_t intMask);

/**
 * @brief	Returns UART interrupts that are enabled
 * @param	pUART	: Pointer to selected UART peripheral
 * @return	Returns the enabled UART interrupts
 * @note	Use an OR'ed value of UART_INTEN_* definitions with this function
 *			to determine which interrupts are enabled. You can check
 *			for multiple enabled bits if needed.
 */
uint32_t UART_GetIntsEnabled(LPC_USART0_Type *pUART);

/**
 * @brief	Get UART interrupt status
 * @param	pUART	: The base of UART peripheral on the chip
 * @return	The Interrupt status register of UART
 * @note	Multiple interrupts may be pending. Mask the return value
 *			with one or more UART_INTEN_* definitions to determine
 *			pending interrupts.
 */
uint32_t UART_GetIntStatus(LPC_USART0_Type *pUART);

/**
 * @brief	Configure data width, parity and stop bits
 * @param	pUART	: Pointer to selected pUART peripheral
 * @param	config	: UART configuration, OR'ed values of select UART_CFG_* defines
 * @return	Nothing
 * @note	Select OR'ed config options for the UART from the UART_CFG_PARITY_*,
 *			UART_CFG_STOPLEN_*, and UART_CFG_DATALEN_* definitions. For example,
 *			a configuration of 8 data bits, 1 stop bit, and even (enabled) parity would be
 *			(UART_CFG_DATALEN_8 | UART_CFG_STOPLEN_1 | UART_CFG_PARITY_EVEN). Will not
 *			alter other bits in the CFG register.
 */
void UART_ConfigData(LPC_USART0_Type *pUART, uint32_t config);

/**
 * @brief	Get the UART status register
 * @param	pUART	: Pointer to selected UARTx peripheral
 * @return	UART status register
 * @note	Multiple statuses may be pending. Mask the return value
 *			with one or more UART_STAT_* definitions to determine
 *			statuses.
 */
uint32_t UART_GetStatus(LPC_USART0_Type *pUART);

/**
 * @brief	Clear the UART status register
 * @param	pUART	: Pointer to selected UARTx peripheral
 * @param	stsMask	: OR'ed statuses to disable
 * @return	Nothing
 * @note	Multiple interrupts may be pending. Mask the return value
 *			with one or more UART_INTEN_* definitions to determine
 *			pending interrupts.
 */
void UART_ClearStatus(LPC_USART0_Type *pUART, uint32_t stsMask);

/**
 * @brief	Set oversample value
 * @param	pUART		: Pointer to selected UARTx peripheral
 * @param	ovrVal		: Oversample value (can be from 5 to 16)
 * @return	Nothing
 * @note	The valid values for ovrVal is 5 to 16 (samples per bit)
 */
void UART_SetOSR(LPC_USART0_Type *pUART, uint32_t ovrVal);

/**
 * @brief	Set address for hardware address matching
 * @param	pUART		: Pointer to selected UARTx peripheral
 * @param	addr		: Address to compare (0x00 to 0xFF)
 * @return	Nothing
 * @note	The valid values for addr is 0x00 to 0xFF
 */
void UART_SetAddr(LPC_USART0_Type *pUART, uint32_t addr);

/**
 * @brief	Initialize the UART peripheral
 * @param	pUART	: The base of UART peripheral on the chip
 * @return	Nothing
 */
void UART_Init(LPC_USART0_Type *pUART);

/**
 * @brief	Deinitialize the UART peripheral
 * @param	pUART	: The base of UART peripheral on the chip
 * @return	Nothing
 */
void UART_DeInit(LPC_USART0_Type *pUART);

/**
 * @brief	Transmit a byte array through the UART peripheral (non-blocking)
 * @param	pUART		: Pointer to selected UART peripheral
 * @param	data		: Pointer to bytes to transmit
 * @param	numBytes	: Number of bytes to transmit
 * @return	The actual number of bytes placed into the FIFO
 * @note	This function places data into the transmit FIFO until either
 *			all the data is in the FIFO or the FIFO is full. This function
 *			will not block in the FIFO is full. The actual number of bytes
 *			placed into the FIFO is returned. This function ignores errors.
 */
int UART_Send(LPC_USART0_Type *pUART, const void *data, int numBytes);

/**
 * @brief	Read data through the UART peripheral (non-blocking)
 * @param	pUART		: Pointer to selected UART peripheral
 * @param	data		: Pointer to bytes array to fill
 * @param	numBytes	: Size of the passed data array
 * @return	The actual number of bytes read
 * @note	This function reads data from the receive FIFO until either
 *			all the data has been read or the passed buffer is completely full.
 *			This function will not block. This function ignores errors.
 */
int UART_Read(LPC_USART0_Type *pUART, void *data, int numBytes);

/**
 * @brief	Set baud rate for UART
 * @param	pUART	: The base of UART peripheral on the chip
 * @param	baudrate: Baud rate to be set
 * @return	Nothing
 */
void UART_SetBaud(LPC_USART0_Type *pUART, uint32_t baudrate);

/**
 * @brief	Transmit a byte array through the UART peripheral (blocking)
 * @param	pUART		: Pointer to selected UART peripheral
 * @param	data		: Pointer to data to transmit
 * @param	numBytes	: Number of bytes to transmit
 * @return	The number of bytes transmitted
 * @note	This function will send or place all bytes into the transmit
 *			FIFO. This function will block until the last bytes are in the FIFO.
 */
int UART_SendBlocking(LPC_USART0_Type *pUART, const void *data, int numBytes);

/**
 * @brief	Read data through the UART peripheral (blocking)
 * @param	pUART		: Pointer to selected UART peripheral
 * @param	data		: Pointer to data array to fill
 * @param	numBytes	: Size of the passed data array
 * @return	The size of the dat array
 * @note	This function reads data from the receive FIFO until the passed
 *			buffer is completely full. The function will block until full.
 *			This function ignores errors.
 */
int UART_ReadBlocking(LPC_USART0_Type *pUART, void *data, int numBytes);

/**
 * @brief	UART receive-only interrupt handler for ring buffers
 * @param	pUART	: Pointer to selected UART peripheral
 * @param	pRB		: Pointer to ring buffer structure to use
 * @return	Nothing
 * @note	If ring buffer support is desired for the receive side
 *			of data transfer, the UART interrupt should call this
 *			function for a receive based interrupt status.
 */
void UART_RXIntHandlerRB(LPC_USART0_Type *pUART, RINGBUFF_T *pRB);

/**
 * @brief	UART transmit-only interrupt handler for ring buffers
 * @param	pUART	: Pointer to selected UART peripheral
 * @param	pRB		: Pointer to ring buffer structure to use
 * @return	Nothing
 * @note	If ring buffer support is desired for the transmit side
 *			of data transfer, the UART interrupt should call this
 *			function for a transmit based interrupt status.
 */
void UART_TXIntHandlerRB(LPC_USART0_Type *pUART, RINGBUFF_T *pRB);

/**
 * @brief	Populate a transmit ring buffer and start UART transmit
 * @param	pUART	: Pointer to selected UART peripheral
 * @param	pRB		: Pointer to ring buffer structure to use
 * @param	data	: Pointer to buffer to move to ring buffer
 * @param	count	: Number of bytes to move
 * @return	The number of bytes placed into the ring buffer
 * @note	Will move the data into the TX ring buffer and start the
 *			transfer. If the number of bytes returned is less than the
 *			number of bytes to send, the ring buffer is considered full.
 */
uint32_t UART_SendRB(LPC_USART0_Type *pUART, RINGBUFF_T *pRB, const void *data, int count);

/**
 * @brief	Copy data from a receive ring buffer
 * @param	pUART	: Pointer to selected UART peripheral
 * @param	pRB		: Pointer to ring buffer structure to use
 * @param	data	: Pointer to buffer to fill from ring buffer
 * @param	bytes	: Size of the passed buffer in bytes
 * @return	The number of bytes placed into the ring buffer
 * @note	Will move the data from the RX ring buffer up to the
 *			the maximum passed buffer size. Returns 0 if there is
 *			no data in the ring buffer.
 */
int UART_ReadRB(LPC_USART0_Type *pUART, RINGBUFF_T *pRB, void *data, int bytes);

/**
 * @brief	UART receive/transmit interrupt handler for ring buffers
 * @param	pUART	: Pointer to selected UART peripheral
 * @param	pRXRB	: Pointer to transmit ring buffer
 * @param	pTXRB	: Pointer to receive ring buffer
 * @return	Nothing
 * @note	This provides a basic implementation of the UART IRQ
 *			handler for support of a ring buffer implementation for
 *			transmit and receive.
 */
void UART_IRQRBHandler(LPC_USART0_Type *pUART, RINGBUFF_T *pRXRB, RINGBUFF_T *pTXRB);

#endif // end __UART_LPC82x_H
/****************************************************************************
                            End Of File
****************************************************************************/
