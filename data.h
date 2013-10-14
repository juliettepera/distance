#ifndef DATAM_H
#define DATAM_H

/* CLASS WHERE ALL THE DATA NEEDED FOR ONE FILE ARE STOCKED --> NO PROCESSING DONE HERE
 *  -> NAME
 *  -> POLYDATA ( NORMAL + ERROR )
 *  -> MAPPER
 *  -> ACTOR
 *  -> FILE PROPERTIES
 *  -> SMOOTHING FILTER
 *  -> SMOOTHING PARAMETERS
 *  -> DOWNSAMPLING FILTER
 *  -> DOWNSAMPLING PARAMETERS
 *  -> ERROR COMPUTER ( COMMING SOON... )
 *  -> ERROR PARAMETERS
 */

// VTK libraries
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkPolyDataReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkSmoothPolyDataFilter.h>
#include <vtkDecimatePro.h>
#include <vtkColorTransferFunction.h>
#include <vtkProperty.h>
#include <vtkTriangleFilter.h>
#include <vtkAbstractArray.h>

// QT libraries
#include <QMessageBox>

// OTHER libraries
#include <string>
#include <iostream>
#include <vector>



class dataM
{
    public:
        dataM( std::string Name = "" );
        void initialization();
        void updateActorProperties();
        int updateTypeOfDisplay();
        int changeMapperInput( int Choice );
        void changeActivScalar();

        // Set the basic data
            void setName( std::string Name );
            void setPolyData( vtkSmartPointer<vtkPolyData> PolyData );

        // Get the basic data
            std::string getName();
            vtkSmartPointer<vtkPolyDataMapper> getMapper();
            vtkSmartPointer <vtkActor> getActor();
            void getPolyData(vtkSmartPointer<vtkPolyData> &NewData);

        // Set the File properties
            void setOpacity( double Opacity );
            void setColor( double Red , double Green , double Blue );
            void setType( int Type );

        // Get the file properties
            double getOpacity();
            double getRed();
            double getBlue();
            double getGreen();
            int getType();

        // Set the smoothing parameters
            void setNumberOfIterationSmooth( int Number );

        // Get the smoothing parameters
            int getNumberOfIterationSmooth();
            vtkSmartPointer <vtkSmoothPolyDataFilter> getSmoother();

        // Set the downSampling parameters
            void setDecimate( double Decimate );

        // Get the downSampling parameters
            double getDecimate();
            vtkSmartPointer <vtkDecimatePro> getDecimer();

        // Set the error parameters
            void setMinSamplingFrequency(int MinSamplingFrequency );
            void setSamplingStep( double SamplingStep );
            void setSignedDistance( bool SignedDistance );
            void setDisplayError( bool DisplayError );
            void setPolyDataError( vtkSmartPointer <vtkPolyData> PolyDataError );
            void setLut( vtkSmartPointer <vtkColorTransferFunction> Lut );

        // Get the error parameters
            int getMinSamplingFrequency();
            double getSamplingStep();
            bool getSignedDistance();
            bool getDisplayError();
            vtkSmartPointer <vtkPolyData> getPolyDataError();
            vtkSmartPointer <vtkColorTransferFunction> getLut();

    private:
        std::string m_Name;
        vtkSmartPointer <vtkPolyDataMapper> m_Mapper;
        vtkSmartPointer <vtkActor> m_Actor;
        vtkSmartPointer <vtkPolyData> m_PolyData;

        double m_Opacity;
        double m_Red;
        double m_Blue;
        double m_Green;
        int m_Type;

        int m_NumberOfIterationSmooth;
        vtkSmartPointer <vtkSmoothPolyDataFilter> m_Smoother;

        double m_Decimate;
        vtkSmartPointer <vtkDecimatePro> m_Decimer;

        bool m_DisplayError;
        int m_MinSamplingFrequency;
        double m_SamplingStep;
        bool m_SignedDistance;
        vtkSmartPointer <vtkPolyData> m_PolyDataError;
        vtkSmartPointer <vtkColorTransferFunction> m_Lut;
};

#endif
