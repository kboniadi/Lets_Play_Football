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
    QFontDatabase::addApplicationFont(":/resource/fonts/OldSportAthletic.ttf");
    QFontDatabase::addApplicationFont(":/resource/fonts/Quicksand_Bold_Oblique.otf");
    QFontDatabase::addApplicationFont(":/resource/fonts/Mont.otf");
    QFontDatabase::addApplicationFont(":/resource/fonts/OldSansBlack.ttf");
    QFontDatabase::addApplicationFont(":/resource/fonts/primetime.ttf");
    QFontDatabase::addApplicationFont(":/resource/fonts/Steinberg.ttf");
}
