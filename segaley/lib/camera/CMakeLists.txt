
add_library(
	camera
	
	include/Camera.h
	include/Camera2D.h
	include/Camera3D.h
	
	source/Camera2D.cpp
	source/Camera3D.cpp
)

target_link_libraries(
	camera PUBLIC
		input-devices
		gl-env
)

target_include_directories(
	camera PUBLIC
		include/
)