#include "Utils.h"

#include <fstream>

namespace utils
{

std::string getFileContent( std::filesystem::path path )
{
	if ( !std::filesystem::exists( path ) )
		throw std::runtime_error( "Invalid path: " + path.string() );

	std::ifstream ifs( path.string() );
	std::string content( ( std::istreambuf_iterator<char>( ifs ) ),
						 ( std::istreambuf_iterator<char>() ) );
	ifs.close();

	return content;
}

} // namespace utils
