#ifndef factory_cpp
#define factory_cpp

#include "Factory.hpp"

#endif 

void FactoryFigure::Register(const string& key,Note* obj)
{
    //si la clé n'est pas déjà présente
    if(m_map.find(key)==m_map.end())
    {
        //on ajoute l'objet dans la map
        m_map[key]=obj;
    }
    
    //on pourrait détruire obj mais cette tâche ne revient pas à Register
}

Note* FactoryFigure::Create(const std::string& key) const
{
    Note* tmp=0;
    std::map<string, Note*>::const_iterator it=m_map.find(key);
    
    //si l'itérateur ne vaut pas map.end(), cela signifie que que la clé à été trouvée
    if(it!=m_map.end())
    {
        tmp=((*it).second)->Clone();
    }
    
    //on pourrait lancer une exeption si la clé n'a pas été trouvée
    
    return tmp;
}
