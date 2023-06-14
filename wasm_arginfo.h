/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 54b0ffc3af871b189435266df516f7575c1b9675 */





ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wasm_runtime_init, 0, 0, _IS_BOOL, 0)

ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wasm_runtime_destroy, 0, 0, IS_VOID, 0)

ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_wasm_runtime_load, WasmModule, 0)
                ZEND_ARG_TYPE_INFO(0, buffer, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_wasm_runtime_instantiate, WasmModuleInstantiate, 0)
                ZEND_ARG_OBJ_INFO(0, module, WasmModule, 0)
                ZEND_ARG_TYPE_INFO(0, default_stack_size, IS_LONG, 0)
                ZEND_ARG_TYPE_INFO(0, default_heap_size, IS_LONG, 0)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_wasm_runtime_lookup_function, WasmFunctionInstantiate, 0)
                ZEND_ARG_OBJ_INFO(0, module_inst, WasmModuleInstantiate, 0)
                ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
                ZEND_ARG_TYPE_INFO(0, signature, IS_STRING, 1)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(arginfo_wasm_runtime_create_exec_env, WasmExecEnv, 0)
                ZEND_ARG_OBJ_INFO(0, module_inst, WasmModuleInstantiate, 0)
                ZEND_ARG_TYPE_INFO(0, stack_size, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wasm_runtime_call_wasm, 0, 0, IS_ARRAY, 0)
                ZEND_ARG_OBJ_INFO(0, exec_env, WasmExecEnv, 0)
                ZEND_ARG_OBJ_INFO(0, function_inst, WasmFunctionInstantiate, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wasm_func_get_param_count, 0, 0, IS_LONG, 0)
                ZEND_ARG_OBJ_INFO(0, function_inst, WasmFunctionInstantiate, 0)
                ZEND_ARG_OBJ_INFO(0, module_inst, WasmModuleInstantiate, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wasm_func_get_result_count, 0, 0, IS_LONG, 0)
                ZEND_ARG_OBJ_INFO(0, function_inst, WasmFunctionInstantiate, 0)
                ZEND_ARG_OBJ_INFO(0, module_inst, WasmModuleInstantiate, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wasm_func_get_param_types, 0, 0, IS_ARRAY, 0)
                ZEND_ARG_OBJ_INFO(0, function_inst, WasmFunctionInstantiate, 0)
                ZEND_ARG_OBJ_INFO(0, module_inst, WasmModuleInstantiate, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wasm_func_get_result_types, 0, 0, IS_LONG, 0)
                ZEND_ARG_OBJ_INFO(0, function_inst, WasmFunctionInstantiate, 0)
                ZEND_ARG_OBJ_INFO(0, module_inst, WasmModuleInstantiate, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Wasm_Value___construct, 0, 0, 1)
                ZEND_ARG_OBJ_INFO(0, kid, WasmValkindEnum, 0)
                ZEND_ARG_TYPE_MASK(0, val, MAY_BE_STRING | MAY_BE_LONG | MAY_BE_DOUBLE, 0)
ZEND_END_ARG_INFO()



ZEND_FUNCTION(wasm_runtime_init);

ZEND_FUNCTION(wasm_runtime_destroy);

ZEND_FUNCTION(wasm_runtime_load);

ZEND_FUNCTION(wasm_runtime_instantiate);

ZEND_FUNCTION(wasm_runtime_lookup_function);

ZEND_FUNCTION(wasm_runtime_create_exec_env);

ZEND_FUNCTION(wasm_runtime_call_wasm);

ZEND_FUNCTION(wasm_func_get_param_count);

ZEND_FUNCTION(wasm_func_get_result_count);

ZEND_FUNCTION(wasm_func_get_param_types);
ZEND_FUNCTION(wasm_func_get_result_types);

ZEND_METHOD(Wasm_Value, __construct);

static const zend_function_entry ext_functions[] = {
        ZEND_FE(wasm_runtime_init, arginfo_wasm_runtime_init)
        ZEND_FE(wasm_runtime_destroy, arginfo_wasm_runtime_destroy)
        ZEND_FE(wasm_runtime_load, arginfo_wasm_runtime_load)
        ZEND_FE(wasm_runtime_instantiate, arginfo_wasm_runtime_instantiate)
        ZEND_FE(wasm_runtime_lookup_function, arginfo_wasm_runtime_lookup_function)
        ZEND_FE(wasm_runtime_create_exec_env, arginfo_wasm_runtime_create_exec_env)
        ZEND_FE(wasm_runtime_call_wasm, arginfo_wasm_runtime_call_wasm)
        ZEND_FE(wasm_func_get_param_count, arginfo_wasm_func_get_param_count)
        ZEND_FE(wasm_func_get_result_count, arginfo_wasm_func_get_result_count)
        ZEND_FE(wasm_func_get_param_types, arginfo_wasm_func_get_param_types)
        ZEND_FE(wasm_func_get_result_types, arginfo_wasm_func_get_result_types)
        ZEND_FE_END
};


