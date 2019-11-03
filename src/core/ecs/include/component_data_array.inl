
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

     //TODO(JOSH): need to add in caching

     T* data = NULL;

     for ( size_t ii = 0; ii < __chunk_nodes->size(); ii++ ) {
          Data_Chunk& chunk = __chunk_nodes->at(ii);
          if ( (index >= chunk.start) && (index <= chunk.end) ) {
               size_t offset = chunk.offset_map[T::__id];
               uint8_t* comp_start = chunk.data + offset;
               data = (T*)(comp_start + ((index - chunk.start) * T::__size));
          }
     }

     return *data;
}

} // end namespace Engine

