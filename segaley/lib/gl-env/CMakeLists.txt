
add_library(
	gl-env
	
	include/Gl.h
	include/Glfw.h
	include/Image.h
	include/Shader.h
	include/ShaderProgram.h
	include/Sprite.h
	include/Texture2D.h
	include/Vao.h
	include/Vbo.h
	include/Window.h

	source/Gl.cpp
	source/Glfw.cpp
	source/Image.cpp
	source/Shader.cpp
	source/ShaderProgram.cpp
	source/Sprite.cpp
	source/Texture2D.cpp
	source/Vao.cpp
	source/Vbo.cpp
	source/Window.cpp
)

target_link_libraries(
	gl-env PUBLIC
		misc
		glfw
		camera
)

target_include_directories(
	gl-env PUBLIC
		include/
)