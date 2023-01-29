file(GLOB SRC_LIST "*.cpp")
set(BINARY_NAME phoenix)
add_executable(${BINARY_NAME} ${SRC_LIST})

add_library(${PHOENIX_TEST} UnderlyingChaos.cpp PhoenixHookPosition.cpp)
target_link_libraries(${PHOENIX_TEST} PUBLIC
                     ${CRYPTO_TARGET} ${TOOL_TARGET} ${TARS_PROTOCOL_TARGET} ${SECURITY_TARGET})