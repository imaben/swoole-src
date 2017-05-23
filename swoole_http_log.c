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
#include "Server.h"
#include <stdio.h>

static FILE *log_fp = NULL;

// old callback
static void (*oldOnClose)(swServer *serv, swDataHead *);

// Replaced callback
static void swoole_http_on_close(swServer *serv, swDataHead *head);

int swoole_http_log_init(swServer *serv)
{
    if (NULL == serv->http_access_log) {
        return SW_OK;
    }

    log_fp = fopen(serv->http_access_log, "a+");
    if (!log_fp) {
        return SW_ERR;
    }

    // Replace callback
    oldOnClose = serv->onClose;
    serv->onClose = swoole_http_on_close;

    return SW_OK;
}

static void swoole_http_on_close(swServer *serv, swDataHead *head)
{
    // todo support
    fprintf(log_fp, "%s %s %s:%d %f %f %s %s %s %s %d %d %s %s %s");
    oldOnClose(serv, head);
}
