add_library(lib_simpleGame
  Source/Game.cpp
  Source/RoundTarget.cpp
  Source/RoundTarget.cpp
)

target_include_directories(lib_simpleGame
 PRIVATE
  Include
)

target_link_libraries(lib_simpleGame PUBLIC sfml-graphics)

add_executable(attackTowerGame
  Source/Main.cpp
)

target_include_directories(attackTowerGame
 PRIVATE
  Include
)

target_link_libraries(attackTowerGame PUBLIC lib_simpleGame sfml-graphics)

add_subdirectory(Test)

# The following command is executed only when cmake is executed
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../media DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
