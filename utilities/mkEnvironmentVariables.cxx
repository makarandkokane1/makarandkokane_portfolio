
/*-------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------*/

#include <cstdlib>
#include <iostream>

//-------------------------------------------------------------------------------------------------

#include "mkEnvironmentVariables.h"

//-------------------------------------------------------------------------------------------------

const char* mkUtilities::getenv (const char* in_envVarName)
{
    return std::getenv (in_envVarName);
}

//-------------------------------------------------------------------------------------------------

bool mkUtilities::getProjectRootPath (
    const char*& out_varName,
    const char*& out_value)
{
    out_varName = "MK_GH_ROOT";

    out_value = mkUtilities::getenv (out_varName);

    return (out_value != nullptr);
}

//-------------------------------------------------------------------------------------------------

void mkUtilities::unittest_envVars ()
{
    const char* varName = nullptr;
    const char* value = nullptr;

    bool isDefined = mkUtilities::getProjectRootPath (varName, value);

    if (isDefined)
    {
        std::cout << "\n" << varName << " = " << value << "\n";
    }
    else
    {
        std::cout << "\n" << varName << " not defined.\n";
    }
}

//-------------------------------------------------------------------------------------------------