static const zend_function_entry class_wasm_module_methods[] = {
        ZEND_FE_END
};


static const zend_function_entry class_wasm_module_inst_methods[] = {
        ZEND_FE_END
};

static const zend_function_entry class_wasm_function_inst_methods[] = {
        ZEND_FE_END
};

static const zend_function_entry class_wasm_exec_env_methods[] = {
        ZEND_FE_END
};

static const zend_function_entry class_wasm_valkind_enum_methods[] = {
        ZEND_FE_END
};



static const zend_function_entry class_wasm_val_methods[] = {
        PHP_ME(Wasm_Value, __construct,               arginfo_class_Wasm_Value___construct,         ZEND_ACC_PUBLIC)
        ZEND_FE_END
};

static zend_class_entry *register_class_wasm_module(void) {
    zend_class_entry ce, *class_entry;

    INIT_CLASS_ENTRY(ce, "WasmModule", class_wasm_module_methods);
    class_entry = zend_register_internal_class_ex(&ce, NULL);
    class_entry->ce_flags |= ZEND_ACC_FINAL | ZEND_ACC_NO_DYNAMIC_PROPERTIES | ZEND_ACC_NOT_SERIALIZABLE;

    return class_entry;
}

static zend_class_entry *register_class_wasm_module_inst(void) {
    zend_class_entry ce, *class_entry;

    INIT_CLASS_ENTRY(ce, "WasmInstantiateModule", class_wasm_module_inst_methods);
    class_entry = zend_register_internal_class_ex(&ce, NULL);
    class_entry->ce_flags |= ZEND_ACC_FINAL | ZEND_ACC_NO_DYNAMIC_PROPERTIES | ZEND_ACC_NOT_SERIALIZABLE;

    return class_entry;
}

static zend_class_entry *register_class_wasm_function_inst(void) {
    zend_class_entry ce, *class_entry;
    INIT_CLASS_ENTRY(ce, "WasmFunctionInstantiate", class_wasm_function_inst_methods);
    class_entry = zend_register_internal_class_ex(&ce, NULL);
    class_entry->ce_flags |= ZEND_ACC_FINAL | ZEND_ACC_NO_DYNAMIC_PROPERTIES | ZEND_ACC_NOT_SERIALIZABLE;
    return class_entry;
}

static zend_class_entry *register_class_wasm_exec_env(void) {
    zend_class_entry ce, *class_entry;
    INIT_CLASS_ENTRY(ce, "WasmExecEnv", class_wasm_exec_env_methods);
    class_entry = zend_register_internal_class_ex(&ce, NULL);
    class_entry->ce_flags |= ZEND_ACC_FINAL | ZEND_ACC_NO_DYNAMIC_PROPERTIES | ZEND_ACC_NOT_SERIALIZABLE;
    return class_entry;
}

static zend_class_entry *register_class_wasm_valkind_enum(void) {
    zend_class_entry *class_entry = zend_register_internal_enum("WasmValkindEnum", IS_LONG, class_wasm_valkind_enum_methods);
    zval v;
    for (int i = 0; i < sizeof(valkind_enum_list) / sizeof(valkind_enum_list[0]); i++) {
        ZVAL_LONG(&v, valkind_enum_list[i].kid);
        zend_enum_add_case_cstr(class_entry, valkind_enum_list[i].name, &v);
    }
    return class_entry;
}

static zend_class_entry *register_class_wasm_val(void) {
    zend_class_entry ce, *class_entry;
    INIT_CLASS_ENTRY(ce, "WasmValue", class_wasm_val_methods);
    class_entry = zend_register_internal_class_ex(&ce, NULL);
    class_entry->ce_flags |= ZEND_ACC_FINAL | ZEND_ACC_CHANGED;

    zend_string *property_kid_class_WasmValkindEnum = zend_string_init(ZEND_STRL("WasmValkindEnum"), 1);

    zend_string *property_kid_name = zend_string_init(ZEND_STRL("kid"), 1);
    zval property_kid_default_value;
    ZVAL_UNDEF(&property_kid_default_value);

    zend_declare_typed_property(class_entry, property_kid_name, &property_kid_default_value, ZEND_ACC_PUBLIC,
                                NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_kid_class_WasmValkindEnum, 0, 0));

    zend_string_release(property_kid_name);

    zend_string *property_val_name = zend_string_init(ZEND_STRL("val"), 1);
    zval property_val_default_value;
    ZVAL_UNDEF(&property_kid_default_value);

    zend_declare_typed_property(class_entry, property_val_name, &property_val_default_value, ZEND_ACC_PUBLIC,
                                NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING | MAY_BE_LONG | MAY_BE_DOUBLE));

    zend_string_release(property_val_name);

    return class_entry;
}

