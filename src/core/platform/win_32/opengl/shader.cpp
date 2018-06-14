#include <stdio.h>
#include "shader.h"
#include "opengl.h"

namespace core {

void *_file_contents( const char *filename, GLint *length )
{
    FILE *f = fopen(filename, "r");
    void *buffer;

    if ( !f ) {
        fprintf(stderr, "Unable to open %s for reading\n", filename);
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    *length = ftell(f);
    fseek(f, 0, SEEK_SET);

    buffer = malloc(*length + 1);
    *length = (GLint)fread(buffer, 1, *length, f);
    fclose(f);
    ((char*)buffer)[*length] = '\0';

    return buffer;
}

void load_shader_file( std::string file_name, shader_type_t type, unsigned int* id )
{
    GLint length;
    GLint shader_ok;
    GLchar *source = (GLchar *)_file_contents(file_name.c_str(), &length);

    if ( !source ) {
        return;
    }

    *id = glCreateShader((unsigned int)type);
    glShaderSource(*id, 1, (const GLchar**)&source, &length);
    free(source);
    glCompileShader(*id);

    glGetShaderiv(*id, GL_COMPILE_STATUS, &shader_ok);
    if ( !shader_ok ) {
        LOG_ERROR("Error loading shader");
        //show_info_log(*shader, uh_glGetShaderiv, uh_glGetShaderInfoLog);
        glDeleteShader(*id);
        return;
    }
}

void create_shader_program( unsigned int vertex_id, unsigned int fragment_id, unsigned int* program_id )
{
    GLint program_ok;

    *program_id = glCreateProgram();

    glAttachShader(*program_id, vertex_id);
    glAttachShader(*program_id, fragment_id);
    glLinkProgram(*program_id);

    glGetProgramiv(*program_id, GL_LINK_STATUS, &program_ok);
    if ( !program_ok ) {
        LOG_ERROR("Error creating program");
        glDeleteProgram(*program_id);
        return;
    }
}

Shader::Shader( std::string vert_file, std::string frag_file )
{
    load_shader(vert_file, VERTEX_SHADER);
    load_shader(frag_file, FRAGMENT_SHADER);
    create_program(false);
}

Shader::Shader( std::string vert_file, std::string frag_file, std::string geom_file )
{
    load_shader(vert_file, VERTEX_SHADER);
    load_shader(frag_file, FRAGMENT_SHADER);
    load_shader(geom_file, GEOMETRY_SHADER);
    create_program(true);
}

void Shader::load_shader( std::string file_name, shader_type_t type )
{
    GLint length;
    GLint shader_ok;
    GLchar *source = (GLchar *)_file_contents(file_name.c_str(), &length);

    if ( !source ) {
        return;
    }

    unsigned int* shader;
    if ( type == VERTEX_SHADER ) {
        shader = &vert_id;
    } else if ( type == FRAGMENT_SHADER ){
        shader = &frag_id;
    } else {
        shader = &geom_id;
    }

    *shader = glCreateShader((unsigned int)type);
    glShaderSource(*shader, 1, (const GLchar**)&source, &length);
    free(source);
    glCompileShader(*shader);

    glGetShaderiv(*shader, GL_COMPILE_STATUS, &shader_ok);
    if ( !shader_ok ) {
        LOG_ERROR("Error loading shader");
        //show_info_log(*shader, uh_glGetShaderiv, uh_glGetShaderInfoLog);
        glDeleteShader(*shader);
        return;
    }
}

void Shader::create_program(bool has_geom)
{
    GLint program_ok;

    unsigned int* program = &prog_id;

    *program = glCreateProgram();

    glAttachShader(*program, vert_id);
    glAttachShader(*program, frag_id);
    if ( has_geom ) {
        glAttachShader(*program, geom_id);
    }
    glLinkProgram(*program);

    glGetProgramiv(*program, GL_LINK_STATUS, &program_ok);
    if ( !program_ok ) {
        LOG_ERROR("Error creating program");
        glDeleteProgram(*program);
        return;
    }
}

} //end namespace core
