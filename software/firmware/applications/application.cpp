/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */

/**
 * @addtogroup STM32
 */
/*@{*/

#include <board.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_led.h"
#include "spi_wifi_rw009.h"
#include "telnet.h"
#include "stm32_i2c.h"

#ifdef RT_USING_FINSH
#include "shell.h"
#endif

#ifdef RT_USING_LWIP
#include <lwip/sys.h>
#include <lwip/api.h>
#include <netif/ethernetif.h>
#endif

extern void set_if(char* netif_name, char* ip_addr, char* gw_addr, char* nm_addr);

void rt_init_thread_entry(void* parameter)
{
	rt_i2c_core_init();
	rt_hw_i2c_init();
	rt_hw_spi_init();
/* LwIP Initialization */
#ifdef RT_USING_LWIP
	{
		extern void lwip_sys_init(void);

		/* register ethernetif device */
		eth_system_device_init();

		/* initialize wifi interface */
		rt_hw_wifi_init("spi10");

		/* init lwip system */
		lwip_sys_init();
		rt_kprintf("TCP/IP initialized!\n");
		
		set_if("w0","192.168.1.9","192.168.1.1","255.255.255.0");
		rw009_join("rtthread_11n","rtthread_finsh");
	}
#endif
		telnet_server_init();
#ifdef RT_USING_FINSH
	/* init finsh */
	finsh_system_init();
	finsh_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

	sys_led_init();
}

int rt_application_init()
{
	rt_thread_t tid;

	tid = rt_thread_create("init",
								rt_init_thread_entry, RT_NULL,
								2048, RT_THREAD_PRIORITY_MAX/3, 20);

	if (tid != RT_NULL)
		rt_thread_startup(tid);

	return 0;
}

/*@}*/
