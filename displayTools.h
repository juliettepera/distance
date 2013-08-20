#ifndef DISPLAYTOOLS_H
#define DISPLAYTOOLS_H

// VTK libraries
#include <vtkSmartPointer.h>
#include <vtkPolyDataReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkProperty.h>
#include <vtkCamera.h>

// Other Libraries
#include <string>
#include <iostream>
#include <vector>

class displayTools
{

    public:
        displayTools( int Indice );

        void setName(std::string Name);
        void setReader( vtkSmartPointer <vtkPolyDataReader> Reader );
        void setMapper( vtkSmartPointer <vtkPolyDataMapper> Mapper );
        void setActor( vtkSmartPointer <vtkActor> Actor );
        void setPolyData( vtkSmartPointer <vtkPolyData> PolyData );
        void setOpacity( double Opacity );
        void setColor( double Red , double Green , double Blue );
        void setSmoothing( bool Smoothing );
        void setNumberOfIterationSmooth( int Number );

        std::string getName();
        vtkSmartPointer <vtkPolyDataReader> getReader();
        vtkSmartPointer<vtkPolyDataMapper> getMapper();
        vtkSmartPointer <vtkActor> getActor();
        vtkSmartPointer<vtkPolyData> getPolyData();
        double getOpacity();
        double getRed();
        double getBlue();
        double getGreen();
        bool getSmoothing();
        int getNumberOfIterationSmooth();

        void initialization();
        void changeInputPort( vtkAlgorithmOutput* Input);

    private:

        int m_Indice;

        vtkSmartPointer <vtkPolyData> m_PolyData;
        vtkSmartPointer <vtkPolyDataReader> m_Reader;
        vtkSmartPointer <vtkPolyDataMapper> m_Mapper;
        vtkSmartPointer <vtkActor> m_Actor;
        std::string m_Name;

        double m_Opacity;
        double m_Red;
        double m_Blue;
        double m_Green;
        bool m_Smoothing;
        int m_NumberOfIterationSmooth;

};

#endif
