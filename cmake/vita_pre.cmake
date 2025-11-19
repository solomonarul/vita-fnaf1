if(NOT DEFINED ENV{VITASDK})
    message(FATAL_ERROR "Please set VITASDK environment variable")
endif()

set(CMAKE_TOOLCHAIN_FILE $ENV{VITASDK}/share/vita.toolchain.cmake CACHE PATH "")
include("$ENV{VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME "Five Nights at Freddy's")
set(VITA_TITLEID "SLMN00001")
set(VITA_VERSION "01.00")

set(VITA_MKSFOEX_FLAGS "${VITA_MKSFOEX_FLAGS} -d PARENTAL_LEVEL=1")
# set(VITA_MKSFOEX_FLAGS "${VITA_MKSFOEX_FLAGS} -d ATTRIBUTE2=12")  # Set for bonus RAM.