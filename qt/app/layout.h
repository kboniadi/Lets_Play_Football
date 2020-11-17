#ifndef LAYOUT_H
#define LAYOUT_H

#include <QDebug>
#include <QFontDatabase>


class Layout
{
public:
    /*!
     * @brief Creates one instance of the layout
     * @return Pointer to the instance of the layout class
     */
    static Layout* instance();

    Layout(); // constructor

    /*!
     * @brief imports application fonts to current system
     */
    void importFonts();

    /*!
     * @brief Destructor
     */
    ~Layout();
};

#endif // LAYOUT_H
