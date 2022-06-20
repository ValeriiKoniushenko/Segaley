#include "DebugActions.h"

#include <filesystem>

void DebugActions::copyAssets()
{
	namespace fs = std::filesystem;

	if ( !fs::exists( ASSETS_SRC_PATH ) )
		throw std::runtime_error( "Can not find a folder with assets to copy it to the binary directory." );

    if ( fs::exists( ASSETS_DIR_NAME ) )
        fs::remove_all( ASSETS_DIR_NAME );

    fs::copy( ASSETS_SRC_PATH, ASSETS_DIR_NAME,
              fs::copy_options::overwrite_existing | fs::copy_options::recursive );
}
