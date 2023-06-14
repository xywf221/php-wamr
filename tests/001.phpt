--TEST--
Check if wasm is loaded
--EXTENSIONS--
wasm
--FILE--
<?php
echo 'The extension "wasm" is available';
?>
--EXPECT--
The extension "wasm" is available
