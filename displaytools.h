#ifndef DISPLAYTOOLS_H
#define DISPLAYTOOLS_H

// VTK libraries
#include <QVTKWidget.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkSmoothPolyDataFilter.h>
#include <vtkPolyDataWriter.h>

// Other Libraries
#include <string>
#include <iostream>
#include <vector>

class displayTools
{

    public:
        displayTools();

        void setName(std::string Name);
        void setReader( vtkSmartPointer <vtkPolyDataReader> Reader );
        void setMapper( vtkSmartPointer <vtkPolyDataMapper> Mapper );
        void setActor( vtkSmartPointer <vtkActor> Actor );
        void setPolyData( vtkSmartPointer <vtkPolyData> PolyData );
        void setOpacity( double Opacity );
        void setRed( double Red );
        void setBlue( double Blue );
        void setGreen( double Green );

        void getName(std::string &Name);
        vtkSmartPointer<vtkPolyDataReader> getReader();
        void getMapper(vtkSmartPointer<vtkPolyDataMapper> &Mapper );
        vtkSmartPointer<vtkActor> getActor();
        void getPolyData(vtkSmartPointer<vtkPolyData> &PolyData );
        void getOpacity( double &Opacity );
        void getRed( double &Red );
        void getBlue( double &Blue );
        void getGreen( double &Green );

        void initialization();

    private:
        vtkSmartPointer <vtkPolyData> m_PolyData;
        vtkSmartPointer <vtkPolyDataReader> m_Reader;
        vtkSmartPointer <vtkPolyDataMapper> m_Mapper;
        vtkSmartPointer <vtkActor> m_Actor;

        std::string m_Name;

        double m_Opacity;
        double m_Red;
        double m_Blue;
        double m_Green;

};

#endif
