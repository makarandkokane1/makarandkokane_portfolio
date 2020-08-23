#include "mkFilesystem.h"
#include "mkEnvironmentVariables.h"
#include <iostream>
#include <set>

void mkUtilities::unittests_filesystem()
{
	std::cout << "mkUtilities::unittests_filesystem()\n";

	std::string l_src1Path;
    {
        const char* varName = nullptr;
        const char* value = nullptr;

        bool isDefined = mkUtilities::getSrc1RootPath(varName, value);

        if (isDefined)
        {
            std::cout << varName << " = " << value << "\n";
            l_src1Path = value;
        }
        else
        {
            std::cout << "\n" << varName << " not defined.\n";
        }
    }
    std::cout << l_src1Path << "\n";
    
    std::set<std::string> extensions = {".h", ".cpp", ".cxx", ".qml", ".c", ".pro", ".txt", ".ini"};

    for (auto& i : std::filesystem::recursive_directory_iterator(l_src1Path))
    {
        const std::filesystem::path p = i.path();
        if (p.has_extension())
        {
            const std::filesystem::path ext = p.extension();
            size_t isPresent = extensions.count(ext.string());
            if (isPresent)
                std::cout << p << "\n";
        }
    }
}
