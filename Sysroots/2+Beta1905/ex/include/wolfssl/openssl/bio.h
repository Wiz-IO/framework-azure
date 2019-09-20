/* bio.h
 *
 * Copyright (C) 2006-2019 wolfSSL Inc.
 *
 * This file is part of wolfSSL.
 *
 * wolfSSL is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * wolfSSL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1335, USA
 */

/* bio.h for openssl */


#ifndef WOLFSSL_BIO_H_
#define WOLFSSL_BIO_H_

#include <wolfssl/openssl/ssl.h>


#ifdef __cplusplus
    extern "C" {
#endif

#define BIO_FLAG_BASE64_NO_NL WOLFSSL_BIO_FLAG_BASE64_NO_NL
#define BIO_FLAG_READ         WOLFSSL_BIO_FLAG_READ
#define BIO_FLAG_WRITE        WOLFSSL_BIO_FLAG_WRITE
#define BIO_FLAG_IO_SPECIAL   WOLFSSL_BIO_FLAG_IO_SPECIAL
#define BIO_FLAG_RETRY        WOLFSSL_BIO_FLAG_RETRY

#define BIO_find_type wolfSSL_BIO_find_type
#define BIO_next      wolfSSL_BIO_next
#define BIO_gets      wolfSSL_BIO_gets
#define BIO_puts      wolfSSL_BIO_puts

#define BIO_TYPE_FILE WOLFSSL_BIO_FILE
#define BIO_TYPE_BIO  WOLFSSL_BIO_BIO
#define BIO_TYPE_MEM  WOLFSSL_BIO_MEMORY
#define BIO_TYPE_BASE64 WOLFSSL_BIO_BASE64

#define BIO_printf wolfSSL_BIO_printf
#define BIO_dump   wolfSSL_BIO_dump

/* BIO callback */
#define BIO_CB_FREE   WOLFSSL_BIO_CB_FREE
#define BIO_CB_READ   WOLFSSL_BIO_CB_READ
#define BIO_CB_WRITE  WOLFSSL_BIO_CB_WRITE
#define BIO_CB_PUTS   WOLFSSL_BIO_CB_PUTS
#define BIO_CB_GETS   WOLFSSL_BIO_CB_GETS
#define BIO_CB_CTRL   WOLFSSL_BIO_CB_CTRL
#define BIO_CB_RETURN WOLFSSL_BIO_CB_RETURN

#define BIO_set_callback         wolfSSL_BIO_set_callback
#define BIO_get_callback         wolfSSL_BIO_get_callback
#define BIO_set_callback_arg     wolfSSL_BIO_set_callback_arg
#define BIO_get_callback_arg     wolfSSL_BIO_get_callback_arg

/* BIO for 1.1.0 or later */
#define BIO_set_init               wolfSSL_BIO_set_init
#define BIO_get_data               wolfSSL_BIO_get_data
#define BIO_set_data               wolfSSL_BIO_set_data
#define BIO_get_shutdown           wolfSSL_BIO_get_shutdown
#define BIO_set_shutdown           wolfSSL_BIO_set_shutdown

/* helper to set specific retry/read flags */
#define BIO_set_retry_read(bio)\
    wolfSSL_BIO_set_flags((bio), WOLFSSL_BIO_FLAG_RETRY | WOLFSSL_BIO_FLAG_READ)

#define BIO_clear_retry_flags      wolfSSL_BIO_clear_retry_flags

#define BIO_meth_new               wolfSSL_BIO_meth_new
#define BIO_meth_set_write         wolfSSL_BIO_meth_set_write
#define BIO_meth_free              wolfSSL_BIO_meth_free
#define BIO_meth_set_write         wolfSSL_BIO_meth_set_write
#define BIO_meth_set_read          wolfSSL_BIO_meth_set_read
#define BIO_meth_set_puts          wolfSSL_BIO_meth_set_puts
#define BIO_meth_set_gets          wolfSSL_BIO_meth_set_gets
#define BIO_meth_set_ctrl          wolfSSL_BIO_meth_set_ctrl
#define BIO_meth_set_create        wolfSSL_BIO_meth_set_create
#define BIO_meth_set_destroy       wolfSSL_BIO_meth_set_destroy


/* BIO CTRL */
#define BIO_CTRL_EOF               2
#define BIO_CTRL_PUSH              6
#define BIO_CTRL_POP               7
#define BIO_CTRL_GET_CLOSE         8
#define BIO_CTRL_SET_CLOSE         9
#define BIO_CTRL_PENDING           10
#define BIO_CTRL_DUP               12

#define BIO_C_SET_BUF_MEM          114
#define BIO_C_GET_BUF_MEM_PTR      115


#ifdef __cplusplus
    }  /* extern "C" */
#endif


#endif /* WOLFSSL_BIO_H_ */

