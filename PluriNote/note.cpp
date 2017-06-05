#ifndef note_cpp
#define note_cpp
#include "note.h"
#endif


/**************************************************************
***                        Clone                            ***
***************************************************************/

int Note::idIterator = 0;

Task* Task::clone(){return new Task(*this);}
Article* Article::clone(){return new Article(*this);}
Image* Image::clone(){return new Image(*this);}
Audio* Audio::clone(){return new Audio(*this);}
Video* Video::clone(){return new Video(*this);}

