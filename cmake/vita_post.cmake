message(STATUS "Linking with PSVita libraries.")

add_compile_definitions(__psp2__)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
        libgpu_es4_ext_stub_weak
        libIMGEGL_stub_weak
        libGLESv2_stub_weak
        SceDisplay_stub
        SceCtrl_stub
        SceGxm_stub
        SceAppMgr_stub
        SceCommonDialog_stub
        SceAudioIn_stub
        SceAudio_stub
        SceHid_stub
        SceMotion_stub
        SceCamera_stub
        SceTouch_stub
        SceAppUtil_stub
        SceIme_stub
        m
)

vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME} UNSAFE NOASLR)
vita_create_vpk(
    ${PROJECT_NAME}.vpk
    ${VITA_TITLEID} ${PROJECT_NAME}.self
    VERSION ${VITA_VERSION}
    NAME ${VITA_APP_NAME}
    FILE platform/vita/sce_sys sce_sys
    FILE platform/vita/module module
    FILE assets assets
)