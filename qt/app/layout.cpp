#include "layout.h"

Layout::Layout()
{

}

Layout::~Layout()
{
    // Output when layout closes{
    qDebug() << "Layout has been closed";
}

Layout* Layout::instance()
{
    // Create one and only one instance of the database
    static Layout instance;
    return &instance;
}

void Layout::importResources()
{
    QFontDatabase::addApplicationFont(":/resource/fonts/Freshman.ttf");
}
