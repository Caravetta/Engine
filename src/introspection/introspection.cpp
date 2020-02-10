#include "introspection.h"

#define CLASS_IDENTIFIER "ENGINE_CLASS"
#define CLASS_BODY_IDENTIFIER "ENGINE_CLASS_BODY"
#define COMPONENT_IDENTIFIER "ENGINE_COMPONENT"
#define STRUCT_IDENTIFIER "ENGINE_STRUCT"

Class::Class( void )
{
     // do nothing
}

Class::Class( std::string& name )
{
     __name = name;
}

Class::~Class( void )
{
     // do nothing
}

std::string& Class::name( void )
{
     return __name;
}

Introspection::Introspection( void )
{

}

Introspection::~Introspection( void )
{

}

void Introspection::parse( Lexer& lexer )
{
     bool continue_parsing = true;

     while ( continue_parsing ) {
          Token token = lexer.next_token(true);

          switch ( token.type() ) {
          case TOKEN_TYPE_HASH: { /* do nothing */ } break;
          case TOKEN_TYPE_OPEN_BRACE: { } break;
          case TOKEN_TYPE_CLOSE_BRACE: { } break;
          case TOKEN_TYPE_IDENTIFIER: {
               if ( token.equals(CLASS_IDENTIFIER) || token.equals(STRUCT_IDENTIFIER) ) {
                    parse_class(lexer);
               }
          } break;
          case TOKEN_TYPE_END_OF_STREAM: { continue_parsing = false; } break;
          }
     }
}

void Introspection::parse_class( Lexer& lexer )
{
     bool is_class = true;

     if ( lexer.current_token().equals(STRUCT_IDENTIFIER) ) {
          is_class = false;
     }

     if ( !lexer.require_token(TOKEN_TYPE_OPEN_PAREN, true) ) {
          printf("Error no opening paren\n");
          return;
     }

     if ( !lexer.require_token(TOKEN_TYPE_CLOSE_PAREN, true) ) {
          printf("Error no closing paren\n");
          return;
     }
#if 0
     if ( !lexer.require_token(TOKEN_TYPE_IDENTIFIER, true) ) {
          printf("Error no identifier\n");
          return;
     }
#endif
     Token token = lexer.next_token(true);

     if ( is_class ) {
          if ( !lexer.current_token().equals("class") ) {
               printf("Error not class token\n");
               return;
          }
     } else {
          if ( !lexer.current_token().equals("struct") ) {
               printf("Error not struct token\n");
               return;
          }
     }

     if ( !lexer.require_token(TOKEN_TYPE_IDENTIFIER, true) ) {
          printf("Error no identifier\n");
          return;
     }

     token = lexer.current_token();
     Class* p_class = const_cast< Class* >(add_class(token.data()));

     if ( !lexer.continue_to(TOKEN_TYPE_OPEN_BRACE) ) {
          printf("Error no openning brace for class %s", p_class->name().c_str() );
          remove_class(p_class->name());
          return;
     }

     std::vector<std::string> identifiers{ CLASS_BODY_IDENTIFIER,
                                           COMPONENT_IDENTIFIER };

     if ( !lexer.continue_to_any_identifier(identifiers) ) {
          printf("Error did not find ENGINE_CLASS_BODY or ENGINE_CLASS_BODY");
          remove_class(p_class->name());
          return;
     }
}

const Class* Introspection::add_class( std::string& class_name )
{
     __classes[class_name] = Class(class_name);

     return &__classes[class_name];
}

void Introspection::remove_class( const std::string& class_name )
{
     __classes.erase(class_name);
}

