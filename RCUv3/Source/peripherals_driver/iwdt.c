/*
 * iwdt.c
 *
 *  Created on: Aug 2, 2023
 *      Author: icepe
 */
#include "iwdt.h"
#include "stm32g0b0xx.h"
#include "LL_API.h"

#define __IWDG_KEY_RELOAD                 0x0000AAAAU               /*!< IWDG Reload Counter Enable   */
#define __IWDG_KEY_ENABLE                 0x0000CCCCU               /*!< IWDG Peripheral Enable       */
#define __IWDG_KEY_WR_ACCESS_ENABLE       0x00005555U               /*!< IWDG KR Write Access Enable  */
#define __IWDG_KEY_WR_ACCESS_DISABLE      0x00000000U

#define __IWDG_PRESCALER_4                0x00000000U                           /*!< Divider by 4   */
#define __IWDG_PRESCALER_8                (IWDG_PR_PR_0)                        /*!< Divider by 8   */
#define __IWDG_PRESCALER_16               (IWDG_PR_PR_1)                        /*!< Divider by 16  */
#define __IWDG_PRESCALER_32               (IWDG_PR_PR_1 | IWDG_PR_PR_0)         /*!< Divider by 32  */
#define __IWDG_PRESCALER_64               (IWDG_PR_PR_2)                        /*!< Divider by 64  */
#define __IWDG_PRESCALER_128              (IWDG_PR_PR_2 | IWDG_PR_PR_0)         /*!< Divider by 128 */
#define __IWDG_PRESCALER_256              (IWDG_PR_PR_2 | IWDG_PR_PR_1)         /*!< Divider by 256 */

static uint32_t __IWDG_IsReady() {
	return ((READ_BIT(IWDG->SR, IWDG_SR_PVU | IWDG_SR_RVU | IWDG_SR_WVU) == 0U) ? 1UL : 0UL);
}
void IWDG_init(void) {
//IWDG_Enable
	WRITE_REG(IWDG->KR, __IWDG_KEY_ENABLE);
//IWDG_EnableWriteAccess
	WRITE_REG(IWDG->KR, __IWDG_KEY_WR_ACCESS_ENABLE);
//IWDG_SetPrescaler
	WRITE_REG(IWDG->PR, IWDG_PR_PR & __IWDG_PRESCALER_256);
//LL_IWDG_SetReloadCounter
	WRITE_REG(IWDG->RLR, IWDG_RLR_RL & 625);
	while (__IWDG_IsReady() != 1)
		;
}
void startWDT(void) {
	IWDG->KR = 0xAAAA; // Writing 0xAAAA in the Key register prevents watchdog reset
	IWDG->KR = 0xCCCC; // Start the independent watchdog timer
}

void cleanWDT(void) {
	IWDG->KR = 0xAAAA;
}
