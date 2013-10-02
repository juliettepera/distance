#include "smoothingGui.h"

smoothingGui::smoothingGui(QWidget * parent , Qt::WFlags f  ): QMainWindow(parent, f)
{
    setupUi(this);

    m_NumberOfMesh = 0;
    m_MeshSelected = -1;

    QObject::connect( pushButtonQuit , SIGNAL( clicked() ) , this , SLOT( pushButtonQuitClicked() ) );
    QObject::connect( pushButtonRun , SIGNAL( clicked() ) , this , SLOT( applySmoothing() ) );
    QObject::connect( spinBoxIteration , SIGNAL( valueChanged( int ) ) , this , SLOT( ChangeValueSmoothing() ) );
    QObject::connect( checkBoxDisplay , SIGNAL( toggled( bool ) ) , this , SLOT( DisplaySmoothing() ) );
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

void smoothingGui::setIcon( QIcon Visible , QIcon Unvisible )
{
   m_Visible = Visible;
   m_Unvisible = Unvisible;
}

void smoothingGui::initialization()
{
    listWidgetLoadedMesh -> clear();

    m_NumberOfMesh = m_MeshList.size();

    int IndiceOfMesh;

    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh ++ )
    {
        m_NumberOfIterationList.push_back( 500 );
        m_DoSmoothList.push_back( false );
        m_DisplayList.push_back( false );
        listWidgetLoadedMesh -> addItem( m_MeshList[ IndiceOfMesh ].c_str() );
    }

    checkBoxDisplay -> setEnabled( false );
    pushButtonRun -> setEnabled( false );
    spinBoxIteration -> setEnabled( false );

}

void smoothingGui::pushButtonQuitClicked()
{
    close();
}

void smoothingGui::ChangeMeshSelected()
{
    if( ! m_MeshList.empty() && m_NumberOfMesh != 0 )
    {
        m_MeshSelected = listWidgetLoadedMesh -> currentRow();

        spinBoxIteration -> setValue( m_NumberOfIterationList[ m_MeshSelected ] );
        checkBoxDisplay -> setChecked( m_DisplayList[ m_MeshSelected ] );
    }

    if( m_MeshSelected != -1 )
    {
        pushButtonRun -> setEnabled( ! m_DoSmoothList[ m_MeshSelected ] );
        spinBoxIteration -> setEnabled( true );
        checkBoxDisplay -> setEnabled( m_DoSmoothList[ m_MeshSelected ] );
    }
}

void smoothingGui::ChangeValueSmoothing()
{
    m_NumberOfIterationList[ m_MeshSelected ] = spinBoxIteration -> value();
    m_MyWindowMesh.setNumberOfIteration( m_MeshSelected , m_NumberOfIterationList[ m_MeshSelected ] );
    pushButtonRun -> setEnabled( true );
}

void smoothingGui::DisplaySmoothing()
{
    if( m_DoSmoothList[ m_MeshSelected ] != false )
    {
        if( checkBoxDisplay -> isChecked() )
        {
            m_DisplayList[ m_MeshSelected ] = true;
            listWidgetLoadedMesh -> item( m_MeshSelected ) -> setIcon( m_Visible );
        }
        else if( ! checkBoxDisplay -> isChecked() )
        {
            m_DisplayList[ m_MeshSelected ] = false;
            listWidgetLoadedMesh -> item( m_MeshSelected ) -> setIcon( m_Unvisible );
        }

        m_MyWindowMesh.setSmoothing( m_MeshSelected , m_DisplayList[ m_MeshSelected ] );
        m_MyWindowMesh.updateSmoothing();
        m_MyWindowMesh.windowUpdate();
    }
}

void smoothingGui::applySmoothing()
{
    m_DoSmoothList[ m_MeshSelected ] = true;
    m_MyWindowMesh.setSmoothing( m_MeshSelected , m_DoSmoothList[ m_MeshSelected ] );

    checkBoxDisplay -> setChecked( true );
    m_DisplayList[ m_MeshSelected ] = true;

    listWidgetLoadedMesh -> item( m_MeshSelected ) -> setIcon( m_Visible );

    checkBoxDisplay -> setEnabled( true );
    pushButtonRun -> setEnabled( false );

    m_MyWindowMesh.updateSmoothing();
    m_MyWindowMesh.windowUpdate();
}
