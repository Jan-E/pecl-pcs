/*
  +----------------------------------------------------------------------+
  | PCS extension <http://PCS.tekwire.net>                       |
  +----------------------------------------------------------------------+
  | Copyright (c) 2015 The PHP Group                                     |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt.                                 |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Francois Laupretre <francois@tekwire.net>                    |
  +----------------------------------------------------------------------+
*/

#ifndef __PCS_UTILS_H
#define __PCS_UTILS_H

/*============================================================================*/

static int in_startup = 1;

/*-----------------------------------------------------*/

static int PCS_Utils_assertModuleIsStarted(void);

static int MINIT_PCS_Utils(TSRMLS_D);
static int MSHUTDOWN_PCS_Utils(TSRMLS_D);
static int RINIT_PCS_Utils(TSRMLS_D);
static int RSHUTDOWN_PCS_Utils(TSRMLS_D);

/*============================================================================*/
#endif
