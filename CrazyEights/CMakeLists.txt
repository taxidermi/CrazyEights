# CMakeList.txt : CMake project for CrazyEights, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (CrazyEights "main.cpp" "template/Card.h" "template/Card.cpp" "template/Player.h" "template/Player.cpp" "template/Deck.h" "template/Deck.cpp"  "src/Round.h" "src/Round.cpp" "src/Game.h" "src/Game.cpp" "src/Utils.h" "src/Bot.h" "src/Bot.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CrazyEights PROPERTY CXX_STANDARD 20)
endif()
