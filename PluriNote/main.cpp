#include <QApplication>
#include <QWidget>
#include "note.h"
#include "noteediteur.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Video i("id1","titre1","desc1","image1");
    VideoEditeur e(&i);
    e.show();
    return app.exec();
}
