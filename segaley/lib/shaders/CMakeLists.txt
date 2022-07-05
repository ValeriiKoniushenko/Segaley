
add_library(
	shaders

		include/GuiShader.h
	include/MainShader.h

		source/GuiShader.cpp
	source/MainShader.cpp
)

target_link_libraries(
	shaders PUBLIC
		gl-env
)

target_include_directories(
	shaders PUBLIC
		include/
)