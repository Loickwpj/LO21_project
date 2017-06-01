#include "Note.h"

/**************************************************************
 ***                        Note                            ***
 ***************************************************************/


string* Note::ids = new string [5];
unsigned int Note::nbId =0;
unsigned int Note::nbMaxId =5;

static Iterator getIterator() const{return Iterator(ids, nbId);}

void addID(const string & id){
    if(nbId == nbMaxId){
        string* old_ids = ids;
        ids = new string[nbIdMax+5];
        for(int i = 0; i < nbId; i++){
            ids[i] = old_ids[i];
        }
    nbMaxId += 5;
    delete[] old_ids;
    }
    ids[nbId++]=id;
}



/**************************************************************
***                        Clone                            ***
***************************************************************/

Tache* Tache::clone(){return new Tache(*this);}
Article* Article::clone(){return new Article(*this);}
Image* Image::clone(){return new Image(*this);}
Audio* Audio::clone(){return new Audio(*this);}
Video* Video::clone(){return new Video(*this);}

