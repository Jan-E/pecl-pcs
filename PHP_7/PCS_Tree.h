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

#ifndef __PCS_TREE_H
#define __PCS_TREE_H

#include "Zend/zend_portability.h"

/*---------------------------------------------------------------*/

/* Node types */

#define PCS_TYPE_DIR	0
#define PCS_TYPE_FILE	1

#define PCS_NODE_IS_DIR(np)		((np)->type == PCS_TYPE_DIR)
#define PCS_NODE_IS_FILE(np)	((np)->type == PCS_TYPE_FILE)

/* For more flags definitions, see client include file */

#define PCS_AUTOLOAD_MASK	0x03

#define PCS_FLAG_NOCHECK	0x04	/* Avoids valgrind errors in debug mode */

/*---*/

#define PCS_NODE_IS_ROOT(_np)	((_np) == root)

/*---*/

struct _PCS_Node {
	struct _PCS_Node *parent;
	int type;
	zend_long flags;
	zend_string *path;
	zend_string *uri;
	union {
		struct {
			char *data;
			size_t len;
			int alloc;
		} f;
		struct {
			HashTable items; /* <entry name> => (PCS_Node *) (ptr) */
		} d;
	} u;
};

typedef struct _PCS_Node PCS_Node;

/*---------------------------------------------------------------*/
/* Persistent data */

/* We don't set a mutex on the tree because there cannot be concurrent writes
   (it is never modified after MINIT).
*/

static PCS_Node *root;	/* Root dir */

static HashTable *pathList;	/* path => (PCS_Node *) (ptr) */
StaticMutexDeclare(pathList)

static HashTable *fileList; /* list of file nodes */

/*---------------------------------------------------------------*/

#ifdef UT_DEBUG
static void PCS_CHECK_NODE(PCS_Node *node)
{
	ZEND_ASSERT(node);
	if (node->parent) {
		PCS_CHECK_NODE(node->parent);
		ZEND_ASSERT(PCS_NODE_IS_DIR(node->parent));
	}
	if (! (node->flags & PCS_FLAG_NOCHECK)) {
		CHECK_ZSTRING(node->path);
		CHECK_ZSTRING(node->uri);
	}
}
#else
#define PCS_CHECK_NODE(node)
#endif

/*------*/

static zend_always_inline char *PCS_FILE_DATA(PCS_Node *node)
{
	PCS_CHECK_NODE(node);
	ZEND_ASSERT(PCS_NODE_IS_FILE(node));
	return node->u.f.data;
}

/*------*/

static zend_always_inline size_t PCS_FILE_LEN(PCS_Node *node)
{
	PCS_CHECK_NODE(node);
	ZEND_ASSERT(PCS_NODE_IS_FILE(node));
	return node->u.f.len;
}

/*------*/

static zend_always_inline int PCS_FILE_ALLOC(PCS_Node *node)
{
	PCS_CHECK_NODE(node);
	ZEND_ASSERT(PCS_NODE_IS_FILE(node));
	return node->u.f.alloc;
}

/*------*/

static zend_always_inline HashTable *PCS_DIR_HT(PCS_Node *node)
{
	PCS_CHECK_NODE(node);
	ZEND_ASSERT(PCS_NODE_IS_DIR(node));
	return &(node->u.d.items);
}

/*============================================================================*/

static PCS_Node *PCS_Tree_addSubNode(PCS_Node *parent, const char *name
	, size_t len, int type, zend_long flags);
static PCS_Node *PCS_Tree_addNode(const char *path, size_t pathlen
	, int type, zend_long flags);
static PCS_Node *PCS_Tree_addDir(const char *path, size_t pathlen, zend_long flags);
static PCS_Node *PCS_Tree_addFile(const char *path, size_t pathlen
	, char *data, size_t datalen, int alloc, zend_long flags);
static void PCS_Tree_destroyNode(zval *zp);
static zend_string *PCS_Tree_cleanPath(const char *path, size_t len);
static PCS_Node *PCS_Tree_resolvePath(zend_string *path);
static PCS_Node *PCS_Tree_getNodeFromPath(const char *path, size_t len);

static int MINIT_PCS_Tree(TSRMLS_D);
static int MSHUTDOWN_PCS_Tree(TSRMLS_D);
static int RINIT_PCS_Tree(TSRMLS_D);
static int RSHUTDOWN_PCS_Tree(TSRMLS_D);

/*============================================================================*/
#endif
