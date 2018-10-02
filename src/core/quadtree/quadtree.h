#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <vector>
#include "../core_common.h"
#include "../math/vector.h"
#include "../math/math_utils.h"

namespace core {

    template <class T>
    class QuadTree {
        private:
        enum quadrant {
            TOP_LEFT    = 1 << 0,
            TOP_RIGHT   = 1 << 1,
            BOT_LEFT    = 1 << 2,
            BOT_RIGHT   = 1 << 3
        };

        struct quadtree_bounds_t {
            float x;
            float y;
            float width;
            float height;
        };

        struct quadtree_entrie_t {
            T*        object;
            Vector2f* position;
            Vector2f* dimensions;
        };

        struct quadtree_node_t {
            std::vector<quadtree_entrie_t*> entries;
            uint16_t                        level;
            quadtree_bounds_t               bounds;
            struct quadtree_node_t*         child_nodes[4];
        };

        quadtree_node_t* root_node;
        uint16_t max_objects;
        uint16_t max_levels;

        void init_quadtree_node( quadtree_node_t* node, uint16_t level, float x, float y, float width, float height );
        void split(quadtree_node_t* node);
        int8_t get_index( quadtree_node_t* node, float x, float y, float width, float height );
        uint8_t get_all_index( quadtree_node_t* node, float x, float y, float width, float height );
        void insert_node( quadtree_node_t* node, quadtree_entrie_t* entrie, float x, float y, float width, float height );
        void retrieve_all_nodes( quadtree_node_t* node, std::vector<T*>* object_vector, float x, float y, float width, float height );

