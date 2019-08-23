
namespace Engine {

template<class T>
Component_Data_Array<T>::Component_Data_Array( Entity_Group& group )
{
	__cur_idx = 0;
	__next_idx = 1;
	__cur_data = NULL;
	__chunk_nodes = &group.__chunk_nodes;
     __size = group.__size;
}

template<class T>
size_t Component_Data_Array<T>::size( void )
{
     return __size;
}

template<class T>
T& Component_Data_Array<T>::operator[]( size_t index ){
     Data_Chunk* p_node = NULL;

     if ( index == __cur_idx && __cur_data != NULL ) {
          return *__cur_data;
	} else if ( index == __next_idx ) {
		p_node = __next_chunk;
     } else {
          for ( size_t ii = 0; ii < __chunk_nodes->size(); ii++ ) {
               p_node = &__chunk_nodes->at(ii);
               if ( index >= p_node->start && index <= p_node->end ) {
				__cur_chunk_idx = ii;
                    break;
               }
               p_node = NULL;
          }
	}

     Data_Chunk& node = *p_node;
     size_t offset = node.offset_map[T::__id];
     __cur_data = (T*)((node.data + offset) + (T::__size * (index - node.start)));
     __cur_idx = index;
	__next_idx = index + 1;

	if ( ((index + 1) > node.end) && ((__cur_chunk_idx + 1) < __chunk_nodes->size()) ) {
		__next_chunk = &__chunk_nodes->at(__cur_chunk_idx + 1);
	} else {
		__next_chunk = p_node;
	}

     return *__cur_data;
}

} // end namespace Engine

