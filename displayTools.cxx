#include "displayTools.h"

displayTools::displayTools( int Indice )
{
    m_Indice = Indice;

    m_PolyData = vtkSmartPointer <vtkPolyData>::New();
    m_Reader = vtkSmartPointer <vtkPolyDataReader>::New() ;
    m_Mapper = vtkSmartPointer <vtkPolyDataMapper>::New() ;
    m_Actor = vtkSmartPointer <vtkActor>::New() ;
    m_Filter = vtkSmartPointer <vtkSmoothPolyDataFilter>::New();
    m_Lut = vtkSmartPointer <vtkColorTransferFunction>::New();

    m_Opacity = 1.0;

    m_Red = rand()/(double)RAND_MAX  ; m_Green = rand()/(double)RAND_MAX  ; m_Blue = rand()/(double)RAND_MAX ;
    m_Smoothing = false;
    m_NumberOfIterationSmooth = 100;

}


// **********************************************************************
void displayTools::setName(std::string Name )
{
    m_Name = Name;
}

void displayTools::setReader( vtkSmartPointer<vtkPolyDataReader> Reader )
{
    m_Reader = Reader;
}

void displayTools::setMapper( vtkSmartPointer<vtkPolyDataMapper> Mapper )
{
    m_Mapper = Mapper;
}

void displayTools::setActor( vtkSmartPointer<vtkActor> Actor)
{
    m_Actor = Actor;
}

void displayTools::setPolyData( vtkSmartPointer <vtkPolyData> PolyData )
{
    m_PolyData = PolyData;
}

void displayTools::setPolyDataError( vtkSmartPointer <vtkPolyData> PolyData )
{
    m_PolyDataError = vtkSmartPointer <vtkPolyData>::New();
    m_PolyDataError = PolyData;
}

void displayTools::setOpacity( double Opacity )
{
    m_Opacity = Opacity;
}

void displayTools::setColor( double Red , double Green , double Blue )
{
    m_Red = Red;
    m_Green = Green;
    m_Blue = Blue;
}

void displayTools::setSmoothing( bool Smoothing )
{
    m_Smoothing = Smoothing;
}

void displayTools::setNumberOfIterationSmooth( int Number )
{
    m_NumberOfIterationSmooth = Number;
}

void displayTools::setLut( vtkSmartPointer <vtkColorTransferFunction> Lut )
{
    m_Lut = Lut;
}

// **********************************************************************
std::string displayTools::getName()
{
    return m_Name;
}

vtkSmartPointer<vtkPolyDataReader> displayTools::getReader()
{
    return m_Reader;
}

vtkSmartPointer<vtkPolyDataMapper> displayTools::getMapper()
{
    return m_Mapper;
}

vtkSmartPointer<vtkActor> displayTools::getActor()
{
    return m_Actor;
}

vtkSmartPointer<vtkPolyData> displayTools::getPolyData()
{
    return m_PolyData;
}

vtkSmartPointer<vtkSmoothPolyDataFilter> displayTools::getFilter()
{
    return m_Filter;
}

double displayTools::getOpacity()
{
    return m_Opacity;
}

double displayTools::getRed()
{
    return m_Red;
}

double displayTools::getGreen()
{
    return m_Green;
}

double displayTools::getBlue()
{
    return m_Blue;
}

bool displayTools::getSmoothing()
{
    return m_Smoothing;
}

int displayTools::getNumberOfIterationSmooth()
{
    return m_NumberOfIterationSmooth;
}



// **********************************************************************
void displayTools::initialization()
{
    m_Reader -> SetFileName( m_Name.c_str() );
    m_Reader -> Update();

    m_PolyData = m_Reader -> GetOutput();

    m_Mapper -> SetInputData( m_PolyData );

    m_Actor -> SetMapper( m_Mapper );
    m_Actor -> GetProperty() -> SetOpacity( m_Opacity );
    m_Actor -> GetProperty() -> SetColor( m_Red , m_Green , m_Blue );
}

void displayTools::changeInputPort( vtkAlgorithmOutput* Input)
{
    m_Mapper -> SetInputConnection( Input );
    m_Actor -> SetMapper( m_Mapper );
}

void displayTools::changeInputData( bool Choice )
{
    m_Mapper = vtkSmartPointer <vtkPolyDataMapper>::New(); // choice 0 no setting of new lut creation of a new mapper for safety
    if( Choice == false )
    {
        m_Mapper->SetInputData( m_PolyData );
    }
    if( Choice == true )
    {
        m_Mapper -> SetInputData( m_PolyDataError );
        m_Mapper -> SetLookupTable( m_Lut );
    }
    m_Actor -> SetMapper( m_Mapper );

}