        public:
        QuadTree( float x, float y, float width, float height );
        QuadTree( uint16_t max_objects, uint16_t max_levels, float x, float y, float width, float height );
        void insert( T* entrie, float x, float y, float width, float height );
        void retrieve( std::vector<T*>* object_vector, float x, float y, float width, float height );
    };

template<typename T>
QuadTree<T>::QuadTree( float x, float y, float width, float height )
{
    max_objects = 4;
    max_levels = 5;
    root_node = new quadtree_node_t;
    init_quadtree_node(root_node, 0, x, y, width, height);

}

template<typename T>
QuadTree<T>::QuadTree( uint16_t max_objects, uint16_t max_levels, float x, float y, float width, float height )
{
    this->max_objects = max_objects;
    this->max_levels = max_levels;
    root_node = new quadtree_node_t;
    init_quadtree_node(root_node, 0, x, y, width, height);
}

template<typename T>
void QuadTree<T>::init_quadtree_node( quadtree_node_t* node, uint16_t level, float x, float y, float width, float height )
{
    node->level = level;
    node->bounds.x = x;
    node->bounds.y = y;
    node->bounds.width = width;
    node->bounds.height = height;
    node->child_nodes[0] = NULL;
    node->child_nodes[1] = NULL;
    node->child_nodes[2] = NULL;
    node->child_nodes[3] = NULL;
}

template<typename T>
void QuadTree<T>::split( quadtree_node_t* node )
{
    float sub_width = (node->bounds.width / 2);
    float sub_height = (node->bounds.height / 2);

    float x = node->bounds.x;
    float y = node->bounds.y;

    node->child_nodes[0] = new quadtree_node_t;
    init_quadtree_node(node->child_nodes[0], node->level+1, x + sub_width, y, sub_width, sub_height);
    node->child_nodes[1] = new quadtree_node_t;
    init_quadtree_node(node->child_nodes[1], node->level+1, x, y, sub_width, sub_height);
    node->child_nodes[2] = new quadtree_node_t;
    init_quadtree_node(node->child_nodes[2], node->level+1, x, y + sub_height, sub_width, sub_height);
    node->child_nodes[3] = new quadtree_node_t;
    init_quadtree_node(node->child_nodes[3], node->level+1, x + sub_width, y + sub_height, sub_width, sub_height);
}

template<typename T>
int8_t QuadTree<T>::get_index( quadtree_node_t* node, float x, float y, float width, float height )
{
    int8_t index = -1;
    float vertical_midpoint = node->bounds.x + (node->bounds.width / 2);
    float horizontal_midpoint = node->bounds.y + (node->bounds.height / 2);

    bool top_quadrant = ((y < horizontal_midpoint) && (y + height < horizontal_midpoint));
    bool bottom_quadrant = (y > horizontal_midpoint);

    if ( (x < vertical_midpoint) && (x + width < vertical_midpoint) ) {
        if ( top_quadrant ) {
            index = 1;
        } else if ( bottom_quadrant ) {
            index = 2;
        }
    } else if ( x > vertical_midpoint ) {
        if ( top_quadrant ) {
            index = 0;
        } else if ( bottom_quadrant ) {
            index = 3;
        }
    }

    return index;
}

template<typename T>
void QuadTree<T>::insert( T* entrie, float x, float y, float width, float height )
{
    quadtree_entrie_t* new_entrie = new quadtree_entrie_t;
    new_entrie->object = entrie;
    new_entrie->position = new Vector2f(x, y);
    new_entrie->dimensions = new Vector2f(width, height);
    insert_node(root_node, new_entrie, x, y, width, height);
}

template<typename T>
void QuadTree<T>::insert_node( quadtree_node_t* node, quadtree_entrie_t* entrie, float x, float y, float width, float height )
{
    if ( node->child_nodes[0] != NULL ) {
        int index = get_index(node, x, y, width, height);

        if ( index != -1 ) {
            insert_node(node->child_nodes[index], entrie, x, y, width, height);
            return;
        }
    }

    node->entries.push_back(entrie);

    if ( (node->entries.size() > max_objects) && (node->level < max_levels) ) {
        if ( node->child_nodes[0] == NULL ) {
            split(node);
        }

        for ( int i = 0; i < node->entries.size(); ) {
            quadtree_entrie_t* tmp_entrie = node->entries.at(i);
            int index = get_index(node, tmp_entrie->position->x, tmp_entrie->position->y, tmp_entrie->dimensions->x, tmp_entrie->dimensions->y);
            if ( index != -1 ) {
                insert_node(node->child_nodes[index], tmp_entrie, tmp_entrie->position->x, tmp_entrie->position->y, tmp_entrie->dimensions->x, tmp_entrie->dimensions->y);
                node->entries.erase(node->entries.begin() + i);
            } else {
                i++;
            }
        }
    }
}

template<typename T>
uint8_t QuadTree<T>::get_all_index( quadtree_node_t* node, float x, float y, float width, float height )
{
    uint8_t index_mask = 0;

    float child_width = node->bounds.width / 2;
    float child_height = node->bounds.height / 2;

    if ( aabb_collision(x, y, width, height, (node->bounds.x + child_width), node->bounds.y, child_width, child_height) ) {
        index_mask |= BOT_RIGHT;
    }

    if ( aabb_collision(x, y, width, height, node->bounds.x, node->bounds.y, child_width, child_height) ) {
        index_mask |= BOT_LEFT;
    }

    if ( aabb_collision(x, y, width, height, node->bounds.x, (node->bounds.y + child_height), child_width, child_height) ) {
        index_mask |= TOP_LEFT;
    }

    if ( aabb_collision(x, y, width, height, (node->bounds.x + child_width), (node->bounds.y + child_height), child_width, child_height) ) {
        index_mask |= TOP_RIGHT;
    }

    return index_mask;
}

template<typename T>
void QuadTree<T>::retrieve( std::vector<T*>* object_vector, float x, float y, float width, float height )
{
    retrieve_all_nodes(root_node, object_vector, x, y, width, height);
}

template<typename T>
void QuadTree<T>::retrieve_all_nodes( quadtree_node_t* node, std::vector<T*>* object_vector, float x, float y, float width, float height )
{
    if ( node == NULL ) {
        return;
    }
    uint8_t index_mask = get_all_index(node, x, y, width, height);

    if ( index_mask > 0 ) {
        if ( index_mask & BOT_RIGHT ) {
            retrieve_all_nodes(node->child_nodes[0], object_vector, x, y, width, height);
        }
        if ( index_mask & BOT_LEFT ) {
            retrieve_all_nodes(node->child_nodes[1], object_vector, x, y, width, height);
        }
        if ( index_mask & TOP_LEFT ) {
            retrieve_all_nodes(node->child_nodes[2], object_vector, x, y, width, height);
        }
        if ( index_mask & TOP_RIGHT ) {
            retrieve_all_nodes(node->child_nodes[3], object_vector, x, y, width, height);
        }
    }

    for ( int i = 0; i < node->entries.size(); i++ ) {
        object_vector->push_back(node->entries.at(i)->object);
    }
}

} //end namespace core

#endif //__QUADTREE_H__
