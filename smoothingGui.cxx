#include "smoothingGui.h"

smoothingGui::smoothingGui(QWidget * parent , Qt::WFlags f  ): QMainWindow(parent, f)
{
    setupUi(this);

    m_NumberOfMesh = 0;
    m_MeshSelected = 0;

    QObject::connect( pushButtonQuit , SIGNAL( clicked() ) , this , SLOT( pushButtonQuitClicked() ) );
    QObject::connect( pushButtonRun , SIGNAL( clicked() ) , this , SLOT( applySmoothing() ) );
    QObject::connect( spinBoxIteration , SIGNAL( valueChanged( int ) ) , this , SLOT( ChangeValueSmoothing() ) );
    QObject::connect( checkBoxState , SIGNAL( stateChanged( int ) ) , this , SLOT( ChangeStateSmoothing() ) );
    QObject::connect( listWidgetLoadedMesh , SIGNAL( itemClicked( QListWidgetItem* ) ) , this , SLOT( ChangeMeshSelected() ) );
}

void smoothingGui::setMeshList( std::vector <std::string> MeshList )
{
   m_MeshList = MeshList;
}

void smoothingGui::setWindow( meshQtDisplay WindowMesh )
{
   m_MyWindowMesh = WindowMesh;
}

void smoothingGui::initialization()
{
    listWidgetLoadedMesh -> clear();

    m_NumberOfMesh = m_MeshList.size();

    int IndiceOfMesh;

    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh ++ )
    {
        m_NumberOfIterationList.push_back( 100 );
        m_DoSmoothList.push_back( false );
        listWidgetLoadedMesh -> addItem( m_MeshList[ IndiceOfMesh ].c_str() );
    }
}

void smoothingGui::pushButtonQuitClicked()
{
    std::cout << " in smoothingGui : quit " << std::endl;
    close();
}

void smoothingGui::ChangeMeshSelected()
{
   m_MeshSelected = listWidgetLoadedMesh -> currentRow();

   spinBoxIteration -> setValue( m_NumberOfIterationList[ m_MeshSelected ] );
   checkBoxState -> setChecked( m_DoSmoothList[ m_MeshSelected ] );
}

void smoothingGui::ChangeValueSmoothing()
{
    m_NumberOfIterationList[ m_MeshSelected ] = spinBoxIteration -> value();
    m_MyWindowMesh.setNumberOfIteration( m_MeshSelected , m_NumberOfIterationList[ m_MeshSelected ] );
}

void smoothingGui::ChangeStateSmoothing()
{
    if( checkBoxState -> isChecked() )
    {
        m_DoSmoothList[ m_MeshSelected ] = true;
    }
    else
    {
        m_DoSmoothList[ m_MeshSelected ] = false;
    }
    m_MyWindowMesh.setSmoothing( m_MeshSelected , m_DoSmoothList[ m_MeshSelected ] );
}

void smoothingGui::applySmoothing()
{
    std::cout << " in smoothingGui : run " << std::endl;
    m_MyWindowMesh.updateSmoothing();
    m_MyWindowMesh.windowUpdate();
}
