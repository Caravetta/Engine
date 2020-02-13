#include <inttypes.h>
#include "introspection.h"

#define CLASS_IDENTIFIER "ENGINE_CLASS"
#define CLASS_BODY_IDENTIFIER "ENGINE_CLASS_BODY"
#define COMPONENT_IDENTIFIER "ENGINE_COMPONENT"
#define STRUCT_IDENTIFIER "ENGINE_STRUCT"
#define PROPERTY_IDENTIFIER "ENGINE_PROPERTY"
#define FUNCTION_IDENTIFIER "ENGINE_FUNCTION"

Class::Class( void )
{
     // do nothing
}

Class::Class( const std::string& name )
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

void Class::set_class_traits( Class_Traits& traits )
{
     __class_traits = traits;
}

Class_Traits& Class::class_traits( void )
{
     return __class_traits;
}

void Class::add_property( Property& property )
{
     __properties.push_back(property);
}

Introspection::Introspection( void )
{
     __starting_comp_id = 1;
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
          default: { /* do nothing */ } break;
          }
     }
}

void Introspection::generate( void )
{
     size_t n_classes = __classes.size();
     printf("Num Classes %zu\n", n_classes);

     Class* cur_class = nullptr;
     FILE* comp_file = nullptr;

     comp_file = fopen("comp_test.h", "w");

     if ( comp_file == nullptr ) {
          printf("Error failed to creatre component file");
          return;
     }

     fprintf(comp_file, "/* Generated File Do Not Modify */\n\n#ifndef __GEN_COMP_H__\n#define __GEN_COMP_H__\n\n#include <inttypes.h>\n\nnamespace __COMP_GEN_ {\n\n");

     for ( auto &element : __classes ) {
          cur_class = &element.second;
          Meta_Class_Type type = cur_class->class_traits().type;

          switch ( type ) {
          case META_CLASS_TYPE_COMPONENT: {
               generate_component(comp_file, cur_class);
          } break;
          case META_CLASS_TYPE_OBJECT: {

          } break;
          default: {
               printf("Error unknown class type\n");
          } break;
          }
     }

     fprintf(comp_file, "\n}\n\n#endif //__GEN_COMP_H__\n");
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
     Class* p_class = add_class(token.data());

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

     parse_body(lexer, p_class);
}

void Introspection::parse_body( Lexer& lexer, Class* cur_class )
{
     Class_Traits class_traits;

     if ( lexer.current_token().equals(CLASS_BODY_IDENTIFIER) ) {
          class_traits.type = META_CLASS_TYPE_OBJECT;
     } else if ( lexer.current_token().equals(COMPONENT_IDENTIFIER) ) {
          class_traits.type = META_CLASS_TYPE_COMPONENT;
     } else {
          class_traits.type = META_CLASS_TYPE_UNKNOWN;
     }

     if ( !lexer.require_token(TOKEN_TYPE_OPEN_PAREN, true) ) {
          printf("Error no openning paren\n");
          remove_class(cur_class->name());
          return;
     }

     switch (class_traits.type) {
     case META_CLASS_TYPE_OBJECT: {
          if ( !lexer.continue_to(TOKEN_TYPE_CLOSE_PAREN) ) {
               printf("Error no closing paren");
               remove_class(cur_class->name());
               return;
          }
     } break;
     case META_CLASS_TYPE_COMPONENT: {
          if ( !lexer.continue_to(TOKEN_TYPE_CLOSE_PAREN) ) {
               printf("Error no closing paren");
               remove_class(cur_class->name());
               return;
          }
     } break;
     default: {
          printf("Error unknown class type\n");
     } break;
     }

     cur_class->set_class_traits(class_traits);

     parse_members(lexer, cur_class);
}

void Introspection::parse_members( Lexer& lexer, Class* cur_class )
{
     bool continue_parsing = true;

     while ( continue_parsing ) {
          Token token = lexer.next_token(true);

          switch (token.type()) {
          case TOKEN_TYPE_IDENTIFIER: {
               if ( token.equals(PROPERTY_IDENTIFIER) ) {
                    parse_property(lexer, cur_class);
               } else if ( token.equals(FUNCTION_IDENTIFIER) ) {

               }
          } break;
          case TOKEN_TYPE_CLOSE_BRACE: {
               if ( lexer.peek_at_next_token().is_type(TOKEN_TYPE_SEMI_COLON) ) {
                    continue_parsing = false;
               }
          } break;
          case TOKEN_TYPE_END_OF_STREAM: {
               continue_parsing = false;
          } break;
          default: { /* do nothing */ } break;
          }
     }
}

void Introspection::parse_property( Lexer& lexer, Class* cur_class )
{
     if ( !lexer.require_token(TOKEN_TYPE_OPEN_PAREN, true) ) {
          return;
     }

     Token token = lexer.current_token();

     while ( !token.is_type(TOKEN_TYPE_CLOSE_PAREN) && !token.is_type(TOKEN_TYPE_END_OF_STREAM) ) {
          token = lexer.next_token(true);
     }

     if ( lexer.peek_at_next_token().equals("const") ) {
          token = lexer.next_token(true);
     }

     if ( !lexer.require_token(TOKEN_TYPE_IDENTIFIER, true) ) {
          printf("Error did not find identifier");
          return;
     }

     lexer.consume_all_namespace_qualifiers();

     if ( !lexer.require_token(TOKEN_TYPE_IDENTIFIER, false) ) {
          printf("Error did not find identifier");
          return;
     }

     Token token_type = lexer.current_token();
     printf("%s\n", token_type.to_string().c_str());

     Token token_name = lexer.next_token(true);

     uint8_t num_pointers = 0;

     while ( !token_name.is_type(TOKEN_TYPE_IDENTIFIER) && !token_name.is_type(TOKEN_TYPE_END_OF_STREAM) ) {

          if ( token_name.is_type(TOKEN_TYPE_ASTERISK) ) {
               num_pointers += 1;
          }

          token_name = lexer.next_token(true);
     }

     Property property;

     property.name = token_name.data();
     property.flags_mask = PROPERTY_FLAGS_NONE;

     switch( num_pointers ) {
     case 0: { /* do nothing */ } break;
     case 1: {
          property.flags_mask |= PROPERTY_FLAGS_IS_POINTER;
     } break;
     case 2: {
          property.flags_mask |= PROPERTY_FLAGS_IS_DOUBLE_POINTER;
     } break;
     default: {
          printf("Error only up to double pointer supported\n");
          return;
     } break;
     }

     printf("%s\n", token_name.to_string().c_str());

     cur_class->add_property(property);
}

Class* Introspection::add_class( const std::string& class_name )
{
     __classes[class_name] = Class(class_name);

     return &__classes[class_name];
}

bool Introspection::class_exists( const std::string& class_name )
{
     return (__classes.find(class_name) != __classes.end());
}

void Introspection::remove_class( const std::string& class_name )
{
     __classes.erase(class_name);
}

void Introspection::generate_component( FILE* fp, Class* cur_class )
{
     //
     fprintf(fp, "struct %s {\n\tconst uint32_t id = %" PRIu32 ";\nconst size_t size = sizeof(::%s);\n};\n",
             cur_class->name().c_str(),
             __starting_comp_id,
             cur_class->name().c_str());

     __starting_comp_id += 1;
}

