
/*-------------------------------------------------------------------------------------------------

APIs for environment variables required to run applications in this repository.

-------------------------------------------------------------------------------------------------*/

#ifndef _mkEnvironmentVariables
#define _mkEnvironmentVariables

//-------------------------------------------------------------------------------------------------

namespace mkUtilities
{
    bool getProjectRootPath (
        const char*& out_varName,
        const char*& out_value);

    bool getSrc1RootPath(
        const char*& out_varName,
        const char*& out_value);

    const char* getenv (const char* in_envVarName);

    void unittest_envVars ();
};

//-------------------------------------------------------------------------------------------------

#endif

//-------------------------------------------------------------------------------------------------
