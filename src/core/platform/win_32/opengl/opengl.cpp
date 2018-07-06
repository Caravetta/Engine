#include <gl/Gl.h>
#include <iostream>
#include "opengl.h"

//TODO: This needs to be move to the windows code area

#define WGL_NUMBER_PIXEL_FORMATS_ARB      0x2000
#define WGL_DRAW_TO_WINDOW_ARB            0x2001
#define WGL_DRAW_TO_BITMAP_ARB            0x2002
#define WGL_ACCELERATION_ARB              0x2003
#define WGL_NEED_PALETTE_ARB              0x2004
#define WGL_NEED_SYSTEM_PALETTE_ARB       0x2005
#define WGL_SWAP_LAYER_BUFFERS_ARB        0x2006
#define WGL_SWAP_METHOD_ARB               0x2007
#define WGL_NUMBER_OVERLAYS_ARB           0x2008
#define WGL_NUMBER_UNDERLAYS_ARB          0x2009
#define WGL_TRANSPARENT_ARB               0x200A
#define WGL_TRANSPARENT_RED_VALUE_ARB     0x2037
#define WGL_TRANSPARENT_GREEN_VALUE_ARB   0x2038
#define WGL_TRANSPARENT_BLUE_VALUE_ARB    0x2039
#define WGL_TRANSPARENT_ALPHA_VALUE_ARB   0x203A
#define WGL_TRANSPARENT_INDEX_VALUE_ARB   0x203B
#define WGL_SHARE_DEPTH_ARB               0x200C
#define WGL_SHARE_STENCIL_ARB             0x200D
#define WGL_SHARE_ACCUM_ARB               0x200E
#define WGL_SUPPORT_GDI_ARB               0x200F
#define WGL_SUPPORT_OPENGL_ARB            0x2010
#define WGL_DOUBLE_BUFFER_ARB             0x2011
#define WGL_STEREO_ARB                    0x2012
#define WGL_PIXEL_TYPE_ARB                0x2013
#define WGL_COLOR_BITS_ARB                0x2014
#define WGL_RED_BITS_ARB                  0x2015
#define WGL_RED_SHIFT_ARB                 0x2016
#define WGL_GREEN_BITS_ARB                0x2017
#define WGL_GREEN_SHIFT_ARB               0x2018
#define WGL_BLUE_BITS_ARB                 0x2019
#define WGL_BLUE_SHIFT_ARB                0x201A
#define WGL_ALPHA_BITS_ARB                0x201B
#define WGL_ALPHA_SHIFT_ARB               0x201C
#define WGL_ACCUM_BITS_ARB                0x201D
#define WGL_ACCUM_RED_BITS_ARB            0x201E
#define WGL_ACCUM_GREEN_BITS_ARB          0x201F
#define WGL_ACCUM_BLUE_BITS_ARB           0x2020
#define WGL_ACCUM_ALPHA_BITS_ARB          0x2021
#define WGL_DEPTH_BITS_ARB                0x2022
#define WGL_STENCIL_BITS_ARB              0x2023
#define WGL_AUX_BUFFERS_ARB               0x2024
#define WGL_NO_ACCELERATION_ARB           0x2025
#define WGL_GENERIC_ACCELERATION_ARB      0x2026
#define WGL_FULL_ACCELERATION_ARB         0x2027
#define WGL_SWAP_EXCHANGE_ARB             0x2028
#define WGL_SWAP_COPY_ARB                 0x2029
#define WGL_SWAP_UNDEFINED_ARB            0x202A
#define WGL_TYPE_RGBA_ARB                 0x202B
#define WGL_TYPE_COLORINDEX_ARB           0x202C
#define WGL_CONTEXT_MAJOR_VERSION_ARB     0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB     0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB       0x2093
#define WGL_CONTEXT_FLAGS_ARB             0x2094
#define ERROR_INVALID_VERSION_ARB         0x2095
#define WGL_CONTEXT_DEBUG_BIT_ARB         0x00000001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x00000002
#define WGL_CONTEXT_PROFILE_MASK_ARB      0x9126
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB  0x00000001

