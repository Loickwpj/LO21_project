#ifndef couple_cpp
#define couple_cpp
#include "couple.h"
#endif

void Couple::saveCouple(QXmlStreamWriter &stream) const{
        stream.writeStartElement("couple");
        stream.writeTextElement("label", getLabel());
        stream.writeTextElement("id1", QString::number( getNote1()->getId() ));
        stream.writeTextElement("id2", QString::number( getNote2()->getId() ));
        stream.writeEndElement();
}


