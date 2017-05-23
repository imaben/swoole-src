/*
 +----------------------------------------------------------------------+
 | Swoole                                                               |
 +----------------------------------------------------------------------+
 | Copyright (c) 2012-2015 The Swoole Group                             |
 +----------------------------------------------------------------------+
 | This source file is subject to version 2.0 of the Apache license,    |
 | that is bundled with this package in the file LICENSE, and is        |
 | available through the world-wide-web at the following url:           |
 | http://www.apache.org/licenses/LICENSE-2.0.html                      |
 | If you did not receive a copy of the Apache2.0 license and are unable|
 | to obtain it through the world-wide-web, please send a note to       |
 | license@swoole.com so we can mail you a copy immediately.            |
 +----------------------------------------------------------------------+
 | Author: maben <www.maben@foxmail.com>                                |
 +----------------------------------------------------------------------+
 */

#include "swoole_http_log.h"

static int log_enable = 0;

static FILE *http_log_fp = NULL;

int swoole_http_log_init(swServer *serv)
{
    if (NULL == serv->http_access_log) {
        return SW_OK;
    }

    http_log_fp = fopen(log_file, "a+");
    if (!http_log_fp) {
        return SW_ERR;
    }

    return SW_OK;
}
