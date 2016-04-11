/* Copyright (c) 2013 Nordic Semiconductor. All Rights Reserved.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the license.txt file.
 */

#ifndef HIBLE_H__
#define HIBLE_H__

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"

#define HIBLE_UUID_BASE		{0x91, 0xF7, 0x8C, 0xB5, 0x35, 0xEA, 0x04, 0x96, \
                         	 0xC0, 0x4F, 0x91, 0x07, 0x00, 0x00, 0x01, 0xE1}
#define HIBLE_UUID_SERVICE	0x2220
#define HIBLE_UUID_SW_CHAR	0x2221

// Forward declaration of the hible_t type. 
typedef struct hible_s hible_t;

typedef void (*hible_write_handler_t) (hible_t * p_ble, uint8_t new_state);

typedef struct
{
    hible_write_handler_t write_handler;                    /**< Event handler to be called when LED characteristic is written. */
} hible_init_t;

/**@brief LED Button Service structure. This contains various status information for the service. */
typedef struct hible_s
{
    uint16_t                    service_handle;
    ble_gatts_char_handles_t    sw_char_handles;
    uint8_t                     uuid_type;
    uint16_t                    conn_handle;
    hible_write_handler_t 		write_handler;
} hible_t;

/**@brief Function for initializing the LED Button Service.
 *
 * @param[out]  p_ble       HIBLE Service structure. This structure will have to be supplied by
 *                          the application. It will be initialized by this function, and will later
 *                          be used to identify this particular service instance.
 * @param[in]   p_ble_init  Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
uint32_t hible_init(hible_t * p_hible, const hible_init_t * p_ble_init);

/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the LED Button Service.
 *
 *
 * @param[in]   p_ble      LED Button Service structure.
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 */
void hible_on_ble_evt(hible_t * p_hible, ble_evt_t * p_ble_evt);

#endif // HIBLE_H__

/** @} */
