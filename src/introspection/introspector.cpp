#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include "lexer.h"
#include "introspection.h"

char* optarg = NULL;
int optind = 1;

int getopt(int argc, char *const argv[], const char *optstring)
{
     if ( (optind >= argc) ||
          (argv[optind][0] != '-') ||
          (argv[optind][0] == 0) ) {
          return -1;
     }

     int opt = argv[optind][1];
     const char *p = strchr(optstring, opt);

     if ( p == NULL ) {
          return '?';
     }

     if ( p[1] == ':' ) {
          optind++;

          if ( optind >= argc ) {
              return '?';
          }

          optarg = argv[optind];
          optind++;
     }

     return opt;
}

static void print_help( void )
{
     printf("Usage:\n");
     printf("-i <include file path> : include file to parse\n");
     printf("-o <file path> : path to generate output file\n");
}

int main( int argc, char** argv )
{
     if ( argc == 1 ) {
          print_help();
          return -1;
     }

     int opt = 0;
     while ( (opt = getopt(argc, argv, "i:o:")) != -1 ) {
          switch (opt) {
          case 'i': {
               printf("got i %s\n", optarg);
          } break;
          case 'o': {
               printf("got o %s\n", optarg);
          } break;
          default: {
               print_help();
               return -1;
          } break;
          }
     }

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
#if 0
     while (1) {
          Token token = lexert.next_token(true);
          printf("%s\n", token.to_string().c_str());
          if ( token.type() == TOKEN_TYPE_END_OF_STREAM ) {
               break;
          }
     }
#endif
     intro.generate();

     return 0;
}
