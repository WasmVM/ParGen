set(CPACK_PACKAGE_NAME ${CMAKE_PROJECT_NAME})

if(WIN32 AND NOT UNIX)
    set(CPACK_SET_DESTDIR OFF)
    set(CPACK_NSIS_PACKAGE_NAME ParGen)
    set(CPACK_NSIS_MODIFY_PATH ON)
    set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
    set(CPACK_PACKAGE_INSTALL_DIRECTORY ParGen)
else(WIN32 AND NOT UNIX)
    set(CPACK_SET_DESTDIR ON)
endif(WIN32 AND NOT UNIX)
set(CPACK_PACKAGE_VENDOR "WasmVM")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Parser generator in C++ flavor")
set(CPACK_VERBATIM_VARIABLES True)
set(CPACK_OUTPUT_FILE_PREFIX ${PROJECT_ROOT})
set(CPACK_DEBIAN_PACKAGE_DEPENDS "")

set(CPACK_THREADS 0)

# Debian
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Luis Hsu")
set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA
    ${CMAKE_CURRENT_LIST_DIR}/triggers
)
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)

# Productbuild
if(APPLE)
set(CPACK_GENERATOR productbuild CACHE STRING "CPack generator")
set(CPACK_PRODUCTBUILD_IDENTIFIER org.WasmVM.ParGen)
endif(APPLE)

include(CPack)