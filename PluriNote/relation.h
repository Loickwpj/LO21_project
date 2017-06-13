#ifndef relation_h
#define relation_h
//#include "couple.h"
//#include "manager.h"
#include "coupleediteur.h"


/** \file relations.h */

/** @class BaseRelation
  *@brief
  * Classe dont les différentes relations ET la classe Référence
  * vont hériter qui présentent les attributs communs et méthodes
  * communes aux relations et à la relation référence
  */

/*******************************************************************
 ***                        Base Relation                        ***
 *******************************************************************/

class Couple;
class Note;

class BaseRelation{
protected:
    QString title;
    QString description;
    Couple** couples;
    unsigned int nbCouple, nbMaxCouple;
public:

    /**
     * @fn BaseRelation
     * @param d = description de la relation
     * @param t = titre de la relation
     * @brief
     * constructeur de BaseRelation
     */

    BaseRelation(const QString & d, const QString & t) : title(t), description(d), couples(nullptr), nbCouple(0), nbMaxCouple(0) {}

    /**
     * @fn BaseRelation
     * @brief constructeur par défaut de la relation qui créé une relation
     * sans titre et sans description et dont le tableau de couple est
     * réduit au pointeur nul
     */
    BaseRelation() :title(""), description(""), couples(nullptr), nbCouple(0), nbMaxCouple(0) {}

    //Accesor

    /**
     * @fn getDescription
     * @return la description de la relation
     */
    const QString & getDescription () const {return description;}

    /**
     * @fn getNbCouple
     * @return  le nombre de couple de la relation
     */
    unsigned int getNbCouple() const {return nbCouple;}

    /**
     * @fn getNbMaxCouple
     * @return le nombre maximal de couple que peut contenir le tableau de couples
     */
    unsigned int getNbMaxCouple() const {return nbMaxCouple;}
    //void addCouple(Note*, Note*);

    /**
     * @fn addCouple
     * @param pointeur sur un couple que l'on souhaite ajouter à la relation
     */
    void addCouple(Couple*);

    /**
     * @fn removeCouple
     * permet de supprimer le couple de la relation dont le label et les deux notes
     * correspondantes sont passés en arguments
     */

    void removeCouple(const QString&,Note*,Note*);

    /**
     * @fn getTitle
     * @return le titre de la relation
     */
    const QString& getTitle() const {return title;}

    /**
     * @fn getCouple
     * @param i : entier qui correspond à la position du couple recherché
     * @return le couple à la ième position dans le tableau de la relation
     *
     */
    Couple* getCouple(int i) const {return couples[i];}
    /**
     * @fn getCouple
     * @param id1 : identificateur de la première note du couple recherché
     * @param id2 : identificateur de la seconde note du couple recherché
     * @return le couple dont les identificateurs des deux notes sont passés en argument
     */

    Couple* getCouple(unsigned int id1, unsigned int id2 ) const;

    /**
     * @fn setTitle
     * @param t = nouveau titre de la relation
     *
     */
    void setTitle(const QString & t) {title=t;}


    /**
     * @fn setDescription
     * @param d = nouvelle description de la relation
     */
    void setDescription(const QString & d) {description=d;}

    //Methods

    /**
     * @fn chercherCoupleInRelation
     * @param note dont on cherche les occurences dans les couples de la relation
     * @brief pour une relation donnée, cette méthode permet de rechercher les couples dont la note 1
     * ou la note 2 sont égales à la note passée en argument
     */

    void chercherCoupleInRelation(Note*);

    /**
     * @fn getNewCouple
     *@brief  permet créer dynamiquement un nouveau couple appartenant à la relation
     */

    void getNewCouple();

    /**
     * @fn CoupleEdit
     * @param couple dont on veut éditer le label
     * @brief permet de créer un éditeur de couple qui nous permettra
     * de modifier le label du couple transmis en paramètre
     */

    void CoupleEdit(Couple*);

    virtual ~BaseRelation() {}



    ///ITERATOR

    /**
     * @class iterator
     * @brief
     * va nous permettre de parcourir séquentiellement l'ensemble
     * des couples d'une relation
     */
    class iterator{
        friend class BaseRelation;
        friend class Relation;
        friend class Reference;
        Couple** currentN;

