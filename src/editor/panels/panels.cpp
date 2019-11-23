#include "panels.h"
#include "gui.h"

void _layout_resize_callback( int32_t width, int32_t height )
{
     Editor_Context& context = *Editor_Context::get_instance();

	float window_width = (float)width;
	float window_height = (float)height;

     context.window_width = window_width;
     context.window_height = window_height;

	context.panels.menu_bar.width = window_width + 2.0f;
     context.panels.menu_bar.height = 0.0f;
     context.panels.menu_bar.x_position = -1.0f;
     context.panels.menu_bar.y_position = 0.0f;

     context.panels.instector.width = window_width * 0.2f;
     context.panels.instector.height = window_height - 20.0f;
     context.panels.instector.x_position = context.window_width - context.panels.instector.width;
     context.panels.instector.y_position = 19.0f;

     context.panels.console.width = window_width - context.panels.instector.width;
     context.panels.console.height = window_height * 0.3;
     context.panels.console.x_position = 0.0f;
     context.panels.console.y_position = window_height - context.panels.console.height;

     context.panels.hierarchy.width = window_width * 0.15f;
     context.panels.hierarchy.height = window_height - 19.0f - context.panels.console.height;
     context.panels.hierarchy.x_position = 0.0f;
     context.panels.hierarchy.y_position = 19.0f;

     context.panels.scene.width = window_width - context.panels.instector.width - context.panels.hierarchy.width;
     context.panels.scene.height = window_height - 19 - context.panels.console.height;
     context.panels.scene.x_position = context.panels.hierarchy.width;
     context.panels.scene.y_position = 19.0f;
}

int init_panels( Editor_Context& context )
{

	context.window->add_resize_callback(_layout_resize_callback);

     init_inspector_panel();

	return 0;
}

int update_panels( Editor_Context& context )
{
     gui_start_frame();

	update_menu_bar_panel(context);
     update_console_panel(context);
     update_inspector_panel(context);
     update_hierarchy_panel(context);
     update_scene_panel(context);

	return 0;
}

