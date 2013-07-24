// My library
#include "distanceGui.h"
#include "distanceDisplay.h"


//************************************************* CLASS ****************************************************
distanceGui::distanceGui(std::string meshA, std::string meshB)
{
    // to display the window?
    setupUi(this);
           
    //******** GLOBAL VARIABLES ********
    m_meshA = meshA;
    m_meshB = meshB;
    m_distance = 0;

    //******** CONNECTION ********
    //MESH A BUTTON TO MESH A LINE EDIT
    QObject::connect( buttonMeshA , SIGNAL( clicked() ) , this , SLOT( OpenMeshBrowseWindowA() ) );
            
    //OUTPUT BUTTON TO OUTPUT LINE EDIT
    QObject::connect( buttonMeshB , SIGNAL( clicked() ) , this , SLOT( OpenMeshBrowseWindowB() ) );
    
    //DISPLAY BUTTON 
    QObject::connect( buttonDisplay , SIGNAL( clicked() ) , this , SLOT( Display() ) );

    //RADIO BUTTON A to B
    QObject::connect( radioAtoB , SIGNAL(clicked() ) , this , SLOT( ChangeValue() ) );

    //RADIO BUTTON B to A
    QObject::connect( radioBtoA , SIGNAL(clicked() ) , this , SLOT( ChangeValue() ) );

    //RADIO BUTTON B to A
    QObject::connect( radioBoth , SIGNAL(clicked() ) , this , SLOT( ChangeValue() ) );

    //APPLY BUTTON 
    QObject::connect( buttonApply , SIGNAL( clicked() ) , this , SLOT( ApplyDistance() ) );
                
    //QUIT BUTTON 
    QObject::connect( buttonQuit , SIGNAL( clicked() ) , qApp , SLOT( quit() ) );
          
    //IF THE PARAMETERS ARE ALLREADY GIVEN BY THE USER
    if( !meshA.empty() )
    {
      lineMeshA->setText( QString( meshA.c_str() ) );
    }
          
    if( !meshB.empty() )
    {
      lineMeshB->setText( QString( meshB.c_str() ) );
    }
                                                                              
}

//************************************************* SLOTS ****************************************************   
// display on the edit line "lineMeshA" the file selected
void distanceGui::OpenMeshBrowseWindowA() 
{
      QString browseMeshA = QFileDialog::getOpenFileName( this , "Open mesh A" , QString() , "vtk mesh (*.vtk)" );
      if( !browseMeshA.isEmpty() )
      {
            lineMeshA -> setText( browseMeshA );
      }
      m_meshA = ( lineMeshA -> text() ).toStdString();
}

// display on the edit line "lineMeshB" the file selected
void distanceGui::OpenMeshBrowseWindowB() 
{
      QString browseMeshB = QFileDialog::getOpenFileName( this , "Open mesh B" , QString() , "vtk mesh (*.vtk)" );
      if( !browseMeshB.isEmpty() )
      {
            lineMeshB -> setText( browseMeshB );
      }
      m_meshB = ( lineMeshB -> text() ).toStdString();
}

// display the two files selected on the box "meshWidget"
void distanceGui::Display()
{
    if( m_meshA != "\0" && m_meshB != "\0")
    {
        //QVTKWIDGETS
        QVTKWidget *widgetMeshA = new QVTKWidget( this -> scrollAreaMeshA );
        QVTKWidget *widgetMeshB = new QVTKWidget( this -> scrollAreaMeshB );
        QVTKWidget *widgetMeshBoth = new QVTKWidget( this -> scrollAreaBoth );

        //SIZES
        //widgetMeshA->resize( scrollAreaMeshA->maximumWidth() , scollAreaMeshA->maximumHeight() );
        // set size automaticly ??????
        QSize sizeA( 351 , 311 );
        QSize sizeBoth( 711 , 381 );

        //VISUALISATION
        windowInitialisation( widgetMeshA , m_meshA , sizeA );
        windowInitialisation( widgetMeshB , m_meshB , sizeA );
        windowInitialisation( widgetMeshBoth , m_meshB, sizeBoth );
     }
}

// change the value of m_distance
void distanceGui::ChangeValue()
{
    if( this -> radioAtoB -> isChecked() )
    {
        m_distance = 1;
    }
    if( this -> radioBtoA -> isChecked() )
    {
        m_distance = 2;
    }
    if( this -> radioBoth -> isChecked() )
    {
        m_distance = 3;
    }
}


// apply the good calculated distance
void distanceGui::ApplyDistance()
{

    //QTextBrowser *widgetText = new QTextBrowser( this -> scrollAreaUser );

    switch( m_distance )
    {
        case 0:
            std::cout << std::endl << "you have to select the distance you want to compute " << std::endl;
            break;

        case 1:
            std::cout << std::endl << "you want to compute the A to B distances " << std::endl;
            break;

        case 2:
            std::cout << std::endl << "you want to compute the B to A distances " << std::endl;
            break;

        case 3:
            std::cout << std::endl << "you want to compute both distances " << std::endl;
            break;
    }
}




