#pragma once

#include "Glfw.h"

#include <string>

class Gl final
{
public:
	Gl() = delete;

	enum class Shader
	{
		Fragment = GL_FRAGMENT_SHADER,
		Vertex = GL_VERTEX_SHADER
	};

	enum class Parameter
	{
		ShaderType = GL_SHADER_TYPE,
		DeleteStatus = GL_DELETE_STATUS,
		CompileStatus = GL_COMPILE_STATUS,
		InfoLogLength = GL_INFO_LOG_LENGTH,
		ShaderSourceLength = GL_SHADER_SOURCE_LENGTH
	};

	static void gladInitialization();
	static GLFWwindow* createWindow( unsigned short width, unsigned short height, const std::string& title );

	static GLuint createShader( Shader type ) noexcept;
	static void shaderSource( GLuint shader, GLsizei count, const std::string& string );
	static void compileShader( GLuint shader );
	static GLint getShaderiv( GLuint shader, Parameter parameter ) noexcept;
	static std::string getShaderInfoLog( GLuint shader ) noexcept;

	class Vbo final
	{
	public:

		enum class Target
		{
			Array = GL_ARRAY_BUFFER,
			AtomicCounter = GL_ATOMIC_COUNTER_BUFFER,
			CopyRead = GL_COPY_READ_BUFFER,
			CopyWrite = GL_COPY_WRITE_BUFFER,
			DispatchIndirect = GL_DISPATCH_INDIRECT_BUFFER,
			DrawIndirect = GL_DRAW_INDIRECT_BUFFER,
			ElementArray = GL_ELEMENT_ARRAY_BUFFER,
			PixelPack = GL_PIXEL_PACK_BUFFER,
			PixelUnpack = GL_PIXEL_UNPACK_BUFFER,
			Query = GL_QUERY_BUFFER,
			ShaderStorage = GL_SHADER_STORAGE_BUFFER,
			Texture = GL_TEXTURE_BUFFER,
			TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER,
			Uniform = GL_UNIFORM_BUFFER
		};

	public:
		static GLuint genBuffer() noexcept;
		static void bindBuffer( Target target, GLuint buffer ) noexcept;

	private:
		static struct BoundBuffer final
		{
			GLuint arrayBuffer = 0;
			GLuint atomicCounterBuffer = 0;
			GLuint copyReadBuffer = 0;
			GLuint copyWriteBuffer = 0;
			GLuint dispatchIndirectBuffer = 0;
			GLuint drawIndirectBuffer = 0;
			GLuint elementArrayBuffer = 0;
			GLuint pixelPackBuffer = 0;
			GLuint pixelUnpackBuffer = 0;
			GLuint queryBuffer = 0;
			GLuint shaderStorageBuffer = 0;
			GLuint textureBuffer = 0;
			GLuint transformFeedbackBuffer = 0;
			GLuint uniformBuffer = 0;
		} bound_;
	};
};