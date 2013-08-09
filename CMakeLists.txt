# GenerateCLP_DIR    
# /devel/linux/SlicerExecutionModel/SlicerExecutionModel-build_ITKv4.3.0_v3Compatible_linux64/GenerateCLP                                                                                                   
# QT4_DIR
# /tools/Qt/Qt4.8.2/Qt4.8.2_linux64_THL                                                                                                                                                                     
# QT_DIR
# /tools/Qt/Qt4.8.2/Qt4.8.2_linux64_THL 
# QT_QMAKE_EXECUTABLE
# /NIRAL/tools/Qt/Qt4.8.2/Qt4.8.2_linux64_THL/bin/qmake                                                                                                                                                     
# VTK_DIR
# /tools/VTK/VTK_5.10.1/VTK_5.10.1_X64_dyn_release_Qt4.8.2_Python/lib/vtk-5.10 



# minimum version required
CMAKE_MINIMUM_REQUIRED( VERSION 2.6 ) 

# name of the project
project( distanceGui )

# find the GenerateCLP headers
FIND_PACKAGE( GenerateCLP REQUIRED )
INCLUDE( ${GenerateCLP_USE_FILE} )

# find the VTK headers
FIND_PACKAGE( VTK )
INCLUDE( ${VTK_USE_FILE} )

# find the QT4 headers
FIND_PACKAGE( Qt4 REQUIRED ) 
INCLUDE( ${QT_USE_FILE} )

# include the directories for the binary and sources files
INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}  ${QT_INCLUDE_DIR} )

# ?????
ADD_DEFINITIONS( -DQT_GUI_LIBS -DQT_CORE_LIB -DQT3_SUPPORT )

# generate moc and ui files
QT4_WRAP_CPP( QtProject_HEADERS_MOC distanceGui.h )
QT4_WRAP_UI( UI_FILES distanceGui.ui )

# set the sources files
SET( Dsources main.cxx distanceGui.h distanceGui.cxx meshQtDisplay.cxx meshQtDisplay.h distanceCompute.cxx distanceCompute.h ${QtProject_HEADERS_MOC} ${UI_FILES} )

# generate the CLP file
GENERATECLP( Dsources main.xml )

# generate the executable
ADD_EXECUTABLE( distance ${Dsources} )

# link the libraries to the executable
TARGET_LINK_LIBRARIES( distance ${QT_LIBRARIES} ${VTK_LIBRARIES} )
