
link_libraries(glfw)

include_directories(${glfw_INCLUDE_DIRS} "${GLFW_SOURCE_DIR}/deps")

if (MATH_LIBRARY)
    link_libraries("${MATH_LIBRARY}")
endif()

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

if (GLFW_USE_OSMESA)
    add_definitions(-DUSE_NATIVE_OSMESA)
endif()

if (WIN32)
    set(ICON glfw.rc)
elseif (APPLE)
    set(ICON glfw.icns myColoredTranglefragmentShaderSource.fs myColoredTranglevertexShaderSource.vs myTextureWithboxFragmentShaderSource.fs myTextureWithboxVertexShaderSource.vs container.jpg awesomeface.png)
    set_source_files_properties(glfw.icns PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources")
    set_source_files_properties(myColoredTranglefragmentShaderSource.fs PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources")
    set_source_files_properties(myColoredTranglevertexShaderSource.vs PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources")
    set_source_files_properties(myTextureWithboxFragmentShaderSource.fs PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources")
    set_source_files_properties(myTextureWithboxVertexShaderSource.vs PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources")
    set_source_files_properties(awesomeface.png PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources")
    set_source_files_properties(container.jpg PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources")
endif()

set(GLAD "${GLFW_SOURCE_DIR}/deps/glad/glad.h"
         "${GLFW_SOURCE_DIR}/deps/glad.c")
set(GETOPT "${GLFW_SOURCE_DIR}/deps/getopt.h"
           "${GLFW_SOURCE_DIR}/deps/getopt.c")
set(TINYCTHREAD "${GLFW_SOURCE_DIR}/deps/tinycthread.h"
                "${GLFW_SOURCE_DIR}/deps/tinycthread.c")
set(READSHADER "${GLFW_SOURCE_DIR}/deps/loadshader.h")
set(LOADIMAGE "${GLFW_SOURCE_DIR}/deps/stb_image.h")


add_executable(boing WIN32 MACOSX_BUNDLE boing.c ${ICON} ${GLAD})
add_executable(gears WIN32 MACOSX_BUNDLE gears.c ${ICON} ${GLAD})
add_executable(heightmap WIN32 MACOSX_BUNDLE heightmap.c ${ICON} ${GLAD})
add_executable(offscreen offscreen.c ${ICON} ${GLAD})
add_executable(particles WIN32 MACOSX_BUNDLE particles.c ${ICON} ${TINYCTHREAD} ${GETOPT} ${GLAD})
add_executable(sharing WIN32 MACOSX_BUNDLE sharing.c ${ICON} ${GLAD})
add_executable(simple WIN32 MACOSX_BUNDLE simple.c ${ICON} ${GLAD})
add_executable(splitview WIN32 MACOSX_BUNDLE splitview.c ${ICON} ${GLAD})
add_executable(wave WIN32 MACOSX_BUNDLE wave.c ${ICON} ${GLAD})
add_executable(myWindow WIN32 MACOSX_BUNDLE myWindow.c ${ICON} ${GLAD})
add_executable(myTrangle WIN32 MACOSX_BUNDLE myTrangle.c ${ICON} ${GLAD})
add_executable(myColoredTrangle WIN32 MACOSX_BUNDLE myColoredTrangle.c ${ICON} ${GLAD} ${READSHADER})
add_executable(myTextureWithbox WIN32 MACOSX_BUNDLE myTextureWithbox.c ${ICON} ${GLAD} ${READSHADER} ${LOADIMAGE})

target_link_libraries(particles "${CMAKE_THREAD_LIBS_INIT}")
if (RT_LIBRARY)
    target_link_libraries(particles "${RT_LIBRARY}")
endif()

set(WINDOWS_BINARIES boing gears heightmap particles sharing simple splitview wave myWindow myTrangle myColoredTrangle myTextureWithbox)
set(CONSOLE_BINARIES offscreen)

set_target_properties(${WINDOWS_BINARIES} ${CONSOLE_BINARIES} PROPERTIES
                      FOLDER "GLFW3/Examples")

if (MSVC)
    # Tell MSVC to use main instead of WinMain for Windows subsystem executables
    set_target_properties(${WINDOWS_BINARIES} PROPERTIES
                          LINK_FLAGS "/ENTRY:mainCRTStartup")
endif()

if (APPLE)
    set_target_properties(boing PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "Boing")
    set_target_properties(gears PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "Gears")
    set_target_properties(heightmap PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "Heightmap")
    set_target_properties(particles PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "Particles")
    set_target_properties(sharing PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "Sharing")
    set_target_properties(simple PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "Simple")
    set_target_properties(splitview PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "SplitView")
    set_target_properties(wave PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "Wave")
    set_target_properties(myWindow PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "MyWindow")
    set_target_properties(myTrangle PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "MyTrangle")
    set_target_properties(myColoredTrangle PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "MyColoredTrangle" RESOURCE "${RESOURCE_FILES}")
    set_target_properties(myTextureWithbox PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "MyColoredTrangle" RESOURCE "${RESOURCE_FILES}")

    set_target_properties(${WINDOWS_BINARIES} PROPERTIES
#                          RESOURCE ${RESOURCE_FILES}
                          MACOSX_BUNDLE_SHORT_VERSION_STRING ${GLFW_VERSION}
                          MACOSX_BUNDLE_LONG_VERSION_STRING ${GLFW_VERSION_FULL}
                          MACOSX_BUNDLE_ICON_FILE glfw.icns
                          MACOSX_BUNDLE_INFO_PLIST "${GLFW_SOURCE_DIR}/CMake/MacOSXBundleInfo.plist.in")
endif()

