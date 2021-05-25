include(${src_dir}/macros.cmake)

set(libmodules              app edge host verifier)
set(enabled_libmodules      app edge host verifier)

# Common
file(GLOB_RECURSE
  COMMON_SOURCE_FILES
  $ENV{KEYSTONE_SM}/src/libcoap/src/oscore-ng/oscore_ng_sha_256.c)

foreach(module ${enabled_libmodules})
    add_subdirectory(${module})
endforeach()

install(FILES $ENV{KEYSTONE_SM}/src/libcoap/include/oscore-ng/oscore_ng_sha_256.h
  $ENV{KEYSTONE_SM}/src/libcoap/include/coap3/coap_internal.h
  DESTINATION ${out_dir}/include)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/shared
  DESTINATION ${out_dir}/include)