void _load_extension_list()
{
	wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
	if ( !wglChoosePixelFormatARB )
	{
		LOG_ERROR("Failed to load wglChoosePixelFormatARB");
	}

	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
	if ( !wglCreateContextAttribsARB )
	{
		LOG_ERROR("Failed to load wglCreateContextAttribsARB");
	}

	glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
	if ( !glCreateShader )
	{
		LOG_ERROR("Failed to load glCreateShader");
	}

	glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
	if ( !glShaderSource )
	{
		LOG_ERROR("Failed to load glShaderSource");
	}

	glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
	if ( !glCompileShader )
	{
		LOG_ERROR("Failed to load glCompileShader");
	}

	glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
	if ( !glGetShaderiv )
	{
		LOG_ERROR("Failed to load glGetShaderiv");
	}

	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
	if ( !glGetShaderInfoLog )
	{
		LOG_ERROR("Failed to load glGetShaderInfoLog");
	}

	glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
	if ( !glCreateProgram )
	{
		LOG_ERROR("Failed to load glCreateProgram");
	}

	glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
	if ( !glCreateProgram )
	{
		LOG_ERROR("Failed to load glCreateProgram");
	}

	glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
	if ( !glAttachShader )
	{
		LOG_ERROR("Failed to load glAttachShader");
	}

	glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
	if ( !glLinkProgram )
	{
		LOG_ERROR("Failed to load glLinkProgram");
	}

	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
	if ( !glGetProgramiv )
	{
		LOG_ERROR("Failed to load glGetProgramiv");
	}

	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
	if ( !glGetProgramInfoLog )
	{
		LOG_ERROR("Failed to load glGetProgramInfoLog");
	}

	glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
	if ( !glDeleteShader )
	{
		LOG_ERROR("Failed to load glDeleteShader");
	}

	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
	if ( !glDeleteProgram )
	{
		LOG_ERROR("Failed to load glDeleteProgram");
	}

	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
	if ( !glGenVertexArrays )
	{
		LOG_ERROR("Failed to load glGenVertexArrays");
	}

	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
	if ( !glBindVertexArray )
	{
		LOG_ERROR("Failed to load glBindVertexArray");
	}

	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
	if ( !glEnableVertexAttribArray )
	{
		LOG_ERROR("Failed to load glEnableVertexAttribArray");
	}

	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");
	if ( !glDisableVertexAttribArray )
	{
		LOG_ERROR("Failed to load glDisableVertexAttribArray");
	}

	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
	if ( !glVertexAttribPointer )
	{
		LOG_ERROR("Failed to load glVertexAttribPointer");
	}

	glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	if ( !glGenBuffers )
	{
		LOG_ERROR("Failed to load glGenBuffers");
	}

    glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
	if ( !glDeleteBuffers )
	{
		LOG_ERROR("Failed to load glDeleteBuffers");
	}

	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	if ( !glBindBuffer )
	{
		LOG_ERROR("Failed to load glBindBuffer");
	}

	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
	if ( !glBufferData )
	{
		LOG_ERROR("Failed to load glBufferData");
	}

	glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	if ( !glGenBuffers )
	{
		LOG_ERROR("Failed to load glGenBuffers");
	}

	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	if ( !glBindBuffer )
	{
		LOG_ERROR("Failed to load glBindBuffer");
	}

	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
	if ( !glBufferData )
	{
		LOG_ERROR("Failed to load glBufferData");
	}

	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
	if ( !glGetUniformLocation )
	{
		LOG_ERROR("Failed to load glGetUniformLocation");
	}

	glActiveTexture = (PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture");
	if ( !glActiveTexture )
	{
		LOG_ERROR("Failed to load glActiveTexture");
	}

	glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
	if ( !glUseProgram )
	{
		LOG_ERROR("Failed to load glUseProgram");
	}

	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
	if ( !glUniformMatrix4fv )
	{
		LOG_ERROR("Failed to load glUniformMatrix4fv");
	}

	glUniform3fv = (PFNGLUNIFORM3FVPROC)wglGetProcAddress("glUniform3fv");
	if ( !glUniform3fv )
	{
		LOG_ERROR("Failed to load glUniform3fv");
	}

	glUniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
	if ( !glUniform1f )
	{
		LOG_ERROR("Failed to load glUniform1f");
	}

    glUniform2f = (PFNGLUNIFORM2FPROC)wglGetProcAddress("glUniform2f");
	if ( !glUniform2f )
	{
		LOG_ERROR("Failed to load glUniform2f");
	}

    glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
	if ( !glUniform1i )
	{
		LOG_ERROR("Failed to load glUniform1i");
	}

	glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
    if ( !glGenerateMipmap )
	{
		LOG_ERROR("Failed to load glGenerateMipmap");
	}

	glGetStringi = (PFNGLGETSTRINGIPROC)wglGetProcAddress("glGetStringi");
    if ( !glGetStringi )
	{
		LOG_ERROR("Failed to load glGetStringi");
	}

    glSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
    if ( !glSwapIntervalEXT )
    {
        LOG_ERROR("Failed to load wglSwapIntervalEXT");
    }
}

LRESULT CALLBACK _TempWndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_CLOSE:
     //       DestroyWindow(hwnd);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int load_opengl_extensions()
{
    WNDCLASSEX wc;
    HINSTANCE instance = GetModuleHandle(NULL);
    HWND hWnd;

    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = (WNDPROC)_TempWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = instance;
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wc.hIconSm = wc.hIcon;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "TempOpenGL";
    wc.cbSize = sizeof(WNDCLASSEX);

    if ( !RegisterClassEx(&wc) ) {
        LOG_ERROR("Failed To Register The Window Class.");
        DWORD dw = GetLastError();
        return 1;
    }

    hWnd = CreateWindowEx(WS_EX_APPWINDOW,
                          "TempOpenGL",
                          "TempOpenGL",
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW,
                          0,
                          0,
                          640,
                          480,
                          NULL,
                          NULL,
                          instance,
                          NULL);

    if ( hWnd == NULL ) {
        LOG_ERROR("Failed to create temp window");
        return 1;
    }

    ShowWindow(hWnd, SW_HIDE);

	HDC deviceContext;
	PIXELFORMATDESCRIPTOR pixelFormat;
	int error;
	HGLRC renderContext;

	deviceContext = GetDC(hWnd);
	if ( !deviceContext ) {
		LOG_ERROR("Failed to get device context");
		return 1;
	}

	// Set a temporary default pixel format.
	error = SetPixelFormat(deviceContext, 1, &pixelFormat);
	if ( error != 1 ) {
		LOG_ERROR("Failed to set pixel format");
		return 1;
	}

	// Create a temporary rendering context.
	renderContext = wglCreateContext(deviceContext);
	if ( !renderContext ) {
		LOG_ERROR("Failed to create context");
		return 1;
	}

	// Set the temporary rendering context as the current rendering context for this window.
	error = wglMakeCurrent(deviceContext, renderContext);
	if ( error != 1 ) {
		LOG_ERROR("Failed to make context current");
		return 1;
	}

	// Initialize the OpenGL extensions needed for this application.  Note that a temporary rendering context was needed to do so.
	_load_extension_list();

	// Release the temporary rendering context now that the extensions have been loaded.
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(renderContext);
	renderContext = NULL;

	// Release the device context for this window.
	ReleaseDC(hWnd, deviceContext);
	deviceContext = 0;
    MSG     msg;
    if ( PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE) ) {
            TranslateMessage(&msg);             // Translate The Message
            DispatchMessage(&msg);              // Dispatch The Message
    }
    DestroyWindow(hWnd);

    return 0;
}

