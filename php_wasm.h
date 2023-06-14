/* wasm extension for PHP */

#include "wasm_export.h"
#include "wasm_c_api.h"

#ifndef PHP_WASM_H
#define PHP_WASM_H

extern zend_module_entry wasm_module_entry;
#define phpext_wasm_ptr &wasm_module_entry

#define PHP_WASM_NAME "wasm"

#define PHP_WASM_AUTHOR "dongmenleishao@outlook.com"

#define PHP_WASM_VERSION "0.1.0"

#if defined(ZTS) && defined(COMPILE_DL_WASM)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif /* PHP_WASM_H */


typedef struct php_wasm_module_object {
    wasm_module_t module;
    zend_object std;
} php_wasm_module_object;

static inline php_wasm_module_object *php_wasm_module_from_obj(zend_object *obj) {
    return (php_wasm_module_object *) ((char *) (obj) - XtOffsetOf(php_wasm_module_object, std));
}

typedef struct php_wasm_module_inst_object{
    wasm_module_inst_t inst;
    zend_object std;
} php_wasm_module_inst_object;


static inline php_wasm_module_inst_object *php_wasm_module_inst_from_obj(zend_object *obj) {
    return (php_wasm_module_inst_object *) ((char *) (obj) - XtOffsetOf(php_wasm_module_inst_object, std));
}

typedef struct php_wasm_function_inst_object {
    wasm_function_inst_t inst;
    zend_object std;
} php_wasm_function_inst_object;

static inline php_wasm_function_inst_object *php_wasm_function_inst_from_obj(zend_object *obj) {
    return (php_wasm_function_inst_object *) ((char *) (obj) - XtOffsetOf(php_wasm_function_inst_object, std));
}

typedef struct php_wasm_exec_env_object {
    wasm_exec_env_t env;
    zend_object std;
} php_wasm_exec_env_object;

static inline php_wasm_exec_env_object *php_wasm_exec_env_from_obj(zend_object *obj) {
    return (php_wasm_exec_env_object *) ((char *) (obj) - XtOffsetOf(php_wasm_exec_env_object, std));
}


typedef struct php_valkind_enum {
    char *name;
    enum wasm_valkind_enum kid;
} php_valkind_enum;

static const php_valkind_enum valkind_enum_list[] = {
        {"WASM_I32",     WASM_I32},
        {"WASM_I64",     WASM_I64},
        {"WASM_F32",     WASM_F32},
        {"WASM_F64",     WASM_F64},
        {"WASM_ANYREF",  WASM_ANYREF},
        {"WASM_FUNCREF", WASM_FUNCREF}
};

static zend_object *php_get_valkind_enum_from_value(zend_class_entry *class_entry, uint8_t value) {
    zend_object *obj;
    for (size_t i = 0; i < sizeof(valkind_enum_list) / sizeof(valkind_enum_list[0]); i++) {
        if (valkind_enum_list[i].kid == value) {
            obj = zend_enum_get_case_cstr(class_entry, valkind_enum_list[i].name);
        }
    }
    return obj;
}

static zval *php_get_class_enum_property_value(zval *entry, const char *name, size_t name_length) {
    zval *prop;
    prop = zend_read_property(Z_OBJCE_P(entry), Z_OBJ_P(entry), name, name_length, 0, NULL);
    return zend_read_property(Z_OBJCE_P(prop), Z_OBJ_P(prop), ZEND_STRL("value"), 0, NULL);
}