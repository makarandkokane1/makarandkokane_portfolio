
/*-------------------------------------------------------------------------------------------------

Demonstrates APIs provided by following Remote VTK modules.
http://dgobbi.github.io/vtk-dicom/
http://dgobbi.github.io/vtk-dicom/doc/vtk-dicom.pdf

If your main focus is on Visualization using VTK, but you need some quick way to read DICOM
datasets, then you are probably using vtkDICOMImageReader
This is a much more richer and robust alternative to vtkDICOMImageReader.

When building VTK, enable Module_vtkDICOM in cmake. It builds these APIs as a remote VTK module.

-------------------------------------------------------------------------------------------------*/

#include "vtkDICOMTag.h"
#include "vtkDICOMVR.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMParser.h"
#include "vtkDICOMValue.h"
#include "vtkDICOMReader.h" 
#include "vtkSmartPointer.h"
#include "vtkImageData.h"

//-------------------------------------------------------------------------------------------------

#include "../../utilities/mkEnvironmentVariables.h"
#include "../mkVisualizeAlgorithmOutput.h"

//-------------------------------------------------------------------------------------------------


int main (int argc, char *argv [])
{
    const char* projectRootPath = nullptr;
    {
        const char* varName = nullptr;
        bool isDefined = mkUtilities::getProjectRootPath (varName, projectRootPath);
        if (!isDefined)
        {
            std::cout << "Can't proceed without definition of environment variable "
                << varName << "\n";
            return -1;
        }
    }

    // Sample usage.
    vtkDICOMTag tg;
    tg = vtkDICOMTag (DC::PixelSpacing);
    unsigned short group = tg.GetGroup ();
    unsigned short element = tg.GetElement ();

    // Sample usage.
    // Value Representation.
    vtkDICOMVR vr (vtkDICOMVR::CS);
    const char* vrName = vr.GetText ();
    bool isVrText = (vr.GetType () == VTK_CHAR);

    std::string sampleDcmFile (projectRootPath);
    {
        const char* relativePath = "/test_data/dicom/ct/nih_nci_nbia/1/Head-Neck Cetuximab-Demo/0522c0001/1.3.6.1.4.1.14519.5.2.1.5099.8010.199920086920823171706454903251/1.3.6.1.4.1.14519.5.2.1.5099.8010.427264300850965737262860055580/000000.dcm";
        sampleDcmFile += relativePath;

    }

    vtkSmartPointer<vtkDICOMParser> parser = vtkSmartPointer<vtkDICOMParser>::New ();
    vtkSmartPointer<vtkDICOMMetaData> metadata = vtkSmartPointer<vtkDICOMMetaData>::New ();
    parser->SetFileName (sampleDcmFile.c_str ());
    parser->SetMetaData (metadata);
    parser->Update ();

    double rowSpacing = 0;
    double columnSpacing = 0;
    vtkDICOMValue pixelSpacing = metadata->GetAttributeValue (DC::PixelSpacing);
    if (pixelSpacing.IsValid ())
    {
        const int numberOfValues = pixelSpacing.GetNumberOfValues ();
        if (numberOfValues == 2)
        {
            rowSpacing = pixelSpacing.GetDouble (0);
            columnSpacing = pixelSpacing.GetDouble (1);
        }
    }

    vtkSmartPointer<vtkDICOMReader> reader = vtkSmartPointer<vtkDICOMReader>::New ();
    reader->SetFileName (sampleDcmFile.c_str ());
    reader->Update ();
    vtkImageData* data = reader->GetOutput ();

    mkUtilities::mkVisualizeVtkImageData (data);

    return 0;
}

//-------------------------------------------------------------------------------------------------

