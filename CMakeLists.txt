#/tools/Qt/Qt4.8.2/Qt4.8.2_linux64_THL/bin/qmake                                                                                                                                                           
#/tools/VTK/VTK_6.0.0/VTK_6.0.0_linux64_dyn_release_Qt4.8.2_Python2.7.5/lib/cmake/vtk-6.0   

# minimum version required
CMAKE_MINIMUM_REQUIRED( VERSION 2.6 ) 

# name of the project
PROJECT( 3DMeshMetric )

# sub-directory of the executable
SET(EXECUTABLE_OUTPUT_PATH bin)

FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/icons DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin )

# find the VTK headers
FIND_PACKAGE( VTK REQUIRED )
INCLUDE( ${VTK_USE_FILE} )

# find the QT4 headers
FIND_PACKAGE( Qt4 REQUIRED ) 
INCLUDE( ${QT_USE_FILE} )

# include the directories for the binary and sources files
INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${QT_INCLUDE_DIR} )

# ?????
ADD_DEFINITIONS( -DQT_GUI_LIBS -DQT_CORE_LIB -DQT3_SUPPORT )

# generate moc and ui files
QT4_WRAP_CPP( QtProject_HEADERS_MOC meshMetricGui.h ColormapWidget.h )
QT4_WRAP_UI( UI_FILES meshMetricGui.ui )

# set the sources files
SET( Dsources 

main.cxx 

meshMetricGui.h
meshMetricGui.cxx

dataM.h
dataM.cxx

processing.h
processing.cxx

display.h
display.cxx

meshValmet.h
meshValmet.cxx

ColormapWidget.h
ColormapWidget.cxx

#gradientArrow.cxx
#gradientArrow.h

#gradientWidgetQT.cxx
#gradientWidgetQT.h

#colorPointStruct.h

MeshValmet/3dmodel.h

MeshValmet/mesh_run.cxx
MeshValmet/mesh_run.h

MeshValmet/model_in.cxx
MeshValmet/model_in.h

MeshValmet/read_model.h

MeshValmet/compute_error.cxx
MeshValmet/compute_error.h

MeshValmet/geomutils.cxx
MeshValmet/geomutils.h

MeshValmet/model_analysis.cxx
MeshValmet/model_analysis.h

MeshValmet/reporting.cxx
MeshValmet/reporting.h

MeshValmet/xalloc.cxx
MeshValmet/xalloc.h

MeshValmet/compute_volume_overlap.cxx
MeshValmet/compute_volume_overlap.h

${QtProject_HEADERS_MOC} ${UI_FILES} )

# generate the executable
ADD_EXECUTABLE( distance ${Dsources} )

# link the libraries to the executable
TARGET_LINK_LIBRARIES( distance ${QT_LIBRARIES} ${VTK_LIBRARIES} )

# for the CTest
SET(BUILD_TESTING ON CACHE BOOL "Build, configure and copy testing files")

IF( BUILD_TESTING )
ENABLE_TESTING()
ADD_SUBDIRECTORY( Testing )
ENDIF()




