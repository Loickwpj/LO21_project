#ifndef singleton_h
#define singleton_h

#include "note.h"

/** @class Singleton
 *@brief classe que l'on a templatisé car de cette classe vont découler les
 * classes Notesmanager, Référence, Relationsmanager ainsi que Corbeille.
 *
 */

template<class T> class Singleton{

    T& operator= (const T&) {}

    //HANDLER

    /**
     * @struct Handler
     * @fn gestion automatique de l'instance unique d' un singleton
     *
     * @brief L'handler est une structure qui nous permet de gérer l'instanciation d'un
     * singleton de manière automatique à la création du singleton et à sa destruction. Il dispose d'un attribut
     * "instance" qui est un pointeur sur l'instance unique du singleton.
     */

    struct Handler{
        T* instance;

        /**
         * @fn Handler
         * @brief constructeur qui réduit le pointeur de singleton au pointeur nul
         */

        Handler(): instance(nullptr) {}
        ~Handler(){
            if(instance) delete instance;   instance = nullptr;
        }
    };
protected:

    /** @brief handler
     *
     *attribut stantic qui ne nécessite pas l'instanciation de la classe
     * pour être gêré
     */

    static struct Handler handler;

public:
    virtual ~Singleton() {}

    /**
     * @fn getInstance
     * @return l'instance unique du singleton si elle existe, la créée dynamiquement sinon
     * @brief permet de gérer  manuellement l'instance du singleton
     */


    static T& getInstance();

    /**
     * @fn removeInstance
     * @brief détruit l'instance unique du singleton si elle existe et la place au pointeur nul,
     * permet également de gérer manuellement l'instance du singleton
     *
     */

    static void removeInstance();

};

///DEFINITION VARIABLE STATIC
template<class T> typename Singleton<T>::Handler Singleton<T>::handler = Singleton<T>::Handler();


template<class T>  T& Singleton<T>::getInstance(){
    if(!handler.instance) handler.instance = new T();
    return *handler.instance;
}

template<class T> void Singleton<T>::removeInstance(){
    if(handler.instance) delete handler.instance;
    handler.instance = nullptr;
}



#endif
