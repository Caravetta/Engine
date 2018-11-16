#include "gui_manager.h"

namespace core {
namespace Gui {

typedef struct {
    std::vector<float> data;
    std::vector<float> text_data;
    unsigned int shader_program;
    vao_t vao;
} gui_render_data_t;

typedef struct {
    std::string title;
    bool        active;
    Vector3f    position;
    uint32_t    width;
    uint32_t    height;
    bool        min;
} frame_t;

typedef struct {
    std::vector<frame_t>    frames;
    frame_t*                current_frame = NULL;
    uint64_t                active_id;
    Font*                   font;
    uint16_t                font_size;
    gui_render_data_t       render_data;
} gui_context_t;

typedef struct {
    Vector3f text_color;

    Vector3f frame_background;
    Vector3f frame_title_bar;

    Vector3f button_non_hover;
    Vector3f button_hovered;
    Vector3f button_clicked;
} gui_color_settings_t;

gui_context_t gui_context;

void _generate_rec( Vector3f position, Vector3f color, uint32_t width, uint32_t height, std::vector<float>* data );
void _generate_text( Vector3f position, Vector3f color, core::Font* font, uint16_t font_size, std::vector<float>* text_data );

void init( std::string vert_path, std::string frag_path )
{
    unsigned int fragment_id;
    unsigned int vertex_id;

    load_shader_file(frag_path, core::FRAGMENT_SHADER, &fragment_id);
    load_shader_file(vert_path, core::VERTEX_SHADER, &vertex_id);

    create_shader_program(vertex_id, fragment_id, &gui_context.render_data.shader_program);

    create_vao(&gui_context.render_data.vao);

    //Pos
    create_float_attribute(&gui_context.render_data.vao, 0, gui_context.render_data.data.data(), (int)gui_context.render_data.data.size() * sizeof(float),
                           3, 6 * sizeof(float), 0, DYNAMIC_DRAW);
    //Color
    create_float_attribute(&gui_context.render_data.vao, 1, gui_context.render_data.data.data(), (int)gui_context.render_data.data.size() * sizeof(float),
                           3, 6 * sizeof(float), 3 * sizeof(float), DYNAMIC_DRAW);

}

void render()
{

}

void start_frame( std::string title, bool active, Vector3f position )
{
    gui_context.frames.push_back(frame_t());
    gui_context.current_frame = &gui_context.frames[gui_context.frames.size() - 1];

    gui_context.current_frame->title = title; //TODO(JOSH): I do not think we need to save this
    gui_context.current_frame->active = active;
    gui_context.current_frame->position = position; //position is top left
    gui_context.current_frame->min = false;

    if ( !active ) {
        // nothing to do just return
        return;
    }

    //generate the frame header
    uint16_t header_height = gui_context.font_size + 10;
    uint16_t header_width = 30;

    Vector3f header_text_pos(position.vec.x + 2, position.vec.y - gui_context.font_size + 5, 0);
    Vector3f header_rec_pos(position.vec.x, position.vec.y - header_height, 0);

    _generate_text(header_text_pos, Vector3f(3, 3, 2), gui_context.font,
                   gui_context.font_size, &gui_context.render_data.text_data);

    _generate_rec(header_rec_pos, Vector3f(3, 3, 2), header_width,
                  header_height, &gui_context.render_data.data);
}

void end_frame()
{
    //generate the frame box;
    if ( gui_context.current_frame->height != 0 ) {
        _generate_rec(gui_context.current_frame->position, Vector3f(3, 3, 2),
                      gui_context.current_frame->width, gui_context.current_frame->height, &gui_context.render_data.data);
    }
    gui_context.current_frame = NULL;

    return;
}

CORE_API bool button( std::string text )
{
    bool return_val = false;

    CHECK_INFO(gui_context.current_frame != NULL, "This Button is not part of a Frame");

    if ( gui_context.current_frame->active ) {
        //check to see if the mouse is over the box
        if ( false ) {
            //check to see if the mouse is clicked
            return_val = false ? true : false;
        }

        //generate the render values
    }

    return return_val;
}

//data layout 3 vec floats 3 color floats
void _generate_rec( Vector3f position, Vector3f color, uint32_t width, uint32_t height, std::vector<float>* data )
{
    data->push_back(position.vec.x); data->push_back(position.vec.y); data->push_back(0);
    data->push_back(color.vec.x); data->push_back(color.vec.y); data->push_back(color.vec.z);

    data->push_back(position.vec.x); data->push_back(position.vec.y + height); data->push_back(0);
    data->push_back(color.vec.x); data->push_back(color.vec.y); data->push_back(color.vec.z);

    data->push_back(position.vec.x + width); data->push_back(position.vec.y + height); data->push_back(0);
    data->push_back(color.vec.x); data->push_back(color.vec.y); data->push_back(color.vec.z);

    data->push_back(position.vec.x); data->push_back(position.vec.y); data->push_back(0);
    data->push_back(color.vec.x); data->push_back(color.vec.y); data->push_back(color.vec.z);

    data->push_back(position.vec.x + width); data->push_back(position.vec.y + height); data->push_back(0);
    data->push_back(color.vec.x); data->push_back(color.vec.y); data->push_back(color.vec.z);

    data->push_back(position.vec.x + width); data->push_back(position.vec.y); data->push_back(0);
    data->push_back(color.vec.x); data->push_back(color.vec.y); data->push_back(color.vec.z);

    return;
}

void _generate_text( Vector3f position, Vector3f color, core::Font* font, uint16_t font_size, std::vector<float>* text_data )
{

}

} // end namespace Gui
} // end namespace core
