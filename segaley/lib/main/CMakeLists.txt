
add_executable(
	segaley
	
	${GLAD_PATH}/glad.c
	source/main.cpp
	include/Program.h
	source/Program.cpp
)

target_link_libraries(
	segaley PRIVATE
	${GLFW_PATH}/lib/glfw3.lib
	${GLFW_PATH}/lib/glfw3dll.lib
	gl-env
	misc
)
