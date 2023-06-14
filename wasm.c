/* wasm extension for PHP */

#ifdef HAVE_CONFIG_H

#include "config.h"

#endif

#include "php.h"
#include "ext/standard/info.h"
#include "zend_attributes.h"
#include "zend_exceptions.h"
#include "zend_enum.h"
#include "php_wasm.h"
#include "wasm_arginfo.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE()  \
    ZEND_PARSE_PARAMETERS_START(0, 0) \
    ZEND_PARSE_PARAMETERS_END()
#endif

zend_class_entry *php_wasm_module_ce;

static zend_object_handlers php_wasm_module_object_handlers;

static zend_object *php_wasm_module_create_object(zend_class_entry *class_type) {
    php_wasm_module_object *intern = zend_object_alloc(sizeof(php_wasm_module_object), class_type);

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &php_wasm_module_object_handlers;
    return &intern->std;
}

static zend_function *php_wasm_module_get_constructor(zend_object *object) {
    zend_throw_error(NULL, "Cannot directly construct WasmModule, use wasm_runtime_load() instead");
    return NULL;
}

static void php_wasm_module_free_obj(zend_object *object) {
    php_wasm_module_object *module_object = php_wasm_module_from_obj(object);
    wasm_runtime_unload(module_object->module);
    zend_object_std_dtor(&module_object->std);
}

zend_class_entry *php_wasm_module_inst_ce;

static zend_object_handlers php_wasm_module_inst_object_handlers;

static zend_object *php_wasm_module_inst_create_object(zend_class_entry *class_type) {
    php_wasm_module_inst_object *intern = zend_object_alloc(sizeof(php_wasm_module_inst_object),
                                                            class_type);

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &php_wasm_module_inst_object_handlers;
    return &intern->std;
}

static zend_function *php_wasm_module_inst_get_constructor(zend_object *object) {
    zend_throw_error(NULL, "Cannot directly construct WasmModule, use wasm_runtime_load() instead");
    return NULL;
}

static void php_wasm_module_inst_free_obj(zend_object *object) {
    php_wasm_module_inst_object *inst_object = php_wasm_module_inst_from_obj(object);
    wasm_runtime_deinstantiate(inst_object->inst);
    zend_object_std_dtor(&inst_object->std);
}

zend_class_entry *php_wasm_function_inst_ce;

static zend_object_handlers php_wasm_function_inst_object_handlers;

static zend_object *php_wasm_function_inst_create_object(zend_class_entry *class_type) {
    php_wasm_function_inst_object *intern = zend_object_alloc(sizeof(php_wasm_function_inst_object),
                                                               class_type);

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &php_wasm_function_inst_object_handlers;
    return &intern->std;
}

static zend_function *php_wasm_function_inst_get_constructor(zend_object *object) {
    zend_throw_error(NULL, "Cannot directly construct WasmFunction, use wasm_runtime_load() instead");
    return NULL;
}

static void php_wasm_function_inst_free_obj(zend_object *object) {
    php_wasm_function_inst_object *inst_object = php_wasm_function_inst_from_obj(object);
    wasm_runtime_deinstantiate(inst_object->inst);
    zend_object_std_dtor(&inst_object->std);
}

zend_class_entry *php_wasm_exec_env_ce;

static zend_object_handlers php_wasm_exec_env_object_handlers;

static zend_object *php_wasm_exec_env_create_object(zend_class_entry *class_type) {
    php_wasm_exec_env_object *intern = zend_object_alloc(sizeof(php_wasm_exec_env_object),
                                                          class_type);

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &php_wasm_exec_env_object_handlers;
    return &intern->std;
}

static zend_function *php_wasm_exec_env_get_constructor(zend_object *object) {
    zend_throw_error(NULL, "Cannot directly construct WasmExecEnv, use wasm_runtime_load() instead");
    return NULL;
}

static void php_wasm_exec_env_free_obj(zend_object *object) {
    php_wasm_exec_env_object *inst_object = php_wasm_exec_env_from_obj(object);
    wasm_runtime_destroy_exec_env(inst_object->env);
    zend_object_std_dtor(&inst_object->std);
}

zend_class_entry *php_wasm_valkind_enum_ce;

zend_class_entry *php_wasm_val_ce;


