cmake_minimum_required (VERSION 2.6)
project( GamepadController )

include_directories("${PROJECT_BINARY_DIR}/Include"
                    "${PROJECT_BINARY_DIR}/Mock"
					"/usr/share/qt4/mkspecs/linux-g++-64"
					"/usr/include/qt4/QtCore"
					"/usr/include/qt4/QtGui"
					"/usr/include/qt4")


file(GLOB GeneratedSources "GeneratedSource/*.cpp")
file(GLOB TestSources "Test/*.cpp")
file(GLOB Gtest "Gtest/gtest-all.o"
				"Gtest/gtest_main.o"
				"Gtest/gmock-all.o")
file(GLOB Sources "Source/*.cpp")

add_executable(JoypadHandlerTest ${GeneratedSources}
                                 ${TestSources}
                                  Source/JoypadHandler.cpp
                                  Source/JoypadAxis.cpp
                                  Source/JoypadButton.cpp
                                  Source/JoypadListener.cpp
                                  Source/SystemController.cpp
                                  Source/PressedOrReleased.cpp
                                  Source/ChromeShortcuts.cpp
                                  Source/ConfigStore.cpp
                                  Source/DolphinShortcuts.cpp
                                  Source/ClementineShortcuts.cpp
                                  Source/VlcShortcuts.cpp
                                  Source/InactivityFilter.cpp
                                  Source/ButtonsAndAxisStateKeeper.cpp)

set(EXTERNAL_LIBS -pthread -lXtst -lQtGui -lQtCore -lpthread -lX11)
target_link_libraries (JoypadHandlerTest gtest gtest_main gmock ${EXTERNAL_LIBS})

add_executable(GamepadController EXCLUDE_FROM_ALL ${GeneratedSources} ${Sources})
target_link_libraries(GamepadController ${EXTERNAL_LIBS})
