
add_library(
	gui
	
	include/Frame.h	
	include/Rectangle.h

	source/Rectangle.cpp
	source/Frame.cpp
)

target_link_libraries(
	gui PUBLIC
		misc
		gl-env
		shaders
)

target_include_directories(
	gui PUBLIC
		include/
)