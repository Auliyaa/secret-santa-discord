# =================================
# sleepy-discord
# =================================
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        #using cmake to configure curl on linux has issues
        #so use system curl
        set(USE_SYSTEM_CURL ON CACHE INTERNAL BOOL "")
endif()

add_subdirectory(yourWaifu/sleepy-discord)
