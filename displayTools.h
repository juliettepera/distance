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
#include <vtkSmoothPolyDataFilter.h>
#include <vtkColorTransferFunction.h>
#include <vtkPolyDataPointSampler.h>

// Other Libraries
#include <string>
#include <iostream>
#include <vector>

class displayTools
{

    public:
        displayTools( int Indice = 0 );

        void setName( std::string Name );
        void setPolyDataError( vtkSmartPointer <vtkPolyData> PolyData );

        void setOpacity( double Opacity );
        void setColor( double Red , double Green , double Blue );
        void setSmoothing( bool Smoothing );
        void setNumberOfIterationSmooth( int Number );
        void setLut( vtkSmartPointer <vtkColorTransferFunction> Lut );
        void setDensity( double Density );
        void setType( int Type );

        std::string getName();
        vtkSmartPointer<vtkPolyDataMapper> getMapper();
        vtkSmartPointer <vtkActor> getActor();
        vtkSmartPointer<vtkPolyData> getPolyData();
        vtkSmartPointer<vtkSmoothPolyDataFilter> getFilter();
        vtkSmartPointer<vtkPolyDataPointSampler> getSampler();
        double getOpacity();
        double getRed();
        double getBlue();
        double getGreen();
        bool getSmoothing();
        int getNumberOfIterationSmooth();
        int getType();

        void initialization();

        void changeMapperInputPort( int Choice );
        void changeInputData( bool Choice );

        void updateActorProperties();
        void updateDisplayProperties();

        //void updateSamplerSetup();
        void changeDataSampler();
        void changeDataFilter();
        //vtkAlgorithmOutput *getOutputFilter();

    private:

        int m_Indice;
        std::string m_Name;

        vtkSmartPointer <vtkPolyData> m_PolyData;
        vtkSmartPointer <vtkPolyData> m_PolyDataError;

        vtkSmartPointer <vtkPolyDataMapper> m_Mapper;
        vtkSmartPointer <vtkActor> m_Actor;

        vtkSmartPointer <vtkSmoothPolyDataFilter> m_Filter;
        vtkSmartPointer <vtkPolyDataPointSampler> m_Sampler;

        vtkSmartPointer <vtkColorTransferFunction> m_Lut;

        double m_Opacity;
        double m_Red;
        double m_Blue;
        double m_Green;
        bool m_Smoothing;
        int m_NumberOfIterationSmooth;
        double m_Density;
        int m_Type;

        bool m_Reference;

};

#endif
