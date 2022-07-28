IF(NOT EXISTS "/Users/lkindere/Desktop/test/Importer/build/install_manifest.txt")
  MESSAGE(FATAL_ERROR "Cannot find install manifest: \"/Users/lkindere/Desktop/test/Importer/build/install_manifest.txt\"")
ENDIF(NOT EXISTS "/Users/lkindere/Desktop/test/Importer/build/install_manifest.txt")

FILE(READ "/Users/lkindere/Desktop/test/Importer/build/install_manifest.txt" files)
STRING(REGEX REPLACE "\n" ";" files "${files}")
FOREACH(file ${files})
  MESSAGE(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
  EXEC_PROGRAM(
    "/Users/lkindere/.brew/Cellar/cmake/3.23.2/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
    OUTPUT_VARIABLE rm_out
    RETURN_VALUE rm_retval
    )
  IF(NOT "${rm_retval}" STREQUAL 0)
    MESSAGE(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
  ENDIF(NOT "${rm_retval}" STREQUAL 0)
ENDFOREACH(file)
