
/*-------------------------------------------------------------------------------------------------

14-mar-2020: Wrote an API to get env var value.
23-aug-2020: Used C++17 std::filesystem to recursively traverse a folder.

-------------------------------------------------------------------------------------------------*/

#include "../mkEnvironmentVariables.h"
#include "../mkMemoryRawArrays.h"
#include "../mkFilesystem.h"

//-------------------------------------------------------------------------------------------------

int main (int argc, char *argv [])
{
    mkUtilities::unittest_envVars ();
    mkUtilities::unittests_rawArrays ();
    mkUtilities::unittests_filesystem ();

    return 0;
}

//-------------------------------------------------------------------------------------------------
