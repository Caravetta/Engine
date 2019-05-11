#ifndef __ENGINE_TYPES_H__
#define __ENGINE_TYPES_H__

#include <stdint.h>
#include <vector>
#include <emmintrin.h>
#include <iostream>
#include <unordered_map>

#ifdef WINDOWS
    #ifdef ENGINE_EXPORT
        #define ENGINE_API __declspec(dllexport)
    #else
        #define ENGINE_API __declspec(dllimport)
    #endif
#elif LINUX
    #define ENGINE_API __attribute__ ((visibility ("default")))
#else
    #define ENGINE_API
#endif

namespace Engine {

/******************************************/
/*                                        */
/*          Engine Return Codes           */
/*                                        */
/******************************************/

typedef enum {
    SUCCESS               = 0,
    ENGINE_ERROR          = -1000,
    ERROR_INVALID_ENTITY,
    COMPONENT_NOT_SET,
    ARCHETYPE_EXISTS,
    ARCHETYPE_DOES_NOT_EXIST,
    MEMORY_ALLOC_FAILED,
    INVALID_EVENT_NAME,
    INVALID_ASSET_NAME,
    NOT_IMPLEMENTED,
    ENTITY_NOT_VALID,
    FILE_ERROR,
    ASSET_NAME_ALREADY_USED,
    INVALID_HANDLE,
    MESH_IS_NOT_DYNAMIC,
} Rc_t;

/******************************************/
/*                                        */
/*          Math Types                    */
/*                                        */
/******************************************/

class ENGINE_API Vector2f {
public:
    union {
        struct {
          float x;
          float y;
        };
        struct {
          float min;
          float max;
        };
    };

    Vector2f();
    Vector2f( const float x, const float y );

    friend ENGINE_API std::ostream& operator<<(std::ostream& stream, const Vector2f& vector);
};

struct ENGINE_API Vector3f {
public:
    union {
        struct {
            //float pad;
            float x;
            float y;
            float z;
            float pad;
        };
        __m128 data;
    };

    Vector3f();
    Vector3f( const float x, const float y, const float z );
    Vector3f( const __m128 data );
    bool compare( const Vector3f &other ) const;
    Vector3f normalize_fast() const;
    Vector3f normalize() const;
    Vector3f cross( const Vector3f& other );

    friend ENGINE_API std::ostream& operator<<(std::ostream& stream, const Vector3f& vector);

    float operator[]( const int index ) const;
    float & operator[]( const int index );
    Vector3f & operator=( const Vector3f &other );
    bool operator==( const Vector3f &other ) const;
    bool operator!=( const Vector3f &other ) const;
    Vector3f operator-() const;
    float operator*( const Vector3f &other ) const;
    Vector3f operator*( const float scalar ) const;
    Vector3f & operator*=( const float scalar );
    Vector3f  operator/( const float scalar ) const;
    Vector3f & operator/=( const float scalar );
    Vector3f & operator/=( const Vector3f &other );
    Vector3f  operator+( const Vector3f &other ) const;
    Vector3f & operator+=( const Vector3f &other );
    Vector3f  operator-( const Vector3f &other ) const;
    Vector3f & operator-=( const Vector3f &other );
};

class ENGINE_API Matrix4f {
public:
    union {
        struct {
            float m00, m01, m02, m03;
        };
        __m128 row_0;
    };
    union {
        struct {
            float m10, m11, m12, m13;
        };
        __m128 row_1;
    };
    union {
        struct {
            float m20, m21, m22, m23;
        };
        __m128 row_2;
    };
    union {
        struct {
            float m30, m31, m32, m33;
        };
        __m128 row_3;
    };

    Matrix4f();
    void identity();
    void translate( Vector3f* vec );
    void rotate( float angle, Vector3f* axis );
    void scale( float scale );
    Matrix4f generate_transform( Vector3f scale, Vector3f position );

    friend ENGINE_API std::ostream& operator<<( std::ostream &strm, const Matrix4f &a );

    Vector3f operator*( const Vector3f &vector ) const;
    Matrix4f operator*( const Matrix4f &other ) const;
};

/************* Asset System **********************/

typedef struct { //TODO(JOSH): hide this in the engine
    union {
        struct {
            uint64_t index  : 32;
            uint64_t phase  : 31;
            uint64_t active : 1;
        };
        uint64_t id;
    };
} Asset_Handle;

struct ENGINE_API Asset {
public:
    //std::string name;
    Asset_Handle handle;
    uint64_t ref_count;

