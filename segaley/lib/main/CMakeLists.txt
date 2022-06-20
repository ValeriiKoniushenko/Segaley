
add_executable(
	segaley
	
	${GLAD_PATH}/glad.c
	source/main.cpp
	include/Program.h
	source/Program.cpp
)

target_link_libraries(
	segaley PRIVATE
	camera
	gl-env
	gui
	input-devices
	misc
	shaders
	font
)

target_include_directories(
	segaley PUBLIC
		include/
)