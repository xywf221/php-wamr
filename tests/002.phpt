--TEST--
test1() Basic test
--EXTENSIONS--
wasm
--FILE--
<?php
$ret = test1();

var_dump($ret);
?>
--EXPECT--
The extension wasm is loaded and working!
NULL
