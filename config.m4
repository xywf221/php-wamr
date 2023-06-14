dnl config.m4 for extension wasm

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary.

dnl If your extension references something external, use 'with':

dnl PHP_ARG_WITH([wasm],
dnl   [for wasm support],
dnl   [AS_HELP_STRING([--with-wasm],
dnl     [Include wasm support])])

dnl Otherwise use 'enable':

PHP_ARG_ENABLE([wasm],
  [whether to enable wasm support],
  [AS_HELP_STRING([--enable-wasm],
    [Enable wasm support])],
  [no])

if test "$PHP_WASM" != "no"; then

  for i in /usr /usr/local ""; do
    if test -r "$i/include/wasm_c_api.h"; then
      WASM_INC_BASE=$i
    fi
  done

  if test -z "$WASM_INC_BASE"; then
    AC_MSG_ERROR(Cannot find wasm_c_api.h Please specify correct wasm micro runtime installation path)
  fi

  PHP_ADD_INCLUDE("$WASM_INC_BASE/include/wasm_c_api.h")
  PHP_ADD_INCLUDE("$WASM_INC_BASE/include/wasm_export.h")
  PHP_ADD_INCLUDE("$WASM_INC_BASE/include/lib_export.h")

  PHP_ADD_LIBRARY_WITH_PATH(iwasm, "$WASM_INC_BASE/lib", WASM_SHARED_LIBADD)

  PHP_NEW_EXTENSION(wasm, wasm.c, $ext_shared)

  PHP_SUBST(WASM_SHARED_LIBADD)
fi
