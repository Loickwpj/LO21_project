#ifndef couple_h
#define couple_h

#include "note.h"


/********************************************************************
 ***                        Couple                                ***
 ********************************************************************/

class Note;

class Couple {
private:
    QString label;
    Note* note1;
    Note* note2;
public:
    Couple(const QString& l,Note* n1, Note* n2) :label(l), note1(n1), note2(n2)  {}
    Couple() : label(""), note1(nullptr), note2(nullptr) {}
    Note* getNote1() const  {return note1;}
    Note* getNote2() const {return note2;}
    const QString& getLabel() const {return label;}



    void setLabel(const QString & l) {label =l;}
    void setNote1(Note* n) {note1=n;}
    void setNote2(Note* n) {note2=n;}

};

#endif
