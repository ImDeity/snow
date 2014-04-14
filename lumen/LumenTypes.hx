package lumen;

import lumen.Lumen;

typedef LumenConfig = {

    ? host                  : App,
    ? window_config         : WindowConfig

}

typedef WindowConfig = {

    ? fullscreen            : Bool,
    ? resizable             : Bool,
    ? borderless            : Bool,
    ? antialiasing          : Int,
    ? stencil_buffer        : Bool,
    ? depth_buffer          : Bool,
    ? vsync                 : Bool,
    ? fps                   : Int,
    ? width                 : Int,
    ? height                : Int,
    ? title                 : String,

    ? orientation           : String,
    ? multitouch_supported  : Bool,
    ? multitouch            : Bool

}

typedef SystemEvent = {

    ? type : SystemEventType

} //SystemEvent

typedef WindowEvent = {

    ? type : WindowEventType

} //WindowEvent


enum SystemEventType {
    unknown;
    ready;    
    update;
    shutdown;
}

//Window stuff

enum WindowEventType {
    unknown;
    window_shown;
    window_hidden;
    window_exposed;
    window_moved;
    window_resized;
    window_minimized;
    window_maximized;
    window_restored;
    window_enter;
    window_leave;
    window_focus_gained;
    window_focus_lost;
    window_close;
}


class SystemEvents {
    
    public static var se_unknown               = 0;
    public static var se_ready                 = 1;
    public static var se_update                = 2;
    public static var se_shutdown              = 3;

//Helpers

    public static function typed(type:Int) : SystemEventType {
        
            if(type == se_ready)  return SystemEventType.ready;
            if(type == se_update)  return SystemEventType.update;
            if(type == se_shutdown)  return SystemEventType.shutdown;

        return SystemEventType.unknown;

    } //typed

} //SystemEvents

class WindowEvents {
    
//window events

    public static var we_unknown          = 0;
    public static var we_shown            = 1;
    public static var we_hidden           = 2;
    public static var we_exposed          = 3;
    public static var we_moved            = 4;
    public static var we_resized          = 5;
    public static var we_minimized        = 6;
    public static var we_maximized        = 7;
    public static var we_restored         = 8;
    public static var we_enter            = 9;
    public static var we_leave            = 10;
    public static var we_focus_gained     = 11;
    public static var we_focus_lost       = 12;
    public static var we_close            = 13;

//Helpers

    public static function typed(type:Int) : WindowEventType {
        
            if(type == we_shown)          return WindowEventType.window_shown;
            if(type == we_hidden)         return WindowEventType.window_hidden;
            if(type == we_exposed)        return WindowEventType.window_exposed;
            if(type == we_moved)          return WindowEventType.window_moved;
            if(type == we_resized)        return WindowEventType.window_resized;
            if(type == we_minimized)      return WindowEventType.window_minimized;
            if(type == we_maximized)      return WindowEventType.window_maximized;
            if(type == we_restored)       return WindowEventType.window_restored;
            if(type == we_enter)          return WindowEventType.window_enter;
            if(type == we_leave)          return WindowEventType.window_leave;
            if(type == we_focus_gained)   return WindowEventType.window_focus_gained;
            if(type == we_focus_lost)     return WindowEventType.window_focus_lost;
            if(type == we_close)          return WindowEventType.window_close;
            
        return WindowEventType.unknown;

    } //typed

} //WindowEvents