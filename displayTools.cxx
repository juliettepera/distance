#include "displayTools.h"

displayTools::displayTools( int Indice )
{
    m_Indice = Indice;

    m_PolyData = vtkSmartPointer <vtkPolyData>::New();

    m_Mapper = vtkSmartPointer <vtkPolyDataMapper>::New() ;
    m_Actor = vtkSmartPointer <vtkActor>::New() ;

    m_Lut = vtkSmartPointer <vtkColorTransferFunction>::New();
    m_Sampler = vtkSmartPointer <vtkPolyDataPointSampler>::New();
    m_Filter = vtkSmartPointer <vtkSmoothPolyDataFilter>::New();

    m_Opacity = 1.0;

    m_Red = rand()/(double)RAND_MAX  ; m_Green = rand()/(double)RAND_MAX  ; m_Blue = rand()/(double)RAND_MAX ;

    m_Smoothing = false;
    m_NumberOfIterationSmooth = 100;

    m_Density = 0.5;
    m_Type = 1;

    m_Reference = false;
}


//************************************** CHANGE THE DIFFERENT ATTRIBUTS *****************************************
void displayTools::setName(std::string Name )
{
    m_Name = Name;
}

void displayTools::setPolyDataError( vtkSmartPointer <vtkPolyData> PolyData )
{
    m_PolyDataError = vtkSmartPointer <vtkPolyData>::New();
    m_PolyDataError = PolyData;
}

void displayTools::setLut( vtkSmartPointer <vtkColorTransferFunction> Lut )
{
    m_Lut = Lut;
}

//************************************** CHANGE THE DIFFERENT PARAMETERS *****************************************
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

void displayTools::setDensity( double Density )
{
    std::cout << " set density " << std::endl;
    m_Density = Density;
}

void displayTools::setType( int Type )
{
    std::cout << " set type " << std::endl;
    m_Type = Type;
}


//**************************************** GET THE DIFFERENT ATTRIBUTS ******************************************
std::string displayTools::getName()
{
    return m_Name;
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

vtkSmartPointer<vtkPolyDataPointSampler> displayTools::getSampler()
{
    return m_Sampler;
}

//**************************************** GET THE DIFFERENT PARAMETERS ******************************************
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

int displayTools::getType()
{
    return m_Type;
}


//************************************************* INITIALIZATION ************************************************
void displayTools::initialization()
{
    std:: cout << "initialization()" << std::endl;
    vtkSmartPointer <vtkPolyDataReader> Reader = vtkSmartPointer <vtkPolyDataReader>::New();

    Reader -> SetFileName( m_Name.c_str() );
    Reader -> Update();

    m_PolyData = Reader -> GetOutput();

    m_Mapper -> SetInputData( m_PolyData );

    m_Actor -> SetMapper( m_Mapper );

    updateActorProperties();
}


//*********************************************** UPDATE PARAMETERS ***********************************************
void displayTools::updateActorProperties()
{
    m_Actor -> GetProperty() -> SetOpacity( m_Opacity );
    m_Actor -> GetProperty() -> SetColor( m_Red , m_Green , m_Blue );
}

void displayTools::updateDisplayProperties()
{
    std::cout << "updateDisplayProperties()" << std::endl;

    vtkSmartPointer <vtkProperty> Property = vtkSmartPointer <vtkProperty>::New();
    Property = m_Actor->GetProperty();

    if( m_Type == 1 )
    {
        Property -> SetRepresentationToSurface();
    }
    else if( m_Type == 2 )
    {
        Property -> SetRepresentationToPoints();
    }
    else if( m_Type == 3 )
    {
        Property -> SetRepresentationToWireframe();
    }
}

//********************************************** CHANGE MAPPER INPUT ********************************************
void displayTools::changeMapperInputPort( int Choice )
{
    std::cout << "changeMapperInputPort()" << std::endl;

    m_Mapper = vtkSmartPointer <vtkPolyDataMapper>::New();

    if( Choice == 1 )
    {
        if( m_Reference == false )
        {
            m_Mapper -> SetInputData( m_PolyData );
        }
        else if( m_Reference == true )
        {
            m_Mapper -> SetInputData( m_PolyDataError );
            m_Mapper -> SetLookupTable( m_Lut );
        }
    }
    else if( Choice == 2 )
    {
        m_Mapper -> SetInputData( m_Filter -> GetOutput() );
        if( m_Reference == true )
        {
            m_Mapper -> SetLookupTable( m_Lut );
        }
    }
    else if( Choice == 3 )
    {
        m_Mapper -> SetInputData( m_Sampler -> GetOutput() );
        if( m_Reference == true )
        {
            m_Mapper -> SetLookupTable( m_Lut );
        }
    }

    m_Actor -> SetMapper( m_Mapper );
    std::cout << "done "<< std::endl;

}

//*********************************************** CHANGE TYPE OF DATA*********************************************
void displayTools::changeInputData( bool Choice )
{
    m_Reference = Choice;
    changeMapperInputPort( 1 );
}

//*********************************************** UPDATE THE FILTER **********************************************
void displayTools::changeDataFilter()
{
   if( m_Reference == true )
   {
        m_Filter -> SetInputData( m_PolyDataError );
   }
   else if( m_Reference == false )
   {
       m_Filter -> SetInputData( m_PolyData );
   }
   m_Filter -> SetNumberOfIterations( m_NumberOfIterationSmooth );
   m_Filter -> Update();
}


//*********************************************** UPDATE THE SAMPLER **********************************************
void displayTools::changeDataSampler()
{
   std::cout << "changeDataSampler()" << std::endl;

   if( m_Reference == true )
   {
        m_Sampler -> SetInputData( m_PolyDataError );
   }
   else if( m_Reference == false )
   {
       m_Sampler -> SetInputData( m_PolyData );
   }
   m_Sampler -> SetDistance( m_Density );
   m_Sampler -> Update();
}

/*void displayTools::updateSamplerSetup()
{
    if( m_Type == 1 )
    {
        std::cout << " surface -> pas de downsampling " << std::endl;
    }
    else if( m_Type == 2 )
    {
        std::cout << " points -> downsampling " << std::endl;

        if( m_Reference == false )
        {
            std::cout << " data normal en entree " << std::endl;
            m_Sampler -> SetInputData( m_PolyData );
        }
        else if( m_Reference == true )
        {
            std::cout << " data error en entree " << std::endl;
            m_Sampler -> SetInputData( m_PolyDataError );
        }
        m_Sampler -> SetDistance( m_Density );
        m_Sampler -> Update();
    }
    else if( m_Type == 3 )
    {
        std::cout << " wireframe -> je sais pas encore comment downsampler " << std::endl;
    }
}*/



