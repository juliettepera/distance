#ifndef MESHQTDISPLAY_H
#define MESHQTDISPLAY_H

// VTK libraries
#include <QVTKWidget.h>

// Qt libraries

// My libraries
#include "meshDisplay.h"

class meshQtDisplay: public meshDisplay
{
    public:
        meshQtDisplay( QWidget *MeshWidget , int NumberOfMesh, std::vector<std::string> MeshList );
        virtual void createLinks( int IndiceOfMesh );

    private:
        QVTKWidget *m_MeshWidget;

};

#endif
