
add_library(
	input-devices
	
	include/Keyboard.h

	source/Keyboard.cpp
)

target_include_directories(
	input-devices PUBLIC
		include/
)