#ifndef NotesManager_hpp
#define NotesManager_hpp

#include "Note.h"

#endif

template<class T> class Singleton{
    
    T& operator= (const T&) {}
   
    //HANDLER
    
    struct Handler{
        T* instance;
        Handler(): instance(nullptr) {}
        ~Handler(){
            if(instance) delete instance;   instance = nullptr;
        }
    };
protected:
    
    static struct Handler handler;

public:
    static T& getInstance();
    static void removeInstance();
};

//Définition variable static
template<class T> typename Singleton<T>::Handler Singleton<T>::handler = Singleton<T>::Handler();


template<class T>  T& Singleton<T>::getInstance(){
    if(!handler.instance) handler.instance = new T();
    return *handler.instance;
}

template<class T> void Singleton<T>::removeInstance(){
    if(handler.instance) delete handler.instance;
    handler.instance = nullptr;
}


