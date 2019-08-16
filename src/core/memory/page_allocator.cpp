#include <cstring>
#include <cstdlib>
#include "page_allocator.h"

namespace Engine {

struct Page_Node {
     void*               page;
     struct Page_Node*   next;
};

struct Page_Allocator {
     uint16_t       pool_size;
     uint16_t       page_size;
     uint16_t       num_pages;
     Page_Node*     head;
     Page_Node*     tail;
};

Page_Allocator* page_allocator = NULL;

void _push_back( Page_Node* node );
Page_Node* _pop_front( void );
Rc_t _allocate_pages( void );

Rc_t init_page_allocator( const uint16_t page_size, const uint16_t pool_size )
{
     Rc_t rc = SUCCESS;

     if ( page_allocator == NULL ) {
          page_allocator = (Page_Allocator*)malloc(sizeof(Page_Allocator));
          if ( page_allocator != NULL ) {
               memset(page_allocator, 0, sizeof(Page_Allocator));
               page_allocator->page_size = page_size;
               page_allocator->pool_size = pool_size;

               rc = _allocate_pages();
          } else {
               rc = MEMORY_ALLOC_FAILED;
          }
     } else {
          rc = ENGINE_ERROR;
     }

     return rc;
}

void _free_pages( void )
{
     Page_Node* node = page_allocator->head;
     Page_Node* cur_node = NULL;

     while ( node != NULL ) {
          cur_node = node;
          node = cur_node->next;
          free(cur_node);
     }
}

void destroy_page_allocator( void )
{
     if ( page_allocator != NULL ) {
          _free_pages();
          free(page_allocator);
          page_allocator = NULL;
     }
}

void* allocate_page( void )
{

     void* page = (void*)_pop_front();

     #if 1
     // check to see if we need to alloc more pages
     if ( page_allocator->num_pages <= (page_allocator->pool_size / 2) ) {
          Rc_t rc = _allocate_pages();
          if ( rc != SUCCESS ) {
               LOG_ERROR( "%s: Failed to allocate pages", __FUNCTION__ );
          }
     }
     #endif

     return page;
}

void free_page( void* page )
{
     if ( page_allocator != NULL ) {
          // check to see if we reached max pool size
          if ( page_allocator->pool_size != page_allocator->num_pages ) {
               Page_Node* node = (Page_Node*)page;
               node->page = page;
               _push_back(node);
          } else {
               free(page);
          }
     } else {
          LOG_ERROR( "%s: Failed to free page", __FUNCTION__ );
     }
}

uint16_t page_size( void )
{
     uint16_t page_size = 0;

     if ( page_allocator != NULL ) {
          page_size = page_allocator->page_size;
     }

     return page_size;
}

void _push_back( Page_Node* node )
{
     node->next = NULL;

     if ( page_allocator->head != NULL ) {
          Page_Node* tail = page_allocator->tail;
          tail->next = node;
          page_allocator->tail = node;

     } else {
          page_allocator->head = node;
          page_allocator->tail = node;
     }

     page_allocator->num_pages += 1;
}

Page_Node* _pop_front( void )
{
     Page_Node* node = NULL;

     if ( page_allocator->head != NULL ) {
          node = page_allocator->head;
          page_allocator->head = node->next;
          page_allocator->num_pages -= 1;
     }

     return node;

}

Rc_t _allocate_pages( void )
{
     Rc_t rc = SUCCESS;
     void* page = NULL;
     Page_Node* node = NULL;

     uint16_t num_allocs = page_allocator->pool_size - page_allocator->num_pages;
     for ( uint16_t ii = 0; ii < num_allocs; ++ii ) {
          page = malloc(page_allocator->page_size);
          if ( page == NULL ) {
               rc = MEMORY_ALLOC_FAILED;
               break;
          }

          node = (Page_Node*)page;
          node->page = page;
          _push_back(node);
     }

     return rc;
}

} // end namespace Engine