    virtual void load( std::string file_path ) = 0;
};

/******************************************/
/*                                        */
/*          Entity Type                   */
/*                                        */
/******************************************/

typedef struct { //TODO(JOSH): hide this in the engine
    union {
        struct {
            uint64_t index  : 32;
            uint64_t phase  : 31;
            uint64_t active : 1;
        };
        uint64_t id;
    };
} Entity;

/******************************************/
/*                                        */
/*          Component Type                */
/*                                        */
/******************************************/

#define NON_VALID_ID 4294967295

typedef enum {
    TRANSFORM_COMP = 0,
    MESH_HANDLE_COMP,
    SHADER_ID_COMP,
    TEXT_COMP,
    FONT_SETTINGS_COMP,
    MATERIAL_HANDLE_COMP,
    PARTICAL_EMITTER_COMP,
    BASE_COMPONENT_COUNT
} base_comp_types_t;

template<typename T>
Rc_t component_create( uint8_t* memory )
{
    new (memory) T;
    return SUCCESS;
}

template<typename T>
Rc_t component_copy( uint8_t* source, uint8_t* dest )
{
    T* source_p = (T*)source;
    T* dest_p = (T*)dest;

    *dest_p = *source_p;

    return SUCCESS;
}

typedef Rc_t (*component_create_function)( uint8_t* memory );
typedef Rc_t (*component_copy_function)( uint8_t* source, uint8_t* dest );

struct component_info {
    component_create_function   create_function;
    component_copy_function     copy_function;
    size_t size;
};

template <typename T>
struct type_idx_info
{
    static uint32_t id;
};

template <typename T>
uint32_t type_idx_info<T>::id{NON_VALID_ID};

/******************************************/
/*                                        */
/*          Archetype Type                */
/*                                        */
/******************************************/

class ENGINE_API Archetype {
private:
    std::unordered_map<uint32_t, uint64_t> component_map;

public:
    std::vector<uint32_t> used_component_ids;

    Archetype( void );
    void add_component( const uint32_t component_id );
    bool has_component( const uint32_t component_id );
    template<typename T> void add_component();
    template<typename T> bool has_component();
};

template<typename T>
uint32_t component_id()
{
    return type_idx_info<T>::id;
}

template<typename T>
void Archetype::add_component()
{
    add_component(component_id<T>());
}

template<typename T>
bool Archetype::has_component()
{
    return has_component(component_id<T>());
}

/********************************************/
/*                                          */
/*            System Type                   */
/*                                          */
/********************************************/

typedef std::vector<uint8_t> Array;

typedef enum {
    COMPONENT_READ_ONLY         = 1 << 0,
    COMPONENT_WRITE_ONLY        = 1 << 1,
    COMPONENT_READ_AND_WRITE    = 1 << 2
} component_usage_t;

typedef struct {
    uint64_t                component_id;
    component_usage_t       usage;
    size_t                  size;
    std::vector<Array*>     array_data_vec;
    std::vector<uint64_t*>  entity_count_vec;
    std::vector<uint8_t*>   packed_data;
} component_node_t;

class ENGINE_API System {
private:
    std::vector<component_node_t>           component_nodes;
    std::unordered_map<uint64_t, uint64_t>  comp_map;

protected:
    uint64_t entity_count = 0;

    void add_component( const uint32_t component_id, const component_usage_t usage );
    void add_component( const uint32_t component_id );
    template<typename T> void add_component( const component_usage_t usage );
    template<typename T> void add_component( void );
    template<typename T> T* get_data_at( const uint64_t idx );
    template<typename T> std::vector<T*>* get_data_vec( void );
    std::vector<uint8_t*>* get_data_vec( const uint32_t component_id );

public:
    std::string             name;
    std::vector<uint64_t>   component_list;

    System(){};
    void add_component_data( uint64_t** enitiy_count, const uint32_t comp_id, Array** data_array );
    bool has_component( const uint32_t component_id );
    template<typename T> bool has_component( void );
    bool pre_update();