PHP_METHOD(Wasm_Value, __construct)
{
    zval *this_val;
    zend_object *kid_obj;
    zend_object *this_obj;
    zval kid_val;
    zval *zkey;

    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_OBJ_OF_CLASS(kid_obj, php_wasm_valkind_enum_ce)
            Z_PARAM_ZVAL(zkey)
    ZEND_PARSE_PARAMETERS_END();

    // convert to zend_object
    this_obj = Z_OBJ_P(ZEND_THIS);

    // convert kid zend_object to zval
    ZVAL_OBJ(&kid_val, kid_obj);

    zend_update_property(php_wasm_val_ce, this_obj, ZEND_STRL("kid"),&kid_val);
    zend_update_property(php_wasm_val_ce, this_obj, ZEND_STRL("val"),zkey);

//    ZVAL_LONG(OBJ_PROP_NUM(obj, 0), id);
//    zval_ptr_dtor(OBJ_PROP_NUM(obj, 1));
//    ZVAL_STR_COPY(OBJ_PROP_NUM(obj, 1), text);
//    ZVAL_LONG(OBJ_PROP_NUM(obj, 2), line);
//    ZVAL_LONG(OBJ_PROP_NUM(obj, 3), pos);
}


PHP_FUNCTION (wasm_runtime_init) {
    ZEND_PARSE_PARAMETERS_NONE();

    bool ret = wasm_runtime_init();

    RETURN_BOOL(ret);
}

PHP_FUNCTION (wasm_runtime_destroy) {
    ZEND_PARSE_PARAMETERS_NONE();

    wasm_runtime_destroy();
}

PHP_FUNCTION (wasm_runtime_load) {
    php_wasm_module_object *module_obj;
    wasm_module_t module;
    unsigned char *buffer;
    size_t buffer_len;

    char error_buf[128];

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s",
                              &buffer, &buffer_len) == FAILURE) {
        RETURN_THROWS();
    }
    module = wasm_runtime_load(buffer, (uint32_t) buffer_len, error_buf, sizeof(error_buf));
    if (module == NULL) {
        zend_throw_exception(NULL, error_buf, 0);
        RETURN_THROWS();
    }

    object_init_ex(return_value, php_wasm_module_ce);
    module_obj = php_wasm_module_from_obj(Z_OBJ_P(return_value));
    module_obj->module = module;
}

PHP_FUNCTION (wasm_runtime_instantiate) {
    wasm_module_inst_t inst;
    php_wasm_module_inst_object *inst_obj;
    zend_object *module_obj;
    zend_long stack_size;
    zend_long heap_size;
    php_wasm_module_object *module;
    char error_buf[128];

    ZEND_PARSE_PARAMETERS_START(3, 3)
            Z_PARAM_OBJ_OF_CLASS(module_obj, php_wasm_module_ce)
            Z_PARAM_LONG(stack_size)
            Z_PARAM_LONG(heap_size)
    ZEND_PARSE_PARAMETERS_END();

    module = php_wasm_module_from_obj(module_obj);

    inst = wasm_runtime_instantiate(module->module, (uint32_t) stack_size, (uint32_t) heap_size,
                                    error_buf, sizeof(error_buf));

    object_init_ex(return_value, php_wasm_module_inst_ce);
    inst_obj = php_wasm_module_inst_from_obj(Z_OBJ_P(return_value));
    inst_obj->inst = inst;
}

PHP_FUNCTION (wasm_runtime_lookup_function) {
    zend_object *obj;
    php_wasm_module_inst_object *module_inst_obj;
    php_wasm_function_inst_object *function_inst_obj;
    wasm_function_inst_t function_inst;
    char *name;
    size_t name_len = 0;
    char *signature = NULL;
    size_t signature_len = 0;

    ZEND_PARSE_PARAMETERS_START(2, 3)
            Z_PARAM_OBJ_OF_CLASS(obj, php_wasm_module_inst_ce)
            Z_PARAM_STRING(name, name_len)
            Z_PARAM_OPTIONAL
            Z_PARAM_STRING_OR_NULL(signature, signature_len)
    ZEND_PARSE_PARAMETERS_END();

    module_inst_obj = php_wasm_module_inst_from_obj(obj);

    function_inst = wasm_runtime_lookup_function(module_inst_obj->inst, name, signature);

    if (function_inst == NULL) {
        zend_throw_exception_ex(NULL, 0, "Unable to find function '%s'", name);
        RETURN_THROWS();
    }

    object_init_ex(return_value, php_wasm_function_inst_ce);
    function_inst_obj = php_wasm_function_inst_from_obj(Z_OBJ_P(return_value));
    function_inst_obj->inst = function_inst;
}

