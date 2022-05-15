
add_library(
	shaders
	
	include/MainShader.h
	
	source/MainShader.cpp
)

target_link_libraries(
	shaders PRIVATE
	gl-env
)