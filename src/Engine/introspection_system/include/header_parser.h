#ifndef __HEADER_PARSER_H__
#define __HEADER_PARSER_H__

#include <string>
#include <vector>
#include "core_common.h"
#include "Engine_Types.h"

namespace Engine {
namespace Introspection {

Rc_t parse_headers( std::vector<std::string>* file_paths );

} // end namespace Introspection
} // end namespace Engine

#endif //__HEADER_PARSER_H__