PHP_FUNCTION(wasm_runtime_create_exec_env){
    zend_object *obj;
    zend_long stack_size;
    php_wasm_module_inst_object *module_inst_obj;
    wasm_exec_env_t exec_env;
    php_wasm_exec_env_object *env_object;

    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_OBJ_OF_CLASS(obj, php_wasm_module_inst_ce)
            Z_PARAM_LONG(stack_size)
    ZEND_PARSE_PARAMETERS_END();

    module_inst_obj = php_wasm_module_inst_from_obj(obj);

    exec_env = wasm_runtime_create_exec_env(module_inst_obj->inst, stack_size);

    object_init_ex(return_value, php_wasm_exec_env_ce);
    env_object = php_wasm_exec_env_from_obj(Z_OBJ_P(return_value));
    env_object->env = exec_env;
}

PHP_FUNCTION(wasm_runtime_call_wasm){
    zend_object *exec_env_obj;
    zend_object *function_inst_obj;
    zval *params;
    zend_array *params_array;
    uint32_t count, params_count, result_count;

    php_wasm_exec_env_object *exec_env;
    php_wasm_function_inst_object *function_inst;

    wasm_module_inst_t module_inst;

    bool call_ret;


    ZEND_PARSE_PARAMETERS_START(3, 3)
            Z_PARAM_OBJ_OF_CLASS(exec_env_obj, php_wasm_exec_env_ce)
            Z_PARAM_OBJ_OF_CLASS(function_inst_obj, php_wasm_function_inst_ce)
            Z_PARAM_ARRAY(params)ZEND_PARSE_PARAMETERS_END();

    params_array = Z_ARRVAL_P(params);

    if (!zend_array_is_list(params_array)) {
        zend_throw_exception_ex(NULL, 0, "params must be an list array");
        RETURN_THROWS();
    }

    count = zend_array_count(params_array);

    int i = 0;
    wasm_val_t args[count];

    zval *hash_entry;
    ZEND_HASH_FOREACH_VAL(params_array, hash_entry)
    {
        // check hash_entry is class wasm_val
        if (Z_TYPE_P(hash_entry) == IS_OBJECT && Z_OBJCE_P(hash_entry) == php_wasm_val_ce) {
            zval *kid_val_prop, *val_prop;
            val_prop = zend_read_property(Z_OBJCE_P(hash_entry), Z_OBJ_P(hash_entry), ZEND_STRL("val"), 0,
                                          NULL);
            kid_val_prop = php_get_class_enum_property_value(hash_entry, ZEND_STRL("kid"));
            args[i].kind = zval_get_long(kid_val_prop);
            switch (args[i].kind) {
                case WASM_I32:
                    args[i].of.i32 = (int32_t) zval_get_long(val_prop);
                    break;
                case WASM_I64:
                    args[i].of.i64 = zval_get_long(val_prop);
                    break;
                case WASM_F32:
                    args[i].of.f32 = (float) zval_get_double(val_prop);
                    break;
                case WASM_F64:
                    args[i].of.f64 = zval_get_double(val_prop);
                    break;
                case WASM_ANYREF:
                    //todo
                    break;
                case WASM_FUNCREF:
                    //todo
                    break;
            }
        } else {
            // warn user
            zend_throw_exception_ex(NULL, 0, "params must be an array of wasm_val");
        }
        i++;
    }ZEND_HASH_FOREACH_END();

    exec_env = php_wasm_exec_env_from_obj(exec_env_obj);
    function_inst = php_wasm_function_inst_from_obj(function_inst_obj);

    module_inst = wasm_runtime_get_module_inst(exec_env->env);

    params_count = wasm_func_get_param_count(function_inst->inst, module_inst);
    result_count = wasm_func_get_result_count(function_inst->inst, module_inst);

    if (params_count != count) {
        zend_throw_exception_ex(NULL, 0, "params count not match with function signature %d:%d", params_count, count);
    }

    wasm_val_t results[result_count];
    call_ret = wasm_runtime_call_wasm_a(exec_env->env, function_inst->inst, result_count, results, count, args);

    if (!call_ret){
        zend_throw_exception_ex(NULL, 0, "Unable to call wasm function : %s", wasm_runtime_get_exception(module_inst));
        RETURN_THROWS();
    }

    array_init_size(return_value,result_count);

    for (int j = 0; j < result_count; j++) {
        zval zv;
        zend_object *obj;
        object_init_ex(&zv, php_wasm_val_ce);
        obj = Z_OBJ(zv);

        ZVAL_OBJ(OBJ_PROP_NUM(obj, 0),  php_get_valkind_enum_from_value(php_wasm_valkind_enum_ce, results[j].kind));
        switch (results[j].kind) {
            case WASM_I32:
                ZVAL_LONG(OBJ_PROP_NUM(obj, 1), results[j].of.i64);
                break;
            case WASM_I64:
                ZVAL_LONG(OBJ_PROP_NUM(obj, 1), results[j].of.i64);
                break;
            case WASM_F32:
                ZVAL_DOUBLE(OBJ_PROP_NUM(obj, 1), results[j].of.f32);
                break;
            case WASM_F64:
                ZVAL_DOUBLE(OBJ_PROP_NUM(obj, 1), results[j].of.f32);
                break;
            case WASM_ANYREF:
                //todo
                break;
            case WASM_FUNCREF:
                //todo
                break;
        }
        add_index_object(return_value,j, obj);
    }

}

