
#include <iostream>
#include <sstream>

namespace Engine {

template<class T>
inline Rc_t Meta_Base::set_property( const std::string& key, const T& value ) const
{
     Rc_t rc = SUCCESS;
     std::ostringstream stream;

     stream << value;

     if ( !stream.fail() ) {
          set_property<std::string>(key, stream.str());
     } else {
          rc = OSTREAM_ERROR;
     }

     return rc;
}

template<>
inline Rc_t Meta_Base::set_property( const std::string& key, const std::string& value ) const
{
     __properties[key] = value;
     return SUCCESS;
}

template<class T>
inline Rc_t Meta_Base::get_property( const std::string& key, T& value ) const
{
     std::string tmp_string;

     Rc_t rc = get_property<std::string>(key, tmp_string);
     if ( rc == SUCCESS ) {
          std::istringstream string_stream(tmp_string);
          string_stream >> value;
          if ( string_stream.fail() ) {
               rc = OSTREAM_ERROR;
          }
     }

     return rc;
}

template<>
inline Rc_t Meta_Base::get_property( const std::string& key, std::string& value ) const
{
     Rc_t rc = SUCCESS;

     std::map< std::string, std::string >::const_iterator iter = __properties.find( key );
     if ( iter != __properties.end() ) {
          value = iter->second;
     } else {
          rc = INVALID_META_PROPERTY;
     }

     return rc;
}

inline std::string Meta_Base::get_property( const std::string& key ) const
{
     std::map< std::string, std::string >::const_iterator iter = __properties.find( key );
     if ( iter != __properties.end() ) {
          return iter->second;
     }

     return std::string();
}

} // end namespace Engine

