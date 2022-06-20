
add_library(
	misc
	
	include/Color.h
	include/DebugActions.h
	include/Rect.h
	include/Repeater.h
	include/Utils.h
	include/WindowSize.h
	
	source/Color.cpp
	source/DebugActions.cpp
	source/Repeater.cpp
	source/Utils.cpp
	source/WindowSize.cpp
)

target_include_directories(
	misc PUBLIC
		include/
)