PHP_FUNCTION(wasm_func_get_param_count){
    zend_object *function_inst_obj;
    zend_object *module_inst_obj;

    php_wasm_function_inst_object *function_inst;
    php_wasm_module_inst_object *module_inst;

    uint32_t count;

    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_OBJ_OF_CLASS(function_inst_obj, php_wasm_function_inst_ce)
            Z_PARAM_OBJ_OF_CLASS(module_inst_obj, php_wasm_module_inst_ce)
    ZEND_PARSE_PARAMETERS_END();

    function_inst = php_wasm_function_inst_from_obj(function_inst_obj);
    module_inst = php_wasm_module_inst_from_obj(module_inst_obj);

    count = wasm_func_get_param_count(function_inst->inst,module_inst->inst);

    RETURN_LONG(count);
}

PHP_FUNCTION(wasm_func_get_result_count){
    zend_object *function_inst_obj;
    zend_object *module_inst_obj;

    php_wasm_function_inst_object *function_inst;
    php_wasm_module_inst_object *module_inst;

    uint32_t count;

    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_OBJ_OF_CLASS(function_inst_obj, php_wasm_function_inst_ce)
            Z_PARAM_OBJ_OF_CLASS(module_inst_obj, php_wasm_module_inst_ce)
    ZEND_PARSE_PARAMETERS_END();

    function_inst = php_wasm_function_inst_from_obj(function_inst_obj);
    module_inst = php_wasm_module_inst_from_obj(module_inst_obj);

    count = wasm_func_get_result_count(function_inst->inst,module_inst->inst);

    RETURN_LONG(count);
}

PHP_FUNCTION(wasm_func_get_param_types) {
    zend_object *function_inst_obj;
    zend_object *module_inst_obj;

    php_wasm_function_inst_object *function_inst;
    php_wasm_module_inst_object *module_inst;


    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_OBJ_OF_CLASS(function_inst_obj, php_wasm_function_inst_ce)
            Z_PARAM_OBJ_OF_CLASS(module_inst_obj, php_wasm_module_inst_ce)
    ZEND_PARSE_PARAMETERS_END();

    function_inst = php_wasm_function_inst_from_obj(function_inst_obj);
    module_inst = php_wasm_module_inst_from_obj(module_inst_obj);

    uint32_t count = wasm_func_get_param_count(function_inst->inst, module_inst->inst);

    wasm_valkind_t param_types[count];

    wasm_func_get_param_types(function_inst->inst, module_inst->inst, param_types);

    array_init(return_value);

    for (int i = 0; i < count; i++) {
        add_index_object(return_value, i, php_get_valkind_enum_from_value(php_wasm_valkind_enum_ce, param_types[i]));
    }

}


PHP_FUNCTION(wasm_func_get_result_types) {
    zend_object *function_inst_obj;
    zend_object *module_inst_obj;

    php_wasm_function_inst_object *function_inst;
    php_wasm_module_inst_object *module_inst;


    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_OBJ_OF_CLASS(function_inst_obj, php_wasm_function_inst_ce)
            Z_PARAM_OBJ_OF_CLASS(module_inst_obj, php_wasm_module_inst_ce)
    ZEND_PARSE_PARAMETERS_END();

    function_inst = php_wasm_function_inst_from_obj(function_inst_obj);
    module_inst = php_wasm_module_inst_from_obj(module_inst_obj);

    uint32_t count = wasm_func_get_result_count(function_inst->inst, module_inst->inst);

    wasm_valkind_t result_types[count];

    wasm_func_get_result_types(function_inst->inst, module_inst->inst, result_types);

    array_init(return_value);

    for (int i = 0; i < count; i++) {
        add_index_object(return_value, i, php_get_valkind_enum_from_value(php_wasm_valkind_enum_ce, result_types[i]));
    }


}