        iterator(Couple**n): currentN(n){}

    public:
        bool operator!=(iterator it) const {return currentN != it.currentN;}
        Couple& value() const {return **currentN;}
        iterator& operator++() {currentN++; return *this;}

    };

    /**
     * @fn begin
     * @return un itérateur pointant sur le premier couple de la relation
     */

    iterator begin() const{ return iterator(couples); }

    /**
     * @fn end
     * @return un itérateur pointant sur le dernier couple de la relation
     */

    iterator end() const{return iterator(couples + nbCouple);}

};


/*******************************************************************
 ***                        Relation                             ***
 *******************************************************************/

/**
 * @class Relation
 * @brief
 * classe qui hérite de BaseRelation et qui rajoute un attribut booléen qui permet
 * de savoir si une relation est orientée ou non
 */

class Relation : public BaseRelation {
    bool oriented;
public:

    /**
     * @fn Relation
     * @param d = description de la relation
     * @param t = titre de la relation
     * @brief constructeur de relation
     */
    Relation(const QString & d, const QString& t) : BaseRelation(t,d), oriented(true) {}

    /**
     * @fn Relation
     * @param d = description de la relation
     * @param t = titre de la relation
     * @param o = détermine si la relation est orientée ou non
     */

    Relation(const QString & d, const QString& t, bool o) : BaseRelation(t,d), oriented(o) {}

    /**
     * @fn setOriented
     *
     * @brief permet de modifier la valeur du booléen oriented
     */

    void setOriented(){oriented= !oriented;}

    /**
     * @fn getOriented
     * @return la valeur du booléen oriented
     */
    bool getOriented() const {return oriented ;}
    ~Relation() {}


};


/*******************************************************************
 ***                        Decorateur                           ***
 *******************************************************************/
/*
class Decorateur : public BaseRelation {
    BaseRelation& base;
public:
    Decorateur( const QString& d, BaseRelation& b) : BaseRelation(d), base(b) {}
    ~Decorateur()=0;
};
*/


/*******************************************************************
 ***                           Référence                         ***
 *******************************************************************/

/**
 * @class Référence
 * @brief
 * classe qui hérite de BaseRelation, est orientée, qui dispose d'une instance unique et ne peut être
 * supprimée
 *
 */

class Reference : public BaseRelation {

private:

    static Reference* instance;

    /**
     * @fn Reference
     *@brief  constructeur de Référence dont, on impose le titre ainsi que la description
     */

    Reference() : BaseRelation("Ensemble des notes référérençant d'autres notes via la notation \{id}","Référence") {}
    ~Reference() {}



public:

    /**
     * @fn getInstance
     * @return l'instance unique de Référence
     */
    static Reference* getInstance();
    /**
     * @fn libererInstance
     * @brief permet de supprimer l'instance unique de référence
     */

    static void libererInstance();

    /**
     * @fn chercherReference
     * @brief vide le tableau de couple de la table de référence puis
     * parcourt les différents champs de type QString de toutes les notes
     * du notesmanager afin de trouver les références faites sous
     * la forme \{id}
     */

    void chercherReference();

    /**
     * @fn addCoupleReference
     * @brief Si une note possède un champ faisant référence à une autre note,
     * on récupère cette note ainsi que l'entier qui correspond à l'id de la
     * note référencée et on les ajoute à la relation référence
     */

    void addCoupleReference(Note&,int);

    /**
     * @brief chercherCouple
     * @param n = note dont on cherches les occurences dans les couples de Référence
     * fonction permettant de rechercher les occurences d'une note passée en argument dans
     * l'ensemble des couples d ela table Référence
     */


    void chercherCouple(Note*n);

    /**
     * @brief checkIfInReference
     * @param note dont on cherche à savoir si elle est référencée ou non
     * @return true si la note transmise en paramètre est référencée, false sinon
     *
     * fonction que l'on utilise pour vérifier si une note est référecée par une autre ou non
     */

    bool checkIfInReference(Note*);

    //void saveRef();
    //void loadRef(QString f);
    //void loadCouple(QXmlStreamReader& xml);


};


#endif