void init_opengl( HDC* hDC, HWND* hWnd, HGLRC* hglrc )
{
	int attributeListInt[30];
	int pixelFormat[1];
	unsigned int formatCount;
	int result;
	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
	int attributeList[5];

	*hDC = GetDC(*hWnd);
	if ( !*hWnd ) {
		std::cout << "Failed to get window context" << std::endl;
		return;
	}

	// Support for OpenGL rendering.
	attributeListInt[0] = WGL_SUPPORT_OPENGL_ARB;
	attributeListInt[1] = TRUE;

	// Support for rendering to a window.
	attributeListInt[2] = WGL_DRAW_TO_WINDOW_ARB;
	attributeListInt[3] = TRUE;

	// Support for hardware acceleration.
	attributeListInt[4] = WGL_ACCELERATION_ARB;
	attributeListInt[5] = WGL_FULL_ACCELERATION_ARB;

	// Support for 24bit color.
	attributeListInt[6] = WGL_COLOR_BITS_ARB;
	attributeListInt[7] = 24;

	// Support for 24 bit depth buffer.
	attributeListInt[8] = WGL_DEPTH_BITS_ARB;
	attributeListInt[9] = 24;

	// Support for double buffer.
	attributeListInt[10] = WGL_DOUBLE_BUFFER_ARB;
	attributeListInt[11] = TRUE;

	// Support for swapping front and back buffer.
	attributeListInt[12] = WGL_SWAP_METHOD_ARB;
	attributeListInt[13] = WGL_SWAP_EXCHANGE_ARB;

	// Support for the RGBA pixel type.
	attributeListInt[14] = WGL_PIXEL_TYPE_ARB;
	attributeListInt[15] = WGL_TYPE_RGBA_ARB;

	// Support for a 8 bit stencil buffer.
	attributeListInt[16] = WGL_STENCIL_BITS_ARB;
	attributeListInt[17] = 8;

    //attributeList[18] = WGL_CONTEXT_PROFILE_MASK_ARB;
    //attributeList[19] = WGL_CONTEXT_CORE_PROFILE_BIT_ARB;

	// Null terminate the attribute list.
	attributeListInt[18] = 0;

	result = wglChoosePixelFormatARB(*hDC, attributeListInt, NULL, 1, pixelFormat, &formatCount);
	if ( result != 1 ) {
		LOG_ERROR("Failed to choose pixel format");
		return;
	}

	// If the video card/display can handle our desired pixel format then we set it as the current one.
	result = SetPixelFormat(*hDC, pixelFormat[0], &pixelFormatDescriptor);
	if ( result != 1 ) {
		LOG_ERROR("Failed to set pixel format");
		return;
	}

	// Set the 4.0 version of OpenGL in the attribute list.
	attributeList[0] = WGL_CONTEXT_MAJOR_VERSION_ARB;
    attributeList[1] = 3;
	attributeList[2] = WGL_CONTEXT_MINOR_VERSION_ARB;
	attributeList[3] = 2;
    int attribs[] =
       {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
            WGL_CONTEXT_MINOR_VERSION_ARB, 2,
            WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0
       };

	// Null terminate the attribute list.
	attributeList[4] = 0;

	// Create a OpenGL 4.0 rendering context.
	*hglrc = wglCreateContextAttribsARB(*hDC, 0, attribs);
	if ( *hglrc == NULL ) {
		LOG_ERROR("Failed to get rendering context");
		return;
	}

	// Set the rendering context to active.
	result = wglMakeCurrent(*hDC, *hglrc);
	if ( result != 1 ) {
		LOG_ERROR("Failed to set rendering context");
		return;
	}
#if 0
	GLint n = 0;
	glGetIntegerv(GL_NUM_EXTENSIONS, &n);
	PFNGLGETSTRINGIPROC glGetStringi = 0;
	glGetStringi = (PFNGLGETSTRINGIPROC)wglGetProcAddress("glGetStringi");

	for (GLint i = 0; i<n; i++)
	{
		const char* extension =
			(const char*)glGetStringi(GL_EXTENSIONS, i);
		UH_LOG("Ext " << i << " " <<extension << " extension");
	}
#endif

    return;
}
