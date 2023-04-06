cmake_minimum_required(VERSION 3.24)

project(BB_ROC)

set(CMAKE_CXX_STANDARD 23)

find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)



set(SOURCE_FILES
        main.cpp
        src/Window/Window.hpp
        src/Window/Window.cpp
        src/Images/IconImage.hpp
        src/enums.hpp
        src/Images/IconImage.cpp src/Instance/Instance.cpp src/Device/PhysicalDevice.hpp src/Device/PhysicalDevice.cpp src/shared.hpp src/Surface/Surface.hpp src/Surface/Surface.cpp)

if(APPLE)

    find_library(Cocoa NAMES Cocoa)
    if (NOT Cocoa)
        message(FATAL_ERROR "Cocoa not found")
    endif()

    set(SOURCE_FILES ${SOURCE_FILES} src/Platforms/MacOS/MMWindow.m src/Platforms/MacOS/MMIcon.m)
    #find xrandr
   # set(SOURCE_FILES ${SOURCE_FILES} src/Platforms/X11/XWindow.cpp src/Platforms/X11/XIcon.cpp)


    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

endif()

if (UNIX AND NOT APPLE)
    find_program(X11_WM_CMD "wmctrl")
    if (X11_WM_CMD)
        find_package(X11 REQUIRED)
        if (NOT X11_FOUND)
            message(FATAL_ERROR "X11 not found")
        endif()
        set(SOURCE_FILES ${SOURCE_FILES} src/Platforms/X11/XWindow.cpp src/Surface/Surface.cpp)
        # Window manager is X11, do something
    endif()
endif()

include_directories(src)

if (APPLE)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan glfw ${Cocoa})

else()
    add_executable(${PROJECT_NAME} ${SOURCE_FILES})
    target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan glfw)

endif()

