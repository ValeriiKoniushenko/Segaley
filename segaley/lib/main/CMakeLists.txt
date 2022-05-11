
add_executable(
	segaley
	${GLAD_PATH}/glad.c
	source/Color.cpp
	source/Gl.cpp
	source/Glfw.cpp
	source/main.cpp
	source/Window.cpp
	source/WindowSize.cpp
	include/Color.h
	include/Gl.h
	include/Glfw.h
	include/Rect.h
	include/Window.h
	include/WindowSize.h
	include/DebugActions.h
	source/DebugActions.cpp
	include/Utils.h
	source/Utils.cpp
	include/Image.h
	source/Image.cpp
)

target_link_libraries(
	segaley PRIVATE
	${GLFW_PATH}/lib/glfw3.lib
	${GLFW_PATH}/lib/glfw3dll.lib
)
