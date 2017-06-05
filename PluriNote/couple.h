#ifndef couple_h
#define couple_h
#include "note.h"

/********************************************************************
 ***                        Couple                                ***
 ********************************************************************/


class Couple {
private:
    QString label;
    Note* note1;
    Note* note2;
public:
    Couple(const QString& l,Note* n1, Note* n2) :label(l), note1(n1), note2(n2) {}
    Note* getNote1() const  {return note1;}
    Note* getNote2() const {return note2;}
    const QString& getLabel() const {return label;}
    void setLabel(const QString & l) {label =l;}

};

#endif
