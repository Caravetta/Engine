#ifndef __INTROSPECTION_H__
#define __INTROSPECTION_H__

#include <unordered_map>
#include "lexer.h"

enum Meta_Class_Type {
     META_CLASS_TYPE_UNKNOWN,
     META_CLASS_TYPE_OBJECT,
     META_CLASS_TYPE_COMPONENT,
};

enum Property_Type {
     PROPERTY_TYPE_UNKNOWN,
     PROPERTY_TYPE_OBJECT,
     PROPERTY_TYPE_BOOL,
     PROPERTY_TYPE_COLOR,
     PROPERTY_TYPE_FLOAT,
     PROPERTY_TYPE_UINT8,
     PROPERTY_TYPE_UINT16,
     PROPERTY_TYPE_UINT32,
     PROPERTY_TYPE_UINT64,
     PROPERTY_TYPE_INT8,
     PROPERTY_TYPE_INT16,
     PROPERTY_TYPE_INT32,
     PROPERTY_TYPE_INT64,
     PROPERTY_TYPE_STRING,
     PROPERTY_TYPE_ARRAY,
     PROPERTY_TYPE_VECTOR3F,
};

enum Property_Flags {
     PROPERTY_FLAGS_NONE = 0,
     PROPERTY_FLAGS_IS_POINTER = 1 << 0,
     PROPERTY_FLAGS_IS_DOUBLE_POINTER = 1 << 1,
};

struct Property {
     std::string name;
     Property_Type type;
     uint32_t flags_mask;
};

struct Class_Traits {
     Meta_Class_Type type;
};

class Class {
public:
     Class( void );
     Class( const std::string& name );
     ~Class( void );

     std::string& name( void );
     void set_class_traits( Class_Traits& traits );
     Class_Traits& class_traits( void );
     void add_property( Property& property );

private:
     std::string __name;
     Class_Traits __class_traits;
     std::vector<Property> __properties;
};

class Introspection
{
public:
     Introspection( void );
     ~Introspection( void );

     void parse( Lexer& lexer );
     void generate( void );

private:
     void parse_class( Lexer& lexer );
     void parse_body( Lexer& lexer, Class* cur_class );
     void parse_members( Lexer& lexer, Class* cur_class );
     void parse_property( Lexer& lexer, Class* cur_class );
     Class* add_class( const std::string& class_name );
     bool class_exists( const std::string& class_name );
     void remove_class( const std::string& class_name );
     void generate_component( FILE* fp, Class* cur_class );

     std::unordered_map< std::string, Class > __classes;
     uint32_t __starting_comp_id;
};

#endif //__INTROSPECTION_H__

