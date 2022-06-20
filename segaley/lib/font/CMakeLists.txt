
add_library(
	font

	include/Font.h
	include/Text.h
	include/TextField.h

	source/Font.cpp
	source/Text.cpp
	source/TextField.cpp
)

target_link_libraries(
	font PUBLIC
		freetype
		gl-env
)

target_include_directories(
	font PUBLIC
		include/
)