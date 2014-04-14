#ifndef LUMEN_HX_BINDINGS_H
#define LUMEN_HX_BINDINGS_H

#include <hx/CFFI.h>

namespace lumen {    

        //forward
    class Object;

        //externs
    extern vkind global_lumen_object_kind;

        //id's
    extern int id_type;
    extern int id_width;
    extern int id_height;
    extern int id_title;
    extern int id_fullscreen;
    extern int id_resizable;
    extern int id_borderless;
    extern int id_antialiasing;
    extern int id_depth_buffer;
    extern int id_stencil_buffer;
    extern int id_vsync;
    extern int id_fps;

    inline void lumen_init_ids() {
        
            //global

        kind_share( &global_lumen_object_kind, "lumen::Object");

            //more common flags

        id_type                 = val_id("type");
        id_width                = val_id("width");
        id_height               = val_id("height");

            //window config flags

        id_title                = val_id("title");
        id_fullscreen           = val_id("fullscreen");
        id_resizable            = val_id("resizable");
        id_borderless           = val_id("borderless");
        id_antialiasing         = val_id("antialiasing");
        id_depth_buffer         = val_id("depth_buffer");
        id_stencil_buffer       = val_id("stencil_buffer");
        id_vsync                = val_id("vsync");
        id_fps                  = val_id("fps");

    } //lumen_init_ids    

// native object wrapper tools

    class Object {

        public:
            
            int ref_count;

        protected:

            virtual ~Object() {}

        public:

            Object( bool has_initial_ref = false ) : ref_count( has_initial_ref ? 1 : 0 ) {}

            Object *grab() {

                ref_count++;

                return this; 

            } //grab

            void drop() { 
                
                ref_count--; 
                
                if( ref_count <= 0 ) {
                    delete this; 
                }

            } //drop

            // virtual int getApiVersion() { 
            //     return NME_API_VERSION; 
            // }
        
    }; //Object

    inline value Object_to_hx( Object *object ) {

       struct releaser {

            static void release_object(value _in_object) {

                if( val_is_kind(_in_object, global_lumen_object_kind) ) {

                    Object *obj = (Object *)val_to_kind( _in_object, global_lumen_object_kind );

                    if(obj) {
                        obj->drop();
                    }

                } //if is global_lumen_object_kind

            } //release_object

       }; //releaser

            //increase references
        object->grab();

            //create the haxe abstract for returning
        value result = alloc_abstract( global_lumen_object_kind, object );
            //tell the gc to collect this object from the releaser struct callback
        val_gc( result, releaser::release_object );
            
        return result;

    } //Object_to_hx


    template<typename T> bool Object_from_hx( value _in_object, T *&_out_object) {
       
        _out_object = 0;

                //check if it's the right kind of object first
            if ( !val_is_kind( _in_object, global_lumen_object_kind) ) {
                return false;
            }

                //fetch the wrapped Object
           Object *object = (Object *)val_to_kind(_in_object,global_lumen_object_kind);
                //cast to the type given and set the out reference
            _out_object = dynamic_cast<T*>( object );

        return _out_object != NULL;

    } //Object_from_hx


// property conversion tools

    inline bool property_bool(value _object, int _val_id, bool _default) {

       value field = val_field(_object,_val_id);

            //handle null/non-existant properties
        if( val_is_null(field) ) {
            return _default;
        } 

       return val_bool( field );

    } //property_bool

    inline int property_int(value _object, int _val_id, int _default) {

       value field = val_field(_object,_val_id);

            //handle null/non-existant properties
        if( val_is_null(field) ) {
            return _default;
        } 

       return (int)val_number( field );

    } //property_int

    inline const char* property_string(value _object, int _val_id, const char* _default) {

       value field = val_field(_object,_val_id);

            //handle null/non-existant properties
        if( val_is_null(field) ) {
            return _default;
        } 

       return val_string( field );

    } //property_string


//// property conversion tools



} //namespace lumen

#endif //LUMEN_HX_BINDINGS_H