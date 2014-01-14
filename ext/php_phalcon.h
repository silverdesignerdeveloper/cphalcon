

#ifndef PHP_PHALCON_H
#define PHP_PHALCON_H 1

#include "kernel/globals.h"

#define PHP_PHALCON_NAME    ""
#define PHP_PHALCON_VERSION "0.0.1"
#define PHP_PHALCON_EXTNAME "phalcon"

typedef struct _zephir_struct_db { 
	zend_bool escape_identifiers;
} zephir_struct_db;

typedef struct _zephir_struct_orm { 
	zend_bool column_renaming;
	zend_bool events;
	int cache_level;
	zend_bool virtual_foreign_keys;
	zend_bool not_null_validations;
	zend_bool exception_on_failed_save;
	zend_bool enable_literals;
} zephir_struct_orm;



ZEND_BEGIN_MODULE_GLOBALS(phalcon)

	/* Memory */
	zephir_memory_entry *start_memory;
	zephir_memory_entry *active_memory;

	/* Virtual Symbol Tables */
	zephir_symbol_table *active_symbol_table;

	/* Function cache */
	HashTable *function_cache;

	/* Max recursion control */
	unsigned int recursive_lock;

	/* Global constants */
	zval *global_true;
	zval *global_false;
	zval *global_null;
	
	zephir_struct_db db;

	zephir_struct_orm orm;


ZEND_END_MODULE_GLOBALS(phalcon)

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_EXTERN_MODULE_GLOBALS(phalcon)

#ifdef ZTS
	#define ZEPHIR_GLOBAL(v) TSRMG(phalcon_globals_id, zend_phalcon_globals *, v)
#else
	#define ZEPHIR_GLOBAL(v) (phalcon_globals.v)
#endif

#ifdef ZTS
	#define ZEPHIR_VGLOBAL ((zend_phalcon_globals *) (*((void ***) tsrm_ls))[TSRM_UNSHUFFLE_RSRC_ID(phalcon_globals_id)])
#else
	#define ZEPHIR_VGLOBAL &(phalcon_globals)
#endif

#define zephir_globals phalcon_globals
#define zend_zephir_globals zend_phalcon_globals

extern zend_module_entry phalcon_module_entry;
#define phpext_phalcon_ptr &phalcon_module_entry

#endif
