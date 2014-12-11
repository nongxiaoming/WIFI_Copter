#include "stdio.h"
#include "stm32f2xx.h"
#include "drv_wifi.h"
#include "mxchipWNET.h"


#define DynamicMemAlloc          
#define AP_NAME           "rtthread_11n"
#define AP_PASSWORD       "rtthread_finsh"


network_InitTypeDef_st wNetConfig;
lib_config_t libConfig;
int wifi_up = 0;

net_para_st para;

void WifiStatusHandler(int event)
{
  switch (event) {
    case MXCHIP_WIFI_UP:
     // printf("Station up \r\n");
      break;
    case MXCHIP_WIFI_DOWN:
     // printf("Station down \r\n");
      break;
    case MXCHIP_UAP_UP:
     // printf("uAP up \r\n");
      getNetPara(&para, Soft_AP);
//      printf("Soft AP mode: IP address: %s \r\n", para.ip);
//      printf("Soft AP mode: NetMask address: %s \r\n", para.mask);
//      printf("Soft AP mode: MAC address: %s \r\n", para.mac);
      break;
    case MXCHIP_UAP_DOWN:
      printf("uAP down \r\n");
      break;
    default:
      break;
  }
  return;
}

void ApListCallback(UwtPara_str *pApList)
{
	int i;
//  printf("Find %d APs: \r\n", pApList->ApNum);
//  for (i=0;i<pApList->ApNum;i++)
//    printf("    SSID: %s, Signal: %d%%\r\n", pApList->ApList[i].ssid, pApList->ApList[i].ApPower);
}

void NetCallback(net_para_st *pnet)
{
//	printf("Station mode: IP address: %s \r\n", pnet->ip);
//	printf("Station mode: NetMask address: %s \r\n", pnet->mask);
//	printf("Station mode: Gateway address: %s \r\n", pnet->gate);
//	printf("Station mode: DNS server address: %s \r\n", pnet->dns);
//  printf("Station mode: MAC address: %s \r\n", pnet->mac);
}

void stationModeStart(void)
{
	int ret;
  memset(&wNetConfig, 0x0, sizeof(network_InitTypeDef_st));
	
	wNetConfig.wifi_mode = Station;
	strcpy((char*)wNetConfig.wifi_ssid, AP_NAME);
	strcpy((char*)wNetConfig.wifi_key, AP_PASSWORD);
	strcpy((char*)wNetConfig.local_ip_addr, "192.168.3.44");
  strcpy((char*)wNetConfig.net_mask, "255.255.255.0");
	strcpy((char*)wNetConfig.gateway_ip_addr, "192.168.3.1");
	wNetConfig.dhcpMode = DHCP_Disable;
	ret = StartNetwork(&wNetConfig);
	//printf("connect to %s....., return %d\r\n", wNetConfig.wifi_ssid, ret);
}

void softAPModeStart(void)
{
  int ret;
  memset(&wNetConfig, 0x0, sizeof(network_InitTypeDef_st));
	
	wNetConfig.wifi_mode = Soft_AP;
  strcpy((char*)wNetConfig.wifi_ssid, "Soft AP test");
  strcpy((char*)wNetConfig.wifi_key, "");
	strcpy((char*)wNetConfig.local_ip_addr, "192.168.0.1");
  strcpy((char*)wNetConfig.net_mask, "255.255.255.0");
	strcpy((char*)wNetConfig.address_pool_start, "192.168.0.10");
	strcpy((char*)wNetConfig.address_pool_end, "192.168.0.177");
	wNetConfig.dhcpMode = DHCP_Server;
	ret = StartNetwork(&wNetConfig);
	//printf("Setup soft AP: %s, return %d\r\n", wNetConfig.wifi_ssid, ret);
}

void RptConfigmodeRslt(network_InitTypeDef_st *nwkpara)
{
//	if(nwkpara == NULL){
//		printf("Configuration failed\r\n");
//	}
//	else{
//		printf("Configuration is successful, SSID:%s, Key:%s\r\n", \
//																		nwkpara->wifi_ssid,\
//																		nwkpara->wifi_key);
//	}
}


void wifi_lib_init(void)
{
  libConfig.tcp_buf_dynamic = mxEnable;
  libConfig.tcp_max_connection_num = 12;
  libConfig.tcp_rx_size = 2048;
  libConfig.tcp_tx_size = 2048;
  libConfig.hw_watchdog = 0;
  libConfig.wifi_channel = WIFI_CHANNEL_1_13;
	lib_config(&libConfig);
}

void wifi_init(void)
{
	mxchipInit();	
}
void wifi_tick(void)
{
  systick_irq();    
	NoOS_systick_irq();
}
 /*******************************************************************************
* Function Name  : SDIO_IRQHandler
* Description    : This function handles SDIO global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_IRQHandler(void)
{
  /* Process All SDIO Interrupt Sources */
  sdio_irq();
}

void DMA2_Stream3_IRQHandler(void)
{
    
	dma_irq();
}

/*******************************************************************************
* Function Name  : DMA2_Stream2_IRQHandler
* Description    : This function handles DMA2 Channel 2 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA2_Stream2_IRQHandler(void)
{
    
//	uart_dma_irq();
}

void USART6_IRQHandler(void)
{
    
    bt_uart_irq();
}
/**
  * @brief  This function handles EXTI15_10.
  * @param  None
  * @retval None
  */
void EXTI15_10_IRQHandler(void)
{
  gpio_irq();
}
void EXTI0_IRQHandler(void)
{
	gpio_irq(); //SDIO OOB interrupt
}

void EXTI3_IRQHandler(void)
{
	gpio_irq(); //User defined external interrupt, EMW3162 button 1: PA3
}
void EXTI9_5_IRQHandler(void)
{
  gpio_irq();//User defined external interrupt, EMW3161 button 1: PH9
}
