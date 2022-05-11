#include "DebugActions.h"

#include <filesystem>

void DebugActions::copyAssets()
{
	namespace fs = std::filesystem;

	if ( !fs::exists( ASSETS_SRC_PATH ) )
		throw std::runtime_error( "Can not find a folder with assets to copy it to the binary directory." );

	fs::create_directory( ASSETS_DIR_NAME );

	fs::copy( ASSETS_SRC_PATH, ASSETS_DIR_NAME,
			  fs::copy_options::update_existing | fs::copy_options::recursive );
}
