/*
 * ethernet.c
 *
 *  Created on: Sep 16, 2025
 *      Author: thangnq
 */


#include "ethernet.h"
#include "platform.h"
#include <dhcp.h>
#include <socket.h>
#include "spi.h"

#ifndef DATA_BUF_SIZE
#define DATA_BUF_SIZE			2048
#endif

#define DHCP_SOCKET     		0
#define SNTP_SOCKET      		1
#define HTTP_SOCKET     		0
#define MBTCP_PORT      		502

#define REG_INPUT_START       	0x0001
#define REG_INPUT_NREGS       	10

#define REG_HOLDING_START     	0x0001
#define REG_HOLDING_NREGS     	10

#define REG_COILS_START       	0x0001
#define REG_COILS_SIZE        	16

#define REG_DISCRETE_START    	0x0001
#define REG_DISCRETE_SIZE     	16

#define USE_DHCP				0

/************************/
/* Select LOOPBACK_MODE */
/************************/
#define LOOPBACK_MAIN_NOBLOCK   0
#define LOOPBACK_MODE           LOOPBACK_MAIN_NOBLOCK

wiz_NetInfo gWIZNETINFO;
uint8_t destip[4] = {192, 168, 6, 210};
uint16_t destport = 3333;

uint8_t memsize[2][8] = { {2,2,2,2,2,2,2,2},{2,2,2,2,2,2,2,2}};
#if USE_DHCP
uint8_t buff[DATA_BUF_SIZE];
#endif

static void Load_Net_Parameters();
int32_t loopback_tcpc(uint8_t sn, uint8_t* buf, uint8_t* destip, uint16_t destport);
void network_init(void);
void my_ip_assign(void);
void my_ip_conflict(void);

void ethernetInit(){
	W5500_SPI_int();
	PCA9555_i2c_init();
	register_wizchip();
	Load_Net_Parameters();
	if (ctlwizchip(0, (void*) memsize) == -1) {
		LOG("WIZCHIP Initialized fail.\r\n")
		;

	} else {
		setSHAR(gWIZNETINFO.mac);

		network_init();
	}

}

static void Load_Net_Parameters()
{
	gWIZNETINFO.gw[0] = 192; //Gateway
	gWIZNETINFO.gw[1] = 168;
	gWIZNETINFO.gw[2] = 1;
	gWIZNETINFO.gw[3] = 1;

	gWIZNETINFO.sn[0]=255; //Mask
	gWIZNETINFO.sn[1]=255;
	gWIZNETINFO.sn[2]=255;
	gWIZNETINFO.sn[3]=0;

	gWIZNETINFO.mac[0]=0x0c; //MAC
	gWIZNETINFO.mac[1]=0x29;
	gWIZNETINFO.mac[2]=0xab;
	gWIZNETINFO.mac[3]=0x7c;
	gWIZNETINFO.mac[4]=0x00;
	gWIZNETINFO.mac[5]=0x00;

	gWIZNETINFO.ip[0]=192; //IP
	gWIZNETINFO.ip[1]=168;
	gWIZNETINFO.ip[2]=1;
	gWIZNETINFO.ip[3]=249;

	gWIZNETINFO.dns[0] = 8;
	gWIZNETINFO.dns[1] = 8;
	gWIZNETINFO.dns[2] = 8;
	gWIZNETINFO.dns[3] = 8;

	gWIZNETINFO.dhcp = NETINFO_STATIC;
}

void network_init(void)
{
 // wiz_NetTimeout gWIZNETTIME = {.retry_cnt = 3, .time_100us = 2000};
	 wiz_NetTimeout gWIZNETTIME = {.retry_cnt = 10, .time_100us = 2000};
  ctlnetwork(CN_SET_TIMEOUT,(void*)&gWIZNETTIME);
  ctlnetwork(CN_GET_TIMEOUT, (void*)&gWIZNETTIME);

  LOG("TIMEOUT: %d, %d\r\n", gWIZNETTIME.retry_cnt,gWIZNETTIME.time_100us);

	ctlnetwork(CN_SET_NETINFO, (void*)&gWIZNETINFO);
	ctlnetwork(CN_GET_NETINFO, (void*)&gWIZNETINFO);
	// Display Network Information
  uint8_t tmpstr[6];
	ctlwizchip(CW_GET_ID,(void*)tmpstr);
	LOG("\r\n=== %s NET CONF ===\r\n",(char*)tmpstr);
	LOG("MAC: %02X:%02X:%02X:%02X:%02X:%02X\r\n",
    gWIZNETINFO.mac[0],gWIZNETINFO.mac[1],gWIZNETINFO.mac[2],gWIZNETINFO.mac[3],gWIZNETINFO.mac[4],gWIZNETINFO.mac[5]);
	LOG("SIP: %d.%d.%d.%d\r\n", gWIZNETINFO.ip[0],gWIZNETINFO.ip[1],gWIZNETINFO.ip[2],gWIZNETINFO.ip[3]);
	LOG("GAR: %d.%d.%d.%d\r\n", gWIZNETINFO.gw[0],gWIZNETINFO.gw[1],gWIZNETINFO.gw[2],gWIZNETINFO.gw[3]);
	LOG("SUB: %d.%d.%d.%d\r\n", gWIZNETINFO.sn[0],gWIZNETINFO.sn[1],gWIZNETINFO.sn[2],gWIZNETINFO.sn[3]);
	LOG("DNS: %d.%d.%d.%d\r\n", gWIZNETINFO.dns[0],gWIZNETINFO.dns[1],gWIZNETINFO.dns[2],gWIZNETINFO.dns[3]);
	LOG("======================\r\n");
}

