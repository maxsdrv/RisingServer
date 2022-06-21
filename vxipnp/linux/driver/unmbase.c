/*
   HISTORY
10.07.2017 Версия: 3.3.4
Поддержка MezaBOX4 (версия 7), также добавили UNMBASE_TYPE_MEZABOX4M

06.06.2017 Версия: 3.3.3
1) Поддержка НМУ AXIe (версия 6) и MezaBOX4 (версия 7)
2) Увеличены задержки при прошивке АРМ НММ и MezaBOX-4M для стабильной прошивки версии 1.14/3.07

24.04.2017 Версия: 3.3.2
Улучшена работа с НММ в части перепрошивки

20.02.2017 Версия: 3.3.1
Поддержка MBaseAXIeLS.

22.09.2016 Версия: 3.3.0
Поддержка MBaseAXIe.

05.11.2014 Версия: 3.2.5
Исправлена ускоренная функция запроса (armvxi_req) для НММ.

31.10.2014 Версия: 3.2.4
Ускорена функция запроса (armvxi_req) для НММ. Попутно теперь даже при возврате ошибки возвращаются и параметры запроса.

18.07.2014 Версия: 3.2.3
Введены функции in32, out32, movein32, moveout32, unmbase_m_ioregs

10.07.2014 Версия: 3.2.2
Введены функции subblock

06.06.2014 Версия: 3.2.1
Запрос состояния на ARM-VXI и MezaBOX-4M правильно отрабатывает ошибки тип-1,тип-2

29.04.2014 Версия: 3.2.0
Поддержка MezaBOX-4M.

08.11.2013 Версия: 3.1.4
unmbase_flash_write для ARM-VXI использует REWRITE для версий прошивки начиная с 1.2.

30.10.2013 Версия: 3.1.3
1) При втором открытии и отсутствии флага сброса контроллеры повторно не загружаются.
Сделано для того, чтобы запущенная позже программа могла запросить коды моделей мезонинов,
не мешая исполнению текущей.
2) В самоконтроле НМ улучшена диагностика неисправностей записи/чтения памяти

06.09.2013: 3.1.2
Только убрана отладочная печать НММ

08.05.2013 версия 3.1.1
Изменен порядок закрытия сеанса,
Добавлено для errChk вывод SpyLog с именем функции и строчкой

03.08.2012 версия 3.1.0
Исправлена ошибка в write_packet для НМ
Добавлено управление НММ (ARM_VXI)
Добавлен атрибут UNMBASE_MATTR_CHECK_OUT_ERR для MezaBOX

21.03.2012 версия 2.32
Введена защита от зависания прерываний типа 2,
Переустановка размера пакета в loop-режиме при размере пакета 0
Переформатировали текст.

14.10.2011 версия 2.30
Введен новый атрибут ViBoolean UNMBASE_MATTR_LOCK_LASTDATA, разрешающий(по умолчанию) / запрещающий
блокировку обновления регистра последних данных на время чтения из него

22.09.2011 версия 2.29
Регистр последнего адреса читается несколько раз для исключения сбоев,
а также проверяются сбои RgSTOP
Для НМ-С новый dimm_control2.rbf с блокировкой RgSTART,STOP,LIMIT

19.04.2011 версия 2.27
Замена РБФ для НМ-С (соответствует 2.25 от 24.05.2010).


18.06.2010 версия 2.26
Восстановление задержки первых данных и длины старта после сброса.
Влияло на некоторые мезонины, если в ПО верхнего уровня проводиля сброс
носителя после сброса мезонинов.


24.05.2010 версия 2.25
Сделаны раздельные блокировки RgCOMMxx,
Заменены RBF - коррекции редко встречающихся сбоев,
Сделан контроль выхода за пределы памяти для ввода,
Поправлена стилистика *хх += ... на (*хх) += ... для совместимости на разных компиляторах

07.04.2009 версия 2.24
При сбоях чтения из памяти ввели освобождение FIFO VXI одиночным чтением до EFA_FVXI

25.02.2009 версия 2.23
1) Для синхронного НМ (версия 2А) применили RBF от версии 2 (более новый)
2) Добавили переустановку rgSTOP при изменении не только размера памяти, но и ширины кадра
для выравнивания по ширине кадра.

15.12.2008 версия 2.22
1) Для MezaBOX сделали разбиение чтения пакетов и блоков более 999900 байт
для скорости и корректности работы по USB

27.11.2008 версия 2.21
1) РБФ, появившийся в версии 2.09, убран. Вернули предыдущий. Коррекция связана с ОСЦ5

23.10.2008 версия 2.20
1) fw_rev не от i а от j.

08.07.2008 версия 2.19
1) Исправлено восстановление группового запуска для упрощенных мезонинов после сброса носителя.

23.06.2008 версия 2.18
1) Добавили блочные функции unmbase_m_movein16 иunmbase_m_moveout16.

24.04.2008 версия 2.17
1) Добавили при самоконтроле блокировку stop_in/stop_out, чтобы соседний тред во время копирования
во временную область данных сеанса не зациклил самоконтроль, а также изменили сброс при самоконтроле.
2) Добавили проверку загрузки RBF MEZ при инициализации

07.04.2008 версия 2.16
1) Добавили атрибут UNMBASE_MATTR_BASE_ID_MSG для повсеместного одинакового описания инструмента

28.03.2008 версия 2.15
1) Сделали mvi внутренний не просто индекс, а содержащий идентификатор, позволяющий отделить его от любых
сеансов, открытых VISA, т.к. сеансы Agilent VISA сейчас тоже просто индексы!

04.03.2008 версия 2.14
1) Заменили dimm_control для типа 3 НМ (с CLK10) - dimm_control3

06.02.2008 версия 2.13
1) Для упрощенных мезонинов при разрешении прерываний ошибочно разрешались прерывания по вводу-выводу.
Влияло на мезонин МС. Исправлено

30.07.2007 версия 2.12
1) Поддержка опорной частоты CLK10

24.07.2007 версия 2.11
1) Поддержка MezaBOX
2) Возврат в обработчике либо extvi либо номера сеанса мезонина.
3) В прерывании после сигнала COMPLETE (одиночный режим) сделан останов

25.05.2007 версия 2.10
1) Ввели блокировку функций останова, которые могут использоваться и в обычном треде и в треде прерываний.

21.05.2007 версия 2.09
1) Заменен РБФ для нормальной работы синхронных мезонинов
2) В самоконтроле теперь проверяем по линиям данных и D00,D01
3) Для поддержки старых драйверов мезонинов основным теперь является unmbase_32.dll
и для него сделан переходник (stub) unmbase.dll в VisualC

13.04.2007 версия 2.08
1) Ввели новые атрибуты UNMBASE_MATTR_MEZ_EXTVI и UNMBASE_MATTR_MEZ_INTVI,
которые используются для нового стиля инициализации мезонинов.
2) Сделана копия DLL как unmbase_32.dll

06.04.2007 версия 2.07
1) Заменен РБФ контроллера памяти - вставлен цифровой фильтр на синхронизации

20.02.2007 версия 2.06
1) Опять заменен РБФ для асинхронного обмена - вставлен цифровой фильтр на ПУСК
2) Теперь глобальные ошибки FIFO VXI обрабатываются на уровне прерываний и в blk_read/blk_write
3) При указании размера пакета 0 размер теперь выставляется 0x00FFFFFF, т.е. запрещается (почти)

05.12.2006 версия 2.05
1) Заменен РБФ для полной совместимости с асинхронными мезонинами (МН4В, МГВ2)
2) Вставлен дополнительный сброс в функцию самоконтроля перед закрытием сеансов
имитатора.

05.10.2006 версия 2.04
1) Заменен РБФ (коррекции по фильтраци DataValid)
2) Вставлена блокировка чтения последних данных, как по софту (Lock), так и железе,
  где запрещается теперь на время чтения обновление для всех мезонинов.
3) Коррекции в функции сброса носителя и закрытия сеанса мезонина, для правильной последовательности
  сброса и останова ввода и вывода мезонинов, т.к. останов ввода МГВ2 после сброса носителя приводил
  к ошибке самоконтроля носителя из-за неверного останова ввода имитатора.
4) Также проведены коррекции для трансляции под VisualC, который используется как компилятор
для release-версии.

20.06.2006 версия 2.03
Исправлена ф-ция m_segment_q, чтобы она работала при запущенном обмене
Также сделано прерывание по LIMIT, а не по LIMIT+1, для выдачи прерываний при переключении сегментов

06.04.2006 версия 2.02
 - Скорректирована функция запуска для приведения стартового адреса в начальное положение
 - Также сделана защита от ошибочного сигнала COMPLETE (мезонин МГВ при начале записи
данных в носитель запускал вывод на НМ. Тот выводит 1 кадр, останавливается и
выставляет COMPLETE).

18.10.2005 версия 2.01
Введены функции работы с сегментами циклического режима:
	unmbase_m_segment
	unmbase_m_segment_q
	unmbase_m_segment_switch
	unmbase_m_segment_cur_q
	unmbase_m_read_segment
	unmbase_m_write_segment
18.10.2005 версия 2.00
Введены функции длины кольца циклического режима
	unmbase_m_loop_size
	unmbase_m_loop_size_q
Добавлена поддержка Н.М.У.

01.09.2005 версия 1.07
Коррекция функции закрытия (раньше не вызывался viClose() и не освобождалась память)
Также переставлены раньше установка флагов state_in, state_out при запуске чтобы нормально отрабатывалось
прерывание при быстром завершении приема/передачи.

26.04.2005 версия 1.06
Коррекция для нормальной работы с SPD разной памяти на быстрых интерфейсах

18.06.2004 версия 1.05
1) Коррекции для нормальной работы с памятью Hyundai
2) Изменения в интерфейсе с технологической панелью для исключения лишних чтений в панели

13.05.2004 версия 1.04
Введена задержка после самоконтроля для восстановления состояния

17.02.2004 версия 1.03
Введена возможность запуска от мезонина (ф-ция unmbase_m_config_trigger)

16.12.2003 версия 1.00.02
Везде упорядочено с errChk вместо return... из середины функций
Также встроено использование unSpy.dll для TECHNO-версии
*/
#define UNMBASE_DRIVER_REVISION "4.1.0"

#include "un_cross.h"

#define _UNMBASE_API _LIB_API_EXPORT

#include "unmbase.h"

//----------------------------------
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//----------------------------------
#ifdef _CVI_
#pragma iso_9899_1999
#endif

#define USE_UNSPY

//#define EXTERNAL_RBF
//#define TECHNO
//#define DBGPRINT 1
#define CHECK_RGSTOP

#define CHECK_ARMVXI_CMD	//если определено - сразу после команды проверяем, что она дошла
//#define CHECK_ARMVXI_CMD_PRINTF
#ifndef CHECK_ARMVXI_CMD_PRINTF
#define CHECK_ARMVXI_CMD_SPY
#endif

//#define ARM_SPY_LOCKS

//#define USE_RBF2_FOR2A	//версия 2.29, НОВЫЙ dimm_control для всех

#ifdef EXTERNAL_RBF
#define DimmRbfFile "dimm_control.rbf"
#define MezRbfFile "mez_control.rbf"
#endif

#ifdef __UN_WINDOWS__

#ifdef _CVI_DEBUG_
#define UNMBASE_DEBUG_CVI
#include <utility.h>
#endif

#ifdef USE_UNSPY
const char unspy_name[] = "unspy.dll";
#endif

#else //LINUX

#ifdef USE_UNSPY
const char unspy_name[] = "libunspy.so";
#endif

#endif	//__UN_WINDOWS__

_UNMBASE_API ViReal64 _VI_FUNC unmbase_util_timer(void)
{
	return cross_timer();
}

_UNMBASE_API void _VI_FUNC unmbase_util_delay(ViReal64 d)
{
	cross_delay(d);
}

_UNMBASE_API ViStatus _VI_FUNC unmbase_util_mutex_open(
								ViChar *mutexName,
								UNMBASE_MUTEX_TYPE *phMutex)
{
	return cross_mutex_open(mutexName, phMutex);
}

_UNMBASE_API void _VI_FUNC unmbase_util_mutex_close(
								UNMBASE_MUTEX_TYPE hMutex)
{
	cross_mutex_close(hMutex);
}

_UNMBASE_API ViStatus _VI_FUNC unmbase_util_mutex_lock(
								UNMBASE_MUTEX_TYPE hMutex,
								ViUInt32 s_tmo)
{
	return cross_mutex_lock(hMutex, s_tmo);
}

_UNMBASE_API ViStatus _VI_FUNC unmbase_util_mutexes_lock(
								ViUInt32 nMutexes,
								UNMBASE_MUTEX_TYPE *hMutexes,
								ViUInt32 s_tmo)	//Number of seconds!!!
{
	return cross_mutexes_lock(nMutexes, hMutexes, s_tmo);
}

_UNMBASE_API void _VI_FUNC unmbase_util_mutex_unlock(
								UNMBASE_MUTEX_TYPE hMutex)
{
	cross_mutex_unlock(hMutex);
}


#define MAX_MEZ 4
#define CheckMezNum(globals, N) if (N<1 || N > globals->maxMez) return UNMBASE_ERROR_M_NUMBER; else


#ifndef EXTERNAL_RBF
#include "dimm_control.h"
#include "mez_control.h"
#include "dimm_control2.h"
#include "mez_control2.h"

#ifndef USE_RBF2_FOR2A
#include "dimm_control3.h"
#endif

#endif

////////////////////////////////////////////////
//  Static internal definitions and functions //
////////////////////////////////////////////////

#ifdef UNMBASE_DEBUG_CVI

#define errChk(fCall) if (status = (fCall), status < 0) {Breakpoint();goto Error;} else

#else

#define errChk(fCall) if (status = (fCall), status < 0) \
	{SpyLog2("(line %d):status=0x%08X\n", __LINE__, status);goto Error;} else

#endif

#define okChk(fCall) if (status = (fCall), 1) {goto Error;} else
#define nullChk(fCall) if ((fCall) == 0) {status = UNMBASE_ERROR_NULL_POINTER; goto Error;} else

#define notNMU(userdata) if ((userdata)->basesimple) return UNMBASE_ERROR_NOT_SUPPORT

//Определения регистров
//регистры в А16 (D16)
#define rgC         0x4 //регистр управления(W)
#define rgC_AM      VI_A16_SPACE
#define maskC_reset             ((ViUInt16)0x0001)
#define maskC_CS1               ((ViUInt16)0x0100)
#define maskC_CS2               ((ViUInt16)0x0200)
#define maskC_nCONF1            ((ViUInt16)0x0400)
#define maskC_nCONF2            ((ViUInt16)0x0800)
#define maskC_EN_A24            ((ViUInt16)0x8000)

#define rgS         0x4 //регистр статуса(R)
#define rgS_AM      VI_A16_SPACE
#define maskS_AEA_FVXI          ((ViUInt16)0x0001)
#define maskS_AFA_FVXI          ((ViUInt16)0x0002)
#define maskS_EFA_FVXI          ((ViUInt16)0x0010)
#define maskS_FFA_FVXI          ((ViUInt16)0x0020)
#define maskS_EFB_FVXI          ((ViUInt16)0x0040)
#define maskS_CS1               ((ViUInt16)0x0080)
#define maskS_CS2               ((ViUInt16)0x0100)
#define maskS_nCONF1            ((ViUInt16)0x0200)
#define maskS_nCONF2            ((ViUInt16)0x0400)
#define maskS_nstatus           ((ViUInt16)0x0800)
#define maskS_conf_done1        ((ViUInt16)0x1000)
#define maskS_conf_done2        ((ViUInt16)0x2000)

#define rgPR        0x8 //регистр признаков(R)
#define rgPR_AM     VI_A16_SPACE
#define maskPR_IRQL             ((ViUInt16)0x0007)
#define shiftPR_IRQL            0
#define maskPR_FFB_FVXI         ((ViUInt16)0x0008)

#define rgCOMM3     0xA //регистр команд(W)
#define rgCOMM3_AM  VI_A16_SPACE
#define maskCOMM3_resetFIFO_VXI     ((ViUInt16)0x0010)
#define maskCOMM3_resetFIFO_MEZ     ((ViUInt16)0x0020)
#define maskCOMM3_IRQ_IC2_RESET     ((ViUInt16)0x0040)
#define maskCOMM3_IRQ_IC3_RESET     ((ViUInt16)0x0080)
#define maskCOMM3_IRQ1_RESET        ((ViUInt16)0x0100)	//НМУ
#define maskCOMM3_IRQ2_RESET        ((ViUInt16)0x0200)	//НМУ
#define maskCOMM3_IRQ3_RESET        ((ViUInt16)0x0400)	//НМУ
#define maskCOMM3_IRQ4_RESET        ((ViUInt16)0x0800)	//НМУ
#define maskCOMM3_IRQ_ALL_RESET     ((ViUInt16)0x0F00)
#define shiftCOMM3_IRQ_ALL_RESET    8
#define maskCOMM3_CLK_DATA			((ViUInt16)0x1000)
#define maskCOMM3_CLK_CLK			((ViUInt16)0x2000)
#define maskCOMM3_CLK_STRB			((ViUInt16)0x8000)
#define maskCOMM3_START             ((ViUInt16)0x4000)	//НМУ
#define maskCOMM3_STOP              ((ViUInt16)0x8000)	//НМУ
#define rgCOMM3_DEFAULT (   maskCOMM3_IRQ_IC2_RESET |   \
							maskCOMM3_IRQ_IC3_RESET |   \
							maskCOMM3_IRQ_ALL_RESET |   \
							maskCOMM3_STOP)

#define rgCONF3     0xC //регистр конфигурации(R/W)
#define rgCONF3_AM  VI_A16_SPACE
#define maskCONF3_TTLIN_LINE        0x0007U	//НМУ
#define shiftCONF3_TTLIN_LINE       0		//НМУ
#define maskCONF3_TTLOUT_LINE       0x0038U	//НМУ
#define shiftCONF3_TTLOUT_LINE      3		//НМУ
#define maskCONF3_TTLIN_EN          0x0040U	//НМУ
#define maskCONF3_TTLOUT_EN         0x0080U	//НМУ
#define maskCONF3_CYCLE             0x0100U
#define maskCONF3_ERRLED            0x0200U	//НМУ
#define maskCONF3_TESTLOOP          0x0400U
#define maskCONF3_VERSION_MASK		0x1800U
#define maskCONF3_VERSION_1			0x1800U
#define maskCONF3_VERSION_2			0x1000U
#define maskCONF3_VERSION_2A		0x0800U
#define maskCONF3_START_SHORT_IN	0x1000U	//НМУ only
#define maskCONF3_START_SHORT_OUT	0x2000U	//НМУ only
#define maskCONF3_START_LONG_IN		0x4000U	//НМУ only
#define maskCONF3_START_LONG_OUT	0x8000U	//НМУ only
#define rgCONF3_DEFAULT         (0)

#define rgCONF_DATA 0xE //регистр данных FLEX(W)
#define rgCONF_DATA_AM      VI_A16_SPACE

#define rgSAM_DATA 0xE //регистр самоконтроля (R/W)	//НМУ only
#define rgSAM_DATA_AM      VI_A16_SPACE			//НМУ only

//////////////////////////////////////////////////
//смещения регистров мезонинов в А24 (D32)
#define offsMEZ1_REG        0x0600  //смещение области регистров мезонина 1
#define offsMEZ2_REG        0x0800  //смещение области регистров мезонина 2
#define offsMEZ3_REG        0x0A00  //смещение области регистров мезонина 3
#define offsMEZ4_REG        0x0C00  //смещение области регистров мезонина 4
#define offsSHAREDRAM       0x1000  //смещение области памяти обмена по VXI (D32)

//регистр управления переключением сегментов
#define rgCOMM11         0x298   //регистр команд 11 (R/W)
#define rgCOMM11_AM      VI_A24_SPACE
#define maskCOMM11_SW1	            0x00000001U   // |1
#define maskCOMM11_SW2	            0x00000002U   // |2
#define maskCOMM11_SW3	            0x00000004U   // |3
#define maskCOMM11_SW4	            0x00000008U   // |4

//область управления памятью
#define rgCOMM1         0x200   //регистр команд 1 (W)
#define rgCOMM1_AM      VI_A24_SPACE
#define maskCOMM1_WR_VXI            0x00000001U
#define maskCOMM1_RD_VXI            0x00000002U
#define maskCOMM1_IN1_ON            0x00000004U   // |1
#define maskCOMM1_IN2_ON            0x00000008U    // |2
#define maskCOMM1_IN3_ON            0x00000010U    // |3
#define maskCOMM1_IN4_ON            0x00000020U    // |4
//#define maskCOMM1_IN_ON               0x0000003CU    // ||||
#define shiftCOMM1_IN_ON            2               // ||||
#define maskCOMM1_OUT1_ON           0x00000040U    // |1
#define maskCOMM1_OUT2_ON           0x00000080U    // |2
#define maskCOMM1_OUT3_ON           0x00000100U    // |3
#define maskCOMM1_OUT4_ON           0x00000200U    // |4
//#define maskCOMM1_OUT_ON          0x000003C0U    // ||||
#define shiftCOMM1_OUT_ON           6               // ||||
#define maskCOMM1_ALL_ON            0x000003FCU    // ||||||||
#define shiftCOMM1_ALL_ON           2               // ||||||||
#define maskCOMM1_I2C_SDA           0x00000400U
#define shiftCOMM1_I2C_SDA          10
#define maskCOMM1_I2C_SCL           0x00000800U
#define shiftCOMM1_I2C_SCL          11
#define maskCOMM1_DIMM_INIT         0x00008000U
#define maskCOMM1_IRQ_IN1_RESET     0x00010000U    // |1
#define maskCOMM1_IRQ_IN2_RESET     0x00020000U    // |2
#define maskCOMM1_IRQ_IN3_RESET     0x00040000U    // |3
#define maskCOMM1_IRQ_IN4_RESET     0x00080000U    // |4
//#define maskCOMM1_IRQ_IN_RESET        0x000F0000U    // ||||
#define shiftCOMM1_IRQ_IN_RESET     16              // ||||
#define maskCOMM1_IRQ_OUT1_RESET    0x00100000U    // |1
#define maskCOMM1_IRQ_OUT2_RESET    0x00200000U    // |2
#define maskCOMM1_IRQ_OUT3_RESET    0x00400000U    // |3
#define maskCOMM1_IRQ_OUT4_RESET    0x00800000U    // |4
//#define maskCOMM1_IRQ_OUT_RESET       0x00F00000U    // ||||
#define shiftCOMM1_IRQ_OUT_RESET    20              // ||||
#define maskCOMM1_IRQ_ALL_RESET     0x00FF0000U    // ||||||||
#define shiftCOMM1_IRQ_ALL_RESET    16              // ||||||||
#define rgCOMM1_DEFAULT (   maskCOMM1_IRQ_ALL_RESET )

#define rgMASKCOMM1         0x204   //маска регистра команд 1 (W)

#define rgSTAT1         0x200   //регистр состояния 1 (R)
#define rgSTAT1_AM      VI_A24_SPACE
#define maskSTAT1_WR_VXI            0x00000001U
#define maskSTAT1_RD_VXI            0x00000002U
#define maskSTAT1_IN1_ON            0x00000004U    // |1
#define maskSTAT1_IN2_ON            0x00000008U    // |2
#define maskSTAT1_IN3_ON            0x00000010U    // |3
#define maskSTAT1_IN4_ON            0x00000020U    // |4
//#define maskSTAT1_IN_ON               0x0000003CU    // ||||
#define shiftSTAT1_IN_ON            2               // ||||
#define maskSTAT1_OUT1_ON           0x00000040U    // |1
#define maskSTAT1_OUT2_ON           0x00000080U    // |2
#define maskSTAT1_OUT3_ON           0x00000100U    // |3
#define maskSTAT1_OUT4_ON           0x00000200U    // |4
//#define maskSTAT1_OUT_ON          0x000003C0U    // ||||
#define shiftSTAT1_OUT_ON           6               // ||||
#define maskSTAT1_ALL_ON            0x000003FCU    // ||||||||
#define shiftSTAT1_ALL_ON           2               // ||||||||
#define maskSTAT1_I2C_SDA           0x00000400U
#define maskSTAT1_IRQ_IN1           0x00010000U    // |1
#define maskSTAT1_IRQ_IN2           0x00020000U    // |2
#define maskSTAT1_IRQ_IN3           0x00040000U    // |3
#define maskSTAT1_IRQ_IN4           0x00080000U    // |4
//#define maskSTAT1_IRQ_IN          0x000F0000U    // ||||
#define shiftSTAT1_IRQ_IN           16              // ||||
#define maskSTAT1_IRQ_OUT1          0x00100000U    // |1
#define maskSTAT1_IRQ_OUT2          0x00200000U    // |2
#define maskSTAT1_IRQ_OUT3          0x00400000U    // |3
#define maskSTAT1_IRQ_OUT4          0x00800000U    // |4
//#define maskSTAT1_IRQ_OUT         0x00F00000U    // ||||
#define shiftSTAT1_IRQ_OUT          20              // ||||
#define maskSTAT1_IRQ_ALL           0x00FF0000U    // ||||||||
#define shiftSTAT1_IRQ_ALL          16              // ||||||||

#define rgCONF1         0x208   //регистр конфигурации 1 (R/W)
#define rgCONF1_AM      VI_A24_SPACE

#define maskCONF1_EN_STARTSTOP	    0x00000001U

#define maskCONF1_FIFO_MEM_START    0x00000040U
#define maskCONF1_FIFO_VXI_B        0x00000080U
#define maskCONF1_COUNT_CONF1       0x00000100U    // |1
#define maskCONF1_COUNT_CONF2       0x00000200U    // |2
#define maskCONF1_COUNT_CONF3       0x00000400U    // |3
#define maskCONF1_COUNT_CONF4       0x00000800U    // |4
#define maskCONF1_COUNT_CONF_ALL    0x00000F00U    // ||||
#define shiftCONF1_COUNT_CONF_ALL   8               // ||||
#define maskCONF1_COL_SEL9          0x00000000U
#define maskCONF1_COL_SEL10         0x00001000U
#define maskCONF1_COL_SEL11         0x00002000U
#define maskCONF1_COL_SEL12         0x00003000U
#define maskCONF1_COL_SEL_ALL       0x00003000U
#define shiftCONF1_COL_SEL_ALL      12              // ||||
#define maskCONF1_ROW_SEL12         0x00000000U
#define maskCONF1_ROW_SEL13         0x00004000U
#define maskCONF1_ROW_SEL_ALL       0x00004000U
#define shiftCONF1_ROW_SEL_ALL      14              // ||||
#define maskCONF1_CS_SEL1           0x00000000U
#define maskCONF1_CS_SEL2           0x00008000U
#define maskCONF1_CS_SEL_ALL        0x00008000U
#define shiftCONF1_CS_SEL_ALL       15              // ||||
#define maskCONF1_IRQ_IN1_DIS       0x00010000U    // |1
#define maskCONF1_IRQ_IN2_DIS       0x00020000U    // |2
#define maskCONF1_IRQ_IN3_DIS       0x00040000U    // |3
#define maskCONF1_IRQ_IN4_DIS       0x00080000U    // |4
//#define maskCONF1_IRQ_IN_DIS          0x000F0000U    // ||||
#define shiftCONF1_IRQ_IN_DIS       16              // ||||
#define maskCONF1_IRQ_OUT1_DIS      0x00100000U    // |1
#define maskCONF1_IRQ_OUT2_DIS      0x00200000U    // |2
#define maskCONF1_IRQ_OUT3_DIS      0x00400000U    // |3
#define maskCONF1_IRQ_OUT4_DIS      0x00800000U    // |4
//#define maskCONF1_IRQ_OUT_DIS     0x00F00000U    // ||||
#define shiftCONF1_IRQ_OUT_DIS      20              // ||||
#define maskCONF1_IRQ_ALL_DIS       0x00FF0000U    // ||||||||
#define shiftCONF1_IRQ_ALL_DIS      16              // ||||||||
#define rgCONF1_DEFAULT (   maskCONF1_COUNT_CONF_ALL |  \
							maskCONF1_IRQ_ALL_DIS )
#define rgCONF1_DEFAULT_MASK (  maskCONF1_COL_SEL_ALL  |    \
								maskCONF1_ROW_SEL_ALL   |    \
								maskCONF1_CS_SEL_ALL   |    \
								maskCONF1_FIFO_MEM_START|    \
								maskCONF1_FIFO_VXI_B)


#define rgLIMIT_AM      VI_A24_SPACE
#define rgSTART_AM      VI_A24_SPACE
#define rgSTOP_AM       VI_A24_SPACE
#define rgCURRENT_AM    VI_A24_SPACE

#define rgSTART_IN1     0x210   //регистр адреса старта, 24 разряда (R/W)
#define rgSTOP_IN1      0x214   //регистр адреса стопа, 24 разряда (R/W)
#define rgCURRENT_IN1   0x218   //регистр текущего адреса, 24 разряда (R/W)
#define rgLIMIT_IN1     0x21C   //кол-во блоков до прерывания, 24 разряда (R/W)

#define rgSTART_IN2     0x220   //регистр адреса старта, 24 разряда (R/W)
#define rgSTOP_IN2      0x224   //регистр адреса стопа, 24 разряда (R/W)
#define rgCURRENT_IN2   0x228   //регистр текущего адреса, 24 разряда (R/W)
#define rgLIMIT_IN2     0x22C   //кол-во блоков до прерывания, 24 разряда (R/W)

#define rgSTART_IN3     0x230   //регистр адреса старта, 24 разряда (R/W)
#define rgSTOP_IN3      0x234   //регистр адреса стопа, 24 разряда (R/W)
#define rgCURRENT_IN3   0x238   //регистр текущего адреса, 24 разряда (R/W)
#define rgLIMIT_IN3     0x23C   //кол-во блоков до прерывания, 24 разряда (R/W)

#define rgSTART_IN4     0x240   //регистр адреса старта, 24 разряда (R/W)
#define rgSTOP_IN4      0x244   //регистр адреса стопа, 24 разряда (R/W)
#define rgCURRENT_IN4   0x248   //регистр текущего адреса, 24 разряда (R/W)
#define rgLIMIT_IN4     0x24C   //кол-во блоков до прерывания, 24 разряда (R/W)

#define rgSTART_OUT1    0x250   //регистр адреса старта, 24 разряда (R/W)
#define rgSTOP_OUT1     0x254   //регистр адреса стопа, 24 разряда (R/W)
#define rgCURRENT_OUT1  0x258   //регистр текущего адреса, 24 разряда (R/W)
#define rgLIMIT_OUT1    0x25C   //кол-во блоков до прерывания, 24 разряда (R/W)

#define rgSTART_OUT2    0x260   //регистр адреса старта, 24 разряда (R/W)
#define rgSTOP_OUT2     0x264   //регистр адреса стопа, 24 разряда (R/W)
#define rgCURRENT_OUT2  0x268   //регистр текущего адреса, 24 разряда (R/W)
#define rgLIMIT_OUT2    0x26C   //кол-во блоков до прерывания, 24 разряда (R/W)

#define rgSTART_OUT3    0x270   //регистр адреса старта, 24 разряда (R/W)
#define rgSTOP_OUT3     0x274   //регистр адреса стопа, 24 разряда (R/W)
#define rgCURRENT_OUT3  0x278   //регистр текущего адреса, 24 разряда (R/W)
#define rgLIMIT_OUT3    0x27C   //кол-во блоков до прерывания, 24 разряда (R/W)

#define rgSTART_OUT4    0x280   //регистр адреса старта, 24 разряда (R/W)
#define rgSTOP_OUT4     0x284   //регистр адреса стопа, 24 разряда (R/W)
#define rgCURRENT_OUT4  0x288   //регистр текущего адреса, 24 разряда (R/W)
#define rgLIMIT_OUT4    0x28C   //кол-во блоков до прерывания, 24 разряда (R/W)

#define rgVXI_START     0x290   //регистр адреса старта, 24 разряда (R/W)
#define rgVXI_STOP      0x294   //регистр адреса стопа, 24 разряда (R/W)
#define rgVXI_CURRENT   0x298   //регистр текущего адреса, 24 разряда (R/W)

//////////////////////////////////////////////////
//регистры управления мезонинами в А24 (D32)
#define rgCOMM2         0x400   //регистр команд 2 (W)
#define rgCOMM2_AM      VI_A24_SPACE
#define maskCOMM2_IN1_EN            0x00000001U
#define maskCOMM2_IN2_EN            0x00000002U
#define maskCOMM2_IN3_EN            0x00000004U
#define maskCOMM2_IN4_EN            0x00000008U
//#define maskCOMM2_IN_EN           0x0000000FU
#define shiftCOMM2_IN_EN        0
#define maskCOMM2_OUT1_EN           0x00000010U
#define maskCOMM2_OUT2_EN           0x00000020U
#define maskCOMM2_OUT3_EN           0x00000040U
#define maskCOMM2_OUT4_EN           0x00000080U
//#define maskCOMM2_OUT_EN      0x000000F0U
#define shiftCOMM2_OUT_EN       4
#define maskCOMM2_IN1_RST           0x00000100U
#define maskCOMM2_IN2_RST           0x00000200U
#define maskCOMM2_IN3_RST           0x00000400U
#define maskCOMM2_IN4_RST           0x00000800U
#define maskCOMM2_IN_ALL_RST        0x00000F00U
//#define maskCOMM2_IN_RST      0x00000F00U
#define shiftCOMM2_IN_RST       8
#define maskCOMM2_IN1_FLUSH         0x00001000U
#define maskCOMM2_IN2_FLUSH         0x00002000U
#define maskCOMM2_IN3_FLUSH         0x00004000U
#define maskCOMM2_IN4_FLUSH         0x00008000U
#define maskCOMM2_IN_ALL_FLUSH      0x0000F000U
//#define maskCOMM2_IN_FLUSH        0x0000F000U
#define shiftCOMM2_IN_FLUSH     12
#define maskCOMM2_ERR1_M1_RST       0x00010000U
#define maskCOMM2_ERR1_M2_RST       0x00020000U
#define maskCOMM2_ERR1_M3_RST       0x00040000U
#define maskCOMM2_ERR1_M4_RST       0x00080000U
#define maskCOMM2_ERR1_ALL_RST      0x000F0000U
#define shiftCOMM2_ERR1_ALL_RST     16
#define maskCOMM2_ERR2_M1_RST       0x00100000U
#define maskCOMM2_ERR2_M2_RST       0x00200000U
#define maskCOMM2_ERR2_M3_RST       0x00400000U
#define maskCOMM2_ERR2_M4_RST       0x00800000U
#define maskCOMM2_ERR2_ALL_RST      0x00F00000U
#define shiftCOMM2_ERR2_ALL_RST     20
#define maskCOMM2_ERR3_RST          0x01000000U
#define maskCOMM2_ERR4_RST          0x02000000U
#define maskCOMM2_IMM_RST           0x04000000U
#define maskCOMM2_LAST_RST          0x08000000U
#define maskCOMM2_LAST_IN1_DIS      0x10000000U
#define maskCOMM2_LAST_IN2_DIS      0x20000000U
#define maskCOMM2_LAST_IN3_DIS      0x40000000U
#define maskCOMM2_LAST_IN4_DIS      0x80000000U
#define maskCOMM2_LAST_ALL_DIS      0xF0000000U
#define shiftCOMM2_LAST_ALL_DIS     28
#define rgCOMM2_DEFAULT (   maskCOMM2_IN_ALL_RST    |   \
							maskCOMM2_IN_ALL_FLUSH  |   \
							maskCOMM2_ERR1_ALL_RST  |   \
							maskCOMM2_ERR2_ALL_RST  |   \
							maskCOMM2_ERR3_RST      |   \
							maskCOMM2_ERR4_RST      |   \
							maskCOMM2_IMM_RST       |   \
							maskCOMM2_LAST_RST  )

#define rgMASKCOMM2         0x414   //маска регистра команд 2 (W)

#define rgSTAT2         0x400   //регистр состояния 2 (R)
#define rgSTAT2_AM      VI_A24_SPACE
#define maskSTAT2_IN1_EN            0x00000001U
#define maskSTAT2_IN2_EN            0x00000002U
#define maskSTAT2_IN3_EN            0x00000004U
#define maskSTAT2_IN4_EN            0x00000008U
//#define maskSTAT2_IN_EN           0x0000000FU
#define shiftSTAT2_IN_EN            0
#define maskSTAT2_OUT1_EN           0x00000010U
#define maskSTAT2_OUT2_EN           0x00000020U
#define maskSTAT2_OUT3_EN           0x00000040U
#define maskSTAT2_OUT4_EN           0x00000080U
//#define maskSTAT2_OUT_EN      0x000000F0U
#define shiftSTAT2_OUT_EN           4
#define maskSTAT2_ALL_EN            0x000000FFU
#define shiftSTAT2_ALL_EN           0
#define maskSTAT2_USEDW             0x0000FC00U
#define shiftSTAT2_USEDW            10
#define maskSTAT2_ERR1_M1           0x00010000U
#define maskSTAT2_ERR1_M2           0x00020000U
#define maskSTAT2_ERR1_M3           0x00040000U
#define maskSTAT2_ERR1_M4           0x00080000U
#define maskSTAT2_ERR1_ALL          0x000F0000U
#define shiftSTAT2_ERR1_ALL         16
#define maskSTAT2_ERR2_M1           0x00100000U
#define maskSTAT2_ERR2_M2           0x00200000U
#define maskSTAT2_ERR2_M3           0x00400000U
#define maskSTAT2_ERR2_M4           0x00800000U
#define maskSTAT2_ERR2_ALL          0x00F00000U
#define shiftSTAT2_ERR2_ALL         20
#define maskSTAT2_ERR3              0x01000000U
#define maskSTAT2_ERR4              0x02000000U
#define maskSTAT2_FFB_FMEM          0x04000000U
#define maskSTAT2_OUT1_READY        0x10000000U
#define maskSTAT2_OUT2_READY        0x20000000U
#define maskSTAT2_OUT3_READY        0x40000000U
#define maskSTAT2_OUT4_READY        0x80000000U
//#define maskSTAT2_OUT_READY       0xF0000000U
#define shiftSTAT2_OUT_READY        28

//Маска по AND для очистки ненужных ошибок
//#define IGNORE_STAT2_ERRORS (~0)
//#define IGNORE_STAT2_ERRORS (~maskSTAT2_ERR1_ALL)
#define IGNORE_STAT2_ERRORS (~maskSTAT2_ERR2_ALL)
//#define IGNORE_STAT2_ERRORS (~(maskSTAT2_ERR1_ALL | maskSTAT2_ERR2_ALL))


#define rgCONF2         0x404   //регистр конфигурации 2 (W)
#define rgCONF2_AM      VI_A24_SPACE
#define maskCONF2_IN1_SINGLE        0x00000001U
#define maskCONF2_IN2_SINGLE        0x00000002U
#define maskCONF2_IN3_SINGLE        0x00000004U
#define maskCONF2_IN4_SINGLE        0x00000008U
//#define maskCONF2_IN_SINGLE       0x0000000FU
#define shiftCONF2_IN_SINGLE        0
#define maskCONF2_OUT1_SINGLE       0x00000010U
#define maskCONF2_OUT2_SINGLE       0x00000020U
#define maskCONF2_OUT3_SINGLE       0x00000040U
#define maskCONF2_OUT4_SINGLE       0x00000080U
//#define maskCONF2_OUT_SINGLE  0x000000F0U
#define shiftCONF2_OUT_SINGLE       4
#define maskCONF2_IMM_IN_ERR2       0x00000100U
#define maskCONF2_IMM_OUT_ERR2      0x00000200U
#define maskCONF2_IMM_D33           0x00000400U
#define maskCONF2_IN1_IMM           0x00000000U
#define maskCONF2_IN2_IMM           0x00001000U
#define maskCONF2_IN3_IMM           0x00002000U
#define maskCONF2_IN4_IMM           0x00003000U
//#define maskCONF2_IN_IMM      0x00003000U
#define shiftCONF2_IN_IMM           12
#define maskCONF2_OUT1_IMM          0x00000000U
#define maskCONF2_OUT2_IMM          0x00004000U
#define maskCONF2_OUT3_IMM          0x00008000U
#define maskCONF2_OUT4_IMM          0x0000C000U
//#define maskCONF2_OUT_IMM         0x0000C000U
#define shiftCONF2_OUT_IMM          14
#define maskCONF2_M1_ERR1_IRQ_DIS   0x00010000U
#define maskCONF2_M2_ERR1_IRQ_DIS   0x00020000U
#define maskCONF2_M3_ERR1_IRQ_DIS   0x00040000U
#define maskCONF2_M4_ERR1_IRQ_DIS   0x00080000U
#define maskCONF2_ALL_ERR1_IRQ_DIS  0x000F0000U
#define shiftCONF2_ALL_ERR1_IRQ_DIS 16
#define maskCONF2_M1_ERR2_IRQ_DIS   0x00100000U
#define maskCONF2_M2_ERR2_IRQ_DIS   0x00200000U
#define maskCONF2_M3_ERR2_IRQ_DIS   0x00400000U
#define maskCONF2_M4_ERR2_IRQ_DIS   0x00800000U
#define maskCONF2_ALL_ERR2_IRQ_DIS  0x00F00000U
#define shiftCONF2_ALL_ERR2_IRQ_DIS 20
#define maskCONF2_ERR3_IRQ_DIS      0x01000000U
#define maskCONF2_ERR4_IRQ_DIS      0x02000000U
#define maskCONF2_TICK_LEN          0x0C000000U
#define shiftCONF2_TICK_LEN         26
#define maskCONF2_ERR4_IRQ_DIS      0x02000000U
#define maskCONF2_RESTIME_EN        0x10000000U
#define maskCONF2_IN_CHK_EN         0x20000000U
#define maskCONF2_IMM_LOOP_EN       0x40000000U
#define rgCONF2_DEFAULT (   maskCONF2_ALL_ERR1_IRQ_DIS  |   \
							maskCONF2_ALL_ERR2_IRQ_DIS  |   \
							maskCONF2_ERR3_IRQ_DIS      |   \
							maskCONF2_ERR4_IRQ_DIS  )

#define rgTIME          0x408   //регистр времени (R)
#define rgTIME_AM       VI_A24_SPACE

#define rgCOMM2A        0x40C   //регистр команд/конфигурации 2А (W)
#define rgCOMM2A_AM     VI_A24_SPACE
#define maskCOMM2A_IN1_START        0x00000001U
#define maskCOMM2A_IN2_START        0x00000002U
#define maskCOMM2A_IN3_START        0x00000004U
#define maskCOMM2A_IN4_START        0x00000008U
//#define maskCOMM2A_IN_START       0x0000000FU
#define shiftCOMM2A_IN_START        0
#define maskCOMM2A_OUT1_START       0x00000010U
#define maskCOMM2A_OUT2_START       0x00000020U
#define maskCOMM2A_OUT3_START       0x00000040U
#define maskCOMM2A_OUT4_START       0x00000080U
//#define maskCOMM2A_OUT_START      0x000000F0U
#define shiftCOMM2A_OUT_START       4
#define maskCOMM2A_IN1_STOP         0x00000100U
#define maskCOMM2A_IN2_STOP         0x00000200U
#define maskCOMM2A_IN3_STOP         0x00000400U
#define maskCOMM2A_IN4_STOP         0x00000800U
//#define maskCOMM2A_IN_STOP            0x00000F00U
#define shiftCOMM2A_IN_STOP         8
#define maskCOMM2A_IN1_RSTFLAG      0x00001000U
#define maskCOMM2A_IN2_RSTFLAG      0x00002000U
#define maskCOMM2A_IN3_RSTFLAG      0x00004000U
#define maskCOMM2A_IN4_RSTFLAG      0x00008000U
#define maskCOMM2A_IN_ALL_RSTFLAG   0x0000F000U
//#define maskCOMM2A_IN_RSTFLAG 0x0000F000U
#define shiftCOMM2A_IN_RSTFLAG      12
#define maskCOMM2A_OUT1_RSTFLAG     0x00010000U
#define maskCOMM2A_OUT2_RSTFLAG     0x00020000U
#define maskCOMM2A_OUT3_RSTFLAG     0x00040000U
#define maskCOMM2A_OUT4_RSTFLAG     0x00080000U
#define maskCOMM2A_OUT_ALL_RSTFLAG  0x000F0000U
//#define maskCOMM2A_OUT_RSTFLAG    0x000F0000U
#define shiftCOMM2A_OUT_RSTFLAG     16
#define maskCOMM2A_M1_WAITSTOP      0x00100000U
#define maskCOMM2A_M2_WAITSTOP      0x00200000U
#define maskCOMM2A_M3_WAITSTOP      0x00400000U
#define maskCOMM2A_M4_WAITSTOP      0x00800000U
#define maskCOMM2A_ALL_WAITSTOP     0x00F00000U
#define shiftCOMM2A_ALL_WAITSTOP    20
#define maskCOMM2A_IN1_STARTCFG     0x01000000U
#define maskCOMM2A_IN2_STARTCFG     0x02000000U
#define maskCOMM2A_IN3_STARTCFG     0x04000000U
#define maskCOMM2A_IN4_STARTCFG     0x08000000U
//#define maskCOMM2A_IN_STARTCFG    0x0F000000U
#define shiftCOMM2A_IN_STARTCFG     24
#define maskCOMM2A_OUT1_STARTCFG    0x10000000U
#define maskCOMM2A_OUT2_STARTCFG    0x20000000U
#define maskCOMM2A_OUT3_STARTCFG    0x40000000U
#define maskCOMM2A_OUT4_STARTCFG    0x80000000U
//#define maskCOMM2A_OUT_STARTCFG       0xF0000000U
#define shiftCOMM2A_OUT_STARTCFG    28
#define rgCOMM2A_DEFAULT (  maskCOMM2A_IN_ALL_RSTFLAG | \
							maskCOMM2A_OUT_ALL_RSTFLAG)

#define rgSTAT2A        0x40C   //регистр состояния 2А (R)
#define rgSTAT2A_AM     VI_A24_SPACE
#define maskSTAT2A_IN1_PAE          0x00000001U
#define maskSTAT2A_IN2_PAE          0x00000002U
#define maskSTAT2A_IN3_PAE          0x00000004U
#define maskSTAT2A_IN4_PAE          0x00000008U
//#define maskSTAT2A_IN_PAE     0x0000000FU
#define shiftSTAT2A_IN_PAE          0
#define maskSTAT2A_OUT1_EMPTY       0x00000010U
#define maskSTAT2A_OUT2_EMPTY       0x00000020U
#define maskSTAT2A_OUT3_EMPTY       0x00000040U
#define maskSTAT2A_OUT4_EMPTY       0x00000080U
//#define maskSTAT2A_OUT_EMPTY      0x000000F0U
#define shiftSTAT2A_OUT_EMPTY       4
#define maskSTAT2A_IN1_EMPTY        0x00000100U
#define maskSTAT2A_IN2_EMPTY        0x00000200U
#define maskSTAT2A_IN3_EMPTY        0x00000400U
#define maskSTAT2A_IN4_EMPTY        0x00000800U
//#define maskSTAT2A_IN_EMPTY       0x00000F00U
#define shiftSTAT2A_IN_EMPTY        8
#define maskSTAT2A_IN1_ON           0x00001000U
#define maskSTAT2A_IN2_ON           0x00002000U
#define maskSTAT2A_IN3_ON           0x00004000U
#define maskSTAT2A_IN4_ON           0x00008000U
//#define maskSTAT2A_IN_ON          0x0000F000U
#define shiftSTAT2A_IN_ON           12
#define maskSTAT2A_OUT1_ON          0x00010000U
#define maskSTAT2A_OUT2_ON          0x00020000U
#define maskSTAT2A_OUT3_ON          0x00040000U
#define maskSTAT2A_OUT4_ON          0x00080000U
//#define maskSTAT2A_OUT_ON         0x000F0000U
#define shiftSTAT2A_OUT_ON          16
#define maskSTAT2A_M1_WAITSTOP      0x00100000U
#define maskSTAT2A_M2_WAITSTOP      0x00200000U
#define maskSTAT2A_M3_WAITSTOP      0x00400000U
#define maskSTAT2A_M4_WAITSTOP      0x00800000U
#define maskSTAT2A_ALL_WAITSTOP     0x00F00000U
#define shiftSTAT2A_ALL_WAITSTOP    20
#define maskSTAT2A_IN1_STARTCFG     0x01000000U
#define maskSTAT2A_IN2_STARTCFG     0x02000000U
#define maskSTAT2A_IN3_STARTCFG     0x04000000U
#define maskSTAT2A_IN4_STARTCFG     0x08000000U
//#define maskSTAT2A_IN_STARTCFG    0x0F000000U
#define shiftSTAT2A_IN_STARTCFG     24
#define maskSTAT2A_OUT1_STARTCFG    0x10000000U
#define maskSTAT2A_OUT2_STARTCFG    0x20000000U
#define maskSTAT2A_OUT3_STARTCFG    0x40000000U
#define maskSTAT2A_OUT4_STARTCFG    0x80000000U
//#define maskSTAT2A_OUT_STARTCFG   0xF0000000U
#define shiftSTAT2A_OUT_STARTCFG    28
#define maskSTAT2A_ALL_STARTCFG     0xFF000000U
#define shiftSTAT2A_ALL_STARTCFG    24

#define rgENDIRQ            0x410   //регистр запрещения прерываний по концу + команды сброса буферов вывода.(W)
#define maskENDIRQ_IN1_DIS          0x00000001U
#define maskENDIRQ_IN2_DIS          0x00000002U
#define maskENDIRQ_IN3_DIS          0x00000004U
#define maskENDIRQ_IN4_DIS          0x00000008U
#define maskENDIRQ_IN_ALL_DIS       0x0000000FU
//#define maskENDIRQ_IN_DIS         00000FU
#define shiftENDIRQ_IN_DIS          0
#define maskENDIRQ_OUT1_DIS         0x00000010U
#define maskENDIRQ_OUT2_DIS         0x00000020U
#define maskENDIRQ_OUT3_DIS         0x00000040U
#define maskENDIRQ_OUT4_DIS         0x00000080U
#define maskENDIRQ_OUT_ALL_DIS      0x000000F0U
//#define maskENDIRQ_OUT_DIS        0x000000F0U
#define shiftENDIRQ_OUT_DIS         4
#define maskENDIRQ_OUT1_BUF_RST     0x10000000U
#define maskENDIRQ_OUT2_BUF_RST     0x20000000U
#define maskENDIRQ_OUT3_BUF_RST     0x40000000U
#define maskENDIRQ_OUT4_BUF_RST     0x80000000U
#define maskENDIRQ_OUT_ALL_BUFF_RST 0xF0000000U
//#define maskENDIRQ_OUT_BUF_RST    0xF0000000U
#define shiftENDIRQ_OUT_BUF_RST     28
#define rgENDIRQ_DEFAULT (  maskENDIRQ_IN_ALL_DIS       |   \
							maskENDIRQ_OUT_ALL_DIS  |   \
							maskENDIRQ_OUT_ALL_BUFF_RST )

#define rgCOMPLETE          0x410   //регистр флагов завершения (R)
#define maskCOMPLETE_IN1            0x01000000U
#define maskCOMPLETE_IN2            0x02000000U
#define maskCOMPLETE_IN3            0x04000000U
#define maskCOMPLETE_IN4            0x08000000U
//#define maskCOMPLETE_IN           0x0F000000U
#define shiftCOMPLETE_IN            24
#define maskCOMPLETE_OUT1           0x10000000U
#define maskCOMPLETE_OUT2           0x20000000U
#define maskCOMPLETE_OUT3           0x40000000U
#define maskCOMPLETE_OUT4           0x80000000U
//#define maskCOMPLETE_IN           0xF0000000U
#define shiftCOMPLETE_OUT           28

#define rgLASTDATA_AM   VI_A24_SPACE
#define rgNWORDS_AM     VI_A24_SPACE
#define rgZ_AM          VI_A24_SPACE
#define rgP_AM          VI_A24_SPACE

#define rgLASTDATA_IN1      0x420   //регистр последних данных (R)
#define rgLASTDATA_IN2      0x424   //регистр последних данных (R)
#define rgLASTDATA_IN3      0x428   //регистр последних данных (R)
#define rgLASTDATA_IN4      0x42C   //регистр последних данных (R)

#define rgNWORDS_IN1        0x420   //регистр кол-ва слов (W)
#define rgNWORDS_IN2        0x424   //регистр кол-ва слов (W)
#define rgNWORDS_IN3        0x428   //регистр кол-ва слов (W)
#define rgNWORDS_IN4        0x42C   //регистр кол-ва слов (W)
#define rgNWORDS_OUT1       0x430   //регистр кол-ва слов (W)
#define rgNWORDS_OUT2       0x434   //регистр кол-ва слов (W)
#define rgNWORDS_OUT3       0x438   //регистр кол-ва слов (W)
#define rgNWORDS_OUT4       0x43C   //регистр кол-ва слов (W)
#define maskNWORDS_S_WIDTH          0x0000000FU
#define shiftNWORDS_S_WIDTH         0
#define maskNWORDS_B_LENGTH         0xFFFF0000U
#define shiftNWORDS_B_LENGTH        16


#define rgZ_IN1         0x440   //задержка ввода (R/W)
#define rgP_IN1         0x444   //период ввода (R/W)
#define rgZ_IN2         0x448   //задержка ввода (R/W)
#define rgP_IN2         0x44C   //период ввода (R/W)
#define rgZ_IN3         0x450   //задержка ввода (R/W)
#define rgP_IN3         0x454   //период ввода (R/W)
#define rgZ_IN4         0x458   //задержка ввода (R/W)
#define rgP_IN4         0x45C   //период ввода (R/W)
#define rgZ_OUT1        0x460   //задержка вывода (R/W)
#define rgP_OUT1        0x464   //период вывода (R/W)
#define rgZ_OUT2        0x468   //задержка вывода (R/W)
#define rgP_OUT2        0x46C   //период вывода (R/W)
#define rgZ_OUT3        0x470   //задержка вывода (R/W)
#define rgP_OUT3        0x474   //период вывода (R/W)
#define rgZ_OUT4        0x478   //задержка вывода (R/W)
#define rgP_OUT4        0x47C   //период вывода (R/W)

static const ViUInt16 maskCOMM3_IRQ_RESET[4] =
{
	maskCOMM3_IRQ1_RESET,
	maskCOMM3_IRQ2_RESET,
	maskCOMM3_IRQ3_RESET,
	maskCOMM3_IRQ4_RESET
};
static const ViUInt32 maskCOMM1_IN_ON[4] =
{
	maskCOMM1_IN1_ON,
	maskCOMM1_IN2_ON,
	maskCOMM1_IN3_ON,
	maskCOMM1_IN4_ON
};
static const ViUInt32 maskCOMM1_OUT_ON[4] =
{
	maskCOMM1_OUT1_ON,
	maskCOMM1_OUT2_ON,
	maskCOMM1_OUT3_ON,
	maskCOMM1_OUT4_ON
};
static const ViUInt32 maskCOMM1_IRQ_IN_RESET[4] =
{
	maskCOMM1_IRQ_IN1_RESET,
	maskCOMM1_IRQ_IN2_RESET,
	maskCOMM1_IRQ_IN3_RESET,
	maskCOMM1_IRQ_IN4_RESET
};
static const ViUInt32 maskCOMM1_IRQ_OUT_RESET[4] =
{
	maskCOMM1_IRQ_OUT1_RESET,
	maskCOMM1_IRQ_OUT2_RESET,
	maskCOMM1_IRQ_OUT3_RESET,
	maskCOMM1_IRQ_OUT4_RESET
};
static const ViUInt32 maskSTAT1_IN_ON[4] =
{
	maskSTAT1_IN1_ON,
	maskSTAT1_IN2_ON,
	maskSTAT1_IN3_ON,
	maskSTAT1_IN4_ON
};
static const ViUInt32 maskSTAT1_OUT_ON[4] =
{
	maskSTAT1_OUT1_ON,
	maskSTAT1_OUT2_ON,
	maskSTAT1_OUT3_ON,
	maskSTAT1_OUT4_ON
};
static const ViUInt32 maskSTAT1_IRQ_IN[4] =
{
	maskSTAT1_IRQ_IN1,
	maskSTAT1_IRQ_IN2,
	maskSTAT1_IRQ_IN3,
	maskSTAT1_IRQ_IN4
};
static const ViUInt32 maskSTAT1_IRQ_OUT[4] =
{
	maskSTAT1_IRQ_OUT1,
	maskSTAT1_IRQ_OUT2,
	maskSTAT1_IRQ_OUT3,
	maskSTAT1_IRQ_OUT4
};
static const ViUInt32 maskCONF1_COUNT_CONF[4] =
{
	maskCONF1_COUNT_CONF1,
	maskCONF1_COUNT_CONF2,
	maskCONF1_COUNT_CONF3,
	maskCONF1_COUNT_CONF4
};
static const ViUInt32 maskCONF1_IRQ_IN_DIS[4] =
{
	maskCONF1_IRQ_IN1_DIS,
	maskCONF1_IRQ_IN2_DIS,
	maskCONF1_IRQ_IN3_DIS,
	maskCONF1_IRQ_IN4_DIS
};
static const ViUInt32 maskCONF1_IRQ_OUT_DIS[4] =
{
	maskCONF1_IRQ_OUT1_DIS,
	maskCONF1_IRQ_OUT2_DIS,
	maskCONF1_IRQ_OUT3_DIS,
	maskCONF1_IRQ_OUT4_DIS
};
static const ViUInt32 maskCOMM2_IN_EN[4] =
{
	maskCOMM2_IN1_EN,
	maskCOMM2_IN2_EN,
	maskCOMM2_IN3_EN,
	maskCOMM2_IN4_EN
};
static const ViUInt32 maskCOMM2_OUT_EN[4] =
{
	maskCOMM2_OUT1_EN,
	maskCOMM2_OUT2_EN,
	maskCOMM2_OUT3_EN,
	maskCOMM2_OUT4_EN
};
static const ViUInt32 maskCOMM2_IN_RST[4] =
{
	maskCOMM2_IN1_RST,
	maskCOMM2_IN2_RST,
	maskCOMM2_IN3_RST,
	maskCOMM2_IN4_RST
};
/*
static const ViUInt32 maskCOMM2_IN_FLUSH[4] =
{
	maskCOMM2_IN1_FLUSH,
	maskCOMM2_IN2_FLUSH,
	maskCOMM2_IN3_FLUSH,
	maskCOMM2_IN4_FLUSH
};
*/
static const ViUInt32 maskCOMM2_ERR1_M_RST[4] =
{
	maskCOMM2_ERR1_M1_RST,
	maskCOMM2_ERR1_M2_RST,
	maskCOMM2_ERR1_M3_RST,
	maskCOMM2_ERR1_M4_RST
};
static const ViUInt32 maskCOMM2_ERR2_M_RST[4] =
{
	maskCOMM2_ERR2_M1_RST,
	maskCOMM2_ERR2_M2_RST,
	maskCOMM2_ERR2_M3_RST,
	maskCOMM2_ERR2_M4_RST
};
/*
static const ViUInt32 maskCOMM2_LAST_IN_DIS[4] =
{
	maskCOMM2_LAST_IN1_DIS,
	maskCOMM2_LAST_IN2_DIS,
	maskCOMM2_LAST_IN3_DIS,
	maskCOMM2_LAST_IN4_DIS
};
*/
static const ViUInt32 maskSTAT2_IN_EN[4] =
{
	maskSTAT2_IN1_EN,
	maskSTAT2_IN2_EN,
	maskSTAT2_IN3_EN,
	maskSTAT2_IN4_EN
};
static const ViUInt32 maskSTAT2_OUT_EN[4] =
{
	maskSTAT2_OUT1_EN,
	maskSTAT2_OUT2_EN,
	maskSTAT2_OUT3_EN,
	maskSTAT2_OUT4_EN
};
static const ViUInt32 maskSTAT2_ERR1_M[4] =
{
	maskSTAT2_ERR1_M1,
	maskSTAT2_ERR1_M2,
	maskSTAT2_ERR1_M3,
	maskSTAT2_ERR1_M4
};
static const ViUInt32 maskSTAT2_ERR2_M[4] =
{
	maskSTAT2_ERR2_M1,
	maskSTAT2_ERR2_M2,
	maskSTAT2_ERR2_M3,
	maskSTAT2_ERR2_M4
};
static const ViUInt32 maskSTAT2_OUT_READY[4] =
{
	maskSTAT2_OUT1_READY,
	maskSTAT2_OUT2_READY,
	maskSTAT2_OUT3_READY,
	maskSTAT2_OUT4_READY
};
static const ViUInt32 maskCONF2_IN_SINGLE[4] =
{
	maskCONF2_IN1_SINGLE,
	maskCONF2_IN2_SINGLE,
	maskCONF2_IN3_SINGLE,
	maskCONF2_IN4_SINGLE
};
static const ViUInt32 maskCONF2_OUT_SINGLE[4] =
{
	maskCONF2_OUT1_SINGLE,
	maskCONF2_OUT2_SINGLE,
	maskCONF2_OUT3_SINGLE,
	maskCONF2_OUT4_SINGLE
};
static const ViUInt32 maskCONF2_IN_IMM[4] =
{
	maskCONF2_IN1_IMM,
	maskCONF2_IN2_IMM,
	maskCONF2_IN3_IMM,
	maskCONF2_IN4_IMM
};
static const ViUInt32 maskCONF2_OUT_IMM[4] =
{
	maskCONF2_OUT1_IMM,
	maskCONF2_OUT2_IMM,
	maskCONF2_OUT3_IMM,
	maskCONF2_OUT4_IMM
};
static const ViUInt32 maskCONF2_M_ERR1_IRQ_DIS[4] =
{
	maskCONF2_M1_ERR1_IRQ_DIS,
	maskCONF2_M2_ERR1_IRQ_DIS,
	maskCONF2_M3_ERR1_IRQ_DIS,
	maskCONF2_M4_ERR1_IRQ_DIS
};
static const ViUInt32 maskCONF2_M_ERR2_IRQ_DIS[4] =
{
	maskCONF2_M1_ERR2_IRQ_DIS,
	maskCONF2_M2_ERR2_IRQ_DIS,
	maskCONF2_M3_ERR2_IRQ_DIS,
	maskCONF2_M4_ERR2_IRQ_DIS
};
static const ViUInt32 maskCOMM2A_IN_START[4] =
{
	maskCOMM2A_IN1_START,
	maskCOMM2A_IN2_START,
	maskCOMM2A_IN3_START,
	maskCOMM2A_IN4_START
};
static const ViUInt32 maskCOMM2A_OUT_START[4] =
{
	maskCOMM2A_OUT1_START,
	maskCOMM2A_OUT2_START,
	maskCOMM2A_OUT3_START,
	maskCOMM2A_OUT4_START
};
static const ViUInt32 maskCOMM2A_IN_STOP[4] =
{
	maskCOMM2A_IN1_STOP,
	maskCOMM2A_IN2_STOP,
	maskCOMM2A_IN3_STOP,
	maskCOMM2A_IN4_STOP
};
static const ViUInt32 maskCOMM2A_IN_RSTFLAG[4] =
{
	maskCOMM2A_IN1_RSTFLAG,
	maskCOMM2A_IN2_RSTFLAG,
	maskCOMM2A_IN3_RSTFLAG,
	maskCOMM2A_IN4_RSTFLAG
};
static const ViUInt32 maskCOMM2A_OUT_RSTFLAG[4] =
{
	maskCOMM2A_OUT1_RSTFLAG,
	maskCOMM2A_OUT2_RSTFLAG,
	maskCOMM2A_OUT3_RSTFLAG,
	maskCOMM2A_OUT4_RSTFLAG
};
static const ViUInt32 maskCOMM2A_M_WAITSTOP[4] =
{
	maskCOMM2A_M1_WAITSTOP,
	maskCOMM2A_M2_WAITSTOP,
	maskCOMM2A_M3_WAITSTOP,
	maskCOMM2A_M4_WAITSTOP
};
static const ViUInt32 maskCOMM2A_IN_STARTCFG[4] =
{
	maskCOMM2A_IN1_STARTCFG,
	maskCOMM2A_IN2_STARTCFG,
	maskCOMM2A_IN3_STARTCFG,
	maskCOMM2A_IN4_STARTCFG
};
static const ViUInt32 maskCOMM2A_OUT_STARTCFG[4] =
{
	maskCOMM2A_OUT1_STARTCFG,
	maskCOMM2A_OUT2_STARTCFG,
	maskCOMM2A_OUT3_STARTCFG,
	maskCOMM2A_OUT4_STARTCFG
};
/*
static const ViUInt32 maskSTAT2A_IN_PAE[4] =
{
	maskSTAT2A_IN1_PAE,
	maskSTAT2A_IN2_PAE,
	maskSTAT2A_IN3_PAE,
	maskSTAT2A_IN4_PAE
};
*/
static const ViUInt32 maskSTAT2A_OUT_EMPTY[4] =
{
	maskSTAT2A_OUT1_EMPTY,
	maskSTAT2A_OUT2_EMPTY,
	maskSTAT2A_OUT3_EMPTY,
	maskSTAT2A_OUT4_EMPTY
};
static const ViUInt32 maskSTAT2A_IN_EMPTY[4] =
{
	maskSTAT2A_IN1_EMPTY,
	maskSTAT2A_IN2_EMPTY,
	maskSTAT2A_IN3_EMPTY,
	maskSTAT2A_IN4_EMPTY
};
static const ViUInt32 maskSTAT2A_IN_ON[4] =
{
	maskSTAT2A_IN1_ON,
	maskSTAT2A_IN2_ON,
	maskSTAT2A_IN3_ON,
	maskSTAT2A_IN4_ON
};
/*
static const ViUInt32 maskSTAT2A_OUT_ON[4] =
{
	maskSTAT2A_OUT1_ON,
	maskSTAT2A_OUT2_ON,
	maskSTAT2A_OUT3_ON,
	maskSTAT2A_OUT4_ON
};
static const ViUInt32 maskSTAT2A_M_WAITSTOP[4] =
{
	maskSTAT2A_M1_WAITSTOP,
	maskSTAT2A_M2_WAITSTOP,
	maskSTAT2A_M3_WAITSTOP,
	maskSTAT2A_M4_WAITSTOP
};
static const ViUInt32 maskSTAT2A_IN_STARTCFG[4] =
{
	maskSTAT2A_IN1_STARTCFG,
	maskSTAT2A_IN2_STARTCFG,
	maskSTAT2A_IN3_STARTCFG,
	maskSTAT2A_IN4_STARTCFG
};
static const ViUInt32 maskSTAT2A_OUT_STARTCFG[4] =
{
	maskSTAT2A_OUT1_STARTCFG,
	maskSTAT2A_OUT2_STARTCFG,
	maskSTAT2A_OUT3_STARTCFG,
	maskSTAT2A_OUT4_STARTCFG
};
*/
static const ViUInt32 maskCOMPLETE_IN[4] =
{
	maskCOMPLETE_IN1,
	maskCOMPLETE_IN2,
	maskCOMPLETE_IN3,
	maskCOMPLETE_IN4
};
static const ViUInt32 maskCOMPLETE_OUT[4] =
{
	maskCOMPLETE_OUT1,
	maskCOMPLETE_OUT2,
	maskCOMPLETE_OUT3,
	maskCOMPLETE_OUT4
};
static const ViUInt32 maskENDIRQ_IN_DIS[4] =
{
	maskENDIRQ_IN1_DIS,
	maskENDIRQ_IN2_DIS,
	maskENDIRQ_IN3_DIS,
	maskENDIRQ_IN4_DIS
};
static const ViUInt32 maskENDIRQ_OUT_DIS[4] =
{
	maskENDIRQ_OUT1_DIS,
	maskENDIRQ_OUT2_DIS,
	maskENDIRQ_OUT3_DIS,
	maskENDIRQ_OUT4_DIS
};
static const ViUInt32 maskENDIRQ_OUT_BUF_RST[4] =
{
	maskENDIRQ_OUT1_BUF_RST,
	maskENDIRQ_OUT2_BUF_RST,
	maskENDIRQ_OUT3_BUF_RST,
	maskENDIRQ_OUT4_BUF_RST
};



static const ViUInt32 offsMEZ[4] = { offsMEZ1_REG, offsMEZ2_REG, offsMEZ3_REG, offsMEZ4_REG};
static const ViUInt32 rgSTART_IN[4] = { rgSTART_IN1, rgSTART_IN2, rgSTART_IN3, rgSTART_IN4};
static const ViUInt32 rgSTOP_IN[4] = { rgSTOP_IN1, rgSTOP_IN2, rgSTOP_IN3, rgSTOP_IN4};
static const ViUInt32 rgCURRENT_IN[4] = { rgCURRENT_IN1, rgCURRENT_IN2, rgCURRENT_IN3, rgCURRENT_IN4};
static const ViUInt32 rgLIMIT_IN[4] = { rgLIMIT_IN1, rgLIMIT_IN2, rgLIMIT_IN3, rgLIMIT_IN4};
static const ViUInt32 rgSTART_OUT[4] = { rgSTART_OUT1, rgSTART_OUT2, rgSTART_OUT3, rgSTART_OUT4};
static const ViUInt32 rgSTOP_OUT[4] = { rgSTOP_OUT1, rgSTOP_OUT2, rgSTOP_OUT3, rgSTOP_OUT4};
static const ViUInt32 rgCURRENT_OUT[4] = { rgCURRENT_OUT1, rgCURRENT_OUT2, rgCURRENT_OUT3, rgCURRENT_OUT4};
static const ViUInt32 rgLIMIT_OUT[4] = { rgLIMIT_OUT1, rgLIMIT_OUT2, rgLIMIT_OUT3, rgLIMIT_OUT4};
static const ViUInt32 rgLASTDATA_IN[4] = { rgLASTDATA_IN1, rgLASTDATA_IN2, rgLASTDATA_IN3, rgLASTDATA_IN4};
static const ViUInt32 rgNWORDS_IN[4] = { rgNWORDS_IN1, rgNWORDS_IN2, rgNWORDS_IN3, rgNWORDS_IN4};
static const ViUInt32 rgNWORDS_OUT[4] = { rgNWORDS_OUT1, rgNWORDS_OUT2, rgNWORDS_OUT3, rgNWORDS_OUT4};
static const ViUInt32 rgZ_IN[4] = { rgZ_IN1, rgZ_IN2, rgZ_IN3, rgZ_IN4};
static const ViUInt32 rgP_IN[4] = { rgP_IN1, rgP_IN2, rgP_IN3, rgP_IN4};
static const ViUInt32 rgZ_OUT[4] = { rgZ_OUT1, rgZ_OUT2, rgZ_OUT3, rgZ_OUT4};
static const ViUInt32 rgP_OUT[4] = { rgP_OUT1, rgP_OUT2, rgP_OUT3, rgP_OUT4};

#define MVI_ID			0xDA010000
#define MVI_ID_MASK		0xFFFF0000
#define MVI_MASK		0x0000FFFF
#define MAX_MVI			512

#define MAX_MEM_BLOCKS	16   //for 4 IN and 4 OUT and free areas between

static const char IOChar[3] = {'I', 'O', 'B'};

//////////////////ВЗАИМОДЕЙСТВИЕ С НМ-АРМ//////////////////////////

#define ARMVXI_ARM1_RAM	0x00000
#define ARMVXI_ARM2_RAM	0x20000

#define ARMVXI_ARM2_ADDR_FLAG	0x80000000	//этот флаг определяет, что обмен будет вестись с памятью второго АРМ

#define ARMVXI_NOLOCK			0
#define ARMVXI_LOCK				1
#define ARMVXI_LOCKUNLOCK		2


#define ARMVXI_TMO1			1.0				//самая длинная команда RESET - 0.75 с, остальные меньше 1 мс

//Команда и данные пересекаются элементами cmd и answ
#pragma pack(push, 4)
typedef struct _VXI_CMD_
{
	ViUInt32 data2;
	ViUInt32 data1;
	ViUInt32 data0;
	union {
		ViUInt32 cmd;
		struct {
			ViUInt32 data16		:16;
			ViUInt32 cmdhigh	:16;
		};
	};

} VXI_CMD, *pVXI_CMD;

typedef struct _VXI_ANSW_
{
	union {
		ViUInt32 answ;
		struct {
			ViUInt32 data16		:16;
			ViUInt32 answhigh	:16;
		};
	};
	ViUInt32 data0;
	ViUInt32 data1;
	ViUInt32 data2;

} VXI_ANSW, *pVXI_ANSW;
#pragma pack(pop)

//======Далее копия arm_vxi_intf.h=======
//(для разработчика - не изменять!!!)


#define VXI_CMD_ID_MASK			0xFC000000
#define VXI_CMD_ID_PLUS			0x04000000
#define VXI_CMD_ID_SHIFT		26

#define VXI_CMD_MASK_CMD		0x03FC0000		//1..7F - CMD, 0 - ANSW
#define VXI_CMD_SHIFT_CMD		19

#define VXI_CMD_MASK_MEZIDX		0x00010000		//0,1
#define VXI_CMD_SHIFT_MEZIDX	16
#define VXI_CMD_MASK_IO			0x00060000		//0,1,2
#define VXI_CMD_SHIFT_IO		17

#define VXI_CMD_MASK_WORD		0x0000FFFF

#define VXI_ANSW_FLAG_ERROR		0x00010000
#define VXI_ANSW_MASK_STATUS	0x0000FFFF

#define VXI_ANSW_MASK_WORD		0x0000FFFF


#define armvxiAreCmd(_x_)		((_x_) & VXI_CMD_MASK_CMD)
#define armvxiAreAnsw(_x_)		(0 == ((_x_) & VXI_CMD_MASK_CMD))
#define armvxiAreErr(_x_)		((_x_) & VXI_ANSW_FLAG_ERROR)
#define armvxiStatus(_x_)		((_x_) & VXI_ANSW_MASK_STATUS)

//данный макрос основан натом, что младшее слово команды - это data16, а собственно команда в младшем слове - 0
#define armvxiCmdD16(_c_,_x_)	((_c_) | (_x_))

#define armvxiSetStatus(_x_)	if (armvxiAreErr(_x_)) \
								status = (UNMBASE_ERROR_OFFSET & ~VXI_ANSW_MASK_STATUS) + armvxiStatus(_x_); else

#define armvxiMidxIoMask(_m_, _io_) ((1 & (_m_))<<VXI_CMD_SHIFT_MEZIDX) | ((_io_)<<VXI_CMD_SHIFT_IO)

#define _ARMCMD_(_x_)		((_x_) << VXI_CMD_SHIFT_CMD)
#define _ARMCMD2IDX_(_x_)	((VXI_CMD_MASK_CMD & (_x_)) >> VXI_CMD_SHIFT_CMD)

//Распределение двухпортовой памяти

#define ARMVXI_DATA_MAX_LEN		0xFF80							//максимальный объем в байтах обмена данными (для двойной буфферизации
#define ARMVXI_DATA_MAX_DWORDS	(ARMVXI_DATA_MAX_LEN/4)			//максимальный объем в словах d32 обмена данными

#define ARMVXI_IRQ				0x1FFFC							//запись сюда генерит прерывание VXI,
#define ARMVXI_IRQ_IDX			0x1FFF4							//здесь индекс последнего StatID !!!
#define ARMVXI_IRQ_BUFF			0x1FF80							//здесь массив StatID
#define ARMVXI_IRQ_BUFF_NBYTES	(ARMVXI_IRQ_IDX - ARMVXI_IRQ_BUFF)	//размер массива StatID (байт)
#define ARMVXI_IRQ_BUFF_NWORDS	(ARMVXI_IRQ_BUFF_NBYTES/4)		//размер массива StatID (слов d32)

#define ARMVXI_CMD				0x00000							//здесь структура VXI_CMD (4 слова d32)
#define ARMVXI_CMD_WORD			0x0000C							//здесь слово d32 собственно команды
#define ARMVXI_CMD2				0x00020							//здесь структура VXI_CMD (4 слова d32)
#define ARMVXI_CMD2_WORD		0x0002C							//здесь слово d32 собственно команды

#define ARMVXI_ANSW				0x0000C							//здесь структура VXI_ANSW (4 слова d32)
#define ARMVXI_ANSW_WORD		0x0000C							//здесь слово d32 собственно ответа
#define ARMVXI_ANSW2			0x0002C							//здесь структура VXI_ANSW (4 слова d32)
#define ARMVXI_ANSW2_WORD		0x0002C							//здесь слово d32 собственно ответа
#define ARMVXI_DATA				0x00040							//здесь область обмена данными
#define ARMVXI_DATA2			0x0FFC0							//здесь область обмена данными второго буфера


#define ARMCMD_NEXT_idx					1
#define ARMCMD_NEXT						_ARMCMD_(ARMCMD_NEXT_idx)
#define ARMCMD_NEXT_nout				0
#define ARMCMD_NEXT_wout				0
#define ARMCMD_NEXT_nin 				0
#define ARMCMD_NEXT_win 				0
//Команда продолжения блочного обмена

#define ARMCMD_MRDBLKq_idx				2
#define ARMCMD_MRDBLKq					_ARMCMD_(ARMCMD_MRDBLKq_idx)
#define ARMCMD_MRDBLKq_nout				2
#define ARMCMD_MRDBLKq_wout				0
#define ARMCMD_MRDBLKq_nin 				1
#define ARMCMD_MRDBLKq_win 				0
//"MRDBLKn idx,nsamples?"	Read Data Array, return NSamples * mglobals->sample_bytes_in

#define ARMCMD_MWRBLK_idx				3
#define ARMCMD_MWRBLK					_ARMCMD_(ARMCMD_MWRBLK_idx)
#define ARMCMD_MWRBLK_nout				2
#define ARMCMD_MWRBLK_wout				0
#define ARMCMD_MWRBLK_nin 				0
#define ARMCMD_MWRBLK_win 				0
//"MWRBLKn idx,nsamples"	Write Data Array, next write NSamples * mglobals->sample_bytes_out

#define ARMCMD_MRDSEGq_idx				4
#define ARMCMD_MRDSEGq					_ARMCMD_(ARMCMD_MRDSEGq_idx)
#define ARMCMD_MRDSEGq_nout				2
#define ARMCMD_MRDSEGq_wout				1
#define ARMCMD_MRDSEGq_nin 				1
#define ARMCMD_MRDSEGq_win 				0
//"MRDSEGn io,seg,idx,nsamples?"	Read Data Array from Segment, return NSamples * mglobals->sample_bytes_XX

#define ARMCMD_MWRSEG_idx				5
#define ARMCMD_MWRSEG					_ARMCMD_(ARMCMD_MWRSEG_idx)
#define ARMCMD_MWRSEG_nout				2
#define ARMCMD_MWRSEG_wout				1
#define ARMCMD_MWRSEG_nin 				0
#define ARMCMD_MWRSEG_win 				0
//"MWRSEGn io,seg,idx,nsamples"	Write Data Array to Segment, next write NSamples * mglobals->sample_bytes_XX

#define ARMCMD_MRDPACKq_idx				6
#define ARMCMD_MRDPACKq					_ARMCMD_(ARMCMD_MRDPACKq_idx)
#define ARMCMD_MRDPACKq_nout			1
#define ARMCMD_MRDPACKq_wout			0
#define ARMCMD_MRDPACKq_nin 			1
#define ARMCMD_MRDPACKq_win 			0
//"MRDPACKn maxsamples?"	Read next ready samples when cycle mode run, return nsamples and NSamples * mglobals->sample_bytes_XX

#define ARMCMD_MRDLASTPACKq_idx			7
#define ARMCMD_MRDLASTPACKq				_ARMCMD_(ARMCMD_MRDLASTPACKq_idx)
#define ARMCMD_MRDLASTPACKq_nout		1
#define ARMCMD_MRDLASTPACKq_wout		0
#define ARMCMD_MRDLASTPACKq_nin 		1
#define ARMCMD_MRDLASTPACKq_win 		0
//"MRDLASTPACKn maxsamples?"	Read last samples when cycle mode run, return nsamples and NSamples * mglobals->sample_bytes_XX

#define ARMCMD_MWRPACK_idx				8
#define ARMCMD_MWRPACK					_ARMCMD_(ARMCMD_MWRPACK_idx)
#define ARMCMD_MWRPACK_nout				1
#define ARMCMD_MWRPACK_wout				0
#define ARMCMD_MWRPACK_nin 				0
#define ARMCMD_MWRPACK_win 				0
//"MWRPACKn nsamples?"		Write samples up to free size

#define ARMCMD_MHOWDATAq_idx			9
#define ARMCMD_MHOWDATAq				_ARMCMD_(ARMCMD_MHOWDATAq_idx)
#define ARMCMD_MHOWDATAq_nout			0
#define ARMCMD_MHOWDATAq_wout			0
#define ARMCMD_MHOWDATAq_nin 			1
#define ARMCMD_MHOWDATAq_win 			0
//"MHOWDATAn io?"			Query how much data is ready

#define ARMCMD_MLASTSAMPq_idx			10
#define ARMCMD_MLASTSAMPq				_ARMCMD_(ARMCMD_MLASTSAMPq_idx)
#define ARMCMD_MLASTSAMPq_nout			0
#define ARMCMD_MLASTSAMPq_wout			0
#define ARMCMD_MLASTSAMPq_nin 			3
#define ARMCMD_MLASTSAMPq_win 			0
//"MLASTSAMPn?"				Read Last Sample, return 4+4+mglobals->sample_bytes_in

#define ARMCMD_MSEGSW_idx				11
#define ARMCMD_MSEGSW					_ARMCMD_(ARMCMD_MSEGSW_idx)
#define ARMCMD_MSEGSW_nout				1
#define ARMCMD_MSEGSW_wout				1
#define ARMCMD_MSEGSW_nin 				0
#define ARMCMD_MSEGSW_win 				0
//"MSEGSWn io,seg,mode"		Switch mezzanine loop segment

#define ARMCMD_MCURSEGq_idx				12
#define ARMCMD_MCURSEGq					_ARMCMD_(ARMCMD_MCURSEGq_idx)
#define ARMCMD_MCURSEGq_nout			0
#define ARMCMD_MCURSEGq_wout			0
#define ARMCMD_MCURSEGq_nin 			0
#define ARMCMD_MCURSEGq_win 			1
//"MCURSEGn io?"			Query current mezzanine loop segment

#define ARMCMD_STATEq_idx				13
#define ARMCMD_STATEq					_ARMCMD_(ARMCMD_STATEq_idx)
#define ARMCMD_STATEq_nout				0
#define ARMCMD_STATEq_wout				0
#define ARMCMD_STATEq_nin 				0
#define ARMCMD_STATEq_win 				1
//"STATE?"					Query state of BASE

#define ARMCMD_MINq_idx					14
#define ARMCMD_MINq						_ARMCMD_(ARMCMD_MINq_idx)
#define ARMCMD_MINq_nout				0
#define ARMCMD_MINq_wout				1
#define ARMCMD_MINq_nin 				0
#define ARMCMD_MINq_win 				1
//"MINn? addr"				Input D16 word from mezzanine memory

#define ARMCMD_MOUT_idx					15
#define ARMCMD_MOUT						_ARMCMD_(ARMCMD_MOUT_idx)
#define ARMCMD_MOUT_nout				1
#define ARMCMD_MOUT_wout				1
#define ARMCMD_MOUT_nin 				0
#define ARMCMD_MOUT_win 				0
//"MOUTn addr,data"			Output D16 word to mezzanine memory

#define ARMCMD_MINBUFq_idx				16
#define ARMCMD_MINBUFq					_ARMCMD_(ARMCMD_MINBUFq_idx)
#define ARMCMD_MINBUFq_nout				2
#define ARMCMD_MINBUFq_wout				1
#define ARMCMD_MINBUFq_nin 				0
#define ARMCMD_MINBUFq_win 				0
//"MINBUFn? addr,count,incr"	Input block of D16 words from mezzanine memory

#define ARMCMD_MOUTBUF_idx				17
#define ARMCMD_MOUTBUF					_ARMCMD_(ARMCMD_MOUTBUF_idx)
#define ARMCMD_MOUTBUF_nout				2
#define ARMCMD_MOUTBUF_wout				1
#define ARMCMD_MOUTBUF_nin 				0
#define ARMCMD_MOUTBUF_win 				0
//"MOUTBUFn addr,count,incr"	Output block of D16 words to mezzanine memory

//Get/Set Mezzanine Attributes
#define MATTR_TYPE          0x03U    //(RO)
#define MATTR_MEMBASE_IN    0x04U    //(RO)
#define MATTR_MEMSIZE_IN    0x05U    //(RO)
#define MATTR_MEMBASE_OUT   0x06U    //(RO)
#define MATTR_MEMSIZE_OUT   0x07U    //(RO)
#define MATTR_DEV_TYPE     	0x09U    //(R/W)
#define MATTR_BASE_TYPE    	0x0AU    //(R/W)
#define MATTR_ASYNC     	0x0BU    //(R/W)

#define ARMCMD_MATTR_idx				18
#define ARMCMD_MATTR					_ARMCMD_(ARMCMD_MATTR_idx)
#define ARMCMD_MATTR_nout				1
#define ARMCMD_MATTR_wout				1
#define ARMCMD_MATTR_nin				0
#define ARMCMD_MATTR_win				0

#define ARMCMD_MATTRq_idx				19
#define ARMCMD_MATTRq					_ARMCMD_(ARMCMD_MATTRq_idx)
#define ARMCMD_MATTRq_nout				0
#define ARMCMD_MATTRq_wout				1
#define ARMCMD_MATTRq_nin				1
#define ARMCMD_MATTRq_win				0

#define ARMCMD_MSWIDTH_idx				20
#define ARMCMD_MSWIDTH					_ARMCMD_(ARMCMD_MSWIDTH_idx)
#define ARMCMD_MSWIDTH_nout				0
#define ARMCMD_MSWIDTH_wout				1
#define ARMCMD_MSWIDTH_nin 				0
#define ARMCMD_MSWIDTH_win 				0

#define ARMCMD_MSWIDTHq_idx				21
#define ARMCMD_MSWIDTHq					_ARMCMD_(ARMCMD_MSWIDTHq_idx)
#define ARMCMD_MSWIDTHq_nout			0
#define ARMCMD_MSWIDTHq_wout			0
#define ARMCMD_MSWIDTHq_nin 			0
#define ARMCMD_MSWIDTHq_win 			1
//"MSWIDTHn io,width"		Set/Query sample width of mezzanine

#define ARMCMD_MFDELAY_idx				22
#define ARMCMD_MFDELAY					_ARMCMD_(ARMCMD_MFDELAY_idx)
#define ARMCMD_MFDELAY_nout				1
#define ARMCMD_MFDELAY_wout				0
#define ARMCMD_MFDELAY_nin 				0
#define ARMCMD_MFDELAY_win 				0

#define ARMCMD_MFDELAYq_idx				23
#define ARMCMD_MFDELAYq					_ARMCMD_(ARMCMD_MFDELAYq_idx)
#define ARMCMD_MFDELAYq_nout			0
#define ARMCMD_MFDELAYq_wout			0
#define ARMCMD_MFDELAYq_nin 			1
#define ARMCMD_MFDELAYq_win 			0
//"MFDELAYn io,firstdelay"	Set/Query delay of first mezzanine sample

#define ARMCMD_MMALLOC_idx				24
#define ARMCMD_MMALLOC					_ARMCMD_(ARMCMD_MMALLOC_idx)
#define ARMCMD_MMALLOC_nout				1
#define ARMCMD_MMALLOC_wout				0
#define ARMCMD_MMALLOC_nin 				2
#define ARMCMD_MMALLOC_win 				0

#define ARMCMD_MMALLOCq_idx				25
#define ARMCMD_MMALLOCq					_ARMCMD_(ARMCMD_MMALLOCq_idx)
#define ARMCMD_MMALLOCq_nout			0
#define ARMCMD_MMALLOCq_wout			0
#define ARMCMD_MMALLOCq_nin 			2
#define ARMCMD_MMALLOCq_win 			0
//"MMALLOCn io,size"		Allocate memory for mezzanine; Query offset, size

#define ARMCMD_MMODE_idx				26
#define ARMCMD_MMODE					_ARMCMD_(ARMCMD_MMODE_idx)
#define ARMCMD_MMODE_nout				0
#define ARMCMD_MMODE_wout				1
#define ARMCMD_MMODE_nin 				0
#define ARMCMD_MMODE_win 				0

#define ARMCMD_MMODEq_idx				27
#define ARMCMD_MMODEq					_ARMCMD_(ARMCMD_MMODEq_idx)
#define ARMCMD_MMODEq_nout				0
#define ARMCMD_MMODEq_wout				0
#define ARMCMD_MMODEq_nin 				1
#define ARMCMD_MMODEq_win 				0
//"MMODEn io,mode"			Set/Query mezzanine mode:single, block or cycle

#define ARMCMD_MTRLEN_idx				28
#define ARMCMD_MTRLEN					_ARMCMD_(ARMCMD_MTRLEN_idx)
#define ARMCMD_MTRLEN_nout				1
#define ARMCMD_MTRLEN_wout				1
#define ARMCMD_MTRLEN_nin 				0
#define ARMCMD_MTRLEN_win 				0

#define ARMCMD_MTRLENq_idx				29
#define ARMCMD_MTRLENq					_ARMCMD_(ARMCMD_MTRLENq_idx)
#define ARMCMD_MTRLENq_nout				0
#define ARMCMD_MTRLENq_wout				0
#define ARMCMD_MTRLENq_nin 				0
#define ARMCMD_MTRLENq_win 				1
//"MTRLENn mode"			Set/Query mezzanine START signal mode: pulse or level

#define ARMCMD_MCLOCK_idx				30
#define ARMCMD_MCLOCK					_ARMCMD_(ARMCMD_MCLOCK_idx)
#define ARMCMD_MCLOCK_nout				1
#define ARMCMD_MCLOCK_wout				0
#define ARMCMD_MCLOCK_nin 				0
#define ARMCMD_MCLOCK_win 				0

#define ARMCMD_MCLOCKq_idx				31
#define ARMCMD_MCLOCKq					_ARMCMD_(ARMCMD_MCLOCKq_idx)
#define ARMCMD_MCLOCKq_nout				0
#define ARMCMD_MCLOCKq_wout				0
#define ARMCMD_MCLOCKq_nin 				1
#define ARMCMD_MCLOCKq_win 				0
//"MCLOCKn io,divisor"		Set/Query mezzanine sampling frequency divisor

#define ARMCMD_MBSIZE_idx				32
#define ARMCMD_MBSIZE					_ARMCMD_(ARMCMD_MBSIZE_idx)
#define ARMCMD_MBSIZE_nout				1
#define ARMCMD_MBSIZE_wout				0
#define ARMCMD_MBSIZE_nin 				0
#define ARMCMD_MBSIZE_win 				0

#define ARMCMD_MBSIZEq_idx				33
#define ARMCMD_MBSIZEq					_ARMCMD_(ARMCMD_MBSIZEq_idx)
#define ARMCMD_MBSIZEq_nout				0
#define ARMCMD_MBSIZEq_wout				0
#define ARMCMD_MBSIZEq_nin 				1
#define ARMCMD_MBSIZEq_win 				0
//"MBSIZEn io,size"			Set/Query mezzanine block size

#define ARMCMD_MLSIZE_idx				34
#define ARMCMD_MLSIZE					_ARMCMD_(ARMCMD_MLSIZE_idx)
#define ARMCMD_MLSIZE_nout				1
#define ARMCMD_MLSIZE_wout				0
#define ARMCMD_MLSIZE_nin 				0
#define ARMCMD_MLSIZE_win 				0

#define ARMCMD_MLSIZEq_idx				35
#define ARMCMD_MLSIZEq					_ARMCMD_(ARMCMD_MLSIZEq_idx)
#define ARMCMD_MLSIZEq_nout				0
#define ARMCMD_MLSIZEq_wout				0
#define ARMCMD_MLSIZEq_nin 				1
#define ARMCMD_MLSIZEq_win 				0
//"MLSIZEn io,size"			Set/Query mezzanine loop size (for current segment)

#define ARMCMD_MSEG_idx					36
#define ARMCMD_MSEG						_ARMCMD_(ARMCMD_MSEG_idx)
#define ARMCMD_MSEG_nout				2
#define ARMCMD_MSEG_wout				1
#define ARMCMD_MSEG_nin 				0
#define ARMCMD_MSEG_win 				0

#define ARMCMD_MSEGq_idx				37
#define ARMCMD_MSEGq					_ARMCMD_(ARMCMD_MSEGq_idx)
#define ARMCMD_MSEGq_nout				0
#define ARMCMD_MSEGq_wout				1
#define ARMCMD_MSEGq_nin 				2
#define ARMCMD_MSEGq_win 				0
//"MSEGn io,seg,offs,size"	Set/Query mezzanine loop segment config (do not switch anything)

#define ARMCMD_MPSIZE_idx				38
#define ARMCMD_MPSIZE					_ARMCMD_(ARMCMD_MPSIZE_idx)
#define ARMCMD_MPSIZE_nout				1
#define ARMCMD_MPSIZE_wout				0
#define ARMCMD_MPSIZE_nin 				0
#define ARMCMD_MPSIZE_win 				0

#define ARMCMD_MPSIZEq_idx				39
#define ARMCMD_MPSIZEq					_ARMCMD_(ARMCMD_MPSIZEq_idx)
#define ARMCMD_MPSIZEq_nout				0
#define ARMCMD_MPSIZEq_wout				0
#define ARMCMD_MPSIZEq_nin				1
#define ARMCMD_MPSIZEq_win				0
//"MPSIZEn io,size"			Set/Query mezzanine packet size

#define ARMCMD_MCFGTRG_idx				40
#define ARMCMD_MCFGTRG					_ARMCMD_(ARMCMD_MCFGTRG_idx)
#define ARMCMD_MCFGTRG_nout				0
#define ARMCMD_MCFGTRG_wout				1
#define ARMCMD_MCFGTRG_nin 				0
#define ARMCMD_MCFGTRG_win 				0

#define ARMCMD_MCFGTRGq_idx				41
#define ARMCMD_MCFGTRGq					_ARMCMD_(ARMCMD_MCFGTRGq_idx)
#define ARMCMD_MCFGTRGq_nout			0
#define ARMCMD_MCFGTRGq_wout			0
#define ARMCMD_MCFGTRGq_nin 			0
#define ARMCMD_MCFGTRGq_win 			1
//"MCFGTRGn io,src"			Set/Query mezzanine trigger source

#define ARMCMD_MSTART_idx				42
#define ARMCMD_MSTART					_ARMCMD_(ARMCMD_MSTART_idx)
#define ARMCMD_MSTART_nout				0
#define ARMCMD_MSTART_wout				0
#define ARMCMD_MSTART_nin 				0
#define ARMCMD_MSTART_win 				0
//"MSTARTn io"				Start mezzanine

#define ARMCMD_MSTOP_idx				43
#define ARMCMD_MSTOP					_ARMCMD_(ARMCMD_MSTOP_idx)
#define ARMCMD_MSTOP_nout				0
#define ARMCMD_MSTOP_wout				0
#define ARMCMD_MSTOP_nin 				0
#define ARMCMD_MSTOP_win 				0
//"MSTOPn io"				Stop mezzanine

#define ARMCMD_MASTOP_idx				44
#define ARMCMD_MASTOP					_ARMCMD_(ARMCMD_MASTOP_idx)
#define ARMCMD_MASTOP_nout				0
#define ARMCMD_MASTOP_wout				0
#define ARMCMD_MASTOP_nin 				0
#define ARMCMD_MASTOP_win 				0
//"MASTOPn io"				Async stop mezzanine

#define ARMCMD_MSTATEq_idx				45
#define ARMCMD_MSTATEq					_ARMCMD_(ARMCMD_MSTATEq_idx)
#define ARMCMD_MSTATEq_nout				0
#define ARMCMD_MSTATEq_wout				0
#define ARMCMD_MSTATEq_nin 				0
#define ARMCMD_MSTATEq_win 				1
//"MSTATEn io?"				Query mezzanine state

#define ARMCMD_MRST_idx					46
#define ARMCMD_MRST						_ARMCMD_(ARMCMD_MRST_idx)
#define ARMCMD_MRST_nout				0
#define ARMCMD_MRST_wout				0
#define ARMCMD_MRST_nin 				0
#define ARMCMD_MRST_win 				0
//"MRSTn io"				Mezzanine RESET

#define ARMCMD_MTYPEq_idx				47
#define ARMCMD_MTYPEq					_ARMCMD_(ARMCMD_MTYPEq_idx)
#define ARMCMD_MTYPEq_nout				0
#define ARMCMD_MTYPEq_wout				0
#define ARMCMD_MTYPEq_nin 				1
#define ARMCMD_MTYPEq_win 				1
//"MTYPEn?"					Query mezzanine type

#define ARMCMD_MEMq_idx					48
#define ARMCMD_MEMq						_ARMCMD_(ARMCMD_MEMq_idx)
#define ARMCMD_MEMq_nout				0
#define ARMCMD_MEMq_wout				0
#define ARMCMD_MEMq_nin 				1
#define ARMCMD_MEMq_win 				0
//"MEM?"					Query memory size

#define ARMCMD_TIMEq_idx				49
#define ARMCMD_TIMEq					_ARMCMD_(ARMCMD_TIMEq_idx)
#define ARMCMD_TIMEq_nout				0
#define ARMCMD_TIMEq_wout				0
#define ARMCMD_TIMEq_nin 				1
#define ARMCMD_TIMEq_win 				0
//"TIME?"					Query current time	//VAV	вообще то у носителя должно быть общее время
												//		но запрашивать будем только у одного из АРМов!!!

#define ARMCMD_TICKS_idx				50
#define ARMCMD_TICKS					_ARMCMD_(ARMCMD_TICKS_idx)
#define ARMCMD_TICKS_nout				0
#define ARMCMD_TICKS_wout				1
#define ARMCMD_TICKS_nin 				0
#define ARMCMD_TICKS_win 				0

#define ARMCMD_TICKSq_idx				51
#define ARMCMD_TICKSq					_ARMCMD_(ARMCMD_TICKSq_idx)
#define ARMCMD_TICKSq_nout				0
#define ARMCMD_TICKSq_wout				0
#define ARMCMD_TICKSq_nin 				0
#define ARMCMD_TICKSq_win 				1
//"TICKS time"				Set/Query time resolution

#define ARMCMD_TRG_ARM_idx				52
#define ARMCMD_TRG_ARM					_ARMCMD_(ARMCMD_TRG_ARM_idx)
#define ARMCMD_TRG_ARM_nout				0
#define ARMCMD_TRG_ARM_wout				0
#define ARMCMD_TRG_ARM_nin 				0
#define ARMCMD_TRG_ARM_win 				0
//"START"					prepare Group START

#define ARMCMD_STOP_idx					53
#define ARMCMD_STOP						_ARMCMD_(ARMCMD_STOP_idx)
#define ARMCMD_STOP_nout				0
#define ARMCMD_STOP_wout				0
#define ARMCMD_STOP_nin 				0
#define ARMCMD_STOP_win 				0
//"STOP"					Group STOP

#define ARMCMD_TIMESYNC_idx				54
#define ARMCMD_TIMESYNC					_ARMCMD_(ARMCMD_TIMESYNC_idx)
#define ARMCMD_TIMESYNC_nout			0
#define ARMCMD_TIMESYNC_wout			1
#define ARMCMD_TIMESYNC_nin 			0
#define ARMCMD_TIMESYNC_win 			0
//"TIMESYNC dosync"			Enable Time Reset on START (TTLTRG or maskCOMM3_START)

//IRQ Subsystem
#define ARMCMD_MIRQ_ENA_idx				55	//сейчас не используем...
#define ARMCMD_MIRQ_ENA					_ARMCMD_(ARMCMD_MIRQ_ENA_idx)
#define ARMCMD_MIRQ_ENA_nout			0
#define ARMCMD_MIRQ_ENA_wout			1
#define ARMCMD_MIRQ_ENA_nin 			0
#define ARMCMD_MIRQ_ENA_win 			0

#define ARMCMD_MIRQ_ENAq_idx			56	//сейчас не используем...
#define ARMCMD_MIRQ_ENAq				_ARMCMD_(ARMCMD_MIRQ_ENAq_idx)
#define ARMCMD_MIRQ_ENAq_nout			0
#define ARMCMD_MIRQ_ENAq_wout			0
#define ARMCMD_MIRQ_ENAq_nin 			1
#define ARMCMD_MIRQ_ENAq_win 			0
//"MIRQ:ENAblen enable"		Set/Query IRQ Enable

#define ARMCMD_REVISIONq_idx			57
#define ARMCMD_REVISIONq				_ARMCMD_(ARMCMD_REVISIONq_idx)
#define ARMCMD_REVISIONq_nout			0
#define ARMCMD_REVISIONq_wout			0
#define ARMCMD_REVISIONq_nin 			3
#define ARMCMD_REVISIONq_win 			0
// Identification query

#define ARMCMD_RST_idx					58
#define ARMCMD_RST						_ARMCMD_(ARMCMD_RST_idx)
#define ARMCMD_RST_nout					0
#define ARMCMD_RST_wout					0
#define ARMCMD_RST_nin 					0
#define ARMCMD_RST_win 					0
// Reset command Mandatory

#define ARMCMD_TSTq_idx					59
#define ARMCMD_TSTq						_ARMCMD_(ARMCMD_TSTq_idx)
#define ARMCMD_TSTq_nout				0
#define ARMCMD_TSTq_wout				0
#define ARMCMD_TSTq_nin 				1
#define ARMCMD_TSTq_win 				1
// Self-test query Mandatory

//Flash EEPROM

#define ARMCMD_FLASH_ERASE_idx			60
#define ARMCMD_FLASH_ERASE				_ARMCMD_(ARMCMD_FLASH_ERASE_idx)
#define ARMCMD_FLASH_ERASE_nout			0
#define ARMCMD_FLASH_ERASE_wout			0
#define ARMCMD_FLASH_ERASE_nin 			0
#define ARMCMD_FLASH_ERASE_win 			0
//"FLASH:ERASE start,size"

#define ARMCMD_FLASH_PREPARE_DATA_idx	61
#define ARMCMD_FLASH_PREPARE_DATA		_ARMCMD_(ARMCMD_FLASH_PREPARE_DATA_idx)
#define ARMCMD_FLASH_PREPARE_DATA_nout	1
#define ARMCMD_FLASH_PREPARE_DATA_wout	0
#define ARMCMD_FLASH_PREPARE_DATA_nin 	0
#define ARMCMD_FLASH_PREPARE_DATA_win 	0
//"FLASH:WRITE addr,size,#"	Write Data Array to FLASH

#define ARMCMD_FLASH_WRITE_PREPARED_idx		62
#define ARMCMD_FLASH_WRITE_PREPARED			_ARMCMD_(ARMCMD_FLASH_WRITE_PREPARED_idx)
#define ARMCMD_FLASH_WRITE_PREPARED_nout	2
#define ARMCMD_FLASH_WRITE_PREPARED_wout	0
#define ARMCMD_FLASH_WRITE_PREPARED_nin 	0
#define ARMCMD_FLASH_WRITE_PREPARED_win 	0
//"FLASH:WRITE addr,size,#"	Write Data Array to FLASH

#define ARMCMD_FLASH_WRITE_idx			63
#define ARMCMD_FLASH_WRITE				_ARMCMD_(ARMCMD_FLASH_WRITE_idx)
#define ARMCMD_FLASH_WRITE_nout			2
#define ARMCMD_FLASH_WRITE_wout			0
#define ARMCMD_FLASH_WRITE_nin 			0
#define ARMCMD_FLASH_WRITE_win 			0
//"FLASH:WRITE addr,size,#"	Write Data Array to FLASH

#define ARMCMD_FLASH_REWRITE_idx		64
#define ARMCMD_FLASH_REWRITE			_ARMCMD_(ARMCMD_FLASH_REWRITE_idx)
#define ARMCMD_FLASH_REWRITE_nout		2
#define ARMCMD_FLASH_REWRITE_wout		0
#define ARMCMD_FLASH_REWRITE_nin 		0
#define ARMCMD_FLASH_REWRITE_win 		0
//"FLASH:REWRITE addr,size,#"	Erase and Write Data Array to FLASH

#define ARMCMD_MEMREADq_idx				65
#define ARMCMD_MEMREADq					_ARMCMD_(ARMCMD_MEMREADq_idx)
#define ARMCMD_MEMREADq_nout			2
#define ARMCMD_MEMREADq_wout			0
#define ARMCMD_MEMREADq_nin 			1
#define ARMCMD_MEMREADq_win 			0
//"MEMREAD? addr,size" Read memory

#define ARMCMD_MEMWRITE_idx				66
#define ARMCMD_MEMWRITE					_ARMCMD_(ARMCMD_MEMWRITE_idx)
#define ARMCMD_MEMWRITE_nout			2
#define ARMCMD_MEMWRITE_wout			0
#define ARMCMD_MEMWRITE_nin 			0
#define ARMCMD_MEMWRITE_win 			0
//"MEMWRITE addr,size" Read memory

#define ARMCMD_REBOOT_idx				67
#define ARMCMD_REBOOT					_ARMCMD_(ARMCMD_REBOOT_idx)
#define ARMCMD_REBOOT_nout				0
#define ARMCMD_REBOOT_wout				0
#define ARMCMD_REBOOT_nin 				0
#define ARMCMD_REBOOT_win 				0
// REBOOT !!!

#define ARMCMD_SPY_idx					68
#define ARMCMD_SPY						_ARMCMD_(ARMCMD_SPY_idx)
#define ARMCMD_SPY_nout					0
#define ARMCMD_SPY_wout					1
#define ARMCMD_SPY_nin					0
#define ARMCMD_SPY_win					0
// Enable/Disable Spy

#define ARMCMD_SPYq_idx					69
#define ARMCMD_SPYq						_ARMCMD_(ARMCMD_SPYq_idx)
#define ARMCMD_SPYq_nout				0
#define ARMCMD_SPYq_wout				0
#define ARMCMD_SPYq_nin					1
#define ARMCMD_SPYq_win					0
// Enable/Disable Spy

#define ARMCMD_STATSPY_idx				70
#define ARMCMD_STATSPY					_ARMCMD_(ARMCMD_STATSPY_idx)
#define ARMCMD_STATSPY_nout				0
#define ARMCMD_STATSPY_wout				0
#define ARMCMD_STATSPY_nin				0
#define ARMCMD_STATSPY_win				0
// Spy and clear Statistics

#define ARMCMD_GENSRQ_idx				71
#define ARMCMD_GENSRQ					_ARMCMD_(ARMCMD_GENSRQ_idx)
#define ARMCMD_GENSRQ_nout				0
#define ARMCMD_GENSRQ_wout				0
#define ARMCMD_GENSRQ_nin 				0
#define ARMCMD_GENSRQ_win 				0
// Debug Generate SRQ

#define ARMCMD_RTCq_idx					72
#define ARMCMD_RTCq						_ARMCMD_(ARMCMD_RTCq_idx)
#define ARMCMD_RTCq_nout				0
#define ARMCMD_RTCq_wout				0
#define ARMCMD_RTCq_nin 				1
#define ARMCMD_RTCq_win 				0
// Debug Get seconds counter

#define ARMCMD_MSBLOCK_idx				73
#define ARMCMD_MSBLOCK					_ARMCMD_(ARMCMD_MSBLOCK_idx)
#define ARMCMD_MSBLOCK_nout				2
#define ARMCMD_MSBLOCK_wout				0
#define ARMCMD_MSBLOCK_nin 				0
#define ARMCMD_MSBLOCK_win 				0

#define ARMCMD_MSBLOCKq_idx				74
#define ARMCMD_MSBLOCKq					_ARMCMD_(ARMCMD_MSBLOCKq_idx)
#define ARMCMD_MSBLOCKq_nout			0
#define ARMCMD_MSBLOCKq_wout			0
#define ARMCMD_MSBLOCKq_nin 			2
#define ARMCMD_MSBLOCKq_win 			0
//"MSBLOCKn io,offs,size"			Set/Query mezzanine subblock

#define ARMCMD_MSBLOCK_START_idx		75
#define ARMCMD_MSBLOCK_START			_ARMCMD_(ARMCMD_MSBLOCK_START_idx)
#define ARMCMD_MSBLOCK_START_nout		2
#define ARMCMD_MSBLOCK_START_wout		0
#define ARMCMD_MSBLOCK_START_nin 		0
#define ARMCMD_MSBLOCK_START_win 		0
//"MSBLOCK:STARTn io,offs,size"		Set and Start mezzanine subblock

#define ARMCMD_MIN32q_idx				76
#define ARMCMD_MIN32q					_ARMCMD_(ARMCMD_MIN32q_idx)
#define ARMCMD_MIN32q_nout				1
#define ARMCMD_MIN32q_wout				1
#define ARMCMD_MIN32q_nin				1
#define ARMCMD_MIN32q_win				0
//"MIN32? addr"						In D32 from mezzanine

#define ARMCMD_MOUT32_idx				77
#define ARMCMD_MOUT32					_ARMCMD_(ARMCMD_MOUT32_idx)
#define ARMCMD_MOUT32_nout				2
#define ARMCMD_MOUT32_wout				1
#define ARMCMD_MOUT32_nin				0
#define ARMCMD_MOUT32_win				0
//"MOUT32 addr,data"				Out D32 to mezzanine

#define ARMCMD_MINBUF32q_idx			78
#define ARMCMD_MINBUF32q				_ARMCMD_(ARMCMD_MINBUF32q_idx)
#define ARMCMD_MINBUF32q_nout			2
#define ARMCMD_MINBUF32q_wout			1
#define ARMCMD_MINBUF32q_nin			0
#define ARMCMD_MINBUF32q_win			0
//"MINBUF32? addr,size"				In D32 block from mezzanine

#define ARMCMD_MOUTBUF32_idx			79
#define ARMCMD_MOUTBUF32				_ARMCMD_(ARMCMD_MOUTBUF32_idx)
#define ARMCMD_MOUTBUF32_nout			2
#define ARMCMD_MOUTBUF32_wout			1
#define ARMCMD_MOUTBUF32_nin			0
#define ARMCMD_MOUTBUF32_win			0
//"MOUTBUF32 addr,size"				Out D32 block to mezzanine


#define ARMCMD_MIOREGSq_idx				80
#define ARMCMD_MIOREGSq					_ARMCMD_(ARMCMD_MIOREGSq_idx)
#define ARMCMD_MIOREGSq_nout			1
#define ARMCMD_MIOREGSq_wout			0
#define ARMCMD_MIOREGSq_nin				0
#define ARMCMD_MIOREGSq_win				0
//"MIOREGSq count,#"				In/Modify/Out D16 block to mezzanine

#define ARMCMD_MAX						80
//======конец копии arm_vxi_intf.h=======

typedef struct _sARMVXI_CMD_
{
	ViUInt32 cmd;
	ViUInt32 nout;
	ViUInt32 wout;
	ViUInt32 nin;
	ViUInt32 win;
} sARMVXI_CMD, *psARMVXI_CMD;

sARMVXI_CMD ArmVxiCmdDef[ARMCMD_MAX+1] = {
	{0,0},	//команда 0 не существует
	{ARMCMD_NEXT,
	 ARMCMD_NEXT_nout,
	 ARMCMD_NEXT_wout,
	 ARMCMD_NEXT_nin,
	 ARMCMD_NEXT_win},
	{ARMCMD_MRDBLKq,
	 ARMCMD_MRDBLKq_nout,
	 ARMCMD_MRDBLKq_wout,
	 ARMCMD_MRDBLKq_nin,
	 ARMCMD_MRDBLKq_win},
	{ARMCMD_MWRBLK,
	 ARMCMD_MWRBLK_nout,
	 ARMCMD_MWRBLK_wout,
	 ARMCMD_MWRBLK_nin,
	 ARMCMD_MWRBLK_win},
	{ARMCMD_MRDSEGq,
	 ARMCMD_MRDSEGq_nout,
	 ARMCMD_MRDSEGq_wout,
	 ARMCMD_MRDSEGq_nin,
	 ARMCMD_MRDSEGq_win},
	{ARMCMD_MWRSEG,
	 ARMCMD_MWRSEG_nout,
	 ARMCMD_MWRSEG_wout,
	 ARMCMD_MWRSEG_nin,
	 ARMCMD_MWRSEG_win},
	{ARMCMD_MRDPACKq,
	 ARMCMD_MRDPACKq_nout,
	 ARMCMD_MRDPACKq_wout,
	 ARMCMD_MRDPACKq_nin,
	 ARMCMD_MRDPACKq_win},
	{ARMCMD_MRDLASTPACKq,
	 ARMCMD_MRDLASTPACKq_nout,
	 ARMCMD_MRDLASTPACKq_wout,
	 ARMCMD_MRDLASTPACKq_nin,
	 ARMCMD_MRDLASTPACKq_win},
	{ARMCMD_MWRPACK,
	 ARMCMD_MWRPACK_nout,
	 ARMCMD_MWRPACK_wout,
	 ARMCMD_MWRPACK_nin,
	 ARMCMD_MWRPACK_win},
	{ARMCMD_MHOWDATAq,
	 ARMCMD_MHOWDATAq_nout,
	 ARMCMD_MHOWDATAq_wout,
	 ARMCMD_MHOWDATAq_nin,
	 ARMCMD_MHOWDATAq_win},
	{ARMCMD_MLASTSAMPq,
	 ARMCMD_MLASTSAMPq_nout,
	 ARMCMD_MLASTSAMPq_wout,
	 ARMCMD_MLASTSAMPq_nin,
	 ARMCMD_MLASTSAMPq_win},
	{ARMCMD_MSEGSW,
	 ARMCMD_MSEGSW_nout,
	 ARMCMD_MSEGSW_wout,
	 ARMCMD_MSEGSW_nin,
	 ARMCMD_MSEGSW_win},
	{ARMCMD_MCURSEGq,
	 ARMCMD_MCURSEGq_nout,
	 ARMCMD_MCURSEGq_wout,
	 ARMCMD_MCURSEGq_nin,
	 ARMCMD_MCURSEGq_win},
	{ARMCMD_STATEq,
	 ARMCMD_STATEq_nout,
	 ARMCMD_STATEq_wout,
	 ARMCMD_STATEq_nin,
	 ARMCMD_STATEq_win},
	{ARMCMD_MINq,
	 ARMCMD_MINq_nout,
	 ARMCMD_MINq_wout,
	 ARMCMD_MINq_nin,
	 ARMCMD_MINq_win},
	{ARMCMD_MOUT,
	 ARMCMD_MOUT_nout,
	 ARMCMD_MOUT_wout,
	 ARMCMD_MOUT_nin,
	 ARMCMD_MOUT_win},
	{ARMCMD_MINBUFq,
	 ARMCMD_MINBUFq_nout,
	 ARMCMD_MINBUFq_wout,
	 ARMCMD_MINBUFq_nin,
	 ARMCMD_MINBUFq_win},
	{ARMCMD_MOUTBUF,
	 ARMCMD_MOUTBUF_nout,
	 ARMCMD_MOUTBUF_wout,
	 ARMCMD_MOUTBUF_nin,
	 ARMCMD_MOUTBUF_win},
	{ARMCMD_MATTR,
	 ARMCMD_MATTR_nout,
	 ARMCMD_MATTR_wout,
	 ARMCMD_MATTR_nin,
	 ARMCMD_MATTR_win},
	{ARMCMD_MATTRq,
	 ARMCMD_MATTRq_nout,
	 ARMCMD_MATTRq_wout,
	 ARMCMD_MATTRq_nin,
	 ARMCMD_MATTRq_win},
	{ARMCMD_MSWIDTH,
	 ARMCMD_MSWIDTH_nout,
	 ARMCMD_MSWIDTH_wout,
	 ARMCMD_MSWIDTH_nin,
	 ARMCMD_MSWIDTH_win},
	{ARMCMD_MSWIDTHq,
	 ARMCMD_MSWIDTHq_nout,
	 ARMCMD_MSWIDTHq_wout,
	 ARMCMD_MSWIDTHq_nin,
	 ARMCMD_MSWIDTHq_win},
	{ARMCMD_MFDELAY,
	 ARMCMD_MFDELAY_nout,
	 ARMCMD_MFDELAY_wout,
	 ARMCMD_MFDELAY_nin,
	 ARMCMD_MFDELAY_win},
	{ARMCMD_MFDELAYq,
	 ARMCMD_MFDELAYq_nout,
	 ARMCMD_MFDELAYq_wout,
	 ARMCMD_MFDELAYq_nin,
	 ARMCMD_MFDELAYq_win},
	{ARMCMD_MMALLOC,
	 ARMCMD_MMALLOC_nout,
	 ARMCMD_MMALLOC_wout,
	 ARMCMD_MMALLOC_nin,
	 ARMCMD_MMALLOC_win},
	{ARMCMD_MMALLOCq,
	 ARMCMD_MMALLOCq_nout,
	 ARMCMD_MMALLOCq_wout,
	 ARMCMD_MMALLOCq_nin,
	 ARMCMD_MMALLOCq_win},
	{ARMCMD_MMODE,
	 ARMCMD_MMODE_nout,
	 ARMCMD_MMODE_wout,
	 ARMCMD_MMODE_nin,
	 ARMCMD_MMODE_win},
	{ARMCMD_MMODEq,
	 ARMCMD_MMODEq_nout,
	 ARMCMD_MMODEq_wout,
	 ARMCMD_MMODEq_nin,
	 ARMCMD_MMODEq_win},
	{ARMCMD_MTRLEN,
	 ARMCMD_MTRLEN_nout,
	 ARMCMD_MTRLEN_wout,
	 ARMCMD_MTRLEN_nin,
	 ARMCMD_MTRLEN_win},
	{ARMCMD_MTRLENq,
	 ARMCMD_MTRLENq_nout,
	 ARMCMD_MTRLENq_wout,
	 ARMCMD_MTRLENq_nin,
	 ARMCMD_MTRLENq_win},
	{ARMCMD_MCLOCK,
	 ARMCMD_MCLOCK_nout,
	 ARMCMD_MCLOCK_wout,
	 ARMCMD_MCLOCK_nin,
	 ARMCMD_MCLOCK_win},
	{ARMCMD_MCLOCKq,
	 ARMCMD_MCLOCKq_nout,
	 ARMCMD_MCLOCKq_wout,
	 ARMCMD_MCLOCKq_nin,
	 ARMCMD_MCLOCKq_win},
	{ARMCMD_MBSIZE,
	 ARMCMD_MBSIZE_nout,
	 ARMCMD_MBSIZE_wout,
	 ARMCMD_MBSIZE_nin,
	 ARMCMD_MBSIZE_win},
	{ARMCMD_MBSIZEq,
	 ARMCMD_MBSIZEq_nout,
	 ARMCMD_MBSIZEq_wout,
	 ARMCMD_MBSIZEq_nin,
	 ARMCMD_MBSIZEq_win},
	{ARMCMD_MLSIZE,
	 ARMCMD_MLSIZE_nout,
	 ARMCMD_MLSIZE_wout,
	 ARMCMD_MLSIZE_nin,
	 ARMCMD_MLSIZE_win},
	{ARMCMD_MLSIZEq,
	 ARMCMD_MLSIZEq_nout,
	 ARMCMD_MLSIZEq_wout,
	 ARMCMD_MLSIZEq_nin,
	 ARMCMD_MLSIZEq_win},
	{ARMCMD_MSEG,
	 ARMCMD_MSEG_nout,
	 ARMCMD_MSEG_wout,
	 ARMCMD_MSEG_nin,
	 ARMCMD_MSEG_win},
	{ARMCMD_MSEGq,
	 ARMCMD_MSEGq_nout,
	 ARMCMD_MSEGq_wout,
	 ARMCMD_MSEGq_nin,
	 ARMCMD_MSEGq_win},
	{ARMCMD_MPSIZE,
	 ARMCMD_MPSIZE_nout,
	 ARMCMD_MPSIZE_wout,
	 ARMCMD_MPSIZE_nin,
	 ARMCMD_MPSIZE_win},
	{ARMCMD_MPSIZEq,
	 ARMCMD_MPSIZEq_nout,
	 ARMCMD_MPSIZEq_wout,
	 ARMCMD_MPSIZEq_nin,
	 ARMCMD_MPSIZEq_win},
	{ARMCMD_MCFGTRG,
	 ARMCMD_MCFGTRG_nout,
	 ARMCMD_MCFGTRG_wout,
	 ARMCMD_MCFGTRG_nin,
	 ARMCMD_MCFGTRG_win},
	{ARMCMD_MCFGTRGq,
	 ARMCMD_MCFGTRGq_nout,
	 ARMCMD_MCFGTRGq_wout,
	 ARMCMD_MCFGTRGq_nin,
	 ARMCMD_MCFGTRGq_win},
	{ARMCMD_MSTART,
	 ARMCMD_MSTART_nout,
	 ARMCMD_MSTART_wout,
	 ARMCMD_MSTART_nin,
	 ARMCMD_MSTART_win},
	{ARMCMD_MSTOP,
	 ARMCMD_MSTOP_nout,
	 ARMCMD_MSTOP_wout,
	 ARMCMD_MSTOP_nin,
	 ARMCMD_MSTOP_win},
	{ARMCMD_MASTOP,
	 ARMCMD_MASTOP_nout,
	 ARMCMD_MASTOP_wout,
	 ARMCMD_MASTOP_nin,
	 ARMCMD_MASTOP_win},
	{ARMCMD_MSTATEq,
	 ARMCMD_MSTATEq_nout,
	 ARMCMD_MSTATEq_wout,
	 ARMCMD_MSTATEq_nin,
	 ARMCMD_MSTATEq_win},
	{ARMCMD_MRST,
	 ARMCMD_MRST_nout,
	 ARMCMD_MRST_wout,
	 ARMCMD_MRST_nin,
	 ARMCMD_MRST_win},
	{ARMCMD_MTYPEq,
	 ARMCMD_MTYPEq_nout,
	 ARMCMD_MTYPEq_wout,
	 ARMCMD_MTYPEq_nin,
	 ARMCMD_MTYPEq_win},
	{ARMCMD_MEMq,
	 ARMCMD_MEMq_nout,
	 ARMCMD_MEMq_wout,
	 ARMCMD_MEMq_nin,
	 ARMCMD_MEMq_win},
	{ARMCMD_TIMEq,
	 ARMCMD_TIMEq_nout,
	 ARMCMD_TIMEq_wout,
	 ARMCMD_TIMEq_nin,
	 ARMCMD_TIMEq_win},
	{ARMCMD_TICKS,
	 ARMCMD_TICKS_nout,
	 ARMCMD_TICKS_wout,
	 ARMCMD_TICKS_nin,
	 ARMCMD_TICKS_win},
	{ARMCMD_TICKSq,
	 ARMCMD_TICKSq_nout,
	 ARMCMD_TICKSq_wout,
	 ARMCMD_TICKSq_nin,
	 ARMCMD_TICKSq_win},
	{ARMCMD_TRG_ARM,
	 ARMCMD_TRG_ARM_nout,
	 ARMCMD_TRG_ARM_wout,
	 ARMCMD_TRG_ARM_nin,
	 ARMCMD_TRG_ARM_win},
	{ARMCMD_STOP,
	 ARMCMD_STOP_nout,
	 ARMCMD_STOP_wout,
	 ARMCMD_STOP_nin,
	 ARMCMD_STOP_win},
	{ARMCMD_TIMESYNC,
	 ARMCMD_TIMESYNC_nout,
	 ARMCMD_TIMESYNC_wout,
	 ARMCMD_TIMESYNC_nin,
	 ARMCMD_TIMESYNC_win},
	{ARMCMD_MIRQ_ENA,
	 ARMCMD_MIRQ_ENA_nout,
	 ARMCMD_MIRQ_ENA_wout,
	 ARMCMD_MIRQ_ENA_nin,
	 ARMCMD_MIRQ_ENA_win},
	{ARMCMD_MIRQ_ENAq,
	 ARMCMD_MIRQ_ENAq_nout,
	 ARMCMD_MIRQ_ENAq_wout,
	 ARMCMD_MIRQ_ENAq_nin,
	 ARMCMD_MIRQ_ENAq_win},
	{ARMCMD_REVISIONq,
	 ARMCMD_REVISIONq_nout,
	 ARMCMD_REVISIONq_wout,
	 ARMCMD_REVISIONq_nin,
	 ARMCMD_REVISIONq_win},
	{ARMCMD_RST,
	 ARMCMD_RST_nout,
	 ARMCMD_RST_wout,
	 ARMCMD_RST_nin,
	 ARMCMD_RST_win},
	{ARMCMD_TSTq,
	 ARMCMD_TSTq_nout,
	 ARMCMD_TSTq_wout,
	 ARMCMD_TSTq_nin,
	 ARMCMD_TSTq_win},
	{ARMCMD_FLASH_ERASE,
	 ARMCMD_FLASH_ERASE_nout,
	 ARMCMD_FLASH_ERASE_wout,
	 ARMCMD_FLASH_ERASE_nin,
	 ARMCMD_FLASH_ERASE_win},
	{ARMCMD_FLASH_PREPARE_DATA,
	 ARMCMD_FLASH_PREPARE_DATA_nout,
	 ARMCMD_FLASH_PREPARE_DATA_wout,
	 ARMCMD_FLASH_PREPARE_DATA_nin,
	 ARMCMD_FLASH_PREPARE_DATA_win},
	{ARMCMD_FLASH_WRITE_PREPARED,
	 ARMCMD_FLASH_WRITE_PREPARED_nout,
	 ARMCMD_FLASH_WRITE_PREPARED_wout,
	 ARMCMD_FLASH_WRITE_PREPARED_nin,
	 ARMCMD_FLASH_WRITE_PREPARED_win},
	{ARMCMD_FLASH_WRITE,
	 ARMCMD_FLASH_WRITE_nout,
	 ARMCMD_FLASH_WRITE_wout,
	 ARMCMD_FLASH_WRITE_nin,
	 ARMCMD_FLASH_WRITE_win},
	{ARMCMD_FLASH_REWRITE,
	 ARMCMD_FLASH_REWRITE_nout,
	 ARMCMD_FLASH_REWRITE_wout,
	 ARMCMD_FLASH_REWRITE_nin,
	 ARMCMD_FLASH_REWRITE_win},
	{ARMCMD_MEMREADq,
	 ARMCMD_MEMREADq_nout,
	 ARMCMD_MEMREADq_wout,
	 ARMCMD_MEMREADq_nin,
	 ARMCMD_MEMREADq_win},
	{ARMCMD_MEMWRITE,
	 ARMCMD_MEMWRITE_nout,
	 ARMCMD_MEMWRITE_wout,
	 ARMCMD_MEMWRITE_nin,
	 ARMCMD_MEMWRITE_win},
	{ARMCMD_REBOOT,
	 ARMCMD_REBOOT_nout,
	 ARMCMD_REBOOT_wout,
	 ARMCMD_REBOOT_nin,
	 ARMCMD_REBOOT_win},
	{ARMCMD_SPY,
	 ARMCMD_SPY_nout,
	 ARMCMD_SPY_wout,
	 ARMCMD_SPY_nin,
	 ARMCMD_SPY_win},
	{ARMCMD_SPYq,
	 ARMCMD_SPYq_nout,
	 ARMCMD_SPYq_wout,
	 ARMCMD_SPYq_nin,
	 ARMCMD_SPYq_win},
	{ARMCMD_STATSPY,
	 ARMCMD_STATSPY_nout,
	 ARMCMD_STATSPY_wout,
	 ARMCMD_STATSPY_nin,
	 ARMCMD_STATSPY_win},
	{ARMCMD_GENSRQ,
	 ARMCMD_GENSRQ_nout,
	 ARMCMD_GENSRQ_wout,
	 ARMCMD_GENSRQ_nin,
	 ARMCMD_GENSRQ_win},
	{ARMCMD_RTCq,
	 ARMCMD_RTCq_nout,
	 ARMCMD_RTCq_wout,
	 ARMCMD_RTCq_nin,
	 ARMCMD_RTCq_win},
	{ARMCMD_MSBLOCK,
	 ARMCMD_MSBLOCK_nout,
	 ARMCMD_MSBLOCK_wout,
	 ARMCMD_MSBLOCK_nin,
	 ARMCMD_MSBLOCK_win},
	{ARMCMD_MSBLOCKq,
	 ARMCMD_MSBLOCKq_nout,
	 ARMCMD_MSBLOCKq_wout,
	 ARMCMD_MSBLOCKq_nin,
	 ARMCMD_MSBLOCKq_win},
	{ARMCMD_MIN32q,
	 ARMCMD_MIN32q_nout,
	 ARMCMD_MIN32q_wout,
	 ARMCMD_MIN32q_nin,
	 ARMCMD_MIN32q_win},
	{ARMCMD_MOUT32,
	 ARMCMD_MOUT32_nout,
	 ARMCMD_MOUT32_wout,
	 ARMCMD_MOUT32_nin,
	 ARMCMD_MOUT32_win},
	{ARMCMD_MINBUF32q,
	 ARMCMD_MINBUF32q_nout,
	 ARMCMD_MINBUF32q_wout,
	 ARMCMD_MINBUF32q_nin,
	 ARMCMD_MINBUF32q_win},
	{ARMCMD_MOUTBUF32,
	 ARMCMD_MOUTBUF32_nout,
	 ARMCMD_MOUTBUF32_wout,
	 ARMCMD_MOUTBUF32_nin,
	 ARMCMD_MOUTBUF32_win},
	{ARMCMD_MIOREGSq,
	 ARMCMD_MIOREGSq_nout,
	 ARMCMD_MIOREGSq_wout,
	 ARMCMD_MIOREGSq_nin,
	 ARMCMD_MIOREGSq_win}
};

///////СТРУКТУРА СЕАНСА МЕЗОНИНА////////

#define BAD_IRQ_MAX		4
#define BAD_IRQ_DT		0.002

typedef struct _UserData UserData, *PUserData;
typedef struct _M_SESSION
{
	PUserData   pbase_data;     //указатель USER DATA сеанса носителя
	ViInt16		basetype;		//тип носителя: UNMBASE_TYPE_U, _1, _2, MB, ARM
	ViInt16		basesimple;		//упрощенный тип носителя
	ViInt32		baseBE;			//тип данных блочного обмена носителя - BIG_ENDIAN
	ViInt32		baseAXIe;		//дополнительно подтип MB - AXIe
	ViSession   basevi;         //UNMBASE_MATTR_BASE_VI     (RO)
	ViSession   extvi;          //UNMBASE_MATTR_MEZ_EXTVI   (R/W)
	ViUInt32    mnum;           //UNMBASE_MATTR_NUM         (RO)
	ViUInt32    midx;           //
	ViUInt16    type;           //UNMBASE_MATTR_TYPE        (RO)
	ViUInt32	dev_type;		//UNMBASE_MATTR_DEV_TYPE    (R/W)	0-common I/O, 1-simplifyed
	ViUInt32    membase_in;     //UNMBASE_MATTR_MEMBASE_IN  (RO)
	ViUInt32    memsize_in;     //UNMBASE_MATTR_MEMSIZE_IN  (RO)
	ViUInt32    membase_out;    //UNMBASE_MATTR_MEMBASE_OUT (RO)
	ViUInt32    memsize_out;    //UNMBASE_MATTR_MEMSIZE_OUT (RO)
	ViAddr      userdata;       //UNMBASE_MATTR_USER_DATA    (R/W)
	ViBoolean	async_type;		//UNMBASE_MATTR_ASYNC		(R/W)

	//для отработки зависающих прерваний
	ViReal64	badIrqTimer;
	ViInt32		badIrqCount;

	ViBoolean	dontLockLastData;		//not UNMBASE_MATTR_LOCK_LASTDATA		(R/W)

	ViBoolean	dontCheckOutErr;		//not UNMBASE_MATTR_CHECK_OUT_ERR

	ViUInt16    start_source_in;        //start source: 0-individual, 1-group, 2-from mez
	ViUInt16    start_source_out;       //start source: 0-individual, 1-group, 2-from mez
	ViInt16     state_in;           //1-run, 0-free, <0 - error
	ViInt16     state_out;          //1-run, 0-free, <0 - error
	ViUInt16    mode_in;            //mode: 0-single, 1-block, 2-cycle
	ViUInt16    mode_out;           //mode: 0-single, 1-block, 2-cycle
	ViUInt16    trig_length;        //trigger: 0-pulse, 1-level
	ViUInt32    divisor_in;         //16 MHz divisor for sampling speed setup
	ViUInt32    divisor_out;        //16 MHz divisor for sampling speed setup
	ViUInt32    first_delay_in;     //delay of first mezzanine sample
	ViUInt32    first_delay_out;    //delay of first mezzanine sample
	ViUInt32    sample_bytes_in;    //bytes width of mezzanine sample (for memory address calculation)
	ViUInt32    sample_words_in;    //32' words width of mezzanine sample
	ViUInt32    sample_bytes_out;   //bytes width of mezzanine sample (for memory address calculation)
	ViUInt32    sample_words_out;   //32' words width of mezzanine sample

	ViUInt32    block_size_in;      //block size (in block mode)
	ViUInt32    block_size_out;     //block size (in block mode)

	ViUInt32    subblock_base_in;   //block base addr (in block mode)
	ViUInt32    subblock_base_out;  //block base addr (in block mode)

	ViUInt32    subblock_size_in;   //block size (in block mode)
	ViUInt32    subblock_size_out;  //block size (in block mode)

	ViUInt32    packet_size_in;     //input packet size
	ViUInt32    packet_size_out;    //output packet size

	ViUInt32    loop_base_in;       //loop base addr (in loop mode)
	ViUInt32    loop_base_out;      //loop base addr (in loop mode)
	ViUInt32    loop_size_in;       //loop size (in loop mode)
	ViUInt32    loop_size_out;      //loop size (in loop mode)

	ViUInt32    loop_seg_in;			//segment index, 0/1
	ViUInt32    loop_seg_out;			//segment index, 0/1

	ViUInt32    loop1_base_in;     //loop base/size for segment 1
	ViUInt32    loop1_size_in;     //
	ViUInt32    loop1_base_out;    //
	ViUInt32    loop1_size_out;    //

	ViUInt32    loop2_base_in;     //loop base/size for segment 2
	ViUInt32    loop2_size_in;     //
	ViUInt32    loop2_base_out;    //
	ViUInt32    loop2_size_out;    //

	ViAddr      user_handler;       //user handler pointer
	ViBoolean   enable_m_irq;       //are IRQ from mezzanine enabled
	ViBoolean   enable_irq;         //are IRQ from base enabled

	ViUInt16    have_last_sample;   //==1 if last sample already in last_sample array
	ViUInt32    last_sample[514];   //last sample (514 for firsttime and lasttime blk read)
	ViUInt32    first_time;         //last time
	ViUInt32    last_time;          //last time

	ViUInt32    next_sample_to_in;  //last non-readed sample addr in cycle mode
	ViUInt32    next_sample_to_out; //first free to write sample addr in cycle mode
	ViUInt8     tmpblock[0x100];    //use when non-full block need to transfer
	ViUInt32    tmp_block_remain;   //how much already remain in tmpblock after previous read
	//usually equal (0x100 - next_sample_to_in & 0xFF)
	//and index in tmpblock = (0x100-tmp_block_remain) !!!

	InterlockedExchange_val stop_in_busy;  //==1 when m_stop in process !!!
	InterlockedExchange_val stop_out_busy; //==1 when m_stop in process !!!

	ViUInt32 saveRgSTART_IN;		//для контроля
	ViUInt32 saveRgSTART_OUT;		//для контроля
	ViUInt32 saveRgSTOP_IN;			//для контроля
	ViUInt32 saveRgSTOP_OUT;		//для контроля

	//для протокола ввода из регистров
	ViInt32		spy_inp_count;
	ViUInt32	spy_inp_addr;
	ViUInt16	spy_inp_data;

	ViInt16		spy_state_in;
	ViInt16		spy_state_out;

} M_SESSION, *PM_SESSION;

typedef struct _UserData
{
	ViSession vi;
	ViSession defaultRM;
	UNMBASE_MUTEX_TYPE hOpenMutex;		//используется для контроля повторного открытия
	ViUInt16 la;
	ViUInt16 mf_la;
	ViUInt16 slot;
	ViStatus init_status;
	ViStatus state;
	ViInt16	basetype;		//тип носителя: UNMBASE_TYPE_U, _1, _2, MB, ARM
	ViInt16	basesimple;		//упрощенный тип носителя
	ViInt32	baseBE;			//тип данных блочного обмена носителя - BIG_ENDIAN
	ViInt32	baseAXIe;		//дополнительно подтип MB - AXIe
	ViInt32	maxMez;			//максимальное количество мезонинов на носителе (НМ,НМУ,НММ,MezaBOX-M = 4, MezaBOX - 2)
	M_SESSION m_session[MAX_MEZ]; //сеансы мезонинов
	ViInt16 m_vi_idx[MAX_MEZ];    //индексы сеансов мезонинов в p_mvi (-1 - none)
	ViUInt8 spd1[128];      //данные SPD
	ViUInt8 spd2[128];      //данные SPD
	ViUInt32 mem_size;      //memory size
	ViInt16 tick_time;      //timer tick resolution
	ViUInt16 alloc_num[MAX_MEM_BLOCKS]; //mezzanine owners of MAX_MEM_BLOCKS ram areas (0 - free area)
	ViUInt16 alloc_io[MAX_MEM_BLOCKS];  //io owners of MAX_MEM_BLOCKS ram areas
	ViUInt32 alloc_ptr[MAX_MEM_BLOCKS]; //pointers to MAX_MEM_BLOCKS ram areas
	ViUInt32 alloc_size[MAX_MEM_BLOCKS];    //size of MAX_MEM_BLOCKS ram areas (0 - no more ram)

	ViInt16 imm_on;         //set to 1 if immitator on

	ViBoolean	is_errled;

	ViInt32	GlobalErrorIRQ;

	UNMBASE_MUTEX_TYPE	MB_busy_mutex;

	UNMBASE_MUTEX_TYPE	Mem_busy_mutex;
	UNMBASE_MUTEX_TYPE	StartStop_busy_mutex;
	ViInt32 Mem_busy_mez;		//для проверки - кто же занял его на весь таймаут...
	UNMBASE_MUTEX_TYPE	LastDta_busy_mutex;
	UNMBASE_MUTEX_TYPE	RgComm1_busy_mutex;
	UNMBASE_MUTEX_TYPE	RgComm2_busy_mutex;

	UNMBASE_MUTEX_TYPE	ARM_busy_mutex[2];
	ViInt32 ARM_busy_mez[2];		//для проверки - кто же занял его на весь таймаут...
	ViUInt32 ArmVxiCmdId[2];
	ViUInt32 ArmVxiIrqIdx[2];

	ViUInt16 start_source;
	ViUInt16 start_master;
	ViUInt16 start_ttltrg;

	ViChar	id_msg[128];		//UNMBASE_MATTR_BASE_ID_MSG
	ViChar	fw_rev[32];
	//Сохранение образов регистров
	//регистры в А16 (D16)
	ViUInt16 saveC;             //W
	/*	ViUInt16 saveCOMM3;         //W
		ViUInt16 saveCONF3;         //R/W
		//регистры управления мезонинами в А24 (D32)
		ViUInt32 saveCOMM1;         //W
		ViUInt32 saveCONF1;         //R/W
		ViUInt32 saveCOMM2;         //W
		ViUInt32 saveCONF2;         //W
		ViUInt32 saveCOMM2A;        //W
		ViUInt32 saveSTART_IN[4];   //R/W
		ViUInt32 saveSTOP_IN[4];    //R/W
		ViUInt32 saveCURRENT_IN[4]; //R/W
		ViUInt32 saveLIMIT_IN[4];   //R/W
		ViUInt32 saveSTART_OUT[4];  //R/W
		ViUInt32 saveSTOP_OUT[4];   //R/W
		ViUInt32 saveCURRENT_OUT[4];//R/W
		ViUInt32 saveLIMIT_OUT[4];  //R/W
		ViUInt32 saveNWORDS_IN[4];  //R/W
		ViUInt32 saveNWORDS_OUT[4]; //R/W
		ViUInt32 saveZ_IN[4];       //R/W
		ViUInt32 saveP_IN[4];       //R/W
		ViUInt32 saveZ_OUT[4];      //R/W
		ViUInt32 saveP_OUT[4];      //R/W */

	ViInt16 spy_state;

} UserData, *PUserData;

PM_SESSION p_mvi[MAX_MVI+1];    //указатели сеансов мезонинов

#define ChkInitStatus() if(globals->init_status) {status=globals->init_status; goto Error;} else

//#define mviChk(mvi, mglobals) if ((mvi==0) || (mvi > MAX_MVI)) {status=VI_ERROR_INV_OBJECT; goto Error;}  \*
//	mglobals = p_mvi[mvi]; if (mglobals == NULL) {status=VI_ERROR_INV_OBJECT; goto Error;} else

//Если MVI_ID==(mvi&MVI_ID_MASK) то это INTVI, иначе это EXTVI, и ищем его среди установленных
//При этом по индексу mvi достаем mglobals, а потом восстанавливаем mvi, добавляя MVI_ID
#define mviChk(mvi, mglobals) if (mvi==0) {return VI_ERROR_INV_OBJECT;}  \
	if (MVI_ID==(mvi&MVI_ID_MASK)) mvi &= MVI_MASK; else { \
		int i = MAX_MVI; \
		while (i) { if (p_mvi[i]) if (p_mvi[i]->extvi == mvi) break; i--; }	\
		if (!i) {return VI_ERROR_INV_OBJECT;} \
		mvi = i; }	\
	mglobals = p_mvi[mvi]; mvi |= MVI_ID; \
	if ((mglobals == NULL)  || (!mglobals->basevi)) {return VI_ERROR_INV_OBJECT;} else

#define mglobalsChk(mglobals) if ((mglobals == NULL) || (!mglobals->basevi)) {return VI_ERROR_INV_OBJECT;} else

#define mbusyChk(mvi, mglobals, io)  if (io ? (mglobals->state_out>0) : (mglobals->state_in>0)) {	\
	if (mglobals->basetype == UNMBASE_TYPE_ARM || (mglobals->basetype & UNMBASE_FLAG_MB)) {		\
		ViInt16 state;		errChk(unmbase_m_state(mvi, io, &state));							\
		if (io ? (mglobals->state_out>0) : (mglobals->state_in>0)) {							\
			status=UNMBASE_ERROR_BUSY; goto Error;}												\
	} else { status=UNMBASE_ERROR_BUSY; goto Error;} } else

#define invalidViBooleanRange(val)          ((val != VI_FALSE && val != VI_TRUE) ? VI_TRUE : VI_FALSE)
#define invalidViInt16Range(val, min, max)  ((val < min || val > max) ? VI_TRUE : VI_FALSE)
#define invalidViInt32Range(val, min, max)  ((val < min || val > max) ? VI_TRUE : VI_FALSE)
#define invalidViUInt16Range(val, min, max) ((val < min || val > max) ? VI_TRUE : VI_FALSE)
#define invalidViUInt32Range(val, min, max) ((val < min || val > max) ? VI_TRUE : VI_FALSE)
#define invalidViReal64Range(val, min, max) ((val < min || val > max) ? VI_TRUE : VI_FALSE)


static ViStatus _VI_FUNC unmbase_m_stop_out(PM_SESSION mglobals);
static ViStatus _VI_FUNC unmbase_m_stop_in(PM_SESSION mglobals);

#define bswap32(x)	\
	((((x) & 0xff000000) >> 24) |	\
	 (((x) & 0x00ff0000) >>  8) |	\
	 (((x) & 0x0000ff00) <<  8) |	\
	 (((x) & 0x000000ff) << 24))

static void memcpy_swap32(void *dst, const void*src, int size)
{
	while (size > 0)
	{
		*(ViUInt32*)dst = bswap32(*(ViUInt32*)src);
		src = ((char*)src)+4;
		dst = ((char*)dst)+4;
		size-=4;
	}
}

static void mem_swap32(void *src, int size)
{
	while (size > 0)
	{
		*(ViUInt32*)src = bswap32(*(ViUInt32*)src);
		src = ((char*)src)+4;
		size-=4;
	}
}
///////////////////UNSPY////////////////////
#ifdef USE_UNSPY

#define SPY_ERR		1
#define SPY_MSG		2
#define SPY_ALL		0xFFFF
#define SPY_F_USER	0x10	//User defined filter
#define SPY_F_USER2	0x20	//User defined filter
#define SPY_F_USER3	0x40	//User defined filter

typedef void (__cdecl* PunFSpyLog) (int filter, const char *fmt, ...);
typedef int  (__cdecl* PunSpyReason) (int spy_reason);
typedef void (__cdecl* PunFRSpyLog) (int reason, int filter, const char *fmt, ...);

static PunFSpyLog unFSpyLog = NULL;
static PunFRSpyLog unFRSpyLog = NULL;
static PunSpyReason unSpyReason = NULL;
static HMODULE HMod=0;

#define ErrSpyLog(_1)  if (unFRSpyLog) unFRSpyLog(SPY_ERR, SPY_F_USER, _1); else
#define ErrSpyLog1(_1, _2)  if (unFRSpyLog) unFRSpyLog(SPY_ERR, SPY_F_USER, _1, _2); else
#define ErrSpyLog2(_1, _2, _3)  if (unFRSpyLog) unFRSpyLog(SPY_ERR, SPY_F_USER, _1, _2, _3); else
#define ErrSpyLog3(_1, _2, _3, _4)  if (unFRSpyLog) unFRSpyLog(SPY_ERR, SPY_F_USER, _1, _2, _3, _4); else
#define ErrSpyLog4(_1, _2, _3, _4, _5)  if (unFRSpyLog) unFRSpyLog(SPY_ERR, SPY_F_USER, _1, _2, _3, _4, _5); else

#define SpyLog(_1)  if (unFSpyLog) unFSpyLog(SPY_F_USER, _1); else
#define SpyLog1(_1, _2) if (unFSpyLog) unFSpyLog(SPY_F_USER, _1, _2); else
#define SpyLog2(_1, _2, _3) if (unFSpyLog) unFSpyLog(SPY_F_USER, _1, _2, _3); else
#define SpyLog3(_1, _2, _3, _4) if (unFSpyLog) unFSpyLog(SPY_F_USER, _1, _2, _3, _4); else
#define SpyLog4(_1, _2, _3, _4, _5) if (unFSpyLog) unFSpyLog(SPY_F_USER, _1, _2, _3, _4, _5); else
#define SpyLog5(_1, _2, _3, _4, _5, _6) if (unFSpyLog) unFSpyLog(SPY_F_USER, _1, _2, _3, _4, _5, _6); else
#define SpyLog6(_1, _2, _3, _4, _5, _6, _7) if (unFSpyLog) unFSpyLog(SPY_F_USER, _1, _2, _3, _4, _5, _6, _7); else
#define Spy2Log(_1)  if (unFSpyLog) unFSpyLog(SPY_F_USER2, _1); else
#define Spy2Log1(_1, _2) if (unFSpyLog) unFSpyLog(SPY_F_USER2, _1, _2); else
#define Spy2Log2(_1, _2, _3) if (unFSpyLog) unFSpyLog(SPY_F_USER2, _1, _2, _3); else
#define Spy2Log3(_1, _2, _3, _4) if (unFSpyLog) unFSpyLog(SPY_F_USER2, _1, _2, _3, _4); else
#define Spy2Log4(_1, _2, _3, _4, _5) if (unFSpyLog) unFSpyLog(SPY_F_USER2, _1, _2, _3, _4, _5); else
#define Spy2Log5(_1, _2, _3, _4, _5, _6) if (unFSpyLog) unFSpyLog(SPY_F_USER2, _1, _2, _3, _4, _5, _6); else
#define Spy2Log6(_1, _2, _3, _4, _5, _6, _7) if (unFSpyLog) unFSpyLog(SPY_F_USER2, _1, _2, _3, _4, _5, _6, _7); else
#define Spy3Log(_1)  if (unFSpyLog) unFSpyLog(SPY_F_USER3, _1); else
#define Spy3Log1(_1, _2) if (unFSpyLog) unFSpyLog(SPY_F_USER3, _1, _2); else
#define Spy3Log2(_1, _2, _3) if (unFSpyLog) unFSpyLog(SPY_F_USER3, _1, _2, _3); else
#define Spy3Log3(_1, _2, _3, _4) if (unFSpyLog) unFSpyLog(SPY_F_USER3, _1, _2, _3, _4); else
#define Spy3Log4(_1, _2, _3, _4, _5) if (unFSpyLog) unFSpyLog(SPY_F_USER3, _1, _2, _3, _4, _5); else
#define Spy3Log5(_1, _2, _3, _4, _5, _6) if (unFSpyLog) unFSpyLog(SPY_F_USER3, _1, _2, _3, _4, _5, _6); else
#define Spy3Log6(_1, _2, _3, _4, _5, _6, _7) if (unFSpyLog) unFSpyLog(SPY_F_USER3, _1, _2, _3, _4, _5, _6, _7); else
#else
#define SpyLog(_1)  if (0) ; else
#define SpyLog1(_1, _2) if (0) ; else
#define SpyLog2(_1, _2, _3) if (0) ; else
#define SpyLog3(_1, _2, _3, _4) if (0) ; else
#define SpyLog4(_1, _2, _3, _4, _5) if (0) ; else
#define SpyLog5(_1, _2, _3, _4, _5, _6) if (0) ; else
#define SpyLog6(_1, _2, _3, _4, _5, _6, _7) if (0) ; else
#define Spy2Log(_1)  if (0) ; else
#define Spy2Log1(_1, _2) if (0) ; else
#define Spy2Log2(_1, _2, _3) if (0) ; else
#define Spy2Log3(_1, _2, _3, _4) if (0) ; else
#define Spy2Log4(_1, _2, _3, _4, _5) if (0) ; else
#define Spy2Log5(_1, _2, _3, _4, _5, _6) if (0) ; else
#define Spy2Log6(_1, _2, _3, _4, _5, _6, _7) if (0) ; else
#define Spy3Log(_1)  if (0) ; else
#define Spy3Log1(_1, _2) if (0) ; else
#define Spy3Log2(_1, _2, _3) if (0) ; else
#define Spy3Log3(_1, _2, _3, _4) if (0) ; else
#define Spy3Log4(_1, _2, _3, _4, _5) if (0) ; else
#define Spy3Log5(_1, _2, _3, _4, _5, _6) if (0) ; else
#define Spy3Log6(_1, _2, _3, _4, _5, _6, _7) if (0) ; else
#define unSpyReason(_1) if (0); else

#define ErrSpyLog(_1)
#define ErrSpyLog1(_1, _2)
#define ErrSpyLog2(_1, _2, _3)
#define ErrSpyLog3(_1, _2, _3, _4)
#define ErrSpyLog4(_1, _2, _3, _4, _5)

#endif	//USE_UNSPY

//Some Message based
#define errChkMB(vi, fCall) if (status = (fCall), status < 0) { \
		status = unmbase_statusUpdate(vi, status); goto Error; \
		} else

//----------------------------------------------------------------
//					ARM
static ViStatus LockARM(PUserData globals, ViInt32 armIdx);
static void UnlockARM(PUserData globals, ViInt32 armIdx);

#ifdef UNMBASE_DEBUG_CVI
static ViStatus ArmVxiReadRAM(ViSession vi, ViInt32 armidx, ViUInt32 addr, ViInt32 nwords, void *buf)
{
	ViStatus status;
	int prestate;

	if (nwords <= 4)
		prestate = SetBreakOnProtectionErrors(0);
	status = viMoveIn32(vi, VI_A32_SPACE,
					(armidx ? ARMVXI_ARM2_RAM : ARMVXI_ARM1_RAM) + addr,
					nwords, (ViUInt32*)buf);
	if (nwords <= 4)
		SetBreakOnProtectionErrors(prestate);
	return status;
}
#else
#define ArmVxiReadRAM(_vi_, _armidx_, _addr_, _nwords_, _buf_) viMoveIn32((_vi_), VI_A32_SPACE, \
					(_armidx_ ? ARMVXI_ARM2_RAM : ARMVXI_ARM1_RAM) + (_addr_), \
					(_nwords_), (ViUInt32*)(_buf_))
#endif

#define ArmVxiInRAM(_vi_, _armidx_, _addr_, _word_) viIn32((_vi_), VI_A32_SPACE, \
					(_armidx_ ? ARMVXI_ARM2_RAM : ARMVXI_ARM1_RAM) + (_addr_), \
					(_word_))

#ifdef UNMBASE_DEBUG_CVI
static ViStatus ArmVxiWriteRAM(ViSession vi, ViInt32 armidx, ViUInt32 addr, ViInt32 nwords, void *buf)
{
	ViStatus status;
	int prestate;

	if (nwords <= 4)
		prestate = SetBreakOnProtectionErrors(0);
	status = viMoveOut32(vi, VI_A32_SPACE,
					(armidx ? ARMVXI_ARM2_RAM : ARMVXI_ARM1_RAM) + addr,
					nwords, (ViUInt32*)buf);
	if (nwords <= 4)
		SetBreakOnProtectionErrors(prestate);
	return status;
}
#else
#define ArmVxiWriteRAM(_vi_, _armidx_, _addr_, _nwords_, _buf_) viMoveOut32((_vi_), VI_A32_SPACE, \
					(_armidx_ ? ARMVXI_ARM2_RAM : ARMVXI_ARM1_RAM) + (_addr_), \
					(_nwords_), (ViUInt32*)(_buf_))
#endif

#define ArmVxiOutRAM(_vi_, _armidx_, _addr_, _word_) viOut32((_vi_), VI_A32_SPACE, \
					(_armidx_ ? ARMVXI_ARM2_RAM : ARMVXI_ARM1_RAM) + (_addr_), \
					(_word_))


//---------------------------------------------------------------
static psARMVXI_CMD getArmCmdDef(ViUInt32 cmd)
{
	static sARMVXI_CMD fullcmd = {0, 3, 3};
	int i;

	//cmd &= (VXI_CMD_MASK_CMD | VXI_CMD_FLAG);
	cmd &= VXI_CMD_MASK_CMD;

	for (i=1; i<=ARMCMD_MAX; i++)
	{
		if (ArmVxiCmdDef[i].cmd == cmd)
			return &ArmVxiCmdDef[i];
	}
	return &fullcmd;
}

//---------------------------------------------------------------
static ViStatus armvxi_arm_readbuf(PUserData globals,
							ViInt32 armIdx,
							ViInt32 bufIdx,
							ViUInt32 *Buff,
							ViUInt32 nBytes)
{
	return ArmVxiReadRAM(globals->vi, armIdx,
					bufIdx ? ARMVXI_DATA2 : ARMVXI_DATA,
					(nBytes+(sizeof(ViUInt32)-1)) / sizeof(ViUInt32),	//чтобы дочитать, если там байты (клиент должен иметь место!!!)
					Buff);
}

//---------------------------------------------------------------
static ViStatus armvxi_arm_writebuf(PUserData globals,
							ViInt32 armIdx,
							ViInt32 bufIdx,
							ViUInt32 *Buff,
							ViUInt32 nBytes)
{
	return ArmVxiWriteRAM(globals->vi, armIdx,
					bufIdx ? ARMVXI_DATA2 : ARMVXI_DATA,
					(nBytes+(sizeof(ViUInt32)-1)) / sizeof(ViUInt32),	//чтобы дописать, если там байты (клиент должен иметь место!!!)
					Buff);
}

//---------------------------------------------------------------
static ViStatus armvxi_mez_readbuf(PM_SESSION mglobals,
							ViInt32 bufIdx,
							ViUInt32 *Buff,
							ViUInt32 nBytes)
{
	return ArmVxiReadRAM(mglobals->pbase_data->vi, (mglobals->midx > 1),
					bufIdx ? ARMVXI_DATA2 : ARMVXI_DATA,
					(nBytes+(sizeof(ViUInt32)-1)) / sizeof(ViUInt32),	//чтобы дочитать, если там байты (клиент должен иметь место!!!)
					Buff);
}

//---------------------------------------------------------------
static ViStatus armvxi_cmd_clear(PUserData globals,
							ViInt32 armIdx)
{
	if (ArmVxiOutRAM(globals->vi, armIdx,
				ARMVXI_CMD_WORD,
				0) >= 0)
	{
		ArmVxiOutRAM(globals->vi, armIdx,
					ARMVXI_CMD2_WORD,
					0);
	}
	return 0;
}

//---------------------------------------------------------------
//Передает команду, добиваясь того, чтобы она была получена.
//В переменной answ уже может быть ответ
static ViStatus armvxi_only_cmd(PUserData globals,
							psARMVXI_CMD cmdDef,
							ViInt32 armIdx,
							ViInt32 cmdIdx,
							pVXI_CMD vxiCmd,
							ViUInt32 *answ)
{
	ViUInt32 tmpansw;
	ViStatus status = 0;

	if (!answ)
		answ = &tmpansw;

	//следующий ID (не 0)
	do
	{
		globals->ArmVxiCmdId[armIdx] = VXI_CMD_ID_MASK & (globals->ArmVxiCmdId[armIdx] + (1<<VXI_CMD_ID_SHIFT));
	} while (!globals->ArmVxiCmdId[armIdx]);

	vxiCmd->cmd = (vxiCmd->cmd & ~VXI_CMD_ID_MASK) | globals->ArmVxiCmdId[armIdx];

#ifdef CHECK_ARMVXI_CMD
	{
		ViInt32 i;
		ViUInt32 badcmd;

		for (i=0; i<1000; i++)
		{
			/*
			errChk(ArmVxiWriteRAM(globals->vi, armIdx,
							cmdIdx ? ARMVXI_CMD2 : ARMVXI_CMD,
							sizeof(VXI_CMD) / sizeof(ViUInt32),
							vxiCmd));
			*/
			if (cmdDef->nout)
				errChk(ArmVxiWriteRAM(globals->vi, armIdx,
								(cmdIdx ? ARMVXI_CMD2 : ARMVXI_CMD) + offsetof(VXI_CMD,cmd) - 4*cmdDef->nout,
								1 + cmdDef->nout,
								(ViUInt8*)vxiCmd + offsetof(VXI_CMD,cmd) - 4*cmdDef->nout));
			else
				errChk(ArmVxiOutRAM(globals->vi, armIdx,
								cmdIdx ? ARMVXI_CMD2_WORD : ARMVXI_CMD_WORD,
								vxiCmd->cmd));

			errChk(ArmVxiInRAM(globals->vi, armIdx,
							cmdIdx ? ARMVXI_ANSW2_WORD : ARMVXI_ANSW_WORD,
							answ));
			if (((*answ) & VXI_CMD_ID_MASK) == globals->ArmVxiCmdId[armIdx])
				break;
			badcmd = (*answ) & VXI_CMD_ID_MASK;
		}
#ifdef CHECK_ARMVXI_CMD_PRINTF
if (i) printf("cmd%d %d times repeat (need %X was %X)\n", cmdIdx, i, globals->ArmVxiCmdId[armIdx], badcmd);
#endif
#ifdef CHECK_ARMVXI_CMD_SPY
if (i) Spy2Log4("cmd%d %d times repeat (need %X was %X)\n", cmdIdx, i, globals->ArmVxiCmdId[armIdx], badcmd);
#endif
		if (1000 == i)
		{
			errChk(VI_ERROR_IO);
		}
	}
#else
	/*
	errChk(ArmVxiWriteRAM(globals->vi, armIdx,
					cmdIdx ? ARMVXI_CMD2 : ARMVXI_CMD,
					sizeof(VXI_CMD) / sizeof(ViUInt32),
					vxiCmd));
	*/
	if (cmdDef->nout)
		errChk(ArmVxiWriteRAM(globals->vi, armIdx,
						(cmdIdx ? ARMVXI_CMD2 : ARMVXI_CMD) + offsetof(VXI_CMD,cmd) - 4*cmdDef->nout,
						1 + cmdDef->nout,
						(ViUInt8*)vxiCmd + offsetof(VXI_CMD,cmd) - 4*cmdDef->nout));
	else
		errChk(ArmVxiOutRAM(globals->vi, armIdx,
						cmdIdx ? ARMVXI_CMD2_WORD : ARMVXI_CMD_WORD,
						vxiCmd->cmd));

	errChk(ArmVxiInRAM(globals->vi, armIdx,
					cmdIdx ? ARMVXI_ANSW2_WORD : ARMVXI_ANSW_WORD,
					answ));
#endif
	//если сразу есть ответ - проверяем на ошибку
	if (armvxiAreAnsw(*answ))
	{
		armvxiSetStatus(*answ);
	}
Error:
	return status;
}

#ifdef CHECK_ARMVXI_CMD
//---------------------------------------------------------------
//Передает команду ARMCMD_NEXT, добиваясь того, чтобы она была получена.
//В переменной answ уже может быть ответ
static ViStatus armvxi_only_cmd_next(PUserData globals,
							ViInt32 armIdx,
							ViInt32 cmdIdx,
							ViUInt32 *answ)
{
	ViUInt32 cmd, tmpansw, i, badcmd;
	ViStatus status = 0;

	if (!answ)
		answ = &tmpansw;

	//следующий ID (не 0)
	do
	{
		globals->ArmVxiCmdId[armIdx] = VXI_CMD_ID_MASK & (globals->ArmVxiCmdId[armIdx] + (1<<VXI_CMD_ID_SHIFT));
	} while (!globals->ArmVxiCmdId[armIdx]);

	cmd = ARMCMD_NEXT | globals->ArmVxiCmdId[armIdx];

	for (i=0; i<1000; i++)
	{
		errChk(ArmVxiOutRAM(globals->vi, armIdx,
						cmdIdx ? ARMVXI_CMD2_WORD : ARMVXI_CMD_WORD,
						cmd));

		errChk(ArmVxiInRAM(globals->vi, armIdx,
						cmdIdx ? ARMVXI_ANSW2_WORD : ARMVXI_ANSW_WORD,
						answ));
		if (((*answ) & VXI_CMD_ID_MASK) == globals->ArmVxiCmdId[armIdx])
			break;
		badcmd = (*answ) & VXI_CMD_ID_MASK;
	}
#ifdef CHECK_ARMVXI_CMD_PRINTF
if (i) printf("next_cmd%d %d times repeat (need %X was %X)\n", cmdIdx, i, globals->ArmVxiCmdId[armIdx], badcmd);
#endif
#ifdef CHECK_ARMVXI_CMD_SPY
if (i) Spy2Log4("next_cmd%d %d times repeat (need %X was %X)\n", cmdIdx, i, globals->ArmVxiCmdId[armIdx], badcmd);
#endif
	if (1000 == i)
	{
		errChk(VI_ERROR_IO);
	}
	//если сразу есть ответ - проверяем на ошибку
	if (armvxiAreAnsw(*answ))
	{
		armvxiSetStatus(*answ);
	}
Error:
	return status;
}
#else
//---------------------------------------------------------------
//Передает команду ARMCMD_NEXT
static ViStatus armvxi_only_cmd_next(PUserData globals,
							ViInt32 armIdx,
							ViInt32 cmdIdx)
{
	//следующий ID (не 0)
	do
	{
		globals->ArmVxiCmdId[armIdx] = VXI_CMD_ID_MASK & (globals->ArmVxiCmdId[armIdx] + (1<<VXI_CMD_ID_SHIFT));
	} while (!globals->ArmVxiCmdId[armIdx]);

	return ArmVxiOutRAM(globals->vi, armIdx,
					cmdIdx ? ARMVXI_CMD2_WORD : ARMVXI_CMD_WORD,
					ARMCMD_NEXT | globals->ArmVxiCmdId[armIdx]);
}
#endif

//---------------------------------------------------------------
//Ждет ответа.
//Возвращает либо ошибку таймаута либо ошибку, которая передана в ответе
static ViStatus armvxi_wait_answ( PUserData globals,
								  ViReal64 tmo,
								  ViInt32 armIdx,
								  ViInt32 cmdIdx,
								  ViUInt32 *answ)
{
	ViInt32 i;
	ViStatus status = 0;
	//сначала пробуем читать несколько раз без таймера,
	//и если не получилось - то тогда по таймеру не более 2 секунд...
	for (i=0; i<100; i++)
	{
		errChk(ArmVxiInRAM(globals->vi, armIdx,
						cmdIdx ? ARMVXI_ANSW2_WORD : ARMVXI_ANSW_WORD,
						answ));
		if (armvxiAreAnsw(*answ))
			break;
	}
	if (i == 100)
	{
		double time0 = cross_timer() + tmo;
		do
		{
			errChk(ArmVxiInRAM(globals->vi, armIdx,
							cmdIdx ? ARMVXI_ANSW2_WORD : ARMVXI_ANSW_WORD,
							answ));
			if (armvxiAreAnsw(*answ))
				break;

		} while (cross_timer() < time0);
	}
	if (!armvxiAreAnsw(*answ))
		//errChk(VI_ERROR_TMO);
{
	//VAV DEBUG
	errChk(ArmVxiInRAM(globals->vi, armIdx,
					cmdIdx ? ARMVXI_ANSW2_WORD : ARMVXI_ANSW_WORD,
					answ));
	if (!armvxiAreAnsw(*answ))
	{
		errChk(VI_ERROR_TMO);
		}
}

	if (armvxiAreErr(*answ))
	{
		armvxiSetStatus(*answ);
	}
Error:
	if (VI_ERROR_TMO == status)
		armvxi_cmd_clear(globals, armIdx);
	return status;
}


//---------------------------------------------------------------
//Ждет ответа.
//Возвращает либо ошибку таймаута либо ошибку, которая передана в ответе
static ViStatus armvxi_wait_answ_d0( PUserData globals,
									ViReal64 tmo,
									ViInt32 armIdx,
									ViInt32 cmdIdx,
									pVXI_ANSW vxiAnsw)
{
	ViInt32 i;
	ViUInt32 answ;
	ViStatus status = 0;
	//сначала пробуем читать несколько раз без таймера,
	//и если не получилось - то тогда по таймеру не более 2 секунд...
	for (i=0; i<100; i++)
	{
		errChk(ArmVxiInRAM(globals->vi, armIdx,
						cmdIdx ? ARMVXI_ANSW2_WORD : ARMVXI_ANSW_WORD,
						&answ));
		if (armvxiAreAnsw(answ))
			break;
	}
	if (i == 100)
	{
		double time0 = cross_timer() + tmo;
		do
		{
			errChk(ArmVxiInRAM(globals->vi, armIdx,
							cmdIdx ? ARMVXI_ANSW2_WORD : ARMVXI_ANSW_WORD,
							&answ));
			if (armvxiAreAnsw(answ))
				break;

		} while (cross_timer() < time0);
	}
	if (!armvxiAreAnsw(answ))
//		errChk(VI_ERROR_TMO);
{
//VAV DEBUG
	errChk(ArmVxiInRAM(globals->vi, armIdx,
					cmdIdx ? ARMVXI_ANSW2_WORD : ARMVXI_ANSW_WORD,
					&answ));
	if (!armvxiAreAnsw(answ))
	{
		errChk(VI_ERROR_TMO);
	}
}

	//сразу проверяем на ошибку
	if (armvxiAreErr(answ))
	{
		armvxiSetStatus(answ);
	}
	else
	{
		errChk(ArmVxiReadRAM(globals->vi, armIdx,
						cmdIdx ? ARMVXI_ANSW2 : ARMVXI_ANSW,
						1 + 1,
						vxiAnsw));
	}
Error:
	if (VI_ERROR_TMO == status)
		armvxi_cmd_clear(globals, armIdx);
	return status;
}

/*
//---------------------------------------------------------------
//Просто читаем ответ (используется только тогда, когда ответ точно готов!)
//Возвращает либо ошибку таймаута либо ошибку, которая передана в ответе
static ViStatus armvxi_read_fullansw( PUserData globals,
								  ViInt32 armIdx,
								  ViInt32 cmdIdx,
								  pVXI_ANSW vxiAnsw)
{
	ViStatus status = 0;

	errChk(ArmVxiReadRAM(globals->vi, armIdx,
					cmdIdx ? ARMVXI_ANSW2 : ARMVXI_ANSW,
					sizeof(VXI_ANSW) / sizeof(ViUInt32),
					vxiAnsw));
	armvxiSetStatus(vxiAnsw->answ);
Error:
	return status;
}
*/

//---------------------------------------------------------------
static ViStatus armvxi_req( PUserData globals,
							ViInt32 lock,
							ViReal64 tmo,
							ViInt32 armIdx,
							pVXI_CMD vxiCmd,
							pVXI_ANSW vxiAnsw)
{
	ViStatus status = 0;
	ViInt32 i;
	ViUInt32 badcmd;
	psARMVXI_CMD cmdDef;
	cmdDef = getArmCmdDef(vxiCmd->cmd);

	if (ARMVXI_NOLOCK != lock)
		LockARM(globals, armIdx);

	//вместо armvxi_only_cmd используем копию его здесь, чтобы сразу читать весь ответ!
	//errChk(armvxi_only_cmd(globals, cmdDef,
	//				armIdx,
	//				0,	//cmdIdx,
	//				vxiCmd,
	//				VI_NULL));

	//следующий ID (не 0)
	do
	{
		globals->ArmVxiCmdId[armIdx] = VXI_CMD_ID_MASK & (globals->ArmVxiCmdId[armIdx] + (1<<VXI_CMD_ID_SHIFT));
	} while (!globals->ArmVxiCmdId[armIdx]);

	vxiCmd->cmd = (vxiCmd->cmd & ~VXI_CMD_ID_MASK) | globals->ArmVxiCmdId[armIdx];

	//поскольку всегда читаем ответ - не смотрим на CHECK_ARMVXI_CMD, а проверяем всегда
	for (i=0; i<1000; i++)
	{
		if (cmdDef->nout)
			errChk(ArmVxiWriteRAM(globals->vi, armIdx,
							ARMVXI_CMD + offsetof(VXI_CMD,cmd) - 4*cmdDef->nout,
							1 + cmdDef->nout,
							(ViUInt8*)vxiCmd + offsetof(VXI_CMD,cmd) - 4*cmdDef->nout));
		else
			errChk(ArmVxiOutRAM(globals->vi, armIdx,
							ARMVXI_CMD_WORD,
							vxiCmd->cmd));

		if (cmdDef->nin)
			errChk(ArmVxiReadRAM(globals->vi, armIdx,
						ARMVXI_ANSW,
						cmdDef->nin+1,
						vxiAnsw));
		else
			errChk(ArmVxiInRAM(globals->vi, armIdx,
						ARMVXI_ANSW_WORD,
						&vxiAnsw->answ));
		if ((vxiAnsw->answ & VXI_CMD_ID_MASK) == globals->ArmVxiCmdId[armIdx])
			break;
		badcmd = vxiAnsw->answ & VXI_CMD_ID_MASK;
	}
#ifdef CHECK_ARMVXI_CMD_PRINTF
if (i) printf("req0 %d times repeat (need %X was %X)\n", i, globals->ArmVxiCmdId[armIdx], badcmd);
#endif
#ifdef CHECK_ARMVXI_CMD_SPY
if (i) Spy2Log3("req0 %d times repeat (need %X was %X)\n", i, globals->ArmVxiCmdId[armIdx], badcmd);
#endif
	if (1000 == i)
	{
		errChk(VI_ERROR_IO);
	}
	if (!armvxiAreAnsw(vxiAnsw->answ))	//если ответ еще не готов - ждем его
	{
		//сначала пробуем читать несколько раз без таймера,
		//и если не получилось - то тогда по таймеру не более 2.0 секунд...
		for (i=0; i<100; i++)
		{
			if (cmdDef->nin)
				errChk(ArmVxiReadRAM(globals->vi, armIdx,
							ARMVXI_ANSW,
							cmdDef->nin+1,
							vxiAnsw));
			else
				errChk(ArmVxiInRAM(globals->vi, armIdx,
							ARMVXI_ANSW_WORD,
							&vxiAnsw->answ));
			if (armvxiAreAnsw(vxiAnsw->answ))
				break;
		}
		if (i == 100)
		{
			double time0 = cross_timer() + tmo;
			do
			{
				if (cmdDef->nin)
					errChk(ArmVxiReadRAM(globals->vi, armIdx,
								ARMVXI_ANSW,
								cmdDef->nin+1,
								vxiAnsw));
				else
					errChk(ArmVxiInRAM(globals->vi, armIdx,
								ARMVXI_ANSW_WORD,
								&vxiAnsw->answ));
				if (armvxiAreAnsw(vxiAnsw->answ))
					break;

			} while (cross_timer() < time0);
		}
		if (!armvxiAreAnsw(vxiAnsw->answ))
		{
			errChk(VI_ERROR_TMO);
			}
	}
	armvxiSetStatus(vxiAnsw->answ);

Error:
	if (VI_ERROR_TMO == status)
		armvxi_cmd_clear(globals, armIdx);
	if (ARMVXI_LOCKUNLOCK == lock)
		UnlockARM(globals, armIdx);
	return status;
}


//---------------------------------------------------------------
//передаем команду, ждем ответа - только статус
static ViStatus armvxi_cmd(PUserData globals,
							ViInt32 lock,
							ViReal64 tmo,
							ViInt32 armIdx,
							pVXI_CMD vxiCmd)
{
	ViStatus status = 0;
	ViInt32 i;
	ViUInt32 answ;
	psARMVXI_CMD cmdDef;
	cmdDef = getArmCmdDef(vxiCmd->cmd);

	if (ARMVXI_NOLOCK != lock)
		LockARM(globals, armIdx);

	errChk(armvxi_only_cmd(globals, cmdDef,
					armIdx,
					0,	//cmdIdx,
					vxiCmd,
					&answ));

	if (!armvxiAreAnsw(answ))
	{
		//сначала пробуем читать несколько раз без таймера,
		//и если не получилось - то тогда по таймеру не более 2.0 секунд...
		for (i=0; i<100; i++)
		{
			errChk(ArmVxiInRAM(globals->vi, armIdx,
							ARMVXI_ANSW_WORD,
							&answ));
			if (armvxiAreAnsw(answ))
				break;
		}
		if (i == 100)
		{
			double time0 = cross_timer() + tmo;
			do
			{
				errChk(ArmVxiInRAM(globals->vi, armIdx,
								ARMVXI_ANSW_WORD,
								&answ));
				if (armvxiAreAnsw(answ))
					break;

			} while (cross_timer() < time0);
		}
		if (!armvxiAreAnsw(answ))
//			errChk(VI_ERROR_TMO);
{
//VAV DEBUG
	errChk(ArmVxiInRAM(globals->vi, armIdx,
					ARMVXI_ANSW_WORD,
					&answ));
	if (!armvxiAreAnsw(answ))
	{
		errChk(VI_ERROR_TMO);
	}
}
	}

	armvxiSetStatus(answ);

Error:
	if (VI_ERROR_TMO == status)
		armvxi_cmd_clear(globals, armIdx);
	if (ARMVXI_LOCKUNLOCK == lock)
		UnlockARM(globals, armIdx);
	return status;
}

//---------------------------------------------------------------
//передаем команду обеим АРМ, ждем ответа от каждого
static ViStatus armvxi_2arms_req(PUserData globals,
								ViInt32 lock,
								ViReal64 tmo,
								pVXI_CMD vxiCmd,
								pVXI_ANSW vxiAnsw1,
								pVXI_ANSW vxiAnsw2)
{
	ViStatus status = 0;
	int i;
	ViInt32 ready1=0, ready2=0;
	VXI_CMD vxiCmd1;
	VXI_CMD vxiCmd2;
	VXI_ANSW tmpVxiAnsw1;
	VXI_ANSW tmpVxiAnsw2;
	psARMVXI_CMD cmdDef;

	//vxiCmd->cmd = cmd;

	cmdDef = getArmCmdDef(vxiCmd->cmd);

	if (!vxiAnsw1)
		vxiAnsw1 = &tmpVxiAnsw1;

	if (!vxiAnsw2)
		vxiAnsw2 = &tmpVxiAnsw2;

	memcpy(&vxiCmd1, vxiCmd, sizeof(VXI_CMD));
	memcpy(&vxiCmd2, vxiCmd, sizeof(VXI_CMD));

	if (ARMVXI_NOLOCK != lock)
		LockARM(globals, -1);

	//следующий ID (не 0)
	do
	{
		globals->ArmVxiCmdId[0] = VXI_CMD_ID_MASK & (globals->ArmVxiCmdId[0] + (1<<VXI_CMD_ID_SHIFT));
	} while (!globals->ArmVxiCmdId[0]);

	vxiCmd1.cmd = (vxiCmd1.cmd & ~VXI_CMD_ID_MASK) | globals->ArmVxiCmdId[0];

	//следующий ID (не 0)
	do
	{
		globals->ArmVxiCmdId[1] = VXI_CMD_ID_MASK & (globals->ArmVxiCmdId[1] + (1<<VXI_CMD_ID_SHIFT));
	} while (!globals->ArmVxiCmdId[1]);

	vxiCmd2.cmd = (vxiCmd2.cmd & ~VXI_CMD_ID_MASK) | globals->ArmVxiCmdId[1];

#ifdef CHECK_ARMVXI_CMD
	for (i=0; i<1000; i++)
	{
		if (!ready1)
		{
			/*
			errChk(ArmVxiWriteRAM(globals->vi, 0,
							ARMVXI_CMD,
							sizeof(VXI_CMD) / sizeof(ViUInt32),
							&vxiCmd1));
			*/
			if (cmdDef->nout)
				errChk(ArmVxiWriteRAM(globals->vi, 0,
								ARMVXI_CMD + offsetof(VXI_CMD,cmd) - 4*cmdDef->nout,
								1 + cmdDef->nout,
								(ViUInt8*)&vxiCmd1 + offsetof(VXI_CMD,cmd) - 4*cmdDef->nout));
			else
				errChk(ArmVxiOutRAM(globals->vi, 0,
								ARMVXI_CMD_WORD,
								vxiCmd1.cmd));


			errChk(ArmVxiInRAM(globals->vi, 0,
							ARMVXI_ANSW_WORD,
							&vxiAnsw1->answ));
			if ((vxiAnsw1->answ & VXI_CMD_ID_MASK) == globals->ArmVxiCmdId[0])
				ready1 = 1;
		}
		if (!ready2)
		{
			/*
			errChk(ArmVxiWriteRAM(globals->vi, 1,
							ARMVXI_CMD,
							sizeof(VXI_CMD) / sizeof(ViUInt32),
							&vxiCmd2));
			*/
			if (cmdDef->nout)
				errChk(ArmVxiWriteRAM(globals->vi, 1,
								ARMVXI_CMD + offsetof(VXI_CMD,cmd) - 4*cmdDef->nout,
								1 + cmdDef->nout,
								(ViUInt8*)&vxiCmd2 + offsetof(VXI_CMD,cmd) - 4*cmdDef->nout));
			else
				errChk(ArmVxiOutRAM(globals->vi, 1,
								ARMVXI_CMD_WORD,
								vxiCmd2.cmd));


			errChk(ArmVxiInRAM(globals->vi, 1,
							ARMVXI_ANSW_WORD,
							&vxiAnsw2->answ));
			if ((vxiAnsw2->answ & VXI_CMD_ID_MASK) == globals->ArmVxiCmdId[1])
				ready2 = 1;
		}
		if (ready1 && ready2)
			break;
	}
#ifdef CHECK_ARMVXI_CMD_PRINTF
if (i) printf("2arms_req %d times repeat\n", i);
#endif
#ifdef CHECK_ARMVXI_CMD_SPY
if (i) Spy2Log1("2arms_req %d times repeat\n", i);
#endif
	if (1000 == i)
	{
		errChk(VI_ERROR_IO);
	}
#else
		/*
		errChk(ArmVxiWriteRAM(globals->vi, 0,
						ARMVXI_CMD,
						sizeof(VXI_CMD) / sizeof(ViUInt32),
						&vxiCmd1));
		*/
		if (cmdDef->nout)
			errChk(ArmVxiWriteRAM(globals->vi, 0,
							ARMVXI_CMD + offsetof(VXI_CMD,cmd) - 4*cmdDef->nout,
							1 + cmdDef->nout,
							(ViUInt8*)vxiCmd1 + offsetof(VXI_CMD,cmd) - 4*cmdDef->nout)));
		else
			errChk(ArmVxiOutRAM(globals->vi, 0,
							ARMVXI_CMD_WORD,
							vxiCmd1->cmd));

		/*
		errChk(ArmVxiWriteRAM(globals->vi, 1,
						ARMVXI_CMD,
						sizeof(VXI_CMD) / sizeof(ViUInt32),
						&vxiCmd2));
		*/
		if (cmdDef->nout)
			errChk(ArmVxiWriteRAM(globals->vi, 1,
							ARMVXI_CMD + offsetof(VXI_CMD,cmd) - 4*cmdDef->nout,
							1 + cmdDef->nout,
							(ViUInt8*)vxiCmd2 + offsetof(VXI_CMD,cmd) - 4*cmdDef->nout)));
		else
			errChk(ArmVxiOutRAM(globals->vi, 1,
							ARMVXI_CMD_WORD,
							vxiCmd2->cmd));
#endif

	ready1 = 0;
	ready2 = 0;

	//сначала пробуем читать несколько раз без таймера,
	//и если не получилось - то тогда по таймеру не более 2.0 секунд...
	for (i=0; i<100; i++)
	{
		if (!ready1)
		{
			/*
			errChk(ArmVxiReadRAM(globals->vi, 0,
						ARMVXI_ANSW,
						sizeof(VXI_ANSW) / sizeof(ViUInt32),
						vxiAnsw1));
			*/
			if (cmdDef->nin)
				errChk(ArmVxiReadRAM(globals->vi, 0,
							ARMVXI_ANSW,
							cmdDef->nin+1,
							vxiAnsw1));
			else
				errChk(ArmVxiInRAM(globals->vi, 0,
							ARMVXI_ANSW_WORD,
							&vxiAnsw1->answ));

			ready1 = armvxiAreAnsw(vxiAnsw1->answ);
		}

		if (!ready2)
		{
			/*
			errChk(ArmVxiReadRAM(globals->vi, 1,
						ARMVXI_ANSW,
						sizeof(VXI_ANSW) / sizeof(ViUInt32),
						vxiAnsw2));
			*/
			if (cmdDef->nin)
				errChk(ArmVxiReadRAM(globals->vi, 1,
							ARMVXI_ANSW,
							cmdDef->nin+1,
							vxiAnsw2));
			else
				errChk(ArmVxiInRAM(globals->vi, 1,
							ARMVXI_ANSW_WORD,
							&vxiAnsw2->answ));

			ready2 = armvxiAreAnsw(vxiAnsw2->answ);
		}

		if (ready1 && ready2)
			break;
	}
	if (i == 100)
	{
		double time0 = cross_timer() + tmo;
		do
		{
			if (!ready1)
			{
				/*
				errChk(ArmVxiReadRAM(globals->vi, 0,
							ARMVXI_ANSW,
							sizeof(VXI_ANSW) / sizeof(ViUInt32),
							vxiAnsw1));
				*/
				if (cmdDef->nin)
					errChk(ArmVxiReadRAM(globals->vi, 0,
								ARMVXI_ANSW,
								cmdDef->nin+1,
								vxiAnsw1));
				else
					errChk(ArmVxiInRAM(globals->vi, 0,
								ARMVXI_ANSW_WORD,
								&vxiAnsw1->answ));

				ready1 = armvxiAreAnsw(vxiAnsw1->answ);
			}

			if (!ready2)
			{
				/*
				errChk(ArmVxiReadRAM(globals->vi, 1,
							ARMVXI_ANSW,
							sizeof(VXI_ANSW) / sizeof(ViUInt32),
							vxiAnsw2));
				*/
				if (cmdDef->nin)
					errChk(ArmVxiReadRAM(globals->vi, 1,
								ARMVXI_ANSW,
								cmdDef->nin+1,
								vxiAnsw2));
				else
					errChk(ArmVxiInRAM(globals->vi, 1,
								ARMVXI_ANSW_WORD,
								&vxiAnsw2->answ));

				ready2 = armvxiAreAnsw(vxiAnsw2->answ);
			}

			if (ready1 && ready2)
				break;

		} while (cross_timer() < time0);
	}
	if (ready1 == 0)
	{
		armvxi_cmd_clear(globals, 0);
		errChk(VI_ERROR_TMO);
	}
	if (ready2 == 0)
	{
		armvxi_cmd_clear(globals, 1);
		errChk(VI_ERROR_TMO);
	}

	armvxiSetStatus(vxiAnsw1->answ);
	if (status >= 0)
	{
		armvxiSetStatus(vxiAnsw2->answ);
	}
Error:
	if (ARMVXI_LOCKUNLOCK == lock)
		UnlockARM(globals, -1);
	return status;
}

//---------------------------------------------------------------
//передаем команду обеим АРМ, ждем получения команды от каждого
static ViStatus armvxi_2arms_cmd(PUserData globals,
								ViInt32 lock,
								ViReal64 tmo,
								pVXI_CMD vxiCmd)
{
	ViStatus status = 0;
	int i;
	ViInt32 ready1=0, ready2=0;
	VXI_CMD vxiCmd1;
	VXI_CMD vxiCmd2;
	ViUInt32 answ1;
	ViUInt32 answ2;
	psARMVXI_CMD cmdDef;

	//vxiCmd->cmd = cmd;

	cmdDef = getArmCmdDef(vxiCmd->cmd);

	memcpy(&vxiCmd1, vxiCmd, sizeof(VXI_CMD));
	memcpy(&vxiCmd2, vxiCmd, sizeof(VXI_CMD));

	if (ARMVXI_NOLOCK != lock)
		LockARM(globals, -1);

	//следующий ID (не 0)
	do
	{
		globals->ArmVxiCmdId[0] = VXI_CMD_ID_MASK & (globals->ArmVxiCmdId[0] + (1<<VXI_CMD_ID_SHIFT));
	} while (!globals->ArmVxiCmdId[0]);

	vxiCmd1.cmd = (vxiCmd1.cmd & ~VXI_CMD_ID_MASK) | globals->ArmVxiCmdId[0];

	//следующий ID (не 0)
	do
	{
		globals->ArmVxiCmdId[1] = VXI_CMD_ID_MASK & (globals->ArmVxiCmdId[1] + (1<<VXI_CMD_ID_SHIFT));
	} while (!globals->ArmVxiCmdId[1]);

	vxiCmd2.cmd = (vxiCmd2.cmd & ~VXI_CMD_ID_MASK) | globals->ArmVxiCmdId[1];

#ifdef CHECK_ARMVXI_CMD
	for (i=0; i<1000; i++)
	{
		if (!ready1)
		{
			/*
			errChk(ArmVxiWriteRAM(globals->vi, 0,
							ARMVXI_CMD,
							sizeof(VXI_CMD) / sizeof(ViUInt32),
							&vxiCmd1));
			*/
			if (cmdDef->nout)
				errChk(ArmVxiWriteRAM(globals->vi, 0,
								ARMVXI_CMD + offsetof(VXI_CMD,cmd) - 4*cmdDef->nout,
								1 + cmdDef->nout,
								(ViUInt8*)&vxiCmd1 + offsetof(VXI_CMD,cmd) - 4*cmdDef->nout));
			else
				errChk(ArmVxiOutRAM(globals->vi, 0,
								ARMVXI_CMD_WORD,
								vxiCmd1.cmd));


			errChk(ArmVxiInRAM(globals->vi, 0,
							ARMVXI_ANSW_WORD,
							&answ1));
			if ((answ1 & VXI_CMD_ID_MASK) == globals->ArmVxiCmdId[0])
				ready1 = 1;
		}
		if (!ready2)
		{
			/*
			errChk(ArmVxiWriteRAM(globals->vi, 1,
							ARMVXI_CMD,
							sizeof(VXI_CMD) / sizeof(ViUInt32),
							&vxiCmd2));
			*/
			if (cmdDef->nout)
				errChk(ArmVxiWriteRAM(globals->vi, 1,
								ARMVXI_CMD + offsetof(VXI_CMD,cmd) - 4*cmdDef->nout,
								1 + cmdDef->nout,
								(ViUInt8*)&vxiCmd2 + offsetof(VXI_CMD,cmd) - 4*cmdDef->nout));
			else
				errChk(ArmVxiOutRAM(globals->vi, 1,
								ARMVXI_CMD_WORD,
								vxiCmd2.cmd));



			errChk(ArmVxiInRAM(globals->vi, 1,
							ARMVXI_ANSW_WORD,
							&answ2));
			if ((answ2 & VXI_CMD_ID_MASK) == globals->ArmVxiCmdId[1])
				ready2 = 1;
		}
		if (ready1 && ready2)
			break;
	}
#ifdef CHECK_ARMVXI_CMD_PRINTF
if (i) printf("2arms_cmd %d times repeat\n", i);
#endif
#ifdef CHECK_ARMVXI_CMD_SPY
if (i) Spy2Log1("2arms_cmd %d times repeat\n", i);
#endif
	if (1000 == i)
	{
		errChk(VI_ERROR_IO);
	}
	ready1 = armvxiAreAnsw(answ1);
	ready2 = armvxiAreAnsw(answ2);

#else
	/*
	errChk(ArmVxiWriteRAM(globals->vi, 0,
					ARMVXI_CMD,
					sizeof(VXI_CMD) / sizeof(ViUInt32),
					&vxiCmd1));
	*/
	if (cmdDef->nout)
		errChk(ArmVxiWriteRAM(globals->vi, 0,
						ARMVXI_CMD + offsetof(VXI_CMD,cmd) - 4*cmdDef->nout,
						1 + cmdDef->nout,
						(ViUInt8*)vxiCmd1 + offsetof(VXI_CMD,cmd) - 4*cmdDef->nout)));
	else
		errChk(ArmVxiOutRAM(globals->vi, 0,
						ARMVXI_CMD_WORD,
						vxiCmd1->cmd));

	/*
	errChk(ArmVxiWriteRAM(globals->vi, 1,
					ARMVXI_CMD,
					sizeof(VXI_CMD) / sizeof(ViUInt32),
					&vxiCmd2));
	*/
	if (cmdDef->nout)
		errChk(ArmVxiWriteRAM(globals->vi, 1,
						ARMVXI_CMD + offsetof(VXI_CMD,cmd) - 4*cmdDef->nout,
						1 + cmdDef->nout,
						(ViUInt8*)vxiCmd2 + offsetof(VXI_CMD,cmd) - 4*cmdDef->nout)));
	else
		errChk(ArmVxiOutRAM(globals->vi, 1,
						ARMVXI_CMD_WORD,
						vxiCmd2->cmd));

	ready1 = 0;
	ready2 = 0;

#endif

	//сначала пробуем читать несколько раз без таймера,
	//и если не получилось - то тогда по таймеру не более 2.0 секунд...
	for (i=0; i<100; i++)
	{
		if (!ready1)
		{
			errChk(ArmVxiInRAM(globals->vi, 0,
							ARMVXI_ANSW_WORD,
							&answ1));
			ready1 = armvxiAreAnsw(answ1);
		}

		if (!ready2)
		{
			errChk(ArmVxiInRAM(globals->vi, 1,
							ARMVXI_ANSW_WORD,
							&answ2));
			ready2 = armvxiAreAnsw(answ2);
		}

		if (ready1 && ready2)
			break;
	}
	if (i == 100)
	{
		double time0 = cross_timer() + tmo;
		do
		{
			if (!ready1)
			{
				errChk(ArmVxiInRAM(globals->vi, 0,
								ARMVXI_ANSW_WORD,
								&answ1));
				ready1 = armvxiAreAnsw(answ1);
			}

			if (!ready2)
			{
				errChk(ArmVxiInRAM(globals->vi, 1,
								ARMVXI_ANSW_WORD,
								&answ2));
				ready2 = armvxiAreAnsw(answ2);
			}

			if (ready1 && ready2)
				break;

		} while (cross_timer() < time0);
	}
	if (ready1 == 0)
	{
		armvxi_cmd_clear(globals, 0);
		errChk(VI_ERROR_TMO);
	}
	if (ready2 == 0)
	{
		armvxi_cmd_clear(globals, 1);
		errChk(VI_ERROR_TMO);
	}

	armvxiSetStatus(answ1);
	if (status >= 0)
	{
		armvxiSetStatus(answ2);
	}
Error:
	if (ARMVXI_LOCKUNLOCK == lock)
		UnlockARM(globals, -1);
	return status;
}

static ViStatus armvxi_mez_cmd( PM_SESSION mglobals,
								ViInt32 lock,
								ViReal64 tmo,
								ViUInt32 io,
								pVXI_CMD vxiCmd,
								pVXI_ANSW vxiAnsw)
{
	//vxiCmd->cmd = cmd | armvxiMidxIoMask(mglobals->midx, io);
	vxiCmd->cmd |= armvxiMidxIoMask(mglobals->midx, io);

	if (vxiAnsw)	//если нет vxiAnsw - только статус!
	{
		return armvxi_req(mglobals->pbase_data, lock, tmo, (mglobals->midx > 1), vxiCmd, vxiAnsw);
	}
	else
	{
		return armvxi_cmd(mglobals->pbase_data, lock, tmo, (mglobals->midx > 1), vxiCmd);
	}
}

static ViStatus armvxi_arm_cmd(PUserData globals,
								ViInt32 lock,
								ViReal64 tmo,
								ViUInt32 armIdx,
								pVXI_CMD vxiCmd,
								pVXI_ANSW vxiAnsw)
{
	//vxiCmd->cmd = cmd;

	if (vxiAnsw)	//если нет vxiAnsw - только статус!
	{
		return armvxi_req(globals, lock, tmo, armIdx, vxiCmd, vxiAnsw);
	}
	else
	{
		return armvxi_cmd(globals, lock, tmo, armIdx, vxiCmd);
	}
}

//-------------------------------------------------------
//выдаем команду и вместе с ней данные с двойной буфферизацией
//ответ - только статус !
//VAV TODO: надо подумать над двойной буферизацией меньшего размера чем ARMVXI_DATA_MAX_LEN
//например, если N больше 4096 но меньше или равно ARMVXI_DATA_MAX_LEN*1.5, то локальный ARMVXI_DATA_MAX_LEN
//будет N/2
static ViStatus armvxi_bwrite_cmd(PUserData globals,
								  ViInt32 lock,
								  ViInt32 armIdx,
								  pVXI_CMD vxiCmd,
								  ViUInt32 N, //number of bytes
								  ViUInt8 *Buff)
{
	ViStatus status = VI_SUCCESS;
	ViUInt32 n, cmdIdx = 0, answ[2] = {0,0};
	psARMVXI_CMD cmdDef;
	double lastTmo;

	if (ARMCMD_FLASH_REWRITE == vxiCmd->cmd)
		lastTmo = ARMVXI_TMO1 + 1.5 + (ViReal64)N / 10000.0;	//пусть 10К в секунду;
	else
		lastTmo = ARMVXI_TMO1 + 1.0;

	cmdDef = getArmCmdDef(vxiCmd->cmd);

	if (!N)
		return 0;

//SpyLog1("======Пишем %p байт", N);

	if (ARMVXI_NOLOCK != lock)
		LockARM(globals, armIdx);

	//первый блок вместе с полной командой
	if (N > ARMVXI_DATA_MAX_LEN)
	{
		n = ARMVXI_DATA_MAX_LEN;
		//вторую команду делаем без команды, но НЕ НОЛЬ (см. алгоритм ARMVXI FW)
		//Примечание: 	именно поле ID делаем "не ноль", т.к. чтение D16 ARM
		//				именно его читает последним (поле данных может оказаться нулем!)
		ArmVxiOutRAM(globals->vi, armIdx,
					ARMVXI_CMD2_WORD,
					0xFC000000);
	}
	else
	{
		n = N;
	}

//SpyLog3("Пишем %p байт из %p, idx=%d", n, Buff, cmdIdx);

	errChk(armvxi_arm_writebuf( globals,
								armIdx,
								cmdIdx,
								(ViUInt32*)Buff,
								n));

	errChk(armvxi_only_cmd( globals, cmdDef,
							armIdx,
							cmdIdx,
							vxiCmd,
							&answ[cmdIdx]));
	N -= n;
	Buff += n;

	while (N)
	{
		int prevIdx;

		prevIdx = cmdIdx;
		cmdIdx = cmdIdx ? 0 : 1;

		//сначала пишем в противоположный буфер
		if (N > ARMVXI_DATA_MAX_LEN)
			n = ARMVXI_DATA_MAX_LEN;
		else
			n = N;
//SpyLog3("Пишем %p байт из %p, idx=%d", n, Buff, cmdIdx);
		errChk(armvxi_arm_writebuf( globals,
									armIdx,
									cmdIdx,
									(ViUInt32*)Buff,
									n));

#ifdef CHECK_ARMVXI_CMD
		errChk(armvxi_only_cmd_next( globals,
								armIdx,
								cmdIdx,
								&answ[cmdIdx]));
#else
		errChk(armvxi_only_cmd_next( globals,
								armIdx,
								cmdIdx));
		answ[cmdIdx] = 0;
#endif
		N -= n;
		Buff += n;

//SpyLog1("Ждем ответ на idx=%d", prevIdx);
		//теперь ждем ответа на предыдущий буфер
		if (!armvxiAreAnsw(answ[prevIdx]))
		{
			errChk(armvxi_wait_answ(globals,
									ARMVXI_TMO1 + 1.0,
									armIdx,
									prevIdx,
									&answ[prevIdx]));
		}
	}
//SpyLog1("Ждем ответ на idx=%d", cmdIdx);
	//и теперь ждем последнего ответа
	if (!armvxiAreAnsw(answ[cmdIdx]))
	{
		errChk(armvxi_wait_answ(globals,
								lastTmo,
								armIdx,
								cmdIdx,
								&answ[cmdIdx]));
	}
Error:
	if (ARMVXI_LOCKUNLOCK == lock)
		UnlockARM(globals, armIdx);
	return status;
}

//-------------------------------------------------------
//выдаем команду и читаем ответ и данные с двойной буфферизацией
//ответ - на первую команду, причем в нем data[0] - реальное число байт, которые нам пришлют!
//VAV TODO: надо подумать над двойной буферизацией меньшего размера чем ARMVXI_DATA_MAX_LEN
//например, если N больше 4096 но меньше или равно ARMVXI_DATA_MAX_LEN*1.5, то локальный ARMVXI_DATA_MAX_LEN
//будет N/2
static ViStatus armvxi_bread_cmd( PUserData globals,
								  ViInt32 lock,
								  ViInt32 armIdx,
								  pVXI_CMD vxiCmd,
								  pVXI_ANSW vxiAnsw,
								  ViUInt32 N,		//max number of bytes
								  ViUInt8 *Buff,
								  ViUInt32 *Nread	//количество реально прочитанных байт
								  )
{
	ViStatus status = VI_SUCCESS;
	ViUInt32 n, cmdIdx = 0;
	VXI_ANSW tmpvxiAnsw;
	ViUInt32 answ[2] = {0,0};
	psARMVXI_CMD cmdDef;
	cmdDef = getArmCmdDef(vxiCmd->cmd);

	if (!N)
		return 0;

	if (!vxiAnsw)
		vxiAnsw = &tmpvxiAnsw;

//SpyLog1("======Читаем %p байт", N);

	if (ARMVXI_NOLOCK != lock)
		LockARM(globals, armIdx);

	//в зависимости от запрашиваемых данных даем запрос на один или сразу два буфера
	errChk(armvxi_only_cmd( globals, cmdDef,
							armIdx,
							0,	//cmdIdx,
							vxiCmd,
							&answ[cmdIdx]));
	if (N > ARMVXI_DATA_MAX_LEN)
	{
#ifdef CHECK_ARMVXI_CMD
		errChk(armvxi_only_cmd_next( globals,
								armIdx,
								1,	//cmdIdx,
								&answ[cmdIdx]));
#else
		errChk(armvxi_only_cmd_next( globals,
								armIdx,
								1));	//cmdIdx
		answ[1] = 0;
#endif
	}
	//теперь ждем ответа на первую команду
	errChk(armvxi_wait_answ_d0(globals,
								1.0+1.0,
								armIdx,
								0,	//cmdIdx,
								vxiAnsw));

	N = vxiAnsw->data0;

	if (Nread)
		*Nread = N;

	//сейчас первый буфер готов
	//
	while (N)
	{
		if (N > ARMVXI_DATA_MAX_LEN)
			n = ARMVXI_DATA_MAX_LEN;
		else
			n = N;

//SpyLog3("Читаем %p байт в %p, idx=%d", n, Buff, cmdIdx);

		//читаем этот буфер
		errChk(armvxi_arm_readbuf(globals,
								armIdx,
								cmdIdx,
								(ViUInt32*)Buff,
								n));
		N -= n;
		Buff += n;

		if (!N)
			break;

		if (N > ARMVXI_DATA_MAX_LEN)
		{
			//сразу же даем на него команду на чтение
#ifdef CHECK_ARMVXI_CMD
			errChk(armvxi_only_cmd_next(globals,
									armIdx,
									cmdIdx,
									&answ[cmdIdx]));
#else
			errChk(armvxi_only_cmd_next(globals,
									armIdx,
									cmdIdx));
			answ[cmdIdx] = 0;
#endif
		}

		cmdIdx = cmdIdx ? 0 : 1;

//SpyLog1("Ждем ответ на idx=%d", cmdIdx);
		//ждем ответа на предыдущий буфер
		if (!armvxiAreAnsw(answ[cmdIdx]))
		{
			errChk(armvxi_wait_answ( globals,
									1.0+1.0,
									armIdx,
									cmdIdx,
									&answ[cmdIdx]));
		}
	}
Error:
	if (ARMVXI_LOCKUNLOCK == lock)
		UnlockARM(globals, armIdx);
	return status;
}

static ViStatus armvxi_mez_cmd_readbuf(PM_SESSION mglobals,
								ViInt32 lock,
								ViUInt32 io,
								pVXI_CMD vxiCmd,
								pVXI_ANSW vxiAnsw,
								ViAddr	buf,
								ViUInt32 count)	//BYTE Syze !!!
{
	int armIdx = (mglobals->midx > 1);

	//vxiCmd->cmd = cmd | armvxiMidxIoMask(mglobals->midx, io);
	vxiCmd->cmd |= armvxiMidxIoMask(mglobals->midx, io);

	return armvxi_bread_cmd(mglobals->pbase_data,
							lock,
							armIdx,
							vxiCmd,
							vxiAnsw,
							count,		//max number of bytes
							buf,
							VI_NULL);	//количество реально прочитанных байт
}

static ViStatus armvxi_mez_cmd_writebuf(PM_SESSION mglobals,
								ViInt32 lock,
								ViUInt32 io,
								pVXI_CMD vxiCmd,
								ViAddr	buf,
								ViUInt32 count)	//BYTE Syze !!!
{
	int armIdx = (mglobals->midx > 1);

	//vxiCmd->cmd = cmd | armvxiMidxIoMask(mglobals->midx, io);
	vxiCmd->cmd |= armvxiMidxIoMask(mglobals->midx, io);

	return armvxi_bwrite_cmd(mglobals->pbase_data,
							lock,
							armIdx,
							vxiCmd,
							count,		//number of bytes
							buf);
}

static ViStatus unmbase_statusUpdate( ViSession vi, ViStatus s)
{
	ViStatus errStatus;
	ViInt32 eventQ;

	if (s != VI_ERROR_CONN_LOST)
	{
		if (s != VI_ERROR_TMO)	// don't access if already timed out!
		{
			errStatus = viPrintf(vi,"*ESR?\n");
			if ( errStatus < VI_SUCCESS)
			{
				viClear(vi);
				return VI_ERROR_SYSTEM_ERROR;
			}

			errStatus = viScanf(vi,"%d", &eventQ);
			if ( errStatus < VI_SUCCESS)
			{
				viClear(vi);
				return VI_ERROR_SYSTEM_ERROR;
			}

			if ( (  0x04 // Query Error
					| 0x08 // Device Dependent Error
					| 0x10 // Execution Error
					| 0x20 // Command Error
				 ) & eventQ )
			{

				viClear(vi);
				return UNMBASE_ERROR_INSTR;	//UNMBASE_INSTR_ERROR_DETECTED;
			}
		}
		viClear(vi);
	}
	return s;
}

static ViStatus LockARM(PUserData globals, ViInt32 armIdx)
{
	ViStatus status = 0;
	if (armIdx < 0)
	{
		if (globals->ARM_busy_mutex[0] &&
			globals->ARM_busy_mutex[1])
		{
			status = unmbase_util_mutexes_lock(2, globals->ARM_busy_mutex, 10);
		}
	}
	else
	if (globals->ARM_busy_mutex[armIdx])
	{
		status = unmbase_util_mutex_lock(globals->ARM_busy_mutex[armIdx], 10);
	}
	if (status < 0)
	{
		ErrSpyLog1("    ERROR: Timeout when try to LockARM(%d)", armIdx);
	}
	return status;
}

static void UnlockARM(PUserData globals, ViInt32 armIdx)
{
	if (armIdx < 0)
	{
		if (globals->ARM_busy_mutex[0])
			unmbase_util_mutex_unlock(globals->ARM_busy_mutex[0]);
		if (globals->ARM_busy_mutex[1])
			unmbase_util_mutex_unlock(globals->ARM_busy_mutex[1]);
	}
	else
	if (globals->ARM_busy_mutex[armIdx])
	{
		unmbase_util_mutex_unlock(globals->ARM_busy_mutex[armIdx]);
	}
}

static ViStatus LockMB(PUserData globals)
{
	ViStatus status = 0;
	if (globals && (UNMBASE_FLAG_MB & globals->basetype) && globals->MB_busy_mutex)
	{
		status = unmbase_util_mutex_lock(globals->MB_busy_mutex, 10);
		if (status < 0)
		{
			ErrSpyLog("ERROR: Timeout when try to LockMB");
		}
	}
	return status;
}

static void UnlockMB(PUserData globals)
{
	if (globals)
		unmbase_util_mutex_unlock(globals->MB_busy_mutex);
}

static ViStatus LockMem(PUserData globals, ViInt32 midx)
{
	ViStatus status = 0;
	if (globals && globals->Mem_busy_mutex)
	{
		status = unmbase_util_mutex_lock(globals->Mem_busy_mutex, 10);
		if (status < 0)
		{
			ErrSpyLog("ERROR: Timeout when try to LockMem");
		}
	}
	return status;
}

static void UnlockMem(PUserData globals)
{
	unmbase_util_mutex_unlock(globals->Mem_busy_mutex);
}

static ViStatus LockStartStop(PUserData globals)
{
	ViStatus status = 0;
	if (globals && globals->StartStop_busy_mutex)
	{
		status = unmbase_util_mutex_lock(globals->StartStop_busy_mutex, 10);
		if (status < 0)
		{
			ErrSpyLog("ERROR: Timeout when try to LockStartStop");
		}
	}
	return status;
}

static void UnlockStartStop(PUserData globals)
{
	unmbase_util_mutex_unlock(globals->StartStop_busy_mutex);
}

static ViStatus LockLastData(PUserData globals)
{
	ViStatus status = 0;
	if (globals && globals->LastDta_busy_mutex)
	{
		status = unmbase_util_mutex_lock(globals->LastDta_busy_mutex, 10);
		if (status < 0)
		{
			ErrSpyLog("ERROR: Timeout when try to LockLastDta");
		}
	}
	return status;
}

static void UnlockLastData(PUserData globals)
{
	unmbase_util_mutex_unlock(globals->LastDta_busy_mutex);
}

static ViStatus LockRgComm1(PUserData globals)
{
	ViStatus status = 0;
	if (globals && globals->RgComm1_busy_mutex)
	{
		status = unmbase_util_mutex_lock(globals->RgComm1_busy_mutex, 10);
		if (status < 0)
		{
			ErrSpyLog("ERROR: Timeout when try to LockRgComm1");
		}
	}
	return status;
}

static void UnlockRgComm1(PUserData globals)
{
	unmbase_util_mutex_unlock(globals->RgComm1_busy_mutex);
}

static ViStatus LockRgComm2(PUserData globals)
{
	ViStatus status = 0;
	if (globals && globals->RgComm2_busy_mutex)
	{
		status = unmbase_util_mutex_lock(globals->RgComm2_busy_mutex, 10);
		if (status < 0)
		{
			ErrSpyLog("ERROR: Timeout when try to LockRgComm2");
		}
	}
	return status;
}

static void UnlockRgComm2(PUserData globals)
{
	unmbase_util_mutex_unlock(globals->RgComm2_busy_mutex);
}

//////////////////////////////////////////////////////
//      Правильный вывод в некоторые регистры       //
//////////////////////////////////////////////////////
static ViStatus Out32_COMM1(ViSession vi, ViUInt32 and_mask, ViUInt32 or_mask)
{
	ViStatus status = VI_SUCCESS;
	ViUInt32 word;
	PUserData globals = NULL;

	if ((status = viGetAttribute (vi, VI_ATTR_USER_DATA, &globals)) < 0)
		return status;

	if ((status = LockRgComm1(globals)) < 0)
		return status;

	errChk( viIn32(vi, VI_A24_SPACE,
				   rgSTAT1,
				   &word));
	word &= and_mask & (maskSTAT1_WR_VXI | maskSTAT1_RD_VXI | maskSTAT1_ALL_ON);
	word |= or_mask;

	errChk( viOut32(vi, VI_A24_SPACE,
					rgMASKCOMM1,
					~and_mask | or_mask));  //NEW FOR COMM1 WRITE MASK!!!

	errChk( viOut32(vi, VI_A24_SPACE,
					rgCOMM1,
					word));
#ifdef DBGPRINT
	printf("COMM1 = %08X\n", word);
#endif
Error:
	UnlockRgComm1(globals);
	return status;
}

static ViStatus Out32_COMM2(ViSession vi, ViUInt32 and_mask, ViUInt32 or_mask)
{
	ViStatus status = VI_SUCCESS;
	ViUInt32 word;
	PUserData globals = NULL;

	if ((status = viGetAttribute (vi, VI_ATTR_USER_DATA, &globals)) < 0)
		return status;

	if ((status = LockRgComm2(globals)) < 0)
		return status;

	errChk( viIn32(vi, VI_A24_SPACE,
				   rgSTAT2,
				   &word));
	word &= maskSTAT2_ALL_EN;
	word &= and_mask;
	word |= or_mask;

	errChk( viOut32(vi, VI_A24_SPACE,
					rgMASKCOMM2,
					~and_mask | or_mask));  //NEW FOR COMM2 WRITE MASK!!!

	errChk( viOut32(vi, VI_A24_SPACE,
					rgCOMM2,
					word));
#ifdef DBGPRINT
	printf("COMM2 = %08X\n", word);
#endif
Error:
	UnlockRgComm2(globals);
	return status;
}

static ViStatus Out32_COMM2A(ViSession vi, ViUInt32 and_mask, ViUInt32 or_mask)
{
	ViStatus status = VI_SUCCESS;
	ViUInt32 word;
	errChk( viIn32(vi, VI_A24_SPACE,
				   rgSTAT2A,
				   &word));
	word &= (maskSTAT2A_ALL_WAITSTOP | maskSTAT2A_ALL_STARTCFG);
	word &= and_mask;
	word |= or_mask;
	errChk( viOut32(vi, VI_A24_SPACE,
					rgCOMM2A,
					word));
#ifdef DBGPRINT
	printf("COMM2A = %08X\n", word);
#endif
Error:
	return status;
}

static ViStatus Out32_COMM11(ViSession vi, ViUInt32 and_mask, ViUInt32 or_mask)
{
	ViStatus status = VI_SUCCESS;
	ViUInt32 word;
	PUserData globals = NULL;

	if ((status = viGetAttribute (vi, VI_ATTR_USER_DATA, &globals)) < 0)
		return status;

	if ((status = LockRgComm1(globals)) < 0)
		return status;

	errChk( viIn32(vi, VI_A24_SPACE,
				   rgCOMM11,
				   &word));
	word &= and_mask;// & (maskSTAT1_WR_VXI | maskSTAT1_RD_VXI | maskSTAT1_ALL_ON);
	word |= or_mask;

	errChk( viOut32(vi, VI_A24_SPACE,
					rgMASKCOMM1,
					~and_mask | or_mask));  //NEW FOR COMM1 WRITE MASK!!!
	errChk( viOut32(vi, VI_A24_SPACE,
					rgCOMM11,
					word));
#ifdef DBGPRINT
	printf("COMM11 = %08X\n", word);
#endif
Error:
	UnlockRgComm1(globals);
	return status;
}

static ViStatus Out32_ENDIRQ(ViSession vi, ViUInt32 and_mask, ViUInt32 or_mask)
{
	ViStatus status = VI_SUCCESS;
	ViUInt32 word;
	errChk( viIn32(vi, VI_A24_SPACE,
				   rgENDIRQ,
				   &word));
	word &= (maskENDIRQ_IN_ALL_DIS | maskENDIRQ_OUT_ALL_DIS);
	word &= and_mask;
	word |= or_mask;
	errChk( viOut32(vi, VI_A24_SPACE,
					rgENDIRQ,
					word));
#ifdef DBGPRINT
	printf("ENDIRQ = %08X\n", word);
#endif
Error:
	return status;
}

static ViStatus Out16_CONF3(ViSession vi, ViUInt16 and_mask, ViUInt16 or_mask)
{
	ViStatus status = VI_SUCCESS;
	ViUInt16 word;
	errChk( viIn16(vi, VI_A16_SPACE,
				   rgCONF3,
				   &word));
	word &= and_mask;
	word |= or_mask;
	errChk( viOut16(vi, VI_A16_SPACE,
					rgCONF3,
					word));
#ifdef DBGPRINT
	printf("CONF3 = %04X\n", word);
#endif
Error:
	return status;
}

static ViStatus Out32_CONF1(ViSession vi, ViUInt32 and_mask, ViUInt32 or_mask)
{
	ViStatus status = VI_SUCCESS;
	ViUInt32 word;
	errChk( viIn32(vi, VI_A24_SPACE,
				   rgCONF1,
				   &word));
	word &= and_mask;
	word |= or_mask;
	errChk( viOut32(vi, VI_A24_SPACE,
					rgCONF1,
					word));
#ifdef DBGPRINT
	printf("CONF1 = %08X\n", word);
#endif
Error:
	return status;
}

static ViStatus Out32_CONF2(ViSession vi, ViUInt32 and_mask, ViUInt32 or_mask)
{
	ViStatus status = VI_SUCCESS;
	ViUInt32 word;
	errChk( viIn32(vi, VI_A24_SPACE,
				   rgCONF2,
				   &word));
	word &= and_mask;
	word |= or_mask;
	errChk( viOut32(vi, VI_A24_SPACE,
					rgCONF2,
					word));
#ifdef DBGPRINT
	printf("CONF2 = %08X\n", word);
#endif
Error:
	return status;
}


static ViStatus Out16_C(ViSession vi, ViUInt16 and_mask, ViUInt16 or_mask)
{
	PUserData globals = NULL;
	ViStatus status = VI_SUCCESS;
	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));
	and_mask = (and_mask & globals->saveC) | or_mask;
	errChk( viOut16(vi, VI_A16_SPACE,
					rgC,
					and_mask));
	globals->saveC = and_mask;
Error:
	return status;
}

static ViStatus STARTSTOP_Enable(ViSession vi, ViInt32 enable)
{
	ViStatus status = VI_SUCCESS;
	ViUInt32 word;
	errChk( viIn32(vi, VI_A24_SPACE,
				   rgCONF1,
				   &word));
	if (enable)
		word |= maskCONF1_EN_STARTSTOP;
	else
		word &= ~maskCONF1_EN_STARTSTOP;
	errChk( viOut32(vi, VI_A24_SPACE,
					rgCONF1,
					word));
#ifdef DBGPRINT
	printf("CONF1 = %08X\n", word);
#endif
Error:
	return status;
}

static ViStatus LockOutSTARTSTOP(PM_SESSION mglobals, const ViUInt32 *PRegs, ViUInt32 data)
{
	ViStatus status = VI_SUCCESS;
	ViUInt32 word;

	status = LockMem (mglobals->pbase_data, mglobals->midx);
	if (status < 0)
		return status;

	errChk( viIn32(mglobals->basevi, VI_A24_SPACE,
				   rgCONF1,
				   &word));
	errChk( viOut32(mglobals->basevi, VI_A24_SPACE,
					rgCONF1,
					word | maskCONF1_EN_STARTSTOP));

	errChk(viOut32 (mglobals->basevi, VI_A24_SPACE,
					PRegs[mglobals->midx],
					data));

	errChk( viOut32(mglobals->basevi, VI_A24_SPACE,
					rgCONF1,
					word & ~maskCONF1_EN_STARTSTOP));
	if (rgSTART_IN == PRegs)
		mglobals->saveRgSTART_IN = data;
	else
		if (rgSTOP_IN == PRegs)
			mglobals->saveRgSTOP_IN = data;
		else
			if (rgSTART_OUT == PRegs)
				mglobals->saveRgSTART_OUT = data;
			else
				if (rgSTOP_OUT == PRegs)
					mglobals->saveRgSTOP_OUT = data;

Error:
	UnlockMem (mglobals->pbase_data);
	return status;
}

static ViStatus LockOutVXISTARTSTOP(PUserData globals, ViUInt32 start, ViUInt32 stop)
{
	ViStatus status = VI_SUCCESS;
	ViUInt32 word;

	status = LockStartStop (globals);
	if (status < 0)
		return status;

	errChk( viIn32(globals->vi, VI_A24_SPACE,
				   rgCONF1,
				   &word));
	errChk( viOut32(globals->vi, VI_A24_SPACE,
					rgCONF1,
					word | maskCONF1_EN_STARTSTOP));

	errChk(viOut32 (globals->vi, VI_A24_SPACE,
					rgVXI_START,
					start));

	errChk(viOut32 (globals->vi, VI_A24_SPACE,
					rgVXI_STOP,
					stop));

	errChk( viOut32(globals->vi, VI_A24_SPACE,
					rgCONF1,
					word & ~maskCONF1_EN_STARTSTOP));

Error:
	UnlockStartStop (globals);
	return status;
}

//организация возможности запуска упрощенного мезонина от обычного носителя notNMU
static ViStatus PrepareSimpleMez(ViSession vi, ViInt32 midx)
{
	ViStatus status = VI_SUCCESS;
	errChk(Out32_CONF2(vi,
					   ~0,
					   maskCONF2_IN_SINGLE[midx]));   //setup SINGLE bit
	errChk( viOut32 (vi, VI_A24_SPACE,
					 rgZ_IN[midx],
					 3));
	errChk( viOut32 (vi, VI_A24_SPACE,
					 rgNWORDS_IN[midx],
					 1 + (1 << shiftNWORDS_B_LENGTH)));  //+1 Nsamples
	errChk( Out32_COMM2A(vi,
						 ~(maskCOMM2A_IN_STARTCFG[midx] | maskCOMM2A_IN_STARTCFG[midx]),
						 (maskCOMM2A_IN_STARTCFG[midx] | maskCOMM2A_IN_STARTCFG[midx])));
	errChk( Out32_COMM2(vi,
						~0,
						maskCOMM2_IN_EN[midx]));
	errChk( Out32_CONF2(vi,               //Disble
						~0,
						maskCONF2_M_ERR1_IRQ_DIS[midx]
						| maskCONF2_M_ERR2_IRQ_DIS[midx]));
Error:
	return status;
}

/*--------------------------------------------------------------------------*/
/* Set Mezzanine attributes                                                 */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_set_attribute (ViSession mvi,
		ViAttr Attribute_Name,
		ViAttrState Attribute_Value)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS;

	mviChk(mvi, mglobals);
	switch (Attribute_Name)
	{
	case UNMBASE_MATTR_USER_DATA:   //(R/W)
		mglobals->userdata = (ViAddr)Attribute_Value;
		return 0;	//для скорости
		//break;

	case UNMBASE_MATTR_MEZ_EXTVI:   //(R/W)
		mglobals->extvi = (ViSession)Attribute_Value;
		SpyLog2("unmbase_m_set_attribute(m%d, extvi=%08X)\n", mglobals->mnum, (ViSession)Attribute_Value);
		return 0;	//для скорости
		//break;

	case UNMBASE_MATTR_DEV_TYPE:   //(R/W)
		SpyLog2("unmbase_m_set_attribute(m%d, dev_type=%d)\n", mglobals->mnum, (ViUInt32)Attribute_Value);
		mglobals->dev_type = (ViUInt32)Attribute_Value;
		if (mglobals->basetype == UNMBASE_TYPE_ARM)
		{	//==> ARM
			VXI_CMD vxiCmd;

			vxiCmd.cmd = armvxiCmdD16(ARMCMD_MATTR,
									  Attribute_Name & 0xFF);
			vxiCmd.data0 = (ViUInt32)Attribute_Value;

			return armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
									0,
									&vxiCmd, VI_NULL);
		}
		else
		if (UNMBASE_FLAG_MB & mglobals->basetype)
		{	//==> MB
			LockMB(mglobals->pbase_data);
			errChkMB(mglobals->basevi, viPrintf(mglobals->basevi,
												"MATTR:DEVTYPE%d %d\n",
												mglobals->mnum, (ViUInt32)Attribute_Value));
		}
		else
		{
			if (((ViUInt32)Attribute_Value) && !mglobals->basesimple)
			{
				//организация возможности запуска упрощенного мезонина от обычного носителя notNMU
				errChk(PrepareSimpleMez(mglobals->basevi, mglobals->midx));
			}
		}
		break;

	case UNMBASE_MATTR_ASYNC:   //(R/W)
		SpyLog2("unmbase_m_set_attribute(m%d, async=%d)\n", mglobals->mnum, (ViUInt32)Attribute_Value);
		if (mglobals->basetype == UNMBASE_TYPE_ARM)
		{	//==> ARM
			VXI_CMD vxiCmd;

			vxiCmd.cmd = armvxiCmdD16(ARMCMD_MATTR,
									  Attribute_Name & 0xFF);
			vxiCmd.data0 = (ViUInt32)Attribute_Value;

			return armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
									0,
									&vxiCmd, VI_NULL);
		}
		else
		if (UNMBASE_FLAG_MB & mglobals->basetype)
		{	//==> MB
			errChkMB(mglobals->basevi, viPrintf(mglobals->basevi,
												"MATTR:ASYNC%d %d\n",
												mglobals->mnum, (ViUInt32)Attribute_Value));
		}
		else
		{
			mglobals->async_type = (ViBoolean)Attribute_Value;
		}
		break;

	case UNMBASE_MATTR_LOCK_LASTDATA:
		SpyLog2("unmbase_m_set_attribute(m%d, lockLastData=%d)\n", mglobals->mnum, (ViUInt32)Attribute_Value);
		if ((mglobals->basetype & UNMBASE_FLAG_MB) ||
			mglobals->basetype == UNMBASE_TYPE_ARM)
		{	//==> MB, ARM
			/*
			для MezaBOX неприменомо
			*/
		}
		else
		{
			mglobals->dontLockLastData = (Attribute_Value == 0);	//not
		}
		break;

	case UNMBASE_MATTR_CHECK_OUT_ERR:
		SpyLog2("unmbase_m_set_attribute(m%d, checkOutErr=%d)\n", mglobals->mnum, (ViUInt32)Attribute_Value);
		if (UNMBASE_FLAG_MB & mglobals->basetype)
		{	//==> MB только
			mglobals->dontCheckOutErr = (Attribute_Value == 0);	//not
		}
		break;

	default:
		errChk(VI_ERROR_NSUP_ATTR);
	}
Error:
	if (mglobals) UnlockMB (mglobals->pbase_data);
	return status;
}


static void unmbase_ErrLed(PUserData globals, ViBoolean On)
{
	ViUInt16 word;
	if (!globals)
		return;
	if ((UNMBASE_FLAG_MB & globals->basetype) && On)
	{	//==> MB - он сам зажигает и тушит, мы только при ошибке очистим свои буферы
		viFlush (globals->vi, VI_WRITE_BUF_DISCARD);
		viFlush (globals->vi, VI_READ_BUF);
		//viClear?????
		return;
	}
	if (globals->is_errled == On)
		return;
	globals->is_errled = On;

	if (viIn16(globals->vi, VI_A16_SPACE, rgCONF3, &word) < 0)
		return;
	if (On)
		word |= maskCONF3_ERRLED;
	else
		word &= ~maskCONF3_ERRLED;
	viOut16(globals->vi, VI_A16_SPACE, rgCONF3, word);
}

static ViStatus unmbase_check_err(ViSession mvi, ViInt16 io)
{
	PM_SESSION mglobals = NULL;
	PUserData globals = NULL;
	ViUInt32 stat2=0, i;
	ViStatus status = VI_SUCCESS;
	mviChk(mvi, mglobals);
	globals = (PUserData)mglobals->pbase_data;

	if (mglobals->dev_type)  	//simplifyed mezzanine
	{
		if (io)
		{
			if (mglobals->state_out)
				unmbase_m_stop_out(mglobals);
			mglobals->state_out = 0;
		}
		else
		{
			if (mglobals->state_in)
				unmbase_m_stop_in(mglobals);
			mglobals->state_in = 0;
		}
		goto Error;
	}

	if (io)     //OUT
	{
		errChk(mglobals->state_out);
		errChk( viIn32(mglobals->basevi, VI_A24_SPACE, rgSTAT2, &stat2));
		stat2 &= IGNORE_STAT2_ERRORS;

		if (globals->basetype == UNMBASE_TYPE_1)
		{
			if (stat2 & maskSTAT2_ERR3)     //Global Error
			{
				mglobals->state_out = -3;
				for (i=0; i<MAX_MEZ; i++)
				{
					if (globals->m_session[i].state_in > 0)
						globals->m_session[i].state_in = mglobals->state_out;
					if (globals->m_session[i].state_out > 0)
						globals->m_session[i].state_out = mglobals->state_out;
					globals->state = mglobals->state_out;
				}
				errChk( Out32_COMM2(mglobals->basevi,
									~0,
									maskCOMM2_ERR3_RST));
				errChk(mglobals->state_out);
			}
			if (stat2 & maskSTAT2_ERR4)     //Global Error
			{
				SpyLog1("ERROR-4 Stat2=%08X\n", stat2);
				mglobals->state_out = -4;
				for (i=0; i<MAX_MEZ; i++)
				{
					if (globals->m_session[i].state_in > 0)
						globals->m_session[i].state_in = mglobals->state_out;
					if (globals->m_session[i].state_out > 0)
						globals->m_session[i].state_out = mglobals->state_out;
					globals->state = mglobals->state_out;
				}
				errChk( Out32_COMM2(mglobals->basevi,
									~0,
									maskCOMM2_ERR4_RST));
				errChk(mglobals->state_out);
			}
		}

		if (globals->imm_on == 0) if (stat2 & maskSTAT2_ERR1_M[mglobals->midx])
			{
				mglobals->state_out = -1;
				errChk( Out32_COMM2(mglobals->basevi,
									~0,
									maskCOMM2_ERR1_M_RST[mglobals->midx]));
			}
		if (stat2 & maskSTAT2_ERR2_M[mglobals->midx])
		{
			SpyLog2("m%d ERROR Stat2=%08X\n", mglobals->mnum, stat2);
			if (mglobals->state_out == -1)
				mglobals->state_out = -12;
			else
				mglobals->state_out = -2;
			errChk( Out32_COMM2(mglobals->basevi,
								~0,
								maskCOMM2_ERR2_M_RST[mglobals->midx]));
		}
		if (mglobals->state_out < 0)
		{
			if (mglobals->state_in > 0)
				mglobals->state_in = mglobals->state_out;
			errChk(mglobals->state_out);
		}
	}
	else      //IN
	{
		errChk(mglobals->state_in);
		errChk( viIn32(mglobals->basevi, VI_A24_SPACE, rgSTAT2, &stat2));
		stat2 &= IGNORE_STAT2_ERRORS;

		if (globals->basetype == UNMBASE_TYPE_1)
		{
			if (stat2 & maskSTAT2_ERR3)     //Global Error
			{
				mglobals->state_in = -3;
				for (i=0; i<MAX_MEZ; i++)
				{
					if (globals->m_session[i].state_out > 0)
						globals->m_session[i].state_out = mglobals->state_in;
					if (globals->m_session[i].state_in > 0)
						globals->m_session[i].state_in = mglobals->state_in;
					globals->state = mglobals->state_in;
				}
				errChk( Out32_COMM2(mglobals->basevi,
									~0,
									maskCOMM2_ERR3_RST));
				errChk(mglobals->state_in);
			}
			if (stat2 & maskSTAT2_ERR4)     //Global Error
			{
				mglobals->state_in = -4;
				SpyLog2("m%d ERROR-4 Stat2=%08X\n", mglobals->mnum, stat2);
				for (i=0; i<MAX_MEZ; i++)
				{
					if (globals->m_session[i].state_out > 0)
						globals->m_session[i].state_out = mglobals->state_in;
					if (globals->m_session[i].state_in > 0)
						globals->m_session[i].state_in = mglobals->state_in;
					globals->state = mglobals->state_in;
				}
				errChk( Out32_COMM2(mglobals->basevi,
									~0,
									maskCOMM2_ERR4_RST));
				errChk(mglobals->state_in);
			}
		}
		if (globals->imm_on == 0) if (stat2 & maskSTAT2_ERR1_M[mglobals->midx])
			{
				mglobals->state_in = -1;
				errChk( Out32_COMM2(mglobals->basevi,
									~0,
									maskCOMM2_ERR1_M_RST[mglobals->midx]));
			}
		if (stat2 & maskSTAT2_ERR2_M[mglobals->midx])
		{

			SpyLog2("m%d ERROR Stat2=%08X\n", mglobals->mnum, stat2);

			if (mglobals->state_in == -1)
				mglobals->state_in = -12;
			else
				mglobals->state_in = -2;
			errChk( Out32_COMM2(mglobals->basevi,
								~0,
								maskCOMM2_ERR2_M_RST[mglobals->midx]));
		}
		if (mglobals->state_in < 0)
		{
			if (mglobals->state_out > 0)
				mglobals->state_out = mglobals->state_in;
			errChk(mglobals->state_in);
		}
	}
Error:
//#ifdef TECHNO
	if (status && stat2) {SpyLog1("Error STAT2=%08X\n", stat2);}	//VAV DBG
//#endif
	if ((status < 0) && mglobals)
		unmbase_ErrLed((PUserData)mglobals->pbase_data, 1);
	return status;
}

_UNMBASE_API ViStatus _VI_FUNC unmbase_io_loop (ViSession vi, ViUInt32 *buff_out, ViUInt32 *buff_in)
{
	ViStatus status = 0;
	ViUInt32 conf1;
	ViUInt16 conf3 = 0;
	errChk( viIn32(vi, VI_A24_SPACE,
				   rgCONF1,
				   &conf1));
	errChk( viOut32(vi, VI_A24_SPACE,
					rgCONF1,
					conf1 | maskCONF1_FIFO_VXI_B));

	errChk( viIn16(vi, VI_A16_SPACE,
				   rgCONF3,
				   &conf3));
	errChk( viOut16(vi, VI_A16_SPACE,
					rgCONF3,
					conf3 | maskCONF3_TESTLOOP));


	errChk( viMoveOut32 (vi, VI_A24_SPACE,
						 offsSHAREDRAM,
						 1024,
						 buff_out));

	errChk( viMoveIn32 (vi, VI_A24_SPACE,
						offsSHAREDRAM,
						1024,
						buff_in));

Error:

	viOut32(vi, VI_A24_SPACE,
			rgCONF1,
			conf1 & ~maskCONF1_FIFO_VXI_B);
	viOut16(vi, VI_A16_SPACE,
			rgCONF3,
			conf3 & ~maskCONF3_TESTLOOP);
	return status;
}

/*
static void spyStartStop(ViSession vi)
{
	ViUInt32 dword, dword1;
	viIn32 (vi, VI_A24_SPACE, rgVXI_START, &dword);
	viIn32 (vi, VI_A24_SPACE, rgVXI_STOP, &dword1);

//	SpyLog3("rgVXI_START = %08X, rgVXI_STOP = %08X (N=%08X)", dword, dword1, dword1-dword);

}
*/

static ViStatus CheckS(ViSession vi, ViUInt16 mask, ViUInt16 ok_mask)
{
	ViStatus status = VI_SUCCESS;
	ViUInt16 S;
	errChk( viIn16(vi, VI_A16_SPACE, rgS, &S));

	if ((S & mask) != ok_mask)
	{
		errChk(UNMBASE_ERROR_FLEX);
	}
	return status;  //Debug - for easy debug
Error:
	return status;
}

static ViStatus CheckA16D16(ViSession vi, ViUInt16 reg, ViUInt16 mask, ViUInt16 ok_mask)
{
	ViStatus status = VI_SUCCESS;
	ViUInt16 word;
	errChk( viIn16(vi, VI_A16_SPACE, reg, &word));

	if ((word & mask) != ok_mask)
	{
		SpyLog4("CheckA16D16(%02X & %04X = %04X) error, read %04X\n", reg, mask, ok_mask, word);
		errChk(UNMBASE_ERROR_INSTR);
	}
	return status;  //Debug - for easy debug
Error:
	return status;
}

static ViStatus CheckA24D32(ViSession vi, ViUInt32 reg, ViUInt32 mask, ViUInt32 ok_mask)
{
	ViStatus status = VI_SUCCESS;
	ViUInt32 word;
	errChk( viIn32(vi, VI_A24_SPACE, reg, &word));

	if ((word & mask) != ok_mask)
	{
		SpyLog4("CheckA24D32(%02X & %08X = %08X) error, read %04X\n", reg, mask, ok_mask, word);
		errChk(UNMBASE_ERROR_INSTR);
	}
	return status;  //Debug - for easy debug
Error:
	return status;
}

//пытаемся очистить FIFO при помощи одиночных чтений
static ViStatus ClearFIFO_VXI(ViSession vi)
{
	ViStatus status;
	ViInt32 i;
	//пока не будет пустое ФИФО - пословно читаем
	for (i=0; i<0x800; i++)
	{
		ViUInt32 dword;
		ViUInt16 word;

		errChk( viIn16 (vi, VI_A16_SPACE,
						rgS,
						&word));

		if (0 == (word & maskS_EFA_FVXI))
			break;		//дождались - опустело...

		viIn32 (vi, VI_A24_SPACE,
				offsSHAREDRAM,
				&dword);
	}
Error:
	return status;
}

static ViStatus ResetFIFO_VXI(	ViSession vi,
							   PUserData globals)
{
	ViStatus status = 0;
	static const ViUInt16 andmask_S  = (maskS_AEA_FVXI | maskS_AFA_FVXI | maskS_EFA_FVXI | maskS_FFA_FVXI | maskS_EFB_FVXI);

	//Reset ALL in rgCOMM3
	errChk( viOut16(vi, VI_A16_SPACE,
					rgCOMM3,
					maskCOMM3_IRQ_IC2_RESET |
					maskCOMM3_IRQ_IC3_RESET |
					maskCOMM3_IRQ_ALL_RESET |
					maskCOMM3_STOP));
	viOut16(vi, VI_A16_SPACE, rgCOMM3, 0);

	errChk( viOut16(vi, VI_A16_SPACE,
					rgCOMM3,
					maskCOMM3_resetFIFO_VXI));

	errChk(ClearFIFO_VXI(vi));

	errChk( CheckA16D16(vi,
						rgPR,
						maskPR_FFB_FVXI,
						0));

	errChk( CheckS(vi,
				   andmask_S,
				   maskS_AFA_FVXI));

	errChk( viOut16(vi, VI_A16_SPACE,
					rgCOMM3,
					0));    //clear reset bits

	errChk( CheckS(vi,
				   maskS_FFA_FVXI,
				   maskS_FFA_FVXI));

	//write Y1,X1,Y2,X2
	errChk( viOut32(vi, 2,
					offsSHAREDRAM,
					0xC0000000));
	errChk( viOut32(vi, 2,
					offsSHAREDRAM,
					0xC0000000));
	errChk( viOut32(vi, 2,
					offsSHAREDRAM,
					0xC0000000));
	errChk( viOut32(vi, 2,
					offsSHAREDRAM,
					0xC0000000));
	errChk( CheckA16D16(vi,
						rgPR,
						maskPR_FFB_FVXI,
						maskPR_FFB_FVXI));
	//Reset FIFO MEZ
	if (globals->basetype == UNMBASE_TYPE_1)
	{
		errChk( viOut16(vi, VI_A16_SPACE,
						rgCOMM3,
						maskCOMM3_resetFIFO_MEZ));
		errChk( CheckA24D32(vi,
							rgSTAT2,
							maskSTAT2_FFB_FMEM,
							0));
		errChk( viOut16(vi, VI_A16_SPACE,
						rgCOMM3,
						0));    //clear reset bits
		errChk( CheckA24D32(vi,
							rgSTAT2,
							maskSTAT2_FFB_FMEM,
							0));
		//write Y1,X1,Y2,X2
		errChk( viOut32(vi, 2,
						offsSHAREDRAM,
						0xC0000000));
		errChk( viOut32(vi, 2,
						offsSHAREDRAM,
						0xC0000000));
		errChk( viOut32(vi, 2,
						offsSHAREDRAM,
						0xC0000000));
		errChk( viOut32(vi, 2,
						offsSHAREDRAM,
						0xC0000000));
		errChk( Out32_CONF1(vi,
							~0,
							maskCONF1_FIFO_MEM_START));
		errChk( Out32_CONF1(vi,
							~maskCONF1_FIFO_MEM_START,
							0));
		errChk( CheckA24D32(vi,
							rgSTAT2,
							maskSTAT2_FFB_FMEM,
							maskSTAT2_FFB_FMEM));
	}
Error:
	return status;
}

//
//Note: if (N & 0xFF) != 0, then read (N+0x100)&0xFF !!!
ViStatus _VI_FUNCC unmbase_blk_read(
	ViSession vi,
	ViUInt32 A,   //global RAM address
	ViUInt32 N,   //number of bytes
	ViUInt8 *Buff,
	ViInt32 midx)	//для отладки - кто блокирует...
{
	ViStatus status = VI_SUCCESS;
	ViUInt32 dword, i, errN, errcount = 0;
	ViUInt8 *errBuff = Buff;
	ViUInt16 word;
	PUserData globals;

	SpyLog3("unmbase_blk_read: Try to read %08X bytes (%08X blocks*64w) from %08X", N, (N+0xFF)>>8, A);

	A = A>>8;   //A - block address
	if (N == 0)
		return 0;
	errN = N = (N+0xFF)>>8;    //number of blocks

	if ((status = viGetAttribute (vi, VI_ATTR_USER_DATA, &globals)) < 0)
		return status;

Next:
	N = errN;
	Buff = errBuff;

	if ((status = LockMem (globals, midx)) < 0)
		return status;

	errChk(LockOutVXISTARTSTOP(globals, A, A+N));

	errChk( Out32_COMM1(vi,
						~0,
						maskCOMM1_RD_VXI));
	while (1)
	{
		i = 0;

		if (N < 16)     //blocks width < 1024 words -> 64 words readings
		{
			while (N)
			{
//spyStartStop(vi);
				do
				{
					errChk( viIn16  (vi, VI_A16_SPACE,
									 rgS,
									 &word));
					if (globals->GlobalErrorIRQ)
					{
						globals->GlobalErrorIRQ = 0;
//printf("GlobalErrorIRQ\n");
						errChk(UNMBASE_ERROR_READ);
					}
					if ((++i) > 1000)
					{
						Out32_COMM1(vi,
									~maskCOMM1_RD_VXI,
									0);
						SpyLog1("  Error: have no 1 in maskS_AEA_FVXI (rgS=%04X)", word);
//printf("  Error: have no 1 in maskS_AEA_FVXI (rgS=%04X)\n", word);
						viIn16  (vi, VI_A16_SPACE, rgPR, &word);
						SpyLog1("                                    (rgPR=%04X)", word);
//printf("                                    (rgPR=%04X)\n", word);
						viIn32  (vi, VI_A24_SPACE, rgSTAT1, &dword);
						SpyLog1("                             (rgSTAT1=%04X)", dword);
//printf("                             (rgSTAT1=%04X)\n", dword);
						errChk(UNMBASE_ERROR_READ);
					}
				}
				while (!(word & maskS_AEA_FVXI)); //wait for 1

				status = viMoveIn32 (vi, 2, offsSHAREDRAM, 64, (ViUInt32*)Buff);
//spyStartStop(vi);
				if (globals->GlobalErrorIRQ)
				{
					globals->GlobalErrorIRQ = 0;
//printf("GlobalErrorIRQ\n");
					status = UNMBASE_ERROR_READ;
				}
				if (status)
				{
					Out32_COMM1(vi,
								~maskCOMM1_RD_VXI,
								0);
				}
				errChk(status);
				Buff += 64*sizeof(ViUInt32);
				N--;
			}
		}
		else      //blocks width >= 1024 words -> 1024 words readings
{
			//spyStartStop(vi);
			do
			{
				if (globals->GlobalErrorIRQ)
				{
					globals->GlobalErrorIRQ = 0;
//printf("GlobalErrorIRQ\n");
					errChk(UNMBASE_ERROR_READ);
				}
				errChk( viIn16  (vi, VI_A16_SPACE,
								 rgPR,
								 &word));
				if ((++i) > 1000)
				{
					Out32_COMM1(vi,
								~maskCOMM1_RD_VXI,
								0);
					SpyLog1("  Error: have no 0 in maskPR_FFB_FVXI (rgPR=%04X)", word);
//printf("  Error: have no 0 in maskPR_FFB_FVXI (rgPR=%04X)\n", word);
					viIn16  (vi, VI_A16_SPACE, rgS, &word);
					SpyLog1("                                       (rgS=%04X)", word);
//printf("                                       (rgS=%04X)\n", word);
					viIn32  (vi, VI_A24_SPACE, rgSTAT1, &dword);
					SpyLog1("                              (rgSTAT1=%04X)", dword);
//printf("                              (rgSTAT1=%04X)\n", dword);
					errChk(UNMBASE_ERROR_READ);
				}
			}
			while (word & maskPR_FFB_FVXI);   //wait for 0

			status = viMoveIn32 (vi, VI_A24_SPACE,
								 offsSHAREDRAM,
								 1024,
								 (ViUInt32*)Buff);
//spyStartStop(vi);
			if (globals->GlobalErrorIRQ)
			{
				globals->GlobalErrorIRQ = 0;
//printf("GlobalErrorIRQ\n");
				status = UNMBASE_ERROR_READ;
			}
			if (status)
			{
				Out32_COMM1(vi,
							~maskCOMM1_RD_VXI,
							0);
			}
			errChk(status);
			Buff += 1024*sizeof(ViUInt32);
			N -= 16;
		}
		if (N == 0)     //no more readings
{
			//spyStartStop(vi);
			i = 0;
			do
			{
				errChk( viIn32  (vi, VI_A24_SPACE,
								 rgSTAT1,
								 &dword));
				if ((++i) > 1000)
				{
					Out32_COMM1(vi,
								~maskCOMM1_RD_VXI,
								0);
					/*viOut32 (vi, VI_A24_SPACE, rgCOMM1, dword & 0x00003C & ~maskCOMM1_RD_VXI);*/
					SpyLog1("  Error: have no 0 in maskSTAT1_RD_VXI after reading (rgSTAT1=%08X)", dword);
//printf("  Error: have no 0 in maskSTAT1_RD_VXI after reading (rgSTAT1=%08X)\n", dword);
					viIn16  (vi, VI_A16_SPACE, rgPR, &word);
					SpyLog1("                                                            (rgPR=%04X)", word);
//printf("                                                            (rgPR=%04X)\n", word);
					viIn16  (vi, VI_A24_SPACE, rgS, &word);
					SpyLog1("                                                             (rgS=%04X)", word);
//printf("                                                             (rgS=%04X)\n", word);
					errChk(UNMBASE_ERROR_READ);
				}
			}
			while (dword & maskSTAT1_RD_VXI); //wait for 0

			errChk( viIn16 (vi, VI_A16_SPACE,
							rgS,
							&word));
			if (word & maskS_EFA_FVXI)
			{
				SpyLog2("  Error: have no 0 in maskS_EFA_FVXI after reading (rgSTAT1=%08X, rgS=%04X)", dword, word);
//printf("  Error: have no 0 in maskS_EFA_FVXI after reading (rgSTAT1=%08X, rgS=%04X)\n", dword, word);
				errChk(UNMBASE_ERROR_READ);
			}
			okChk(VI_SUCCESS);
		}
	}
Error:
	UnlockMem(globals);
	if (errcount < 3)
	{
		if (status < 0)
		{
			errcount++;
			/* БЫЛО:
			errChk( viOut16(vi, VI_A16_SPACE,
							rgCOMM3,
							maskCOMM3_resetFIFO_VXI));
			viOut16(vi, VI_A16_SPACE, rgCOMM3, 0);
			теперь :
			*/
			LockMem(globals, midx);

			errChk( Out32_COMM1(vi,
								~maskCOMM1_RD_VXI,
								0));
			//присваиваем стоп-адрес текущему
			errChk( viOut32 (vi, VI_A24_SPACE,
							 rgVXI_STOP,
							 A+errN-N+1));//dword));
			//пока не будет пустое ФИФО - пословно читаем
			errChk(ClearFIFO_VXI(vi));

			UnlockMem(globals);

			SpyLog2("Try to do NEXT unmbase_blk_read(%d), status=%08X", errcount, status);
//printf("Try to do NEXT unmbase_blk_read(%d), status=%08X\n", errcount, status);
//spyStartStop(vi);
			goto Next;
		}
	}
	else
		unSpyReason(0);	//stop spy
	SpyLog1("unmbase_blk_read return %08X", status);
	return status;
}

//Note: if (N & 0xFF) != 0, then read (N+0x100)&0xFF !!!
ViStatus _VI_FUNCC unmbase_blk_write(ViSession vi,
									 ViUInt32 A, //global RAM address
									 ViUInt32 N, //number of bytes
									 ViUInt8 *Buff,
									 ViInt32 midx)	//для отладки - кто блокирует...
{
	ViStatus status = VI_SUCCESS;
	ViUInt32 dword, i;
	ViUInt16 word;
	PUserData globals;

	SpyLog3("unmbase_blk_write: Try to write %08X bytes (%08X blocks*64w) to %08X", N, (N+0xFF)>>8, A);

	if ((status = viGetAttribute (vi, VI_ATTR_USER_DATA, &globals)) < 0)
		return status;

	A = A>>8;   //A - block address
	N = (N+0xFF)>>8;    //number of blocks

	if ((status = LockMem (globals, midx)) < 0)
		return status;

	errChk(LockOutVXISTARTSTOP(globals, A, A+N));
	errChk( Out32_COMM1(vi,
						~0,
						maskCOMM1_WR_VXI));
	i = 0;
	do
	{
		errChk( viIn32  (vi, VI_A24_SPACE,
						 rgSTAT1,
						 &dword));
		if ((++i) > 100)
		{
			SpyLog1("  Error: have no 1 in maskSTAT1_WR_VXI (rgSTAT1=%08X)", dword);
			errChk(UNMBASE_ERROR_WRITE);
		}
		if (!(dword & maskSTAT1_WR_VXI))
		{
			errChk( Out32_COMM1(vi,
								~0,
								maskCOMM1_WR_VXI));
		}
	}
	while (!(dword & maskSTAT1_WR_VXI)); //wait for 1

	while (1)
	{
		i = 0;

		if (N < 16)     //blocks width < 1024 words -> 64 words readings
		{
			while (N)
			{
				do
				{
					errChk( viIn16  (vi, VI_A16_SPACE,
									 rgS,
									 &word));
					if (globals->GlobalErrorIRQ)
					{
						globals->GlobalErrorIRQ = 0;
//printf("GlobalErrorIRQ\n");
						//errChk(UNMBASE_ERROR_WRITE);
					}
					if ((++i) > 400)
					{
						SpyLog1("  Error: have no 1 in maskS_AFA_FVXI (rgS=%04X)", word);
						viIn16  (vi, VI_A16_SPACE, rgPR, &word);
						SpyLog1("                                    (rgPR=%04X)", word);
						viIn32  (vi, VI_A24_SPACE, rgSTAT1, &dword);
						SpyLog1("                             (rgSTAT1=%04X)", dword);
						errChk(UNMBASE_ERROR_WRITE);
					}
				}
				while (!(word & maskS_AFA_FVXI)); //wait for 1

				status = viMoveOut32 (vi, VI_A24_SPACE,
									  offsSHAREDRAM,
									  64,
									  (ViUInt32*)Buff);
				if (globals->GlobalErrorIRQ)
				{
					globals->GlobalErrorIRQ = 0;
//printf("GlobalErrorIRQ\n");
					//errChk(UNMBASE_ERROR_WRITE);
				}
				errChk(status);
				Buff += 64*sizeof(ViUInt32);
				N--;
			}
		}
		else      //blocks width >= 1024 words -> 1024 words readings
		{
			do
			{
				errChk( viIn16  (vi, VI_A16_SPACE,
								 rgS,
								 &word));
				if (globals->GlobalErrorIRQ)
				{
					globals->GlobalErrorIRQ = 0;
//printf("GlobalErrorIRQ\n");
					errChk(UNMBASE_ERROR_READ);
				}
				if ((++i) > 1000)
				{
					SpyLog1("  Error: have no 0 in maskS_EFB_FVXI (rgS=%04X)", word);
					viIn16  (vi, VI_A16_SPACE, rgPR, &word);
					SpyLog1("                                    (rgPR=%04X)", word);
					viIn32  (vi, VI_A24_SPACE, rgSTAT1, &dword);
					SpyLog1("                             (rgSTAT1=%04X)", dword);
					errChk(UNMBASE_ERROR_WRITE);
				}
			}
			while (word & maskS_EFB_FVXI);    //wait for 0

			status = viMoveOut32 (vi, VI_A24_SPACE,
								  offsSHAREDRAM,
								  1024,
								  (ViUInt32*)Buff);
			if (globals->GlobalErrorIRQ)
			{
//printf("GlobalErrorIRQ\n");
				globals->GlobalErrorIRQ = 0;
				//errChk(UNMBASE_ERROR_WRITE);
			}
			errChk(status);
			Buff += 1024*sizeof(ViUInt32);
			N -= 16;
		}
		if (N == 0)     //no more readings
		{
			i = 0;
			do
			{
				errChk( viIn32  (vi, VI_A24_SPACE,
								 rgSTAT1,
								 &dword));
				if ((++i) > 1000)
				{
					Out32_COMM1(vi,
								~maskCOMM1_WR_VXI,
								0);
					/*viOut32 (vi, VI_A24_SPACE, rgCOMM1, dword & 0x00003C & ~maskCOMM1_WR_VXI);*/
					SpyLog1("  Error: have no 0 in maskSTAT1_WR_VXI after writing (rgSTAT1=%08X)", dword);
					viIn16  (vi, VI_A16_SPACE, rgPR, &word);
					SpyLog1("                                                            (rgPR=%04X)", word);
					viIn16  (vi, VI_A24_SPACE, rgS, &word);
					SpyLog1("                                                             (rgS=%04X)", word);
					errChk(UNMBASE_ERROR_WRITE);
				}
			}
			while (dword & maskSTAT1_WR_VXI); //wait for 0

			errChk( viIn16 (vi, VI_A16_SPACE,
							rgS,
							&word));
			if (word & maskS_EFB_FVXI)
			{
				SpyLog1("  Error: have no 0 in maskS_EFB_FVXI (rgS=%04X)", word);
				viIn16  (vi, VI_A16_SPACE, rgPR, &word);
				SpyLog1("                                    (rgPR=%04X)", word);
				viIn32  (vi, VI_A24_SPACE, rgSTAT1, &dword);
				SpyLog1("                             (rgSTAT1=%04X)", dword);
				errChk(UNMBASE_ERROR_WRITE);
			}

			okChk(VI_SUCCESS);
		}
	}

Error:
	UnlockMem(globals);
	return status;
}

ViStatus _VI_FUNCC unmbase_arm_data_read(ViSession vi,
									 ViUInt32 armIdx,
									 ViUInt32 A,   //global RAM address
									 ViUInt32 N,   //number of bytes
									 ViUInt8 *Buff)
{
	PUserData globals = NULL;
	ViStatus status = VI_SUCCESS;
	VXI_CMD vxiCmd;

SpyLog3("unmbase_arm_data_read(arm%d,%08X[%08X])\n", armIdx, A, N);
	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));

	if (globals->basetype == UNMBASE_TYPE_ARM)
	{
		vxiCmd.cmd = ARMCMD_MEMREADq;
		vxiCmd.data0 = A;
		vxiCmd.data1 = N;

		status = armvxi_bread_cmd(globals,
								ARMVXI_LOCKUNLOCK,
								armIdx,
								&vxiCmd,
								VI_NULL,
								N,		//max number of bytes
								Buff,
								VI_NULL);	//количество реально прочитанных байт
	}
	else
	if (UNMBASE_FLAG_MB & globals->basetype)
	{
		ViChar tmpbuff[32];
		ViUInt32 cnt;

		errChkMB(vi, viPrintf (vi,
						 "ARM:MEMREAD%d? 0x%08x,0x%08X\n",
						 armIdx+1, A, N));

		LockMB(globals);
		errChkMB(vi, viBufRead (vi, (ViPBuf)tmpbuff, 2, &cnt));
		if ((cnt != 2) || (*tmpbuff != '#'))
		{
			errChk(UNMBASE_ERROR_INSTR);
		}
		errChkMB(vi, viBufRead (vi, (ViPBuf)tmpbuff, tmpbuff[1] - '0', &cnt));
		tmpbuff[cnt] = 0;
		cnt = atoi(tmpbuff);
		errChkMB(vi, viBufRead (vi, (ViPBuf)Buff, cnt, &cnt));
		if (globals->baseBE)
		{
			mem_swap32(Buff, (cnt+3)&~3);
		}
		viFlush (vi, VI_READ_BUF_DISCARD);
		okChk(VI_SUCCESS);
	}
	else
		status = VI_ERROR_NSUP_OPER;
Error:
	UnlockMB(globals);
	return status;
}

ViStatus _VI_FUNCC unmbase_data_read(ViSession vi,
									 ViUInt32 A,   //global RAM address
									 ViUInt32 N,   //number of bytes
									 ViUInt8 *Buff)
{
	PUserData globals = NULL;
	ViStatus status = VI_SUCCESS;
	ViUInt32 i, n;
	ViUInt8 tmpblock[64*sizeof(ViUInt32)];
	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));

	if (globals->basetype == UNMBASE_TYPE_ARM)
	{
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;
		ViUInt32 armIdx;

		if (ARMVXI_ARM2_ADDR_FLAG & A)
		{
			A &= ~ARMVXI_ARM2_ADDR_FLAG;
			armIdx = 1;
		}
		else
		{
			armIdx = 0;
		}

		vxiCmd.cmd = ARMCMD_MEMREADq;
		vxiCmd.data0 = A;
		vxiCmd.data1 = N;

		return armvxi_bread_cmd(globals,
								ARMVXI_LOCKUNLOCK,
								armIdx,
								&vxiCmd,
								&vxiAnsw,
								N,		//max number of bytes
								Buff,
								VI_NULL);	//количество реально прочитанных байт
	}
	else
	if (UNMBASE_FLAG_MB & globals->basetype)
	{
		ViChar tmpbuff[32];
		ViUInt32 cnt;

		errChkMB(vi, viPrintf (vi,
						 "MEMREAD? 0x%08x,0x%08X\n",
						 A, N));

		LockMB(globals);
		errChkMB(vi, viBufRead (vi, (ViPBuf)tmpbuff, 2, &cnt));
		if ((cnt != 2) || (*tmpbuff != '#'))
		{
			errChk(UNMBASE_ERROR_INSTR);
		}
		errChkMB(vi, viBufRead (vi, (ViPBuf)tmpbuff, tmpbuff[1] - '0', &cnt));
		tmpbuff[cnt] = 0;
		cnt = atoi(tmpbuff);
		errChkMB(vi, viBufRead (vi, (ViPBuf)Buff, cnt, &cnt));
		if (globals->baseBE)
			mem_swap32(Buff, cnt);
		viFlush (vi, VI_READ_BUF_DISCARD);
		okChk(VI_SUCCESS);
	}

	i = A & 0xFF;   //internal block index
	if (i)      //we have first non-full block
	{
		//read first block from (A & ~0xFF) to tmpblock
		errChk( unmbase_blk_read(vi,
								 (A & ~0xFF),
								 64*sizeof(ViUInt32),
								 tmpblock, -1));
		n = 0x100 - (A & 0xFF);     //how real data we have in first block
		if (n > N)      //if we need bytes not to block end, correct n
			n = N;

		memcpy(Buff, &(tmpblock[i]), n);
		if (n == N)     //are all transfered?
		{
			okChk(VI_SUCCESS);
		}
		Buff += n;      //Buff point to next data
		N -= n;         //
		A += n;         //now (A & 0xFF) always zero
	}

	n = N & ~0xFF;      //byte syze of all full blocks
	if (n)      //we have some full blocks
	{

		//read not more 2 MBytes!!!
		while (n > (2*1024*1024))
		{
			//read full blocks to Buff
			errChk( unmbase_blk_read(vi,
									 A,
									 (2*1024*1024),
									 Buff, -1));
			n -= (2*1024*1024);
			Buff += (2*1024*1024);      //Buff point to next data
			N -= (2*1024*1024);         //
			A += (2*1024*1024);         //now A & 0xFF always zero
		}
		//read full blocks to Buff
		errChk( unmbase_blk_read(vi,
								 A,
								 n,
								 Buff, -1));
		if (n == N)     //are all transfered?
		{
			okChk(VI_SUCCESS);
		}
		Buff += n;      //Buff point to next data
		N -= n;         //
		A += n;         //now A & 0xFF always zero
	}

	//now we assume that we have last non-full block with N byte size
	//read first block from A to tmpblock
	errChk( unmbase_blk_read(vi,
							 A,
							 N,
							 tmpblock, -1));

	memcpy(Buff, tmpblock, N);
Error:
	UnlockMB(globals);
	return status;
}

ViStatus _VI_FUNCC unmbase_arm_cmd(ViSession vi,
									ViUInt32 armIdx,
									ViUInt32 *vxiCmd,
									ViUInt32 *vxiAnsw)
{
	PUserData globals = NULL;
	ViStatus status = VI_SUCCESS;

	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));

	if (globals->basetype == UNMBASE_TYPE_ARM)
	{
		status = armvxi_req(globals, ARMVXI_LOCKUNLOCK, 1.0, armIdx,
						(pVXI_CMD)vxiCmd,
						(pVXI_ANSW)vxiAnsw);
	}
	else
		status = VI_ERROR_NSUP_OPER;
Error:
	return status;
}

ViStatus _VI_FUNCC unmbase_arm_data_write(ViSession vi,
										ViUInt32 armIdx,
										ViUInt32 A, //global RAM address
										ViUInt32 N, //number of bytes
										ViUInt8 *Buff)
{
	PUserData globals = NULL;
	ViStatus status = VI_SUCCESS;
	VXI_CMD vxiCmd;

	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));

	if (globals->basetype == UNMBASE_TYPE_ARM)
	{
		vxiCmd.cmd = ARMCMD_MEMWRITE;
		vxiCmd.data0 = A;
		vxiCmd.data1 = N;

		status = armvxi_bwrite_cmd(globals,
									 ARMVXI_LOCKUNLOCK,
									 armIdx,
									 &vxiCmd,
									 N, //number of bytes
									 Buff);
	}
	else
	if (UNMBASE_FLAG_MB & globals->basetype)
	{
		ViChar tmpbuff[96], *tmpbuffptr;
		ViUInt32 cnt, digits;

		//готовим для передачи выровненныый блок данных 488.2 Arbitrary Length Binary Block
		sprintf(tmpbuff, "%u", N);
		digits = strlen(tmpbuff);
		sprintf(tmpbuff, "ARM:MEMWRITE%u %u,%u",
				armIdx+1, A, N);
		cnt = strlen(tmpbuff);
		tmpbuffptr = &tmpbuff[cnt];
		//общее количество передаваемых байт команды до начала данных = digits + cnt + 2 (это "#n")
		cnt += digits+2;
		while (cnt&3)
		{
			*tmpbuffptr++ = ' ';	//выравниваем при помощи пробелов
			cnt++;
		}
		sprintf(tmpbuffptr, "#%u%u",
				digits, N);

		LockMB(globals);

		errChkMB(vi, viBufWrite (vi, (ViPBuf)tmpbuff, cnt, VI_NULL));

		if (globals->baseBE)
		{
			void *tmpbuf = malloc(N);

			if (!tmpbuf)
			{
				errChk(VI_ERROR_ALLOC);
			}
			memcpy(tmpbuf, Buff, N);
			mem_swap32(Buff, (N+3)&~3);
			status = viBufWrite (vi, (ViPBuf)tmpbuf, N, &cnt);
			free(tmpbuf);
			errChkMB(vi, status);
		}
		else
		{
			errChkMB(vi, viBufWrite (vi, (ViPBuf)Buff, N, &cnt));
		}
		errChkMB(vi, viFlush (vi, VI_WRITE_BUF));
		okChk(VI_SUCCESS);
	}
	else
		status = VI_ERROR_NSUP_OPER;
Error:
	UnlockMB(globals);
	return status;
}

ViStatus _VI_FUNCC unmbase_data_write(ViSession vi,
									  ViUInt32 A, //global RAM address
									  ViUInt32 N, //number of bytes
									  ViUInt8 *Buff)
{
	PUserData globals = NULL;
	ViStatus status = VI_SUCCESS;
	ViUInt32 i, n;
	ViUInt8 tmpblock[64*sizeof(ViUInt32)];

	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));

	if (globals->basetype == UNMBASE_TYPE_ARM)
	{
		VXI_CMD vxiCmd;
		int armIdx;

		if (ARMVXI_ARM2_ADDR_FLAG & A)
		{
			A &= ~ARMVXI_ARM2_ADDR_FLAG;
			armIdx = 1;
		}
		else
		{
			armIdx = 0;
		}

		vxiCmd.cmd = ARMCMD_MEMWRITE;
		vxiCmd.data0 = A;
		vxiCmd.data1 = N;

		return armvxi_bwrite_cmd(globals,
								 ARMVXI_LOCKUNLOCK,
								 armIdx,
								 &vxiCmd,
								 N, //number of bytes
								 Buff);
	}
	else
	if (UNMBASE_FLAG_MB & globals->basetype)
	{
		ViChar tmpbuff[96], *tmpbuffptr;
		ViUInt32 cnt, digits;

		//готовим для передачи выровненныый блок данных 488.2 Arbitrary Length Binary Block
		sprintf(tmpbuff, "%u", N);
		digits = strlen(tmpbuff);
		sprintf(tmpbuff, "MEMWRITE %u,%u",
				A, N);
		cnt = strlen(tmpbuff);
		tmpbuffptr = &tmpbuff[cnt];
		//общее количество передаваемых байт команды до начала данных = digits + cnt + 2 (это "#n")
		cnt += digits+2;
		while (cnt&3)
		{
			*tmpbuffptr++ = ' ';	//выравниваем при помощи пробелов
			cnt++;
		}
		sprintf(tmpbuffptr, "#%u%u",
				digits, N);

		LockMB(globals);

		errChkMB(vi, viBufWrite (vi, (ViPBuf)tmpbuff, cnt, VI_NULL));

		if (globals->baseBE)
		{
			void *swapbuf = malloc(N);
			if (!swapbuf)
			{
				errChk(VI_ERROR_ALLOC);
			}
			memcpy_swap32(swapbuf, Buff, N);
			status = viBufWrite (vi, (ViPBuf)swapbuf, N, &cnt);
			free(swapbuf);
			errChkMB(vi, status);
		}
		else
			errChkMB(vi, viBufWrite (vi, (ViPBuf)Buff, N, &cnt));

		errChkMB(vi, viFlush (vi, VI_WRITE_BUF));
		okChk(VI_SUCCESS);
	}
	i = A & 0xFF;   //internal block index
	if (i)      //we have first non-full block -
	{
		//read first block from (A & ~0xFF) to local tmpblock
		errChk( unmbase_blk_read(vi,
								 (A & ~0xFF),
								 64*sizeof(ViUInt32),
								 tmpblock, -1));

		n = 0x100 - (A & 0xFF);     //how real data we have to write in first block
		if (n > N)      //if we need bytes not to block end, correct n
			n = N;

		memcpy(&(tmpblock[i]), Buff, n);
		//write first block from tmpblock to (A & ~0xFF)
		errChk( unmbase_blk_write(vi,
								  (A & ~0xFF),
								  64*sizeof(ViUInt32),
								  tmpblock, -1));

		if (n == N)     //are all transfered?
		{
			okChk(VI_SUCCESS);
		}
		Buff += n;      //Buff point to next data
		N -= n;         //
		A += n;         //now (A & 0xFF) always zero
	}

	n = N & ~0xFF;      //byte syze of all full blocks
	if (n)      //we have some full blocks
	{
		//write not more 2 MBytes!!!
		while (n > (2*1024*1024))
		{
			//write full blocks from Buff to A
			errChk( unmbase_blk_write(vi,
									  A,
									  (2*1024*1024),
									  Buff, -1));
			n -= (2*1024*1024);
			Buff += (2*1024*1024);      //Buff point to next data
			N -= (2*1024*1024);         //
			A += (2*1024*1024);
		}
		//write full blocks from Buff to A
		errChk( unmbase_blk_write(vi,
								  A,
								  n,
								  Buff, -1));
		if (n == N)     //are all transfered?
		{
			okChk(VI_SUCCESS);
		}
		Buff += n;      //Buff point to next data
		N -= n;         //
		A += n;
	}

	if (N)
	{
		//now we assume that we have last non-full block with N byte size
		//read last block from A to local tmpblock
		errChk( unmbase_blk_read(vi,
								 A,
								 64*sizeof(ViUInt32),
								 tmpblock, -1));

		memcpy(tmpblock, Buff, N);
		//write last block from tmpblock to A
		errChk( unmbase_blk_write(vi,
								  A,
								  64*sizeof(ViUInt32),
								  tmpblock, -1));
	}
Error:
	UnlockMB(globals);
	return status;
}

static ViStatus m_data_read(PM_SESSION mglobals, ViUInt32 A, ViUInt32 N, ViUInt8 *Buff)
{
	ViUInt32 i, n;
	ViStatus status = VI_SUCCESS;

	mglobalsChk(mglobals);
	A +=  mglobals->membase_in;
	SpyLog3("m%d read block %08X bytes from %08X", mglobals->mnum, N, A);

	mglobals->tmp_block_remain = 0; //no remain bytes in tmpblock
	i = A & 0xFF;   //internal block index
	if (i)      //we have first non-full block
	{
		//read first block from (A & ~0xFF) to tmpblock
//SpyLog2("mDataRead(%d) 64w from %08X", mglobals->midx, (A & ~0xFF));
		errChk( unmbase_blk_read(mglobals->basevi,
								 (A & ~0xFF),
								 64*sizeof(ViUInt32),
								 mglobals->tmpblock, mglobals->midx));
		n = 0x100 - (A & 0xFF);     //how real data we have in first block
		if (n > N)      //if we need bytes not to block end, correct n
			n = N;

		memcpy(Buff, &(mglobals->tmpblock[i]), n);
		if (n == N)     //are all transfered?
		{
			okChk(VI_SUCCESS);
		}
		Buff += n;      //Buff point to next data
		N -= n;         //
		A += n;         //now (A & 0xFF) always zero
	}

	n = N & ~0xFF;      //byte syze of all full blocks
	if (n)      //we have some full blocks
	{
		//read not more 2 MBytes!!!
		while (n > (2*1024*1024))
		{
			//read full blocks to Buff
//SpyLog3("mDataRead(%d) %08Xw from %08X", mglobals->midx, (2*1024*1024), A);
			errChk( unmbase_blk_read(mglobals->basevi,
									 A,
									 (2*1024*1024),
									 Buff, mglobals->midx));
			n -= (2*1024*1024);
			Buff += (2*1024*1024);      //Buff point to next data
			N -= (2*1024*1024);         //
			A += (2*1024*1024);         //now A & 0xFF always zero
		}
		//read full blocks to Buff
//SpyLog3("mDataRead(%d) %08Xw from %08X", mglobals->midx, n, A);
		errChk( unmbase_blk_read(mglobals->basevi,
								 A,
								 n,
								 Buff, mglobals->midx));
		if (n == N)     //are all transfered?
		{
			okChk(VI_SUCCESS);
		}
		Buff += n;      //Buff point to next data
		N -= n;         //
		A += n;         //now A & 0xFF always zero
	}

	//now we assume that we have last non-full block with N byte size
	//read first block from A to tmpblock
//SpyLog3("mDataRead(%d) %08Xw from %08X (set VXIbusy)", mglobals->midx, N, A);
	errChk( unmbase_blk_read(mglobals->basevi,
							 A,
							 N,
							 mglobals->tmpblock, mglobals->midx));

	memcpy(Buff, &(mglobals->tmpblock), N);
	mglobals->tmp_block_remain = 0x100 - N; //how bytes remain in tmpblock
Error:
	return status;
}


/*
1) Если адрес приходится на невыровненный блок, то считываем блок, меняем в нем нужный кусок
   и записываем обратно.
2) Пишем все целые блоки
3) Если есть остаток, то считываем блок, меняем в нем нужный кусок и записываем обратно.
*/
static ViStatus m_data_write(PM_SESSION mglobals, ViUInt32 A, ViUInt32 N, ViUInt8 *Buff)
{
	ViStatus status = VI_SUCCESS;
	ViUInt32 i, n;
	ViUInt8 tmpblock[64*sizeof(ViUInt32)];

	mglobalsChk(mglobals);
	A +=  mglobals->membase_out;
	i = A & 0xFF;   //internal block index
	if (i)      //we have first non-full block -
	{
		//read first block from (A & ~0xFF) to local tmpblock
		errChk( unmbase_blk_read(mglobals->basevi,
								 (A & ~0xFF),
								 64*sizeof(ViUInt32),
								 tmpblock, mglobals->midx));

		n = 0x100 - (A & 0xFF);     //how real data we have to write in first block
		if (n > N)      //if we need bytes not to block end, correct n
			n = N;

		memcpy(&(tmpblock[i]), Buff, n);
		//write first block from tmpblock to (A & ~0xFF)
		errChk( unmbase_blk_write(mglobals->basevi,
								  (A & ~0xFF),
								  64*sizeof(ViUInt32),
								  tmpblock, mglobals->midx));

		if (n == N)     //are all transfered?
		{
			okChk(VI_SUCCESS);
		}
		Buff += n;      //Buff point to next data
		N -= n;         //
		A += n;         //now (A & 0xFF) always zero
	}

	n = N & ~0xFF;      //byte syze of all full blocks
	if (n)      //we have some full blocks
	{
		//write not more 2 MBytes!!!
		while (n > (2*1024*1024))
		{
			//write full blocks from Buff to A
			errChk( unmbase_blk_write(mglobals->basevi,
									  A,
									  (2*1024*1024),
									  Buff, mglobals->midx));
			n -= (2*1024*1024);
			Buff += (2*1024*1024);      //Buff point to next data
			N -= (2*1024*1024);         //
			A += (2*1024*1024);
		}
		//write full blocks from Buff to A
		errChk( unmbase_blk_write(mglobals->basevi,
								  A,
								  n,
								  Buff, mglobals->midx));
		if (n == N)     //are all transfered?
		{
			okChk(VI_SUCCESS);
		}
		Buff += n;      //Buff point to next data
		N -= n;         //
		A += n;
	}

	if (N)
	{
		//now we assume that we have last non-full block with N byte size
		//read last block from A to local tmpblock
		errChk( unmbase_blk_read(mglobals->basevi,
								 A,
								 64*sizeof(ViUInt32),
								 tmpblock, mglobals->midx));

		memcpy(tmpblock, Buff, N);
		//write last block from tmpblock to A
		errChk( unmbase_blk_write(mglobals->basevi,
								  A,
								  64*sizeof(ViUInt32),
								  tmpblock, mglobals->midx));
	}
Error:
	return status;
}

//--------------------------------------------------
ViStatus _VI_FUNCC unmbase_flash_write(ViSession vi,
									  ViUInt32 armIdx,
									  ViUInt32 A, //FLASH Address (full ARM address)
									  ViUInt32 N, //number of bytes
									  ViUInt8 *Buff)
{
	PUserData globals = NULL;
	ViStatus status = VI_SUCCESS;
	ViInt32 oldTMO = -1, locked = 0;
	char tmpstr[256];
	char *buf=VI_NULL;

SpyLog3("unmbase_flash_write(arm%d,%08X[%08X])\n", armIdx, A, N);
	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));

	if (globals->basetype == UNMBASE_TYPE_ARM)
	{
		VXI_CMD vxiCmd;

		if (atof(globals->fw_rev) < 1.015)	//первые версии (до 1.02) поддерживают PREPARE/WRITE только с EEPROM ATMEL !
		{
			vxiCmd.cmd = ARMCMD_FLASH_PREPARE_DATA;
			vxiCmd.data0 = N;

			status = armvxi_bwrite_cmd(globals,
									 ARMVXI_LOCK,
									 armIdx,
									 &vxiCmd,
									 N, //number of bytes
									 Buff);
			if (0 == status)
			{
				vxiCmd.cmd = ARMCMD_FLASH_WRITE_PREPARED;
				vxiCmd.data0 = A;
				vxiCmd.data1 = N;

				status = armvxi_cmd(globals,
								 ARMVXI_NOLOCK,
								 0.5 + (ViReal64)N / 10000.0,	//пусть 10К в секунду...
								 armIdx,
								 &vxiCmd);
				UnlockARM(globals, armIdx);
			}
		}
		else
		{
			vxiCmd.cmd = ARMCMD_FLASH_REWRITE;
			vxiCmd.data0 = A;
			vxiCmd.data1 = N;

			status = armvxi_bwrite_cmd(globals,
									 0,
									 armIdx,
									 &vxiCmd,
									 N, //number of bytes
									 Buff);
			 //tmo need to be: 0.5 + (ViReal64)N / 10000.0,	//пусть 10К в секунду...
		}
		if (!status)
			cross_delay(0.050 + (ViReal64)N / 1000000.0);
		return status;
	}
	else
	if (UNMBASE_FLAG_MB & globals->basetype)
	{
		LockMB(globals);
		if ((!globals->baseBE && !globals->baseAXIe) ||
			armIdx > 1)
		{
			sprintf(tmpstr,
					"FLASH:REWRITE    0x%08X,0x%08X,#",
					A,
					(N + 0x3FF) & ~0x3FF);	//align to 1 K
		}
		else
		{
			sprintf(tmpstr,
					"ARM:FLASH:REWRITE%u   0x%08X,0x%08X,#",
					armIdx+1,
					A,
					(N + 0x3FF) & ~0x3FF);	//align to 1 K
		}
		locked = strlen(tmpstr);

		buf = malloc(locked + N);
		if (!buf)
		{
			errChk(VI_ERROR_ALLOC);
		}
		strcpy(buf, tmpstr);
		memcpy(buf+locked, Buff, N);
		if (globals->baseBE &&
			armIdx <= 1)
		{
			mem_swap32(buf+locked, (N+3)&~3);
		}
		viGetAttribute(vi, VI_ATTR_TMO_VALUE, &oldTMO);
		viSetAttribute(vi, VI_ATTR_TMO_VALUE, 20000);	//20 s.

		errChk(viWrite (vi, (ViBuf)buf, locked+N, 0));
		//tmo need to be: 0.5 + (ViReal64)N / 10000.0,	//пусть 10К в секунду...
		
		cross_delay(0.050 + (ViReal64)N / 1000000.0);
	}
	else
		status = VI_ERROR_NSUP_OPER;
Error:
	if (oldTMO >= 0)
		viSetAttribute(vi, VI_ATTR_TMO_VALUE, oldTMO);

	if (locked)
		UnlockMB(globals);
	if (buf)
		free(buf);
	return status;
}

//--------------------------------------------------
ViStatus _VI_FUNCC unmbase_reboot(ViSession vi,
								  ViUInt32 armIdx)
{
	PUserData globals = NULL;
	ViStatus status = VI_SUCCESS;

	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));

	if (globals->basetype == UNMBASE_TYPE_ARM)
	{
		status = ArmVxiOutRAM(globals->vi, armIdx,
					ARMVXI_CMD_WORD,
					ARMCMD_REBOOT);
	}
	else
	if (UNMBASE_FLAG_MB & globals->basetype)
	{
		LockMB(globals);

		if ((!globals->baseBE && !globals->baseAXIe) ||
			armIdx > 1)
		{
			status = viPrintf (vi,
							   "REBOOT\n");
		}
		else
		{
			status = viPrintf (vi,
							   "ARM:REBOOT%d\n",
							   armIdx+1);
		}
		UnlockMB(globals);
		errChkMB(vi, status);
	}
	else
		status = VI_ERROR_NSUP_OPER;
Error:
	return status;
}

//--------------------------------------------------
ViStatus _VI_FUNCC unmbase_rtc_q(ViSession vi,
								  ViUInt32 armIdx,
								  ViUInt32 *rtc)
{
	PUserData globals = NULL;
	ViStatus status = VI_SUCCESS;

	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));

	if (globals->basetype == UNMBASE_TYPE_ARM)
	{
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;

		vxiCmd.cmd = ARMCMD_RTCq;

		errChk(armvxi_arm_cmd( globals,
					ARMVXI_LOCKUNLOCK,
					ARMVXI_TMO1,
					armIdx,
					&vxiCmd, &vxiAnsw));

		*rtc = vxiAnsw.data0;
	}
	else
		status = VI_ERROR_NSUP_OPER;
Error:
	return status;
}

//--------------------------------------------------
ViStatus _VI_FUNCC unmbase_spy(ViSession vi,
								  ViUInt32 armIdx,
								  ViUInt32 enable)
{
	PUserData globals = NULL;
	ViStatus status = VI_SUCCESS;

	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));

	if (globals->basetype == UNMBASE_TYPE_ARM)
	{
		VXI_CMD vxiCmd;

		vxiCmd.cmd = armvxiCmdD16(ARMCMD_SPY,
								  enable);

		errChk(armvxi_arm_cmd( globals,
					ARMVXI_LOCKUNLOCK,
					ARMVXI_TMO1,
					armIdx,
					&vxiCmd, NULL));
	}
	else
	if (UNMBASE_FLAG_MB & globals->basetype)
	{
		LockMB(globals);

		if ((!globals->baseBE && !globals->baseAXIe) ||
			armIdx > 1)
		{
			status = viPrintf (vi,
							   "SPY %d\n",
							   enable);
		}
		else
		{
			status = viPrintf (vi,
							   "ARM:SPY%d %d\n",
							   armIdx+1,
							   enable);
		}
		UnlockMB(globals);
		errChkMB(vi, status);
	}
	else
		status = VI_ERROR_NSUP_OPER;
Error:
	return status;
}

//--------------------------------------------------
ViStatus _VI_FUNCC unmbase_spy_q(ViSession vi,
								  ViUInt32 armIdx,
								  ViChar *spybuf)
{
	PUserData globals = NULL;
	ViStatus status = VI_SUCCESS;

	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));

	*spybuf = 0;
	if (globals->basetype == UNMBASE_TYPE_ARM)
	{
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;

		vxiCmd.cmd = ARMCMD_SPYq;

		errChk(armvxi_bread_cmd(globals,
								ARMVXI_LOCKUNLOCK,
								armIdx,
								&vxiCmd,
								&vxiAnsw,
								65536,		//max number of bytes
								(ViUInt8*)spybuf,
								VI_NULL));	//количество реально прочитанных байт
	}
	else
	if (UNMBASE_FLAG_MB & globals->basetype)
	{
		LockMB(globals);

		if ((!globals->baseBE && !globals->baseAXIe) ||
			armIdx > 1)
		{
			status = viQueryf (vi,
							   "SPY?\n",
							   "%65536t",
							   spybuf);
		}
		else
		{
			ViInt32 len;
			status = viQueryf (vi,
							   "ARM:SPY%d?\n",
							   "%65536t",
							   armIdx+1,
							   spybuf);
			len = strlen(spybuf);
			mem_swap32(spybuf, (len+3)&~3);
		}
		UnlockMB(globals);
		errChkMB(vi, status);
	}
	else
		status = VI_ERROR_NSUP_OPER;
Error:
	return status;
}

//--------------------------------------------------
ViStatus _VI_FUNCC unmbase_stat_spy(ViSession vi,
								  ViUInt32 armIdx)
{
	PUserData globals = NULL;
	ViStatus status = VI_SUCCESS;

	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));

	if (globals->basetype == UNMBASE_TYPE_ARM)
	{
		VXI_CMD vxiCmd;

		vxiCmd.cmd = ARMCMD_STATSPY;
		errChk(armvxi_arm_cmd( globals,
					ARMVXI_LOCKUNLOCK,
					ARMVXI_TMO1,
					armIdx,
					&vxiCmd, NULL));
	}
	else
		status = VI_ERROR_NSUP_OPER;
Error:
	return status;
}

//////////////////S  P  D/////////////////////

#define spdROWS(buff)       (buff[3])
#define spdCOLUMNS(buff)    (buff[4])
#define spdSIDES(buff)      (buff[5])
#define spdBANKS(buff)      (buff[17])

static ViUInt32 GetDIMMsize(ViUInt8 buff[])
{
	return ((1 << ((spdROWS(buff)+spdCOLUMNS(buff)))) * spdSIDES(buff) * spdBANKS(buff) * 8);
}

//pass NULL if one of the SPD absent
static ViStatus CheckSPD(ViUInt8 buff1[], ViUInt8 buff2[])
{
	if (!(buff1 || buff2))
		return UNMBASE_ERROR_SPD;
	if (buff1)
		if ((buff1[2] != 4) ||
				(spdROWS(buff1) < 12) || (spdROWS(buff1) > 13) ||
				(spdCOLUMNS(buff1) < 9) || (spdCOLUMNS(buff1) > 12) ||
				(spdSIDES(buff1) < 1) || (spdSIDES(buff1) > 2) ||
				(spdBANKS(buff1) != 4) ||
				!((buff1[6] == 64) || (buff1[6] == 72)) ||
				(buff1[8] != 1) ||
				((buff1[16] & 0x80) != 0x80))
			return UNMBASE_ERROR_SPD;
	if (buff2)
		if ((buff2[2] != 4) ||
				(spdROWS(buff2) < 12) || (spdROWS(buff2) > 13) ||
				(spdCOLUMNS(buff2) < 9) || (spdCOLUMNS(buff2) > 12) ||
				(spdSIDES(buff2) < 1) || (spdSIDES(buff2) > 2) ||
				(spdBANKS(buff2) != 4) ||
				!((buff2[6] == 64) || (buff2[6] == 72)) ||
				(buff2[8] != 1) ||
				((buff2[16] & 0x80) != 0x80))
			return UNMBASE_ERROR_SPD;
	if (buff1 && buff2)
		if ((buff1[0] != buff2[0]) ||
				(buff1[3] != buff2[3]) ||
				(buff1[4] != buff2[4]) ||
				(buff1[5] != buff2[5]) ||
				(buff1[6] != buff2[6]))
			return UNMBASE_ERROR_SPD;
	return 0;
}

static ViStatus ConfigRAM(ViSession vi, ViUInt8 buff[])
{
	ViUInt32 word;
	ViStatus status = VI_SUCCESS;
	errChk( viIn32(vi, 2, rgCONF1, &word));
	word &= ~(maskCONF1_COL_SEL_ALL | maskCONF1_ROW_SEL_ALL | maskCONF1_CS_SEL_ALL);
	switch (spdCOLUMNS(buff))
	{
	case 9:
		word |= maskCONF1_COL_SEL9;
		break;
	case 10:
		word |= maskCONF1_COL_SEL10;
		break;
	case 11:
		word |= maskCONF1_COL_SEL11;
		break;
	case 12:
		word |= maskCONF1_COL_SEL12;
		break;
	}
	if (spdROWS(buff) == 13)
		word |= maskCONF1_ROW_SEL13;
	if (spdSIDES(buff) == 2)
		word |= maskCONF1_CS_SEL2;
	errChk( viOut32(vi, 2, rgCONF1, word));
Error:
	return status;
}

////////////////SPD EEPROM///////////////////
//inverse data

//#define SPD_BLOCK_IO

#define SPD_BLK_N		256
#define SPD_BLK_REP		3

typedef struct _sSPD_WORK
{
	ViInt32 fastintf;
	ViUInt32 D;
	ViUInt32 buf[SPD_BLK_N];
#ifdef SPD_BLOCK_IO
	ViUInt32 outbuf[SPD_BLK_N*SPD_BLK_N];
#endif
	ViUInt32 n;
} sSPD_WORK, *psSPD_WORK;

static ViStatus _VI_FUNC spdFlushOut (ViSession vi, psSPD_WORK spd)
{
	ViStatus status = 0;
	PUserData globals = NULL;

	if (spd->n)
	{
		ViUInt32 i;

		if (viGetAttribute (vi, VI_ATTR_USER_DATA, &globals) < 0)
			globals = NULL;

		if (globals && (status = LockRgComm1(globals)) < 0)
			return status;

#ifndef SPD_BLOCK_IO	//SINGLE
		for (i=0; i<spd->n; i++)
		{
			if (spd->fastintf)
			{	//DUMB cross_delay
				ViUInt16 tmp16;
				viIn16(vi, VI_A16_SPACE, 2, &tmp16);
			}
			errChk(viOut32 (vi, 2, rgCOMM1, spd->buf[i]));
		}
#else	//BLOCK
		ViUInt32 N = 0;
		for (i=0; i<spd->n; i++)
		{
			int j;

			for (j=0; j<SPD_BLK_REP; j++)
			{
				spd->outbuf[N++] = spd->buf[i];
			}
		}
		errChk(viMoveOut32 (vi, 2, rgCOMM1, N, spd->outbuf));

#endif
		//if (spd->n > spdMaxOut)
		//	spdMaxOut = spd->n;
	}
Error:
	if (globals)
		UnlockRgComm1(globals);
	spd->n = 0;
	spd->D = 0xFFFFFFFF;
	return status;
}

static ViStatus _VI_FUNC spdOut (ViSession vi, psSPD_WORK spd, ViUInt32 word)
{
	word ^= (maskCOMM1_I2C_SDA | maskCOMM1_I2C_SCL);
	if (spd->D != word)
	{
		spd->D = word;
		spd->buf[spd->n++] = word;
	}
	if (SPD_BLK_N == spd->n)
		return spdFlushOut(vi, spd);
	return 0;
}

static ViStatus _VI_FUNC spdIn (ViSession vi, psSPD_WORK spd, ViUInt8 *bit)
{
	ViStatus status = VI_SUCCESS;
	PUserData globals = NULL;
	ViUInt32 d;

	errChk(spdFlushOut(vi, spd));


	if (viGetAttribute (vi, VI_ATTR_USER_DATA, &globals) < 0)
		globals = NULL;

	if (globals && (status = LockRgComm1(globals)) < 0)
		return status;

	if (spd->fastintf)
	{	//DUMB cross_delay
		ViUInt16 tmp16;
		viIn16(vi, VI_A16_SPACE, 2, &tmp16);
	}
	errChk( viIn32 (vi, 2, rgSTAT1, &d));                       //read data
	*bit = ((d & maskSTAT1_I2C_SDA) != 0);
Error:
	if (globals)
		UnlockRgComm1(globals);
	return status;
}

static ViStatus _VI_FUNC spdSTART (ViSession vi, psSPD_WORK spd)
{
	ViStatus status = VI_SUCCESS;

	errChk( spdOut (vi, spd, maskCOMM1_I2C_SDA | maskCOMM1_I2C_SCL));
	errChk( spdOut (vi, spd, maskCOMM1_I2C_SCL));
	errChk( spdOut (vi, spd, 0));
Error:
	return status;
}

_UNMBASE_API ViStatus _VI_FUNC spdSTOP (ViSession vi, psSPD_WORK spd)
{
	ViStatus status = VI_SUCCESS;

	errChk( spdOut (vi, spd, maskCOMM1_I2C_SCL));
	errChk( spdOut (vi, spd, maskCOMM1_I2C_SDA | maskCOMM1_I2C_SCL));
Error:
	return status;
}

_UNMBASE_API ViStatus _VI_FUNC unmbase_spd_w_byte (ViSession vi, psSPD_WORK spd, ViUInt8 data)
{
	ViStatus status = VI_SUCCESS;
	ViInt16 i;
	ViUInt32 d;
	ViUInt8 bit;

	for (i = 0; i < 8; i++)     //high bit first, shift all 8 bits to SDA
	{

		d = (data & 0x80) ? maskCOMM1_I2C_SDA : 0;
		data = data << 1;

		errChk( spdOut (vi, spd, d));

		d |= maskCOMM1_I2C_SCL;

		errChk( spdOut (vi, spd, d));

		d &= ~maskCOMM1_I2C_SCL;

		if (i==7)   //last bit
		{
			errChk( spdOut (vi, spd, maskCOMM1_I2C_SDA));
			errChk( spdOut (vi, spd, maskCOMM1_I2C_SDA | maskCOMM1_I2C_SCL));
			errChk( spdOut (vi, spd, maskCOMM1_I2C_SDA));
		}
		else
		{
			errChk( spdOut (vi, spd, d));
		}
	}
	//cross_delay(0.001);
	errChk( spdIn (vi, spd, &bit));  //read ASK
	if (bit)    //if ASK != 0
	{
		errChk(UNMBASE_ERROR_SPD);
	}
Error:
	return status;
}

_UNMBASE_API ViStatus _VI_FUNC unmbase_spd_r_byte (ViSession vi, psSPD_WORK spd, ViUInt8 *data, ViInt16 last)
{
	ViStatus status = VI_SUCCESS;
	ViInt16 i;
	ViUInt8 bit;

	*data = 0;

	errChk( spdOut (vi, spd, maskCOMM1_I2C_SDA));                    //0 1
	for (i = 0;i < 8;i++)   //high bit first, shift all 8 bits to SDA
	{
		errChk( spdOut (vi, spd, maskCOMM1_I2C_SDA | maskCOMM1_I2C_SCL)); //C=1,D=1
		errChk( spdIn (vi, spd, &bit));
		*data = (*data << 1) | bit; //shift previous bit
		errChk( spdOut (vi, spd, maskCOMM1_I2C_SDA));                    //C=0,D=1

	}

//ASK
	if (last)
	{
		errChk( spdOut (vi, spd, maskCOMM1_I2C_SDA));                    //0 1
		errChk( spdOut (vi, spd, maskCOMM1_I2C_SDA | maskCOMM1_I2C_SCL)); //1 1
		errChk( spdOut (vi, spd, maskCOMM1_I2C_SDA));                    // 1 0
	}
	else
	{
		errChk( spdOut (vi, spd, 0));                    //0 0
		errChk( spdOut (vi, spd, maskCOMM1_I2C_SCL));    //1 0
		errChk( spdOut (vi, spd, maskCOMM1_I2C_SDA));    //0 1
	}

Error:
	return status;
}

ViStatus  _VI_FUNC unmbase_spd_read(ViSession vi, ViInt16 dimm, ViUInt8 buff[])
{
	ViStatus status = VI_SUCCESS;
	ViInt16 i;
	psSPD_WORK spd = calloc(1, sizeof(*spd));
	if (!spd)
	{
		errChk(VI_ERROR_ALLOC);
	}
	spd->D = 0xFFFFFFFF;
	spd->fastintf = 1;

	//
	{	// проверка - быстрый или медленный это интерфейс
		char tmpstr[256];
		viGetAttribute (vi, VI_ATTR_INTF_INST_NAME, tmpstr);
		if (strstr(tmpstr, "TCP"))
			spd->fastintf = 0;
		else
		if (strstr(tmpstr, "USB"))
			spd->fastintf = 0;
	}
	errChk( viOut32(vi, VI_A24_SPACE,
					rgMASKCOMM1,
					0xFFFFFFFF));  //NEW FOR COMM1 WRITE MASK!!!
	errChk( spdSTART (vi, spd));
	errChk( unmbase_spd_w_byte(vi, spd, 0xA0 | (dimm<<1)));  //DEVICE SELECT CODE (WR)
	errChk( unmbase_spd_w_byte(vi, spd, 0x00));  //Address=0
	errChk( spdSTART (vi, spd));
	errChk( unmbase_spd_w_byte(vi, spd, 0xA1 | (dimm<<1)));  //DEVICE SELECT CODE (RD)
	for (i=0; i<128; i++)
	{
		errChk( unmbase_spd_r_byte(vi, spd, &buff[i], (i==127)));
	}
	errChk( spdSTOP (vi, spd));
	errChk( spdFlushOut(vi, spd));
Error:
	if (spd)
		free(spd);
	return status;
}

ViStatus  _VI_FUNC unmbase_spd_write(ViSession vi, ViInt16 dimm, ViUInt8 buff[])
{
	ViStatus status = VI_SUCCESS;
	ViInt16 i, j;
	psSPD_WORK spd = calloc(1, sizeof(*spd));
	if (!spd)
	{
		errChk(VI_ERROR_ALLOC);
	}
	spd->D = 0xFFFFFFFF;
	spd->fastintf = 1;
	//
	{	// проверка - быстрый или медленный это интерфейс
		char tmpstr[256];
		viGetAttribute (vi, VI_ATTR_INTF_INST_NAME, tmpstr);
		if (!strstr(tmpstr, "TCP"))
			spd->fastintf = 0;
		else
		if (!strstr(tmpstr, "USB"))
			spd->fastintf = 0;
	}
	for (i=0; i<16; i++)
	{
		errChk( spdSTART (vi, spd));
		errChk( unmbase_spd_w_byte(vi, spd, 0xA0 | (dimm<<1)));  //DEVICE SELECT CODE (WR)
		errChk( unmbase_spd_w_byte(vi, spd, i*8));   //Address=0,8,16...
		for (j=0; j<8; j++)
		{
			errChk( unmbase_spd_w_byte(vi, spd, buff[i*8+j]));
		}
		spdFlushOut(vi, spd);
		//cross_delay(0.001);
		errChk( spdSTOP (vi, spd));
		cross_delay(0.100);
	}
	errChk( spdFlushOut(vi, spd));
Error:
	if (spd)
		free(spd);
	return status;
}


static ViStatus progFlex1(ViSession vi, const ViUInt8 *buff, ViInt32 size, int firstFlexLoad)
{
//Для Флекса1 делаем алгоритм на спец. функциях вывода Out16_xxx (потом либо восстанавливаем, либо делаем и для флекса2)
	ViInt32 i;
	ViStatus status = VI_SUCCESS;
	ViUInt16 *buff2;
	static const ViUInt16 S_mask = maskS_nstatus |
								   maskS_nCONF1;
	static const ViUInt16 S_mask_ok = maskS_nstatus |
									  maskS_nCONF1;

	static const ViUInt16 S_mask1 = maskS_nstatus |
									maskS_nCONF1;
	buff2 = (ViUInt16 *)malloc(size*2);
	if (buff2 == 0)
	{
		errChk(VI_ERROR_ALLOC);
	}
	//Reset
	errChk( Out16_C(vi,
					~0,
					1));
	errChk( Out16_C(vi,
					~1,
					0));
	cross_delay(0.001);
	size -= 1;  //Altera rbf have one excess trailed byte

	/*  errChk( CheckS(vi,
						S_mask,
						S_mask_ok));    //do not check - may be we already loaded FLEX
	*/
	errChk( Out16_C(vi,
					0,
					maskC_nCONF1 + maskC_nCONF2 + maskC_CS1 + maskC_CS2 + maskC_EN_A24));
	errChk( CheckS(vi,
				   S_mask,
				   S_mask_ok));
	errChk( Out16_C(vi,
					~maskC_nCONF1,
					0));
	cross_delay(0.001);

	errChk( Out16_C(vi,
					~0,
					maskC_nCONF1));
	cross_delay(0.001);

	errChk( CheckS(vi,
				   S_mask1,
				   S_mask1));

	errChk( Out16_C(vi,
					~maskC_CS1,
					0));
	cross_delay(0.001);

	errChk( CheckS(vi,
				   maskS_CS1,
				   0));

//  for (i=0; i<size; i++) {
//      errChk( viOut16(vi, VI_A16_SPACE,
//                      rgCONF_DATA,
//                      buff[i]));
//  }
	for (i=0; i<size; i++)
		buff2[i] = buff[i];
	viSetAttribute (vi, VI_ATTR_DEST_INCREMENT, 0);
#ifdef UNMBASE_DEBUG_CVI
	SetBreakOnProtectionErrors (0);
#endif
	if (firstFlexLoad)
	{
		viMoveOut16(vi, VI_A16_SPACE,
					2,
					size < 0x10000 ? size : 0x10000,
					buff2);
	}
	errChk( viMoveOut16(vi, VI_A16_SPACE,
						rgCONF_DATA,
						size,
						buff2));
#ifdef UNMBASE_DEBUG_CVI
	SetBreakOnProtectionErrors (1);
#endif
	errChk( Out16_C(vi,
					~0,
					maskC_CS1));
	cross_delay(0.001);

	errChk( CheckS(vi,
				   maskS_conf_done1,
				   maskS_conf_done1));
Error:
	if (buff2)
		free(buff2);
	return status;
}

static ViStatus progFlex2(ViSession vi, const ViUInt8 *buff, ViInt32 size, int firstFlexLoad)
{
//Для Флекса2 делаем алгоритм на спец. функциях вывода Out16_xxx (потом либо восстанавливаем, либо делаем и для флекса2)
	ViInt32 i;
	ViStatus status = VI_SUCCESS;
	ViUInt16 *buff2;
	static const ViUInt16 S_mask = maskS_nstatus |
								   maskS_nCONF2;
	static const ViUInt16 S_mask_ok = maskS_nstatus |
									  maskS_nCONF2;

	static const ViUInt16 S_mask1 = maskS_nstatus |
									maskS_nCONF2;

	buff2 = (ViUInt16 *)malloc(size*2);
	if (buff2 == 0)
	{
		errChk(VI_ERROR_ALLOC);
	}
	//Reset
	errChk( Out16_C(vi,
					~0,
					1));
	errChk( Out16_C(vi,
					~1,
					0));
	cross_delay(0.001);
	size -= 1;  //Altera rbf have one excess trailed byte

	/*  errChk( CheckS(vi,
						S_mask,
						S_mask_ok));    //do not check - may be we already loaded FLEX
	*/
	errChk( Out16_C(vi,
					0,
					maskC_nCONF1 + maskC_nCONF2 + maskC_CS1 + maskC_CS2 + maskC_EN_A24));

	errChk( CheckS(vi,
				   S_mask,
				   S_mask_ok));

	errChk( Out16_C(vi,
					~maskC_nCONF2,
					0));
	cross_delay(0.001);

	errChk( Out16_C(vi,
					~0,
					maskC_nCONF2));
	cross_delay(0.001);

	errChk( CheckS(vi,
				   S_mask1,
				   S_mask1));

	errChk( Out16_C(vi,
					~maskC_CS2,
					0));
	cross_delay(0.001);

	errChk( CheckS(vi,
				   maskS_CS2,
				   0));

//  for (i=0; i<size; i++) {
//      errChk( viOut16(vi, VI_A16_SPACE,
//                      rgCONF_DATA,
//                      buff[i]));
//  }
	for (i=0; i<size; i++)
		buff2[i] = buff[i];
	viSetAttribute (vi, VI_ATTR_DEST_INCREMENT, 0);
#ifdef UNMBASE_DEBUG_CVI
	SetBreakOnProtectionErrors (0);
#endif
	if (firstFlexLoad)
	{
		viMoveOut16(vi, VI_A16_SPACE,
					2,
					size < 0x10000 ? size : 0x10000,
					buff2);
	}
	errChk( viMoveOut16(vi, VI_A16_SPACE,
						rgCONF_DATA,
						size,
						buff2));
#ifdef UNMBASE_DEBUG_CVI
	SetBreakOnProtectionErrors (1);
#endif

	errChk( Out16_C(vi,
					~0,
					maskC_CS2));
	cross_delay(0.001);

	errChk( CheckS(vi,
				   maskS_conf_done2,
				   maskS_conf_done2));
Error:
	if (buff2)
		free(buff2);
	return status;
}

/*--------------------------------------------------------------------------*/
/* IRQ Handler                                                              */
/*--------------------------------------------------------------------------*/
//#define PROCESS_BAD_IRQ
#define UNMBASE_SRQ_MEZ_IRQ			0x00
#define UNMBASE_SRQ_TRANS_BLOCK		0x10
#define UNMBASE_SRQ_RECV_BLOCK      0x20
#define UNMBASE_SRQ_TRANS_PACKET    0x30
#define UNMBASE_SRQ_RECV_PACKET     0x40
#define UNMBASE_SRQ_ERR1			0xE0
#define UNMBASE_SRQ_ERR2			0xF0

static void SrqHandler(ViSession     vi,
					   PUserData globals,
					   ViInt32 statid)
{
	ViInt32 i = (statid & 0x7)-1;	//mezzanine number

	SpyLog1("SRQ StatID=0x%02X\n", statid);

	if (globals->m_session[i].user_handler !=(ViAddr) VI_NULL)
	{

		if (globals->m_session[i].enable_irq)
		{

			switch (statid & 0xF0)
			{
			case UNMBASE_SRQ_MEZ_IRQ:	//конец блока
				globals->m_session[i].enable_irq = (* ((unmbase_UserHandler) globals->m_session[i].user_handler))
												   (globals->m_session[i].extvi ? globals->m_session[i].extvi : MVI_ID |globals->m_vi_idx[i],
													UNMBASE_IRQ_MEZ_IRQ);
				break;
			case UNMBASE_SRQ_RECV_BLOCK:	//конец блока
				globals->m_session[i].enable_irq = (* ((unmbase_UserHandler) globals->m_session[i].user_handler))
												   (globals->m_session[i].extvi ? globals->m_session[i].extvi : MVI_ID |globals->m_vi_idx[i],
													UNMBASE_IRQ_RECV_BLOCK);
				break;
			case UNMBASE_SRQ_RECV_PACKET: //конец пакета
				globals->m_session[i].enable_irq = (* ((unmbase_UserHandler) globals->m_session[i].user_handler))
												   (globals->m_session[i].extvi ? globals->m_session[i].extvi : MVI_ID |globals->m_vi_idx[i],
													UNMBASE_IRQ_RECV_PACKET);
				break;
			case UNMBASE_SRQ_TRANS_BLOCK:	//конец блока
				globals->m_session[i].enable_irq = (* ((unmbase_UserHandler) globals->m_session[i].user_handler))
												   (globals->m_session[i].extvi ? globals->m_session[i].extvi : MVI_ID |globals->m_vi_idx[i],
													UNMBASE_IRQ_TRANS_BLOCK);
				break;
			case UNMBASE_SRQ_TRANS_PACKET: //конец пакета
				globals->m_session[i].enable_irq = (* ((unmbase_UserHandler) globals->m_session[i].user_handler))
												   (globals->m_session[i].extvi ? globals->m_session[i].extvi : MVI_ID |globals->m_vi_idx[i],
													UNMBASE_IRQ_TRANS_PACKET);
				break;
			case UNMBASE_SRQ_ERR1: //ошибка 1
				globals->m_session[i].enable_irq = (* ((unmbase_UserHandler) globals->m_session[i].user_handler))
												   (globals->m_session[i].extvi ? globals->m_session[i].extvi : MVI_ID |globals->m_vi_idx[i],
													UNMBASE_IRQ_ERR_1);
				break;
			case UNMBASE_SRQ_ERR2: //ошибка 1
				globals->m_session[i].enable_irq = (* ((unmbase_UserHandler) globals->m_session[i].user_handler))
												   (globals->m_session[i].extvi ? globals->m_session[i].extvi : MVI_ID |globals->m_vi_idx[i],
													UNMBASE_IRQ_ERR_2);
				break;
			}
		}
	}
}

static ViStatus _VI_FUNCH unmbase_IntHandler (ViSession vi,
		ViEventType type,
		ViEvent     context,
		PUserData globals)
{
	ViUInt32 statID;
	ViUInt32 stat1, stat2, complete, i;
	ViInt16 state = 0;
	ViStatus status = 0;

//printf("IRQ %08X, vi=%08X (%08X)\n", type, vi, globals->vi);
	if (globals->vi != vi)
		return VI_SUCCESS;		   //Irina DBG
	if (UNMBASE_FLAG_MB & globals->basetype)
	{	//==> MB
		ViInt32 statid[4];	//1,2,3,4 - конец блока;0x11,0x11,0x11,0x11 - конец пакета
		while (1)
		{
			LockMB(globals);
			if ((status = viQueryf(vi, "STATID?;STATID?;STATID?;STATID?\n",
								   "%i;%i;%i;%i",
								   &statid[0], &statid[1], &statid[2], &statid[3])) < 0)
			{
				//он чё, заблокирован?!
				UnlockMB(globals);
				SpyLog1("SRQ StatID Query Failed!!! status=0x%08X\n", status);
				break;
			}
			UnlockMB(globals);
			{
				int i;
				for (i=0; i<4; i++)
				{
					if (!statid[i])
						return 0;
					if (((statid[i] & 0x7) -1) > (globals->maxMez-1))	//mezzanine number
						SpyLog1("SRQ StatID=0x%02X - wrong mez number!\n", statid[i]);
					else
						SrqHandler(vi, globals, statid[i]);
				}
			}
		}

		return 0;
	}
//Check - what IRQ
//???
	viGetAttribute (context, VI_ATTR_INTR_STATUS_ID, &statID);
	SpyLog1("StatID=%04X\n", statID&0xFFFF);

	if (globals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM TODO ???
		ViInt32 armIdx;
		ViUInt32 statid[2][ARMVXI_IRQ_BUFF_NWORDS+1];
		ViUInt32 j, N=0;

		if (0 == (statID & 0x300))
			goto CheckMezIrq;	//это не от АРМов

		//сначала читаем все StatID
		for (armIdx=0; armIdx<2; armIdx++)
		{
			if (0 == (statID & (0x100 << armIdx)))	//проверяем, от какого АРМ пришло прерывание
				continue;

			errChk(ArmVxiReadRAM(vi, armIdx,
							ARMVXI_IRQ_BUFF,
							ARMVXI_IRQ_BUFF_NWORDS+1, //+1, там индекс
							&statid[armIdx][0]));	//(не "statid[armIdx][0]" из-за warn Non Initialized...)
		}
		//для второго АРМ сразу корректируем номер мезонина, содержащийся в StatID
		if (statID & 0x200)
		{
			for (j=0; j<ARMVXI_IRQ_BUFF_NWORDS; j++)
			{
				if (((statid[1][j] & 7)-1) < 2)	//проверка, а вдруг там не номер мезонина (1 или 2)
				{
					statid[1][j] += 2;
				}
			}
		}
		//выделяем из них неодинаковые и строим единый массив,
		//используя под него statid[0]
		for (armIdx=0; armIdx<2; armIdx++)
		{
			ViUInt32 ArmVxiIrqIdx;

			if (0 == (statID & (0x100 << armIdx)))	//проверяем, от какого АРМ пришло прерывание
				continue;

			ArmVxiIrqIdx = statid[armIdx][ARMVXI_IRQ_BUFF_NWORDS];	//это ARMVXI_IRQ_IDX !!!

			if (ArmVxiIrqIdx >= ARMVXI_IRQ_BUFF_NWORDS)	//ошибка
				continue;

			if (ArmVxiIrqIdx < globals->ArmVxiIrqIdx[armIdx])
			{   //есть сначала до конца буфера
				for (i=globals->ArmVxiIrqIdx[armIdx]; i<ARMVXI_IRQ_BUFF_NWORDS; i++)
				{
					//если есть одинаковые - убираем
					for (j=0; j<N; j++)
					{
						if (statid[armIdx][i] == statid[0][j])
							break;
					}
					if (j == N)
						statid[0][N++] = statid[armIdx][i];
				}
				globals->ArmVxiIrqIdx[armIdx] = 0;
			}
			for (i=globals->ArmVxiIrqIdx[armIdx]; i<ArmVxiIrqIdx; i++)
			{
				//если есть одинаковые - убираем
				for (j=0; j<N; j++)
				{
					if (statid[armIdx][i] == statid[0][j])
						break;
				}
				if (j == N)
					statid[0][N++] = statid[armIdx][i];
			}
			globals->ArmVxiIrqIdx[armIdx] = ArmVxiIrqIdx;
		}
		//сбрасываем StatID
		for (armIdx=0; armIdx<2; armIdx++)
		{
			if (0 == (statID & (0x100 << armIdx)))	//проверяем, от какого АРМ пришло прерывание
				continue;

			errChk(ArmVxiInRAM(vi, armIdx,
							ARMVXI_IRQ,
							&j));
		}
		errChk( viOut16(vi, VI_A16_SPACE,   //clear IRQ from IC2 and IC3
						rgCOMM3,
						maskCOMM3_IRQ_IC2_RESET | maskCOMM3_IRQ_IC3_RESET));

		//Теперь вызываем верхний уровень для всех StatID
		for (i=0; i<N; i++)
		{
			if (statid[0][i])
			{
				if (((statid[0][i] & 0x7) -1) > (globals->maxMez-1))	//mezzanine number
					SpyLog1("SRQ StatID=0x%02X - wrong mez number!\n", statid[0][i]);
				else
					SrqHandler(vi, globals, statid[0][i]);
			}
		}

		goto CheckMezIrq;
	}

	if (statID & 0xC000)
	{
		globals->GlobalErrorIRQ++;
		//errChk(UNMBASE_ERROR_INSTR);
	}
	if (statID & 0x0300)    //IRQ from RAM or MEZ controller
	{

		if (statID & 0x0100)     //IRQ from RAM controller
		{
			errChk(viIn32(vi, VI_A24_SPACE,
						  rgSTAT1,
						  &stat1));
			SpyLog1("STAT1=%08X", stat1);
		}
		else
			stat1 = 0;

		if (statID & 0x0200)    //IRQ from MEZ controller
		{
			errChk(viIn32(vi, VI_A24_SPACE,
						  rgSTAT2,
						  &stat2));
			//проверка на зависающие прерывания по stat2
			if (maskSTAT2_ERR2_ALL & stat2)
			{
				ViUInt32 stat2x = stat2;

				stat2 &= IGNORE_STAT2_ERRORS;

				for (i=0; i<4; i++)
				{
					//Check IN
					if (stat2x & maskSTAT2_ERR2_M[i])
					{
						ViReal64 thistime = cross_timer();
						if ((thistime - globals->m_session[i].badIrqTimer) > BAD_IRQ_DT)
						{
							globals->m_session[i].badIrqCount = 0;
							globals->m_session[i].badIrqTimer = thistime;
						}
						else
						{
							//похоже, зависло...
							globals->m_session[i].badIrqCount++;
							if (globals->m_session[i].badIrqCount >= BAD_IRQ_MAX)
								stat2 |= maskSTAT2_ERR2_M[i];	//восстанавливаем данную ошибку
							SpyLog1("m%d: BAD ERR2!", i+1);
							globals->m_session[i].badIrqTimer = thistime;
						}
					}
				}
			}
			else
			{
				stat2 &= IGNORE_STAT2_ERRORS;
			}
			errChk(viIn32(vi, VI_A24_SPACE,
						  rgCOMPLETE,
						  &complete));
			SpyLog2("STAT2=%08X, COMPLETE=%08X", stat2, complete);
		}
		else
		{
			stat2 = 0;
			complete = 0;
		}

		for (i=0; i<4; i++)
		{
			//Check IN
			if ((stat1 & maskSTAT1_IRQ_IN[i]) ||
					(stat2 & maskSTAT2_ERR1_M[i]) ||
					(stat2 & maskSTAT2_ERR2_M[i]))
			{

				if (globals->m_session[i].state_in)
				{
					status = unmbase_m_state (MVI_ID |globals->m_vi_idx[i], UNMBASE_IOMODE_IN, &state); //check state
					SpyLog2("m%d StateIN=%d", i+1, state);
					if (state == 0)     //end of block
					{
						//user callback for receiving all block
						if (globals->m_session[i].user_handler !=(ViAddr) VI_NULL)
							if (globals->m_session[i].enable_irq)
								globals->m_session[i].enable_irq = (* ((unmbase_UserHandler) globals->m_session[i].user_handler))
																   (globals->m_session[i].extvi ? globals->m_session[i].extvi : MVI_ID |globals->m_vi_idx[i],
																	UNMBASE_IRQ_RECV_BLOCK);
						SpyLog3("m%d (end blk)- callback %08X return %d", i+1, globals->m_session[i].user_handler, globals->m_session[i].enable_irq);
					}
					else
					if (state > 0)   //receive packet
					{
						//user callback for receiving packet
						if (globals->m_session[i].user_handler !=(ViAddr) VI_NULL)
							if (globals->m_session[i].enable_irq)
								globals->m_session[i].enable_irq = (* ((unmbase_UserHandler) globals->m_session[i].user_handler))
																   (globals->m_session[i].extvi ? globals->m_session[i].extvi : MVI_ID |globals->m_vi_idx[i],
																	UNMBASE_IRQ_RECV_PACKET);
						SpyLog3("m%d (pkt recv)- callback %08X return %d", i+1, globals->m_session[i].user_handler, globals->m_session[i].enable_irq);
					}
					else      //ERROR !!!
					{
						//user callback for ERROR
						if (globals->m_session[i].user_handler !=(ViAddr) VI_NULL)
							if (globals->m_session[i].enable_irq)
							{
								if (stat2 & maskSTAT2_ERR1_M[i])
									globals->m_session[i].enable_irq = (* ((unmbase_UserHandler) globals->m_session[i].user_handler))
																	   (globals->m_session[i].extvi ? globals->m_session[i].extvi : MVI_ID |globals->m_vi_idx[i],
																		UNMBASE_IRQ_ERR_1);
								else
								if (stat2 & maskSTAT2_ERR2_M[i])
									globals->m_session[i].enable_irq = (* ((unmbase_UserHandler) globals->m_session[i].user_handler))
																	   (globals->m_session[i].extvi ? globals->m_session[i].extvi : MVI_ID |globals->m_vi_idx[i],
																		UNMBASE_IRQ_ERR_2);
								else
									globals->m_session[i].enable_irq = (* ((unmbase_UserHandler) globals->m_session[i].user_handler))
																	   (globals->m_session[i].extvi ? globals->m_session[i].extvi : MVI_ID |globals->m_vi_idx[i],
																		status);
							}
						SpyLog3("m%d (error)- callback %08X return %d", i+1, globals->m_session[i].user_handler, globals->m_session[i].enable_irq);
					}
				}
				errChk( Out32_COMM1(vi,     //clear IRQ
									~0,
									maskCOMM1_IRQ_IN_RESET[i]));
				if (globals->m_session[i].enable_irq)
					errChk( Out32_CONF1(vi,
										~maskCONF1_IRQ_IN_DIS[i],
										0));
				else
					errChk( Out32_CONF1(vi,
										~0,
										maskCONF1_IRQ_IN_DIS[i]));
			}
			else
			if (complete & maskCOMPLETE_IN[i])
			{
				SpyLog1("m%d - Complete", i+1);


				if (globals->m_session[i].mode_in == UNMBASE_MODE_SINGLE)
				{
					unmbase_m_stop_in(&globals->m_session[i]);
				}
				else
				{
					errChk( Out32_COMM2A(vi,
										 ~0,
										 maskCOMM2A_IN_RSTFLAG[i]));
				}
			}
			//Check OUT
			if ((stat1 & maskSTAT1_IRQ_OUT[i]) ||
					(stat2 & maskSTAT2_ERR1_M[i]) ||
					(stat2 & maskSTAT2_ERR2_M[i]))
			{

				if (globals->m_session[i].state_out)
				{
					status = unmbase_m_state (MVI_ID |globals->m_vi_idx[i], UNMBASE_IOMODE_OUT, &state);    //check state
					SpyLog2("m%d StateOUT=%d", i+1, state);
					if (state == 0)     //end of block
					{
						//user callback for receiving all block
						if (globals->m_session[i].user_handler !=(ViAddr) VI_NULL)
							if (globals->m_session[i].enable_irq)
								globals->m_session[i].enable_irq = (* ((unmbase_UserHandler) globals->m_session[i].user_handler))
																   (globals->m_session[i].extvi ? globals->m_session[i].extvi : MVI_ID |globals->m_vi_idx[i],
																	UNMBASE_IRQ_TRANS_BLOCK);
					}
					else
					if (state > 0)   //receive packet
					{
						//user callback for receiving packet
						if (globals->m_session[i].user_handler !=(ViAddr) VI_NULL)
							if (globals->m_session[i].enable_irq)
								globals->m_session[i].enable_irq = (* ((unmbase_UserHandler) globals->m_session[i].user_handler))
																   (globals->m_session[i].extvi ? globals->m_session[i].extvi : MVI_ID |globals->m_vi_idx[i],
																	UNMBASE_IRQ_TRANS_PACKET);
					}
					else      //ERROR !!!
					{
						//user callback for ERROR
						if (globals->m_session[i].user_handler !=(ViAddr) VI_NULL)
							if (globals->m_session[i].enable_irq)
							{
								if (stat2 & maskSTAT2_ERR1_M[i])
									globals->m_session[i].enable_irq = (* ((unmbase_UserHandler) globals->m_session[i].user_handler))
																	   (globals->m_session[i].extvi ? globals->m_session[i].extvi : MVI_ID |globals->m_vi_idx[i],
																		UNMBASE_IRQ_ERR_1);
								else
								if (stat2 & maskSTAT2_ERR2_M[i])
									globals->m_session[i].enable_irq = (* ((unmbase_UserHandler) globals->m_session[i].user_handler))
																	   (globals->m_session[i].extvi ? globals->m_session[i].extvi : MVI_ID |globals->m_vi_idx[i],
																		UNMBASE_IRQ_ERR_2);
								else
									globals->m_session[i].enable_irq = (* ((unmbase_UserHandler) globals->m_session[i].user_handler))
																	   (globals->m_session[i].extvi ? globals->m_session[i].extvi : MVI_ID |globals->m_vi_idx[i],
																		status);
							}
					}
				}
				errChk( Out32_COMM1(vi,     //clear IRQ
									~0,
									maskCOMM1_IRQ_OUT_RESET[i]));
				if (globals->m_session[i].enable_irq)
					errChk( Out32_CONF1(vi,
										~maskCONF1_IRQ_OUT_DIS[i],
										0));
				else
					errChk( Out32_CONF1(vi,
										~0,
										maskCONF1_IRQ_OUT_DIS[i]));
			}
			else
			if (complete & maskCOMPLETE_OUT[i])
			{
				errChk( Out32_COMM2A(vi,
									 ~0,
									 maskCOMM2A_OUT_RSTFLAG[i]));
			}
		}
		errChk( viOut16(vi, VI_A16_SPACE,   //clear IRQ from IC2 and IC3
						rgCOMM3,
						maskCOMM3_IRQ_IC2_RESET | maskCOMM3_IRQ_IC3_RESET));
		viOut16(vi, VI_A16_SPACE, rgCOMM3, 0);
	}
CheckMezIrq:
//NOTE: IRQ From Mezzanine Do Not affect Base IRQ and "enable_irq" value
	if (statID & 0x0400)    //IRQ from Mez1
	{
		//user callback for IRQ from mez1
		if (globals->m_session[0].user_handler !=(ViAddr) VI_NULL)
			if (globals->m_session[0].enable_m_irq)
				globals->m_session[0].enable_m_irq = (* ((unmbase_UserHandler) globals->m_session[0].user_handler))
													 (globals->m_session[0].extvi ? globals->m_session[0].extvi : MVI_ID |globals->m_vi_idx[0],
													  UNMBASE_IRQ_MEZ_IRQ);
		if (globals->m_session[0].enable_m_irq)
		{
			errChk( viOut16(vi, VI_A16_SPACE,
							rgCOMM3,
							maskCOMM3_IRQ1_RESET));
			viOut16(vi, VI_A16_SPACE, rgCOMM3, 0);
		}
		SpyLog2("m1 (mez irq)- callback %08X return %d", globals->m_session[0].user_handler, globals->m_session[0].enable_irq);
	}
	if (statID & 0x0800)    //IRQ from Mez2
	{
		//user callback for IRQ from mez2
		if (globals->m_session[1].user_handler !=(ViAddr) VI_NULL)
			if (globals->m_session[1].enable_m_irq)
				globals->m_session[1].enable_m_irq = (* ((unmbase_UserHandler) globals->m_session[1].user_handler))
													 (globals->m_session[1].extvi ? globals->m_session[1].extvi : MVI_ID |globals->m_vi_idx[1],
													  UNMBASE_IRQ_MEZ_IRQ);
		if (globals->m_session[1].enable_m_irq)
		{
			errChk( viOut16(vi, VI_A16_SPACE,
							rgCOMM3,
							maskCOMM3_IRQ2_RESET));
			viOut16(vi, VI_A16_SPACE, rgCOMM3, 0);
		}
		SpyLog2("m2 (mez irq)- callback %08X return %d", globals->m_session[1].user_handler, globals->m_session[1].enable_irq);
	}
	if (statID & 0x1000)    //IRQ from Mez3
	{
		//user callback for IRQ from mez3
		if (globals->m_session[2].user_handler !=(ViAddr) VI_NULL)
			if (globals->m_session[2].enable_m_irq)
				globals->m_session[2].enable_m_irq = (* ((unmbase_UserHandler) globals->m_session[2].user_handler))
													 (globals->m_session[2].extvi ? globals->m_session[2].extvi : MVI_ID |globals->m_vi_idx[2],
													  UNMBASE_IRQ_MEZ_IRQ);
		if (globals->m_session[2].enable_m_irq)
		{
			errChk( viOut16(vi, VI_A16_SPACE,
							rgCOMM3,
							maskCOMM3_IRQ3_RESET));
			viOut16(vi, VI_A16_SPACE, rgCOMM3, 0);
		}
		SpyLog2("m3 (mez irq)- callback %08X return %d", globals->m_session[2].user_handler, globals->m_session[2].enable_irq);
	}
	if (statID & 0x2000)    //IRQ from Mez4
	{
		//user callback for IRQ from mez4
		if (globals->m_session[3].user_handler !=(ViAddr) VI_NULL)
			if (globals->m_session[3].enable_m_irq)
				globals->m_session[3].enable_m_irq = (* ((unmbase_UserHandler) globals->m_session[3].user_handler))
													 (globals->m_session[3].extvi ? globals->m_session[3].extvi : MVI_ID |globals->m_vi_idx[3],
													  UNMBASE_IRQ_MEZ_IRQ);
		if (globals->m_session[3].enable_m_irq)
		{
			errChk( viOut16(vi, VI_A16_SPACE,
							rgCOMM3,
							maskCOMM3_IRQ4_RESET));
			viOut16(vi, VI_A16_SPACE, rgCOMM3, 0);
		}
		SpyLog2("m4 (mez irq)- callback %08X return %d", globals->m_session[3].user_handler, globals->m_session[3].enable_irq);
	}
	return VI_SUCCESS;
Error:
//now may be store error information in globals?
//and call ALL mezzanine handlers
	if (status == UNMBASE_ERROR_INSTR)
	{
#ifdef PROCESS_BAD_IRQ
		//store error and call enabled handlers
		for (i=0; i<4; i++)
		{
			if (globals->m_session[i].state_in > 0)
			{
				globals->m_session[i].state_in = -3;
				if (globals->m_session[i].user_handler !=(ViAddr) VI_NULL)
					if (globals->m_session[i].enable_irq)
						globals->m_session[i].enable_irq = (* ((unmbase_UserHandler) globals->m_session[i].user_handler))
														   (globals->m_session[i].extvi ? globals->m_session[i].extvi : MVI_ID |globals->m_vi_idx[i],
															status);
			}
			if (globals->m_session[i].state_out > 0)
			{
				globals->m_session[i].state_out = -3;
				if (globals->m_session[i].user_handler !=(ViAddr) VI_NULL)
					if (globals->m_session[i].enable_irq)
						globals->m_session[i].enable_irq = (* ((unmbase_UserHandler) globals->m_session[i].user_handler))
														   (globals->m_session[i].extvi ? globals->m_session[i].extvi : MVI_ID |globals->m_vi_idx[i],
															status);
			}
		}
		globals->state = -4;
#endif
	}
	return VI_SUCCESS;
}


/*--------------------------------------------------------------------------*/
/* Enable/Disable Events                                                    */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_config_event (ViSession mvi,
		ViBoolean enable)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = 0;
	ViUInt32 word;
	mviChk(mvi, mglobals);
	SpyLog2("unmbase_m_config_event(m%d, %d)", mglobals->mnum, enable);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;

		vxiCmd.cmd = armvxiCmdD16(ARMCMD_MIRQ_ENA,
								  enable);

		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								0,
								&vxiCmd, VI_NULL);

		mglobals->enable_irq = enable;
		mglobals->enable_m_irq = enable;
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		status = viPrintf (mglobals->basevi,
						   "MIRQ:ENABLE%d %d\n",
						   mglobals->mnum, enable);
		UnlockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, status);
		mglobals->enable_irq = enable;
		mglobals->enable_m_irq = enable;
	}
	else
	{
		if (!mglobals->basesimple)
		{
			errChk( Out32_CONF1(mglobals->basevi,               //Disble
								~0,
								(maskCONF1_IRQ_IN_DIS[mglobals->midx]
								 | maskCONF1_IRQ_OUT_DIS[mglobals->midx])));
			errChk( Out32_CONF2(mglobals->basevi,               //Disble
								~0,
								(maskCONF2_M_ERR1_IRQ_DIS[mglobals->midx]
								 | maskCONF2_M_ERR2_IRQ_DIS[mglobals->midx]
								 | maskCONF2_ERR3_IRQ_DIS
								 | maskCONF2_ERR4_IRQ_DIS)));
			errChk( viIn32 (mglobals->basevi, VI_A24_SPACE, rgENDIRQ, &word));
			errChk( viOut32 (mglobals->basevi, VI_A24_SPACE, rgENDIRQ,      //Disble
							 word |
							 (maskENDIRQ_IN_DIS[mglobals->midx]
							  | maskENDIRQ_OUT_DIS[mglobals->midx])));
			errChk( Out32_COMM1(mglobals->basevi,               //Reset
								~0,
								maskCOMM1_IRQ_IN_RESET[mglobals->midx]
								| maskCOMM1_IRQ_OUT_RESET[mglobals->midx]));
			errChk( Out32_COMM2(mglobals->basevi,               //Reset
								~0,
								maskCOMM2_ERR1_M_RST[mglobals->midx]
								| maskCOMM2_ERR2_M_RST[mglobals->midx]));
			errChk( viOut16(mglobals->basevi, VI_A16_SPACE,     //Reset
							rgCOMM3,
							maskCOMM3_IRQ_IC2_RESET
							| maskCOMM3_IRQ_IC3_RESET));
			viOut16(mglobals->basevi, VI_A16_SPACE, rgCOMM3, 0);
			if (enable)
			{
				if (!mglobals->dev_type)	//НЕ упрощенный
				{
					errChk( Out32_CONF1(mglobals->basevi,               //Enable
										~(maskCONF1_IRQ_IN_DIS[mglobals->midx]
										  | maskCONF1_IRQ_OUT_DIS[mglobals->midx]),
										0));
				}
				errChk( viOut16(mglobals->basevi, VI_A16_SPACE,     //Reset / Enable
								rgCOMM3,
								maskCOMM3_IRQ_RESET[mglobals->midx]
								| maskCOMM3_IRQ_IC2_RESET
								| maskCOMM3_IRQ_IC3_RESET));
				viOut16(mglobals->basevi, VI_A16_SPACE, rgCOMM3, 0);

				if (((PUserData)(mglobals->pbase_data))->imm_on == 0)
				{
					if (!mglobals->dev_type)  	//НЕ упрощенный
					{
						errChk( Out32_CONF2(mglobals->basevi,               //Enable
											~(maskCONF2_M_ERR1_IRQ_DIS[mglobals->midx]
											  | maskCONF2_M_ERR2_IRQ_DIS[mglobals->midx]
											  | maskCONF2_ERR3_IRQ_DIS
											  | maskCONF2_ERR4_IRQ_DIS),
											0));
						errChk( viIn32 (mglobals->basevi, VI_A24_SPACE, rgENDIRQ, &word));
						errChk( viOut32 (mglobals->basevi, VI_A24_SPACE, rgENDIRQ,              //Enable
										 word &
										 ~(maskENDIRQ_IN_DIS[mglobals->midx]
										   | maskENDIRQ_OUT_DIS[mglobals->midx])));
					}
					else	//упрощенный
					{
						errChk( Out32_CONF2(mglobals->basevi,               //Enable
											~( maskCONF2_ERR3_IRQ_DIS
											   | maskCONF2_ERR4_IRQ_DIS),
											0));
					}
				}
			}
		}
		else  	//basesimple
		{
			if (enable)
			{
				errChk( viOut16(mglobals->basevi, VI_A16_SPACE,     //Reset / Enable
								rgCOMM3,
								maskCOMM3_IRQ_RESET[mglobals->midx]
								| maskCOMM3_IRQ_IC2_RESET
								| maskCOMM3_IRQ_IC3_RESET));
			}
		}
	}
	mglobals->enable_irq = enable;
	mglobals->enable_m_irq = enable;
Error:
	if (mglobals)
		unmbase_ErrLed((PUserData)mglobals->pbase_data, status<0);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Query event enabled                                                      */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_config_event_q (ViSession mvi,
		ViBoolean *enable,
		ViBoolean *m_enable)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS;
	mviChk(mvi, mglobals);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;

		vxiCmd.cmd = ARMCMD_MIRQ_ENAq;

		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								0,
								&vxiCmd, &vxiAnsw);

		*enable = (ViBoolean)vxiAnsw.data16;
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		status = viQueryf (mglobals->basevi,
						   "MIRQ:ENABLE%d?\n",
						   "%hd",
						   mglobals->mnum,
						   &enable);
		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
		UnlockMB (mglobals->pbase_data);
		errChkMB(mglobals->basevi, status);
	}
	else
	{
		*enable = mglobals->enable_irq;
		*m_enable = mglobals->enable_m_irq;
	}
Error:
	return status;
}

/*--------------------------------------------------------------------------*/
/* Init clock source for CLK10                                              */
/*--------------------------------------------------------------------------*/
static void InitClk10(ViSession vi)
{
	ViInt32 i, x = 0x301401;
	ViUInt16 tmpdta;
	ViStatus status;

	errChk( viOut16(vi, VI_A16_SPACE,
					rgCOMM3,
					0));
	//Empty STRB for ECS Logic clear
	viIn16 (vi, VI_A16_SPACE, 2, &tmpdta);	//dumb delay for FAST interface
	errChk( viOut16(vi, VI_A16_SPACE,
					rgCOMM3,
					maskCOMM3_CLK_STRB));
	viIn16 (vi, VI_A16_SPACE, 2, &tmpdta);	//dumb delay for FAST interface
	errChk( viOut16(vi, VI_A16_SPACE,
					rgCOMM3,
					0));
	viIn16 (vi, VI_A16_SPACE, 2, &tmpdta);	//dumb delay for FAST interface

	for (i=0; i<24; i++)
	{
		if (x & 0x00800000)
		{
			errChk( viOut16(vi, VI_A16_SPACE,
							rgCOMM3,
							maskCOMM3_CLK_DATA));
			errChk( viOut16(vi, VI_A16_SPACE,
							rgCOMM3,
							maskCOMM3_CLK_DATA | maskCOMM3_CLK_CLK));
			errChk( viOut16(vi, VI_A16_SPACE,
							rgCOMM3,
							maskCOMM3_CLK_DATA));
		}
		else
		{
			errChk( viOut16(vi, VI_A16_SPACE,
							rgCOMM3,
							0));
			errChk( viOut16(vi, VI_A16_SPACE,
							rgCOMM3,
							maskCOMM3_CLK_CLK));
			errChk( viOut16(vi, VI_A16_SPACE,
							rgCOMM3,
							0));
		}
		x = x<<1;
	}
	viIn16 (vi, VI_A16_SPACE, 2, &tmpdta);	//dumb delay for FAST interface
	errChk( viOut16(vi, VI_A16_SPACE,
					rgCOMM3,
					maskCOMM3_CLK_STRB));
	viIn16 (vi, VI_A16_SPACE, 2, &tmpdta);	//dumb delay for FAST interface
	errChk( viOut16(vi, VI_A16_SPACE,
					rgCOMM3,
					0));
Error:
	return;
}

static ViStatus LoadDimmFlex(ViSession vi, void* userdata, int firstFlexLoad)
{
	PUserData globals = userdata;
	ViStatus status = 0;
#ifdef EXTERNAL_RBF
	int fhandle, fsize;
	ViUInt8 *filebuff;
#endif

#ifndef EXTERNAL_RBF
	//Load FLEX 1
	SpyLog1("Try to prog dimm control flex (rev.%d)...", globals->basetype);
#ifdef TECHNO
	printf("Try to prog dimm control flex (rev.%d)...", globals->basetype);
#endif
	switch (globals->basetype)
	{
	case UNMBASE_TYPE_1:
		status = progFlex1(vi, dimm_control, dimm_control_size, firstFlexLoad);
		break;
	case UNMBASE_TYPE_2:
		status = progFlex1(vi, dimm_control2, dimm_control2_size, firstFlexLoad);
		break;
	case UNMBASE_TYPE_2A:
#ifdef USE_RBF2_FOR2A
		status = progFlex1(vi, dimm_control2, dimm_control2_size, firstFlexLoad);
#else
		status = progFlex1(vi, dimm_control3, dimm_control3_size, firstFlexLoad);
#endif
		break;
	}
	if (status < 0)
		goto WarnInit;
	SpyLog("OK\n");
#ifdef TECHNO
	printf("OK\n");
#endif
#else
	//Load FLEX 1
	SpyLog("Try to prog dimm control flex...");
#ifdef TECHNO
	printf("Try to prog dimm control flex...");
#endif
	if (GetFileInfo (DimmRbfFile, &fsize) != 1)
		goto WarnInit;
	fhandle = OpenFile (DimmRbfFile, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_BINARY);
	if (fhandle <= 0)
		goto WarnInit;
	filebuff = malloc(fsize);
	if (ReadFile (fhandle, filebuff, fsize) != fsize)
		goto WarnInit;
	CloseFile(fhandle);
	status = progFlex1(vi, filebuff, fsize, firstFlexLoad);
	free(filebuff);
	if (status < 0)
		goto WarnInit;
	SpyLog("OK\n");
#ifdef TECHNO
	printf("OK\n");
#endif
#endif
WarnInit:
	return status;
}

static ViStatus LoadMezFlex(ViSession vi, void* userdata, int firstFlexLoad)
{
	PUserData globals = userdata;
	ViStatus status = 0;
#ifdef EXTERNAL_RBF
	int fhandle, fsize;
	ViUInt8 *filebuff;
#endif
#ifndef EXTERNAL_RBF

	//Load FLEX 2
	SpyLog("Try to prog mez control flex...");
#ifdef TECHNO
	printf("Try to prog mez control flex...");
#endif
	if (globals->basetype != UNMBASE_TYPE_1)
		status = progFlex2(vi, mez_control2, mez_control2_size, firstFlexLoad);
	else
		status = progFlex2(vi, mez_control, mez_control_size, firstFlexLoad);
	if (status < 0)
		goto WarnInit;
	SpyLog("OK\n");
#ifdef TECHNO
	printf("OK\n");
#endif
#else
	//Load FLEX 2
	SpyLog("Try to prog mez control flex...");
#ifdef TECHNO
	printf("Try to prog mez control flex...");
#endif
	if (GetFileInfo (MezRbfFile, &fsize) != 1)
		goto WarnInit;
	fhandle = OpenFile (MezRbfFile, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_BINARY);
	if (fhandle <= 0)
		goto WarnInit;
	filebuff = malloc(fsize);
	if (ReadFile (fhandle, filebuff, fsize) != fsize)
		goto WarnInit;
	CloseFile(fhandle);
	status = progFlex2(vi, filebuff, fsize, firstFlexLoad);
	free(filebuff);
	if (status < 0)
		goto WarnInit;
	SpyLog("OK\n");
#ifdef TECHNO
	printf("OK\n");
#endif
#endif

WarnInit:
	return status;
}

/*--------------------------------------------------------------------------*/
/* Initialisation                                                           */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_init (ViRsrc rsrcName,
		ViBoolean id_query,
		ViBoolean reset,
		ViSession *vi)
{
	ViSession defaultRM = 0;
	PUserData globals = 0;
	ViStatus status = 0;
	ViInt32 i, j, firstFlexLoad=1;
	ViInt32 firstProcess;
	ViUInt16 w16, intftype, mf_la, slot;
	ViChar serial[32];
	ViChar address[256];
	ViInt32 repeat_mez = 10;
	static const ViChar MezaBoxIdn[] = UNMBASE_MEZABOX_IDN;

#ifdef UNMBASE_DEBUG_CVI
	SetBreakOnProtectionErrors (0);
	SetBreakOnLibraryErrors (0);
	SetBreakOnFirstChanceExceptions (0);
#endif
#ifdef USE_UNSPY
	//////////////Load unSpy.dll
	if (!HMod)
	{
		HMod = cross_load_dll(unspy_name);
		if (HMod)
		{
			unFSpyLog = (PunFSpyLog)cross_get_dll_sym(HMod, "unFSpyLog");
			unFRSpyLog = (PunFRSpyLog)cross_get_dll_sym(HMod, "unFRSpyLog");
			unSpyReason = (PunSpyReason)cross_get_dll_sym(HMod, "unSpyReason");
		}
	}
#endif
	SpyLog("unmbase_init");
	///////////////////////////

	*vi = VI_NULL;

	/*- Проверка входных параметров -----------------------------------------*/
	if (invalidViBooleanRange (id_query))
	{
		errChk(VI_ERROR_PARAMETER2);
	}
	if (invalidViBooleanRange (reset))
	{
		errChk(VI_ERROR_PARAMETER3);
	}
	SpyLog("Try to open instrument...");
#ifdef TECHNO
	printf("Try to open instrument...");
#endif

	/* Открытие сеанса Resource Manager */
	errChk( viOpenDefaultRM (&defaultRM));

	/* Открытие устройства */
	errChk( viOpen (defaultRM, rsrcName, VI_NULL, VI_NULL, vi));

	/* Резервируем память для переменных сеанса устройства */
	if ((globals = (PUserData) calloc (1, sizeof (UserData))) == NULL)
	{
		errChk (VI_ERROR_ALLOC);
	}
	//Сразу запоминаем VI для нормальной отработки ErrLed
	globals->vi = *vi;

	// Сохраняем указатель на переменные сеанса
	errChk( viSetAttribute (*vi, VI_ATTR_USER_DATA, (ViAttrState) globals));

	for (i=0; i<MAX_MEZ; i++)
		globals->m_vi_idx[i] = -1;  //unlock all mvi
	globals->maxMez = MAX_MEZ;		//по умолчанию, потом при необходимости корректируем


//	if (id_query == VI_TRUE)	мы всегда проверяем, т.к. поддерживаем несколько типов
//Вот здесь надо СРАЗУ посмотреть - а может это USB или TCPIP???
	viGetAttribute(*vi, VI_ATTR_INTF_TYPE, &intftype);
	switch (intftype)
	{
	case VI_INTF_TCPIP:
	case VI_INTF_USB:
		//==> MB
		globals->basetype = UNMBASE_TYPE_MB;	//он же UNMBASE_TYPE_MEZABOX
		viSetBuf(*vi, VI_READ_BUF, (65536*4));	//делаем громадный буфер чтения 256К
		viSetBuf(*vi, VI_WRITE_BUF, 65536);		//и большой буфер записи 64К
		viClear(*vi);
		errChk(viQueryf(*vi, "*IDN?\n", "%t", address));
		if (0 != strncmp(address, MezaBoxIdn, (sizeof(MezaBoxIdn)-1)))
		{
			errChk (VI_ERROR_FAIL_ID_QUERY);
		}
		//------------------------
		for (i=0; i<31; i++)
		{
			serial[i] = address[i + sizeof(MezaBoxIdn)];
			if ((serial[i] == ',') ||
				(serial[i] == 0))
				break;
		}
		serial[i] = 0;
		if (',' == address[i + sizeof(MezaBoxIdn)])
		{
			for (i++, j=0; i<64; i++, j++)
			{
				globals->fw_rev[j] = address[i + sizeof(MezaBoxIdn)];
				if ((globals->fw_rev[j] == ',') ||
					(globals->fw_rev[j] == 0))
					break;
			}
			globals->fw_rev[j] = 0;
			
			if (globals->fw_rev[0] < '3')		//2.xx MezaBOX
				globals->maxMez = 2;
			else
			if (globals->fw_rev[0] == '3')		//3.xx MezaBOX-4M (PPC)
			{
				globals->basetype = UNMBASE_TYPE_MEZABOX4M;
				globals->baseBE = 1;
			}
			else
			if (globals->fw_rev[0] == '4')		//4.xx MBaseAXIe
			{
				globals->basetype = UNMBASE_TYPE_AXIe0;
				globals->baseAXIe = 1;
			}
			else
			if (globals->fw_rev[0] == '5')		//5.xx MBaseAXIeLS
			{
				globals->basetype = UNMBASE_TYPE_AXIeLS;
				globals->baseAXIe = 1;
			}
			else
			if (globals->fw_rev[0] == '6')		//6.xx MBaseAXIeU
			{
				globals->basetype = UNMBASE_TYPE_AXIeU;
				globals->baseAXIe = 1;
				globals->basesimple = 1;
			}
			else
			if (globals->fw_rev[0] == '7')		//7.xx MezaBOX-4
			{
				globals->basetype = UNMBASE_TYPE_MEZABOX4;
			}
			if (globals->baseAXIe)
			{
				char *cptr;
				
				*address = 0;
				errChk(viQueryf(*vi, "CONF:ADDRID?;*ERR?\n", "%256t", address));
				cptr = strchr(address, ';');
				if (cptr && '0' == cptr[1] && isdigit(*address))
				{
					globals->slot = atoi(address);;
					if (0x3F == globals->slot)
						globals->slot = 0;
				}
			}
		}
		else
			strcpy(globals->fw_rev, "n/a");
		if (VI_INTF_TCPIP == intftype)
		{
			char *cptr = globals->id_msg;
			viGetAttribute (*vi, VI_ATTR_TCPIP_ADDR, address);
			if (UNMBASE_TYPE_AXIe0 == globals->basetype)
			{
#ifdef ENGLISH
				cptr += sprintf(cptr,
						"MBase AXIe, LXI ");
				if (globals->slot)
					cptr += sprintf(cptr,
							"s.%d ",
							globals->slot);
				cptr += sprintf(cptr,
						"(%s, #:%s)",
						address,
						serial);
#else
				cptr += sprintf(cptr,
						"НМ AXIe, LXI ");
				if (globals->slot)
					cptr += sprintf(cptr,
							"s.%d ",
							globals->slot);
				cptr += sprintf(cptr,
						"(%c, #:%s)",
						address,
						serial);
#endif
			}
			else
			if (UNMBASE_TYPE_AXIeLS == globals->basetype)
			{
#ifdef ENGLISH
				cptr += sprintf(cptr,
						"MBase LS AXIe, LXI ");
				if (globals->slot)
					cptr += sprintf(cptr,
							"s.%d ",
							globals->slot);
				cptr += sprintf(cptr,
						"(%s, #:%s)",
						address,
						serial);
#else
				cptr += sprintf(cptr,
						"НМ НС AXIe, LXI ");
				if (globals->slot)
					cptr += sprintf(cptr,
							"s.%d ",
							globals->slot);
				cptr += sprintf(cptr,
						"(%s, #:%s)",
						address,
						serial);
#endif
			}
			else
			if (UNMBASE_TYPE_AXIeU == globals->basetype)
			{
#ifdef ENGLISH
				cptr += sprintf(cptr,
						"MBase U AXIe, LXI ");
				if (globals->slot)
					cptr += sprintf(cptr,
							"s.%d ",
							globals->slot);
				cptr += sprintf(cptr,
						"(%s, #:%s)",
						address,
						serial);
#else
				cptr += sprintf(cptr,
						"НМУ AXIe, LXI ");
				if (globals->slot)
					cptr += sprintf(cptr,
							"s.%d ",
							globals->slot);
				cptr += sprintf(cptr,
						"(%s, #:%s)",
						address,
						serial);
#endif
			}
			else
			if (UNMBASE_TYPE_MEZABOX4 == globals->basetype)
			{
				sprintf(globals->id_msg,
#ifdef ENGLISH
						"MezaBOX-4, LXI (%s, #:%s)",
#else
						"MezaBOX-4, LXI (%s, №:%s)",
#endif
						address,
						serial);
			}
			else
			if (UNMBASE_TYPE_MEZABOX4M == globals->basetype)
			{
				sprintf(globals->id_msg,
#ifdef ENGLISH
						"MezaBOX-4M, LXI (%s, #:%s)",
#else
						"MezaBOX-4M, LXI (%s, №:%s)",
#endif
						address,
						serial);
			}
			else
			{
				sprintf(globals->id_msg,
#ifdef ENGLISH
						"MezaBOX, LXI (%s, #:%s)",
#else
						"MezaBOX, LXI (%s, №:%s)",
#endif
						address,
						serial);
			}
		}
		else
		{
			if (UNMBASE_TYPE_MEZABOX4 == globals->basetype)
			{
				sprintf(globals->id_msg,
#ifdef ENGLISH
						"MezaBOX-4, LXI (%s, #:%s)",
#else
						"MezaBOX-4, LXI (%s, №:%s)",
#endif
						address,
						serial);
			}
			else
			if (UNMBASE_TYPE_MEZABOX4M == globals->basetype)
			{
				sprintf(globals->id_msg,
#ifdef ENGLISH
						"MezaBOX-4M, LXI (%s, #:%s)",
#else
						"MezaBOX-4M, LXI (%s, №:%s)",
#endif
						address,
						serial);
			}
			else
			{
				sprintf(globals->id_msg,
#ifdef ENGLISH
						"MezaBOX, USB (#:%s)",
#else
						"MezaBOX, USB (№:%s)",
#endif
						serial);
			}
		}
		/* не надо, async мезонины сделают это сами if (reset)
		{
			//пустое чтение для странных мезонинов
			viPrintf(*vi, "MSTART1 I;MSTART2 I\n");
			Sleep(10);
			viPrintf(*vi, "MRST1 I;MRST2 I\n");
		}*/
		//------------------------
		break;

	case VI_INTF_VXI:
	case VI_INTF_GPIB_VXI:
		errChk( viGetAttribute (*vi, VI_ATTR_MANF_ID, (ViPAttrState) &w16));

		if ((w16 & 0x0FFF) != UN_MANUFACTURER_ID)
		{
			errChk (VI_ERROR_FAIL_ID_QUERY);
		}
		errChk( viGetAttribute (*vi, VI_ATTR_MAINFRAME_LA, (ViPAttrState) &mf_la));
		errChk( viGetAttribute (*vi, VI_ATTR_SLOT, (ViPAttrState) &slot));

		// Запрос типа устройства
		errChk( viGetAttribute (*vi, VI_ATTR_VXI_DEV_CLASS, (ViPAttrState) &w16));
		if (VI_VXI_CLASS_MESSAGE == w16)
		{
			viSetBuf(*vi, VI_READ_BUF, (65536*4));	//делаем громадный буфер чтения 256К
			viSetBuf(*vi, VI_WRITE_BUF, 65536);		//и большой буфер записи 64К
			//для MessageBased VXI доделаем тогда, когда будет такого типа модуль
			globals->basetype = UNMBASE_TYPE_MB;
			strcpy(globals->fw_rev, "1.0MB");
		}
		else
		{
			errChk( viGetAttribute (*vi, VI_ATTR_MODEL_CODE, (ViPAttrState) &w16));

			if (w16 == UNMBASE_MODEL_CODE)
			{
				globals->basetype = UNMBASE_TYPE_1;
				//strcpy(globals->fw_rev, "1.0");	//далее уточним...
			}
			else
			if (w16 == UNMBASEU_MODEL_CODE)
			{
				globals->basetype = UNMBASE_TYPE_U;
				globals->basesimple = 1;
				strcpy(globals->fw_rev, "1.0-U");
			}
			else
			if (w16 == UNMBASE_MODEL_ARMVXI)
			{	//==> ARM
				VXI_CMD vxiCmd;
				VXI_ANSW vxiAnsw;

				//поскольку используем здесь команды, сразу инициализируем блокировки
				globals->basetype = UNMBASE_TYPE_ARM;
				globals->init_status = 0;

				sprintf(globals->id_msg,
#ifdef ENGLISH
					"MBase-ARM.  mainframe LA:0x%02X, slot:%d",
#else
					"НММ  Л.А.крейта:0x%02X, слот:%d",
#endif
					mf_la,
					slot);

				sprintf(address, "%s-%s", globals->id_msg, "ARM1");
				unmbase_util_mutex_open(address, &globals->ARM_busy_mutex[0]);

				sprintf(address, "%s-%s", globals->id_msg, "ARM2");
				unmbase_util_mutex_open(address, &globals->ARM_busy_mutex[1]);
				//Set BLOCK move mode
				viSetAttribute (*vi, VI_ATTR_SRC_ACCESS_PRIV, VI_BLCK_PRIV);
				viSetAttribute (*vi, VI_ATTR_DEST_ACCESS_PRIV, VI_BLCK_PRIV);

				armvxi_cmd_clear(globals, 0);
				armvxi_cmd_clear(globals, 1);
				//читаем текущие индексы массива прерываний АРМ
				//чтобы в дальнейшем соответствовать
				errChk(ArmVxiInRAM(*vi, 0,
								ARMVXI_IRQ_IDX,
								&globals->ArmVxiIrqIdx[0]));
				if (globals->ArmVxiIrqIdx[0] >= ARMVXI_IRQ_BUFF_NWORDS)
					globals->ArmVxiIrqIdx[0] = 0;

				errChk(ArmVxiInRAM(*vi, 1,
								ARMVXI_IRQ_IDX,
								&globals->ArmVxiIrqIdx[1]));
				if (globals->ArmVxiIrqIdx[1] >= ARMVXI_IRQ_BUFF_NWORDS)
					globals->ArmVxiIrqIdx[1] = 0;

				cross_delay(0.005);

				//версию запрашиваем только у одного АРМ !!!
				vxiCmd.cmd = ARMCMD_REVISIONq;

				errChk(armvxi_arm_cmd( globals,
									ARMVXI_LOCKUNLOCK,
									ARMVXI_TMO1,
									0,
									&vxiCmd, &vxiAnsw));

				sprintf(globals->fw_rev, "%u.%02u ARM", vxiAnsw.data0, vxiAnsw.data1);

				goto LastStep;
			}
			else
				errChk (VI_ERROR_FAIL_ID_QUERY);
		}
		//------------------------
		switch (globals->basetype)
		{
		case UNMBASE_TYPE_U:
			sprintf(globals->id_msg,
#ifdef ENGLISH
				"MBase-U.  mainframe LA:0x%02X, slot:%d",
#else
				"НМУ  Л.А.крейта:0x%02X, слот:%d",
#endif
				mf_la,
				slot);
			break;

		default:
			sprintf(globals->id_msg,
#ifdef ENGLISH
				"MBase.  mainframe LA:0x%02X, slot:%d",
#else
				"НМ  Л.А.крейта:0x%02X, слот:%d",
#endif
				mf_la,
				slot);
			break;
		}
		//------------------------
		break;
	}	//endof switch (intftype)

	/* Инициализируем переменные сеанса */
	//errChk( viGetAttribute (*vi, VI_ATTR_VXI_LA, (ViPAttrState) &globals->la));
	//errChk( viGetAttribute (*vi, VI_ATTR_MAINFRAME_LA, (ViPAttrState) &globals->mf_la));
	//errChk( viGetAttribute (*vi, VI_ATTR_SLOT, (ViPAttrState) &globals->slot));
	SpyLog("OK\n");
#ifdef TECHNO
	printf("OK\n");
#endif

	//проверка, что уже открыт такой инструмент
	viGetAttribute (*vi, VI_ATTR_RSRC_NAME, address);
	sprintf(address, "%s_UnmbaseOpenMutex", rsrcName);
	for (i=0; address[i]; i++)
	{
		if (!isalnum(address[i]))
			address[i] = '_';
	}
#ifdef __UN_WINDOWS__
	globals->hOpenMutex = CreateMutex(NULL, TRUE, address);
	if (!globals->hOpenMutex ||
		GetLastError() != ERROR_ALREADY_EXISTS)
	{
		firstProcess = 1;
	}
	else
	{
		firstProcess = 0;
	}
#else
	firstProcess = 1;	//HOW IN LINUX TODO THIS?!
#endif // __UN_WINDOWS__

	if (UNMBASE_FLAG_MB & globals->basetype)	//НМ MessageBased ничего из дальнейшего не может...
	{	//==> MB
		globals->init_status = 0;

		sprintf(address, "%s-%s", globals->id_msg, "MB");
		unmbase_util_mutex_open(address, &globals->MB_busy_mutex);
		goto LastStep;
	}

//soft reset
	if (firstProcess || reset)
	{
		errChk( viIn16(*vi, VI_A16_SPACE, rgS, &w16));
		w16 |= maskC_reset;
		errChk( viOut16(*vi, VI_A16_SPACE, rgC, w16));
		cross_delay(0.001);
		w16 &= ~maskC_reset;
		errChk( viOut16(*vi, VI_A16_SPACE, rgC, w16));
	}
	sprintf(address, "%s-%s", globals->id_msg, "RGCOMM1");
	unmbase_util_mutex_open(address, &globals->RgComm1_busy_mutex);

	sprintf(address, "%s-%s", globals->id_msg, "RGCOMM2");
	unmbase_util_mutex_open(address, &globals->RgComm2_busy_mutex);

//Check revision
	if (globals->basesimple)  	//НМУ ничего из дальнейшего не может...
	{
		if (firstProcess || reset)
		{
			errChk( viOut16(*vi, VI_A16_SPACE, rgCONF3, rgCONF3_DEFAULT));
			errChk( viOut16(*vi, VI_A16_SPACE, rgCOMM3, rgCOMM3_DEFAULT));
			viOut16(*vi, VI_A16_SPACE, rgCOMM3, 0);
		}
		globals->init_status = 0;

		goto LastStep;
	}

	sprintf(address, "%s-%s", globals->id_msg, "MEM");
	unmbase_util_mutex_open(address, &globals->Mem_busy_mutex);

	sprintf(address, "%s-%s", globals->id_msg, "LDATA");
	unmbase_util_mutex_open(address, &globals->LastDta_busy_mutex);

	sprintf(address, "%s-%s", globals->id_msg, "STARTSTOP");
	unmbase_util_mutex_open(address, &globals->StartStop_busy_mutex);

	errChk(viIn16 (*vi, VI_A16_SPACE, rgCONF3, &w16));
	errChk(viOut16 (*vi, VI_A16_SPACE, rgCONF3, w16 | maskCONF3_VERSION_MASK));
	errChk(viIn16 (*vi, VI_A16_SPACE, rgCONF3, &w16));
	switch (w16 & maskCONF3_VERSION_MASK)
	{
	case maskCONF3_VERSION_1:
		globals->basetype = UNMBASE_TYPE_1;
		strcpy(globals->fw_rev, "1.0");
		break;
	case maskCONF3_VERSION_2:
		globals->basetype = UNMBASE_TYPE_2;
		strcpy(globals->fw_rev, "2.0");
		break;
	case maskCONF3_VERSION_2A:
		globals->basetype = UNMBASE_TYPE_2A;	//это версия с опорой от CLK10 !!!
		strcpy(globals->fw_rev, "3.0");
		if (firstProcess)
			InitClk10(*vi);
		break;
	default:
		sprintf(globals->fw_rev, "%d.0", globals->basetype);
		break;
	}
	if (firstProcess)
		globals->init_status = UNMBASE_ERROR_FLEX;

	if (firstProcess)
	{
		status = LoadDimmFlex(*vi, globals, firstFlexLoad);
		if (status < 0)
			goto WarnInit;
	}
#ifndef TECHNO
do_repeat_mez:
#endif
	if (firstProcess)
	{
		status = LoadMezFlex(*vi, globals, firstFlexLoad);
		if (status < 0)
			goto WarnInit;
	}
	firstFlexLoad = 0;

/////////////First RESET////////////
	if (firstProcess || reset)
	{
		SpyLog("Try first reset do...");
#ifdef TECHNO
		printf("Try first reset do...");
#endif
		errChk( viOut32(*vi, VI_A24_SPACE, rgCONF1, rgCONF1_DEFAULT));
		errChk( viOut32(*vi, VI_A24_SPACE, rgCONF2, rgCONF2_DEFAULT));
		errChk( viOut16(*vi, VI_A16_SPACE, rgCONF3, rgCONF3_DEFAULT));
		errChk( viOut32(*vi, VI_A24_SPACE, rgMASKCOMM1, 0xFFFFFFFF));
		errChk( viOut32(*vi, VI_A24_SPACE, rgCOMM1, rgCOMM1_DEFAULT));
		errChk( viOut32(*vi, VI_A24_SPACE, rgMASKCOMM2, 0xFFFFFFFF));
		errChk( viOut32(*vi, VI_A24_SPACE, rgCOMM2, rgCOMM2_DEFAULT));
		errChk( viOut32(*vi, VI_A24_SPACE, rgCOMM2A, rgCOMM2A_DEFAULT));
		errChk( viOut16(*vi, VI_A16_SPACE, rgCOMM3, rgCOMM3_DEFAULT));
		viOut16(*vi, VI_A16_SPACE, rgCOMM3, 0);
		errChk( viOut32(*vi, VI_A24_SPACE, rgENDIRQ, rgENDIRQ_DEFAULT));
		SpyLog("OK\n");
#ifdef TECHNO
		printf("OK\n");
#endif

		SpyLog("Try to reset FIFO...");
#ifdef TECHNO
		printf("Try to reset FIFO...");
#endif
		status = ResetFIFO_VXI(*vi, globals);
		if (status == UNMBASE_ERROR_INSTR)
		{
			globals->init_status = status;
			goto WarnInit;
		}
		errChk(status);
	}
	globals->init_status = 0;   //OK FLEX and FIFO VXI
	SpyLog("OK\n");
#ifdef TECHNO
	printf("OK\n");
#endif

	SpyLog("Read spd1...");
#ifdef TECHNO
	printf("Read spd1...");
#endif
	status = unmbase_spd_read(*vi,
							  0,
							  globals->spd1);
	if (status == UNMBASE_ERROR_SPD)
	{
		globals->init_status = status;
		globals->spd1[0] = 0;
	}
	else
		errChk(status);
	if (!globals->spd1[0])
	{
		SpyLog("spd1 not found\n");
#ifdef TECHNO
		printf("spd1 not found\n");
#endif
	}
	else
	{
		SpyLog("OK\n");
#ifdef TECHNO
		printf("OK\n");
#endif
	}

	SpyLog("Read spd2...");
#ifdef TECHNO
	printf("Read spd2...");
#endif
	status = unmbase_spd_read(*vi,
							  1,
							  globals->spd2);
	if (status == UNMBASE_ERROR_SPD)
	{
		globals->spd2[0] = 0;
		if (globals->init_status == status)
			goto WarnInit;       //no one DIMM found
	}
	else
		errChk(status);
	if (!globals->spd2[0])
	{
		SpyLog("spd2 not found\n");
#ifdef TECHNO
		printf("spd2 not found\n");
#endif
	}
	else
	{
		SpyLog("OK\n");
#ifdef TECHNO
		printf("OK\n");
#endif
	}

	globals->init_status = 0;   //OK one ore two SPD

	SpyLog("Check SPD data...");
#ifdef TECHNO
	printf("Check SPD data...");
#endif
	globals->init_status = CheckSPD( globals->spd1[0]?globals->spd1:0, globals->spd2[0]?globals->spd2:0);
	if (globals->init_status)
		goto WarnInit;       //SPD Error
	SpyLog("OK\n");
#ifdef TECHNO
	printf("OK\n");
#endif
	if (firstProcess || reset)
	{
		SpyLog("Try to config RAM...");
#ifdef TECHNO
		printf("Try to config RAM...");
#endif
		errChk( ConfigRAM(*vi, globals->spd1[0] ? globals->spd1 : globals->spd2));  //both RAM must be identical, so config for one of the SPD
		SpyLog("OK\n");
#ifdef TECHNO
		printf("OK\n");
#endif
	}

	if (globals->spd1[0])
		globals->mem_size = GetDIMMsize(globals->spd1);
	if (globals->spd2[0])
		globals->mem_size += GetDIMMsize(globals->spd2);
	globals->alloc_size[0] = globals->mem_size;

	//Set BLOCK move mode
	//viSetAttribute (*vi, VI_ATTR_SRC_ACCESS_PRIV, VI_BLCK_PRIV);  //Not acceptible for MXI2
	//viSetAttribute (*vi, VI_ATTR_DEST_ACCESS_PRIV, VI_BLCK_PRIV);
	if (firstProcess || reset)
	{
#ifndef TECHNO
		if (repeat_mez--)
		{
			ViInt16 result;
			unmbase_self_test(*vi, &result, address);
			if (result)
				goto do_repeat_mez;
			unmbase_self_test(*vi, &result, address);
			if (result)
				goto do_repeat_mez;
		}
#else
		{
			ViInt16 result;
			unmbase_self_test(*vi, &result, address);
		}
#endif
	}
LastStep:
	/* RESET */
	if (reset)
		unmbase_reset (*vi);

	/*устанавливаем обработчик прерывания*/
	if (UNMBASE_FLAG_MB & globals->basetype)  	//НМ MessageBased ничего из дальнейшего не может...
	{	//==> MB
		viClear(*vi);
		errChk( viInstallHandler (*vi, VI_EVENT_SERVICE_REQ, (ViHndlr)unmbase_IntHandler, globals));
		errChk( viEnableEvent (*vi, VI_EVENT_SERVICE_REQ, VI_HNDLR, VI_NULL));
		viPrintf(*vi, "*SRE 32;*ESE 64\n");	//enable User Request
	}
	else
	{
		errChk( viInstallHandler (*vi, VI_EVENT_VXI_VME_INTR, (ViHndlr)unmbase_IntHandler, globals));
		errChk( viEnableEvent (*vi, VI_EVENT_VXI_VME_INTR, VI_HNDLR, VI_NULL));
		if (globals->basetype == UNMBASE_TYPE_ARM)
		{
			//еще раз читаем текущие индексы массива прерываний АРМ
			//чтобы в дальнейшем соответствовать
			errChk(ArmVxiInRAM(*vi, 0,
							ARMVXI_IRQ_IDX,
							&globals->ArmVxiIrqIdx[0]));
			errChk(ArmVxiInRAM(*vi, 1,
							ARMVXI_IRQ_IDX,
							&globals->ArmVxiIrqIdx[1]));
		}
	}
	/*Debug - we can at debug time
		//LOCK Session - We cant work in multisession !!!
		errChk( viLock (*vi, VI_EXCLUSIVE_LOCK, VI_TMO_IMMEDIATE, VI_NULL, VI_NULL));
	*/

	if (status == 0)
	{
		SpyLog("ALL Initialisation OK\n");
#ifdef TECHNO
		printf("ALL Initialisation OK\n");
#endif
	}
	globals->defaultRM = defaultRM;
	return status;

WarnInit:
	globals->defaultRM = defaultRM;
	unmbase_ErrLed(globals, 1);
	return UNMBASE_WARN_INIT;

Error:
	if (*vi)
	{
		viClose(*vi);
		*vi = VI_NULL;
	}
	if (defaultRM)
		viClose(defaultRM);
	if (globals)
	{
		if (globals->hOpenMutex)
			unmbase_util_mutex_close(globals->hOpenMutex);
		if (globals->ARM_busy_mutex[0])
			unmbase_util_mutex_close(globals->ARM_busy_mutex[0]);
		if (globals->ARM_busy_mutex[1])
			unmbase_util_mutex_close(globals->ARM_busy_mutex[1]);
		if (globals->MB_busy_mutex)
			unmbase_util_mutex_close(globals->MB_busy_mutex);
		if (globals->Mem_busy_mutex)
			unmbase_util_mutex_close(globals->Mem_busy_mutex);
		if (globals->LastDta_busy_mutex)
			unmbase_util_mutex_close(globals->LastDta_busy_mutex);
		if (globals->StartStop_busy_mutex)
			unmbase_util_mutex_close(globals->StartStop_busy_mutex);
		if (globals->RgComm1_busy_mutex)
			unmbase_util_mutex_close(globals->RgComm1_busy_mutex);
		if (globals->RgComm2_busy_mutex)
			unmbase_util_mutex_close(globals->RgComm2_busy_mutex);
		free (globals);
	}
	return status;
}

/*--------------------------------------------------------------------------*/
/* Init mezzanine session                                                   */
/*  On mez number Num (if present) open session. Session number is     */
/* index in global array p_mvi + 1, where store session structure pointer   */
/*--------------------------------------------------------------------------*/

static void m_init_at(PUserData globals, ViUInt32 mvi, ViUInt16 midx)
{
	PM_SESSION mglobals = NULL;
	mvi &= MVI_MASK;
	mglobals = &(globals->m_session[midx]);
	p_mvi[mvi] = mglobals;
	memset(mglobals, 0, sizeof(M_SESSION)); //zero fill mglobals
	//store index mvi
	globals->m_vi_idx[midx] = (ViInt16)mvi;
	//store m_session info
	mglobals->pbase_data = globals;

	mglobals->basetype = globals->basetype;
	mglobals->basesimple = globals->basesimple;

	//build attributes
	mglobals->basevi = globals->vi;		//UNMBASE_MATTR_BASE_VI     (RO)
	mglobals->baseBE = globals->baseBE;
	mglobals->baseAXIe = globals->baseAXIe;
	mglobals->mnum = midx+1;
	mglobals->midx = midx;				//UNMBASE_MATTR_NUM         (RO)

	if (!(UNMBASE_FLAG_MB & globals->basetype) &&
		UNMBASE_TYPE_ARM != globals->basetype)
	{	//==> not MB, ARM
		viIn16 (globals->vi, VI_A24_SPACE,
				offsMEZ[midx]+2,
				&mglobals->type);       //UNMBASE_MATTR_TYPE        (RO)
	}
	/*
	All zeroes already settled
		mglobals->membase_in = 0;       //UNMBASE_MATTR_MEMBASE_IN  (RO)
		mglobals->memsize_in = 0;       //UNMBASE_MATTR_MEMSIZE_IN  (RO)
		mglobals->membase_out = 0;  //UNMBASE_MATTR_MEMBASE_OUT (RO)
		mglobals->memsize_out = 0;  //UNMBASE_MATTR_MEMSIZE_OUT (RO)
		mglobals->userdata = 0;     //UNMBASE_MATTR_USER_DATA   (R/W)
		mglobals->loop_base_in = 0;
		mglobals->loop_base_out = 0;
		mglobals->loop_size_in = 0;
		mglobals->loop_size_out = 0;
	*/
	//setup some default values
	mglobals->divisor_out = 0xFFFFFFFF;
	mglobals->first_delay_out = 0xFFFFFFFF;
	mglobals->sample_words_out = 0xFFFFFFFF;
	mglobals->divisor_in = 0xFFFFFFFF;
	mglobals->first_delay_in = 0xFFFFFFFF;
	mglobals->sample_words_in = 0xFFFFFFFF;
	//setup some hardware defaults
	unmbase_m_mode (MVI_ID | mvi, 0, 0);
	unmbase_m_mode (MVI_ID | mvi, 1, 0);
}

_UNMBASE_API ViStatus _VI_FUNC unmbase_m_init (ViSession vi,
		ViUInt16 Num,
		ViSession *mvi)
{
	PUserData globals = 0;
	ViStatus status = VI_SUCCESS;
	ViUInt32 midx = Num-1;

	SpyLog1("unmbase_m_init(m%d)", Num);

	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));
	ChkInitStatus();
	CheckMezNum(globals, Num);
	nullChk(mvi);

	if (globals->m_vi_idx[midx] != -1)
		errChk(VI_ERROR_RSRC_LOCKED);

	//find free msession number
	*mvi=MAX_MVI;
	while (p_mvi[*mvi])
		(*mvi)--;
	if (*mvi == 0)
		errChk(VI_ERROR_ALLOC);

	*mvi = MVI_ID | *mvi;

	m_init_at(globals, *mvi, (ViUInt16)midx);

	SpyLog2("m%d init, session=%08X", Num, *mvi);

Error:
	unmbase_ErrLed(globals, status<0);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Close mezzanine session                                                  */
/*  Free session structure (->m_vi_idx=-1) and session number (p_mvi[m_vi_idx] = 0)  */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_close (ViSession mvi)
{
	PUserData globals = NULL;
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS;
	mviChk(mvi, mglobals);

	SpyLog1("unmbase_m_close(m%d)", mglobals->mnum);

	globals = (PUserData)mglobals->pbase_data;
	if (globals == NULL)
		errChk(VI_ERROR_INV_OBJECT);
	unmbase_ErrLed(globals, 0);

	if (!mglobals->basesimple)
	{
		if ((UNMBASE_FLAG_MB & mglobals->basetype)  ||
			mglobals->basetype == UNMBASE_TYPE_ARM)
		{	//==> MB, ARM
			unmbase_m_stop (mvi, UNMBASE_IOMODE_BOTH);
			unmbase_m_alloc (mvi, 0, 0, 0);     //free up IN RAM
			unmbase_m_alloc (mvi, 1, 0, 0);     //free up OUT RAM
		}
		else
		{
			unmbase_m_stop(mvi, UNMBASE_IOMODE_BOTH);//unmbase_m_stop_out(mglobals);
			//unmbase_m_stop_in(mglobals);
			unmbase_m_alloc (mvi, 0, 0, 0);     //free up IN RAM
			unmbase_m_alloc (mvi, 1, 0, 0);     //free up OUT RAM

			LockOutSTARTSTOP(mglobals, rgLIMIT_IN, 0x00FFFFFF);
			LockOutSTARTSTOP(mglobals, rgSTOP_IN, 0x00FFFFFF);
			LockOutSTARTSTOP(mglobals, rgSTART_IN, 0x00FFFFF0);

			LockOutSTARTSTOP(mglobals, rgLIMIT_OUT, 0x00FFFFFF);
			LockOutSTARTSTOP(mglobals, rgSTOP_OUT, 0x00FFFFFF);
			LockOutSTARTSTOP(mglobals, rgSTART_OUT, 0x00FFFFF0);
		}
	}
	unmbase_ErrLed(globals, 0);		//чтобы случайно не осталась индикация ошибки, если она включилась при закрытии

	//free m_session of this mez on current base
	globals->m_vi_idx[mglobals->midx] = -1;
	memset(mglobals, 0, sizeof(M_SESSION));

	//free pm_session pointer
	p_mvi[MVI_MASK & mvi] = NULL;
Error:
	return status;
}

/*--------------------------------------------------------------------------*/
/* Get Mezzanine Attributes                                                 */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_get_attribute (ViSession mvi,
		ViAttr Attribute_Name,
		void *Attribute_Value)
{
	PUserData globals = NULL;
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS;
	int i = MAX_MVI;
	if (mvi==0)
		errChk(VI_ERROR_INV_OBJECT);

	if (MVI_ID != (MVI_ID_MASK & mvi))  	//это может быть vi носителя?! проверим!
	{
		//ищем этот mvi среди внешних
		while (i)
		{
			if (p_mvi[i]) if (p_mvi[i]->extvi == mvi)
					break;
			i--;
		}
		//если не нашли - это сеанс носителя!
		if (!i)
		{
			errChk( viGetAttribute (mvi, VI_ATTR_USER_DATA, &globals));
			switch (Attribute_Name)
			{
			case UNMBASE_MATTR_BASE_VI:     //(RO)
				*(ViSession*)Attribute_Value = mvi;
				break;
			case UNMBASE_MATTR_BASE_TYPE:   //(R/W)
				if (globals->basesimple)
					*(ViUInt16*)Attribute_Value = UNMBASE_TYPE_U;	//для совместимости
				else
					*(ViUInt16*)Attribute_Value = globals->basetype;
				break;
			case UNMBASE_MATTR_BASE_ID_MSG:
				strcpy((ViChar*)Attribute_Value, globals->id_msg);
				break;

			default:
				errChk(VI_ERROR_NSUP_ATTR);
			}
			return 0;
		}
		mvi = i | MVI_ID;
	}
	//сейчас mvi = это индекс + MVI_ID
	mglobals = p_mvi[MVI_MASK & mvi];
	if (mglobals == NULL)
		errChk(VI_ERROR_INV_OBJECT);

	//сначала те атрибуты, что не зависят от типа носителя
	switch (Attribute_Name)
	{
	case UNMBASE_MATTR_USER_DATA:    //(R/W)
		*(ViAddr*)Attribute_Value = mglobals->userdata;
		return 0;
	//а это глобальный атрибут носителя
	case UNMBASE_MATTR_BASE_ID_MSG:
		errChk( viGetAttribute (mglobals->basevi, VI_ATTR_USER_DATA, &globals));
		strcpy((ViChar*)Attribute_Value, globals->id_msg);
		return 0;
	case UNMBASE_MATTR_BASE_VI:     //(RO)
		*(ViSession*)Attribute_Value = mglobals->basevi;
		return 0;
	case UNMBASE_MATTR_MEZ_EXTVI:     //(RO)
		*(ViSession*)Attribute_Value = mglobals->extvi;
		return 0;
	case UNMBASE_MATTR_NUM:         //(RO)
		*(ViUInt32*)Attribute_Value = mglobals->mnum;
		return 0;
	}
	//если дошли, делаем разделение между типами носителя

	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;

		vxiCmd.cmd = armvxiCmdD16(ARMCMD_MATTRq,
								  Attribute_Name & 0xFF);

		errChk(armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								0,
								&vxiCmd, &vxiAnsw));
		*(ViUInt32*)Attribute_Value = vxiAnsw.data0;
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB

		ViSession vi = mglobals->basevi;
		LockMB(mglobals->pbase_data);
		switch (Attribute_Name)
		{
		case UNMBASE_MATTR_TYPE:        //(RO)
			errChkMB(vi, viQueryf (vi, "MATTR:TYPE%d?\n", "%u", mglobals->mnum, Attribute_Value));
			break;
		case UNMBASE_MATTR_MEMBASE_IN:      //(RO)
			errChkMB(vi, viQueryf (vi, "MATTR:MEMBASE%d? I\n", "%u", mglobals->mnum, Attribute_Value));
			break;
		case UNMBASE_MATTR_MEMSIZE_IN:      //(RO)
			errChkMB(vi, viQueryf (vi, "MATTR:MEMSIZE%d? I\n", "%u", mglobals->mnum, Attribute_Value));
			break;
		case UNMBASE_MATTR_MEMBASE_OUT:     //(RO)
			errChkMB(vi, viQueryf (vi, "MATTR:MEMBASE%d? O\n", "%u", mglobals->mnum, Attribute_Value));
			break;
		case UNMBASE_MATTR_MEMSIZE_OUT:     //(RO)
			errChkMB(vi, viQueryf (vi, "MATTR:MEMSIZE%d? O\n", "%u", mglobals->mnum, Attribute_Value));
			break;
		case UNMBASE_MATTR_DEV_TYPE:   //(R/W)
			errChkMB(vi, viQueryf (vi, "MATTR:DEVTYPE%d?\n", "%u", mglobals->mnum, Attribute_Value));
			break;
		case UNMBASE_MATTR_BASE_TYPE:   //(R/W)
			errChkMB(vi, viQueryf (vi, "MATTR:BASETYPE%d?\n", "%hd", mglobals->mnum, Attribute_Value));
			break;
		case UNMBASE_MATTR_ASYNC:   //(R/W)
			errChkMB(vi, viQueryf (vi, "MATTR:ASYNC%d?\n", "%hd", mglobals->mnum, Attribute_Value));
			break;

		default:
			errChk(VI_ERROR_NSUP_ATTR);
		}
		viFlush (vi, VI_READ_BUF_DISCARD);
	}
	else
	{
		switch (Attribute_Name)
		{
		case UNMBASE_MATTR_TYPE:        //(RO)
			*(ViUInt32*)Attribute_Value = mglobals->type;
			break;
		case UNMBASE_MATTR_MEMBASE_IN:      //(RO)
			*(ViUInt32*)Attribute_Value = mglobals->membase_in;
			break;
		case UNMBASE_MATTR_MEMSIZE_IN:      //(RO)
			*(ViUInt32*)Attribute_Value = mglobals->memsize_in;
			break;
		case UNMBASE_MATTR_MEMBASE_OUT:     //(RO)
			*(ViUInt32*)Attribute_Value = mglobals->membase_out;
			break;
		case UNMBASE_MATTR_MEMSIZE_OUT:     //(RO)
			*(ViUInt32*)Attribute_Value = mglobals->memsize_out;
			break;
		case UNMBASE_MATTR_DEV_TYPE:   //(R/W)
			*(ViUInt32*)Attribute_Value = mglobals->dev_type;
			break;
		case UNMBASE_MATTR_BASE_TYPE:   //(R/W)
			*(ViUInt16*)Attribute_Value = mglobals->basetype;
			break;
		case UNMBASE_MATTR_ASYNC:   //(R/W)
			*(ViBoolean*)Attribute_Value = mglobals->async_type;
			break;
		case UNMBASE_MATTR_LOCK_LASTDATA:
			*(ViBoolean*)Attribute_Value = (mglobals->dontLockLastData == 0);	//not
			break;
		case UNMBASE_MATTR_CHECK_OUT_ERR:
			*(ViBoolean*)Attribute_Value = (mglobals->dontCheckOutErr == 0);	//not
			break;
		default:
			errChk(VI_ERROR_NSUP_ATTR);
		}
	}
Error:
	if (mglobals) UnlockMB(mglobals->pbase_data);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Input D16 word from mezzanine memory                                     */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_in16 (ViSession mvi,
		ViUInt32 Addr,
		ViUInt16 *Data)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS, mbstatus = VI_SUCCESS;
	mviChk(mvi, mglobals);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;

		vxiCmd.cmd = armvxiCmdD16(ARMCMD_MINq, Addr);

		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								0,
								&vxiCmd, &vxiAnsw);

		*Data = (ViUInt16)vxiAnsw.data16;
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viQueryf (mglobals->basevi,
											 "MIN%d? %d;*ERR?\n",
											 "%hu;%d",
											 mglobals->mnum, Addr,
											 Data,
											 &mbstatus));
		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
		errChk(mbstatus);
	}
	else
	{
		unmbase_ErrLed((PUserData)mglobals->pbase_data, 0);
		errChk(viIn16 (mglobals->basevi, VI_A24_SPACE,
					   offsMEZ[mglobals->midx]+Addr,
					   Data));
	}
Error:
	if (mglobals) UnlockMB (mglobals->pbase_data);
//VAV DBG
#ifdef USE_UNSPY
	{
		if (mglobals->spy_inp_addr==Addr && mglobals->spy_inp_data==*Data)
		{
			mglobals->spy_inp_count++;
			return status;
		}
		else
		{
			if (mglobals->spy_inp_count)
			{
				if (mglobals->spy_inp_addr == Addr)
					SpyLog4("unmbase_m_in16(m%d, %04X=%04X) same data %d times, but now:\n",
						mglobals->mnum, mglobals->spy_inp_addr, mglobals->spy_inp_data, mglobals->spy_inp_count);
				else
					SpyLog4("unmbase_m_in16(m%d, %04X=%04X) same data %d times\n",
						mglobals->mnum, mglobals->spy_inp_addr, mglobals->spy_inp_data, mglobals->spy_inp_count);
				mglobals->spy_inp_count = 0;
			}
			mglobals->spy_inp_addr = Addr;
			mglobals->spy_inp_data = *Data;
		}
	}

	SpyLog3("unmbase_m_in16(m%d, %04X=%04X)", mglobals->mnum, Addr, *Data);
#endif
	return status;
}

/*--------------------------------------------------------------------------*/
/* Input block of D16 words from mezzanine memory                           */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_movein16 (ViSession mvi,
		ViUInt32 Addr,
		ViUInt16 *Buff,
		ViInt32 Count,
		ViBoolean Increment)
{
	PM_SESSION mglobals = NULL;
	ViInt32 oldincr;
	ViStatus status = VI_SUCCESS;//, mbstatus = VI_SUCCESS;
	mviChk(mvi, mglobals);
	if (mglobals->spy_inp_count)
	{
		SpyLog4("unmbase_m_in16(m%d, %04X=%04X) same data %d times\n",
			mglobals->mnum, mglobals->spy_inp_addr, mglobals->spy_inp_data, mglobals->spy_inp_count);
		mglobals->spy_inp_count = 0;
		mglobals->spy_inp_addr = 0;
	}
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;

		vxiCmd.cmd = armvxiCmdD16(ARMCMD_MINBUFq,
								  Addr);
		vxiCmd.data0 = Count;
		vxiCmd.data1 = Increment;

		status = armvxi_mez_cmd_readbuf(mglobals, ARMVXI_LOCKUNLOCK,
								0,
								&vxiCmd, VI_NULL,
								Buff,
								Count*sizeof(ViUInt16));
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		ViChar tmpbuff[32];
		ViUInt32 cnt;
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viPrintf (mglobals->basevi,
											 "MINBUF%d? %d,%d,%d\n",
											 mglobals->mnum, Addr, Count, Increment));
		errChkMB(mglobals->basevi, viBufRead (mglobals->basevi, (ViPBuf)tmpbuff, 2, &cnt));
		if ((cnt != 2) || (*tmpbuff != '#'))
			errChk(UNMBASE_ERROR_INSTR);
		errChkMB(mglobals->basevi, viBufRead (mglobals->basevi, (ViPBuf)tmpbuff, tmpbuff[1] - '0', &cnt));
		tmpbuff[cnt] = 0;
		cnt = atoi(tmpbuff);
		errChkMB(mglobals->basevi, viBufRead (mglobals->basevi, (ViPBuf)Buff, cnt, &cnt));
		if (mglobals->baseBE)
			mem_swap32(Buff, cnt);
		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
		okChk(VI_SUCCESS);
	}
	else
	{
		unmbase_ErrLed((PUserData)mglobals->pbase_data, 0);
		errChk(viLock(mglobals->basevi, VI_EXCLUSIVE_LOCK, 10000, NULL, NULL));
		viGetAttribute(mglobals->basevi, VI_ATTR_SRC_INCREMENT, &oldincr);
		viSetAttribute(mglobals->basevi, VI_ATTR_SRC_INCREMENT, Increment);
		status = viMoveIn16 (mglobals->basevi, VI_A24_SPACE,
							 offsMEZ[mglobals->midx]+Addr,
							 Count, Buff);
		viSetAttribute(mglobals->basevi, VI_ATTR_SRC_INCREMENT, oldincr);
		viUnlock(mglobals->basevi);
	}
Error:
	if (mglobals) UnlockMB (mglobals->pbase_data);
//VAV DBG
	SpyLog4("unmbase_m_movein16(m%d, %04X[%d]=%04X...)", mglobals->mnum, Addr, Count, *Buff);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Output D16 word to mezzanine memory                                      */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_out16 (ViSession mvi,
		ViUInt32 Addr,
		ViUInt16 Data)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS, mbstatus = VI_SUCCESS;
	mviChk(mvi, mglobals);
	if (mglobals->spy_inp_count)
	{
		SpyLog4("unmbase_m_in16(m%d, %04X=%04X) same data %d times\n",
			mglobals->mnum, mglobals->spy_inp_addr, mglobals->spy_inp_data, mglobals->spy_inp_count);
		mglobals->spy_inp_count = 0;
		mglobals->spy_inp_addr = 0;
	}
	SpyLog3("unmbase_m_out16(m%d, %04X=%04X)", mglobals->mnum, Addr, Data);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;

		vxiCmd.cmd = armvxiCmdD16(ARMCMD_MOUT,
								  Addr);
		vxiCmd.data0 = Data;

		return armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								0,
								&vxiCmd, VI_NULL);
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		if (mglobals->dontCheckOutErr)
		{	//POKE стиль, без проверки ошибок
			errChkMB(mglobals->basevi, viPrintf (mglobals->basevi,
											 "MOUT%d %d,%d\n",
											 "%d",
											 mglobals->mnum, Addr, Data));
		}
		else
		{
			errChkMB(mglobals->basevi, viQueryf (mglobals->basevi,
											 "MOUT%d %d,%d;*ERR?\n",
											 "%d",
											 mglobals->mnum, Addr, Data,
											 &mbstatus));
		}
		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
		errChk(mbstatus);
	}
	else
	{
		unmbase_ErrLed((PUserData)mglobals->pbase_data, 0);
		errChk (viOut16 (mglobals->basevi, VI_A24_SPACE,
						 offsMEZ[mglobals->midx]+Addr,
						 Data));
	}
Error:
	if (mglobals) UnlockMB (mglobals->pbase_data);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Output block of D16 words to mezzanine memory                            */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_moveout16 (ViSession mvi,
		ViUInt32 Addr,
		ViUInt16 *Buff,
		ViInt32 Count,
		ViBoolean Increment)
{
	PM_SESSION mglobals = NULL;
	ViInt32 oldincr;
	ViStatus status = VI_SUCCESS;//, mbstatus = VI_SUCCESS;
	mviChk(mvi, mglobals);
	if (mglobals->spy_inp_count)
	{
		SpyLog4("unmbase_m_in16(m%d, %04X=%04X) same data %d times\n",
			mglobals->mnum, mglobals->spy_inp_addr, mglobals->spy_inp_data, mglobals->spy_inp_count);
		mglobals->spy_inp_count = 0;
		mglobals->spy_inp_addr = 0;
	}
	SpyLog4("unmbase_m_moveout16(m%d, %04X[%d]=%04X...)", mglobals->mnum, Addr, Count, *Buff);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;

		vxiCmd.cmd = armvxiCmdD16(ARMCMD_MOUTBUF,
								  Addr);
		vxiCmd.data0 = Count;
		vxiCmd.data1 = Increment;

		status = armvxi_mez_cmd_writebuf(mglobals, ARMVXI_LOCKUNLOCK,
								0,
								&vxiCmd,
								Buff,
								Count*sizeof(ViUInt16));
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		ViChar tmpbuff[96], *tmpbuffptr;
		ViUInt32 cnt, digits;

		//готовим для передачи выровненныый блок данных 488.2 Arbitrary Length Binary Block
		sprintf(tmpbuff, "%d", Count*sizeof(ViUInt16));	//byte size
		digits = strlen(tmpbuff);
		sprintf(tmpbuff, "MOUTBUF%d %d,%d,%d",
				mglobals->mnum, Addr, Count, Increment);
		Count *= sizeof(ViUInt16);	//to byte size
		cnt = strlen(tmpbuff);
		tmpbuffptr = &tmpbuff[cnt];
		//общее количество передаваемых байт команды до начала данных = digits + cnt + 2 (это "#n")
		cnt += digits+2;
		while (cnt&3)
		{
			*tmpbuffptr++ = ' ';	//выравниваем при помощи пробелов
			cnt++;
		}
		sprintf(tmpbuffptr, "#%d%d",
				digits, Count);

		LockMB(mglobals->pbase_data);

		errChkMB(mglobals->basevi, viBufWrite (mglobals->basevi, (ViPBuf)tmpbuff, cnt, VI_NULL));

		if (mglobals->baseBE)
		{
			void *swapbuf = malloc(Count);
			if (!swapbuf)
				errChk(VI_ERROR_ALLOC);

			memcpy_swap32(swapbuf, Buff, Count);
			status = viBufWrite (mglobals->basevi, (ViPBuf)swapbuf, Count, &cnt);
			free(swapbuf);
			errChkMB(mglobals->basevi, status);
		}
		else
			errChkMB(mglobals->basevi, viBufWrite (mglobals->basevi, (ViPBuf)Buff, Count, &cnt));

		errChkMB(mglobals->basevi, viFlush (mglobals->basevi, VI_WRITE_BUF));
		okChk(VI_SUCCESS);
	}
	else
	{
		unmbase_ErrLed((PUserData)mglobals->pbase_data, 0);
		errChk(viLock(mglobals->basevi, VI_EXCLUSIVE_LOCK, 10000, NULL, NULL));
		viGetAttribute(mglobals->basevi, VI_ATTR_DEST_INCREMENT, &oldincr);
		viSetAttribute(mglobals->basevi, VI_ATTR_DEST_INCREMENT, Increment);
		status = viMoveOut16 (mglobals->basevi, VI_A24_SPACE,
							  offsMEZ[mglobals->midx]+Addr,
							  Count, Buff);
		viSetAttribute(mglobals->basevi, VI_ATTR_DEST_INCREMENT, oldincr);
		viUnlock(mglobals->basevi);
	}
Error:
	if (mglobals) UnlockMB (mglobals->pbase_data);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Input D32 word from mezzanine memory                                     */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_in32 (ViSession mvi,
		ViUInt32 Addr,
		ViUInt32 Addr2,
		ViUInt32 *Data)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS, mbstatus = VI_SUCCESS;
	mviChk(mvi, mglobals);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;

		vxiCmd.cmd = armvxiCmdD16(ARMCMD_MIN32q,
								  Addr);
		vxiCmd.data0 = Addr2;

		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								0,
								&vxiCmd, &vxiAnsw);

		*Data = vxiAnsw.data0;
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viQueryf (mglobals->basevi,
											 "MINDW%d? %d,%d;*ERR?\n",
											 "%u;%d",
											 mglobals->mnum, Addr, Addr2,
											 Data,
											 &mbstatus));
		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
		errChk(mbstatus);
	}
	else
	{
		ViUInt16 d16, d16_2;

		unmbase_ErrLed((PUserData)mglobals->pbase_data, 0);
		errChk(viIn16 (mglobals->basevi, VI_A24_SPACE,
					   offsMEZ[mglobals->midx]+Addr,
					   &d16));
		errChk(viIn16 (mglobals->basevi, VI_A24_SPACE,
					   offsMEZ[mglobals->midx]+Addr2,
					   &d16_2));
		*Data = (ViUInt32)d16 | ((ViUInt32)d16_2 << 16);
	}
Error:
	if (mglobals) UnlockMB (mglobals->pbase_data);
//VAV DBG
	SpyLog3("unmbase_m_in32(m%d, %04X=%08X)", mglobals->mnum, Addr, *Data);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Input block of D32 words from mezzanine memory                           */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_movein32 (ViSession mvi,
		ViUInt32 Addr,
		ViUInt32 Addr2,
		ViUInt32 *Buff,
		ViInt32 Count)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS;//, mbstatus = VI_SUCCESS;
	mviChk(mvi, mglobals);

	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;

		vxiCmd.cmd = armvxiCmdD16(ARMCMD_MINBUF32q,
								  Addr);
		vxiCmd.data0 = Addr2;

		vxiCmd.data1 = Count;

		status = armvxi_mez_cmd_readbuf(mglobals, ARMVXI_LOCKUNLOCK,
								0,
								&vxiCmd, VI_NULL,
								Buff,
								Count*sizeof(ViUInt32));
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		ViChar tmpbuff[32];
		ViUInt32 cnt;
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viPrintf (mglobals->basevi,
											 "MINBUFDW%d? %d,%d,%d\n",
											 mglobals->mnum, Addr, Addr2, Count));
		errChkMB(mglobals->basevi, viBufRead (mglobals->basevi, (ViPBuf)tmpbuff, 2, &cnt));
		if ((cnt != 2) || (*tmpbuff != '#'))
			errChk(UNMBASE_ERROR_INSTR);
		errChkMB(mglobals->basevi, viBufRead (mglobals->basevi, (ViPBuf)tmpbuff, tmpbuff[1] - '0', &cnt));
		tmpbuff[cnt] = 0;
		cnt = atoi(tmpbuff);
		errChkMB(mglobals->basevi, viBufRead (mglobals->basevi, (ViPBuf)Buff, cnt, &cnt));
		if (mglobals->baseBE)
			mem_swap32(Buff, cnt);
		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
		okChk(VI_SUCCESS);
	}
	else
	{
		ViUInt16 d16, d16_2;
		ViUInt32 cnt = Count;
		ViUInt32 *buf = Buff;

		unmbase_ErrLed((PUserData)mglobals->pbase_data, 0);
		while (cnt)
		{
			errChk(viIn16 (mglobals->basevi, VI_A24_SPACE,
						   offsMEZ[mglobals->midx]+Addr,
						   &d16));
			errChk(viIn16 (mglobals->basevi, VI_A24_SPACE,
						   offsMEZ[mglobals->midx]+Addr2,
						   &d16_2));
			*buf = (ViUInt32)d16 | ((ViUInt32)d16_2 << 16);
			buf++;
			cnt--;
		}
	}
Error:
	if (mglobals) UnlockMB (mglobals->pbase_data);
//VAV DBG
	SpyLog4("unmbase_m_movein32(m%d, %04X[%d]=%08X...)", mglobals->mnum, Addr, Count, *Buff);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Output D32 word to mezzanine memory                                      */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_out32 (ViSession mvi,
		ViUInt32 Addr,
		ViUInt32 Addr2,
		ViUInt32 Data)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS, mbstatus = VI_SUCCESS;
	mviChk(mvi, mglobals);

	SpyLog3("unmbase_m_out32(m%d, %04X=%08X)", mglobals->mnum, Addr, Data);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;

		vxiCmd.cmd = armvxiCmdD16(ARMCMD_MOUT32,
								  Addr);
		vxiCmd.data0 = Addr2;

		vxiCmd.data1 = Data;

		return armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								0,
								&vxiCmd, VI_NULL);
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		if (mglobals->dontCheckOutErr)
		{	//POKE стиль, без проверки ошибок
			errChkMB(mglobals->basevi, viPrintf (mglobals->basevi,
											 "MOUTDW%d %d,%d,%d\n",
											 "%d",
											 mglobals->mnum, Addr, Addr2, Data));
		}
		else
		{
			errChkMB(mglobals->basevi, viQueryf (mglobals->basevi,
											 "MOUTDW%d %d,%d,%d;*ERR?\n",
											 "%d",
											 mglobals->mnum, Addr, Addr2, Data,
											 &mbstatus));
		}
		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
		errChk(mbstatus);
	}
	else
	{
		unmbase_ErrLed((PUserData)mglobals->pbase_data, 0);
		errChk (viOut16 (mglobals->basevi, VI_A24_SPACE,
						 offsMEZ[mglobals->midx]+Addr,
						 Data & 0xFFFF));
		errChk (viOut16 (mglobals->basevi, VI_A24_SPACE,
						 offsMEZ[mglobals->midx]+Addr2,
						 (Data >> 16) & 0xFFFF));
	}
Error:
	if (mglobals) UnlockMB (mglobals->pbase_data);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Output block of D32 words to mezzanine memory                            */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_moveout32 (ViSession mvi,
		ViUInt32 Addr,
		ViUInt32 Addr2,
		ViUInt32 *Buff,
		ViInt32 Count)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS;//, mbstatus = VI_SUCCESS;
	mviChk(mvi, mglobals);

	SpyLog4("unmbase_m_moveout32(m%d, %04X[%d]=%08X...)", mglobals->mnum, Addr, Count, *Buff);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;

		vxiCmd.cmd = armvxiCmdD16(ARMCMD_MOUTBUF32,
								  Addr);
		vxiCmd.data0 = Addr2;

		vxiCmd.data1 = Count;

		status = armvxi_mez_cmd_writebuf(mglobals, ARMVXI_LOCKUNLOCK,
								0,
								&vxiCmd,
								Buff,
								Count*sizeof(ViUInt32));
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		ViChar tmpbuff[96], *tmpbuffptr;
		ViUInt32 cnt, digits;

		//готовим для передачи выровненныый блок данных 488.2 Arbitrary Length Binary Block
		sprintf(tmpbuff, "%d", Count*sizeof(ViUInt32));	//byte size
		digits = strlen(tmpbuff);
		sprintf(tmpbuff, "MOUTBUFDW%d %d,%d,%d",
				mglobals->mnum, Addr, Addr2, Count);
		Count *= sizeof(ViUInt32);	//to byte size
		cnt = strlen(tmpbuff);
		tmpbuffptr = &tmpbuff[cnt];
		//общее количество передаваемых байт команды до начала данных = digits + cnt + 2 (это "#n")
		cnt += digits+2;
		while (cnt&3)
		{
			*tmpbuffptr++ = ' ';	//выравниваем при помощи пробелов
			cnt++;
		}
		sprintf(tmpbuffptr, "#%d%d",
				digits, Count);

		LockMB(mglobals->pbase_data);

		errChkMB(mglobals->basevi, viBufWrite (mglobals->basevi, (ViPBuf)tmpbuff, cnt, VI_NULL));

		if (mglobals->baseBE)
		{
			void *swapbuf = malloc(Count);
			if (!swapbuf)
				errChk(VI_ERROR_ALLOC);

			memcpy_swap32(swapbuf, Buff, Count);
			status = viBufWrite (mglobals->basevi, (ViPBuf)swapbuf, Count, &cnt);
			free(swapbuf);
			errChkMB(mglobals->basevi, status);
		}
		else
			errChkMB(mglobals->basevi, viBufWrite (mglobals->basevi, (ViPBuf)Buff, Count, &cnt));

		errChkMB(mglobals->basevi, viFlush (mglobals->basevi, VI_WRITE_BUF));
		okChk(VI_SUCCESS);
	}
	else
	{
		ViUInt32 cnt = Count;
		ViUInt32 *buf = Buff;

		unmbase_ErrLed((PUserData)mglobals->pbase_data, 0);
		while (cnt)
		{
			errChk (viOut16 (mglobals->basevi, VI_A24_SPACE,
							 offsMEZ[mglobals->midx]+Addr,
							 (*buf) & 0xFFFF));
			errChk (viOut16 (mglobals->basevi, VI_A24_SPACE,
							 offsMEZ[mglobals->midx]+Addr2,
							 ((*buf) >> 16) & 0xFFFF));
			buf++;
			cnt--;
		}
	}
Error:
	if (mglobals) UnlockMB (mglobals->pbase_data);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Input/Output block of D16 words from/to mezzanine memory                 */
/*--------------------------------------------------------------------------*/
//Операции работы со счетчиком и переходы есть в прошивках, но
//используются для отладки. В unmbase.h не определены!
#define UNMBASE_IOREGS_TODO_SET_CNT		0x1500
#define UNMBASE_IOREGS_TODO_MINUS_CNT	0x1600
#define UNMBASE_IOREGS_TODO_GOTO		0x1700

_UNMBASE_API ViStatus _VI_FUNC unmbase_m_ioregs (ViSession mvi,
								ViInt32 Count,
								ViUInt16 *OutBuf,
								ViUInt16 *InBuf)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS;//, mbstatus = VI_SUCCESS;
	ViUInt32 i, N;
	ViUInt16 M = 0;
	ViUInt16 F = 0;
	ViUInt16 C = 0;
	ViUInt16 *tmpInBuf = NULL;
	mviChk(mvi, mglobals);

//#define SPY_M_IOREGS

#ifdef SPY_M_IOREGS
	char spystr[256];
	char *spyptr = spystr;
#define SpyIOregsStart(_1, _2, _3, _4) spyptr = spystr + sprintf(spystr, _1, _2, _3, _4)
#define SpyIOregs(_1, _2) spyptr += sprintf(spyptr, _1, _2)
#define SpyIOregsEnd() do {strcpy(spyptr, "\n"); SpyLog(spystr); spyptr = spystr;} while (0)
#else
#define SpyIOregsStart(_1, _2, _3, _4)
#define SpyIOregs(_1, _2)
#define SpyIOregsEnd()
#endif

	SpyLog4("unmbase_m_ioregs(m%d, [%d]=%04X/%04X...)", mglobals->mnum, Count, OutBuf[0], OutBuf[1]);
	if (!Count)
		return status;

	//чтобы не делать циклы внутри, ограничим общее количество в 256 (1024 байт)
	//это ограничение распространяется на прошивки,
	//поэтому нельзя делать GOTO в командных буферах больше 256 операций!
	do
	{
		if (Count <= 256)
		{
			N = Count;
			Count = 0;
		}
		else
		{
			N = 256;
			Count -= 256;
		}

		if (mglobals->basetype == UNMBASE_TYPE_ARM)
		{	//==> ARM
			VXI_CMD vxiCmd;

			vxiCmd.cmd = ARMCMD_MIOREGSq;

			vxiCmd.data0 = N;

			status = armvxi_mez_cmd_writebuf(mglobals, ARMVXI_LOCK,
									0,
									&vxiCmd,
									OutBuf,
									N*sizeof(ViUInt16)*2);
			if (status >= 0 &&
				InBuf)
			{
				status = armvxi_mez_readbuf(mglobals,
								0,
								(ViUInt32*)InBuf,
								N*sizeof(ViUInt16));
			}
			UnlockARM(mglobals->pbase_data, mglobals->midx > 1);
		}
		else
		if (UNMBASE_FLAG_MB & mglobals->basetype)
		{	//==> MB
			ViChar tmpbuff[96], *tmpbuffptr;
			ViUInt32 cnt, digits;

			//готовим для передачи выровненныый блок данных 488.2 Arbitrary Length Binary Block
			sprintf(tmpbuff, "%d", N*sizeof(ViUInt16)*2);	//byte size
			digits = strlen(tmpbuff);
			sprintf(tmpbuff, "MIOREGS%d? %d",
					mglobals->mnum, N);
			N *= sizeof(ViUInt16)*2;	//to byte size
			cnt = strlen(tmpbuff);
			tmpbuffptr = &tmpbuff[cnt];
			//общее количество передаваемых байт команды до начала данных = digits + cnt + 2 (это "#n")
			cnt += digits+2;
			while (cnt&3)
			{
				*tmpbuffptr++ = ' ';	//выравниваем при помощи пробелов
				cnt++;
			}
			sprintf(tmpbuffptr, "#%d%d",
					digits, N);

			LockMB(mglobals->pbase_data);

			errChkMB(mglobals->basevi, viBufWrite (mglobals->basevi, (ViPBuf)tmpbuff, cnt, VI_NULL));

			if (mglobals->baseBE)
			{
				void *swapbuf = malloc(N);
				if (!swapbuf)
					errChk(VI_ERROR_ALLOC);

				memcpy_swap32(swapbuf, OutBuf, N);
				status = viBufWrite (mglobals->basevi, (ViPBuf)swapbuf, N, &cnt);
				free(swapbuf);
				errChkMB(mglobals->basevi, status);
			}
			else
				errChkMB(mglobals->basevi, viBufWrite (mglobals->basevi, (ViPBuf)OutBuf, N, &cnt));

			errChkMB(mglobals->basevi, viFlush (mglobals->basevi, VI_WRITE_BUF));


			errChkMB(mglobals->basevi, viBufRead (mglobals->basevi, (ViPBuf)tmpbuff, 2, &cnt));
			if ((cnt != 2) || (*tmpbuff != '#'))
				errChk(UNMBASE_ERROR_INSTR);
			errChkMB(mglobals->basevi, viBufRead (mglobals->basevi, (ViPBuf)tmpbuff, tmpbuff[1] - '0', &cnt));
			tmpbuff[cnt] = 0;
			cnt = atoi(tmpbuff);

			if (cnt > N*sizeof(ViUInt16))
				cnt = N*sizeof(ViUInt16);

			errChkMB(mglobals->basevi, viBufRead (mglobals->basevi, (ViPBuf)InBuf, cnt, &cnt));
			if (mglobals->baseBE)
				mem_swap32(InBuf, cnt);

			viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
			UnlockMB (mglobals->pbase_data);
			if (status > 0)
				status = 0;
		}
		else
		{
#define UNMBASE_IOREGS_TODO_READ_FROM	UNMBASE_IOREGS_TODO_READ
#define UNMBASE_IOREGS_TODO_READ_TO		UNMBASE_IOREGS_TODO_R_XOR_W
#define UNMBASE_IOREGS_TODO_WRITE_FROM	UNMBASE_IOREGS_TODO_R_AND_W
#define UNMBASE_IOREGS_TODO_WRITE_TO	UNMBASE_IOREGS_TODO_WRITE

			if (!tmpInBuf)
			{
				tmpInBuf = malloc(N * sizeof(ViUInt16));
				if (!tmpInBuf)
					errChk(VI_ERROR_ALLOC);
			}
			unmbase_ErrLed((PUserData)mglobals->pbase_data, 0);

			for (i=0; i<N; i++)
			{
				ViUInt16 todo = OutBuf[i*2+0] & UNMBASE_IOREGS_TODO_MASK;
				ViUInt16 addr = OutBuf[i*2+0] & UNMBASE_IOREGS_ADDR_MASK;
				ViUInt16 data = OutBuf[i*2+1];
				ViUInt16 rdata;


				if ((OutBuf[i*2+0] & UNMBASE_IOREGS_IF_0 && F != 0) ||
					(OutBuf[i*2+0] & UNMBASE_IOREGS_IF_1 && F == 0))
				{	//condition FALSE, skip
					data = 0;
					todo = 0xFFFF;//SKIP FLAG
				}
SpyIOregsStart("IOR %04X(A=%02X,D=%04X):", todo, addr, data);
				if (todo <= UNMBASE_IOREGS_TODO_READ_TO)
				{	//have any read
					errChk (viIn16 (mglobals->basevi, VI_A24_SPACE,
									 offsMEZ[mglobals->midx]+addr,
									 &rdata));
SpyIOregs(" rd %04X", rdata);
				}
				//result already in data!
				switch (todo)
				{
				case UNMBASE_IOREGS_TODO_READ:
					data = rdata;
					break;

				//read, modify, write
				case UNMBASE_IOREGS_TODO_R_AND_W:
SpyIOregs(" & %04X", data);
					data = rdata & data;
					break;

				case UNMBASE_IOREGS_TODO_R_OR_W:
SpyIOregs(" | %04X", data);
					data = rdata | data;
					break;

				case UNMBASE_IOREGS_TODO_R_XOR_W:
SpyIOregs(" ^ %04X", data);
					data = rdata ^ data;
					break;

				//read, modify, set M
				case UNMBASE_IOREGS_TODO_R_AND_M:
SpyIOregs(" & %04X", data);
					data = M = rdata & data;
					break;

				case UNMBASE_IOREGS_TODO_R_OR_M:
SpyIOregs(" | %04X", data);
					data = M = rdata | data;
					break;

				case UNMBASE_IOREGS_TODO_R_XOR_M:
SpyIOregs(" ^ %04X", data);
					data = M = rdata ^ data;
					break;

				//get M, modify, write
				case UNMBASE_IOREGS_TODO_M_AND_W:
SpyIOregs(" & %04X", data);
					data = M & data;
					break;

				case UNMBASE_IOREGS_TODO_M_OR_W:
SpyIOregs(" | %04X", data);
					data = M | data;
					break;

				case UNMBASE_IOREGS_TODO_M_XOR_W:
SpyIOregs(" ^ %04X", data);
					data = M ^ data;
					break;

				//modify M
				case UNMBASE_IOREGS_TODO_M_PLUS:
SpyIOregs(" + %04X", data);
					M += data;
					data = M;
					break;

				case UNMBASE_IOREGS_TODO_M_MINUS:
SpyIOregs(" - %04X", data);
					M -= data;
					data = M;
					break;

				case UNMBASE_IOREGS_TODO_M_AND:
SpyIOregs(" & %04X", data);
					M &= data;
					data = M;
					break;

				case UNMBASE_IOREGS_TODO_M_OR:
SpyIOregs(" | %04X", data);
					M |= data;
					data = M;
					break;

				case UNMBASE_IOREGS_TODO_M_XOR:
SpyIOregs(" ^ %04X", data);
					M ^= data;
					data = M;
					break;

				case UNMBASE_IOREGS_TODO_M_LSL:
SpyIOregs(" << %04X", data);
					M = M << data;
					data = M;
					break;

				case UNMBASE_IOREGS_TODO_M_LSR:
SpyIOregs(" >> %04X", data);
					M = M >> data;
					data = M;
					break;

				case UNMBASE_IOREGS_TODO_M_AND_F:
SpyIOregs(" F & %04X", data);
					data = M & data;
					break;

				//wait for 0/1
				case UNMBASE_IOREGS_TODO_R_WAIT0:
SpyIOregs(" wait 0 &%04X", data);
					if (0 != (rdata & data))
					{
						ViReal64 t0 = cross_timer();
						while ((cross_timer()-t0) < 0.020)	//не более 20 мс
						{
							errChk (viIn16 (mglobals->basevi, VI_A24_SPACE,
											 offsMEZ[mglobals->midx]+addr,
											 &rdata));
							if (0 == (rdata & data))
								break;
						}
						errChk (VI_ERROR_TMO);
					}
					data = rdata;
					break;

				case UNMBASE_IOREGS_TODO_R_WAIT1:
SpyIOregs(" wait 1 &%04X", data);
					if (0 == (rdata & data))
					{
						ViReal64 t0 = cross_timer();
						while ((cross_timer()-t0) < 0.020)	//не более 20 мс
						{
							errChk (viIn16 (mglobals->basevi, VI_A24_SPACE,
											 offsMEZ[mglobals->midx]+addr,
											 &rdata));
							if (0 != (rdata & data))
								break;
						}
						errChk (VI_ERROR_TMO);
					}
					data = rdata;
					break;

				case UNMBASE_IOREGS_TODO_SET_CNT:
SpyIOregs(" set cnt %d", data);
					C = data;
					break;

				case UNMBASE_IOREGS_TODO_MINUS_CNT:
SpyIOregs(" cnt %d-%d", data);
					C -= data;
					data = C;
					break;

				case UNMBASE_IOREGS_TODO_GOTO:
SpyIOregs(" goto %d", data);
					// 0: next, -1: loop forever
					tmpInBuf[i] = data;
					if (0x8000 & data)
						i += 0xFFFF0000 | (ViUInt32)data;
					else
						i += data;
					goto toContinue;

				}	//end switch

				if (todo >= UNMBASE_IOREGS_TODO_WRITE_FROM &&
					todo <= UNMBASE_IOREGS_TODO_WRITE_TO)
				{	//have any write
SpyIOregs(" wr %04X", data);
					errChk (viOut16 (mglobals->basevi, VI_A24_SPACE,
									 offsMEZ[mglobals->midx]+addr,
									 data));
				}
SpyIOregsEnd();

				if (todo != 0xFFFF)		//SKIP FLAG
					F = data;

				tmpInBuf[i] = data;
toContinue:
				;
			}
			OutBuf += N*2;

			memcpy(InBuf, tmpInBuf, N*sizeof(ViUInt16));
			InBuf += N;
		}
	} while (Count);

Error:
	if (tmpInBuf)
		free(tmpInBuf);
	if (status > 0 && mglobals) UnlockMB (mglobals->pbase_data);
	return status;
}

/*--------------------------------------------------------------------------*/
//делаем кратно 256 и ширине кадра
/*--------------------------------------------------------------------------*/
static ViUInt32 checkLsize(ViUInt32 lsize, ViUInt32 sampsize)
{
	ViUInt32 oldlsize=lsize;
	if (sampsize)
	{
		if (lsize % sampsize)
			SpyLog2("Try to correct Lsize, initial lsize=%08X, sampsize=%08X\n", lsize, sampsize);

		while (lsize)
		{
			lsize = lsize - (lsize % sampsize);
			if (lsize & 0xFF)
				lsize--;
			else
				break;
		}
	}
	if (oldlsize != lsize)
		SpyLog2("Correct Lsize from %08X to %08X\n", oldlsize, lsize);
	return lsize;
}

/*--------------------------------------------------------------------------*/
/* Set sample width of mezzanine                                            */
/*--------------------------------------------------------------------------*/
//OK1 - есть некоторые непонятки с кол-вом кадров в режиме СРЕЗ - нафига больше одного делать? Пока только один
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_sample_width (ViSession mvi,
		ViUInt16 io,
		ViUInt32 Width)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS;
	mviChk(mvi, mglobals);
	notNMU(mglobals);
	SpyLog2("unmbase_m_sample_width(m%d sample width=%d)", mglobals->mnum, Width);
	mbusyChk(mvi, mglobals, io);
	if (invalidViUInt16Range(Width, 1, 31)) //
		errChk(VI_ERROR_PARAMETER2);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;

		if (io)	//сохраняем, чтобы потом не запрашивать - оно нам надо для вычисления ко-ва сэмплов
			mglobals->sample_bytes_out = Width*sizeof(ViUInt32);
		else
			mglobals->sample_bytes_in = Width*sizeof(ViUInt32);

		vxiCmd.cmd = armvxiCmdD16(ARMCMD_MSWIDTH,
								  Width);

		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								io,
								&vxiCmd, VI_NULL);
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		if (io)	//сохраняем, чтобы потом не запрашивать - оно нам надо для вычисления ко-ва сэмплов
			mglobals->sample_bytes_out = Width*sizeof(ViUInt32);
		else
			mglobals->sample_bytes_in = Width*sizeof(ViUInt32);
		errChkMB(mglobals->basevi, viPrintf(mglobals->basevi,
											"MSWIDTH%d %c,%d\n",
											mglobals->mnum, IOChar[io], Width));
	}
	else
	{
		if (io)     //OUT
		{
			//store sample width
			mglobals->sample_bytes_out = Width*sizeof(ViUInt32);
			mglobals->sample_words_out = Width; //later used for RgNWORDS
			//setup sample width, NOTE: Now only 1 Nsamples
			errChk( viOut32 (mglobals->basevi, VI_A24_SPACE,
							 rgNWORDS_OUT[mglobals->midx],
							 mglobals->sample_words_out + (1 << shiftNWORDS_B_LENGTH))); //+1 Nsamples
			if (mglobals->memsize_out)
			{
				//переустановим также rgSTOP для выравнивания по новой ширине кадра
				ViUInt32 start, stop, loop_size_out;

				errChk( viIn32 (mglobals->basevi, VI_A24_SPACE,
								rgSTOP_OUT[mglobals->midx],
								&stop));
				errChk( viIn32 (mglobals->basevi, VI_A24_SPACE,
								rgSTART_OUT[mglobals->midx],
								&start));
				loop_size_out = checkLsize((stop-start)<<8, mglobals->sample_bytes_out);
				stop = start + (loop_size_out >> 8);      //for block address

				errChk(LockOutSTARTSTOP(mglobals,
										rgSTOP_OUT,
										stop));
			}
#ifdef DBGPRINT
			printf("NWORDS_OUT = %08X\n", mglobals->sample_words_out + (1 << shiftNWORDS_B_LENGTH));
#endif
		}
		else   //IN
		{
			//store sample width
			mglobals->sample_bytes_in = Width*sizeof(ViUInt32);
			mglobals->sample_words_in = Width;  //later used for RgNWORDS
			//setup sample width, NOTE: Now only 1 Nsamples
			errChk( viOut32 (mglobals->basevi, VI_A24_SPACE,
							 rgNWORDS_IN[mglobals->midx],
							 mglobals->sample_words_in + (1 << shiftNWORDS_B_LENGTH)));  //+1 Nsamples
			if (mglobals->memsize_in)
			{
				//переустановим также rgSTOP для выравнивания по новой ширине кадра
				ViUInt32 start, stop, loop_size_in;

				errChk( viIn32 (mglobals->basevi, VI_A24_SPACE,
								rgSTOP_IN[mglobals->midx],
								&stop));
				errChk( viIn32 (mglobals->basevi, VI_A24_SPACE,
								rgSTART_IN[mglobals->midx],
								&start));
				loop_size_in = checkLsize((stop-start)<<8, mglobals->sample_bytes_in);
				stop = start + (loop_size_in >> 8);      //for block address

				errChk(LockOutSTARTSTOP(mglobals,
										rgSTOP_IN,
										stop));

			}
#ifdef DBGPRINT
			printf("NWORDS_IN = %08X\n", mglobals->sample_words_in + (1 << shiftNWORDS_B_LENGTH));
#endif
		}
	}
Error:
	if (mglobals)
	{
		unmbase_ErrLed((PUserData)mglobals->pbase_data, status<0);
		UnlockMB (mglobals->pbase_data);
	}
	return status;
}

/*--------------------------------------------------------------------------*/
/* Query sample width of mezzanine                                          */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_sample_width_q (ViSession mvi,
		ViUInt16 io,
		ViUInt32 *Width)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS;
	mviChk(mvi, mglobals);
	notNMU(mglobals);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;

		vxiCmd.cmd = ARMCMD_MSWIDTHq;

		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								io,
								&vxiCmd, &vxiAnsw);

		*Width = vxiAnsw.data16;
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viQueryf(mglobals->basevi,
											"MSWIDTH%d? %c\n",
											"%u",
											mglobals->mnum, IOChar[io],
											Width));
		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
	}
	else
	{
		//return sample width
		*Width = io ? mglobals->sample_words_out : mglobals->sample_words_in;
	}
Error:
	if (mglobals) UnlockMB (mglobals->pbase_data);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Set delay of first mezzanine sample                                      */
/*--------------------------------------------------------------------------*/
//OK1 - FirstDelay должен быть не менее 2х
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_first_delay (ViSession mvi,
		ViUInt16 io,
		ViUInt32 FirstDelay)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS;
	mviChk(mvi, mglobals);
	notNMU(mglobals);
	SpyLog2("unmbase_m_first_delay(m%d, %d)", mglobals->mnum, FirstDelay);
	mbusyChk(mvi, mglobals, io);
	if (FirstDelay < 2)
		errChk(VI_ERROR_PARAMETER2);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;

		vxiCmd.cmd = ARMCMD_MFDELAY;
		vxiCmd.data0 = FirstDelay;

		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								io,
								&vxiCmd, VI_NULL);
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viPrintf(mglobals->basevi,
											"MFDELAY%d %c,%d\n",
											mglobals->mnum, IOChar[io], FirstDelay));
	}
	else
	{
		if (io)     //OUT
		{
			//store first delay
			mglobals->first_delay_out = FirstDelay;
			//setup first delay
			errChk( viOut32 (mglobals->basevi, VI_A24_SPACE,
							 rgZ_OUT[mglobals->midx],
							 FirstDelay-2));
#ifdef DBGPRINT
			printf("rgZ_OUT = %08X\n", FirstDelay-2);
#endif
		}
		else   //IN
		{
			//store first delay
			mglobals->first_delay_in = FirstDelay;
			//setup first delay
			errChk( viOut32 (mglobals->basevi, VI_A24_SPACE,
							 rgZ_IN[mglobals->midx],
							 FirstDelay-2));
#ifdef DBGPRINT
			printf("rgZ_IN = %08X\n", FirstDelay-2);
#endif
		}
	}
Error:
	if (mglobals)
	{
		unmbase_ErrLed((PUserData)mglobals->pbase_data, status<0);
		UnlockMB (mglobals->pbase_data);
	}
	return status;
}

/*--------------------------------------------------------------------------*/
/* Query delay of first mezzanine sample                                    */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_first_delay_q (ViSession mvi,
		ViUInt16 io,
		ViUInt32 *FirstDelay)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS;
	mviChk(mvi, mglobals);
	notNMU(mglobals);
	//return first delay
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;

		vxiCmd.cmd = ARMCMD_MFDELAYq;

		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								io,
								&vxiCmd, &vxiAnsw);

		*FirstDelay = vxiAnsw.data0;
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viQueryf(mglobals->basevi,
											"MFDELAY%d? %c\n",
											"%u",
											mglobals->mnum, IOChar[io],
											FirstDelay));
		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
	}
	else
	{
		*FirstDelay = io ? mglobals->first_delay_out : mglobals->first_delay_in;
	}
Error:
	if (mglobals) UnlockMB (mglobals->pbase_data);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Allocate memory for mezzanine                                            */
/*--------------------------------------------------------------------------*/
//OK1

_UNMBASE_API ViStatus _VI_FUNC unmbase_m_alloc (ViSession mvi,
		ViUInt16 io,
		ViUInt32 Size,
		ViUInt32 *Addr)
{
	PUserData globals = NULL;
	PM_SESSION mglobals = NULL;
	ViUInt32 i, j;
	ViUInt16 old_alloc_num[MAX_MEM_BLOCKS]; //mezzanine owners of MAX_MEM_BLOCKS ram areas (0 - free area)
	ViUInt16 old_alloc_io[MAX_MEM_BLOCKS];  //io owners of MAX_MEM_BLOCKS ram areas
	ViUInt32 old_alloc_ptr[MAX_MEM_BLOCKS]; //pointers to MAX_MEM_BLOCKS ram areas
	ViUInt32 old_alloc_size[MAX_MEM_BLOCKS];    //size of MAX_MEM_BLOCKS ram areas (0 - no more ram)
	ViUInt32 *membase=0, *memsize=0; //point to x_in or x_out apropriate to io
	ViStatus status = VI_SUCCESS;
	ViUInt32 tmpAddr;

	mviChk(mvi, mglobals);
	notNMU(mglobals);
	SpyLog2("unmbase_m_alloc(m%d, %d samples)", mglobals->mnum, Size);
	mbusyChk(mvi, mglobals, io);
	if (!Addr)
		Addr = &tmpAddr;
	*Addr = 0;
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;

		vxiCmd.cmd = ARMCMD_MMALLOC;
		vxiCmd.data0 = Size;

		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								io,
								&vxiCmd, &vxiAnsw);

		*Addr = vxiAnsw.data0;
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viQueryf(mglobals->basevi,
											"MMALLOC%d %c,%d;"
											"MMALLOC%d? %c\n",
											"%u,%u",
											mglobals->mnum, IOChar[io], Size,
											mglobals->mnum, IOChar[io],
											Addr, &Size));
		viClear(mglobals->basevi);	//поскольку при большом MMALLOC там остается ошибка...
		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
	}
	else
	{
		globals = (PUserData)mglobals->pbase_data;
		if (globals == NULL)
			errChk(VI_ERROR_INV_OBJECT);
		if (io)     //OUT
		{
			membase = &(mglobals->membase_out);
			memsize = &(mglobals->memsize_out);
		}
		else      //IN
		{
			membase = &(mglobals->membase_in);
			memsize = &(mglobals->memsize_in);
		}
		Size = (Size+0xFF)&~0xFF;   //for 0x100 bytes divisions!!!
		//store old allocations for restoration on error
		memcpy (old_alloc_num, globals->alloc_num, sizeof(*old_alloc_num)*MAX_MEM_BLOCKS);
		memcpy (old_alloc_io, globals->alloc_io, sizeof(*old_alloc_io)*MAX_MEM_BLOCKS);
		memcpy (old_alloc_ptr, globals->alloc_ptr, sizeof(*old_alloc_ptr)*MAX_MEM_BLOCKS);
		memcpy (old_alloc_size, globals->alloc_size, sizeof(*old_alloc_size)*MAX_MEM_BLOCKS);
		//if size = 0, then free memory
		//or if realloc - at first free memory too
		if ((Size == 0) || (*memsize != 0))
		{
			for (i=0; i<MAX_MEM_BLOCKS; i++)
			{
				if ((globals->alloc_num[i] == (mglobals->mnum)) &&
						(globals->alloc_io[i] == io))
					globals->alloc_num[i] = 0;
			}
			//merge free ram areas
			i=0;
			while (i<(MAX_MEM_BLOCKS-1))
			{
				if ((globals->alloc_num[i] == 0) && (globals->alloc_num[i+1] == 0))
				{
					//merge (i) area and (i+1) area
					globals->alloc_size[i] += globals->alloc_size[i+1];
					//shift all areas left
					for (j=i+1; j<(MAX_MEM_BLOCKS-1); j++)
					{
						globals->alloc_num[j] = globals->alloc_num[j+1];
						globals->alloc_io[j] = globals->alloc_io[j+1];
						globals->alloc_size[j] = globals->alloc_size[j+1];
						globals->alloc_ptr[j] = globals->alloc_ptr[j+1];
					}
					globals->alloc_size[MAX_MEM_BLOCKS-1] = 0;
					if ((globals->alloc_num[i+1] == 0) &&   //if next RAM block also free
							(globals->alloc_size[i+1]))         //and not zero size
						i--;    //try to stay here. May be need to merge more then 2 blocks
				}
				i++;
			}
			if (Size == 0)
			{
				*membase = 0;
				*memsize = 0;
				okChk(VI_SUCCESS);
			}
		}
		//Allocate or reallocate Ram. If reallocate not succeed, restore previous allocation
		//find minimum free memory block >= required size
		j=0xFFFF;   //index of best block
		i=0;
		while ((i<MAX_MEM_BLOCKS) && (globals->alloc_size[i] !=0))
		{
			if (globals->alloc_num[i] == 0)
			{
				if (globals->alloc_size[i] > *Addr)
					*Addr = globals->alloc_size[i];
				if (globals->alloc_size[i] >= Size)
				{
					if (j == 0xFFFF)
						j = i;  //first free block with required size
					else
					if (globals->alloc_size[i] < globals->alloc_size[j])
						j = i;  //free block with better size
				}
			}
			i++;
		}
		if (j == 0xFFFF)    //no required memory, restore allocations
		{
			memcpy (globals->alloc_num, old_alloc_num, sizeof(*old_alloc_num)*MAX_MEM_BLOCKS);
			memcpy (globals->alloc_io, old_alloc_io, sizeof(*old_alloc_io)*MAX_MEM_BLOCKS);
			memcpy (globals->alloc_ptr, old_alloc_ptr, sizeof(*old_alloc_ptr)*MAX_MEM_BLOCKS);
			memcpy (globals->alloc_size, old_alloc_size, sizeof(*old_alloc_size)*MAX_MEM_BLOCKS);
			errChk(UNMBASE_ERROR_NO_MEMORY);
		}
		//Yes, we found free memory with required size
		*membase = globals->alloc_ptr[j];
		*memsize = Size;
		globals->alloc_num[j] = (ViUInt16)(mglobals->mnum);  //current block is own by this mezzanine
		globals->alloc_io[j] = io;              //current block is own by IN or OUT part of this mezzanine
		*Addr = *membase;
		//if required size == size of block - no rebuild allocations need, return
		if (globals->alloc_size[j] == Size)
			okChk(VI_SUCCESS);
		//rebuild allocations
		for (i=(MAX_MEM_BLOCKS-1); i>j; i--)
		{
			globals->alloc_num[i] = globals->alloc_num[i-1];
			globals->alloc_io[i] = globals->alloc_io[i-1];
			globals->alloc_size[i] = globals->alloc_size[i-1];
			globals->alloc_ptr[i] = globals->alloc_ptr[i-1];
		}
		//split current block into allocated and free
		globals->alloc_num[j+1] = 0;                            //next is free
		globals->alloc_size[j+1] = globals->alloc_size[j]-Size; //remainder size
		globals->alloc_ptr[j+1] = globals->alloc_ptr[j]+Size;   //shift pointer
		globals->alloc_size[j] = Size;                          //current block size
	}
Error:
	//setup segments data
	//Irina 12-2006
	if (mglobals && memsize && *memsize)
	{
		if (io)     //OUT
		{
			//делаем кратно 256 и ширине кадра
			ViUInt32 loop_size_out = checkLsize(mglobals->memsize_out, mglobals->sample_bytes_out);
			if (!loop_size_out)
				loop_size_out = mglobals->memsize_out;
			mglobals->loop_base_out = mglobals->loop1_base_out = mglobals->loop2_base_out = 0;
			mglobals->loop_size_out =mglobals->loop1_size_out = loop_size_out;
			mglobals->loop2_size_out = 0;
			SpyLog3("m%do Allocate %08X bytes at %08X", mglobals->mnum, mglobals->membase_out, mglobals->memsize_out);
		}
		else      //IN
		{
			ViUInt32 loop_size_in = checkLsize(mglobals->memsize_in, mglobals->sample_bytes_in);
			if (!loop_size_in)
				loop_size_in = mglobals->memsize_in;
			mglobals->loop_base_in = mglobals->loop1_base_in = mglobals->loop2_base_in = 0;
			mglobals->loop_size_in = mglobals->loop1_size_in = loop_size_in;
			mglobals->loop2_size_in = 0;
			SpyLog3("m%di Allocate %08X bytes at %08X", mglobals->mnum, mglobals->membase_in, mglobals->memsize_in);
		}
	}

	if (mglobals) UnlockMB (mglobals->pbase_data);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Query mezzanine allocated memory                                         */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_alloc_q (ViSession mvi,
		ViUInt16 io,
		ViUInt32 *Size,
		ViUInt32 *Addr)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS;
	ViUInt32 tmpSize, tmpAddr;
	mviChk(mvi, mglobals);
	notNMU(mglobals);
	if (!Size)
		Size = &tmpSize;
	if (!Addr)
		Addr = &tmpAddr;
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;

		vxiCmd.cmd = ARMCMD_MMALLOCq;
		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								io,
								&vxiCmd, &vxiAnsw);

		*Addr = vxiAnsw.data0;
		*Size = vxiAnsw.data1;
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viQueryf(mglobals->basevi,
											"MMALLOC%d? %c\n",
											"%u,%u",
											mglobals->mnum, IOChar[io],
											Addr, Size));
		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
	}
	else
	{
		if (io)     //OUT
		{
			*Addr = mglobals->membase_out;
			*Size = mglobals->memsize_out;
		}
		else      //IN
		{
			*Addr = mglobals->membase_in;
			*Size = mglobals->memsize_in;
		}
	}
Error:
	if (mglobals) UnlockMB (mglobals->pbase_data);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Switch mezzanine mode:single, block or cycle                             */
/*--------------------------------------------------------------------------*/
//ВНИМАНИЕ!!! Для одного мезонина можно комбинировать на вводе и выводе любой режим с одиночным,
//      но нельзя блочный и непрерывный!!!
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_mode (ViSession mvi,
		ViUInt16 io,
		ViUInt16 Mode)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS;
	ViUInt32 start, stop;

	mviChk(mvi, mglobals);
	notNMU(mglobals);
	SpyLog2("unmbase_m_mode(m%d Mode %d)", mglobals->mnum, Mode);
	mbusyChk(mvi, mglobals, io);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;

		vxiCmd.cmd = armvxiCmdD16(ARMCMD_MMODE,
								  Mode);

		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								io,
								&vxiCmd, VI_NULL);
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viPrintf(mglobals->basevi,
											"MMODE%d %c,%d\n",
											mglobals->mnum, IOChar[io], Mode));
	}
	else
	{
		if (io)     //OUT
		{
			//store mode
			mglobals->mode_out = Mode;

			switch (Mode)
			{
			case UNMBASE_MODE_SINGLE:
				errChk(Out32_CONF2(mglobals->basevi,
								   ~0,
								   maskCONF2_OUT_SINGLE[mglobals->midx]));  //setup SINGLE bit

				errChk(Out32_CONF1(mglobals->basevi,
								   ~0,
								   maskCONF1_COUNT_CONF[mglobals->midx]));  //set NOLOOP
				if (mglobals->sample_bytes_out)     //may be need restore sample width with Nsamples=1
				{
					//setup one sample RAM block
					start = mglobals->membase_out >> 8;     //for block address
					stop = start +
						   ((mglobals->sample_bytes_out + //size in bytes
							 255)                        //for up to integer num of blocks
							>> 8);                  //for block address
					errChk(LockOutSTARTSTOP(mglobals,
											rgLIMIT_OUT,
											stop-start));   //IRQ at end
					errChk(LockOutSTARTSTOP(mglobals,
											rgSTOP_OUT,
											stop));
					errChk(LockOutSTARTSTOP(mglobals,
											rgSTART_OUT,
											start));

					errChk( viOut32 (mglobals->basevi, VI_A24_SPACE,
									 rgNWORDS_OUT[mglobals->midx],
									 mglobals->sample_words_out + (1 << shiftNWORDS_B_LENGTH)));
				}
				break;
			case UNMBASE_MODE_BLOCK:
				mglobals->next_sample_to_out = 0;   //clear memory for out

				errChk(Out32_CONF2(mglobals->basevi,
								   ~maskCONF2_OUT_SINGLE[mglobals->midx],   //clear SINGLE bit
								   0));
				errChk(Out32_CONF1(mglobals->basevi,
								   ~0,
								   maskCONF1_COUNT_CONF[mglobals->midx]));  //set NOLOOP

				if (mglobals->block_size_out)       //may be need restore  block size
				{
					if (mglobals->subblock_base_out)
						errChk( unmbase_m_subblock (mvi,
													  io,
													  mglobals->subblock_base_out,
													  mglobals->subblock_size_out));
					else
						errChk( unmbase_m_block_size (mvi,
													  io,
													  mglobals->block_size_out));
				}
				if (mglobals->mode_in == UNMBASE_MODE_LOOP) //!!! Don't mix MODE_BLOCK and MODE_LOOP !!!
					errChk(unmbase_m_mode(mvi, UNMBASE_IOMODE_IN, Mode));   //so set block mode too
				break;
			case UNMBASE_MODE_LOOP:
				mglobals->next_sample_to_out = 0;   //clear memory for out
				errChk(Out32_CONF2(mglobals->basevi,
								   ~maskCONF2_OUT_SINGLE[mglobals->midx],   //clear SINGLE bit
								   0));

				errChk(Out32_CONF1(mglobals->basevi,
								   ~maskCONF1_COUNT_CONF[mglobals->midx],   //clear NOLOOP
								   0));

				//if (mglobals->packet_size_out)      //may be need restore  packet size
				{
					errChk( unmbase_m_packet_size (mvi,
												   io,
												   mglobals->packet_size_out));
				}
				if (mglobals->mode_in == UNMBASE_MODE_BLOCK)                //!!! Don't mix MODE_BLOCK and MODE_LOOP !!!
					errChk(unmbase_m_mode(mvi, UNMBASE_IOMODE_IN, Mode));   //so set loop mode too
				break;
			}
		}
		else      //IN
		{
			//store mode
			mglobals->mode_in = Mode;

			switch (Mode)
			{
			case UNMBASE_MODE_SINGLE:
				errChk(Out32_CONF2(mglobals->basevi,
								   ~0,
								   maskCONF2_IN_SINGLE[mglobals->midx]));   //setup SINGLE bit

				errChk(Out32_CONF1(mglobals->basevi,
								   ~0,
								   maskCONF1_COUNT_CONF[mglobals->midx]));  //set NOLOOP
				if (mglobals->sample_bytes_in)      //may be need restore sample width with Nsamples=1
				{
					//setup one sample RAM block
					start = mglobals->membase_in >> 8;      //for block address
					stop = start +
						   ((mglobals->sample_bytes_in +  //size in bytes
							 255)                      //for up to integer num of blocks
							>> 8);                //for block address
					errChk(LockOutSTARTSTOP(mglobals,
											rgLIMIT_IN,
											stop-start));   //IRQ at end
					errChk(LockOutSTARTSTOP(mglobals,
											rgSTOP_IN,
											stop));
					errChk(LockOutSTARTSTOP(mglobals,
											rgSTART_IN,
											start));

					errChk( viOut32 (mglobals->basevi, VI_A24_SPACE,
									 rgNWORDS_IN[mglobals->midx],
									 mglobals->sample_words_in + (1 << shiftNWORDS_B_LENGTH)));
				}
				break;

			case UNMBASE_MODE_BLOCK:

				errChk(Out32_CONF2(mglobals->basevi,
								   ~maskCONF2_IN_SINGLE[mglobals->midx],    //clear SINGLE bit
								   0));
				errChk(Out32_CONF1(mglobals->basevi,
								   ~0,
								   maskCONF1_COUNT_CONF[mglobals->midx]));  //set NOLOOP

				if (mglobals->block_size_in)        //may be need restore  block size
				{
					if (mglobals->subblock_base_in)
						errChk( unmbase_m_subblock (mvi,
													  io,
													  mglobals->subblock_base_in,
													  mglobals->subblock_size_in));
					else
						errChk( unmbase_m_block_size (mvi,
												  io,
												  mglobals->block_size_in));
				}
				if (mglobals->mode_out == UNMBASE_MODE_LOOP)            //!!! Don't mix MODE_BLOCK and MODE_LOOP !!!
					errChk(unmbase_m_mode(mvi, UNMBASE_IOMODE_OUT, Mode));  //so set block mode too
				break;
			case UNMBASE_MODE_LOOP:
				errChk(Out32_CONF2(mglobals->basevi,
								   ~maskCONF2_IN_SINGLE[mglobals->midx],    //clear SINGLE bit
								   0));

				errChk(Out32_CONF1(mglobals->basevi,
								   ~maskCONF1_COUNT_CONF[mglobals->midx],   //clear NOLOOP
								   0));

				//if (mglobals->packet_size_in)       //may be need restore  packet size
				{
					errChk( unmbase_m_packet_size (mvi,
												   io,
												   mglobals->packet_size_in));
				}
				if (mglobals->mode_out == UNMBASE_MODE_LOOP)            //!!! Don't mix MODE_BLOCK and MODE_LOOP !!!
					errChk(unmbase_m_mode(mvi, UNMBASE_IOMODE_OUT, Mode));  //so set loop mode too

				break;
			}
		}
	}
Error:
	if (mglobals)
	{
		unmbase_ErrLed((PUserData)mglobals->pbase_data, status<0);
		UnlockMB (mglobals->pbase_data);
	}
	return status;
}

/*--------------------------------------------------------------------------*/
/* Query mezzanine mode:single, block or cycle                             */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_mode_q (ViSession mvi,
		ViUInt16 io,
		ViUInt16 *Mode)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS;
	mviChk(mvi, mglobals);
	notNMU(mglobals);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;

		vxiCmd.cmd = ARMCMD_MMODEq;

		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								io,
								&vxiCmd, &vxiAnsw);

		*Mode = (ViUInt16)vxiAnsw.data16;
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viQueryf(mglobals->basevi,
											"MMODE%d? %c\n",
											"%hd",
											mglobals->mnum, IOChar[io],
											Mode));
		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
	}
	else
	{
		//return mode
		*Mode = io ? mglobals->mode_out : mglobals->mode_in;
	}
Error:
	if (mglobals) UnlockMB (mglobals->pbase_data);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Switch mezzanine START signal mode: pulse or level                       */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_trig_length (ViSession mvi,
		ViUInt16 Mode)
{
	PM_SESSION mglobals = NULL;
	PUserData globals = NULL;
	ViStatus status = VI_SUCCESS;
	ViInt32 i;
	mviChk(mvi, mglobals);
	globals = (PUserData)mglobals->pbase_data;
	SpyLog2("unmbase_m_trig_length(m%d, %d)", mglobals->mnum, Mode);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;

		vxiCmd.cmd = armvxiCmdD16(ARMCMD_MTRLEN,
								  Mode);

		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								0,
								&vxiCmd, VI_NULL);
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		if (!globals->basesimple)
		{
			LockMB(mglobals->pbase_data);
			errChkMB(mglobals->basevi, viPrintf(mglobals->basevi,
											"MTRLEN%d %d\n",
											mglobals->mnum, Mode));
		}
	}
	else
	{
		if (globals->basesimple)
		{
			//store mode
			for (i=0; i<4; i++)
				globals->m_session[i].trig_length = Mode;

			errChk( Out16_CONF3(mglobals->basevi,
								((ViUInt16)~0xF000),
								Mode ? (maskCONF3_START_LONG_IN | maskCONF3_START_LONG_OUT)
								: (maskCONF3_START_SHORT_IN | maskCONF3_START_SHORT_OUT)));

		}
		else
		{
			mbusyChk(mvi, mglobals, 0);
			mbusyChk(mvi, mglobals, 1);
			//store mode
			mglobals->trig_length = Mode;
			//setup mode
			errChk( Out32_COMM2A(mglobals->basevi,
								 ~maskCOMM2A_M_WAITSTOP[mglobals->midx],
								 Mode ? maskCOMM2A_M_WAITSTOP[mglobals->midx] : 0));

		}
	}
Error:
	if (mglobals)
	{
		unmbase_ErrLed((PUserData)mglobals->pbase_data, status<0);
		UnlockMB (mglobals->pbase_data);
	}
	return status;
}

/*--------------------------------------------------------------------------*/
/* Query mezzanine START signal mode: pulse or level                        */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_trig_length_q (ViSession mvi,
		ViUInt16 *Mode)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS;
	mviChk(mvi, mglobals);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;

		vxiCmd.cmd = ARMCMD_MTRLENq;

		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								0,
								&vxiCmd, &vxiAnsw);

		*Mode = (ViUInt16)vxiAnsw.data16;
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viQueryf(mglobals->basevi,
											"MTRLEN%d?\n",
											"%hd",
											mglobals->mnum,
											Mode));
		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
	}
	else
	{
		*Mode = mglobals->trig_length;
	}
Error:
	if (mglobals) UnlockMB (mglobals->pbase_data);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Set mezzanine sampling frequency                                         */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_clock (ViSession mvi,
		ViUInt16 io,
		ViUInt32 Divisor)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS;
	mviChk(mvi, mglobals);
	notNMU(mglobals);
	SpyLog2("unmbase_m_clock(m%d, %d)", mglobals->mnum, Divisor);
	mbusyChk(mvi, mglobals, io);
	if (Divisor < 5)
		errChk(VI_ERROR_PARAMETER2);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;

		vxiCmd.cmd = ARMCMD_MCLOCK;
		vxiCmd.data0 = Divisor;

		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								io,
								&vxiCmd, VI_NULL);
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viPrintf(mglobals->basevi,
											"MCLOCK%d %c,%d\n",
											mglobals->mnum, IOChar[io], Divisor));
	}
	else
	{
		if (io)     //OUT
		{
			//store divisor
			mglobals->divisor_out = Divisor;
			//setup divisor
			errChk( viOut32 (mglobals->basevi, VI_A24_SPACE,
							 rgP_OUT[mglobals->midx],
							 Divisor-1));
#ifdef DBGPRINT
			printf("rgP_OUT = %08X\n", Divisor-1);
#endif
		}
		else      //IN
		{
			//store divisor
			mglobals->divisor_in = Divisor;
			//setup divisor
			errChk( viOut32 (mglobals->basevi, VI_A24_SPACE,
							 rgP_IN[mglobals->midx],
							 Divisor-1));
#ifdef DBGPRINT
			printf("rgP_IN = %08X\n", Divisor-1);
#endif
		}
	}
Error:
	if (mglobals)
	{
		unmbase_ErrLed((PUserData)mglobals->pbase_data, status<0);
		UnlockMB (mglobals->pbase_data);
	}
	return status;
}

/*--------------------------------------------------------------------------*/
/* Query mezzanine sampling frequency                                         */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_clock_q (ViSession mvi,
		ViUInt16 io,
		ViUInt32 *Divisor)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS;
	mviChk(mvi, mglobals);
	notNMU(mglobals);
	//return divisor
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;

		vxiCmd.cmd = ARMCMD_MCLOCKq;

		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								io,
								&vxiCmd, &vxiAnsw);

		*Divisor = vxiAnsw.data0;
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viQueryf(mglobals->basevi,
											"MCLOCK%d? %c\n",
											"%u",
											mglobals->mnum, IOChar[io],
											Divisor));
		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
	}
	else
	{
		*Divisor = io ? mglobals->divisor_out : mglobals->divisor_in;
	}
Error:
	if (mglobals) UnlockMB (mglobals->pbase_data);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Set mezzanine block size                                                 */
/* Note: Call this when switch to BLOCK mode!                               */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_block_size (ViSession mvi,
		ViUInt16 io,
		ViUInt32 Size)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = 0;
	ViUInt32 start, stop;
	mviChk(mvi, mglobals);
	notNMU(mglobals);
	SpyLog2("unmbase_m_block_size(m%d, %d)", mglobals->mnum, Size);
	mbusyChk(mvi, mglobals, io);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;

		vxiCmd.cmd = ARMCMD_MBSIZE;
		vxiCmd.data0 = Size;
		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								io,
								&vxiCmd, VI_NULL);
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viPrintf(mglobals->basevi,
											"MBSIZE%d %c,%d\n",
											mglobals->mnum, IOChar[io], Size));
	}
	else
	{

		if (io)     //OUT
		{
			//store block size
			mglobals->block_size_out = Size;
			mglobals->subblock_base_out = 0;
			mglobals->subblock_size_out = Size;

			if (mglobals->mode_out == UNMBASE_MODE_BLOCK)
			{
				//setup block size
				start = mglobals->membase_out >> 8;     //for block address
				stop = start +
					   (((Size * mglobals->sample_bytes_out) +  //size in bytes
						 255)                                 //for up to integer num of blocks
						>> 8);                           //for block address
				errChk(LockOutSTARTSTOP(mglobals,
										rgLIMIT_OUT,
										stop-start));   //IRQ at end
				errChk(LockOutSTARTSTOP(mglobals,
										rgSTOP_OUT,
										stop));
				errChk(LockOutSTARTSTOP(mglobals,
										rgSTART_OUT,
										start));
				SpyLog4("m%do block %08X-%08X (%08X bytes)", mglobals->mnum, start<<8, stop<<8, (stop-start)<<8);
			}
		}
		else      //IN
		{
			//store block size
			mglobals->block_size_in = Size;
			mglobals->subblock_base_in = 0;
			mglobals->subblock_size_in = Size;
			if (mglobals->mode_in == UNMBASE_MODE_BLOCK)
			{
				//setup block size
				start = mglobals->membase_in >> 8;      //for block address
				stop = start +
					   (((Size * mglobals->sample_bytes_in) +   //size in bytes
						 255)                                 //for up to integer num of blocks
						>> 8);                           //for block address
				errChk(LockOutSTARTSTOP(mglobals,
										rgLIMIT_IN,
										stop-start));   //IRQ at end
				errChk(LockOutSTARTSTOP(mglobals,
										rgSTOP_IN,
										stop));
				errChk(LockOutSTARTSTOP(mglobals,
										rgSTART_IN,
										start));
				SpyLog4("m%di block %08X-%08X (%08X bytes)", mglobals->mnum, start<<8, stop<<8, (stop-start)<<8);
			}
		}
	}
Error:
	if (mglobals)
	{
		unmbase_ErrLed((PUserData)mglobals->pbase_data, status<0);
		UnlockMB (mglobals->pbase_data);
	}
	return status;
}

/*--------------------------------------------------------------------------*/
/* Query mezzanine block size                                               */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_block_size_q (ViSession mvi,
		ViUInt16 io,
		ViUInt32 *Size)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS;
	mviChk(mvi, mglobals);
	notNMU(mglobals);
	//return block size
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;

		vxiCmd.cmd = ARMCMD_MBSIZEq;
		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								io,
								&vxiCmd, &vxiAnsw);

		*Size = vxiAnsw.data0;
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viQueryf(mglobals->basevi,
											"MBSIZE%d? %c\n",
											"%u",
											mglobals->mnum, IOChar[io],
											Size));
		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
	}
	else
	{
		*Size = io ? mglobals->block_size_out : mglobals->block_size_in;
	}
Error:
	if (mglobals) UnlockMB (mglobals->pbase_data);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Set mezzanine subblock                                                   */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_subblock (ViSession mvi,
		ViUInt16 io,
		ViUInt32 Idx,
		ViUInt32 Size)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = 0, mbstatus = 0;
	ViUInt32 start, stop;
	mviChk(mvi, mglobals);
	notNMU(mglobals);
	SpyLog3("unmbase_m_subblock(m%d, %d, %d)", mglobals->mnum, Idx, Size);
	mbusyChk(mvi, mglobals, io);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;

		vxiCmd.cmd = ARMCMD_MSBLOCK;
		vxiCmd.data0 = Idx;
		vxiCmd.data1 = Size;
		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								io,
								&vxiCmd, VI_NULL);
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viQueryf(mglobals->basevi,
											"MSBLOCK%d %c,%d,%d;*ERR?\n",
											"%d",
											mglobals->mnum, IOChar[io], Idx, Size,
											&mbstatus));
		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
		errChk(mbstatus);
	}
	else
	{

		if (io)     //OUT
		{
			//store subblock size
			mglobals->subblock_base_out = Idx * mglobals->sample_bytes_out;
			mglobals->subblock_size_out = Size;
			if (mglobals->mode_out == UNMBASE_MODE_BLOCK)
			{
				//setup block size
				start = mglobals->subblock_base_out >> 8;     //for block address
				stop = start +
					   (((Size * mglobals->sample_bytes_out) +  //size in bytes
						 255)                                 //for up to integer num of blocks
						>> 8);                           //for block address
				errChk(LockOutSTARTSTOP(mglobals,
										rgLIMIT_OUT,
										stop-start));   //IRQ at end
				errChk(LockOutSTARTSTOP(mglobals,
										rgSTOP_OUT,
										stop));
				errChk(LockOutSTARTSTOP(mglobals,
										rgSTART_OUT,
										start));
				SpyLog4("m%do block %08X-%08X (%08X bytes)", mglobals->mnum, start<<8, stop<<8, (stop-start)<<8);
			}
		}
		else      //IN
		{
			//store subblock size
			mglobals->subblock_base_in = Idx * mglobals->sample_bytes_in;
			mglobals->subblock_size_in = Size;
			if (mglobals->mode_in == UNMBASE_MODE_BLOCK)
			{
				//setup block size
				start = mglobals->subblock_base_in >> 8;      //for block address
				stop = start +
					   (((Size * mglobals->sample_bytes_in) +   //size in bytes
						 255)                                 //for up to integer num of blocks
						>> 8);                           //for block address
				errChk(LockOutSTARTSTOP(mglobals,
										rgLIMIT_IN,
										stop-start));   //IRQ at end
				errChk(LockOutSTARTSTOP(mglobals,
										rgSTOP_IN,
										stop));
				errChk(LockOutSTARTSTOP(mglobals,
										rgSTART_IN,
										start));
				SpyLog4("m%di block %08X-%08X (%08X bytes)", mglobals->mnum, start<<8, stop<<8, (stop-start)<<8);
			}
		}
	}
Error:
	if (mglobals)
	{
		unmbase_ErrLed((PUserData)mglobals->pbase_data, status<0);
		UnlockMB (mglobals->pbase_data);
	}
	return status;
}

/*--------------------------------------------------------------------------*/
/* Set and Start mezzanine subblock                                         */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_subblock_start (ViSession mvi,
		ViUInt16 io,
		ViUInt32 Idx,
		ViUInt32 Size)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = 0, mbstatus = 0;
	mviChk(mvi, mglobals);
	notNMU(mglobals);
	SpyLog3("unmbase_m_subblock_start(m%d, %d, %d)", mglobals->mnum, Idx, Size);
	mbusyChk(mvi, mglobals, io);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;

		vxiCmd.cmd = ARMCMD_MSBLOCK_START;
		vxiCmd.data0 = Idx;
		vxiCmd.data1 = Size;
		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								io,
								&vxiCmd, VI_NULL);
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viQueryf(mglobals->basevi,
											"MSBLOCK:START%d %c,%d,%d;*ERR?\n",
											"%d",
											mglobals->mnum, IOChar[io], Idx, Size,
											&mbstatus));
		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
		errChk(mbstatus);
	}
	else
	{
		errChk(unmbase_m_subblock (mvi, io, Idx, Size));
		errChk(unmbase_m_start (mvi, io));
	}
Error:
	if (mglobals)
	{
		unmbase_ErrLed((PUserData)mglobals->pbase_data, status<0);
		UnlockMB (mglobals->pbase_data);
	}
	return status;
}

/*--------------------------------------------------------------------------*/
/* Query mezzanine subblock                                                 */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_subblock_q (ViSession mvi,
		ViUInt16 io,
		ViUInt32 *Idx,
		ViUInt32 *Size)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS;
	mviChk(mvi, mglobals);
	notNMU(mglobals);
	//return block size
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;

		vxiCmd.cmd = ARMCMD_MSBLOCKq;
		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								io,
								&vxiCmd, &vxiAnsw);

		*Idx = vxiAnsw.data0;
		*Size = vxiAnsw.data1;
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viQueryf(mglobals->basevi,
											"MSBLOCK%d? %c\n",
											"%u,%u",
											mglobals->mnum, IOChar[io],
											Idx, Size));
		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
	}
	else
	{
		if (io)
		{
			if (mglobals->sample_bytes_out)
			{
				*Idx = mglobals->subblock_base_out / mglobals->sample_bytes_out;
				*Size = mglobals->subblock_size_out;
			}
			else
			{
				*Idx = 0;
				*Size = 0;
			}
		}
		else
		{
			if (mglobals->sample_bytes_in)
			{
				*Idx = mglobals->subblock_base_in / mglobals->sample_bytes_in;
				*Size = mglobals->subblock_size_in;
			}
			else
			{
				*Idx = 0;
				*Size = 0;
			}
		}
	}
Error:
	if (mglobals) UnlockMB (mglobals->pbase_data);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Set mezzanine loop size                                                  */
/* (setup for current segment)                                              */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_loop_size (ViSession mvi,
		ViUInt16 io,
		ViUInt32 Size)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = 0;
	mviChk(mvi, mglobals);
	notNMU(mglobals);
	SpyLog2("unmbase_m_loop_size(%d, %d)", mglobals->mnum, Size);
	mbusyChk(mvi, mglobals, io);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;

		vxiCmd.cmd = ARMCMD_MLSIZE;
		vxiCmd.data0 = Size;
		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								io,
								&vxiCmd, VI_NULL);
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viPrintf(mglobals->basevi,
											"MLSIZE%d %c,%d\n",
											mglobals->mnum, IOChar[io], Size));
	}
	else
	{
		if (io)     //OUT
		{
			if (mglobals->loop_seg_out)
			{
				errChk(unmbase_m_segment(mvi, io, 1,
										 mglobals->loop2_base_out/mglobals->sample_bytes_out,
										 Size));
				mglobals->loop_size_out = mglobals->loop2_size_out;
				mglobals->loop_base_out = mglobals->loop2_base_out;
			}
			else
			{
				errChk(unmbase_m_segment(mvi, io, 0,
										 mglobals->loop1_base_out/mglobals->sample_bytes_out,
										 Size));
				mglobals->loop_size_out = mglobals->loop1_size_out;
				mglobals->loop_base_out = mglobals->loop1_base_out;
			}
			if (mglobals->mode_out == UNMBASE_MODE_LOOP)
				status = unmbase_m_packet_size (mvi, io, mglobals->packet_size_out);	//install all sizes for loop mode
		}
		else      //IN
		{
			if (mglobals->loop_seg_in)
			{
				errChk(unmbase_m_segment(mvi, io, 1,
										 mglobals->loop2_base_in/mglobals->sample_bytes_in,
										 Size));
				mglobals->loop_size_in = mglobals->loop2_size_in;
				mglobals->loop_base_in = mglobals->loop2_base_in;
			}
			else
			{
				errChk(unmbase_m_segment(mvi, io, 0,
										 mglobals->loop1_base_in/mglobals->sample_bytes_in,
										 Size));
				mglobals->loop_size_in = mglobals->loop1_size_in;
				mglobals->loop_base_in = mglobals->loop1_base_in;
			}
			if (mglobals->mode_in == UNMBASE_MODE_LOOP)
				status = unmbase_m_packet_size (mvi, io, mglobals->packet_size_in);	//install all sizes for loop mode
		}
	}
Error:
	if (mglobals)
	{
		unmbase_ErrLed((PUserData)mglobals->pbase_data, status<0);
		UnlockMB (mglobals->pbase_data);
	}
	return status;
}

/*--------------------------------------------------------------------------*/
/* Query mezzanine loop size                                               */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_loop_size_q (ViSession mvi,
		ViUInt16 io,
		ViUInt32 *Size)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS;
	mviChk(mvi, mglobals);
	notNMU(mglobals);
	//return loop size
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;

		vxiCmd.cmd = ARMCMD_MLSIZEq;

		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								io,
								&vxiCmd, &vxiAnsw);

		*Size = vxiAnsw.data0;
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viQueryf(mglobals->basevi,
											"MLSIZE%d? %c\n",
											"%u",
											mglobals->mnum, IOChar[io],
											Size));
		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
	}
	else
	{
		*Size = io ? mglobals->loop_size_out / mglobals->sample_bytes_out
				: mglobals->loop_size_in / mglobals->sample_bytes_in;
	}
Error:
	if (mglobals) UnlockMB (mglobals->pbase_data);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Set mezzanine loop segment config                                        */
/* (do not switch anything)                                                 */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_segment (ViSession mvi,
		ViUInt16 io,
		ViUInt32 Segment,
		ViUInt32 Offset,
		ViUInt32 Size)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = 0;
	mviChk(mvi, mglobals);
	notNMU(mglobals);
	SpyLog4("unmbase_m_segment(m%d, %d, %d, %d)", mglobals->mnum, Segment, Offset, Size);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;

		vxiCmd.cmd = armvxiCmdD16(ARMCMD_MSEG,
								  Segment);
		vxiCmd.data0 = Offset;
		vxiCmd.data1 = Size;
		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								io,
								&vxiCmd, VI_NULL);
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viPrintf(mglobals->basevi,
											"MSEG%d %c,%d,%d,%d\n",
											mglobals->mnum, IOChar[io], Segment, Offset, Size));
	}
	else
	{
		if (io)     //OUT
		{
			if ((mglobals->state_out>0) && (mglobals->loop_seg_out == Segment))
				errChk(UNMBASE_ERROR_BUSY);
			Size *= mglobals->sample_bytes_out;	//to byte size
			Size = checkLsize(Size, mglobals->sample_bytes_out);
			Offset *=  mglobals->sample_bytes_out;	//to byte offset
			Offset = 0xFFFFFF00 & (Offset + 0xFF);	//align
			//store loop size
			if ((Offset + Size) > mglobals->memsize_out)
				errChk(UNMBASE_ERROR_NO_MEMORY);
			if (Segment)
			{
				mglobals->loop2_size_out = Size;
				mglobals->loop2_base_out = Offset;
			}
			else
			{
				mglobals->loop1_size_out = Size;
				mglobals->loop1_base_out = Offset;
			}
		}
		else      //IN
		{
			if ((mglobals->state_in>0) && (mglobals->loop_seg_in == Segment))
				errChk(UNMBASE_ERROR_BUSY);
			Size *= mglobals->sample_bytes_in;	//to byte size
			Size = checkLsize(Size, mglobals->sample_bytes_in);
			Offset *=  mglobals->sample_bytes_in;	//to byte offset
			Offset = 0xFFFFFF00 & (Offset + 0xFF);	//align
			//store loop size
			if ((Offset + Size) > mglobals->memsize_in)
				errChk(UNMBASE_ERROR_NO_MEMORY);
			if (Segment)
			{
				mglobals->loop2_size_in = Size;
				mglobals->loop2_base_in = Offset;
			}
			else
			{
				mglobals->loop1_size_in = Size;
				mglobals->loop1_base_in = Offset;
			}
		}
	}
Error:
	if (mglobals) UnlockMB (mglobals->pbase_data);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Query mezzanine loop segment config                                      */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_segment_q (ViSession mvi,
		ViUInt16 io,
		ViUInt32 Segment,
		ViUInt32 *Offset,
		ViUInt32 *Size)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = 0;
	mviChk(mvi, mglobals);
	notNMU(mglobals);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;

		vxiCmd.cmd = armvxiCmdD16(ARMCMD_MSEGq,
								  Segment);

		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								io,
								&vxiCmd, &vxiAnsw);

		*Offset = vxiAnsw.data0;
		*Size = vxiAnsw.data1;
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viQueryf(mglobals->basevi,
											"MSEG%d? %c,%d\n",
											"%u,%u",
											mglobals->mnum, IOChar[io], Segment,
											Offset, Size));
		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
	}
	else
	{
		if (io)     //OUT
		{
			if (Segment)
			{
				*Size = mglobals->loop2_size_out;
				*Offset = mglobals->loop2_base_out;
			}
			else
			{
				*Size = mglobals->loop1_size_out;
				*Offset = mglobals->loop1_base_out;
			}
			*Size = checkLsize(*Size, mglobals->sample_bytes_out);
			(*Size) /= mglobals->sample_bytes_out;
			(*Offset) /= mglobals->sample_bytes_out;
		}
		else      //IN
		{
			if (Segment)
			{
				*Size = mglobals->loop2_size_in;
				*Offset = mglobals->loop2_base_in;
			}
			else
			{
				*Size = mglobals->loop1_size_in;
				*Offset = mglobals->loop1_base_in;
			}
			*Size = checkLsize(*Size, mglobals->sample_bytes_in);
			(*Size) /= mglobals->sample_bytes_in;
			(*Offset) /= mglobals->sample_bytes_in;
		}
	}
Error:
	if (mglobals) UnlockMB (mglobals->pbase_data);
	return status;
}


/*--------------------------------------------------------------------------*/
/* Switch mezzanine packet size                                             */
/*--------------------------------------------------------------------------*/
static ViStatus _VI_FUNC unmbase_m_packet_size_switch (ViSession mvi,
		ViUInt16 io,
		ViUInt32 Size)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = 0;
	ViUInt32 start, stop;
	mviChk(mvi, mglobals);
	notNMU(mglobals);
	SpyLog2("unmbase_m_packet_size_switch(%d, %d)", mglobals->mnum, Size);
//	mbusyChk(mvi, mglobals, io);	а вот мы можем в процессе менять характеристики!!!
	if (io)     //OUT
	{
		mglobals->next_sample_to_out = 0; //clear data to out pointer
		//store packet size
		mglobals->packet_size_out = Size;

		if (mglobals->mode_out == UNMBASE_MODE_LOOP)
		{
			//setup assigned RAM size
			ViUInt32 loop_size_out = checkLsize(mglobals->loop_size_out, mglobals->sample_bytes_out);
			start = (mglobals->membase_out + mglobals->loop_base_out) >> 8;             //for block address
			stop = start + (loop_size_out >> 8);      //for block address

			//setup packet size, i.e. IRQ at end of packet
			if (Size)
				errChk(LockOutSTARTSTOP(mglobals,
										rgLIMIT_OUT,
										(((Size * mglobals->sample_bytes_out) //size in bytes
										  + 255)                                              //up to full block
										 >> 8)));                                         //for block address
			else
				errChk(LockOutSTARTSTOP(mglobals,
										rgLIMIT_OUT,
										0x00FFFFFF));

			errChk(LockOutSTARTSTOP(mglobals,
									rgSTOP_OUT,
									stop));
			errChk(LockOutSTARTSTOP(mglobals,
									rgSTART_OUT,
									start));
		}
	}
	else      //IN
	{
		mglobals->next_sample_to_in = 0; //clear data to in pointer
		//store packet size
		mglobals->packet_size_in = Size;
		if (mglobals->mode_in == UNMBASE_MODE_LOOP)
		{
			//setup full assigned RAM size
			ViUInt32 loop_size_in = checkLsize(mglobals->loop_size_in, mglobals->sample_bytes_in);
			start = (mglobals->membase_in + mglobals->loop_base_in) >> 8;              //for block address
			stop = start + (loop_size_in >> 8);       //for block address

			//setup packet size, i.e. IRQ at end of packet
			if (Size)
				errChk(LockOutSTARTSTOP(mglobals,
										rgLIMIT_IN,
										(((Size * mglobals->sample_bytes_in) //size in bytes
										  + 255)                                              //up to full block
										 >> 8)));                                         //for block address
			else
				errChk(LockOutSTARTSTOP(mglobals,
										rgLIMIT_IN,
										0x00FFFFFF));

			errChk(LockOutSTARTSTOP(mglobals,
									rgSTOP_IN,
									stop));
			errChk(LockOutSTARTSTOP(mglobals,
									rgSTART_IN,
									start));
		}
	}
Error:
	if (mglobals)
		unmbase_ErrLed((PUserData)mglobals->pbase_data, status<0);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Switch mezzanine loop segment                                            */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_segment_switch (ViSession mvi,
		ViUInt16 io,
		ViUInt32 Segment,
		ViBoolean mode)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = 0;
	ViInt16 state;
	mviChk(mvi, mglobals);
	notNMU(mglobals);
	SpyLog3("unmbase_m_segment_switch(m%d, %d, %d)", mglobals->mnum, Segment, mode);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;

		vxiCmd.cmd = armvxiCmdD16(ARMCMD_MSEGSW,
								  Segment);
		vxiCmd.data0 = mode;
		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								io,
								&vxiCmd, VI_NULL);
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viPrintf(mglobals->basevi,
											"MSEGSW%d %c,%d,%d\n",
											mglobals->mnum, IOChar[io], Segment, mode));
	}
	else
	{
		if (io)     //OUT
		{
			mglobals->loop_seg_out = Segment;
			if (Segment)
			{
				mglobals->loop_size_out = mglobals->loop2_size_out;
				mglobals->loop_base_out = mglobals->loop2_base_out;
			}
			else
			{
				mglobals->loop_size_out = mglobals->loop1_size_out;
				mglobals->loop_base_out = mglobals->loop1_base_out;
			}
			if (mglobals->mode_out == UNMBASE_MODE_LOOP)
			{
				unmbase_m_state(mvi, io, &state);
				if (state == 1)  	//если процесс запущен, то переключение в зависимости от флага
				{
					if (mode)  	//ожидание завершения
					{
						Out32_COMM11(mglobals->basevi,
									 ~0,
									 1 << mglobals->midx);
					}
					else  	//немедленное переключение
					{
						;
					}
				}
				status = unmbase_m_packet_size_switch (mvi, io, mglobals->packet_size_out);	//install all sizes for loop mode
			}
		}
		else      //IN
		{
			mglobals->loop_seg_in = Segment;
			if (Segment)
			{
				mglobals->loop_size_in = mglobals->loop2_size_in;
				mglobals->loop_base_in = mglobals->loop2_base_in;
			}
			else
			{
				mglobals->loop_size_in = mglobals->loop1_size_in;
				mglobals->loop_base_in = mglobals->loop1_base_in;
			}
			if (mglobals->mode_in == UNMBASE_MODE_LOOP)
			{
				unmbase_m_state(mvi, io, &state);
				if (state == 1)  	//если процесс запущен, то переключение в зависимости от флага
				{
					if (mode)  	//ожидание завершения
					{
						Out32_COMM11(mglobals->basevi,
									 ~0,
									 1 << mglobals->midx);
					}
					else  	//немедленное переключение
					{
						;
					}
				}
				status = unmbase_m_packet_size_switch (mvi, io, mglobals->packet_size_in);	//install all sizes for loop mode
			}
		}
	}
Error:
	if (mglobals) UnlockMB (mglobals->pbase_data);
	return status;
}


/*--------------------------------------------------------------------------*/
/* Query current mezzanine loop segment                                     */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_segment_cur_q (ViSession mvi,
		ViUInt16 io,
		ViUInt32 *Segment)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = 0;
	mviChk(mvi, mglobals);
	notNMU(mglobals);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;

		vxiCmd.cmd = ARMCMD_MCURSEGq;

		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								io,
								&vxiCmd, &vxiAnsw);

		*Segment = vxiAnsw.data16;
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viQueryf(mglobals->basevi,
											"MCURSEG%d? %c\n",
											"%u",
											mglobals->mnum, IOChar[io],
											Segment));
		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
	}
	else
	{
		if (io)     //OUT
		{
			*Segment = mglobals->loop_seg_out;
		}
		else      //IN
		{
			*Segment = mglobals->loop_seg_in;
		}
	}
Error:
	if (mglobals) UnlockMB (mglobals->pbase_data);
	return status;
}


/*--------------------------------------------------------------------------*/
/* Set mezzanine packet size                                                */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_packet_size (ViSession mvi,
		ViUInt16 io,
		ViUInt32 Size)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = 0;
	ViUInt32 start, stop;
	mviChk(mvi, mglobals);
	notNMU(mglobals);
	SpyLog2("unmbase_m_packet_size(m%d, %d)", mglobals->mnum, Size);
//	mbusyChk(mvi, mglobals, io);	а вот мы можем в процессе менять характеристики!!!
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;

		vxiCmd.cmd = ARMCMD_MPSIZE;
		vxiCmd.data0 = Size;

		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								io,
								&vxiCmd, VI_NULL);
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viPrintf(mglobals->basevi,
											"MPSIZE%d %c,%d\n",
											mglobals->mnum, IOChar[io], Size));
	}
	else
	{
		if (io)     //OUT
		{
			//store packet size
			mglobals->packet_size_out = Size;
			if (mglobals->state_out <= 0)
			{
				mglobals->next_sample_to_out = 0; //clear data to out pointer
				if (mglobals->mode_out == UNMBASE_MODE_LOOP)
				{
					//setup assigned RAM size
					ViUInt32 loop_size_out = checkLsize(mglobals->loop_size_out, mglobals->sample_bytes_out);
					start = (mglobals->membase_out + mglobals->loop_base_out) >> 8;             //for block address
					stop = start + (loop_size_out >> 8);      //for block address
					//setup packet size, i.e. IRQ at end of packet
					if (Size)
						errChk(LockOutSTARTSTOP(mglobals,
												rgLIMIT_OUT,
												(((Size * mglobals->sample_bytes_out) //size in bytes
												  + 255)                                              //up to full block
												 >> 8)));                                         //for block address
					else
						errChk(LockOutSTARTSTOP(mglobals,
												rgLIMIT_OUT,
												0x00FFFFFF));

					errChk(LockOutSTARTSTOP(mglobals,
											rgSTOP_OUT,
											stop));
					errChk(LockOutSTARTSTOP(mglobals,
											rgSTART_OUT,
											start));
				}
			}
		}
		else      //IN
		{
			//store packet size
			mglobals->packet_size_in = Size;
			if (mglobals->state_in <= 0)
			{
				mglobals->next_sample_to_in = 0; //clear data to in pointer
				if (mglobals->mode_in == UNMBASE_MODE_LOOP)
				{
					//setup full assigned RAM size
					ViUInt32 loop_size_in = checkLsize(mglobals->loop_size_in, mglobals->sample_bytes_in);
					start = (mglobals->membase_in + mglobals->loop_base_in) >> 8;              //for block address
					stop = start + (loop_size_in >> 8);       //for block address
					//setup packet size, i.e. IRQ at end of packet
					if (Size)
						errChk(LockOutSTARTSTOP(mglobals,
												rgLIMIT_IN,
												(((Size * mglobals->sample_bytes_in)  //size in bytes
												  + 255)                                              //up to full block
												 >> 8)));                                         //for block address
					else
						errChk(LockOutSTARTSTOP(mglobals,
												rgLIMIT_IN,
												0x00FFFFFF));

					errChk(LockOutSTARTSTOP(mglobals,
											rgSTOP_IN,
											stop));
					errChk(LockOutSTARTSTOP(mglobals,
											rgSTART_IN,
											start));
				}
			}
		}
	}
Error:
	if (mglobals)
	{
		unmbase_ErrLed((PUserData)mglobals->pbase_data, status<0);
		UnlockMB (mglobals->pbase_data);
	}
	return status;
}

/*--------------------------------------------------------------------------*/
/* Query mezzanine packet size                                              */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_packet_size_q (ViSession mvi,
		ViUInt16 io,
		ViUInt32 *Size)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS;
	mviChk(mvi, mglobals);
	notNMU(mglobals);
	//return packet size
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;

		vxiCmd.cmd = ARMCMD_MPSIZEq;
		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								io,
								&vxiCmd, &vxiAnsw);

		*Size = vxiAnsw.data0;
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viQueryf(mglobals->basevi,
											"MPSIZE%d? %c\n",
											"%u",
											mglobals->mnum, IOChar[io],
											Size));
		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
	}
	else
	{
		*Size = io ? mglobals->packet_size_out : mglobals->packet_size_in;
	}
Error:
	if (mglobals) UnlockMB (mglobals->pbase_data);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Install user IRQ handler                                                 */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_handler (ViSession mvi,
		ViAddr Handler)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS;
	mviChk(mvi, mglobals);
	SpyLog2("unmbase_m_handler(m%d, handler 0x%08X)", mglobals->mnum, Handler);
	//store user handler
	mglobals->user_handler = Handler;
	return status;
}

//получение LastAddr с учетом возможных сбоев
static ViStatus GetLastOutAddr(PM_SESSION mglobals, ViUInt32 *lastaddr)
{
	ViStatus status=0;
	ViUInt32 oldincr, nRepeat = 5;
	ViUInt32 data[3];

	while (!status && nRepeat)
	{
		viGetAttribute(mglobals->basevi, VI_ATTR_SRC_INCREMENT, &oldincr);
		viSetAttribute(mglobals->basevi, VI_ATTR_SRC_INCREMENT, 0);

		status = viMoveIn32 (mglobals->basevi, VI_A24_SPACE,
							 rgCURRENT_OUT[mglobals->midx],
							 3,
							 data);
		viSetAttribute(mglobals->basevi, VI_ATTR_SRC_INCREMENT, oldincr);

		if (status < 0)
			break;

		data[0] = (data[0] & 0x00FFFFFF);
		data[1] = (data[1] & 0x00FFFFFF);
		data[2] = (data[2] & 0x00FFFFFF);

		if (data[2] == data[1] &&
				data[2] <= mglobals->saveRgSTOP_OUT &&
				data[2] >= mglobals->saveRgSTART_OUT)
		{
			*lastaddr = data[2];
			break;
		}
		else
			if (data[1] == data[0] &&
					data[1] <= mglobals->saveRgSTOP_OUT &&
					data[1] >= mglobals->saveRgSTART_OUT)
			{
				*lastaddr = data[1];
				break;
			}
		*lastaddr = data[2];

		SpyLog5("GetLastOutAddr mez%d %d get %08X, %08X, %08X!\n", mglobals->midx, 5-nRepeat, data[0], data[1], data[2]);

		nRepeat--;
	}
	if (!nRepeat)
		status = UNMBASE_ERROR_INSTR;
	return status;
}

//получение LastAddr с учетом возможных сбоев
static ViStatus GetLastInAddr(PM_SESSION mglobals, ViUInt32 *lastaddr)
{
	ViStatus status=0;
	ViUInt32 oldincr, nRepeat = 5;
	ViUInt32 data[3];

	while (!status && nRepeat)
	{
		viGetAttribute(mglobals->basevi, VI_ATTR_SRC_INCREMENT, &oldincr);
		viSetAttribute(mglobals->basevi, VI_ATTR_SRC_INCREMENT, 0);

		status = viMoveIn32 (mglobals->basevi, VI_A24_SPACE,
							 rgCURRENT_IN[mglobals->midx],
							 3,
							 data);
		viSetAttribute(mglobals->basevi, VI_ATTR_SRC_INCREMENT, oldincr);

		if (status < 0)
			break;

		data[0] = (data[0] & 0x00FFFFFF);
		data[1] = (data[1] & 0x00FFFFFF);
		data[2] = (data[2] & 0x00FFFFFF);

		if (data[2] == data[1] &&
				data[2] <= mglobals->saveRgSTOP_IN &&
				data[2] >= mglobals->saveRgSTART_IN)
		{
			*lastaddr = data[2];
			break;
		}
		else
			if (data[1] == data[0] &&
					data[1] <= mglobals->saveRgSTOP_IN &&
					data[1] >= mglobals->saveRgSTART_IN)
			{
				*lastaddr = data[1];
				break;
			}
		*lastaddr = data[2];

		SpyLog5("GetLastInAddr mez%d %d get %08X, %08X, %08X!\n", mglobals->midx, 5-nRepeat, data[0], data[1], data[2]);

		nRepeat--;
	}
	if (!nRepeat)
		status = UNMBASE_ERROR_INSTR;
	return status;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
ViStatus LogAllRegs(ViSession vi)
{
#define ALL_RS_NUM	((rgLIMIT_IN4+4-rgSTART_IN1)/4)
	ViStatus status=0;
	int i;
	ViUInt32 oldincr;
	ViUInt32 data[ALL_RS_NUM];

	viGetAttribute(vi, VI_ATTR_SRC_INCREMENT, &oldincr);
	viSetAttribute(vi, VI_ATTR_SRC_INCREMENT, 1);

	status = viMoveIn32 (vi, VI_A24_SPACE,
						rgSTART_IN1,
						ALL_RS_NUM,
						data);
	viSetAttribute(vi, VI_ATTR_SRC_INCREMENT, oldincr);

	if (status < 0)
		return status;

	for (i=0; i<ALL_RS_NUM; i++)
		data[i] = (data[i] & 0x00FFFFFF);

	SpyLog("All registers Start, Stop, Current, Limit\n");

	for (i=0; i<ALL_RS_NUM; i+=4)
	{
		SpyLog5("%d:%08X, %08X, %08X, %08X", i/4+1, data[i+0], data[i+1], data[i+2], data[i+3]);
	}
	status = viIn32 (vi, VI_A24_SPACE,
						rgSTAT1,
						data);
	SpyLog1("rgSTAT1=%08X\n", data[0]);

	status = viIn32 (vi, VI_A24_SPACE,
						rgSTAT2,
						data);
	SpyLog1("rgSTAT2=%08X\n", data[0]);

	status = viIn32 (vi, VI_A24_SPACE,
						rgSTAT2A,
						data);
	SpyLog1("rgSTAT2A=%08X\n", data[0]);

	return status;
}
*/

static ViStatus HowInPacket(PM_SESSION mglobals, ViUInt32 *howremain, ViUInt32 *addr1, ViUInt32 *size1, ViUInt32 *size2)
{
	ViUInt32 lastaddr, badbytes, loop_size_in, memsize_in=0x12345678;
	ViStatus status = 0;

	mglobalsChk(mglobals);
	*size1 = *size2 = 0;
	*howremain = mglobals->tmp_block_remain;
	//detect, where next free block (how blocks already in memory)

	//пытаемся читать хорошо...
	status = GetLastInAddr(mglobals, &lastaddr);
	if (UNMBASE_ERROR_INSTR == status)
	{
		lastaddr = ((lastaddr & 0x00FFFFFF) << 8) - mglobals->membase_in;
		goto LastAddrError;
	}
	errChk(status);

#ifdef CHECK_RGSTOP
	errChk( viIn32(mglobals->basevi, VI_A24_SPACE,
				   rgSTOP_IN[mglobals->midx],
				   &badbytes));
	badbytes &= 0x00FFFFFF;
	if (mglobals->saveRgSTOP_IN != badbytes)	//если не равно - читаем еще раз!
	{
		errChk( viIn32(mglobals->basevi, VI_A24_SPACE,
					   rgSTOP_IN[mglobals->midx],
					   &badbytes));
		badbytes &= 0x00FFFFFF;
	}
	if (mglobals->saveRgSTOP_IN != badbytes)
	{
		SpyLog4("m%d ERROR! RgSTOP changed from %08X to %08X (current lastaddr=%08X)!",
				mglobals->mnum,
				mglobals->saveRgSTOP_IN,
				badbytes,
				lastaddr);
		//LogAllRegs(mglobals->basevi);
		if (lastaddr >= mglobals->saveRgSTOP_IN)
		{
			ErrSpyLog("  Stop mezzanine!!!");
			unmbase_m_stop_in(mglobals);
			unmbase_ErrLed((PUserData)mglobals->pbase_data, 1);
			errChk(UNMBASE_ERROR_INSTR);
		}
		else
		{
			ErrSpyLog1("  Restore rgSTOP to %08X",
					   mglobals->saveRgSTOP_IN);
			errChk(LockOutSTARTSTOP(mglobals,
									rgSTOP_IN,
									mglobals->saveRgSTOP_IN));
		}
	}
#endif
	//корректируем для соответствия текущему RgSTOP, который могли переустановить !!!
	memsize_in = checkLsize(mglobals->memsize_in, mglobals->sample_bytes_in);

	lastaddr = ((lastaddr & 0x00FFFFFF) << 8) - mglobals->membase_in;

	if (lastaddr > memsize_in)
	{
		//ERROR! Current address don't back to start!!!
LastAddrError:
		//LogAllRegs(mglobals->basevi);
		unmbase_m_stop_in(mglobals);
		unmbase_ErrLed((PUserData)mglobals->pbase_data, 1);
		SpyLog4("m%d ERROR! lastoffs=%08X, membase_in=%08X, memsize_in=%08X)!",
				mglobals->mnum,
				lastaddr,
				mglobals->membase_in,
				memsize_in);
		lastaddr += mglobals->membase_in;
		lastaddr = lastaddr>>8;
		//viIn32(mglobals->basevi, VI_A24_SPACE,
		//			rgCURRENT_IN[mglobals->midx],
		//			&lastaddr);
		lastaddr &= 0x00FFFFFF;
		viIn32(mglobals->basevi, VI_A24_SPACE,
			   rgSTOP_IN[mglobals->midx],
			   &badbytes);
		badbytes &= 0x00FFFFFF;

		ErrSpyLog3("m%d ERROR! Current pointer (%08X) go above end limit(%08X)!",
				   mglobals->mnum,
				   lastaddr,
				   badbytes);
		errChk(UNMBASE_ERROR_INSTR);
	}
	//Detect segment
	if ((lastaddr >= mglobals->loop_base_in) &&
			(lastaddr < mglobals->loop_base_in + checkLsize(mglobals->loop_size_in, mglobals->sample_bytes_in)))
	{
		//This is current segment
		lastaddr -=  mglobals->loop_base_in;     //convert to mezzanine memory pointer
		loop_size_in = mglobals->loop_size_in;

	}
	else
	if  ((lastaddr >= mglobals->loop1_base_in) &&
			  (lastaddr < mglobals->loop1_base_in + checkLsize(mglobals->loop1_size_in, mglobals->sample_bytes_in)))
	{
		//This is segment 1
		lastaddr -=  mglobals->loop1_base_in;     //convert to mezzanine memory pointer
		loop_size_in = mglobals->loop1_size_in;
	}
	else
	{
		//This is segment 2
		lastaddr -=  mglobals->loop2_base_in;     //convert to mezzanine memory pointer
		loop_size_in = mglobals->loop2_size_in;
	}

	loop_size_in = checkLsize(loop_size_in, mglobals->sample_bytes_in);

	*addr1 = mglobals->next_sample_to_in;

	if (lastaddr < *addr1)     //we have data at first up to memory end
	{

		*size1 = loop_size_in - *addr1;

		if (0x80000000 & *size1)
			*size1 = 0;		//если перешли через границу

		*size2 = lastaddr;
	}
	else
	if (lastaddr > mglobals->next_sample_to_in)      //all we need from next_sample_to_in to lastaddr
	{
		*size1 = lastaddr - mglobals->next_sample_to_in;
	}
	else
		;     //no more data ready


	if (*size1)
	{
		if (*size1 > *howremain)
		{
			(*size1) -= *howremain;
			(*addr1) += *howremain;
		}
		else
		{
			*size1 = 0;
		}
	}
	badbytes = (*howremain + *size1 + *size2) % mglobals->sample_bytes_in;      //how much bytes not in-sample
	//delete badbytes
	if (badbytes && *size2)
	{
		if (badbytes >= *size2)
		{
			badbytes -= *size2;
			*size2 = 0;
		}
		else
		{
			(*size2) -= badbytes;
			badbytes = 0;
		}
	}
	if (badbytes && *size1)
	{
		if (badbytes >= *size1)
		{
			badbytes -= *size1;
			*size1 = 0;
		}
		else
		{
			(*size1) -= badbytes;
			badbytes = 0;
		}
	}
	if (badbytes && *howremain)
	{
		if (badbytes >= *howremain)
		{
			badbytes -= *howremain;
			*howremain = 0;
		}
		else
		{
			(*howremain) -= badbytes;
			badbytes = 0;
		}
	}
Error:
	return status;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static ViStatus HowInLastPacket(PM_SESSION mglobals, ViUInt32 size, ViUInt32 *addr1, ViUInt32 *size1, ViUInt32 *size2)
{
	ViStatus status = 0;
	mglobalsChk(mglobals);
	*size2 = *size1 = 0;
	//detect, where next free block (how blocks already in memory)
	//пытаемся читать хорошо...
	errChk(GetLastInAddr(mglobals, addr1));
	//lastaddr - next free block address
	*addr1 = ((*addr1) << 8) - mglobals->membase_in - mglobals->loop_base_in;      //convert to mezzanine memory pointer

	(*addr1) -= (*addr1) % mglobals->sample_bytes_in;				//align to sample

	*size1 = checkLsize(mglobals->loop_size_in, mglobals->sample_bytes_in) - *addr1;

	*size2 = *addr1;


	if (size < *size2)
	{
		*addr1 = (*size2 - size);
		*size1 = size;
		*size2 = 0;
	}
	else
	{
		size -= *size2;
		if (size < *size1)
		{
			(*addr1) += (*size1 - size);
			*size1 = size;
		}
	}

Error:
	return status;
}

/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_howmuch_data_q (ViSession mvi,
		ViUInt16 io,
		ViUInt32 *howmuch)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = 0;
	ViUInt32 lastaddr, word;
	ViUInt32 howremain, addr1, size1, size2, loop_size_out;
	ViInt16 state;
	mviChk(mvi, mglobals);
	notNMU(mglobals);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;

		vxiCmd.cmd = ARMCMD_MHOWDATAq;
		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								io,
								&vxiCmd, &vxiAnsw);

		*howmuch = vxiAnsw.data0;
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		//MB Time = 1.4 ms
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viQueryf(mglobals->basevi,
											"MHOWDATA%d? %c\n",
											"%u",
											mglobals->mnum, IOChar[io],
											howmuch));
		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);

	}
	else
	{
		*howmuch = 0;
		if (io)     //OUT
		{
			//lastaddr - next free block address
			if (mglobals->mode_out == UNMBASE_MODE_LOOP)
			{

				loop_size_out = checkLsize(mglobals->loop_size_out, mglobals->sample_bytes_out);

				//detect, where next free block (how blocks already in memory)
				if (!mglobals->state_out)	//if idle, free up to memory end
				{
					lastaddr = loop_size_out;
				}
				else
				{
					errChk(GetLastOutAddr(mglobals, &lastaddr));	//пытаемся читать хорошо...

					lastaddr = (lastaddr << 8) - mglobals->membase_out;
				}

				//Detect segment
				if ((lastaddr >= mglobals->loop_base_out) &&
						(lastaddr < mglobals->loop_base_out + loop_size_out))
				{
					//This is current segment
					lastaddr -=  mglobals->loop_base_out;     //convert to mezzanine memory pointer
					if (lastaddr < mglobals->next_sample_to_out)    //we have data at first up to memory end
					{

						*howmuch = loop_size_out - mglobals->next_sample_to_out + lastaddr;

					}
					else
					if (lastaddr > mglobals->next_sample_to_out)     //all we need from next_sample_to_out to lastaddr
					{

						*howmuch = lastaddr - mglobals->next_sample_to_out;

					}
					else
						;     //no more data ready
				}
				else
				if  ((lastaddr >= mglobals->loop1_base_out) &&
						  (lastaddr < mglobals->loop1_base_out + mglobals->loop1_size_out))
				{
					//This is segment 1
					lastaddr -=  mglobals->loop1_base_out;     //convert to mezzanine memory pointer
					if (lastaddr < mglobals->next_sample_to_out)    //we have data at first up to memory end
					{

						*howmuch = mglobals->loop1_size_out - mglobals->next_sample_to_out + lastaddr;

					}
					else
					if (lastaddr > mglobals->next_sample_to_out)     //all we need from next_sample_to_out to lastaddr
					{

						*howmuch = lastaddr - mglobals->next_sample_to_out;

					}
					else
						;     //no more data ready
				}
				else
				{
					//This is segment 2
					lastaddr -=  mglobals->loop2_base_out;     //convert to mezzanine memory pointer
					if (lastaddr < mglobals->next_sample_to_out)    //we have data at first up to memory end
					{

						*howmuch = mglobals->loop2_size_out - mglobals->next_sample_to_out + lastaddr;

					}
					else
					if (lastaddr > mglobals->next_sample_to_out)     //all we need from next_sample_to_out to lastaddr
					{

						*howmuch = lastaddr - mglobals->next_sample_to_out;

					}
					else
						;     //no more data ready
				}
				(*howmuch) /= mglobals->sample_bytes_out;     //how much bytes not in-sample
				okChk(VI_SUCCESS);
			}
			else
			if (mglobals->mode_out == UNMBASE_MODE_BLOCK)
			{
				//detect, where next free block (how blocks already in memory)
				//пытаемся читать хорошо...
				errChk(GetLastOutAddr(mglobals, &lastaddr));
				lastaddr = (lastaddr << 8) -
							(mglobals->membase_out +
							 mglobals->subblock_base_out  * mglobals->sample_bytes_out); //convert to mezzanine memory pointer
				if (lastaddr == 0)      //May be already reach end of block?
				{
					errChk(unmbase_m_state (mvi, 0, &state));
					if (state == 0) //Yes, we transfer all
						lastaddr = mglobals->subblock_size_out * mglobals->sample_bytes_out;//???sample_words_out;
				}
				*howmuch = lastaddr / mglobals->sample_bytes_out;//???sample_words_out; //to samples size
			}
			else      //SINGLE, only check if process finished
			{
				errChk( viIn32(mglobals->basevi, VI_A24_SPACE,
							   rgSTAT1,
							   &word));
				if ((word & maskSTAT1_OUT_ON[mglobals->midx]) == 0)
					*howmuch = 1;
			}
		}
		else      //IN
		{
			if (mglobals->mode_in == UNMBASE_MODE_LOOP)
			{
				//not mean, running or not, simple read up to end of received data
				errChk(HowInPacket(mglobals, &howremain, &addr1, &size1, &size2));
				*howmuch = (howremain + size1 + size2) / mglobals->sample_bytes_in;
				okChk(VI_SUCCESS);
			}
			else
			if (mglobals->mode_in == UNMBASE_MODE_BLOCK)
			{
				if (mglobals->state_in)     //if running
				{
					//пытаемся читать хорошо...
					errChk(GetLastInAddr(mglobals, &lastaddr));
					lastaddr = (lastaddr << 8) -
							(mglobals->membase_in +
							 mglobals->subblock_base_in  * mglobals->sample_bytes_in); //convert to mezzanine memory pointer
					if (lastaddr == 0)      //May be already reach end of block?
					{
						errChk(unmbase_m_state (mvi, 0, &state));
						if (state == 0) //Yes, we transfer all
							lastaddr = mglobals->subblock_size_in * mglobals->sample_bytes_in;//???sample_words_in;
					}
					*howmuch = lastaddr / mglobals->sample_bytes_in;//???sample_words_in;   //to samples size
				}
				else      //may be finished
				{
					*howmuch = mglobals->subblock_size_in;
				}
			}
			else      //SINGLE, only check if process finished
			{
				if (mglobals->state_in)     //if running
				{
					errChk( viIn32(mglobals->basevi, VI_A24_SPACE,
								   rgSTAT1,
								   &word));
					if ((word & maskSTAT1_IN_ON[mglobals->midx]) == 0)
						*howmuch = 1;
				}
				else  //may be finished
					*howmuch = 1;
			}
		}
	}
Error:
	if (mglobals)
	{
		SpyLog2("unmbase_m_howmuch_data_q(m%d, %d samples ready)", mglobals->mnum, *howmuch);

		unmbase_ErrLed((PUserData)mglobals->pbase_data, status<0);
		UnlockMB (mglobals->pbase_data);
	}
	return status;
}

/*--------------------------------------------------------------------------*/
/* Read Last Sample                                                         */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_read_last (ViSession mvi,
		ViUInt32 *Buff,
		ViUInt32 *firstTime,
		ViUInt32 *thisTime)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = 0;
	ViUInt32 prevtime, oldincr;
	ViUInt32 tmptime1, tmptime2;

	mviChk(mvi, mglobals);
	notNMU(mglobals);
	SpyLog1("unmbase_m_read_last(%d)", mglobals->midx);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;

		//в ответе на данную команду: size, firstTime, thisTime
		vxiCmd.cmd = ARMCMD_MLASTSAMPq;
		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCK, ARMVXI_TMO1,
								0,
								&vxiCmd, &vxiAnsw);

		if (status >= 0 &&
			Buff &&
			vxiAnsw.data0)
		{
			status = armvxi_mez_readbuf(mglobals,
							0,
							Buff,
							vxiAnsw.data0);
		}
		UnlockARM(mglobals->pbase_data, mglobals->midx > 1);

		if (firstTime)
			*firstTime = vxiAnsw.data1;
		if (thisTime)
			*thisTime = vxiAnsw.data2;


		okChk(status);
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		ViChar tmpbuff[32];
		ViUInt32 cnt;
		if (!firstTime)
			firstTime = &tmptime1;
		if (!thisTime)
			thisTime = &tmptime2;
		LockMB(mglobals->pbase_data);

		errChkMB(mglobals->basevi, viPrintf (mglobals->basevi,
											 "MLASTSAMP%d?\n",
											 mglobals->mnum));
		errChkMB(mglobals->basevi, viScanf(mglobals->basevi,
										   "%d,%d,",
										   firstTime, thisTime));

		errChkMB(mglobals->basevi, viBufRead (mglobals->basevi, (ViPBuf)tmpbuff, 2, &cnt));
		if ((cnt != 2) || (*tmpbuff != '#'))
			errChk(UNMBASE_ERROR_INSTR);
		errChkMB(mglobals->basevi, viBufRead (mglobals->basevi, (ViPBuf)tmpbuff, tmpbuff[1] - '0', &cnt));
		tmpbuff[cnt] = 0;
		cnt = atoi(tmpbuff);
		errChkMB(mglobals->basevi, viBufRead (mglobals->basevi, (ViPBuf)Buff, cnt, &cnt));
		if (mglobals->baseBE)
			mem_swap32(Buff, cnt);

		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
		okChk(VI_SUCCESS);
	}
	//if have no any samples NOW WE DO NOT KNOW THIS!
	//  errChk(UNMBASE_ERROR_NODATA);

	prevtime = mglobals->last_time;

//На время чтения блокировка
	errChk(LockLastData(mglobals->pbase_data));

	if (0 == mglobals->dontLockLastData)
	{
		status = Out32_COMM2(mglobals->basevi,
							 ~0,
							 maskCOMM2_LAST_ALL_DIS);
	}

	//read last sample to mglobals->last_sample, last time to mglobals->last_time;
	errChk(viLock(mglobals->basevi, VI_EXCLUSIVE_LOCK, 10000, NULL, NULL));

	viGetAttribute(mglobals->basevi, VI_ATTR_SRC_INCREMENT, &oldincr);
	viSetAttribute(mglobals->basevi, VI_ATTR_SRC_INCREMENT, 0);

	status = viMoveIn32 (mglobals->basevi, VI_A24_SPACE,
						 rgLASTDATA_IN[mglobals->midx],
						 mglobals->sample_words_in + 2, //+2 for firsttime and lasttime
						 mglobals->last_sample);

	viSetAttribute(mglobals->basevi, VI_ATTR_SRC_INCREMENT, oldincr);

	viUnlock(mglobals->basevi);
	UnlockLastData(mglobals->pbase_data);

	errChk(status);

	mglobals->first_time = mglobals->last_sample[mglobals->sample_words_in+1];  //move firsttime to our real location
	mglobals->last_time = mglobals->last_sample[mglobals->sample_words_in]; //move lasttime to our real location

	if (Buff)
		memcpy((ViAddr)Buff, (ViAddr)mglobals->last_sample, mglobals->sample_bytes_in);
	if (thisTime)
		*thisTime = mglobals->last_time;
	if (firstTime)
		*firstTime = mglobals->first_time;

	if (prevtime == mglobals->last_time)    //previous sample are with the same timestamp!
		return UNMBASE_WARN_REREADED;
Error:
	if (mglobals)
	{
		unmbase_ErrLed((PUserData)mglobals->pbase_data, status<0);
		UnlockMB (mglobals->pbase_data);
	}
	return status;
}

/*--------------------------------------------------------------------------*/
/* Read Data Array                                                          */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_read_block (ViSession mvi,
		ViUInt32 Idx,
		ViUInt32 NSamples,
		ViUInt32 Buff[])
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS;
	mviChk(mvi, mglobals);
	notNMU(mglobals);

	SpyLog3("unmbase_m_read_block(m%d, %d from %d)", mglobals->mnum, NSamples, Idx);

	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM TODO
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;
		ViUInt32 cnt, armIdx;

		armIdx = mglobals->midx > 1 ? 1 : 0;

		if (!mglobals->sample_bytes_in)  	//если мы вошли без сброса и хотим что-то узнать про размер пакета
		{
			vxiCmd.cmd = ARMCMD_MSWIDTHq;
			status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
									0,
									&vxiCmd, &vxiAnsw);

			mglobals->sample_bytes_in = vxiAnsw.data0 * sizeof(ViUInt32);

		}
		//Для оптимизации чтения будем читать не более 999900 байт!
		do
		{
			ViUInt32 nsamples, bytes;

			bytes = NSamples * mglobals->sample_bytes_in;
			if (bytes > 999900)
			{
				nsamples = 999900 / mglobals->sample_bytes_in;
				while (0x3 & (nsamples * mglobals->sample_bytes_in))	//заодно выровняем
					nsamples--;
			}
			else
				nsamples = NSamples;

			vxiCmd.cmd = ARMCMD_MRDBLKq | armvxiMidxIoMask(mglobals->midx, 0);
			vxiCmd.data0 = Idx;
			vxiCmd.data1 = nsamples;

			errChk(armvxi_bread_cmd(mglobals->pbase_data,
									ARMVXI_LOCKUNLOCK,
									armIdx,
									&vxiCmd,
									&vxiAnsw,
									nsamples * mglobals->sample_bytes_in,		//max number of bytes
									(ViUInt8*)Buff,
									&cnt));	//количество реально прочитанных байт

			cnt = vxiAnsw.data0;
			//nsamples = cnt / mglobals->sample_bytes_in
			NSamples -= nsamples;
			if (NSamples)
			{
				ViUInt8 *buf8 = ((ViUInt8*)Buff) + nsamples * mglobals->sample_bytes_in;
				Buff = (ViUInt32*)buf8;
				Idx += nsamples;
			}
		}
		while (NSamples);

		okChk(VI_SUCCESS);
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		ViChar tmpbuff[32];
		ViUInt32 cnt;

		if (!mglobals->sample_bytes_in)  	//если мы вошли без сброса и хотим что-то узнать про размер пакета
		{
			LockMB(mglobals->pbase_data);
			errChkMB(mglobals->basevi, viQueryf(mglobals->basevi,
												"MSWIDTH%d? I\n",
												"%u",
												mglobals->mnum,
												&mglobals->sample_bytes_in));
			UnlockMB (mglobals->pbase_data);
			mglobals->sample_bytes_in *= sizeof(ViUInt32);

		}
		//Для оптимизации чтения будем читать не более 999900 байт!
		do
		{
			ViUInt32 nsamples, bytes;

			bytes = NSamples * mglobals->sample_bytes_in;
			if (bytes > 999900)
			{
				nsamples = 999900 / mglobals->sample_bytes_in;
				while (0x3 & (nsamples * mglobals->sample_bytes_in))	//заодно выровняем
					nsamples--;
			}
			else
				nsamples = NSamples;

			LockMB(mglobals->pbase_data);
			errChkMB(mglobals->basevi, viPrintf (mglobals->basevi,
												 "MRDBLK%d? %d,%d\n",
												 mglobals->mnum, Idx, nsamples));
			errChkMB(mglobals->basevi, viBufRead (mglobals->basevi, (ViPBuf)tmpbuff, 2, &cnt));
			if ((cnt != 2) || (*tmpbuff != '#'))
				errChk(UNMBASE_ERROR_INSTR);
			errChkMB(mglobals->basevi, viBufRead (mglobals->basevi, (ViPBuf)tmpbuff, tmpbuff[1] - '0', &cnt));
			tmpbuff[cnt] = 0;
			cnt = atoi(tmpbuff);
			errChkMB(mglobals->basevi, viBufRead (mglobals->basevi, (ViPBuf)Buff, cnt, &cnt));
			if (mglobals->baseBE)
				mem_swap32(Buff, cnt);

			NSamples -= nsamples;
			if (NSamples)
			{
				ViUInt8 *buf8 = ((ViUInt8*)Buff) + nsamples * mglobals->sample_bytes_in;
				Buff = (ViUInt32*)buf8;
				Idx += nsamples;

				UnlockMB (mglobals->pbase_data);
			}
		}
		while (NSamples);


		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
		okChk(VI_SUCCESS);
	}

	unmbase_ErrLed((PUserData)mglobals->pbase_data, 0);
	errChk ( m_data_read(mglobals,
						 Idx * mglobals->sample_bytes_in,    //base memory byte index
						 NSamples * mglobals->sample_bytes_in,                   //byte size
						 (ViUInt8*)Buff));
Error:
	if (mglobals) UnlockMB (mglobals->pbase_data);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Write Data Array                                                         */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_write_block (ViSession mvi,
		ViUInt32 Idx,
		ViUInt32 NSamples,
		ViUInt32 Buff[])
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS;
	mviChk(mvi, mglobals);
	notNMU(mglobals);
	SpyLog3("unmbase_m_write_block(m%d, %d to %d)", mglobals->mnum, NSamples, Idx);

	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM TODO
		VXI_CMD vxiCmd;
		ViUInt32 armIdx;

		armIdx = mglobals->midx > 1 ? 1 : 0;

		vxiCmd.cmd = ARMCMD_MWRBLK | armvxiMidxIoMask(mglobals->midx, 1);
		vxiCmd.data0 = Idx;
		vxiCmd.data1 = NSamples;

		errChk(armvxi_bwrite_cmd(mglobals->pbase_data,
								ARMVXI_LOCKUNLOCK,
								armIdx,
								&vxiCmd,
								NSamples * mglobals->sample_bytes_out,		//max number of bytes
								(ViUInt8*)Buff));
		okChk(VI_SUCCESS);
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		ViChar tmpbuff[96], *tmpbuffptr;
		ViUInt32 N, cnt, digits;

		//готовим для передачи выровненныый блок данных 488.2 Arbitrary Length Binary Block
		N = NSamples * mglobals->sample_bytes_out;
		sprintf(tmpbuff, "%d", N);	//byte size
		digits = strlen(tmpbuff);
		sprintf(tmpbuff, "MWRBLK%d %d,%d,",
				mglobals->mnum,
				Idx,
				NSamples);
		cnt = strlen(tmpbuff);
		tmpbuffptr = &tmpbuff[cnt];
		//общее количество передаваемых байт команды до начала данных = digits + cnt + 2 (это "#n")
		cnt += digits+2;
		while (cnt&3)
		{
			*tmpbuffptr++ = ' ';	//выравниваем при помощи пробелов
			cnt++;
		}
		sprintf(tmpbuffptr, "#%d%d",
				digits, N);

		LockMB(mglobals->pbase_data);

		errChkMB(mglobals->basevi, viBufWrite (mglobals->basevi, (ViPBuf)tmpbuff, cnt, VI_NULL));

		if (mglobals->baseBE)
		{
			void *swapbuf = malloc(N);
			if (!swapbuf)
				errChk(VI_ERROR_ALLOC);

			memcpy_swap32(swapbuf, Buff, N);
			status = viBufWrite (mglobals->basevi, (ViPBuf)swapbuf, N, &cnt);
			free(swapbuf);
			errChkMB(mglobals->basevi, status);
		}
		else
			errChkMB(mglobals->basevi, viBufWrite (mglobals->basevi, (ViPBuf)Buff, N, &cnt));

		errChkMB(mglobals->basevi, viFlush (mglobals->basevi, VI_WRITE_BUF));
		okChk(VI_SUCCESS);
	}
	unmbase_ErrLed((PUserData)mglobals->pbase_data, 0);
	errChk ( m_data_write(mglobals,
						  Idx * mglobals->sample_bytes_out,   //base memory byte index
						  NSamples * mglobals->sample_bytes_out,                  //byte size
						  (ViUInt8*)Buff));
Error:
	if (mglobals) UnlockMB(mglobals->pbase_data);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Read Data Array from Segment                                             */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_read_segment (ViSession mvi,
		ViUInt16 io,
		ViUInt32 Segment,
		ViUInt32 Idx,
		ViUInt32 NSamples,
		ViUInt32 Buff[])
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS;
	ViUInt32 offs, size;
	mviChk(mvi, mglobals);
	notNMU(mglobals);
	SpyLog4("unmbase_m_read_segment(m%d, s%d, %d from %d)", mglobals->mnum, Segment, NSamples, Idx);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM TODO
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;
		ViUInt32 cnt, armIdx;

		armIdx = mglobals->midx > 1 ? 1 : 0;

		if (!mglobals->sample_bytes_in)  	//если мы вошли без сброса и хотим что-то узнать про размер пакета
		{
			vxiCmd.cmd = ARMCMD_MSWIDTHq;
			status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
									0,
									&vxiCmd, &vxiAnsw);

			mglobals->sample_bytes_in = vxiAnsw.data0 * sizeof(ViUInt32);

		}
		//Для оптимизации чтения будем читать не более 999900 байт!
		do
		{
			ViUInt32 nsamples, bytes;

			bytes = NSamples * mglobals->sample_bytes_in;
			if (bytes > 999900)
			{
				nsamples = 999900 / mglobals->sample_bytes_in;
				while (0x3 & (nsamples * mglobals->sample_bytes_in))	//заодно выровняем
					nsamples--;
			}
			else
				nsamples = NSamples;

			vxiCmd.cmd = armvxiCmdD16(ARMCMD_MRDSEGq | armvxiMidxIoMask(mglobals->midx, 0),
									  Segment);
			vxiCmd.data0 = Idx;
			vxiCmd.data1 = nsamples;

			errChk(armvxi_bread_cmd(mglobals->pbase_data,
									ARMVXI_LOCKUNLOCK,
									armIdx,
									&vxiCmd,
									&vxiAnsw,
									nsamples * mglobals->sample_bytes_in,		//max number of bytes
									(ViUInt8*)Buff,
									&cnt));	//количество реально прочитанных байт

			cnt = vxiAnsw.data0;
			//nsamples = cnt / mglobals->sample_bytes_in
			NSamples -= nsamples;
			if (NSamples)
			{
				ViUInt8 *buf8 = ((ViUInt8*)Buff) + nsamples * mglobals->sample_bytes_in;
				Buff = (ViUInt32*)buf8;
				Idx += nsamples;
			}
		}
		while (NSamples);

		okChk(VI_SUCCESS);
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		ViChar tmpbuff[32];
		ViUInt32 cnt;


		if (!mglobals->sample_bytes_in)  	//если мы вошли без сброса и хотим что-то узнать про размер пакета
		{
			LockMB(mglobals->pbase_data);
			errChkMB(mglobals->basevi, viQueryf(mglobals->basevi,
												"MSWIDTH%d? I\n",
												"%u",
												mglobals->mnum,
												&mglobals->sample_bytes_in));
			UnlockMB (mglobals->pbase_data);
			mglobals->sample_bytes_in *= sizeof(ViUInt32);

		}
		//Для оптимизации чтения будем читать не более 999900 байт!
		do
		{
			ViUInt32 nsamples, bytes;

			bytes = NSamples * mglobals->sample_bytes_in;
			if (bytes > 999900)
			{
				nsamples = 999900 / mglobals->sample_bytes_in;
				while (0x3 & (nsamples * mglobals->sample_bytes_in))	//заодно выровняем
					nsamples--;
			}
			else
				nsamples = NSamples;

			LockMB(mglobals->pbase_data);
			errChkMB(mglobals->basevi, viPrintf (mglobals->basevi,
												 "MRDSEG%d? %c,%d,%d,%d\n",
												 mglobals->mnum, IOChar[io], Segment, Idx, nsamples));
			errChkMB(mglobals->basevi, viBufRead (mglobals->basevi, (ViPBuf)tmpbuff, 2, &cnt));
			if ((cnt != 2) || (*tmpbuff != '#'))
				errChk(UNMBASE_ERROR_INSTR);
			errChkMB(mglobals->basevi, viBufRead (mglobals->basevi, (ViPBuf)tmpbuff, tmpbuff[1] - '0', &cnt));
			tmpbuff[cnt] = 0;
			cnt = atoi(tmpbuff);
			errChkMB(mglobals->basevi, viBufRead (mglobals->basevi, (ViPBuf)Buff, cnt, &cnt));
			if (mglobals->baseBE)
				mem_swap32(Buff, cnt);

			NSamples -= nsamples;
			if (NSamples)
			{
				ViUInt8 *buf8 = ((ViUInt8*)Buff) + nsamples * mglobals->sample_bytes_in;
				Buff = (ViUInt32*)buf8;
				Idx += nsamples;

				UnlockMB (mglobals->pbase_data);
			}
		}
		while (NSamples);

		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
		okChk(VI_SUCCESS);
	}
	unmbase_ErrLed((PUserData)mglobals->pbase_data, 0);
	if (io)
	{
		if (Segment)
			offs = mglobals->loop2_base_out;
		else
			offs = mglobals->loop1_base_out;
		offs += Idx * mglobals->sample_bytes_out;			//base memory byte index
		size = NSamples * mglobals->sample_bytes_out;		//byte size
	}
	else
	{
		if (Segment)
			offs = mglobals->loop2_base_in;
		else
			offs = mglobals->loop1_base_in;
		offs += Idx * mglobals->sample_bytes_in;			//base memory byte index
		size = NSamples * mglobals->sample_bytes_in;		//byte size
	}
	errChk ( m_data_read(mglobals,
						 offs,
						 size,
						 (ViUInt8*)Buff));
Error:
	if (mglobals) UnlockMB (mglobals->pbase_data);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Write Data Array to Segment                                              */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_write_segment (ViSession mvi,
		ViUInt16 io,
		ViUInt32 Segment,
		ViUInt32 Idx,
		ViUInt32 NSamples,
		ViUInt32 Buff[])
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS;
	ViUInt32 offs, size;
	mviChk(mvi, mglobals);
	notNMU(mglobals);
	SpyLog4("unmbase_m_write_segment(m%d, s%d, %d to %d)", mglobals->mnum, Segment, NSamples, Idx);

	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM TODO
		VXI_CMD vxiCmd;
		ViUInt32 armIdx;

		armIdx = mglobals->midx > 1 ? 1 : 0;

		vxiCmd.cmd = armvxiCmdD16(ARMCMD_MWRSEG | armvxiMidxIoMask(mglobals->midx, 1),
								  Segment);
		vxiCmd.data0 = Idx;
		vxiCmd.data1 = NSamples;

		errChk(armvxi_bwrite_cmd(mglobals->pbase_data,
								ARMVXI_LOCKUNLOCK,
								armIdx,
								&vxiCmd,
								NSamples * mglobals->sample_bytes_out,		//max number of bytes
								(ViUInt8*)Buff));
		okChk(VI_SUCCESS);
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		ViChar tmpbuff[96], *tmpbuffptr;
		ViUInt32 N, cnt, digits;

		//готовим для передачи выровненныый блок данных 488.2 Arbitrary Length Binary Block
		N = NSamples * (io ? mglobals->sample_bytes_out : mglobals->sample_bytes_in);
		sprintf(tmpbuff, "%d", N);	//byte size
		digits = strlen(tmpbuff);
		sprintf(tmpbuff, "MWRSEG%d %c,%d,%d,%d,",
				mglobals->mnum, IOChar[io], Segment, Idx, NSamples);
		cnt = strlen(tmpbuff);
		tmpbuffptr = &tmpbuff[cnt];
		//общее количество передаваемых байт команды до начала данных = digits + cnt + 2 (это "#n")
		cnt += digits+2;
		while (cnt&3)
		{
			*tmpbuffptr++ = ' ';	//выравниваем при помощи пробелов
			cnt++;
		}
		sprintf(tmpbuffptr, "#%d%d",
				digits, N);

		LockMB(mglobals->pbase_data);

		errChkMB(mglobals->basevi, viBufWrite (mglobals->basevi, (ViPBuf)tmpbuff, cnt, VI_NULL));

		if (mglobals->baseBE)
		{
			void *swapbuf = malloc(N);
			if (!swapbuf)
				errChk(VI_ERROR_ALLOC);

			memcpy_swap32(swapbuf, Buff, N);
			status = viBufWrite (mglobals->basevi, (ViPBuf)swapbuf, N, &cnt);
			free(swapbuf);
			errChkMB(mglobals->basevi, status);
		}
		else
			errChkMB(mglobals->basevi, viBufWrite (mglobals->basevi, (ViPBuf)Buff, N, &cnt));

		errChkMB(mglobals->basevi, viFlush (mglobals->basevi, VI_WRITE_BUF));
		okChk(VI_SUCCESS);
	}
	unmbase_ErrLed((PUserData)mglobals->pbase_data, 0);
	if (io)
	{
		if (Segment)
			offs = mglobals->loop2_base_out;
		else
			offs = mglobals->loop1_base_out;
		offs += Idx * mglobals->sample_bytes_out;			//base memory byte index
		size = NSamples * mglobals->sample_bytes_out;		//byte size
	}
	else
	{
		if (Segment)
			offs = mglobals->loop2_base_in;
		else
			offs = mglobals->loop1_base_in;
		offs += Idx * mglobals->sample_bytes_in;			//base memory byte index
		size = NSamples * mglobals->sample_bytes_in;		//byte size
	}
	errChk ( m_data_write(mglobals,
						  offs,
						  size,
						  (ViUInt8*)Buff));
Error:
	if (mglobals) UnlockMB(mglobals->pbase_data);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Read next ready samples when cycle mode run                              */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_read_packet (ViSession mvi,
		ViUInt32 NSamples,
		ViUInt32 Buff[],
		ViUInt32 *ReadNSamples)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = 0;
	ViUInt32 needNSamples = NSamples;
	mviChk(mvi, mglobals);
	notNMU(mglobals);

	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM TODO
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;
		ViUInt32 cnt, armIdx;

		armIdx = mglobals->midx > 1 ? 1 : 0;

		*ReadNSamples = 0;

		//Для оптимизации чтения будем читать не более 999900 байт!
		do
		{
			ViUInt32 nsamples, bytes;

			bytes = NSamples * mglobals->sample_bytes_in;
			if (bytes > 999900)
			{
				nsamples = 999900 / mglobals->sample_bytes_in;
				while (0x3 & (nsamples * mglobals->sample_bytes_in))	//заодно выровняем
					nsamples--;
			}
			else
				nsamples = NSamples;

			vxiCmd.cmd = ARMCMD_MRDPACKq | armvxiMidxIoMask(mglobals->midx, 0);
			vxiCmd.data0 = nsamples;

			errChk(armvxi_bread_cmd(mglobals->pbase_data,
									ARMVXI_LOCKUNLOCK,
									armIdx,
									&vxiCmd,
									&vxiAnsw,
									nsamples * mglobals->sample_bytes_in,		//max number of bytes
									(ViUInt8*)Buff,
									&cnt));	//количество реально прочитанных байт


			SpyLog6("unmbase_m_read_packet(m%d Arm cmd[x%08X,%d], answ[x%08X,%d], cnt=%d", 
						mglobals->mnum,
						vxiCmd.cmd, vxiCmd.data0,
						vxiAnsw.answ, vxiAnsw.data0,
						cnt);
			
			
			cnt = vxiAnsw.data0;
			cnt /= mglobals->sample_bytes_in;
			(*ReadNSamples) += cnt;
			if (cnt < nsamples)		//чтобы не попасть в ситуацию, когда инструмент постепенно успевает чуть-чуть
				break;				//подкачивать данные
			NSamples -= cnt;
			if (NSamples)
			{
				ViUInt8 *buf8 = ((ViUInt8*)Buff) + nsamples * mglobals->sample_bytes_in;
				Buff = (ViUInt32*)buf8;

				UnlockMB (mglobals->pbase_data);
			}
		}
		while (NSamples);

		okChk(VI_SUCCESS);
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		ViChar tmpbuff[32];
		ViUInt32 cnt;

		*ReadNSamples = 0;

		//Для оптимизации чтения будем читать не более 999900 байт!
		do
		{
			ViUInt32 nsamples, bytes;

			bytes = NSamples * mglobals->sample_bytes_in;
			if (bytes > 999900)
			{
				nsamples = 999900 / mglobals->sample_bytes_in;
				while (0x3 & (nsamples * mglobals->sample_bytes_in))	//заодно выровняем
					nsamples--;
			}
			else
				nsamples = NSamples;

			LockMB(mglobals->pbase_data);
			if (!*ReadNSamples)
			{
				//первое чтение с контролем ошибок
				errChkMB(mglobals->basevi, viPrintf (mglobals->basevi,
													 "MRDPACK%d? %d\n",
													 mglobals->mnum, nsamples));
				errChkMB(mglobals->basevi, viBufRead (mglobals->basevi, (ViPBuf)tmpbuff, 2, &cnt));
				if ((cnt != 2) || (*tmpbuff != '#'))
					errChk(UNMBASE_ERROR_INSTR);
				errChkMB(mglobals->basevi, viBufRead (mglobals->basevi, (ViPBuf)tmpbuff, tmpbuff[1] - '0', &cnt));
				tmpbuff[cnt] = 0;
				cnt = atoi(tmpbuff);
				errChkMB(mglobals->basevi, viBufRead (mglobals->basevi, (ViPBuf)Buff, cnt, &cnt));
				if (mglobals->baseBE)
					mem_swap32(Buff, cnt);
			}
			else
			{
				//последующие без контроля, чтобы оставшиеся данные просто остались непрочитанными
				if (viPrintf (mglobals->basevi,
							  "MRDPACK%d? %d\n",
							  mglobals->mnum, nsamples) < 0)
				{
					viClear(mglobals->basevi);
					break;
				}
				if (viBufRead (mglobals->basevi, (ViPBuf)tmpbuff, 2, &cnt) < 0)
				{
					viClear(mglobals->basevi);
					break;
				}
				if ((cnt != 2) || (*tmpbuff != '#'))
				{
					viClear(mglobals->basevi);
					break;
				}
				if (viBufRead (mglobals->basevi, (ViPBuf)tmpbuff, tmpbuff[1] - '0', &cnt) < 0)
				{
					viClear(mglobals->basevi);
					break;
				}
				tmpbuff[cnt] = 0;
				cnt = atoi(tmpbuff);
				if (viBufRead (mglobals->basevi, (ViPBuf)Buff, cnt, &cnt) < 0)
				{
					viClear(mglobals->basevi);
					break;
				}
				if (mglobals->baseBE)
					mem_swap32(Buff, cnt);
			}
			cnt /= mglobals->sample_bytes_in;
			(*ReadNSamples) += cnt;
			if (cnt < nsamples)		//чтобы не попасть в ситуацию, когда инструмент постепенно успевает чуть-чуть
				break;				//подкачивать данные
			NSamples -= cnt;
			if (NSamples)
			{
				ViUInt8 *buf8 = ((ViUInt8*)Buff) + nsamples * mglobals->sample_bytes_in;
				Buff = (ViUInt32*)buf8;

				UnlockMB (mglobals->pbase_data);
			}
		}
		while (NSamples);

		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);

		okChk(VI_SUCCESS);
	}
	else
	{
		ViUInt32 n, N;
		ViUInt32 howremain, addr1=0, size1=0, size2=0, loop_size_in;

		*ReadNSamples = 0;
		if (NSamples == 0)
			okChk(VI_SUCCESS);

		loop_size_in = checkLsize(mglobals->loop_size_in, mglobals->sample_bytes_in);

		N = NSamples * mglobals->sample_bytes_in;   //N - max bytes

		if (N < mglobals->tmp_block_remain)     //if all we need already readed
		{
			howremain = N;
			size1 = size2 = 0;
		}
		else
		{
			errChk(HowInPacket(mglobals, &howremain, &addr1, &size1, &size2));
		}
		//delete not needed data
		n = howremain + size1 + size2;
		if (N < n)      //if we have more data than requested
		{
			n-=N;   //n=not required bytes number
			if (n && size2)
			{
				if (n >= size2)
				{
					n -= size2;
					size2 = 0;
				}
				else
				{
					size2 -= n;
					n = 0;
				}
			}
			if (n && size1)
			{
				if (n >= size1)
				{
					n -= size1;
					size1 = 0;
				}
				else
				{
					size1 -= n;
					n = 0;
				}
			}
			if (n && howremain)
			{
				if (n >= howremain)
				{
					n -= howremain;
					howremain = 0;
				}
				else
				{
					howremain -= n;
					n = 0;
				}
			}
		}
		else      //if we have less or equal data to requested
			N = n;

		//Now we can read (howremain + size1 + size2) real bytes!!!
		if (howremain)      //we have something in tmpblock
		{
			memcpy(Buff, &(mglobals->tmpblock[0x100-mglobals->tmp_block_remain]), howremain);
			mglobals->tmp_block_remain -= howremain;
			(*ReadNSamples) += howremain;
			Buff = (ViUInt32*) &(((ViUInt8*)Buff)[howremain]);

			mglobals->next_sample_to_in += howremain;
			if (mglobals->next_sample_to_in >= loop_size_in)    //if achieve memory end, go to start
				mglobals->next_sample_to_in = 0;
		}
		if (size1)      //we have something in addr1
		{
			errChk( m_data_read(mglobals,
								addr1,  //base memory byte index
								size1,  //byte size
								(ViUInt8*)Buff));
			(*ReadNSamples) += size1;
			Buff = (ViUInt32*) &(((ViUInt8*)Buff)[size1]);

			mglobals->next_sample_to_in += size1;
			if (mglobals->next_sample_to_in >= loop_size_in)    //
				mglobals->next_sample_to_in = 0;
			if (N == 0)  //if all we need already readed
			{
				(*ReadNSamples) /= mglobals->sample_bytes_in;
				okChk(VI_SUCCESS);
			}
		}
		if (size2)      //we have something in memory begin
		{
			errChk( m_data_read(mglobals,
								0,  //base memory byte index
								size2,  //byte size
								(ViUInt8*)Buff));
			(*ReadNSamples) += size2;
			Buff = (ViUInt32*) &(((ViUInt8*)Buff)[size2]);

			mglobals->next_sample_to_in += size2;
			if (mglobals->next_sample_to_in >= loop_size_in)    //
				mglobals->next_sample_to_in = 0;
		}
		//No more data remain in memory, or no more data needed - return
		(*ReadNSamples) /= mglobals->sample_bytes_in;
	}
Error:
	if (mglobals)
	{
		if (status < 0)
			SpyLog3("unmbase_m_read_packet(m%d, want %d) return status %08X", mglobals->mnum, needNSamples, status);
		else
		if (*ReadNSamples)
			SpyLog3("unmbase_m_read_packet(m%d, want %d, return %d)", mglobals->mnum, needNSamples, *ReadNSamples);
		unmbase_ErrLed((PUserData)mglobals->pbase_data, status<0);
		UnlockMB (mglobals->pbase_data);
	}
	return status;
}

/*--------------------------------------------------------------------------*/
/* Read last samples when cycle mode run                                    */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_read_last_packet (ViSession mvi,
		ViUInt32 NSamples,
		ViUInt32 Buff[],
		ViUInt32 *ReadNSamples)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = 0;
	ViUInt32 needNSamples = NSamples;
	mviChk(mvi, mglobals);
	notNMU(mglobals);

	*ReadNSamples = 0;
	if (NSamples == 0)
		okChk(VI_SUCCESS);

	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM TODO
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;
		ViUInt32 cnt, armIdx;

		armIdx = mglobals->midx > 1 ? 1 : 0;

		*ReadNSamples = 0;

		if (!mglobals->sample_bytes_in)  	//если мы вошли без сброса и хотим что-то узнать про размер пакета
		{
			vxiCmd.cmd = ARMCMD_MSWIDTHq;
			status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
									0,
									&vxiCmd, &vxiAnsw);

			mglobals->sample_bytes_in = vxiAnsw.data0 * sizeof(ViUInt32);

		}
		//здесь надо бы отследить, чтобы не пытались читать lastpacket размером более 1 мБайта!!!
		//а то пытались читать не более 999900 байт, а адрес-то смещается...

		vxiCmd.cmd = ARMCMD_MRDLASTPACKq | armvxiMidxIoMask(mglobals->midx, 0);
		vxiCmd.data0 = NSamples;

		errChk(armvxi_bread_cmd(mglobals->pbase_data,
								ARMVXI_LOCKUNLOCK,
								armIdx,
								&vxiCmd,
								&vxiAnsw,
								NSamples * mglobals->sample_bytes_in,		//max number of bytes
								(ViUInt8*)Buff,
								&cnt));	//количество реально прочитанных байт

		cnt = vxiAnsw.data0;
		cnt /= mglobals->sample_bytes_in;
		(*ReadNSamples) = cnt;

		okChk(VI_SUCCESS);
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		//здесь надо бы отследить, чтобы не пытались читать lastpacket размером более 1 мБайта!!!
		ViChar tmpbuff[32];
		ViUInt32 cnt;
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viPrintf (mglobals->basevi,
											 "MRDLASTPACK%d? %d\n",
											 mglobals->mnum, NSamples));
		errChkMB(mglobals->basevi, viBufRead (mglobals->basevi, (ViPBuf)tmpbuff, 2, &cnt));
		if ((cnt != 2) || (*tmpbuff != '#'))
			errChk(UNMBASE_ERROR_INSTR);
		errChkMB(mglobals->basevi, viBufRead (mglobals->basevi, (ViPBuf)tmpbuff, tmpbuff[1] - '0', &cnt));
		tmpbuff[cnt] = 0;
		cnt = atoi(tmpbuff);
		errChkMB(mglobals->basevi, viBufRead (mglobals->basevi, (ViPBuf)Buff, cnt, &cnt));
		if (mglobals->baseBE)
			mem_swap32(Buff, cnt);

		if (!mglobals->sample_bytes_in)  	//если мы вошли без сброса и хотим что-то узнать про размер пакета
		{
			errChkMB(mglobals->basevi, viQueryf(mglobals->basevi,
												"MSWIDTH%d? I\n",
												"%u",
												mglobals->mnum,
												&mglobals->sample_bytes_in));
			mglobals->sample_bytes_in *= sizeof(ViUInt32);

		}
		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
		*ReadNSamples = cnt / mglobals->sample_bytes_in;
		okChk(VI_SUCCESS);
	}
	else
	{
		ViUInt32 N;
		ViUInt32 addr1, size1, size2, loop_size_in;

		loop_size_in = checkLsize(mglobals->loop_size_in, mglobals->sample_bytes_in);

		N = NSamples * mglobals->sample_bytes_in;   //N - max bytes

		mglobals->tmp_block_remain = 0;

		errChk(HowInLastPacket(mglobals, N, &addr1, &size1, &size2));

		mglobals->next_sample_to_in	= addr1;

		//Now we can read (size1 + size2) real bytes!!!
		if (size1)      //we have something in addr1
		{
			errChk( m_data_read(mglobals,
								addr1,  //base memory byte index
								size1,  //byte size
								(ViUInt8*)Buff));
			(*ReadNSamples) += size1;
			Buff = (ViUInt32*) &(((ViUInt8*)Buff)[size1]);

			mglobals->next_sample_to_in += size1;
			if (mglobals->next_sample_to_in >= loop_size_in)    //
				mglobals->next_sample_to_in = 0;
			if (N == 0)  //if all we need already readed
			{
				(*ReadNSamples) /= mglobals->sample_bytes_in;
				okChk(VI_SUCCESS);
			}
		}
		if (size2)      //we have something in memory begin
		{
			errChk( m_data_read(mglobals,
								0,  //base memory byte index
								size2,  //byte size
								(ViUInt8*)Buff));
			(*ReadNSamples) += size2;
			Buff = (ViUInt32*) &(((ViUInt8*)Buff)[size2]);

			mglobals->next_sample_to_in += size2;
			if (mglobals->next_sample_to_in >= loop_size_in)    //
				mglobals->next_sample_to_in = 0;
		}
		//No more data remain in memory, or no more data needed - return
		(*ReadNSamples) /= mglobals->sample_bytes_in;
	}
Error:
	if (mglobals)
	{
		if (status < 0)
			SpyLog3("unmbase_m_read_last_packet(m%d, want %d) return status %08X", mglobals->mnum, needNSamples, status);
		else
		if (*ReadNSamples)
			SpyLog3("unmbase_m_read_last_packet(m%d, want %d, return %d)", mglobals->mnum, needNSamples, *ReadNSamples);

		unmbase_ErrLed((PUserData)mglobals->pbase_data, status<0);
		UnlockMB (mglobals->pbase_data);
	}
	return status;
}

/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_write_packet (ViSession mvi,
		ViUInt32 NSamples,
		ViUInt32 Buff[],
		ViUInt32 *WriteNSamples)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = 0;
	mviChk(mvi, mglobals);
	notNMU(mglobals);
	SpyLog2("unmbase_m_write_packet(m%d, %d)", mglobals->mnum, NSamples);
	*WriteNSamples = 0;

	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM TODO
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;
		ViUInt32 armIdx;

		armIdx = mglobals->midx > 1 ? 1 : 0;

		//Здесь надо сначала запросить - сколько данных можно писать.
		vxiCmd.cmd = ARMCMD_MHOWDATAq;
		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								1,
								&vxiCmd, &vxiAnsw);
		SpyLog1("can write %d\n", vxiAnsw.data0);
		if (NSamples > vxiAnsw.data0)
			NSamples = vxiAnsw.data0;

		vxiCmd.cmd = ARMCMD_MWRPACK | armvxiMidxIoMask(mglobals->midx, 1);
		vxiCmd.data0 = NSamples;

		errChk(armvxi_bwrite_cmd(mglobals->pbase_data,
								ARMVXI_LOCKUNLOCK,
								armIdx,
								&vxiCmd,
								NSamples * mglobals->sample_bytes_out,		//max number of bytes
								(ViUInt8*)Buff));
		//в принципе, в answ содержится количество байт, которые понадобились...

		*WriteNSamples = NSamples;
		okChk(VI_SUCCESS);
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		ViChar tmpbuff[128], *tmpbuffptr;
		ViUInt32 N, cnt, digits;

		LockMB(mglobals->pbase_data);
		//Здесь надо сначала запросить - сколько данных можно писать.
		errChkMB(mglobals->basevi, viQueryf(mglobals->basevi,
											"MHOWDATA%d? O\n",
											"%u",
											mglobals->mnum,
											WriteNSamples));
		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
		SpyLog1("can write %d\n", *WriteNSamples);
		if (NSamples > *WriteNSamples)
			NSamples = *WriteNSamples;

		//готовим для передачи выровненныый блок данных 488.2 Arbitrary Length Binary Block
		N = NSamples * mglobals->sample_bytes_out;
		sprintf(tmpbuff, "%d", N);	//byte size
		digits = strlen(tmpbuff);
		sprintf(tmpbuff, "MWRPACK%d %d,",
				mglobals->mnum, NSamples);
		cnt = strlen(tmpbuff);
		tmpbuffptr = &tmpbuff[cnt];
		//общее количество передаваемых байт команды до начала данных = digits + cnt + 2 (это "#n")
		cnt += digits+2;
		while (cnt&3)
		{
			*tmpbuffptr++ = ' ';	//выравниваем при помощи пробелов
			cnt++;
		}
		sprintf(tmpbuffptr, "#%d%d",
				digits, N);

		errChkMB(mglobals->basevi, viBufWrite (mglobals->basevi, (ViPBuf)tmpbuff, cnt, VI_NULL));

		if (mglobals->baseBE)
		{
			void *swapbuf = malloc(N);
			if (!swapbuf)
				errChk(VI_ERROR_ALLOC);

			memcpy_swap32(swapbuf, Buff, N);
			status = viBufWrite (mglobals->basevi, (ViPBuf)swapbuf, N, &cnt);
			free(swapbuf);
			errChkMB(mglobals->basevi, status);
		}
		else
			errChkMB(mglobals->basevi, viBufWrite (mglobals->basevi, (ViPBuf)Buff, N, &cnt));

		errChkMB(mglobals->basevi, viFlush (mglobals->basevi, VI_WRITE_BUF));
		*WriteNSamples = cnt / mglobals->sample_bytes_out;
		okChk(VI_SUCCESS);
	}
	else
	{
		ViUInt32 n, N, lastaddr, loop_size_out;

		loop_size_out = checkLsize(mglobals->loop_size_out, mglobals->sample_bytes_out);

		N = NSamples * mglobals->sample_bytes_out;  //N - max bytes
		if (N == 0) //if have no data to write
			okChk(VI_SUCCESS);
		//if not started, then can write up to memory end
		if (!mglobals->state_out)
		{
			lastaddr = loop_size_out;
		}
		else
		{
			//detect, where next free block (how blocks already in memory)
			//пытаемся читать хорошо...
			errChk(GetLastOutAddr(mglobals, &lastaddr));
			//lastaddr - first non-free block address
			lastaddr = (lastaddr << 8) - mglobals->membase_out - mglobals->loop_base_out;     //convert to mezzanine memory pointer
		}
		lastaddr = checkLsize(lastaddr, mglobals->sample_bytes_out);
		if (lastaddr == mglobals->next_sample_to_out)   //if we have no room for next data
		{
			okChk(VI_SUCCESS);
		}
		if (mglobals->next_sample_to_out >= loop_size_out)  //go to memory start
			mglobals->next_sample_to_out = 0;
		if (lastaddr < mglobals->next_sample_to_out)    //need to write first up to memory end
		{
			n = loop_size_out - mglobals->next_sample_to_out;   //n = bytes up to memory end
			if (N < n)
				n = N;
			errChk( m_data_write(mglobals,
								 mglobals->next_sample_to_out,   //base memory byte index
								 n,                                              //byte size
								 (ViUInt8*)Buff));
			(*WriteNSamples) += n;
			N -= n;
			Buff = (ViUInt32*) &(((ViUInt8*)Buff)[n]);

			mglobals->next_sample_to_out += n;
			if (N == 0)
			{
				(*WriteNSamples) /= mglobals->sample_bytes_out;
				okChk(VI_SUCCESS);
			}
		}
		//now write from mglobals->next_sample_to_out up to lastaddr
		if (mglobals->next_sample_to_out >= loop_size_out)  //go to memory start
			mglobals->next_sample_to_out = 0;
		n = lastaddr - mglobals->next_sample_to_out;
		if (N < n)
			n = N;
		errChk( m_data_write(mglobals,
							 mglobals->next_sample_to_out,   //base memory byte index
							 n,                                              //byte size
							 (ViUInt8*)Buff));
		(*WriteNSamples) += n;

		mglobals->next_sample_to_out += n;
		//no more data needed - return
		(*WriteNSamples) /= mglobals->sample_bytes_out;
	}
Error:
	if (mglobals)
	{
		unmbase_ErrLed((PUserData)mglobals->pbase_data, status<0);
		UnlockMB(mglobals->pbase_data);
	}
	return status;
}

/*--------------------------------------------------------------------------*/
/* Setup mezzanine trigger source                                           */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_config_trigger (ViSession mvi,
		ViUInt16 io,
		ViInt16 StartSource)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS;
	mviChk(mvi, mglobals);

	SpyLog2("unmbase_m_config_trigger(m%d, %d)", mglobals->mnum, StartSource);

	if (mglobals->dev_type == 0)
	{
		notNMU(mglobals);
	}
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;

		vxiCmd.cmd = armvxiCmdD16(ARMCMD_MCFGTRG,
								  StartSource);

		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								io,
								&vxiCmd, VI_NULL);
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		mbusyChk(mvi, mglobals, io);
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viPrintf(mglobals->basevi,
											"MCFGTRG%d %c,%d\n",
											mglobals->mnum, IOChar[io], StartSource));
	}
	else
	{
		if (mglobals->dev_type &&
			mglobals->basesimple)
		{
			if (io)
				mglobals->start_source_out = StartSource;
			else
				mglobals->start_source_in = StartSource;
			return 0;
		}

		mbusyChk(mvi, mglobals, io);
		if (io)     //OUT
		{
			mglobals->start_source_out = StartSource;
			//setup mode
			status = Out32_COMM2A(mglobals->basevi,
								  ~maskCOMM2A_OUT_STARTCFG[mglobals->midx],
								  (StartSource==1) ? maskCOMM2A_OUT_STARTCFG[mglobals->midx] : 0);
		}
		else      //IN
		{
			mglobals->start_source_in = StartSource;
			//setup mode
			status = Out32_COMM2A(mglobals->basevi,
								  ~maskCOMM2A_IN_STARTCFG[mglobals->midx],
								  (StartSource==1) ? maskCOMM2A_IN_STARTCFG[mglobals->midx] : 0);
		}
	}
Error:
	if (mglobals)
	{
		unmbase_ErrLed((PUserData)mglobals->pbase_data, status<0);
		UnlockMB (mglobals->pbase_data);
	}
	return status;
}

/*--------------------------------------------------------------------------*/
/* Return mezzanine trigger source                                          */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_config_trigger_q (ViSession mvi,
		ViUInt16 io,
		ViInt16 *StartSource)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS;
	mviChk(mvi, mglobals);
	notNMU(mglobals);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;

		vxiCmd.cmd = ARMCMD_MCFGTRGq;
		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								io,
								&vxiCmd, &vxiAnsw);

		*StartSource = (ViInt16)vxiAnsw.data16;
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viQueryf(mglobals->basevi,
											"MCFGTRG%d? %c\n",
											"%hd",
											mglobals->mnum, IOChar[io],
											StartSource));
		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
	}
	else
	{
		*StartSource = io ? mglobals->start_source_out : mglobals->start_source_in;
	}
Error:
	if (mglobals) UnlockMB (mglobals->pbase_data);
	return status;
}

/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
//OK1 - without divisor checking
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_start (ViSession mvi,
		ViUInt16 io)
{
	PM_SESSION mglobals = NULL;
//ViUInt32 i, alltime;
	ViUInt32 word, i;
	ViStatus status = VI_SUCCESS, mbstatus = VI_SUCCESS;
	mviChk(mvi, mglobals);

	if (mglobals->dev_type)		//for simplyfied do nothing
		return 0;
	notNMU(mglobals);

	SpyLog2("unmbase_m_start(m%d, io=%d)", mglobals->mnum,io);

	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;

		vxiCmd.cmd = ARMCMD_MSTART;
		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, 2.0,
								io,
								&vxiCmd, VI_NULL);
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viQueryf(mglobals->basevi,
											"MSTART%d %c;*ERR?\n",
											"%d",
											mglobals->mnum, IOChar[io],
											&mbstatus));
		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
		errChk(mbstatus);
	}
	else
	{

		if (io < UNMBASE_IOMODE_BOTH)
			mbusyChk(mvi, mglobals, io);
		else
		if ( mglobals->state_out | mglobals->state_in)
			errChk(UNMBASE_ERROR_BUSY);

		//для отработки зависающих прерваний
		mglobals->badIrqTimer = 0;
		mglobals->badIrqCount = 0;

		//clear all errors
		errChk(Out32_COMM2(mglobals->basevi,
						   ~0,
						   maskCOMM2_ERR1_M_RST[mglobals->midx] |
						   maskCOMM2_ERR2_M_RST[mglobals->midx] |
						   maskCOMM2_ERR3_RST |
						   maskCOMM2_ERR4_RST));
		/*
		//check all mezzanine divisors  ??? VAV Debug now!!!
		//!!! Need to be settled mglobals->state_xx before !!!
			globals = (PUserData)mglobals->pbase_data;
			mglobals->state_in = 1;
			for (i=0, alltime=0; i<4; i++)
				alltime +=  globals->m_session[i].state_out ? (globals->m_session[i].sample_words_out + 2) : 0 +
							globals->m_session[i].state_in ? (globals->m_session[i].sample_words_in + 4) : 0;
			for (i=0; i<4; i++)
				if ((globals->m_session[i].state_out & (globals->m_session[i].divisor_out < alltime)) ||
					(globals->m_session[i].state_in & (globals->m_session[i].divisor_in < alltime))) {
					status = UNMBASE_ERROR_TOO_FAST;
					break;
				}
		*/
		if ((io == UNMBASE_IOMODE_OUT) || (io == UNMBASE_IOMODE_BOTH))      //OUT
		{
			//mglobals->next_sample_to_out = 0; //clear data to out pointer
			/*не проверяем, т.к. данные могли быть записаны и раньше
					if (mglobals->mode_out == UNMBASE_MODE_LOOP)    //need to be already data in memory
						if (mglobals->next_sample_to_out == 0)  //if no packets ready inmem
							errChk(UNMBASE_ERROR_NODATA);
			*/
			errChk(LockOutSTARTSTOP(mglobals,
									rgSTART_OUT,
									(mglobals->mode_out == UNMBASE_MODE_LOOP) ? (mglobals->membase_out + mglobals->loop_base_out) >> 8 :
									mglobals->membase_out >> 8));      //for block address

			mglobals->state_out = 1;
			//prepare
			errChk( viIn32(mglobals->basevi, VI_A24_SPACE,
						   rgSTAT2A,
						   &word));
			if ((word & maskSTAT2A_OUT_EMPTY[mglobals->midx]) == 0)      //Output Buffer not empty
			{
				//errChk(Out32_COMM2(mglobals->basevi,
				//                      ~0,
				//                      maskCOMM2_OUT_RST[mglobals->midx]));
				SpyLog("Error OUT_NOT_EMPTY when start\n");
				errChk(UNMBASE_ERROR_INSTR);
			}

			errChk( Out32_COMM1(mglobals->basevi,
								~0,
								maskCOMM1_OUT_ON[mglobals->midx]));

			for (i=0; i<100; i++)
			{
				errChk( viIn32(mglobals->basevi, VI_A24_SPACE,
							   rgSTAT2,
							   &word));
				word &= IGNORE_STAT2_ERRORS;

				if ((word & maskSTAT2_OUT_READY[mglobals->midx]) == 0)
					break;
				if (i==99)
				{
					SpyLog("Error not STAT2_OUT_READY when start\n");
					errChk(UNMBASE_ERROR_INSTR);
				}
			}

			errChk( Out32_COMM2(mglobals->basevi,
								~0,
								maskCOMM2_OUT_EN[mglobals->midx]));
			errChk( viIn32(mglobals->basevi, VI_A24_SPACE,
						   rgSTAT2,
						   &word));
			word &= IGNORE_STAT2_ERRORS;

			if ((word & maskSTAT2_OUT_EN[mglobals->midx]) == 0)
			{
				SpyLog("Error not STAT2_OUT_EN when start\n");
				errChk(UNMBASE_ERROR_INSTR);
			}

			errChk( Out32_COMM2A(mglobals->basevi,
								 ~0,
								 maskCOMM2A_OUT_RSTFLAG[mglobals->midx]));

			//check sync type
			if (mglobals->start_source_out)   //group or internal
			{
				//we already ready for base trigger
			}
			else      //individual
			{
				//program start
				if (io != UNMBASE_IOMODE_BOTH)  //Else simultaneously start later
					errChk( Out32_COMM2A(mglobals->basevi,
										 ~0,
										 maskCOMM2A_OUT_START[mglobals->midx]));
			}
		}
		//do not do ELSE!!! As we can receive UNMBASE_MODE_BOTH !!!
		if ((io == UNMBASE_IOMODE_IN) || (io == UNMBASE_IOMODE_BOTH))       //IN
		{
			mglobals->tmp_block_remain = 0; //clear all readed data
			mglobals->next_sample_to_in = 0;    //clear all readed data
			mglobals->state_in = 1;
			errChk(LockOutSTARTSTOP(mglobals,
									rgSTART_IN,
									(mglobals->mode_in == UNMBASE_MODE_LOOP) ? (mglobals->membase_in + mglobals->loop_base_in) >> 8 :
									mglobals->membase_in >> 8));      //for block address
			//prepare
			errChk( viIn32(mglobals->basevi, VI_A24_SPACE,
						   rgSTAT2A,
						   &word));
			if ((word & maskSTAT2A_IN_EMPTY[mglobals->midx]) == 0)   //Input Buffer not empty
			{
				errChk( Out32_COMM2(mglobals->basevi,
									~0,
									maskCOMM2_IN_RST[mglobals->midx]));
			}
			errChk( Out32_COMM1(mglobals->basevi,
								~0,
								maskCOMM1_IN_ON[mglobals->midx]));
			errChk( viIn32(mglobals->basevi, VI_A24_SPACE,
						   rgSTAT1,
						   &word));
			if ((word & maskSTAT1_IN_ON[mglobals->midx]) == 0)
			{
				SpyLog("Error not STAT1_IN_ON when start\n");
				errChk(UNMBASE_ERROR_INSTR);
			}

			errChk( Out32_COMM2(mglobals->basevi,
								~0,
								maskCOMM2_IN_EN[mglobals->midx]));
			errChk( viIn32(mglobals->basevi, VI_A24_SPACE,
						   rgSTAT2,
						   &word));
			word &= IGNORE_STAT2_ERRORS;

			if ((word & maskSTAT2_IN_EN[mglobals->midx]) == 0)
			{
				SpyLog("Error not STAT2_IN_EN when start\n");
				errChk(UNMBASE_ERROR_INSTR);
			}

			errChk( Out32_COMM2A(mglobals->basevi,
								 ~0,
								 maskCOMM2A_IN_RSTFLAG[mglobals->midx]));
			//check sync type
			if (mglobals->start_source_in)   //group or internal
			{
				//we already ready for base trigger
			}
			else      //individual
			{
				//program start
				if (io != UNMBASE_IOMODE_BOTH)      //Else simultaneously start later
				{
					errChk( Out32_COMM2A(mglobals->basevi,
										 ~0,
										 maskCOMM2A_IN_START[mglobals->midx]));
				}
				else
				{
					errChk( Out32_COMM2A(mglobals->basevi,
										 ~0,
										 maskCOMM2A_IN_START[mglobals->midx] | maskCOMM2A_OUT_START[mglobals->midx])); //YOOOOO!
				}
			}
		}
	}
Error:
	if (mglobals)
	{
		if (status < 0)
		{
			if ((io == UNMBASE_IOMODE_OUT) || (io == UNMBASE_IOMODE_BOTH))
			{
				mglobals->next_sample_to_out = 0;   //clear memory for out
				mglobals->state_out = 0;
			}
			if ((io == UNMBASE_IOMODE_IN) || (io == UNMBASE_IOMODE_BOTH))
				mglobals->state_in = 0;
		}
		unmbase_ErrLed((PUserData)mglobals->pbase_data, status<0);
		UnlockMB (mglobals->pbase_data);
	}
	return status;
}

/*--------------------------------------------------------------------------*/
/*  Immediate Stop                                                          */
/*--------------------------------------------------------------------------*/
static ViStatus _VI_FUNC unmbase_m_stop_out(PM_SESSION mglobals)
{
	ViStatus status = 0;
	ViInt16 state = 0;
	ViUInt32 word, encompl, i;
	ViBoolean Compl, On;

	mglobalsChk(mglobals);
	notNMU(mglobals);
	if (InterlockedExchange(&mglobals->stop_out_busy, 1))
	{
		while (InterlockedExchange(&mglobals->stop_out_busy, 1))
		{
			cross_switch_thread();
		}
		InterlockedExchange(&mglobals->stop_out_busy, 0);
		return 0;
	}
	errChk( viIn32 (mglobals->basevi, VI_A24_SPACE, rgENDIRQ, &encompl));
	errChk( viOut32 (mglobals->basevi, VI_A24_SPACE, rgENDIRQ,      //Disble
					 encompl | maskENDIRQ_OUT_DIS[mglobals->midx]));
	if (mglobals->dev_type)
		goto Error;
	errChk( viIn32(mglobals->basevi, VI_A24_SPACE,
				   rgSTAT1,
				   &word));
	On = (word & maskSTAT1_OUT_ON[mglobals->midx]) != 0;
	if (On)     //need to stop manually
	{
		errChk( viIn32(mglobals->basevi, VI_A24_SPACE,
					   rgCOMPLETE,
					   &word));
		Compl = (word & maskCOMPLETE_OUT[mglobals->midx]) != 0;
		if (Compl == 0)
		{

			errChk( Out32_COMM1(mglobals->basevi,
								~maskCOMM1_OUT_ON[mglobals->midx],
								0));
			i = 0;
			while (VI_TRUE)     //wait to complete
			{
				if (mglobals->divisor_in == 0xFFFFFFFF) //if divisor not settled
					break;
				if (i++ > mglobals->divisor_out*3)
				{
					SpyLog("Error not COMPLETE_OUT when stop\n");
					errChk(UNMBASE_ERROR_INSTR);
				}
				errChk( viIn32(mglobals->basevi, VI_A24_SPACE,
							   rgCOMPLETE,
							   &word));
				Compl = (word & maskCOMPLETE_OUT[mglobals->midx]) != 0;
				if (Compl)
					break;
			}
		}
	}
	//???????????????????????????????????????
	errChk( Out32_COMM1(mglobals->basevi,
						~maskCOMM1_OUT_ON[mglobals->midx],
						0));
	errChk( Out32_COMM2(mglobals->basevi,
						~maskCOMM2_OUT_EN[mglobals->midx],
						0));
	errChk( Out32_COMM2A(mglobals->basevi,
						 ~0,
						 maskCOMM2A_OUT_RSTFLAG[mglobals->midx]));
	errChk( Out32_ENDIRQ(mglobals->basevi,
						 ~0,
						 maskENDIRQ_OUT_BUF_RST[mglobals->midx]));
	errChk( Out32_COMM1(mglobals->basevi,
						~0,
						maskCOMM1_IRQ_OUT_RESET[mglobals->midx]));

	mglobals->state_out = 0;
Error:
	mglobals->next_sample_to_out = 0;   //clear memory for out
	viOut32 (mglobals->basevi, VI_A24_SPACE, rgENDIRQ, encompl); //restore
//clear all errors for this mezzanine
	Out32_COMM2(mglobals->basevi,
				~0,
				maskCOMM2_ERR1_M_RST[mglobals->midx] |
				maskCOMM2_ERR2_M_RST[mglobals->midx]);
	Out32_COMM1(mglobals->basevi,   //clear IRQ
				~0,
				maskCOMM1_IRQ_OUT_RESET[mglobals->midx]);
//check additional errors
	if (status<0)
	{
		SpyLog1("ERROR-4 unmbase_m_stop_out(m%d)\n", mglobals->mnum);
		state = -4;
	}
	if (mglobals->state_out > 0)
		mglobals->state_out = state;

	//для отработки зависающих прерваний
	mglobals->badIrqTimer = 0;
	mglobals->badIrqCount = 0;

	InterlockedExchange(&mglobals->stop_out_busy, 0);

	return status;
}

static ViStatus _VI_FUNC unmbase_m_async_stop_in(PM_SESSION mglobals)
{
	ViStatus status = 0;
	ViUInt32 word, encompl;
	ViInt16 state = 0;
	mglobalsChk(mglobals);
	if (UNMBASE_MODE_SINGLE == mglobals->mode_in)
		return unmbase_m_stop_in(mglobals);
	notNMU(mglobals);

	if (InterlockedExchange(&mglobals->stop_in_busy, 1))
	{
		while (InterlockedExchange(&mglobals->stop_in_busy, 1))
		{
			cross_switch_thread();
		}
		InterlockedExchange(&mglobals->stop_in_busy, 0);
		return 0;
	}

	errChk( viIn32 (mglobals->basevi, VI_A24_SPACE, rgENDIRQ, &encompl));
	errChk( viOut32 (mglobals->basevi, VI_A24_SPACE, rgENDIRQ,      //Disble
					 encompl | maskENDIRQ_IN_DIS[mglobals->midx]));
//	switch (mglobals->mode_in) {
//	case UNMBASE_MODE_BLOCK:
//	case UNMBASE_MODE_LOOP:
	errChk( viIn32(mglobals->basevi, VI_A24_SPACE,
				   rgSTAT2A,
				   &word));
	if (word & maskSTAT2A_IN_ON[mglobals->midx])
	{
		//для асинхронного режима здесь уже 0
		SpyLog("Error have STAT2A_IN_ON when async_stop\n");
		errChk(UNMBASE_ERROR_INSTR);
	}

	errChk( Out32_COMM2A(mglobals->basevi,
						 ~0,
						 maskCOMM2A_IN_RSTFLAG[mglobals->midx]));
	errChk( viIn32(mglobals->basevi, VI_A24_SPACE,
				   rgSTAT2A,
				   &word));
	if ((word & maskSTAT2A_IN_EMPTY[mglobals->midx]) == 0)   //if not empty
	{
		errChk( Out32_COMM2(mglobals->basevi,
							~0,
							maskCOMM2_IN_RST[mglobals->midx]));
		cross_delay(0.001);
	}
	errChk( Out32_COMM2(mglobals->basevi,
						~maskCOMM2_IN_EN[mglobals->midx],
						0));

	errChk( Out32_COMM1(mglobals->basevi,
						~maskCOMM1_IN_ON[mglobals->midx],
						0));
Error:
	viOut32 (mglobals->basevi, VI_A24_SPACE, rgENDIRQ, encompl);    //restore
//clear all errors for this mezzanine
	Out32_COMM2(mglobals->basevi,
				~0,
				maskCOMM2_ERR1_M_RST[mglobals->midx] |
				maskCOMM2_ERR2_M_RST[mglobals->midx]);
	Out32_COMM1(mglobals->basevi,   //clear IRQ
				~0,
				maskCOMM1_IRQ_IN_RESET[mglobals->midx]);
	if (status<0)
	{
		SpyLog1("ERROR-4 unmbase_m_async_stop_in(m%d)\n", mglobals->mnum);
		state = -4;
	}
	if (mglobals->state_in > 0)
		mglobals->state_in = state;

	//для отработки зависающих прерваний
	mglobals->badIrqTimer = 0;
	mglobals->badIrqCount = 0;

	InterlockedExchange(&mglobals->stop_in_busy, 0);
	return status;
}

static ViStatus _VI_FUNC unmbase_m_stop_in(PM_SESSION mglobals)
{
	ViStatus status = 0;
	ViUInt32 word, encompl, i;
	ViInt16 state = 0;
	mglobalsChk(mglobals);
	notNMU(mglobals);

	if ((mglobals->mode_in != UNMBASE_MODE_SINGLE) && mglobals->async_type)
		return unmbase_m_async_stop_in(mglobals);

	if (InterlockedExchange(&mglobals->stop_in_busy, 1))
	{
		while (InterlockedExchange(&mglobals->stop_in_busy, 1))
		{
			cross_switch_thread();
		}
		InterlockedExchange(&mglobals->stop_in_busy, 0);
		return 0;
	}

	errChk( viIn32 (mglobals->basevi, VI_A24_SPACE, rgENDIRQ, &encompl));
	errChk( viOut32 (mglobals->basevi, VI_A24_SPACE, rgENDIRQ,      //Disble
					 encompl | maskENDIRQ_IN_DIS[mglobals->midx]));
	if (mglobals->dev_type)
		goto Error;
	switch (mglobals->mode_in)
	{
	case UNMBASE_MODE_SINGLE:
		errChk( viIn32(mglobals->basevi, VI_A24_SPACE,
					   rgCOMPLETE,
					   &word));
		if ((word & maskCOMPLETE_IN[mglobals->midx]) == 0)   //if not complete, forced stop
		{
			errChk( Out32_COMM2A(mglobals->basevi,
								 ~0,
								 maskCOMM2A_IN_STOP[mglobals->midx]));
			for (i=0; i<100; i++)   //wait to complete
			{
				errChk( viIn32(mglobals->basevi, VI_A24_SPACE,
							   rgCOMPLETE,
							   &word));
				if (word & maskCOMPLETE_IN[mglobals->midx])
					break;
			}
		}
		errChk( Out32_COMM2A(mglobals->basevi,
							 ~0,
							 maskCOMM2A_IN_RSTFLAG[mglobals->midx]));
		errChk( viIn32(mglobals->basevi, VI_A24_SPACE,
					   rgSTAT2A,
					   &word));
		if ((word & maskSTAT2A_IN_EMPTY[mglobals->midx]) == 0)   //if not empty
		{
			errChk( Out32_COMM2(mglobals->basevi,
								~0,
								maskCOMM2_IN_RST[mglobals->midx]));
			cross_delay(0.001);
		}
		errChk( Out32_COMM2(mglobals->basevi,
							~maskCOMM2_IN_EN[mglobals->midx],
							0));
		errChk( Out32_COMM1(mglobals->basevi,
							~maskCOMM1_IN_ON[mglobals->midx],
							0));
		break;
	case UNMBASE_MODE_BLOCK:
	case UNMBASE_MODE_LOOP:
#ifdef DBGPRINT
		printf("stop block in  \n   ");
#endif
		errChk( viIn32(mglobals->basevi, VI_A24_SPACE,
					   rgSTAT2A,
					   &word));
		if (word & maskSTAT2A_IN_ON[mglobals->midx])
		{
			errChk( Out32_COMM2A(mglobals->basevi,
								 ~0,
								 maskCOMM2A_IN_STOP[mglobals->midx]));
			i = 0;
			while (VI_TRUE)     //wait to complete
			{
				if (mglobals->divisor_in == 0xFFFFFFFF) //if divisor not settled
					break;
				if (i++ > mglobals->divisor_in)
				{
					SpyLog("ERROR-4 unmbase_m_stop_in: do not clear maskSTAT2A_IN_ON\n");
					errChk(UNMBASE_ERROR_INSTR);
				}
				errChk( viIn32(mglobals->basevi, VI_A24_SPACE,
							   rgSTAT2A,
							   &word));
				if ((word & maskSTAT2A_IN_ON[mglobals->midx]) == 0)
					break;
			}
		}
#ifdef DBGPRINT
		printf("inON2A == 0\n   ");
#endif
		errChk( viIn32(mglobals->basevi, VI_A24_SPACE,
					   rgSTAT1,
					   &word));
		if ((word & maskSTAT1_IN_ON[mglobals->midx]) || (mglobals->state_in > 0))    //if not stopped
		{
			i = 0;
			while (VI_TRUE)     //wait to complete
			{
				if (mglobals->divisor_in == 0xFFFFFFFF) //if divisor not settled
					break;
				if (i++ > mglobals->divisor_in)
				{
					SpyLog1("ERROR-4 unmbase_m_stop_in: do not set COMPLETE, old state=%d\n", mglobals->state_in);
					errChk(UNMBASE_ERROR_INSTR);
				}
				errChk( viIn32(mglobals->basevi, VI_A24_SPACE,
							   rgCOMPLETE,
							   &word));
				if (word & maskCOMPLETE_IN[mglobals->midx])
					break;
			}
		}
#ifdef DBGPRINT
		printf("complete=1, rst\n   ");
#endif
		errChk( Out32_COMM2A(mglobals->basevi,
							 ~0,
							 maskCOMM2A_IN_RSTFLAG[mglobals->midx]));
		errChk( viIn32(mglobals->basevi, VI_A24_SPACE,
					   rgSTAT2A,
					   &word));
		if ((word & maskSTAT2A_IN_EMPTY[mglobals->midx]) == 0)   //if not empty
		{
#ifdef DBGPRINT
			printf("no empty - rst\n   ");
#endif
			errChk( Out32_COMM2(mglobals->basevi,
								~0,
								maskCOMM2_IN_RST[mglobals->midx]));
			cross_delay(0.001);
		}
		errChk( Out32_COMM2(mglobals->basevi,
							~maskCOMM2_IN_EN[mglobals->midx],
							0));

		errChk( Out32_COMM1(mglobals->basevi,
							~maskCOMM1_IN_ON[mglobals->midx],
							0));
		break;
	}
Error:
	viOut32 (mglobals->basevi, VI_A24_SPACE, rgENDIRQ, encompl);    //restore
//clear all errors for this mezzanine
	Out32_COMM2(mglobals->basevi,
				~0,
				maskCOMM2_ERR1_M_RST[mglobals->midx] |
				maskCOMM2_ERR2_M_RST[mglobals->midx]);
	Out32_COMM1(mglobals->basevi,   //clear IRQ
				~0,
				maskCOMM1_IRQ_IN_RESET[mglobals->midx]);
	if (status<0)
	{
		state = -4;
		SpyLog("ERROR-4 unmbase_m_stop_in\n");
	}
	if (mglobals->state_in > 0)
		mglobals->state_in = state;
	//для отработки зависающих прерваний
	mglobals->badIrqTimer = 0;
	mglobals->badIrqCount = 0;

	InterlockedExchange(&mglobals->stop_in_busy, 0);
	return status;
}

/*--------------------------------------------------------------------------*/
/*  Immediate Stop                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_stop (ViSession mvi,
		ViUInt16 io)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS, mbstatus = VI_SUCCESS;
	mviChk(mvi, mglobals);
	notNMU(mglobals);
	SpyLog2("unmbase_m_stop(m%d, io=%d)", mglobals->mnum, io);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;

		vxiCmd.cmd = ARMCMD_MSTOP;
		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, 2.0,
								io,
								&vxiCmd, VI_NULL);
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viQueryf(mglobals->basevi,
											"MSTOP%d %c;*ERR?\n",
											"%d",
											mglobals->mnum, IOChar[io],
											&mbstatus));
		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
		errChk(mbstatus);
	}
	else
	{
		if (io == UNMBASE_IOMODE_BOTH)      //recursively call this for OUT and IN ;)
		{
			errChk(unmbase_m_stop (mvi, UNMBASE_IOMODE_OUT));
			return unmbase_m_stop (mvi, UNMBASE_IOMODE_IN);
		}
		if (io)     //OUT
		{
			if (!mglobals->state_out)
				okChk(VI_SUCCESS);
			errChk(unmbase_m_stop_out(mglobals));
		}
		else      //IN
		{
			if (!mglobals->state_in)
				okChk(VI_SUCCESS);
			errChk(unmbase_m_stop_in(mglobals));
		}
	}
Error:
	if (mglobals)
	{
		//для отработки зависающих прерваний
		mglobals->badIrqTimer = 0;
		mglobals->badIrqCount = 0;

		unmbase_ErrLed((PUserData)mglobals->pbase_data, status<0);
		UnlockMB (mglobals->pbase_data);
	}
	return status;
}

/*--------------------------------------------------------------------------*/
/*  Immediate Stop                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_async_stop (ViSession mvi,
		ViUInt16 io)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS, mbstatus = VI_SUCCESS;
	mviChk(mvi, mglobals);
	notNMU(mglobals);
	SpyLog2("unmbase_m_async_stop(m%d, io=%d)", mglobals->mnum, io);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;

		vxiCmd.cmd = ARMCMD_MASTOP;
		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, 2.0,
								io,
								&vxiCmd, VI_NULL);
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viQueryf(mglobals->basevi,
											"MASTOP%d %c;*ERR?\n",
											"%d",
											mglobals->mnum, IOChar[io],
											&mbstatus));
		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
		errChk(mbstatus);
	}
	else
	{
		if (io == UNMBASE_IOMODE_BOTH)      //recursively call this for OUT and IN ;)
		{
			errChk(unmbase_m_async_stop (mvi, UNMBASE_IOMODE_OUT));
			return unmbase_m_async_stop (mvi, UNMBASE_IOMODE_IN);
		}
		if (io)     //OUT
		{
			if (!mglobals->state_out)
				okChk(VI_SUCCESS);
			errChk(unmbase_m_stop_out(mglobals));
		}
		else      //IN
		{
			if (!mglobals->state_in)
				okChk(VI_SUCCESS);
			errChk(unmbase_m_async_stop_in(mglobals));
		}
	}
Error:
	if (mglobals)
	{
		//для отработки зависающих прерваний
		mglobals->badIrqTimer = 0;
		mglobals->badIrqCount = 0;

		unmbase_ErrLed((PUserData)mglobals->pbase_data, status<0);
		UnlockMB (mglobals->pbase_data);
	}
	return status;
}

/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_state (ViSession mvi,
		ViUInt16 io,
		ViInt16 *State)
{
	PM_SESSION mglobals=NULL;
	ViStatus status = VI_SUCCESS, mbstatus = VI_SUCCESS;
	ViUInt32 compl, stat;
	ViInt32 err;
	mviChk(mvi, mglobals);
	if (mglobals->basesimple)
	{
		mglobals->state_out = 0;
		mglobals->state_in = 0;
		*State = 0;
		return status;
	}
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;

		vxiCmd.cmd = ARMCMD_MSTATEq;
		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								io,
								&vxiCmd, &vxiAnsw);

		if (status < 0)
			*State = 0;
		else
			*State = (ViInt16)vxiAnsw.data16;
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viQueryf(mglobals->basevi,
											"MSTATE%d? %c;*ERR?\n",
											"%hd;%d",
											mglobals->mnum, IOChar[io],
											State, &mbstatus));
		viFlush (mglobals->basevi, VI_READ_BUF_DISCARD);
		if (mbstatus < 0)
		{
			*State = 0;
			errChk(mbstatus);
		}
	}
	else
	{
		if (mglobals->dev_type)  	//simplifyed mezzanine
		{
			if (io)
			{
				if (mglobals->state_out)
					unmbase_m_stop_out(mglobals);
				mglobals->state_out = 0;
			}
			else
			{
				if (mglobals->state_in)
					unmbase_m_stop_in(mglobals);
				mglobals->state_in = 0;
			}
			*State = 0;
			goto Error;
		}
		if (io)     //OUT
		{
			*State = mglobals->state_out;
			if (*State)
			{
				if (*State > 0)
				{
//VAV DBG
#ifdef USE_UNSPY
					{
						if (mglobals->spy_state_out != mglobals->state_out)
						{
							mglobals->spy_state_out = mglobals->state_out;
							SpyLog2("unmbase_m_state(m%do, entry state=%d), now check_err\n", mglobals->mnum, mglobals->spy_state_out);
						}
#endif
						err = unmbase_check_err(mvi, io);
//VAV DBG
#ifdef USE_UNSPY
						if (mglobals->spy_state_out != mglobals->state_out)
						{
							mglobals->spy_state_out = mglobals->state_out;
							SpyLog2("return from check_err with state=%d, err=%d\n", mglobals->spy_state_out, err);
						}
#endif
						if (err < 0)
							unmbase_m_stop_out(mglobals);
//VAV DBG
#ifdef USE_UNSPY
					}
#endif
				}
				else
					err = *State;
				if (err < 0)
				{
					SpyLog2("m%do err=%d", mglobals->mnum, err);
					*State = -1;
					switch (err)
					{
					case -1:
						SpyLog("UNMBASE_ERROR_MEZ_IO");
						errChk(UNMBASE_ERROR_MEZ_IO);
						break;
					case -2:
						SpyLog("UNMBASE_ERROR_MEZ_IO2");
						errChk(UNMBASE_ERROR_MEZ_IO2);
						break;
					case -3:
						SpyLog("UNMBASE_ERROR_INSTR");
						errChk(UNMBASE_ERROR_INSTR);
						break;
					case -4:
						SpyLog("UNMBASE_ERROR_INSTR");
						errChk(UNMBASE_ERROR_INSTR);
						break;
					case -12:
						SpyLog("UNMBASE_ERROR_MEZ_IO12");
						errChk(UNMBASE_ERROR_MEZ_IO12);
						break;
					default:        //VISA I/O Error
						errChk(err);
					}
				}
				if (mglobals->mode_out == UNMBASE_MODE_SINGLE)
				{
					errChk( viIn32(mglobals->basevi, VI_A24_SPACE,
								   rgCOMPLETE,
								   &compl));
					if ((compl & maskCOMPLETE_OUT[mglobals->midx]) != 0)
					{
						unmbase_m_stop_out(mglobals);
						*State = mglobals->state_out;
					}
				}
				else
				if (mglobals->mode_out == UNMBASE_MODE_BLOCK)
				{
					errChk( viIn32(mglobals->basevi, VI_A24_SPACE,
								   rgSTAT1,
								   &stat));
					if ((stat & maskSTAT1_OUT_ON[mglobals->midx]) == 0)
					{
						errChk( viIn32(mglobals->basevi, VI_A24_SPACE,
									   rgCOMPLETE,
									   &stat));
						if (stat & maskCOMPLETE_OUT[mglobals->midx])
						{
							unmbase_m_stop_out(mglobals);
							*State = mglobals->state_out;
						}
					}
				}

			}
		}
		else      //IN
		{
			*State = mglobals->state_in;
			if (*State)
			{
				if (*State > 0)
				{
//VAV DBG
#ifdef USE_UNSPY
					{
						if (mglobals->spy_state_in != mglobals->state_in)
						{
							mglobals->spy_state_in = mglobals->state_in;
							SpyLog2("unmbase_m_state(m%di, entry state=%d), now check_err\n", mglobals->mnum, mglobals->spy_state_in);
						}
#endif
						err = unmbase_check_err(mvi, io);
//VAV DBG
#ifdef USE_UNSPY
						if (mglobals->spy_state_in != mglobals->state_in)
						{
							mglobals->spy_state_in = mglobals->state_in;
							SpyLog2("return from check_err with state=%d, err=%d\n", mglobals->spy_state_in, err);
						}
#endif
						if (err < 0)
							unmbase_m_stop_in(mglobals);
//VAV DBG
#ifdef USE_UNSPY
					}
#endif
				}
				else
					err = *State;
				if (err < 0)
				{
					SpyLog2("m%di err=%d", mglobals->mnum, err);
					*State = -1;
					switch (err)
					{
					case -1:
						SpyLog("UNMBASE_ERROR_MEZ_IO");
						errChk(UNMBASE_ERROR_MEZ_IO);
						break;
					case -2:
						SpyLog("UNMBASE_ERROR_MEZ_IO2");
						errChk(UNMBASE_ERROR_MEZ_IO2);
						break;
					case -3:
						SpyLog("UNMBASE_ERROR_INSTR");
						errChk(UNMBASE_ERROR_INSTR);
						break;
					case -4:
						SpyLog("UNMBASE_ERROR_INSTR");
						errChk(UNMBASE_ERROR_INSTR);
						break;
					case -12:
						SpyLog("UNMBASE_ERROR_MEZ_IO12");
						errChk(UNMBASE_ERROR_MEZ_IO12);
						break;
					default:        //VISA I/O Error
						errChk(err);
					}
				}
				if (mglobals->mode_in == UNMBASE_MODE_SINGLE)
				{
					errChk( viIn32(mglobals->basevi, VI_A24_SPACE,
								   rgCOMPLETE,
								   &compl));
					if ((compl & maskCOMPLETE_IN[mglobals->midx]) != 0)
					{
						unmbase_m_stop_in(mglobals);
						*State = mglobals->state_in;
					}
				}
				else
				if (mglobals->mode_in == UNMBASE_MODE_BLOCK)
				{
					errChk( viIn32(mglobals->basevi, VI_A24_SPACE,
								   rgSTAT1,
								   &stat));
					if ((stat & maskSTAT1_IN_ON[mglobals->midx]) == 0)
					{
						if (!mglobals->async_type)
						{
							unmbase_m_stop_in(mglobals);
							*State = mglobals->state_in;
						}
						else
							*State = 0;
					}
				}

			}
		}
	}
Error:
	if (mglobals)
	{
		unmbase_ErrLed((PUserData)mglobals->pbase_data, status<0);
		UnlockMB (mglobals->pbase_data);
		if (status < 0)
			SpyLog3("unmbase_m_state(m%d, %d) return %08X\n", mglobals->mnum, io, status);
	}
	return status;
}

/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_reset (ViSession mvi, ViUInt16 io)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS;
	mviChk(mvi, mglobals);
	SpyLog1("unmbase_m_reset(m%d)", mglobals->mnum);
	if (mglobals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;

		vxiCmd.cmd = ARMCMD_MRST;
		status = armvxi_mez_cmd(mglobals, ARMVXI_LOCKUNLOCK, 2.0,
								io,
								&vxiCmd, VI_NULL);
	}
	else
	if (UNMBASE_FLAG_MB & mglobals->basetype)
	{	//==> MB
		LockMB(mglobals->pbase_data);
		errChkMB(mglobals->basevi, viPrintf(mglobals->basevi,
											"MRST%d %c\n",
											mglobals->mnum, IOChar[io]));
	}
	else
	{
		unmbase_ErrLed((PUserData)mglobals->pbase_data, 0);
		if ((io == UNMBASE_IOMODE_OUT) || (io == UNMBASE_IOMODE_BOTH))
		{
			unmbase_m_stop_out(mglobals);
			mglobals->state_out = 0;
			mglobals->next_sample_to_out = 0;   //clear memory for out
			unmbase_m_config_event (mvi, 0);
			unmbase_m_mode (mvi, UNMBASE_IOMODE_OUT, 0/*mglobals->mode_out*/);
			unmbase_m_mode (mvi, UNMBASE_IOMODE_OUT, mglobals->mode_out);
		}
		if ((io == UNMBASE_IOMODE_IN) || (io == UNMBASE_IOMODE_BOTH))
		{
			unmbase_m_stop_in(mglobals);
			mglobals->state_in = 0;
			unmbase_m_config_event (mvi, 0);
			unmbase_m_mode (mvi, UNMBASE_IOMODE_IN, 0/*mglobals->mode_in*/);
			unmbase_m_mode (mvi, UNMBASE_IOMODE_IN, mglobals->mode_in);
		}
	}
	//для отработки зависающих прерваний
	mglobals->badIrqTimer = 0;
	mglobals->badIrqCount = 0;
Error:
	if (mglobals) UnlockMB (mglobals->pbase_data);
	return status;
}

ViStatus _VI_FUNC unmbase_m_sftreset (ViSession mvi, ViUInt16 io)
{
	PM_SESSION mglobals = NULL;
	ViStatus status = VI_SUCCESS;
	mviChk(mvi, mglobals);
	if ((io == UNMBASE_IOMODE_OUT) || (io == UNMBASE_IOMODE_BOTH))
	{
		unmbase_m_stop_out(mglobals);
		mglobals->state_out = 0;
		mglobals->next_sample_to_out = 0;   //clear memory for out
		unmbase_m_config_event (mvi, 0);
		unmbase_m_mode (mvi, UNMBASE_IOMODE_OUT, 0/*mglobals->mode_out*/);
		unmbase_m_mode (mvi, UNMBASE_IOMODE_OUT, mglobals->mode_out);
	}
	if ((io == UNMBASE_IOMODE_IN) || (io == UNMBASE_IOMODE_BOTH))
	{
		unmbase_m_stop_in(mglobals);
		mglobals->state_in = 0;
		unmbase_m_config_event (mvi, 0);
		unmbase_m_mode (mvi, UNMBASE_IOMODE_IN, 0/*mglobals->mode_in*/);
		unmbase_m_mode (mvi, UNMBASE_IOMODE_IN, mglobals->mode_in);
	}
	return status;
}

/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_type_q (ViSession vi,
		ViInt16 N,
		ViInt16 *Present,
		ViInt16 *Type)
{
	PUserData globals = NULL;
	ViStatus status = 0;
	ViUInt16 word;
	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));
	CheckMezNum(globals, N);
	if (!Present)
		errChk(VI_ERROR_PARAMETER3);
	if (!Type)
		errChk(VI_ERROR_PARAMETER4);
	*Present = 0;
	*Type = 0;
	if (globals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;

		vxiCmd.cmd = ARMCMD_MTYPEq | armvxiMidxIoMask(N-1, 0);

		status = armvxi_req( globals,
					ARMVXI_LOCKUNLOCK,
					ARMVXI_TMO1,
					N > 2 ? 1 : 0,
					&vxiCmd, &vxiAnsw);
		if (status >= 0)
		{
			*Present = (ViInt16)vxiAnsw.data16;
			*Type = (ViInt16)vxiAnsw.data0;
		}
	}
	else
	if (UNMBASE_FLAG_MB & globals->basetype)
	{	//==> MB
		LockMB(globals);
		errChkMB(vi, viQueryf(vi,
							  "MTYPE%d?\n",
							  "%hd,%hd",
							  N,
							  Present, Type));
		viFlush (vi, VI_READ_BUF_DISCARD);
	}
	else
	{
		ChkInitStatus();
		errChk (viIn16 (vi, VI_A24_SPACE,
						offsMEZ[N-1]+2,     //address 2
						&word));
		*Present = (word != 0xFFFF);
		*Type = word & 0xFF;    //only lower byte
	}
Error:
	SpyLog3("unmbase_m_type_q(m%d, %d, %d)", N, *Type, *Present);
	unmbase_ErrLed(globals, status<0);
	UnlockMB (globals);
	return status;
}

/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_mem_q (ViSession vi,
		ViUInt32 *MemSize)
{
	PUserData globals = NULL;
	ViStatus status = VI_SUCCESS;
	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));
	if (!MemSize)
		errChk(VI_ERROR_PARAMETER2);
	*MemSize = 0;
	if (globals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw1, vxiAnsw2;

		vxiCmd.cmd = ARMCMD_MEMq;

		errChk(armvxi_2arms_req(globals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								&vxiCmd, &vxiAnsw1, &vxiAnsw2));

		*MemSize = vxiAnsw1.data0 + vxiAnsw2.data0;
	}
	else
	if (UNMBASE_FLAG_MB & globals->basetype)
	{	//==> MB
		LockMB(globals);
		errChkMB(vi, viQueryf(vi,
							  "MEM?\n",
							  "%u",
							  MemSize));
		viFlush (vi, VI_READ_BUF_DISCARD);
	}
	else
	{
		*MemSize = globals->mem_size;
		ChkInitStatus();
	}
Error:
	SpyLog2("unmbase_m_mem_q(%d Mb) return %X", *MemSize / (1024*1024), status);
	UnlockMB (globals);
	return status;
}

/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_config_trigger (ViSession vi,
		ViInt16 StartSource,
		ViInt16 Master,
		ViInt16 TTLTRGline)
{
	PUserData globals = NULL;
	ViStatus status = VI_SUCCESS;
	ViUInt16 word;
	SpyLog3("unmbase_config_trigger(%d, %d, %d)", StartSource, Master, TTLTRGline);
	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));

	if (UNMBASE_FLAG_MB & globals->basetype)
	{	//==> MB
		LockMB(globals);
		errChkMB(vi, viPrintf(vi,
							  "TRIGCFG %d,%d,%d\n",
							  StartSource, Master, TTLTRGline));
	}
	else
	{
		//if (globals->basetype == UNMBASE_TYPE_ARM) VAV TODO
		//Для старта оба АРМа должны быть переведены в позицию ожидания внешнего запуска,
		//и тогда можно дать через VXI сигнал ПУСК !!!
		ChkInitStatus();
		globals->start_source = StartSource;
		globals->start_master = Master;
		globals->start_ttltrg = TTLTRGline;
		errChk( viIn16(vi, VI_A16_SPACE,
					   rgCONF3,
					   &word));
		word &= ~(maskCONF3_TTLIN_LINE |
				  maskCONF3_TTLOUT_LINE |
				  maskCONF3_TTLIN_EN |
				  maskCONF3_TTLOUT_EN |
				  maskCONF3_ERRLED);
		if (StartSource)    //source - TTLTRG
		{
			word |= TTLTRGline << shiftCONF3_TTLIN_LINE;
		}
		else
		if (Master)      //source - program, master TTLTRG
		{
			word |= TTLTRGline << shiftCONF3_TTLOUT_LINE;
		}
		else      //single programm start
		{
			//word=word;
		}
		errChk( viOut16(vi, VI_A16_SPACE,
						rgCONF3,
						word));
	}
Error:
	unmbase_ErrLed(globals, status<0);
	UnlockMB (globals);
	return status;
}

/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_config_trigger_q (ViSession vi,
		ViInt16 *StartSource,
		ViInt16 *Master,
		ViInt16 *TTLTRGline)
{
	PUserData globals = NULL;
	ViStatus status = VI_SUCCESS;
	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));

	if (UNMBASE_FLAG_MB & globals->basetype)
	{	//==> MB
		LockMB(globals);
		errChkMB(vi, viQueryf(vi,
							  "TRIGCFG?\n",
							  "%hd,%hd,%hd",
							  StartSource, Master, TTLTRGline));
		viFlush (vi, VI_READ_BUF_DISCARD);
	}
	else
	{
		*StartSource = globals->start_source;
		*Master = globals->start_master;
		*TTLTRGline = globals->start_ttltrg;
	}
Error:
	UnlockMB (globals);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Time query                                                               */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_time_q (ViSession vi,
		ViUInt32 *time)
{
	PUserData globals = NULL;
	ViStatus status = VI_SUCCESS;
	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));
	notNMU(globals);
	if (!time)
		errChk(VI_ERROR_PARAMETER2);

	if (globals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		//VAV	вообще то у носителя должно быть общее время
		//		но запрашивать будем только у одного из АРМов!!!
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;

		vxiCmd.cmd = ARMCMD_TIMEq;
		status = armvxi_arm_cmd(globals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								0,
								&vxiCmd, &vxiAnsw);

		*time = vxiAnsw.data0;
	}
	else
	if (UNMBASE_FLAG_MB & globals->basetype)
	{	//==> MB
		LockMB(globals);
		errChkMB(vi, viQueryf(vi,
							  "TIME?\n",
							  "%u",
							  time));
		viFlush (vi, VI_READ_BUF_DISCARD);
	}
	else
	{
		ChkInitStatus();
		errChk( viIn32 (vi, VI_A24_SPACE,
						rgTIME,
						time));
	}
Error:
	SpyLog1("unmbase_time_q(time=%d)", *time);
	unmbase_ErrLed(globals, status<0);
	UnlockMB (globals);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Config time resolution                                                   */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_config_ticks (ViSession vi,
		ViInt16 tval)
{
	PUserData globals = NULL;
	ViStatus status = VI_SUCCESS;
	SpyLog1("unmbase_config_ticks(%d)", tval);
	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));
	notNMU(globals);
	if (invalidViInt16Range(tval, 0, 3))
		errChk(VI_ERROR_PARAMETER2);
	if (globals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;

		vxiCmd.cmd = armvxiCmdD16(ARMCMD_TICKS,
								  tval);

		errChk(armvxi_2arms_req(globals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								&vxiCmd, VI_NULL, VI_NULL));
	}
	else
	if (UNMBASE_FLAG_MB & globals->basetype)
	{	//==> MB
		LockMB(globals);
		errChkMB(vi, viPrintf(vi,
							  "TICKS %d\n",
							  tval));
	}
	else
	{
		ChkInitStatus();
		globals->tick_time = tval;
		errChk(Out32_CONF2(vi,
						   ~maskCONF2_TICK_LEN,
						   tval << shiftCONF2_TICK_LEN));
	}
Error:
	unmbase_ErrLed(globals, status<0);
	UnlockMB (globals);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Time resolution query                                                    */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_config_ticks_q (ViSession vi,
		ViInt16 *time)
{
	PUserData globals = NULL;
	ViStatus status = VI_SUCCESS;
	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));
	notNMU(globals);
	if (!time)
		errChk(VI_ERROR_PARAMETER2);
	if (globals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw;

		//запрашиваем только у первого АРМа
		vxiCmd.cmd = ARMCMD_TICKSq;

		status = armvxi_arm_cmd(globals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								0,
								&vxiCmd, &vxiAnsw);

		*time = (ViInt16)vxiAnsw.data16;
	}
	else
	if (UNMBASE_FLAG_MB & globals->basetype)
	{	//==> MB
		LockMB(globals);
		errChkMB(vi, viQueryf(vi,
							  "TICKS?\n",
							  "%hd",
							  time));
		viFlush (vi, VI_READ_BUF_DISCARD);
	}
	else
	{
		*time = globals->tick_time;
	}
Error:
	UnlockMB (globals);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Group START                                                              */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_start (ViSession vi)
{
	PUserData globals = NULL;
	ViStatus status = VI_SUCCESS;
	ViUInt16 word;
	SpyLog("unmbase_start()");
	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));
	if (UNMBASE_FLAG_MB & globals->basetype)
	{	//==> MB
		LockMB(globals);
		errChkMB(vi, viPrintf(vi,
							  "*TRG\n"));
	}
	else
	{
		ChkInitStatus();
		if (globals->basetype == UNMBASE_TYPE_ARM)
		{   //VAV TODO
			//Для старта оба АРМа должны быть переведены в позицию ожидания внешнего запуска,
			//и тогда можно дать через VXI сигнал ПУСК !!!
			VXI_CMD vxiCmd;

			vxiCmd.cmd = ARMCMD_TRG_ARM;
			errChk(armvxi_2arms_cmd(globals, ARMVXI_LOCKUNLOCK,ARMVXI_TMO1,
									&vxiCmd));


		}
		errChk( viIn16(vi, VI_A16_SPACE,
					   rgCONF3,
					   &word));
		word &= ~(maskCONF3_TTLIN_EN |
				  maskCONF3_TTLOUT_EN);
		if (globals->start_source)      //source - TTLTRG
		{
			word |= maskCONF3_TTLIN_EN;
			errChk( viOut16(vi, VI_A16_SPACE,
							rgCONF3,
							word));
		}
		else
		{
			if (globals->start_master)  //source - program, master TTLTRG
				word |= maskCONF3_TTLOUT_EN;    //sorry, this incompatible... | maskCONF3_TTLIN_EN;
			errChk( viOut16(vi, VI_A16_SPACE,
							rgCONF3,
							word));
			//source - program
			errChk( viOut16(vi, VI_A16_SPACE,
							rgCOMM3,
							maskCOMM3_IRQ_IC2_RESET |
							maskCOMM3_IRQ_IC3_RESET |
							maskCOMM3_IRQ_ALL_RESET |
							maskCOMM3_START));
			viOut16(vi, VI_A16_SPACE, rgCOMM3, 0);

		}
	}
Error:
	unmbase_ErrLed(globals, status<0);
	UnlockMB (globals);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Group STOP                                                               */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_stop (ViSession vi)
{
	PUserData globals = NULL;
	ViStatus status = VI_SUCCESS;
	ViUInt16 word, i;
	SpyLog("unmbase_stop()");
	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));
	if (UNMBASE_FLAG_MB & globals->basetype)
	{	//==> MB
		LockMB(globals);
		errChkMB(vi, viPrintf(vi,
							  "STOP\n"));
	}
	else
	{
		//if (globals->basetype == UNMBASE_TYPE_ARM) VAV TODO
		//вроде бы для АРМ аналогично
		ChkInitStatus();
		errChk( viIn16(vi, VI_A16_SPACE,
					   rgCONF3,
					   &word));
		word &= ~(maskCONF3_TTLIN_EN |
				  maskCONF3_TTLOUT_EN);
		errChk( viOut16(vi, VI_A16_SPACE,
						rgCONF3,
						word));

		///////////////////////////////////////
		errChk( viOut16(vi, VI_A16_SPACE,		//ПОЧЕМУ ТО РАНЬШЕ ДЛЯ НЕ-УПРОЩЕННОЙ БАЗЫ НЕ ДЕЛАЛ...
						rgCOMM3,
						rgCOMM3_DEFAULT));
		viOut16(vi, VI_A16_SPACE, rgCOMM3, 0);
		///////////////////////////////////////
		for (i=0; i<4; i++)
		{
			if (globals->m_vi_idx[i] != -1)
			{
				unmbase_m_stop(MVI_ID |globals->m_vi_idx[i], UNMBASE_IOMODE_BOTH);
			}
			globals->m_session[i].state_in = 0;
			globals->m_session[i].state_out = 0;
			globals->m_session[i].next_sample_to_out = 0;   //clear memory for out
		}
	}
Error:
	unmbase_ErrLed(globals, status<0);
	UnlockMB (globals);
	return status;
}

/*--------------------------------------------------------------------------*/
/* State of BASE                                                            */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_state (ViSession vi,
		ViInt16 *State)
{
	PUserData globals = NULL;
	ViStatus status = VI_SUCCESS;
	ViInt16 i, state;
	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));
	if (globals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		//для обеих ARM опрос состояния и совмещение
		VXI_CMD vxiCmd;
		VXI_ANSW vxiAnsw1, vxiAnsw2;

		vxiCmd.cmd = ARMCMD_STATEq;

		errChk(armvxi_2arms_req(globals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								&vxiCmd, &vxiAnsw1, &vxiAnsw2));

		*State = (0x3 & vxiAnsw1.data16) | ((0x3 & vxiAnsw2.data16) << 2);
	}
	else
	if (UNMBASE_FLAG_MB & globals->basetype)
	{	//==> MB
		LockMB(globals);
		errChkMB(vi, viQueryf(vi,
							  "STATE?\n",
							  "%hd",
							  State));
		viFlush (vi, VI_READ_BUF_DISCARD);
	}
	else
	{
		ChkInitStatus();

		*State = 0;
		for (i=0; i<4; i++)
		{
			//Check IN
			if (globals->m_session[i].state_in)
				status = unmbase_m_state (MVI_ID |globals->m_vi_idx[i], UNMBASE_IOMODE_IN, &state); //check state
			//Check OUT
			if (globals->m_session[i].state_out)
				status = unmbase_m_state (MVI_ID |globals->m_vi_idx[i], UNMBASE_IOMODE_OUT, &state);    //check state
			*State |= ((globals->m_session[i].state_in > 0) || (globals->m_session[i].state_out > 0)) << i;
		}
	}
Error:
#ifdef USE_UNSPY
	{
		if (globals->spy_state != *State)
		{
			globals->spy_state = *State;
			SpyLog1("unmbase_state(state=%04X)", *State);
		}
	}
#endif
	unmbase_ErrLed(globals, status<0);
	UnlockMB (globals);
	return status;
}

/*--------------------------------------------------------------------------*/
/* Enable Time Reset on START (TTLTRG or maskCOMM3_START)                   */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_time_sync (ViSession vi, ViBoolean dosync)
{
	PUserData globals = NULL;
	ViStatus status = VI_SUCCESS;
	SpyLog1("unmbase_time_sync(%d)", dosync);
	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));
	notNMU(globals);
	if (globals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;

		vxiCmd.cmd = armvxiCmdD16(ARMCMD_TIMESYNC,
								  dosync);

		errChk(armvxi_2arms_req(globals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
								&vxiCmd, VI_NULL, VI_NULL));
	}
	else
	if (UNMBASE_FLAG_MB & globals->basetype)
	{	//==> MB
		LockMB(globals);
		errChkMB(vi, viPrintf(vi,
							  "TIMESYNC %d\n",
							  dosync));
	}
	else
	{
		ChkInitStatus();
		if (dosync)
			errChk( Out32_CONF2(vi,
								~0,
								maskCONF2_RESTIME_EN));
		else
			errChk( Out32_CONF2(vi,
								~maskCONF2_RESTIME_EN,
								0 ));
	}
Error:
	unmbase_ErrLed(globals, status<0);
	UnlockMB (globals);
	return status;
}

/*--------------------------------------------------------------------------*/
/* RESET                                                                    */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_reset (ViSession vi)
{
	PUserData globals = NULL;
	ViStatus status = VI_SUCCESS;
	ViInt32 i;
	ViUInt16 word16;
	SpyLog("unmbase_reset()");
	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));

	if (UNMBASE_FLAG_MB & globals->basetype)
	{	//==> MB
		LockMB(globals);
		viClear(vi);
		status = viPrintf(vi,
						  "*RST\n");
		UnlockMB(globals);
		if (status >= 0)
		{
			//then reset callback for all mezzanines
			for (i=0; i<globals->maxMez; i++)
			{
				if (globals->m_vi_idx[i] != -1)
				{
					if (globals->m_session[i].user_handler !=(ViAddr) VI_NULL)
						(* ((unmbase_UserHandler) globals->m_session[i].user_handler))
						(globals->m_session[i].extvi ? globals->m_session[i].extvi : MVI_ID |globals->m_vi_idx[i],
						 UNMBASE_EVENT_RESET);
				}
			}
		}
		return status;

	}
	if (globals->basetype == UNMBASE_TYPE_ARM)
	{	//==> ARM
		VXI_CMD vxiCmd;

		unmbase_ErrLed(globals, 0);
		ChkInitStatus();

		vxiCmd.cmd = ARMCMD_RST;

		errChk(armvxi_2arms_req(globals, ARMVXI_LOCKUNLOCK, 2.0,
								&vxiCmd, VI_NULL, VI_NULL));
		for (i=0; i<4; i++)
		{
			if (globals->m_vi_idx[i] != -1)
			{
				if (globals->m_session[i].user_handler !=(ViAddr) VI_NULL)
					(* ((unmbase_UserHandler) globals->m_session[i].user_handler))
					(globals->m_session[i].extvi ? globals->m_session[i].extvi : MVI_ID |globals->m_vi_idx[i],
					 UNMBASE_EVENT_RESET);

				globals->m_session[i].state_in = 0;
				globals->m_session[i].state_out = 0;
			}
		}
	}
	else
	{
		unmbase_ErrLed(globals, 0);
		ChkInitStatus();
		//просто останов носителя
		unmbase_stop (vi);


		if (globals->basesimple)  	//упрощенный!
		{
			//сначала сброс по биту сброса
			errChk( viIn16(vi, VI_A16_SPACE, rgS, &word16));
			word16 |= maskC_reset;
			errChk( viOut16(vi, VI_A16_SPACE, rgC, word16));
			cross_delay(0.001);
			word16 &= ~maskC_reset;
			errChk( viOut16(vi, VI_A16_SPACE, rgC, word16 | maskC_EN_A24));

			errChk( viOut16(vi, VI_A16_SPACE, rgCOMM3, rgCOMM3_DEFAULT));
			viOut16(vi, VI_A16_SPACE, rgCOMM3, 0);
			errChk( Out16_CONF3(vi,
								((ViUInt16)~0xF000),
								maskCONF3_START_SHORT_IN | maskCONF3_START_SHORT_OUT));
			//then reset callback for all mezzanines
			for (i=0; i<4; i++)
			{
				if (globals->m_vi_idx[i] != -1)
				{
					unmbase_m_stop(globals->m_vi_idx[i], UNMBASE_IOMODE_BOTH);
					if (globals->m_session[i].user_handler !=(ViAddr) VI_NULL)
						(* ((unmbase_UserHandler) globals->m_session[i].user_handler))
						(globals->m_session[i].extvi ? globals->m_session[i].extvi : MVI_ID |globals->m_vi_idx[i],
						 UNMBASE_EVENT_RESET);
				}
				globals->m_session[i].state_in = 0;
				globals->m_session[i].state_out = 0;
			}
		}
		else  								//не упрощенный! но может быть АРМ!!!
		{
			//сначала останов и reset callback for all mezzanines
			for (i=0; i<4; i++)
			{
				if (globals->m_vi_idx[i] != -1)
				{
					unmbase_m_stop_out(&globals->m_session[i]);
					unmbase_m_stop_in(&globals->m_session[i]);
					if (globals->m_session[i].user_handler !=(ViAddr) VI_NULL)
						(* ((unmbase_UserHandler) globals->m_session[i].user_handler))
						(globals->m_session[i].extvi ? globals->m_session[i].extvi : MVI_ID |globals->m_vi_idx[i],
						 UNMBASE_EVENT_RESET);

					if (globals->m_session[i].dev_type)
					{
						//организация возможности запуска упрощенного мезонина от обычного носителя notNMU
						;//	делается это в конце!!! errChk(PrepareSimpleMez(globals->vi, i));
					}
					else
					{
						STARTSTOP_Enable(vi, 1);
						errChk( viOut32(vi, VI_A24_SPACE, rgLIMIT_IN[i], 0x00FFFFFF));
						errChk( viOut32(vi, VI_A24_SPACE, rgSTOP_IN[i], 0x00FFFFFF));
						errChk( viOut32(vi, VI_A24_SPACE, rgSTART_IN[i], 0x00FFFFF0));
						errChk( viOut32(vi, VI_A24_SPACE, rgLIMIT_OUT[i], 0x00FFFFFF));
						errChk( viOut32(vi, VI_A24_SPACE, rgSTOP_OUT[i], 0x00FFFFFF));
						errChk( viOut32(vi, VI_A24_SPACE, rgSTART_OUT[i], 0x00FFFFF0));
						STARTSTOP_Enable(vi, 0);
					}
					globals->m_session[i].state_in = 0;
					globals->m_session[i].state_out = 0;
					globals->m_session[i].next_sample_to_out = 0;   //clear memory for out
				}
			}
			//сброс по биту сброса
			errChk( viIn16(vi, VI_A16_SPACE, rgS, &word16));
			word16 |= maskC_reset;
			errChk( viOut16(vi, VI_A16_SPACE, rgC, word16));
			cross_delay(0.001);
			word16 &= ~maskC_reset;
			errChk( viOut16(vi, VI_A16_SPACE, rgC, word16 | maskC_EN_A24));

			//теперь сброс собственно носителя
			errChk( viOut32(vi, VI_A24_SPACE, rgMASKCOMM1, 0xFFFFFFFF));
			errChk( viOut32(vi, VI_A24_SPACE, rgCOMM1, rgCOMM1_DEFAULT));
			errChk( viOut32(vi, VI_A24_SPACE, rgMASKCOMM2, 0xFFFFFFFF));
			errChk( viOut32(vi, VI_A24_SPACE, rgCOMM2, rgCOMM2_DEFAULT));
			errChk( viOut32(vi, VI_A24_SPACE, rgCOMM2A, rgCOMM2A_DEFAULT));
			errChk( viOut16(vi, VI_A16_SPACE, rgCOMM3, rgCOMM3_DEFAULT));
			viOut16(vi, VI_A16_SPACE, rgCOMM3, 0);
			errChk( viOut32(vi, VI_A24_SPACE, rgENDIRQ, rgENDIRQ_DEFAULT));
			cross_delay(0.001);

			status = ResetFIFO_VXI(vi, globals);
			cross_delay(0.001);
			errChk( ConfigRAM(vi, globals->spd1[0] ? globals->spd1 : globals->spd2));   //both RAM must be identical, so config for one of the SPD
			cross_delay(0.001);

			globals->state = 0;
			//now restore important hardware settings
			unmbase_config_ticks (vi, globals->tick_time);

			for (i=0; i<4; i++)
			{
				if (globals->m_vi_idx[i] != -1)
				{
					if (globals->m_session[i].dev_type)
					{
						//восстановление возможности запуска упрощенного мезонина от обычного носителя notNMU
						errChk(PrepareSimpleMez(globals->vi, i));
					}
					//и для всех мезонинов некоторые параметры...
					errChk( Out32_COMM2A(vi,
										 ~maskCOMM2A_M_WAITSTOP[i],
										 globals->m_session[i].trig_length ? maskCOMM2A_M_WAITSTOP[i] : 0));

					if (globals->m_session[i].first_delay_in >=2)
						errChk( viOut32 (vi, VI_A24_SPACE,
										 rgZ_IN[i],
										 globals->m_session[i].first_delay_in-2));

					if (globals->m_session[i].first_delay_out >=2)
						errChk( viOut32 (vi, VI_A24_SPACE,
										 rgZ_OUT[i],
										 globals->m_session[i].first_delay_out-2));
				}
			}
		}
		unmbase_config_trigger (vi,
								globals->start_source,
								globals->start_master,
								globals->start_ttltrg);
	}
Error:
	if (globals && globals->basetype != UNMBASE_TYPE_ARM)
		STARTSTOP_Enable(vi, 0);
	cross_delay(0.04);
	return status;
}

ViStatus _VI_FUNC unmbase_sftreset (ViSession vi)
{
	PUserData globals = NULL;
	ViStatus status = VI_SUCCESS;
	ViInt32 i;
	ViUInt16 word16;
	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));
	unmbase_ErrLed(globals, 0);
	ChkInitStatus();

	//просто останов носителя
	unmbase_stop (vi);


	if (globals->basesimple)  	//упрощенный!
	{
		//сначала сброс по биту сброса
		errChk( viIn16(vi, VI_A16_SPACE, rgS, &word16));
		word16 |= maskC_reset;
		errChk( viOut16(vi, VI_A16_SPACE, rgC, word16));
		cross_delay(0.001);
		word16 &= ~maskC_reset;
		errChk( viOut16(vi, VI_A16_SPACE, rgC, word16 | maskC_EN_A24));

		errChk( viOut16(vi, VI_A16_SPACE, rgCOMM3, rgCOMM3_DEFAULT));
		viOut16(vi, VI_A16_SPACE, rgCOMM3, 0);
		errChk( Out16_CONF3(vi,
							((ViUInt16)~0xF000),
							maskCONF3_START_SHORT_IN | maskCONF3_START_SHORT_OUT));
	}
	else  								//не упрощенный!
	{
		//сначала останов и reset callback for all mezzanines
		for (i=0; i<4; i++)
		{
			if (globals->m_vi_idx[i] != -1)
			{
				//unmbase_m_stop(MVI_ID |globals->m_vi_idx[i], UNMBASE_IOMODE_BOTH);
				unmbase_m_stop_out(&globals->m_session[i]);
				unmbase_m_stop_in(&globals->m_session[i]);
				if (globals->basetype != UNMBASE_TYPE_ARM)
				{
					if (globals->m_session[i].dev_type)
					{
						//организация возможности запуска упрощенного мезонина от обычного носителя notNMU
						;// делается это в конце errChk(PrepareSimpleMez(globals->vi, i));
					}
					else
					{
						STARTSTOP_Enable(vi, 1);
						errChk( viOut32(vi, VI_A24_SPACE, rgLIMIT_IN[i], 0x00FFFFFF));
						errChk( viOut32(vi, VI_A24_SPACE, rgSTOP_IN[i], 0x00FFFFFF));
						errChk( viOut32(vi, VI_A24_SPACE, rgSTART_IN[i], 0x00FFFFF0));
						errChk( viOut32(vi, VI_A24_SPACE, rgLIMIT_OUT[i], 0x00FFFFFF));
						errChk( viOut32(vi, VI_A24_SPACE, rgSTOP_OUT[i], 0x00FFFFFF));
						errChk( viOut32(vi, VI_A24_SPACE, rgSTART_OUT[i], 0x00FFFFF0));
						STARTSTOP_Enable(vi, 0);
					}
				}
				globals->m_session[i].state_in = 0;
				globals->m_session[i].state_out = 0;
				globals->m_session[i].next_sample_to_out = 0;   //clear memory for out
			}
		}
		if (globals->basetype != UNMBASE_TYPE_ARM)
		{
			//сброс по биту сброса
			errChk( viIn16(vi, VI_A16_SPACE, rgS, &word16));
			word16 |= maskC_reset;
			errChk( viOut16(vi, VI_A16_SPACE, rgC, word16));
			cross_delay(0.001);
			word16 &= ~maskC_reset;
			errChk( viOut16(vi, VI_A16_SPACE, rgC, word16 | maskC_EN_A24));
			//теперь сброс собственно носителя
			errChk( viOut32(vi, VI_A24_SPACE, rgMASKCOMM1, 0xFFFFFFFF));
			errChk( viOut32(vi, VI_A24_SPACE, rgCOMM1, rgCOMM1_DEFAULT));
			errChk( viOut32(vi, VI_A24_SPACE, rgMASKCOMM2, 0xFFFFFFFF));
			errChk( viOut32(vi, VI_A24_SPACE, rgCOMM2, rgCOMM2_DEFAULT));
			errChk( viOut32(vi, VI_A24_SPACE, rgCOMM2A, rgCOMM2A_DEFAULT));
			errChk( viOut16(vi, VI_A16_SPACE, rgCOMM3, rgCOMM3_DEFAULT));
			viOut16(vi, VI_A16_SPACE, rgCOMM3, 0);
			errChk( viOut32(vi, VI_A24_SPACE, rgENDIRQ, rgENDIRQ_DEFAULT));
			cross_delay(0.001);

			status = ResetFIFO_VXI(vi, globals);
			cross_delay(0.001);
			errChk( ConfigRAM(vi, globals->spd1[0] ? globals->spd1 : globals->spd2));   //both RAM must be identical, so config for one of the SPD
			cross_delay(0.001);
		}

		globals->state = 0;
//now restore important hardware settings
		unmbase_config_ticks (vi, globals->tick_time);
		//восстановление возможности запуска упрощенного мезонина от обычного носителя notNMU
		for (i=0; i<4; i++)
		{
			if (globals->m_vi_idx[i] != -1)
			{
				if (globals->m_session[i].dev_type)
				{
					errChk(PrepareSimpleMez(globals->vi, i));
				}
			}
		}
	}
	unmbase_config_trigger (vi,
							globals->start_source,
							globals->start_master,
							globals->start_ttltrg);
Error:
	if (globals && globals->basetype != UNMBASE_TYPE_ARM)
		STARTSTOP_Enable(vi, 0);
	cross_delay(0.04);
	return status;
}

/*--------------------------------------------------------------------------*/
/* SELF TEST                                                                */
/*--------------------------------------------------------------------------*/
///////////////////All About IMMITATOR///////////////////
_UNMBASE_API ViStatus _VI_FUNC unmbase_imm_on (ViSession vi,
		ViUInt16 num,
		ViUInt16 bit33,
		ViUInt16 data_valid,
		ViUInt16 empty)
{
	PUserData globals = NULL;
	ViStatus status = VI_SUCCESS;
	ViUInt32 word;
	SpyLog("unmbase_imm_on");
	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));
	notNMU(globals);
	errChk( viIn32(vi, VI_A24_SPACE,
				   rgCONF2,
				   &word));

	word &= ~(maskCONF2_IN4_IMM |
			  maskCONF2_OUT4_IMM |
			  maskCONF2_IMM_D33 |
			  maskCONF2_IMM_IN_ERR2 |
			  maskCONF2_IMM_OUT_ERR2);

	word |= maskCONF2_IN_IMM[num-1] |
			maskCONF2_OUT_IMM[num-1] |
			(bit33 ? maskCONF2_IMM_D33 : 0) |
			(data_valid ? maskCONF2_IMM_IN_ERR2 : 0) |
			(empty ? maskCONF2_IMM_OUT_ERR2 : 0) |
			maskCONF2_IMM_LOOP_EN;

	errChk( viOut32(vi, VI_A24_SPACE,
					rgCONF2,
					word));
	globals->imm_on = 1;
Error:
	unmbase_ErrLed(globals, status<0);
	return status;
}
//-------------------------------------------
_UNMBASE_API ViStatus _VI_FUNC unmbase_imm_off (ViSession vi)
{
	PUserData globals = NULL;
	ViStatus status = VI_SUCCESS;
	ViUInt32 word;
	SpyLog("unmbase_imm_off");
	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));
	notNMU(globals);

	errChk( viIn32(vi, VI_A24_SPACE,
				   rgCONF2,
				   &word));

	word &= ~maskCONF2_IMM_LOOP_EN;

	errChk( viOut32(vi, VI_A24_SPACE,
					rgCONF2,
					word));
	globals->imm_on = 0;
Error:
	unmbase_ErrLed(globals, status<0);
	return status;
}

/*--------------------------------------------------------------------------*/
/*       SELF TEST ROUTINE                                                  */
/*--------------------------------------------------------------------------*/
#ifdef TECHNO
extern unsigned char *buff_in, *buff_out;	//VAV2 DEBUG
#define TECHNO_DATA
#else
#define TECHNO_DATA static
#endif
TECHNO_DATA ViUInt32 unmbase_DEBUG_DELAY_IN = 1000;
TECHNO_DATA ViUInt32 unmbase_DEBUG_DELAY_OUT = 1000-(160+2);
TECHNO_DATA ViUInt32 unmbase_DEBUG_CLOCK = 2*160+2+4;
TECHNO_DATA ViUInt32 unmbase_DEBUG_NCYCLES = 1;
TECHNO_DATA ViUInt32 unmbase_DEBUG_NSAMPLES = 100;
TECHNO_DATA ViUInt32 unmbase_DEBUG_1ST_M = 4;
TECHNO_DATA ViUInt32 unmbase_DEBUG_WIDTH = 16;
#ifdef TECHNO
TECHNO_DATA ViUInt32 unmbase_DEBUG_START_DELAY = 0;
#endif

static const ViChar *err_io = {"Ошибка ввода вывода при самоконтроле"};
static const ViChar *err_data = {"Ошибка данных: записано 0x%04X, прочитано 0x%04X"};

static ViInt32 sftCmpInt(const ViUInt32 *buf1, const ViUInt32 *buf2, ViInt32 cnt)
{
	int i;
	for (i=0; i<cnt; i++)
	{
		if (buf1[i] != buf2[i])
			return i;
	}
	return -1;
}

static ViStatus _VI_FUNC unmbase_v1_self_test (ViSession vi, PUserData globals,
		ViInt16 *TestResult,
		ViChar _VI_FAR TestMessage[])
{
	ViStatus status = VI_SUCCESS;
	M_SESSION *imm_session;
	PM_SESSION old_m_sessions[4];
	ViSession old_mvi[4] = {0,0,0,0};

	ViSession imm_vi=0;
	ViInt16 mez_n, statein=0, stateout=0;
	ViUInt32 *inbuff = 0, *outbuff = 0, i;
	ViUInt32 inbuffaddr, outbuffaddr;

	ViUInt32 saveConf1=-1, saveConf2=0;

	ViUInt16 old_alloc_num[MAX_MEM_BLOCKS]; //mezzanine owners of MAX_MEM_BLOCKS ram areas (0 - free area)
	ViUInt16 old_alloc_io[MAX_MEM_BLOCKS];  //io owners of MAX_MEM_BLOCKS ram areas
	ViUInt32 old_alloc_ptr[MAX_MEM_BLOCKS]; //pointers to MAX_MEM_BLOCKS ram areas
	ViUInt32 old_alloc_size[MAX_MEM_BLOCKS];    //size of MAX_MEM_BLOCKS ram areas (0 - no more ram)

	ViUInt32 NCyclesSFT=1;

#define MAX_CECNT	10
#define MAX_CECNT2	3

	ViInt32	CEcnt;
	ViInt32 CEidx;
	ViUInt32 CEdiff;
	ViUInt32 CEaddr;

	//store old allocations for restoration
	memcpy (old_alloc_num, globals->alloc_num, sizeof(*old_alloc_num)*MAX_MEM_BLOCKS);
	memcpy (old_alloc_io, globals->alloc_io, sizeof(*old_alloc_io)*MAX_MEM_BLOCKS);
	memcpy (old_alloc_ptr, globals->alloc_ptr, sizeof(*old_alloc_ptr)*MAX_MEM_BLOCKS);
	memcpy (old_alloc_size, globals->alloc_size, sizeof(*old_alloc_size)*MAX_MEM_BLOCKS);
	//store old m_sessions
	for (i=0; i<4; i++)
	{
		if (globals->m_vi_idx[i] != -1)
		{
			old_mvi[i] = MVI_ID | globals->m_vi_idx[i];
			old_m_sessions[i] = (PM_SESSION)malloc(sizeof(M_SESSION));
			//wait for any other threads can stop in and out and we lock it!!!
			if (InterlockedExchange(&globals->m_session[i].stop_out_busy, 1))
			{
				while (InterlockedExchange(&globals->m_session[i].stop_out_busy, 1))
				{
					cross_switch_thread();
				}
			}
			if (InterlockedExchange(&globals->m_session[i].stop_in_busy, 1))
			{
				while (InterlockedExchange(&globals->m_session[i].stop_in_busy, 1))
				{
					cross_switch_thread();
				}
			}
			memcpy(old_m_sessions[i], &globals->m_session[i], sizeof(M_SESSION));
			unmbase_m_close(MVI_ID |globals->m_vi_idx[i]);
			//memset(&globals->m_session[i], 0, sizeof(M_SESSION));
		}
		else old_m_sessions[i] = 0;
	}

	if (globals->init_status)
	{
		unmbase_error_message (VI_NULL, globals->init_status, TestMessage);
		*TestResult = 1;    //init stage error
		errChk(UNMBASE_ERROR_SELFTEST);
	}
	errChk( viIn32(vi, VI_A24_SPACE, rgCONF1, &saveConf1));
	errChk( viIn32(vi, VI_A24_SPACE, rgCONF2, &saveConf2));
	errChk( Out32_CONF1(vi, rgCONF1_DEFAULT_MASK, rgCONF1_DEFAULT));
	errChk( viOut32(vi, VI_A24_SPACE, rgCONF2, rgCONF2_DEFAULT));

	errChk(unmbase_config_trigger (vi, 0, 0, 0));

#ifdef UNMBASE_DEBUG_CVI
	inbuff = (ViUInt32*)malloc(4*unmbase_DEBUG_NSAMPLES*unmbase_DEBUG_WIDTH*4);
	outbuff = (ViUInt32*)malloc(4*unmbase_DEBUG_NSAMPLES*unmbase_DEBUG_WIDTH*4);
#else
	inbuff = (ViUInt32*)malloc(unmbase_DEBUG_NSAMPLES*unmbase_DEBUG_WIDTH*4);
	outbuff = (ViUInt32*)malloc(unmbase_DEBUG_NSAMPLES*unmbase_DEBUG_WIDTH*4);
#endif
	if (!(inbuff && outbuff))   //can't allocate
	{
		strcpy(TestMessage, "Недостаточно свободной памяти для проведения полного теста");
		*TestResult = 2;
		errChk(UNMBASE_ERROR_SELFTEST);
	}
	//Checks with immitator
//  mez_n = -1;
//  while (mez_n < 3) {
//      mez_n++;
	mez_n = (ViInt16)unmbase_DEBUG_1ST_M;
	while (mez_n)
	{
		mez_n--;
		memset(globals->alloc_size, 0, sizeof(*old_alloc_size)*MAX_MEM_BLOCKS);
		memset(globals->alloc_ptr, 0, sizeof(*old_alloc_ptr)*MAX_MEM_BLOCKS);
		memset(globals->alloc_num, 0, sizeof(*old_alloc_num)*MAX_MEM_BLOCKS);
		globals->alloc_size[0] = globals->mem_size;
		errChk(unmbase_imm_on (vi,
							   mez_n+1,
							   0,      //bit33,
							   0,      //data_valid,
							   0));        //empty);
		imm_session = &globals->m_session[mez_n];
		errChk(unmbase_m_init (vi, mez_n+1, &imm_vi));

		status = unmbase_m_alloc (imm_vi, UNMBASE_IOMODE_IN, unmbase_DEBUG_NSAMPLES*unmbase_DEBUG_WIDTH*4, &inbuffaddr);    //10 blocks
		status |= unmbase_m_alloc (imm_vi, UNMBASE_IOMODE_OUT, unmbase_DEBUG_NSAMPLES*unmbase_DEBUG_WIDTH*4, &outbuffaddr); //10 blocks
		if (status)     //can't allocate RAM
		{
			strcpy(TestMessage, "Недостаточно свободной памяти в модуле для проведения полного теста");
			*TestResult = 2;    //not enough room for immitator
			errChk(UNMBASE_ERROR_SELFTEST);
		}
		for (NCyclesSFT=1; NCyclesSFT<=unmbase_DEBUG_NCYCLES; NCyclesSFT++)     //???DEBUG
		{

			errChk(unmbase_m_clock (imm_vi,
									UNMBASE_IOMODE_IN,
									unmbase_DEBUG_CLOCK));  //2*160+2+4));
			errChk(unmbase_m_clock (imm_vi,
									UNMBASE_IOMODE_OUT,
									unmbase_DEBUG_CLOCK));  //2*160+2+4));
			errChk(unmbase_m_first_delay (imm_vi,
										  UNMBASE_IOMODE_IN,
										  unmbase_DEBUG_DELAY_IN));   //1000));
			errChk(unmbase_m_first_delay (imm_vi,
										  UNMBASE_IOMODE_OUT,
										  unmbase_DEBUG_DELAY_OUT));  //1000-(160+2)));

			errChk(unmbase_m_trig_length (imm_vi, 1));

			errChk(unmbase_m_sample_width (imm_vi,
										   UNMBASE_IOMODE_IN,
										   unmbase_DEBUG_WIDTH));
			errChk(unmbase_m_sample_width (imm_vi,
										   UNMBASE_IOMODE_OUT,
										   unmbase_DEBUG_WIDTH));
			errChk(unmbase_m_mode (imm_vi,
								   UNMBASE_IOMODE_IN,
								   UNMBASE_MODE_BLOCK));
			errChk(unmbase_m_mode (imm_vi,
								   UNMBASE_IOMODE_OUT,
								   UNMBASE_MODE_BLOCK));
			errChk(unmbase_m_block_size (imm_vi,
										 UNMBASE_IOMODE_IN,
										 unmbase_DEBUG_NSAMPLES));   //40
			errChk(unmbase_m_block_size (imm_vi,
										 UNMBASE_IOMODE_OUT,
										 unmbase_DEBUG_NSAMPLES));   //40
			errChk(unmbase_m_config_trigger (imm_vi,
											 UNMBASE_IOMODE_IN,
											 0));
			errChk(unmbase_m_config_trigger (imm_vi,
											 UNMBASE_IOMODE_OUT,
											 0));
			errChk(unmbase_m_config_event (imm_vi, 0));
			srand((unsigned int)(1000.0*cross_timer()));
			for (i=0; i<(unmbase_DEBUG_NSAMPLES*unmbase_DEBUG_WIDTH); i++)
				outbuff[i] = (0x3 & rand()) | (ViUInt32)((double)0xFFFFFFFF/(double)RAND_MAX) * rand();

			CEcnt=MAX_CECNT;
			CEdiff = 0;
			CEaddr = 0;
cecnt1:
			errChk(unmbase_m_write_block (imm_vi, 0, unmbase_DEBUG_NSAMPLES, outbuff));

			//check RAM data integrity
			errChk(m_data_read(imm_session,  outbuffaddr-inbuffaddr,  unmbase_DEBUG_NSAMPLES*unmbase_DEBUG_WIDTH*4, (ViUInt8 *)inbuff));

			CEidx = sftCmpInt(inbuff, outbuff, unmbase_DEBUG_NSAMPLES*unmbase_DEBUG_WIDTH);
			if (CEidx >= 0)
			{
				CEdiff |= outbuff[CEidx] ^ inbuff[CEidx];
				if (!CEaddr)
					CEaddr = outbuffaddr;
				else
				if (CEaddr != outbuffaddr)
					CEaddr = 0xFFFFFFFF;
				if (CEcnt--)
				{
					if (!CEidx &&
						(inbuff[1] == outbuff[0] ||
						inbuff[0] == outbuff[1]))
					{
#ifdef TECHNO	//VAV2 DBG
						printf("write %08X,%08X, read %08X,%08X\n",
								outbuff[0],
								outbuff[1],
								inbuff[0],
								inbuff[1]);
#endif
#ifdef UNMBASE_DEBUG_CVI
						printf("%d left, write %08X,%08X, read %08X,%08X\n",
								CEcnt,
								outbuff[0],
								outbuff[1],
								inbuff[0],
								inbuff[1]);
#endif
						SpyLog5("%d left, write %08X,%08X, read %08X,%08X\n",
								CEcnt,
								outbuff[0],
								outbuff[1],
								inbuff[0],
								inbuff[1]);
					}
					else
					{
#ifdef TECHNO	//VAV2 DBG
						printf("don't compare at %08X (%08X-%08X)\n", outbuffaddr, outbuff[CEidx], inbuff[CEidx]);
#endif
#ifdef UNMBASE_DEBUG_CVI
						printf("%d left, don't compare at %08X (%08X-%08X)\n", CEcnt, outbuffaddr, outbuff[CEidx], inbuff[CEidx]);
#endif
						SpyLog3("don't compare at %08X (%08X-%08X)\n", outbuffaddr, outbuff[CEidx], inbuff[CEidx]);
					}
					goto cecnt1;
				}
#ifdef TECHNO	//VAV2 DBG
				memcpy(buff_in, inbuff, unmbase_DEBUG_NSAMPLES*unmbase_DEBUG_WIDTH*4);
				memcpy(buff_out, outbuff, unmbase_DEBUG_NSAMPLES*unmbase_DEBUG_WIDTH*4);
#endif
				/*
				sprintf(TestMessage,
						"Не совпадают данные записи(%08X)/чтения(%08X) в память %08X модуля",
						*outbuff, *inbuff, outbuffaddr);
				*/
				if (!CEidx &&
					(inbuff[1] == outbuff[0] ||
					inbuff[0] == outbuff[1]))
				{
					sprintf(TestMessage,
						"При записи/чтении в память смещены данные чтения");
				}
				else
				if (0xFFFFFFFF == CEaddr)
				{
					sprintf(TestMessage,
						"Не совпадают данные записи/чтения в память, биты %08X",
						CEdiff);
				}
				else
				{
					sprintf(TestMessage,
						"Не совпадают данные записи/чтения в память, адрес %08X, биты %08X",
						CEaddr, CEdiff);
				}
				*TestResult = 4;    //Bad I/O
				errChk(UNMBASE_ERROR_SELFTEST);
			}
			inbuff[0]++;    //if now we do not read correctly, inbuff != outbuff

			CEcnt=MAX_CECNT2;
			CEdiff = 0;
			CEaddr = 0;
cecnt2:
			errChk(unmbase_m_start (imm_vi, UNMBASE_IOMODE_BOTH));      //start IN and OUT
#ifdef TECHNO
			if (unmbase_DEBUG_START_DELAY)
				cross_delay (((double)unmbase_DEBUG_START_DELAY)/1000.0);
#endif
			i = 1000 +
				unmbase_DEBUG_NSAMPLES * unmbase_DEBUG_WIDTH * unmbase_DEBUG_CLOCK;
			do
			{
				status = unmbase_m_state (imm_vi, UNMBASE_IOMODE_IN, &statein);
				if (status >= 0)
					status = unmbase_m_state (imm_vi, UNMBASE_IOMODE_OUT, &stateout);
				i--;

			} while (i && (statein || stateout) && (status >= 0));

			unmbase_m_stop (imm_vi, UNMBASE_IOMODE_BOTH);
			unmbase_m_stop (imm_vi, UNMBASE_IOMODE_BOTH);
			if (status < 0)
			{
				unmbase_error_message (VI_NULL, status, TestMessage);
				*TestResult = 4;    //Bad I/O
				errChk(UNMBASE_ERROR_SELFTEST);
			}
			if (i == 0)
			{
				if (statein &&stateout)
					sprintf(TestMessage, "Не завершены режимы ввода/вывода при проверке связи с мезонином %d", mez_n+1);
				else
				if (statein)
					sprintf(TestMessage, "Не завершен режим ввода при проверке связи с мезонином %d", mez_n+1);
				else
					sprintf(TestMessage, "Не завершен режим вывода при проверке связи с мезонином %d", mez_n+1);
				*TestResult = 4;    //Bad I/O
				errChk(UNMBASE_ERROR_SELFTEST);
			}
			errChk(unmbase_m_read_block (imm_vi, 0, unmbase_DEBUG_NSAMPLES, inbuff));
//-------------------
			CEidx = sftCmpInt(inbuff, outbuff, unmbase_DEBUG_NSAMPLES*unmbase_DEBUG_WIDTH);
			if (CEidx >= 0)
			{
				CEdiff |= outbuff[CEidx] ^ inbuff[CEidx];
				if (!CEaddr)
					CEaddr = outbuffaddr;
				else
				if (CEaddr != outbuffaddr)
					CEaddr = 0xFFFFFFFF;
				if (CEcnt--)
				{
					if (!CEidx &&
						(inbuff[1] == outbuff[0] ||
						inbuff[0] == outbuff[1]))
					{
#ifdef TECHNO	//VAV2 DBG
						printf("write %08X,%08X, read %08X,%08X\n",
								outbuff[0],
								outbuff[1],
								inbuff[0],
								inbuff[1]);
#endif
#ifdef UNMBASE_DEBUG_CVI
						printf("%d left, write %08X,%08X, read %08X,%08X\n",
								CEcnt,
								outbuff[0],
								outbuff[1],
								inbuff[0],
								inbuff[1]);
#endif
						SpyLog5("%d left, write %08X,%08X, read %08X,%08X\n",
								CEcnt,
								outbuff[0],
								outbuff[1],
								inbuff[0],
								inbuff[1]);
					}
					else
					{
#ifdef TECHNO	//VAV2 DBG
						printf("don't compare at %08X (%08X-%08X)\n", outbuffaddr, outbuff[CEidx], inbuff[CEidx]);
#endif
#ifdef UNMBASE_DEBUG_CVI
						printf("%d left, don't compare at %08X (%08X-%08X)\n", CEcnt, outbuffaddr, outbuff[CEidx], inbuff[CEidx]);
#endif
						SpyLog3("don't compare at %08X (%08X-%08X)\n", outbuffaddr, outbuff[CEidx], inbuff[CEidx]);
					}
					goto cecnt2;
				}
#ifdef TECHNO	//VAV2 DBG
				memcpy(buff_in, inbuff, unmbase_DEBUG_NSAMPLES*unmbase_DEBUG_WIDTH*4);
				memcpy(buff_out, outbuff, unmbase_DEBUG_NSAMPLES*unmbase_DEBUG_WIDTH*4);
#endif
				/*
				sprintf(TestMessage,
						"Не совпадают данные записи(%08X)/чтения(%08X) в память %08X модуля",
						*outbuff, *inbuff, outbuffaddr);
				*/
				if (!CEidx &&
					(inbuff[1] == outbuff[0] ||
					inbuff[0] == outbuff[1]))
				{
					sprintf(TestMessage,
						"При проверке связи с мезонином %d смещены данные чтения", mez_n+1);
				}
				else
				if (0xFFFFFFFF == CEaddr)
				{
					sprintf(TestMessage,
						"При проверке связи с мезонином %d не совпадают данные ввода/вывода, биты %08X",
						mez_n+1,
						CEdiff);
				}
				else
				{
					sprintf(TestMessage,
						"При проверке связи с мезонином %d не совпадают данные ввода/вывода, адрес %08X, биты %08X",
						mez_n+1,
						CEaddr, CEdiff);
				}
				*TestResult = 4;    //Bad I/O
				errChk(UNMBASE_ERROR_SELFTEST);
			}
//-------------------

			//check output RAM data integrity
			errChk(m_data_read(imm_session,  outbuffaddr-inbuffaddr,  unmbase_DEBUG_NSAMPLES*unmbase_DEBUG_WIDTH*4, (ViUInt8 *)inbuff));

			if (memcmp (inbuff, outbuff, unmbase_DEBUG_NSAMPLES*unmbase_DEBUG_WIDTH*4))
			{
#ifdef TECHNO	//VAV2 DBG
				memcpy(buff_in, inbuff, unmbase_DEBUG_NSAMPLES*unmbase_DEBUG_WIDTH*4);
				memcpy(buff_out, outbuff, unmbase_DEBUG_NSAMPLES*unmbase_DEBUG_WIDTH*4);
#endif
				strcpy(TestMessage, "Не совпадают данные записи/чтения области вывода модуля после обмена");
				*TestResult = 5;    //Bad I/O
				errChk(UNMBASE_ERROR_SELFTEST);
			}
#ifdef TECHNO	//VAV2 DBG
			memcpy(buff_in, inbuff, unmbase_DEBUG_NSAMPLES*unmbase_DEBUG_WIDTH*4);
			memcpy(buff_out, inbuff, unmbase_DEBUG_NSAMPLES*unmbase_DEBUG_WIDTH*4);
#endif



		}   //NCyclesSFT cycle end
		unmbase_sftreset(vi);
		//restore allocations
		memcpy (globals->alloc_num, old_alloc_num, sizeof(*old_alloc_num)*MAX_MEM_BLOCKS);
		memcpy (globals->alloc_io, old_alloc_io, sizeof(*old_alloc_io)*MAX_MEM_BLOCKS);
		memcpy (globals->alloc_ptr, old_alloc_ptr, sizeof(*old_alloc_ptr)*MAX_MEM_BLOCKS);
		memcpy (globals->alloc_size, old_alloc_size, sizeof(*old_alloc_size)*MAX_MEM_BLOCKS);

		unmbase_m_close (imm_vi);
		imm_vi = 0;
	}
	mez_n++;    //if we pass without errors
Error:
	if (!globals)
		return status;
	unmbase_ErrLed(globals, status<0);
	if (!globals->basesimple)
	{
		if (imm_vi)
			unmbase_m_close (imm_vi);
		unmbase_imm_off (vi);
		if (globals)
		{
			memcpy (globals->alloc_num, old_alloc_num, sizeof(*old_alloc_num)*MAX_MEM_BLOCKS);
			memcpy (globals->alloc_io, old_alloc_io, sizeof(*old_alloc_io)*MAX_MEM_BLOCKS);
			memcpy (globals->alloc_ptr, old_alloc_ptr, sizeof(*old_alloc_ptr)*MAX_MEM_BLOCKS);
			memcpy (globals->alloc_size, old_alloc_size, sizeof(*old_alloc_size)*MAX_MEM_BLOCKS);
		}
		//restore mezzanine sessions
		for (i=0; i<4; i++)
		{
			if (old_m_sessions[i])
			{
				m_init_at(globals, old_mvi[i], (ViUInt16)old_m_sessions[i]->midx);

				if (old_m_sessions[i]->sample_words_in != 0xFFFFFFFF)
					unmbase_m_sample_width (old_mvi[i], UNMBASE_IOMODE_IN, old_m_sessions[i]->sample_words_in);
				if (old_m_sessions[i]->sample_words_out != 0xFFFFFFFF)
					unmbase_m_sample_width (old_mvi[i], UNMBASE_IOMODE_OUT, old_m_sessions[i]->sample_words_out);
				if (old_m_sessions[i]->first_delay_in != 0xFFFFFFFF)
					unmbase_m_first_delay (old_mvi[i], UNMBASE_IOMODE_IN, old_m_sessions[i]->first_delay_in);
				if (old_m_sessions[i]->first_delay_out != 0xFFFFFFFF)
					unmbase_m_first_delay (old_mvi[i], UNMBASE_IOMODE_OUT, old_m_sessions[i]->first_delay_out);
				if (old_m_sessions[i]->divisor_in != 0xFFFFFFFF)
					unmbase_m_clock (old_mvi[i], UNMBASE_IOMODE_IN, old_m_sessions[i]->divisor_in);
				if (old_m_sessions[i]->divisor_out != 0xFFFFFFFF)
					unmbase_m_clock (old_mvi[i], UNMBASE_IOMODE_OUT, old_m_sessions[i]->divisor_out);
				unmbase_m_mode (old_mvi[i], UNMBASE_IOMODE_IN, 0);
				unmbase_m_mode (old_mvi[i], UNMBASE_IOMODE_OUT, 0);
				unmbase_m_config_trigger (old_mvi[i], UNMBASE_IOMODE_IN, old_m_sessions[i]->start_source_in);
				unmbase_m_config_trigger (old_mvi[i], UNMBASE_IOMODE_OUT, old_m_sessions[i]->start_source_out);

				memcpy(&globals->m_session[i], old_m_sessions[i], sizeof(M_SESSION));
				//Unlock locked threads
				InterlockedExchange(&globals->m_session[i].stop_in_busy, 0);
				InterlockedExchange(&globals->m_session[i].stop_out_busy, 0);
				unmbase_m_config_event (old_mvi[i],
										old_m_sessions[i]->enable_m_irq);

				unmbase_m_sftreset(old_mvi[i], UNMBASE_IOMODE_BOTH);  //reset to default state

				free(old_m_sessions[i]);
			}
		}
		//restore allocations
		if (saveConf1 != -1)
		{
			viOut32(vi, VI_A24_SPACE, rgCONF1, saveConf1);
			viOut32(vi, VI_A24_SPACE, rgCONF2, saveConf2);
		}
	}
#ifdef TECHNO
	*TestResult = (ViInt16)NCyclesSFT; //???DEBUG
#endif
	if (inbuff)
		free(inbuff);
	if (outbuff)
		free(outbuff);

	return status;
}

static ViStatus _VI_FUNC unmbase_u_self_test (ViSession vi, PUserData globals,
		ViInt16 *TestResult,
		ViChar _VI_FAR TestMessage[])
{
	ViStatus status = VI_SUCCESS;
	ViUInt16 w16;
	ViUInt32 i;

	if (globals->init_status)
	{
		unmbase_error_message (VI_NULL, globals->init_status, TestMessage);
		*TestResult = 1;    //init stage error
		errChk(UNMBASE_ERROR_SELFTEST);
	}
	for (i=0; i<=16; i++)
	{
		errChk( viOut16(vi, VI_A16_SPACE, rgSAM_DATA, 0xFFFF&(1<<i)));
		errChk( viIn16(vi, VI_A16_SPACE, rgSAM_DATA, &w16));
		if (w16 != (0xFFFF&(1<<i)))
		{
			sprintf(TestMessage, err_data,
					0xFFFF&(1<<i),
					w16);
			*TestResult = 2;
			errChk(UNMBASE_ERROR_SELFTEST);
		}
	}
	for (i=0; i<=16; i++)
	{
		errChk( viOut16(vi, VI_A16_SPACE, rgSAM_DATA, 0xFFFF&~(1<<i)));
		errChk( viIn16(vi, VI_A16_SPACE, rgSAM_DATA, &w16));
		if (w16 != (0xFFFF&~(1<<i)))
		{
			sprintf(TestMessage, err_data,
					0xFFFF&~(1<<i),
					w16);
			*TestResult = 2;
			errChk(UNMBASE_ERROR_SELFTEST);
		}
	}
	//проверка формирования сигнала пуск
	errChk( Out16_CONF3(vi,
						((ViUInt16)~0xF000),
						maskCONF3_START_SHORT_IN | maskCONF3_START_SHORT_OUT));
	errChk( viOut16(vi, VI_A16_SPACE,
					rgCOMM3,
					maskCOMM3_IRQ_IC2_RESET |
					maskCOMM3_IRQ_IC3_RESET |
					maskCOMM3_IRQ_ALL_RESET |
					maskCOMM3_STOP));
	errChk( viOut16(vi, VI_A16_SPACE,
					rgCOMM3,
					maskCOMM3_IRQ_IC2_RESET |
					maskCOMM3_IRQ_IC3_RESET |
					maskCOMM3_IRQ_ALL_RESET |
					maskCOMM3_START));
	errChk( viIn16(vi, VI_A16_SPACE, rgS, &w16));
	if ((w16 & 3) != 3)
	{
		sprintf(TestMessage, "Ошибка формирования сигналов ПУСК");
		*TestResult = 3;
		errChk(UNMBASE_ERROR_SELFTEST);
	}

	*TestResult = 0;
	return VI_SUCCESS;
Error:
	return status;
}

static ViStatus _VI_FUNC unmbase_mb_self_test (ViSession vi, PUserData globals,
		ViInt16 *TestResult,
		ViChar _VI_FAR TestMessage[])
{
	ViStatus status = VI_SUCCESS;


	SpyLog("unmbase_self_test");
	*TestResult = -1;
	strcpy(TestMessage, err_io);

	LockMB(globals);
	status = viQueryf (vi,
					   "*TST?\n",
					   "%hd",
					   TestResult);
	errChkMB(vi, status);
	if (*TestResult != 0)  /* for a value of not 0, read additional message */
	{
		int n;
		//errChkMB(vi, viScanf (vi, ",\"%256[^\"]", TestMessage));
		errChkMB(vi, viScanf (vi, ",%256t", TestMessage));
		n = strlen(TestMessage);
		if (n)
			n--;
		if ('\n' == TestMessage[n])
			TestMessage[n] = 0;
		status = UNMBASE_ERROR_SELFTEST;
	}
	else
	{
		strcpy(TestMessage, "Самоконтроль успешно завершен.");
		status = VI_SUCCESS;
	}
	viFlush (vi, VI_READ_BUF_DISCARD);
Error:
	UnlockMB (globals);
	return status;
}

static ViStatus _VI_FUNC unmbase_arm_self_test (ViSession vi, PUserData globals,
		ViInt16 *TestResult,
		ViChar _VI_FAR TestMessage[])
{
	ViStatus status = VI_SUCCESS;
	VXI_CMD vxiCmd;
	VXI_ANSW vxiAnsw;
	ViInt32 armIdx;

	for (armIdx=0; armIdx<2; armIdx++)
	{
		//в ответе на данную команду: strlen(TestMessage)+1, TestResult; данные - TestMessage
		vxiCmd.cmd = ARMCMD_TSTq;

		errChk(armvxi_arm_cmd(globals, ARMVXI_LOCKUNLOCK, ARMVXI_TMO1,
							  armIdx,
							  &vxiCmd, &vxiAnsw));

		if (TestMessage)
		{
			*TestMessage = 0;
			if (vxiAnsw.data0)
			{
				errChk(armvxi_arm_readbuf(globals,
								armIdx,
								0,	//bufIdx
								(ViUInt32 *)TestMessage,
								vxiAnsw.data0));
			}
		}
		if (TestResult)
			*TestResult = (ViInt16)vxiAnsw.data16;

		if (vxiAnsw.data16)
			errChk(UNMBASE_ERROR_SELFTEST);
	}
Error:

	return status;
}

_UNMBASE_API ViStatus _VI_FUNC unmbase_self_test (ViSession vi,
		ViInt16 *TestResult,
		ViChar _VI_FAR TestMessage[])
{
	PUserData globals = 0;
	ViStatus status = VI_SUCCESS;

	SpyLog("unmbase_self_test");
	*TestResult = -1;
	strcpy(TestMessage, err_io);
	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));

	if (globals->basetype == UNMBASE_TYPE_ARM)
	{
		status = unmbase_arm_self_test(vi, globals, TestResult, TestMessage);
	}
	else
	if (UNMBASE_FLAG_MB & globals->basetype)
	{
		status = unmbase_mb_self_test(vi, globals, TestResult, TestMessage);
	}
	else
	{
		unmbase_sftreset(vi);

		if (globals->basesimple)
		{
			status = unmbase_u_self_test(vi, globals, TestResult, TestMessage);
		}
		else
		{
			status = unmbase_v1_self_test(vi, globals, TestResult, TestMessage);
			unmbase_sftreset(vi);
			status = unmbase_v1_self_test(vi, globals, TestResult, TestMessage);
		}
		if (status == 0)
		{
			strcpy(TestMessage, "Самоконтроль успешно завершен.");
			*TestResult = 0;
		}
		unmbase_reset(vi);
		cross_delay(0.1);
	}
	if (status < 0)
		status = UNMBASE_ERROR_SELFTEST;
	else
	if (!*TestResult)
		status = VI_SUCCESS;
	if (*TestResult)
		SpyLog2("   unmbase_self_test ERROR! code=%d, msg=%s", *TestResult, TestMessage);
Error:
	return status;
}

/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_error_query (ViSession vi,
		ViInt32 *Error,
		ViChar _VI_FAR ErrorMessage[])
{
	ViStatus status;
	PUserData globals = 0;

	*Error = 0;
	strcpy(ErrorMessage, "no error");
	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));
	if (UNMBASE_FLAG_MB & globals->basetype)
	{	//==> MB
		LockMB(globals);
		status = viQueryf (vi,
						   "*ERR?\n",
						   "%d",
						   Error);
		UnlockMB (globals);

		errChkMB(vi, status);
		if (*Error != 0) /* for a value of not 0, read additional message */
			//errChkMB(vi, viScanf (vi, ",\"%256[^\"]", TestMessage));
			errChkMB(vi, viScanf (vi, ",%256t", ErrorMessage));
		viFlush (vi, VI_READ_BUF_DISCARD);
	}
	else
	{
		status = VI_WARN_NSUP_ERROR_QUERY;
	}
Error:
	return status;
}

/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_error_message (ViSession vi,
		ViStatus Status,
		ViChar _VI_FAR ErrorMessage[])
{
	ViStatus status = VI_SUCCESS;
	switch (Status)
	{
#ifdef ENGLISH
	case VI_ERROR_PARAMETER1   :
		strcpy (ErrorMessage, "Error parameter 1");
		break;
	case VI_ERROR_PARAMETER2   :
		strcpy (ErrorMessage, "Error parameter 2");
		break;
	case VI_ERROR_PARAMETER3   :
		strcpy (ErrorMessage, "Error parameter 3");
		break;
	case VI_ERROR_PARAMETER4   :
		strcpy (ErrorMessage, "Error parameter 4");
		break;

	case VI_ERROR_FAIL_ID_QUERY:
		strcpy (ErrorMessage, "ID query fail");
		break;

	case UNMBASE_ERROR_SELFTEST    :
		strcpy (ErrorMessage, "Error self-test");
		break;
	case UNMBASE_ERROR_FLEX        :
		strcpy (ErrorMessage, "Hardware error (FLEX)");
		break;
	case UNMBASE_ERROR_INSTR       :
		strcpy (ErrorMessage, "Hardware error");
		break;
	case UNMBASE_ERROR_SPD         :
		strcpy (ErrorMessage, "Hardware error (SDRAM DIMM)");
		break;
	case UNMBASE_ERROR_BUSY        :
		strcpy (ErrorMessage, "Instrument is busy (I/O in process)");
		break;
	case UNMBASE_ERROR_M_NUMBER    :
		strcpy (ErrorMessage, "Bad mezzanine number");
		break;
	case UNMBASE_ERROR_NO_MEMORY   :
		strcpy (ErrorMessage, "Not enough RAM on instrument");
		break;
	case UNMBASE_ERROR_NODATA      :
		strcpy (ErrorMessage, "Have no data");
		break;
	case UNMBASE_ERROR_READ        :
		strcpy (ErrorMessage, "Read error");
		break;
	case UNMBASE_ERROR_WRITE       :
		strcpy (ErrorMessage, "Write error");
		break;
	case UNMBASE_ERROR_MEZ_IO      :
		strcpy (ErrorMessage, "Mezzanine I/O error (type 1)");
		break;
	case UNMBASE_ERROR_MEZ_IO2      :
		strcpy (ErrorMessage, "Mezzanine I/O error (type 2)");
		break;
	case UNMBASE_ERROR_MEZ_IO12      :
		strcpy (ErrorMessage, "Mezzanine I/O error (type 1,2)");
		break;
	case UNMBASE_ERROR_TOO_FAST    :
		strcpy (ErrorMessage, "Too fast I/O speed configuration");
		break;
	case UNMBASE_ERROR_NO_CLOCKS       :
		strcpy (ErrorMessage, "Period not configured");
		break;
	case UNMBASE_ERROR_NO_FIRST_DELAY  :
		strcpy (ErrorMessage, "First delay not configured");
		break;
	case UNMBASE_ERROR_NO_SAMPLE_LENGTH    :
		strcpy (ErrorMessage, "Sample width not configured");
		break;
	case UNMBASE_ERROR_NO_PACKET_SIZE      :
		strcpy (ErrorMessage, "Packet size not configured");
		break;
	case UNMBASE_ERROR_NO_BLOCK_SIZE       :
		strcpy (ErrorMessage, "Block size not configured");
		break;
	case UNMBASE_ERROR_NO_ALLOC            :
		strcpy (ErrorMessage, "Mezzanine RAM not allocated");
		break;
	case UNMBASE_ERROR_NULL_POINTER	:
		strcpy (ErrorMessage, "NULL pointer error");
		break;
	case UNMBASE_ERROR_NOT_SUPPORT	:
		strcpy (ErrorMessage, "This function not supported on current hardware");
		break;
	case UNMBASE_WARN_INIT         :
		strcpy (ErrorMessage, "Initialisation phase error. Use self-test for details.");
		break;
	case UNMBASE_WARN_REREADED     :
		strcpy (ErrorMessage, "Repeat read same data");
		break;
#else
	case VI_ERROR_PARAMETER1   :
		strcpy (ErrorMessage, "Ошибка параметра 1");
		break;
	case VI_ERROR_PARAMETER2   :
		strcpy (ErrorMessage, "Ошибка параметра 2");
		break;
	case VI_ERROR_PARAMETER3   :
		strcpy (ErrorMessage, "Ошибка параметра 3");
		break;
	case VI_ERROR_PARAMETER4   :
		strcpy (ErrorMessage, "Ошибка параметра 4");
		break;

	case VI_ERROR_FAIL_ID_QUERY:
		strcpy (ErrorMessage, "Несоответствие типа инструмента");
		break;

	case UNMBASE_ERROR_SELFTEST    :
		strcpy (ErrorMessage, "Ошибка самоконтроля");
		break;
	case UNMBASE_ERROR_FLEX        :
		strcpy (ErrorMessage, "Аппаратура инструмента неисправна (FLEX)");
		break;
	case UNMBASE_ERROR_INSTR       :
		strcpy (ErrorMessage, "Аппаратура инструмента неисправна");
		break;
	case UNMBASE_ERROR_SPD         :
		strcpy (ErrorMessage, "Аппаратура инструмента неисправна (SDRAM DIMM)");
		break;
	case UNMBASE_ERROR_BUSY        :
		strcpy (ErrorMessage, "Инструмент занят (идет процесс ввода/вывода)");
		break;
	case UNMBASE_ERROR_M_NUMBER    :
		strcpy (ErrorMessage, "Неверный номер М-модуля");
		break;
	case UNMBASE_ERROR_NO_MEMORY   :
		strcpy (ErrorMessage, "Недостаточно установлено памяти на базовом модуле");
		break;
	case UNMBASE_ERROR_NODATA      :
		strcpy (ErrorMessage, "Нет данных");
		break;
	case UNMBASE_ERROR_READ        :
		strcpy (ErrorMessage, "Ошибка чтения");
		break;
	case UNMBASE_ERROR_WRITE       :
		strcpy (ErrorMessage, "Ошибка записи");
		break;
	case UNMBASE_ERROR_MEZ_IO      :
		strcpy (ErrorMessage, "Ошибка обмена с М-модулем (тип 1)");
		break;
	case UNMBASE_ERROR_MEZ_IO2      :
		strcpy (ErrorMessage, "Ошибка обмена с М-модулем (тип 2)");
		break;
	case UNMBASE_ERROR_MEZ_IO12      :
		strcpy (ErrorMessage, "Ошибка обмена с М-модулем (типы 1 и 2)");
		break;
	case UNMBASE_ERROR_TOO_FAST    :
		strcpy (ErrorMessage, "Слишком велика установленная скорость ввода/вывода");
		break;
	case UNMBASE_ERROR_NO_CLOCKS       :
		strcpy (ErrorMessage, "Не задан период обмена");
		break;
	case UNMBASE_ERROR_NO_FIRST_DELAY  :
		strcpy (ErrorMessage, "Не задана задержка первого обмена");
		break;
	case UNMBASE_ERROR_NO_SAMPLE_LENGTH    :
		strcpy (ErrorMessage, "Не задана ширина кадра");
		break;
	case UNMBASE_ERROR_NO_PACKET_SIZE      :
		strcpy (ErrorMessage, "Не задан размер пакета");
		break;
	case UNMBASE_ERROR_NO_BLOCK_SIZE       :
		strcpy (ErrorMessage, "Не задан размер блока");
		break;
	case UNMBASE_ERROR_NO_ALLOC            :
		strcpy (ErrorMessage, "Не выделена память для М-модуля");
		break;
	case UNMBASE_ERROR_NULL_POINTER	:
		strcpy (ErrorMessage, "Драйверу ошибочно передан нулевой указатель");
		break;
	case UNMBASE_ERROR_NOT_SUPPORT	:
		strcpy (ErrorMessage, "Функция не поддерживается данным типом модуля");
		break;
	case UNMBASE_WARN_INIT         :
		strcpy (ErrorMessage, "Инициализация прошла с ошибками. Используйте самоконтроль инструмента.");
		break;
	case UNMBASE_WARN_REREADED     :
		strcpy (ErrorMessage, "Повторное чтение тех же данных");
		break;
#endif
	default:
		if (viStatusDesc (vi, Status, ErrorMessage) != VI_SUCCESS)
		{
			strcpy (ErrorMessage, "Unknown status");
			status = VI_WARN_UNKNOWN_STATUS;
		}
		break;
	}
	SpyLog2("unmbase_error_message(err:%08X, msg:%s)", Status, ErrorMessage);
	return status;
}

/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_revision_query (ViSession vi,
		ViChar _VI_FAR SoftRevision[],
		ViChar _VI_FAR HardRevision[])
{
	PUserData globals = NULL;
	ViStatus status = VI_SUCCESS;
	strcpy (SoftRevision, UNMBASE_DRIVER_REVISION);
	if (vi)
	{
		errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));
		strcpy(HardRevision, globals->fw_rev);
	}
	else
		strcpy (HardRevision, "<not available>");
Error:
	return VI_SUCCESS;
}

/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_close (ViSession vi)
{
	PUserData globals = 0;
	ViStatus status = VI_SUCCESS;
	viUnlock(vi);
	SpyLog("unmbase_close()");
	errChk( viGetAttribute (vi, VI_ATTR_USER_DATA, &globals));
	if (globals)
	{
		if (globals->m_vi_idx[0] >= 0)
			unmbase_m_close (MVI_ID |globals->m_vi_idx[0]);
		if (globals->m_vi_idx[1] >= 0)
			unmbase_m_close (MVI_ID |globals->m_vi_idx[1]);
		if (globals->m_vi_idx[2] >= 0)
			unmbase_m_close (MVI_ID |globals->m_vi_idx[2]);
		if (globals->m_vi_idx[3] >= 0)
			unmbase_m_close (MVI_ID |globals->m_vi_idx[3]);

		unmbase_ErrLed(globals, 0);

		if (globals->hOpenMutex)
			unmbase_util_mutex_close(globals->hOpenMutex);
		if (globals->MB_busy_mutex)
			unmbase_util_mutex_close(globals->MB_busy_mutex);
		if (globals->Mem_busy_mutex)
			unmbase_util_mutex_close(globals->Mem_busy_mutex);
		if (globals->LastDta_busy_mutex)
			unmbase_util_mutex_close(globals->LastDta_busy_mutex);
		if (globals->StartStop_busy_mutex)
			unmbase_util_mutex_close(globals->StartStop_busy_mutex);
		if (globals->RgComm1_busy_mutex)
			unmbase_util_mutex_close(globals->RgComm1_busy_mutex);
		if (globals->RgComm2_busy_mutex)
			unmbase_util_mutex_close(globals->RgComm2_busy_mutex);

	}
Error:
	if (vi)
		viClose(vi);
	if (globals)
	{
		viClose(globals->defaultRM);
		free(globals);
	}
#ifdef USE_UNSPY
	if (HMod) {
		cross_free_dll(HMod);
	}
#endif
	return status;
}
#ifdef __UN_WINDOWS__
BOOL APIENTRY DllMain( UNMBASE_MUTEX_TYPE hModule,
					   DWORD  ul_reason_for_call,
					   LPVOID lpReserved
					 )
{
	return TRUE;
}
#else	//LINUX debug!!!

int main(void)
{
	char name[251];
	strcpy(name, "TCPIP0::192.168.0.199::inst0::INSTR");
	//strcpy(name, "VXI0::2::INSTR");
	ViSession vi = 0;
	fprintf(stderr, "unmbase_init start\n");
	ViStatus status = unmbase_init(name, 1, 0, &vi);
	fprintf(stderr, "INIT: %s:\n\tstatus = %#x vi = %d\n", name, status, vi);

	ViInt16 result;
	status = unmbase_self_test(vi, &result, name);
	fprintf(stderr, "TEST: %s:\n\tstatus = %#x result = %d\n", name, status, result);

	status = unmbase_close(vi);
	fprintf(stderr, "CLOSE: status = %#x\n", status);
	return 0;
}

#endif
