#include <QtGui/QApplication>
#include <comparison.h>

using namespace std;

comparison *comp;

string ref_img;
string comp_img;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    /*if(argc < 3){
        cout << "images not provided" << endl;
        cout << "usage is ./imagecomp </path/to/refimg> </path/to/comp_img>" << endl;
        return -1;
    }*/

    Task* task = new Task();

    comp = new comparison();

    char* c_ref = argv[1];
    char* c_comp = argv[2];

    ref_img = (string)c_ref;
    comp_img = (string)c_comp;

    QObject::connect(task, SIGNAL(finished()),&app, SLOT(quit()));

    QTimer::singleShot(10, task, SLOT(run()));

    return app.exec();
}


void Task::run()
{
    if(!comp->loadimages(ref_img, comp_img)){
        cout << "image load failed, check paths and format" << endl;
        cout << "exiting..." << endl;
        QCoreApplication::instance()->quit();
    }

    comp->compareimages();

    QCoreApplication::instance()->quit();

    return;
}
