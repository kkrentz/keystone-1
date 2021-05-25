project(keystone-verifier C CXX)

set(CFLAGS      "-Wall -Werror")
set(LDFLAGS     "-static")

add_compile_definitions(uECC_CURVE=uECC_secp256r1
                        uECC_ENABLE_VLI_API=1
                        uECC_SUPPORTS_secp160r1=0
                        uECC_SUPPORTS_secp192r1=0
                        uECC_SUPPORTS_secp224r1=0
                        uECC_SUPPORTS_secp256r1=1
                        uECC_SUPPORTS_secp256k1=0
                        )

set(SOURCE_FILES
    json11.cpp
    keys.cpp
    Report.cpp
    $ENV{KEYSTONE_SM}/src/libcoap/ext/micro-ecc/uECC.c
    )

set(INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}/include/verifier
    $ENV{KEYSTONE_SM}/src/libcoap/ext/micro-ecc
    $ENV{KEYSTONE_SM}/src/
    )

set(CMAKE_C_FLAGS          "${CMAKE_C_FLAGS} ${CFLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LDFLAGS}")

include_directories(${INCLUDE_DIRS})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${COMMON_SOURCE_FILES})

install(TARGETS ${PROJECT_NAME} DESTINATION ${out_dir}/lib)
install(DIRECTORY ${INCLUDE_DIRS} DESTINATION ${out_dir}/include)
