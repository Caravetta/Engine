#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
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
     std::vector<std::string> include_files;

     if ( argc == 1 ) {
          print_help();
          return -1;
     }

     int opt = 0;
     while ( (opt = getopt(argc, argv, "i:o:")) != -1 ) {
          switch (opt) {
          case 'i': {
               include_files.push_back(optarg);
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

     Introspection intro;

     for ( size_t ii = 0; ii < include_files.size(); ii++ ) {
          printf("%s\n", include_files[ii].c_str());
          std::ifstream t(include_files[ii]);
          std::stringstream buffer;
          buffer << t.rdbuf();
          Lexer lexer(buffer.str());
          intro.parse(lexer);
     }

     intro.generate();

     return 0;
}
