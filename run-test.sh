#!/usr/bin/env sh

php -d extension=./modules/wasm.so -r '
wasm_runtime_init();
#$module = wasm_runtime_load(file_get_contents("/Users/dmls/Downloads/test.abc"));
$module = wasm_runtime_load(file_get_contents("./testdata/math.wasm"));
$inst = wasm_runtime_instantiate($module,8092,8092);
$func_inst = wasm_runtime_lookup_function($inst,"add");
$exec_env = wasm_runtime_create_exec_env($inst, 64 * 1024);

$params = [
  new WasmValue(WasmValkindEnum::WASM_I64,9223372036854775800),
  new WasmValue(WasmValkindEnum::WASM_I64,1)
];

var_dump(wasm_runtime_call_wasm($exec_env,$func_inst,$params));

';