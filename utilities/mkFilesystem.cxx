#include "mkFilesystem.h"
#include "mkEnvironmentVariables.h"

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

    std::shared_ptr<mkUtilities::fsFileDirectoryNode> node = mkUtilities::fsFileDirectoryNode::create(l_src1Path);
    node->recreateContent(extensions);
    std::cout << (*node) << "\n";
}

void mkUtilities::fsFileDirectoryNode::recreateContent(const std::set<std::string>& filterExtensions,
    const bool& in_flatContents)
{
    clearContent();

    if (!std::filesystem::is_directory(m_path))
        return;

    if (!in_flatContents)
    {
        for (auto& i : std::filesystem::directory_iterator(m_path))
        {
            const std::filesystem::path path2 = i.path();
            bool validEntry = false;
            bool isDirectory2 = std::filesystem::is_directory(path2);
            if (isDirectory2)
                validEntry = true;
            if (!isDirectory2 && path2.has_extension())
            {
                const std::filesystem::path ext = path2.extension();
                size_t isPresent = filterExtensions.count(ext.string());
                if (isPresent)
                {
                    validEntry = true;
                }
            }
            if (validEntry)
            {
                std::shared_ptr<mkUtilities::fsFileDirectoryNode> node = mkUtilities::fsFileDirectoryNode::create(path2);
                node->recreateContent(filterExtensions);
                m_content.push_back(node);
            }
        }
    }
    else
    {
        for (auto& i : std::filesystem::recursive_directory_iterator(m_path))
        {
            const std::filesystem::path path2 = i.path();
            if (path2.has_extension())
            {
                const std::filesystem::path ext = path2.extension();
                size_t isPresent = filterExtensions.count(ext.string());
                if (isPresent)
                {
                    std::shared_ptr<mkUtilities::fsFileDirectoryNode> node = mkUtilities::fsFileDirectoryNode::create(path2);
                    node->clearContent();
                    m_content.push_back(node);
                }
            }
        }
    }
}

void mkUtilities::fsFileDirectoryNode::clearContent()
{
    m_content.clear();
}

std::shared_ptr<mkUtilities::fsFileDirectoryNode> mkUtilities::fsFileDirectoryNode::create(
    const std::filesystem::path& in_path)
{
    std::shared_ptr<mkUtilities::fsFileDirectoryNode> out = std::shared_ptr<mkUtilities::fsFileDirectoryNode>(
        new mkUtilities::fsFileDirectoryNode(in_path));

    return out;
}

mkUtilities::fsFileDirectoryNode::fsFileDirectoryNode(const std::filesystem::path& in_path) :
    m_path(in_path)
{

}

std::ostream& mkUtilities::operator << (std::ostream& os, const mkUtilities::fsFileDirectoryNode& obj)
{
    os << obj.m_path << "\n";

    std::list<std::shared_ptr<mkUtilities::fsFileDirectoryNode>>::const_iterator iterator;
    for (iterator = obj.m_content.cbegin(); iterator != obj.m_content.cend(); ++iterator)
    {
        std::shared_ptr<mkUtilities::fsFileDirectoryNode> p = *iterator;
        os << (*p);
    }

    return os;
}

std::filesystem::file_time_type mkUtilities::fsFileDirectoryNode::getLastModifiedTime() const
{
    std::filesystem::file_time_type t = std::filesystem::last_write_time(m_path);

    return t;
}