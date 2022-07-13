
add_library(
	gui
	
	include/Frame.h
	include/TextLine.h

	source/Frame.cpp
	source/TextLine.cpp
)

target_link_libraries(
	gui PUBLIC
		font
		misc
		gl-env
		shaders
)

target_include_directories(
	gui PUBLIC
		include/
)