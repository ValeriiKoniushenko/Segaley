#pragma once

#include "Glfw.h"

#include <string>
#include <vector>

class Gl final
{
public:
	Gl() = delete;


	enum class DataType
	{
		None,
		Byte = GL_BYTE,
		UnsignedByte = GL_UNSIGNED_BYTE,
		Short = GL_SHORT,
		UnsignedShort = GL_UNSIGNED_SHORT,
		Int = GL_INT,
		UnsignedInt = GL_UNSIGNED_INT,
		Float = GL_FLOAT,
		FloatVec2 = GL_FLOAT_VEC2,
		FloatVec3 = GL_FLOAT_VEC3,
		FloatVec4 = GL_FLOAT_VEC4,
		IntVec2 = GL_INT_VEC2,
		IntVec3 = GL_INT_VEC3,
		IntVec4 = GL_INT_VEC4,
		Bool = GL_BOOL,
		BoolVec2 = GL_BOOL_VEC2,
		BoolVec3 = GL_BOOL_VEC3,
		BoolVec4 = GL_BOOL_VEC4,
		FloatMat2 = GL_FLOAT_MAT2,
		FloatMat3 = GL_FLOAT_MAT3,
		FloatMat4 = GL_FLOAT_MAT4,
		Sampler1d = GL_SAMPLER_1D,
		Sampler2d = GL_SAMPLER_2D,
		Sampler3d = GL_SAMPLER_3D,
		SamplerCube = GL_SAMPLER_CUBE,
		Sampler1d_shadow = GL_SAMPLER_1D_SHADOW,
		Sampler2d_shadow = GL_SAMPLER_2D_SHADOW
	};

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
		ShaderSourceLength = GL_SHADER_SOURCE_LENGTH,
		LinkStatus = GL_LINK_STATUS,
		ValidateStatus = GL_VALIDATE_STATUS,
		AttachedShaders = GL_ATTACHED_SHADERS,
		ActiveAttributes = GL_ACTIVE_ATTRIBUTES,
		ActiveAttribute_max_length = GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
		ActiveUniforms = GL_ACTIVE_UNIFORMS
	};

	enum class DrawMode
	{
		Points = GL_POINTS,
		Lines = GL_LINES,
		LineLoop = GL_LINE_LOOP,
		LineStrip = GL_LINE_STRIP,
		Triangles = GL_TRIANGLES,
		TriangleStrip = GL_TRIANGLE_STRIP,
		TriangleFan = GL_TRIANGLE_FAN,
		Quads = GL_QUADS
	};

	struct Attribute
	{
		DataType type = DataType::None;
		std::string name;
		GLuint id = 0;
	};

	static void gladInitialization();
	static GLFWwindow* createWindow( unsigned short width, unsigned short height, const std::string& title );

	static GLuint createShader( Shader type ) noexcept;
	static void shaderSource( GLuint shader, GLsizei count, const std::string& string );
	static void compileShader( GLuint shader );
	static GLint getShaderiv( GLuint shader, Parameter parameter ) noexcept;
	static std::string getShaderInfoLog( GLuint shader ) noexcept;
	static void deleteShader( GLuint program, GLuint shader );
	static void detachShader( GLuint program, GLuint shader ) noexcept;
	static bool isAttachedShader( GLuint program, GLuint shader ) noexcept;

	static GLint getProgramiv( GLuint program, Parameter parameter ) noexcept;
	static std::string getProgramInfoLog( GLuint program ) noexcept;
	static GLuint createProgram() noexcept;
	static void attachShader( GLuint program, GLuint shader ) noexcept;
	static void linkProgram( GLuint program );
	static void deleteProgram( GLuint program ) noexcept;
	static std::vector< GLuint > getAttachedShaders( GLuint program ) noexcept;
	static std::vector< Attribute > getAtrributes( GLuint program ) noexcept;

	static void vertexAttribPointer( GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer );
	static void enableVertexAttribArray	( GLuint index ) noexcept;

	static void drawArrays( DrawMode mode, GLint first, GLsizei count );

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

		enum class DrawType
		{
			StreamDraw = GL_STREAM_DRAW,
			StreamRead = GL_STREAM_READ,
			StreamCopy = GL_STREAM_COPY,
			StaticDraw = GL_STATIC_DRAW,
			StaticRead = GL_STATIC_READ,
			StaticCopy = GL_STATIC_COPY,
			DynamicDraw = GL_DYNAMIC_DRAW,
			DynamicRead = GL_DYNAMIC_READ,
			DynamicCopy = GL_DYNAMIC_COPY
		};

	public:
		static GLuint generate() noexcept;
		static void bind( Target target, GLuint buffer ) noexcept;
		static void bufferData( Target target, GLsizeiptr size, const void* data, DrawType drawType );
		static void deleteBuffer( GLuint buffer ) noexcept;

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

			void setBuffer( Target target, GLuint buffer ) noexcept;
			bool isSetBuffer( Target target ) noexcept;
		} bound_;
	};

	class Vao final
	{
	public:
		static GLuint generate() noexcept;
		static void bind( GLuint vao ) noexcept;
		static bool isBind() noexcept;
		static void reset() noexcept;
		static void deleteBuffer( GLuint buffer ) noexcept;

	private:
		static GLuint boundVao_;
	};
};