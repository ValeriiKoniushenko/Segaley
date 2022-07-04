cmake_minimum_required( VERSION 3.0 )

project( Segaley VERSION 2.0 )

set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED true )

set( DEPENDENCIES_DIR_NAME dependencies )
set( DEPENDENCIES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${DEPENDENCIES_DIR_NAME} )

set( GLAD_PATH "${DEPENDENCIES_PATH}/GLAD" )
set( GLEW_PATH "${DEPENDENCIES_PATH}/GLEW" )
set( GLM_PATH "${DEPENDENCIES_PATH}/GLM" )
set( MISC_PATH "${DEPENDENCIES_PATH}/misc" )
set( FREETYPE_PATH "${DEPENDENCIES_PATH}/freetype-2.11.1" )
set( BOOST_PATH "C:/boost_1_79_0" )

set( ASSETS_DIR_NAME "assets" )
set( ASSETS_SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/${ASSETS_DIR_NAME}" )
set( CONFIGS_DIR_NAME "configs" )
set( CONFIGS_SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/${CONFIGS_DIR_NAME}" )

add_compile_definitions( ASSETS_SRC_PATH="${ASSETS_SRC_PATH}" )
add_compile_definitions( ASSETS_DIR_NAME="${ASSETS_DIR_NAME}" )
add_compile_definitions( CONFIGS_DIR_NAME="${CONFIGS_DIR_NAME}" )
add_compile_definitions( CONFIGS_SRC_PATH="${CONFIGS_SRC_PATH}" )
add_compile_definitions( DEFAULT_FONT="C:/Windows/Fonts/arial.ttf" )
add_compile_definitions( DEBUG_LVL )

include_directories(
	${GLAD_PATH}
	${GLEW_PATH}/include
	${GLM_PATH}
	${MISC_PATH}
	${DEPENDS_PATH}
	${FREETYPE_PATH}/include
	${BOOST_PATH}
)

add_subdirectory( segaley/lib/camera )
add_subdirectory( segaley/lib/font )
add_subdirectory( segaley/lib/gl-env )
add_subdirectory( segaley/lib/gui )
add_subdirectory( segaley/lib/input-devices )
add_subdirectory( segaley/lib/main )
add_subdirectory( segaley/lib/misc )
add_subdirectory( segaley/lib/shaders )
add_subdirectory( dependencies/freetype-2.10.0 )
add_subdirectory( dependencies/glfw-3.3.7 )