
#include "wizchip_conf.h"
#include "spi.h"

#include "drv_spi.h"
#include "platform.h"

void SPI_CrisEnter(void)
{
    __set_PRIMASK(1);
}
/**
  * @brief  ?????
  * @retval None
  */
void SPI_CrisExit(void)
{
    __set_PRIMASK(0);
}
 
/**
  * @brief  ?????????
  * @retval None
  */
void SPI_CS_Select(void)
{
	W5500_SPI_CS_SELECT();
}
/**
  * @brief  ?????????
  * @retval None
  */
void SPI_CS_Deselect(void)
{
	W5500_SPI_CS_DESELECT();
}
void register_wizchip()
{
	// First of all, Should register SPI callback functions implemented by user for accessing WIZCHIP 
	/* Critical section callback */
	reg_wizchip_cris_cbfunc(SPI_CrisEnter, SPI_CrisExit);   
	/* Chip selection call back */
	reg_wizchip_cs_cbfunc(SPI_CS_Select, SPI_CS_Deselect);
	/* SPI Read & Write callback function */
	reg_wizchip_spi_cbfunc(W5500_SPI_ReadByte, W5500_SPI_WriteByte);
}



