PHP_MINIT_FUNCTION (wasm) {
    php_wasm_module_ce = register_class_wasm_module();
    php_wasm_module_ce->create_object = &php_wasm_module_create_object;

    memcpy(&php_wasm_module_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    php_wasm_module_object_handlers.offset = XtOffsetOf(struct php_wasm_module_object, std);
    php_wasm_module_object_handlers.free_obj = php_wasm_module_free_obj;
    php_wasm_module_object_handlers.clone_obj = NULL;


    php_wasm_module_inst_ce = register_class_wasm_module_inst();
    php_wasm_module_inst_ce->create_object = &php_wasm_module_inst_create_object;

    memcpy(&php_wasm_module_inst_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    php_wasm_module_inst_object_handlers.offset = XtOffsetOf(struct php_wasm_module_inst_object, std);
    php_wasm_module_inst_object_handlers.free_obj = php_wasm_module_inst_free_obj;
    php_wasm_module_inst_object_handlers.clone_obj = NULL;

    // wasm function class
    php_wasm_function_inst_ce = register_class_wasm_function_inst();
    php_wasm_function_inst_ce->create_object = &php_wasm_function_inst_create_object;

    memcpy(&php_wasm_function_inst_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    php_wasm_function_inst_object_handlers.offset = XtOffsetOf(struct php_wasm_function_inst_object, std);
    php_wasm_function_inst_object_handlers.get_constructor = php_wasm_function_inst_get_constructor;
    php_wasm_function_inst_object_handlers.free_obj = php_wasm_function_inst_free_obj;
    php_wasm_function_inst_object_handlers.clone_obj = NULL;

    // wasm exec env class

    php_wasm_exec_env_ce = register_class_wasm_exec_env();
    php_wasm_exec_env_ce->create_object = &php_wasm_exec_env_create_object;

    memcpy(&php_wasm_exec_env_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    php_wasm_exec_env_object_handlers.offset = XtOffsetOf(struct php_wasm_exec_env_object, std);
    php_wasm_exec_env_object_handlers.get_constructor = php_wasm_exec_env_get_constructor;
    php_wasm_exec_env_object_handlers.free_obj = php_wasm_exec_env_free_obj;
    php_wasm_exec_env_object_handlers.clone_obj = NULL;

    php_wasm_valkind_enum_ce = register_class_wasm_valkind_enum();
    php_wasm_val_ce = register_class_wasm_val();

    return SUCCESS;
}

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION (wasm) {
#if defined(ZTS) && defined(COMPILE_DL_WASM)
    ZEND_TSRMLS_CACHE_UPDATE();
#endif

    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION (wasm) {
    zend_string *wasm_version_text;
    uint32_t major, minor, patch;
    wasm_runtime_get_version(&major, &minor, &patch);
    wasm_version_text = zend_strpprintf(255,"%d.%d.%d",major,minor,patch);

    php_info_print_table_start();
    php_info_print_table_row(2, "wasm support", "enabled");
    php_info_print_table_row(2, "wasm version", ZSTR_VAL(wasm_version_text));
    php_info_print_table_end();
}
/* }}} */

/* {{{ wasm_module_entry */
zend_module_entry wasm_module_entry = {
        STANDARD_MODULE_HEADER,
        "wasm",              /* Extension name */
        ext_functions,      /* zend_function_entry */
        PHP_MINIT(wasm),  /* PHP_MINIT - Module initialization */
        NULL,              /* PHP_MSHUTDOWN - Module shutdown */
        PHP_RINIT(wasm),  /* PHP_RINIT - Request initialization */
        NULL,              /* PHP_RSHUTDOWN - Request shutdown */
        PHP_MINFO(wasm),  /* PHP_MINFO - Module info */
        PHP_WASM_VERSION, /* Version */
        STANDARD_MODULE_PROPERTIES};
/* }}} */

#ifdef COMPILE_DL_WASM
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif

ZEND_GET_MODULE(wasm)

#endif
