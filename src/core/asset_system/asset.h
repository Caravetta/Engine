#ifndef __ASSET_H__
#define __ASSET_H__

#include <string>
#include "../core_common.h"
#include "../handle_system/handle.h"

namespace core {

typedef base_handle_t Asset_Handle;

struct CORE_API Asset {
protected:
    std::string name;
    Asset_Handle handle;
    uint64_t ref_count;
public:
    Asset(){};
    virtual void load( std::string file_path ) = 0;
};

} // end namespace core

#endif //__ASSET_H__