    virtual void init( void ) = 0;
    virtual void update( void ) = 0;
    virtual void shutdown( void ) = 0;
};

template<typename T>
bool System::has_component()
{
    return has_component(component_id<T>());
}

template<typename T>
T* System::get_data_at( uint64_t idx )
{
    //START_TIME_BLOCK(system_get_data_at);
    uint64_t comp_id = component_id<T>();
    uint64_t comp_total = 0;
    T* return_data = NULL;

    // find the index that this comp is at.
    std::unordered_map<uint64_t, uint64_t>::const_iterator comp_idx = comp_map.find(comp_id);
    if ( comp_idx != comp_map.end() ) {

        //CHECK_INFO( comp_id == component_nodes[comp_idx->second].component_id,
        //            "comp_id:" << comp_id << " component_nodes[comp_idx->second].component_id:" << component_nodes[comp_idx->second].component_id);
        for ( int i = 0; i < component_nodes[comp_idx->second].entity_count_vec.size(); i++ ) {
            comp_total += *(component_nodes[comp_idx->second].entity_count_vec[i]);

            // if idx is less than comp_total then the data must be in this current comp_data node

            if ( idx < comp_total ) {
                //END_TIME_BLOCK(system_get_data_at);
                return (T*)&(component_nodes[comp_idx->second].array_data_vec[i]->at(component_nodes[comp_idx->second].size * idx));
            }
        }

        //CHECK_INFO( idx > comp_total, "idx:" << idx << " comp_total:" << comp_total);
    }

    //CHECK_INFO( comp_idx == comp_map.end(), "This comp ID:" << comp_id << " is not tracked by " << name );

    //END_TIME_BLOCK(system_get_data_at);
    return return_data;
}

template<typename T>
std::vector<T*>* System::get_data_vec()
{
    return (std::vector<T*>*)get_data_vec(component_id<T>());
}

template<typename T>
void System::add_component( component_usage_t usage )
{
    add_component(component_id<T>(), usage);
}

template<typename T>
void System::add_component()
{
    add_component(component_id<T>(), COMPONENT_READ_AND_WRITE);
}

/******************************************/
/*                                        */
/*          Default Systems               */
/*                                        */
/******************************************/

class ENGINE_API Mesh_Render_System : public System {
public:
    Mesh_Render_System();
    void init();
    void update();
    void shutdown();
};

class ENGINE_API Text_Render_System : public System {
public:
    Text_Render_System();
    void init();
    void update();
    void shutdown();
};

class ENGINE_API Partical_System : public System {
public:
    Partical_System();
    void init();
    void update();
    void shutdown();
};

/******************************************/
/*                                        */
/*        Default Component Types         */
/*                                        */
/******************************************/

typedef struct { //TODO(JOSH): hide this in the engine
    union {
        struct {
            uint64_t index  : 32;
            uint64_t phase  : 32;
        };
        uint64_t id;
    };
} Texture_Handle;

struct ENGINE_API Texture {
    uint32_t width;
    uint32_t height;
    uint32_t bits_per_pixel;
    std::vector<uint8_t> pixel_data;
    Texture_Handle handle;
};

/********************************************/
/*                                          */
/*           Material Type                  */
/*                                          */
/********************************************/

typedef struct { //TODO(JOSH): hide this in the engine
    union {
        struct {
            uint64_t index  : 32;
            uint64_t phase  : 32;
        };
        uint64_t id;
    };
} Material_Handle;

typedef enum {
    VEC3_ELEMENT,
    MATRIX4_ELEMENT,
    TEXT_HANDLE_ELEMENT,
} material_element_type_t;

typedef struct {
    std::string element_name;
    uint32_t data_offset;
    material_element_type_t type;
} material_element_info_t;

struct ENGINE_API Material {
private:
    uint8_t* data;
    uint64_t data_size = 0;
    std::unordered_map<std::string, uint64_t> element_map;
public:
    std::vector<material_element_info_t> element_info_vec;
    uint32_t shader_id;
    Rc_t add_element( std::string name, material_element_type_t type );
    template<typename T> Rc_t set_element( std::string name, T data );
    template<typename T> T* get_element( std::string name );
};

template<typename T>
Rc_t Material::set_element( std::string name, T data )
{
    std::unordered_map<std::string, uint64_t>::const_iterator ele = element_map.find(name);
    if ( ele != element_map.end() ) {
        //TODO(JOSH): This is really bad need to find a better way of doing this
        material_element_info_t* ele_info = &element_info_vec[ele->second];
        T* ele_data = (T*)(this->data + ele_info->data_offset);
        *ele_data = data;
    }

    return ENGINE_ERROR;
}

template<typename T>
T* Material::get_element( std::string name )
{
    std::unordered_map<std::string, uint64_t>::const_iterator ele = element_map.find(name);
    if ( ele != element_map.end() ) {
        material_element_info_t* ele_info = &element_info_vec[ele->second];
        return (T*)(this->data + ele_info->data_offset);
    }

    return NULL;
}

/********************************************/
/*                                          */
/*             Mesh Type                    */
/*                                          */
/********************************************/

typedef struct { //TODO(JOSH): hide this in the engine
    union {
        struct {
            uint64_t index  : 32;
            uint64_t phase  : 32;
        };
        uint64_t id;
    };
} Mesh_Handle;

typedef enum {
    MESH_STATIC_DRAW    = 0x88E4,
    MESH_DYNAMIC_DRAW   = 0x88E8,
} mesh_usage_t;

struct ENGINE_API Mesh {
    uint32_t indices_count;
    uint32_t* indices;
    uint32_t vertices_count;
    float* vertices;
    uint32_t normals_count;
    float* normals;
    uint32_t textures_count;
    float* textures;
    Mesh_Handle handle;

