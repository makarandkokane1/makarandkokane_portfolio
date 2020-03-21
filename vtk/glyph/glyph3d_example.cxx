
/*-------------------------------------------------------------------------------------------------

glyph: A small graphic symbol.

Originally copied from 'OrientedGlyphs' project in VTK Examples.

-------------------------------------------------------------------------------------------------*/

#include "vtkSphereSource.h"
#include "vtkArrowSource.h"
#include "vtkGlyph3D.h"

//-------------------------------------------------------------------------------------------------

#include "../../utilities/mkEnvironmentVariables.h"
#include "../../utilities/mkMemoryRawArrays.h"
#include "../mkVisualizeAlgorithmOutput.h"

//-------------------------------------------------------------------------------------------------

int example_OrientedGlyphs ();

//-------------------------------------------------------------------------------------------------

int main (int argc, char *argv [])
{
    example_OrientedGlyphs ();

    return 0;
}

//-------------------------------------------------------------------------------------------------

int example_OrientedGlyphs ()
{
    // vtkSphereSource creates a polygonal (discretized) sphere.
    // By default, the surface tessellation of the sphere uses triangles.
    vtkSmartPointer<vtkPolyDataAlgorithm> sphereSource = vtkSmartPointer<vtkSphereSource>::New ();
    sphereSource->Update ();
    vtkPolyData* sphere = sphereSource->GetOutput ();

    vtkSmartPointer<vtkArrowSource> arrowSource = vtkSmartPointer<vtkArrowSource>::New ();

    vtkSmartPointer<vtkGlyph3D> glyph3D = vtkSmartPointer<vtkGlyph3D>::New ();
    glyph3D->SetSourceConnection (arrowSource->GetOutputPort ());
    glyph3D->SetVectorModeToUseNormal ();
    glyph3D->SetInputData (sphere);
    glyph3D->SetScaleFactor (.2);
    glyph3D->Update ();

    mkUtilities::mkVisualizeAlgorithmOutput (glyph3D->GetOutputPort ());

    return EXIT_SUCCESS;
}

//-------------------------------------------------------------------------------------------------
