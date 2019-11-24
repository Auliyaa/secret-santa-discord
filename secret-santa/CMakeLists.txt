# =================================
# target: secret-santa
# =================================
add_executable(secret-santa
    src/main.cpp
    src/santa.cpp
)

target_include_directories(secret-santa PRIVATE
    include
)

target_link_libraries(secret-santa PRIVATE
    sleepy-discord
)

install(TARGETS secret-santa DESTINATION bin)
