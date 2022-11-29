#ifndef _UNMBASE_HEADER
#define _UNMBASE_HEADER

#include <visa.h>
#include <vpptype.h>

#if defined(__cplusplus) || defined(__cplusplus__)
extern "C" {
#endif

#ifndef _UNMBASE_API	//внутри unmbase.c определено как __declspec(dllexport), иначе импортируем
#define _UNMBASE_API
#endif

#ifndef UN_MANUFACTURER_ID
#define UN_MANUFACTURER_ID              ((ViUInt16) 0x0E76)
#endif

#ifndef UN_USB_VENDOR_ID
#define UN_USB_VENDOR_ID                ((ViUInt16) 0x19BB)
#endif

#define UNMBASE_MODEL_CODE              ((ViUInt16) 0x010D)
#define UNMBASEU_MODEL_CODE             ((ViUInt16) 0x0155)
#define UNMBASE_MODEL_ARMVXI            ((ViUInt16) 0x0177)

#define UNMBASE_USB_MODEL_CODE          ((ViUInt16) 0x1004)

#define UNMBASE_MEZABOX_IDN          "INFORMTEST,UNMBASE"

#define UNMBASE_FLAG_MB			0x10	//флаг типа - Message Based

#define UNMBASE_TYPE_U			0	//упрощенный
#define UNMBASE_TYPE_1			1	//верси€ 1
#define UNMBASE_TYPE_2			2	//верси€ 2
#define UNMBASE_TYPE_2A			3	//верси€ 2A
#define UNMBASE_TYPE_MB			UNMBASE_FLAG_MB	//Message Based
#define UNMBASE_TYPE_ARM		0x20	//VXI на базе 2хј–ћ

#define UNMBASE_TYPE_MEZABOX	(UNMBASE_FLAG_MB)
#define UNMBASE_TYPE_AXIe0		(UNMBASE_FLAG_MB+1)
#define UNMBASE_TYPE_AXIeLS		(UNMBASE_FLAG_MB+2)
#define UNMBASE_TYPE_AXIeU		(UNMBASE_FLAG_MB+3)
#define UNMBASE_TYPE_MEZABOX4	(UNMBASE_FLAG_MB+4)
#define UNMBASE_TYPE_MEZABOX4M	(UNMBASE_FLAG_MB+5)



#define UNMBASE_IOMODE_IN           0
#define UNMBASE_IOMODE_OUT          1
#define UNMBASE_IOMODE_BOTH         2

#define UNMBASE_MODE_SINGLE         0
#define UNMBASE_MODE_BLOCK          1
#define UNMBASE_MODE_LOOP           2

/******************************************/
/*         Mezzanine attributes           */
/******************************************/
#define UNMBASE_MATTR_BASE_VI       0x3FFF0801UL    //(RO)
#define UNMBASE_MATTR_NUM           0x3FFF0802UL    //(RO)
#define UNMBASE_MATTR_TYPE          0x3FFF0803UL    //(RO)
#define UNMBASE_MATTR_MEMBASE_IN    0x3FFF0804UL    //(RO)
#define UNMBASE_MATTR_MEMSIZE_IN    0x3FFF0805UL    //(RO)
#define UNMBASE_MATTR_MEMBASE_OUT   0x3FFF0806UL    //(RO)
#define UNMBASE_MATTR_MEMSIZE_OUT   0x3FFF0807UL    //(RO)
#define UNMBASE_MATTR_USER_DATA     0x3FFF0808UL    //(R/W)
#define UNMBASE_MATTR_DEV_TYPE     	0x3FFF0809UL    //(R/W)
#define UNMBASE_MATTR_BASE_TYPE    	0x3FFF080AUL    //(R/W)
#define UNMBASE_MATTR_ASYNC     	0x3FFF080BUL    //(R/W)
#define UNMBASE_MATTR_MEZ_EXTVI     0x3FFF080CUL    //(R/W)
#define UNMBASE_MATTR_MEZ_INTVI     0x3FFF080DUL    //(RO)

#define UNMBASE_MATTR_LOCK_LASTDATA 0x3FFF080EUL    //(R/W)

#define UNMBASE_MATTR_CHECK_OUT_ERR 0x3FFF080FUL    //(R/W)

#define UNMBASE_MATTR_BASE_ID_MSG   0x3FFF0880UL    //(RO)

/******************************************/
/*  Error and Complete codes definitions  */
/******************************************/
#define UNMBASE_ERROR_OFFSET            (_VI_ERROR + 0x3FFC0800L)
#define UNMBASE_WARN_OFFSET             (0x3FFC0800L)

#define UNMBASE_ERROR_SELFTEST          (UNMBASE_ERROR_OFFSET + 0x0BL)
#define UNMBASE_ERROR_FLEX              (UNMBASE_ERROR_OFFSET + 0x0CL)
#define UNMBASE_ERROR_INSTR             (UNMBASE_ERROR_OFFSET + 0x0DL)
#define UNMBASE_ERROR_SPD               (UNMBASE_ERROR_OFFSET + 0x0EL)
#define UNMBASE_ERROR_BUSY              (UNMBASE_ERROR_OFFSET + 0x0FL)
#define UNMBASE_ERROR_M_NUMBER          (UNMBASE_ERROR_OFFSET + 0x10L)
#define UNMBASE_ERROR_NO_MEMORY         (UNMBASE_ERROR_OFFSET + 0x11L)
#define UNMBASE_ERROR_NODATA            (UNMBASE_ERROR_OFFSET + 0x12L)
#define UNMBASE_ERROR_READ              (UNMBASE_ERROR_OFFSET + 0x13L)
#define UNMBASE_ERROR_WRITE             (UNMBASE_ERROR_OFFSET + 0x14L)
#define UNMBASE_ERROR_MEZ_IO            (UNMBASE_ERROR_OFFSET + 0x15L)
#define UNMBASE_ERROR_TOO_FAST          (UNMBASE_ERROR_OFFSET + 0x16L)
#define UNMBASE_ERROR_NO_CLOCKS         (UNMBASE_ERROR_OFFSET + 0x17L)
#define UNMBASE_ERROR_NO_FIRST_DELAY    (UNMBASE_ERROR_OFFSET + 0x18L)
#define UNMBASE_ERROR_NO_SAMPLE_LENGTH  (UNMBASE_ERROR_OFFSET + 0x19L)
#define UNMBASE_ERROR_NO_PACKET_SIZE    (UNMBASE_ERROR_OFFSET + 0x1AL)
#define UNMBASE_ERROR_NO_BLOCK_SIZE     (UNMBASE_ERROR_OFFSET + 0x1BL)
#define UNMBASE_ERROR_NO_ALLOC          (UNMBASE_ERROR_OFFSET + 0x1CL)
#define UNMBASE_ERROR_NULL_POINTER      (UNMBASE_ERROR_OFFSET + 0x1DL)
#define UNMBASE_ERROR_MEZ_IO2           (UNMBASE_ERROR_OFFSET + 0x1EL)
#define UNMBASE_ERROR_NOT_SUPPORT       (UNMBASE_ERROR_OFFSET + 0x1FL)
#define UNMBASE_ERROR_MEZ_IO12          (UNMBASE_ERROR_OFFSET + 0x20L)

#define UNMBASE_WARN_INIT               (UNMBASE_WARN_OFFSET + 0x11L)
#define UNMBASE_WARN_REREADED           (UNMBASE_WARN_OFFSET + 0x12L)

typedef ViBoolean (_VI_FUNCH _VI_PTR unmbase_UserHandler)(ViSession mvi, ViInt32 reason);

#define UNMBASE_IRQ_MEZ_IRQ             0
#define UNMBASE_IRQ_TRANS_BLOCK         1
#define UNMBASE_IRQ_RECV_BLOCK          2
#define UNMBASE_IRQ_TRANS_PACKET        3
#define UNMBASE_IRQ_RECV_PACKET         4
#define UNMBASE_EVENT_RESET             10
#define UNMBASE_IRQ_ERR_1               -1
#define UNMBASE_IRQ_ERR_2               -2

/******************************************/
/*      Driver functions definitions      */
/******************************************/

_UNMBASE_API ViStatus _VI_FUNC unmbase_init (ViRsrc rsrcName,
							ViBoolean id_query,
							ViBoolean reset,
							ViSession *vi);
/*--------------------------------------------------------------------------*/
/* Init mezzanine session                                                   */
/*  On M-module number Num (if present); open session. Session number is     */
/* index in global array p_mvi + 1, where store session structure pointer   */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_init (ViSession vi,
								ViUInt16 Num,
								ViSession *mvi);
/*--------------------------------------------------------------------------*/
/* Close mezzanine session                                                  */
/*  Free session structure (->m_vi_idx=0); and session number (p_mvi[m_vi_idx] = 0);  */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_close (ViSession mvi);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_get_attribute (ViSession mvi,
								ViAttr Attribute_Name,
								void *Attribute_Value);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_set_attribute (ViSession mvi,
								ViAttr Attribute_Name,
								ViAttrState Attribute_Value);
/*--------------------------------------------------------------------------*/
/* Input D16 word from mezzanine memory                                     */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_in16 (ViSession mvi,
								ViUInt32 Addr,
								ViUInt16 *Data);
/*--------------------------------------------------------------------------*/
/* Output D16 word to mezzanine memory                                      */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_out16 (ViSession mvi,
								ViUInt32 Addr,
								ViUInt16 Data);
/*--------------------------------------------------------------------------*/
/* Input block of D16 words from mezzanine memory                           */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_movein16 (ViSession mvi,
								ViUInt32 Addr,
								ViUInt16 *Buff,
								ViInt32 Count,
								ViBoolean Increment);
/*--------------------------------------------------------------------------*/
/* Output block of D16 words to mezzanine memory                            */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_moveout16 (ViSession mvi,
								ViUInt32 Addr,
								ViUInt16 *Buff,
								ViInt32 Count,
								ViBoolean Increment);
/*--------------------------------------------------------------------------*/
/* Input D32 word from mezzanine memory                                     */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_in32 (ViSession mvi,
								ViUInt32 Addr,
								ViUInt32 Addr2,
								ViUInt32 *Data);
/*--------------------------------------------------------------------------*/
/* Output D32 word to mezzanine memory                                      */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_out32 (ViSession mvi,
								ViUInt32 Addr,
								ViUInt32 Addr2,
								ViUInt32 Data);
/*--------------------------------------------------------------------------*/
/* Input block of D32 words from mezzanine memory                           */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_movein32 (ViSession mvi,
								ViUInt32 Addr,
								ViUInt32 Addr2,
								ViUInt32 *Buff,
								ViInt32 Count);
/*--------------------------------------------------------------------------*/
/* Output block of D32 words to mezzanine memory                            */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_moveout32 (ViSession mvi,
								ViUInt32 Addr,
								ViUInt32 Addr2,
								ViUInt32 *Buff,
								ViInt32 Count);
/*--------------------------------------------------------------------------*/
/* Input/Output block of D16 words from/to mezzanine memory                 */
/*--------------------------------------------------------------------------*/
#define UNMBASE_IOREGS_ADDR_MASK	0x00FE
#define UNMBASE_IOREGS_TODO_MASK	0x3F00
#define UNMBASE_IOREGS_IF_MASK		0xC000
//condition todo
#define UNMBASE_IOREGS_IF_0			0x4000
#define UNMBASE_IOREGS_IF_1			0x8000
//simple read
#define UNMBASE_IOREGS_TODO_READ	0x0000	//R
//read, modify, store to M
#define UNMBASE_IOREGS_TODO_R_AND_M	0x0100	//R
#define UNMBASE_IOREGS_TODO_R_OR_M	0x0200	//R
#define UNMBASE_IOREGS_TODO_R_XOR_M	0x0300	//R
//wait for bit 0/1 (no more 20 ms)
#define UNMBASE_IOREGS_TODO_R_WAIT0	0x0400	//R
#define UNMBASE_IOREGS_TODO_R_WAIT1	0x0500	//R
//read, modify, write
#define UNMBASE_IOREGS_TODO_R_AND_W	0x0600	//RW
#define UNMBASE_IOREGS_TODO_R_OR_W	0x0700	//RW
#define UNMBASE_IOREGS_TODO_R_XOR_W	0x0800	//RW
//get M, modify, write
#define UNMBASE_IOREGS_TODO_M_AND_W	0x0900	//W
#define UNMBASE_IOREGS_TODO_M_OR_W	0x0A00	//W
#define UNMBASE_IOREGS_TODO_M_XOR_W	0x0B00	//W
//simple write
#define UNMBASE_IOREGS_TODO_WRITE	0x0C00	//W
//M modify
#define UNMBASE_IOREGS_TODO_M_AND	0x0D00	//
#define UNMBASE_IOREGS_TODO_M_OR	0x0E00	//
#define UNMBASE_IOREGS_TODO_M_XOR	0x0F00	//
#define UNMBASE_IOREGS_TODO_M_PLUS	0x1000	//
#define UNMBASE_IOREGS_TODO_M_MINUS	0x1100	//
#define UNMBASE_IOREGS_TODO_M_LSL	0x1200	//
#define UNMBASE_IOREGS_TODO_M_LSR	0x1300	//
//M mask and set Flag (M not changed)
#define UNMBASE_IOREGS_TODO_M_AND_F	0x1400	//

_UNMBASE_API ViStatus _VI_FUNC unmbase_m_ioregs (ViSession mvi,
								ViInt32 Count,
								ViUInt16 *OutBuf,
								ViUInt16 *InBuf);

/*--------------------------------------------------------------------------*/
/* Set sample width of mezzanine                                            */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_sample_width (ViSession mvi,
								ViUInt16 io,
								ViUInt32 Width);
/*--------------------------------------------------------------------------*/
/* Query sample width of mezzanine                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_sample_width_q (ViSession mvi,
								ViUInt16 io,
								ViUInt32 *Width);
/*--------------------------------------------------------------------------*/
/* Set delay of first mezzanine sample                                      */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_first_delay (ViSession mvi,
								ViUInt16 io,
								ViUInt32 FirstDelay);
/*--------------------------------------------------------------------------*/
/* Query delay of first mezzanine sample                                    */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_first_delay_q (ViSession mvi,
								ViUInt16 io,
								ViUInt32 *FirstDelay);
/*--------------------------------------------------------------------------*/
/* Allocate memory for mezzanine                                            */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_alloc (ViSession mvi,
								ViUInt16 io,
								ViUInt32 Size,
								ViUInt32 *Addr);
/*--------------------------------------------------------------------------*/
/* Query mezzanine allocated memory                                         */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_alloc_q (ViSession mvi,
								ViUInt16 io,
								ViUInt32 *Size,
								ViUInt32 *Addr);
/*--------------------------------------------------------------------------*/
/* Switch mezzanine mode:single, block or cycle                             */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_mode (ViSession mvi,
								ViUInt16 io,
								ViUInt16 Mode);
/*--------------------------------------------------------------------------*/
/* Query mezzanine mode:single, block or cycle                             */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_mode_q (ViSession mvi,
								ViUInt16 io,
								ViUInt16 *Mode);
/*--------------------------------------------------------------------------*/
/* Switch mezzanine START signal mode: pulse or level                       */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_trig_length (ViSession mvi,
								ViUInt16 Mode);
/*--------------------------------------------------------------------------*/
/* Query mezzanine START signal mode: pulse or level                        */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_trig_length_q (ViSession mvi,
								ViUInt16 *Mode);
/*--------------------------------------------------------------------------*/
/* Setup mezzanine trigger source                                           */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_config_trigger (ViSession mvi,
										ViUInt16 io,
										ViInt16 StartSource);
/*--------------------------------------------------------------------------*/
/* Return mezzanine trigger source                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_config_trigger_q (ViSession mvi,
										ViUInt16 io,
										ViInt16 *StartSource);
/*--------------------------------------------------------------------------*/
/* Set mezzanine sampling frequency                                         */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_clock (ViSession mvi,
								ViUInt16 io,
								ViUInt32 Divisor);
/*--------------------------------------------------------------------------*/
/* Query mezzanine sampling frequency                                       */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_clock_q (ViSession mvi,
								ViUInt16 io,
								ViUInt32 *Divisor);
/*--------------------------------------------------------------------------*/
/* Set mezzanine block size                                                 */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_block_size (ViSession mvi,
								ViUInt16 io,
								ViUInt32 Size);
/*--------------------------------------------------------------------------*/
/* Query mezzanine block size                                               */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_block_size_q (ViSession mvi,
								ViUInt16 io,
								ViUInt32 *Size);
/*--------------------------------------------------------------------------*/
/* Set mezzanine subblock                                                   */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_subblock (ViSession mvi,
								ViUInt16 io,
								ViUInt32 Idx,
								ViUInt32 Size);
/*--------------------------------------------------------------------------*/
/* Set and Start mezzanine subblock                                         */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_subblock_start (ViSession mvi,
								ViUInt16 io,
								ViUInt32 Idx,
								ViUInt32 Size);
/*--------------------------------------------------------------------------*/
/* Query mezzanine subblock                                                 */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_subblock_q (ViSession mvi,
								ViUInt16 io,
								ViUInt32 *Idx,
								ViUInt32 *Size);
/*--------------------------------------------------------------------------*/
/* Set mezzanine loop size                                                */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_loop_size (ViSession mvi,
								ViUInt16 io,
								ViUInt32 Size);
/*--------------------------------------------------------------------------*/
/* Query mezzanine loop size                                               */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_loop_size_q (ViSession mvi,
								ViUInt16 io,
								ViUInt32 *Size);

/*--------------------------------------------------------------------------*/
/* Set mezzanine loop segment config                                        */
/* (do not switch anything)                                                 */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_segment (ViSession mvi,
								ViUInt16 io,
								ViUInt32 Segment,
								ViUInt32 Offset,
								ViUInt32 Size);
/*--------------------------------------------------------------------------*/
/* Query mezzanine loop segment config                                      */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_segment_q (ViSession mvi,
								ViUInt16 io,
								ViUInt32 Segment,
								ViUInt32 *Offset,
								ViUInt32 *Size);
/*--------------------------------------------------------------------------*/
/* Switch mezzanine loop segment                                            */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_segment_switch (ViSession mvi,
								ViUInt16 io,
								ViUInt32 Segment,
								ViBoolean mode);
/*--------------------------------------------------------------------------*/
/* Query current mezzanine loop segment                                     */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_segment_cur_q (ViSession mvi,
								ViUInt16 io,
								ViUInt32 *Segment);

/*--------------------------------------------------------------------------*/
/* Set mezzanine packet size                                                */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_packet_size (ViSession mvi,
								ViUInt16 io,
								ViUInt32 Size);
/*--------------------------------------------------------------------------*/
/* Query mezzanine packet size                                              */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_packet_size_q (ViSession mvi,
								ViUInt16 io,
								ViUInt32 *Size);
/*--------------------------------------------------------------------------*/
/* Install user IRQ handler                                                 */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_handler (ViSession mvi,
								ViAddr Handler);
/*--------------------------------------------------------------------------*/
/* Enable/Disable Events                                                    */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_config_event (ViSession mvi,
								ViBoolean enable);
/*--------------------------------------------------------------------------*/
/* Query event enabled                                                      */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_config_event_q (ViSession mvi,
								ViBoolean *enable,
								ViBoolean *m_enable);
/*--------------------------------------------------------------------------*/
/* Read Last Sample                                                         */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_read_last (ViSession mvi,
									ViUInt32 Buff[],
									ViUInt32 *firstTime,
									ViUInt32 *thisTime);
/*--------------------------------------------------------------------------*/
/* Read Data Array                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_read_block (ViSession mvi,
									ViUInt32 Idx,
									ViUInt32 NSamples,
									ViUInt32 Buff[]);
/*--------------------------------------------------------------------------*/
/* Read next ready samples when cycle mode run                              */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_read_packet (ViSession mvi,
										ViUInt32 NSamples,
										ViUInt32 Buff[],
										ViUInt32 *ReadNSamples);
/*--------------------------------------------------------------------------*/
/* Read last samples when cycle mode run                                    */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_read_last_packet (ViSession mvi,
										ViUInt32 NSamples,
										ViUInt32 Buff[],
										ViUInt32 *ReadNSamples);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_write_block (ViSession mvi,
										ViUInt32 Idx,
										ViUInt32 NSamples,
										ViUInt32 Buff[]);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_write_packet (ViSession mvi,
										ViUInt32 NSamples,
										ViUInt32 Buff[],
										ViUInt32 *WriteNSamples);
/*--------------------------------------------------------------------------*/
/* Read Data Array from Segment                                             */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_read_segment (ViSession mvi,
										ViUInt16 io,
										ViUInt32 Segment,
										ViUInt32 Idx,
										ViUInt32 NSamples,
										ViUInt32 Buff[]);
/*--------------------------------------------------------------------------*/
/* Write Data Array to Segment                                              */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_write_segment (ViSession mvi,
										ViUInt16 io,
										ViUInt32 Segment,
										ViUInt32 Idx,
										ViUInt32 NSamples,
										ViUInt32 Buff[]);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_start (ViSession mvi,
								ViUInt16 io);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_stop (ViSession mvi,
								ViUInt16 io);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_async_stop (ViSession mvi,
								ViUInt16 io);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_state (ViSession mvi,
									ViUInt16 io,
									ViInt16 *State);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_reset (ViSession mvi,
									ViUInt16 io);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_type_q (ViSession vi,
									ViInt16 N,
									ViInt16 *Present,
									ViInt16 *Type);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_mem_q (ViSession vi,
								ViUInt32 *MemSize);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_time_q (ViSession vi,
								ViUInt32 *time);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_config_trigger (ViSession vi,
										ViInt16 StartSource,
										ViInt16 Master,
										ViInt16 TTLTRGline);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_config_trigger_q (ViSession vi,
										ViInt16 *StartSource,
										ViInt16 *Master,
										ViInt16 *TTLTRGline);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_config_ticks (ViSession vi,
										ViInt16 time);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_config_ticks_q (ViSession vi,
										ViInt16 *time);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_start (ViSession vi);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_stop (ViSession vi);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_state (ViSession vi,
								ViInt16 *State);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_time_sync (ViSession vi, ViBoolean dosync);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_howmuch_data_q (ViSession mvi,
									ViUInt16 io,
									ViUInt32 *howmuch);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_reset (ViSession vi);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_self_test (ViSession vi,
									ViInt16 *TestResult,
									ViChar _VI_FAR TestMessage[]);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_error_query (ViSession vi,
										ViInt32 *Error,
										ViChar _VI_FAR ErrorMessage[]);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_error_message (ViSession vi,
										ViStatus Status,
										ViChar _VI_FAR ErrorMessage[]);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_revision_query (ViSession vi,
										ViChar _VI_FAR HardRevision[],
										ViChar _VI_FAR SoftRevision[]);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_close (ViSession vi);

/*--------------------------------------------------------------------------*/
/* Utility functions for internal usage                                     */
/*--------------------------------------------------------------------------*/
typedef void *UNMBASE_MUTEX_TYPE;

ViStatus _VI_FUNCC unmbase_data_read(ViSession vi,
						  ViUInt32 A,   //global RAM address
						  ViUInt32 N,   //number of bytes
						  ViPUInt8 Buff);
ViStatus _VI_FUNCC unmbase_data_write(ViSession vi,
						ViUInt32 A, //global RAM address
						ViUInt32 N, //number of bytes
						ViPUInt8 Buff);
//for old compatibility
ViStatus _VI_FUNCC unmbase_blk_read(ViSession vi,
						  ViUInt32 A,   //global RAM address
						  ViUInt32 N,   //number of bytes
						  ViPUInt8 Buff,
						  ViInt32 mez);	//дл€ отладки - кто блокирует...
ViStatus _VI_FUNCC unmbase_blk_write(ViSession vi,
						ViUInt32 A, //global RAM address
						ViUInt32 N, //number of bytes
						ViPUInt8 Buff,
						ViInt32 mez);	//дл€ отладки - кто блокирует...


_UNMBASE_API ViReal64 _VI_FUNC unmbase_util_timer(void);

_UNMBASE_API void _VI_FUNC unmbase_util_delay(ViReal64 d);

//return 1 if already exist
_UNMBASE_API ViStatus _VI_FUNC unmbase_util_mutex_open(
								ViChar *mutexName,
								UNMBASE_MUTEX_TYPE *hMutex);

_UNMBASE_API void _VI_FUNC unmbase_util_mutex_close(
								UNMBASE_MUTEX_TYPE hMutex);

_UNMBASE_API ViStatus _VI_FUNC unmbase_util_mutex_lock(
								UNMBASE_MUTEX_TYPE hMutex,
								ViUInt32 s_tmo);	//Number of seconds!!!

_UNMBASE_API ViStatus _VI_FUNC unmbase_util_mutexes_lock(
								ViUInt32 nMutexes,
								UNMBASE_MUTEX_TYPE *hMutexes,
								ViUInt32 s_tmo);	//Number of seconds!!!

_UNMBASE_API void _VI_FUNC unmbase_util_mutex_unlock(
								UNMBASE_MUTEX_TYPE hMutex);

#if defined(__cplusplus) || defined(__cplusplus__)
		}       //extern "C" {
#endif

#endif  //_UNMBASE_HEADER
