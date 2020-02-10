#ifndef __INTROSPECTION_H__
#define __INTROSPECTION_H__

#include <unordered_map>
#include "Lexer.h"

enum Meta_Class_Type {
     META_CLASS_TYPE_UNKNOWN,
     META_CLASS_TYPE_OBJECT,
     META_CLASS_TYPE_APPLICATION,
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

class Class {
public:
     Class( void );
     Class( std::string& name );
     ~Class( void );

     std::string& name( void );

private:
     std::string __name;
};

class Introspection
{
public:
     Introspection( void );
     ~Introspection( void );

     void parse( Lexer& lexer );

private:
     void parse_class( Lexer& lexer );
     const Class* add_class( std::string& class_name );
     void remove_class( const std::string& class_name );

     std::unordered_map< std::string, Class > __classes;
};

#endif //__INTROSPECTION_H__

