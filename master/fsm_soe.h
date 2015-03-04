/******************************************************************************
 *
 *  $Id: fsm_soe.h,v c6c8b457bb40 2010/03/09 13:40:25 fp $
 *
 *  Copyright (C) 2006-2008  Florian Pose, Ingenieurgemeinschaft IgH
 *
 *  This file is part of the IgH EtherCAT Master.
 *
 *  The IgH EtherCAT Master is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License version 2, as
 *  published by the Free Software Foundation.
 *
 *  The IgH EtherCAT Master is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
 *  Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with the IgH EtherCAT Master; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *  ---
 *
 *  The license mentioned above concerns the source code only. Using the
 *  EtherCAT technology and brand is only permitted in compliance with the
 *  industrial property and similar rights of Beckhoff Automation GmbH.
 *
 *****************************************************************************/

/**
   \file
   EtherCAT CoE state machines.
*/

/*****************************************************************************/

#ifndef __EC_FSM_SOE_H__
#define __EC_FSM_SOE_H__

#include "globals.h"
#include "datagram.h"
#include "slave.h"
#include "soe_request.h"

/*****************************************************************************/

typedef struct ec_fsm_soe ec_fsm_soe_t; /**< \see ec_fsm_soe */

/** Finite state machines for the Sercos over EtherCAT protocol.
 */
struct ec_fsm_soe {
    ec_slave_t *slave; /**< slave the FSM runs on */
    ec_datagram_t *datagram; /**< datagram used in the state machine */
    unsigned int retries; /**< retries upon datagram timeout */

    void (*state)(ec_fsm_soe_t *); /**< CoE state function */
    unsigned long jiffies_start; /**< CoE timestamp. */
    ec_soe_request_t *request; /**< SoE request */
    off_t offset; /**< IDN data offset during fragmented write. */
};

/*****************************************************************************/

void ec_fsm_soe_init(ec_fsm_soe_t *, ec_datagram_t *);
void ec_fsm_soe_clear(ec_fsm_soe_t *);

void ec_fsm_soe_transfer(ec_fsm_soe_t *, ec_slave_t *, ec_soe_request_t *);

int ec_fsm_soe_exec(ec_fsm_soe_t *);
int ec_fsm_soe_success(ec_fsm_soe_t *);

/*****************************************************************************/

#endif