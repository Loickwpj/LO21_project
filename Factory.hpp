#ifndef factory_hpp 
#define factory_hpp

#include <map>
#include <string>

#include "Note.hpp"


class FactoryNote
{
public:
    static std::map<std::string,Note*> m_map;
    
public:
    //Fonction qui associe clé <=> prototype
    static void Register(const std::string& key,Figure* obj);
    
    //Celle qui va créer les objets
    Figure* Create(const std::string& key) const;

};


#endif