    Mesh();

    Rc_t serialize( std::ofstream* out_stream );
    Rc_t deserialize( std::ifstream* in_stream );
};

struct ENGINE_API Transform {
    Vector3f position;
    Vector3f scale;
    Vector3f rotation;
};

struct ENGINE_API Shader_ID {
    uint32_t program_id;
};

typedef struct { //TODO(JOSH): hide this in the engine
    union {
        struct {
            uint64_t index  : 32;
            uint64_t phase  : 32;
        };
        uint64_t id;
    };
} Font_Handle;

typedef std::string Text;

struct ENGINE_API Font_Settings {
    uint16_t size;
    Font_Handle font_handle;
    uint16_t string_new_line_pad;
};

/******************************************/
/*                                        */
/*          Camera Type                   */
/*                                        */
/******************************************/

struct ENGINE_API Camera {
    Transform   transform;
    Matrix4f    view_matrix;
    Matrix4f    projection_matrix;
    float       field_of_view; //Note: This is in degrees;
    float       near_plane;
    float       far_plane;
    float       aspect_ratio;
};

/******************************************/
/*                                        */
/*       Partical Emitter Type            */
/*                                        */
/******************************************/

enum Partical_Type {
    BILLBOARD_PARTICAL_TYPE,
    MESH_PARTICAL_TYPE
};

struct Partical {
    Transform transform;
    float     life;
    Vector3f  speed;
};

struct ENGINE_API Partical_Emitter {
    Partical_Type         type;
    std::vector<Partical> particals;
    Vector3f              partical_speed;

    float                 spawn_rate;
    float                 last_spawn;
    Mesh                  mesh;
    Mesh_Handle           mesh_handle;
    float                 life_time;
    float                 width;
    float                 height;
};

/******************************************/
/*                                        */
/*              Key Codes                 */
/*                                        */
/******************************************/

typedef enum {
    KEY_ESCAPE,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_0,
    KEY_MINUS,
    KEY_EQUALS,
    KEY_BACKSPACE,
    KEY_TAB,
    KEY_Q,
    KEY_W,
    KEY_E,
    KEY_R,
    KEY_T,
    KEY_Y,
    KEY_U,
    KEY_I,
    KEY_O,
    KEY_P,
    KEY_BRACKETLEFT,
    KEY_BRACKETRIGHT,
    KEY_ENTER,
    KEY_CONTROLLEFT,
    KEY_A,
    KEY_S,
    KEY_D,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_SEMICOLON,
    KEY_APOSTROPHE,
    KEY_GRAVE,
    KEY_SHIFTLEFT,
    KEY_BACKSLASH,
    KEY_Z,
    KEY_X,
    KEY_C,
    KEY_V,
    KEY_B,
    KEY_N,
    KEY_M,
    KEY_COMMA,
    KEY_PREIOD,
    KEY_SLASH,
    KEY_SHIFTRIGHT,
    KEY_NUMPAD_MULTIPLY,
    KEY_ALTLEFT,
    KEY_SPACE,
    KEY_CAPSLOCK,
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_NUMLOCK,
    KEY_SCROLLLOCK,
    KEY_NUMPAD_7,
    KEY_NUMPAD_8,
    KEY_NUMPAD_9,
    KEY_NUMPAD_MINUS,
    KEY_NUMPAD_4,
    KEY_NUMPAD_5,
    KEY_NUMPAD_6,
    KEY_NUMPAD_PLUS,
    KEY_NUMPAD_1,
    KEY_NUMPAD_2,
    KEY_NUMPAD_3,
    KEY_NUMPAD_0,
    KEY_NUMPAD_PERIOD,
    KEY_ALT_PRINTSCREEN,
    KEY_BRACKETANGLE,
    KEY_F11,
    KEY_F12,
} key_t;

} // end namespace Engine

#endif
