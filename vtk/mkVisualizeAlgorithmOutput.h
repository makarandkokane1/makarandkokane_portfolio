
/*-------------------------------------------------------------------------------------------------

APIs for visualizing output of vtkAlgorithm.

-------------------------------------------------------------------------------------------------*/

#ifndef _mkVisualizeAlgorithmOutput
#define _mkVisualizeAlgorithmOutput

//-------------------------------------------------------------------------------------------------

#include "vtkAlgorithmOutput.h"
#include "vtkImageData.h"

//-------------------------------------------------------------------------------------------------

namespace mkUtilities
{
    void mkVisualizeAlgorithmOutput (vtkAlgorithmOutput* in);

    // TODO: Move to a different file, when more usages evolve.
    void mkVisualizeVtkImageData (vtkImageData* vtkData);

};

//-------------------------------------------------------------------------------------------------

#endif

//-------------------------------------------------------------------------------------------------
