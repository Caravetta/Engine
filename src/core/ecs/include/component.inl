
namespace Engine {

template<class T>
Component_ID component_id( void )
{
     return T::__id;
}

template<class T>
size_t component_size( void )
{
     return T::__size;
}

template<class T>
Component_Registrar<T>::Component_Registrar( void )
     : Component_Base_Registrar()
{
     Component_Base_Registrar::add_to_list(this);
}

template<class T>
Component_Registrar<T>::~Component_Registrar( void )
{
     //do nothing
}

template<class T>
void Component_Registrar<T>::component_register( Component_ID id )
{
     T::setup_component(id);
}

} // end namespace Engine

