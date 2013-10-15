#ifndef TESTMESHVALMET_H
#define TESTMESHVALMET_H

// Vtk Libraries
#include <QVTKWidget.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkPolyDataReader.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkIdTypeArray.h>
#include <vtkPolyDataMapper.h>
#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkPolyDataNormals.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkDoubleArray.h>
#include <vtkColorTransferFunction.h>
#include <vtkPointData.h>
#include <vtkFloatArray.h>

// Qt Libraries
#include <QMainWindow>
#include <QFileDialog>
#include <QObject>
#include <QProgressDialog>
#include <QMessageBox>


// Other Libraries
#include <iostream>
#include <string>

// MeshValmet Libraries
#include "MeshValmet/mesh_run.h"

#include "dataM.h"


class testMeshValmet: public QMainWindow
{

    public:
        testMeshValmet();

        void SetData1(vtkSmartPointer<vtkPolyData> Data1 );
        void SetData2( vtkSmartPointer<vtkPolyData> Data2 );
        void SetSamplingStep( double SamplingStep );
        void SetMinSampleFrequency( int MinSampleFrequency );
        void SetSignedDistance( bool SignedDistance );

        vtkSmartPointer <vtkPolyData> GetFinalData();
        vtkSmartPointer <vtkColorTransferFunction> GetLut();

        void CalculateError();
        friend void mesh_run(const args *args,
                             model_error *model1, model_error *model2,
                             outbuf *out, prog_reporter *progress,
                             dist_surf_surf_stats *stats, dist_surf_surf_stats *stats_rev,
                             double *abs_sampling_step, double *abs_sampling_dens);
        void drawVertexErrorT();
        void CreateLutError();
        int testPolyData( vtkSmartPointer <vtkPolyData> inData , vtkSmartPointer <vtkPolyData> outData );

    private:

        vtkSmartPointer <vtkPolyData> m_FinalData;
        vtkSmartPointer <vtkColorTransferFunction> m_Lut;

        struct args m_Pargs;

        struct model_error m_ModelError1;
        struct model_error m_ModelError2;

        struct outbuf *m_Out;

        struct dist_surf_surf_stats m_Stats;
        struct dist_surf_surf_stats m_StatsRev;

        double m_AbsSamplingStep;
        double m_AbsSamplingDens;

        double m_DiceCoefficient[1];
        double m_IntUnionRatio[1];

        double m_Dmax;
        double m_Dmin;

        double m_Downsampling;
        double m_Middle;

        struct look
        {
           float R;
           float G;
           float B;
        };

        look m_Lookuptable[256];

};

#endif
