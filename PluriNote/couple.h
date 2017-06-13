#ifndef couple_h
#define couple_h

/** @file couple.h
*/

#include "note.h"



/********************************************************************
 ***                        Couple                                ***
 ********************************************************************/

class Note;

/*! \class Couple
 * \brief Classe qui aggrège deux notes
 *
 * Les couples sont gérés par des relations
 *  et peuvent disposer d'un label éditable
 *
 */

class Couple {
private:
    QString label;
    Note* note1;
    Note* note2;
public:
    ///CONSTRUCTEURS

    /**
     * @brief Couple (constructeur)
     * @param l : label du couple
     * @param n1 : pointeur sur la première note du couple
     * @param n2 : pointeur sur la seconde note du couple
     *
     */
    Couple(const QString& l,Note* n1, Note* n2) :label(l), note1(n1), note2(n2)  {}

    /**
     * @brief Couple (constructeur par défaut)
     *
     * \return couple sans label dont les deux notes sont égalent au pointeur null
     */
    Couple() : label(""), note1(nullptr), note2(nullptr) {}

    ///ACCESSEURS

    /**
     * @brief getNote1
     * @return la première note du couple
     */
    Note* getNote1() const  {return note1;}

    /**
     * @brief getNote2
     * @return la seconde note du couple
     */
    Note* getNote2() const {return note2;}

    /**
     * @brief getLabel
     * @return le label d'un couple
     */
    const QString& getLabel() const {return label;}

    ///SET

    /**
     * @brief setLabel
     * @param l : la nouvelle valeur du label
     *
     * permet de modifier la valeur du label
     */
    void setLabel(const QString & l) {label =l;}

    /**
     * @brief setNote1
     * @param n : pointeur sur la nouvelle note 1 du couple
     *
     * permet de modifier la note 1 du couple
     */
    void setNote1(Note* n) {note1=n;}

    /**
     * @brief setNote2
     * @param n : pointeur sur la nouvelle note 2 du couple
     *
     * permet de modifier la note 2 du couple
     */

    void setNote2(Note* n) {note2=n;}

    ///SAVE
    void saveCouple(QXmlStreamWriter &stream) const;

};

#endif
