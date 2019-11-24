# =================================
# import target: sleepy-discord
# =================================
include(ExternalProject)

ExternalProject_Add(sleepy-discord-ext
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/yourWaifu/sleepy-discord
    BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/yourWaifu/sleepy-discord/build
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=RelWithDebInfo
    INSTALL_COMMAND ""
)

add_library(sleepy-discord STATIC IMPORTED GLOBAL)

set(SLEEPY_DISCORD_INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/yourWaifu/sleepy-discord/include
    ${CMAKE_CURRENT_SOURCE_DIR}/yourWaifu/sleepy-discord/deps/asio/asio/include
    ${CMAKE_CURRENT_SOURCE_DIR}/yourWaifu/sleepy-discord/deps/cpr/include
)

foreach(iid ${SLEEPY_DISCORD_INCLUDE_DIRECTORIES})
    file(MAKE_DIRECTORY ${iid})
endforeach(iid)

set_target_properties(sleepy-discord PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/yourWaifu/sleepy-discord/build/sleepy_discord/libsleepy-discord.a
    INTERFACE_INCLUDE_DIRECTORIES "${SLEEPY_DISCORD_INCLUDE_DIRECTORIES}"
)

add_dependencies(sleepy-discord sleepy-discord-ext)
