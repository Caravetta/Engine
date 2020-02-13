#include <iostream>
#include <fstream>
#include <sstream>
#include "lexer.h"
#include "introspection.h"

int main( void )
{
     std::ifstream t("file.txt");
     std::stringstream buffer;
     buffer << t.rdbuf();

     Lexer lexer(buffer.str());
     Introspection intro;
     intro.parse(lexer);

     std::ifstream tt("file.txt");
     std::stringstream buffert;
     buffert << tt.rdbuf();

     Lexer lexert(buffert.str());

     while (1) {
          Token token = lexert.next_token(true);
          printf("%s\n", token.to_string().c_str());
          if ( token.type() == TOKEN_TYPE_END_OF_STREAM ) {
               break;
          }
     }

     intro.generate();

     return 0;
}
