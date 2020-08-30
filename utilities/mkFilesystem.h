
/*-------------------------------------------------------------------------------------------------

Uses C++17 std::filesystem.

-------------------------------------------------------------------------------------------------*/

#ifndef _mkFilesystem
#define _mkFilesystem

#include <filesystem>
#include <iostream>
#include <set>

namespace mkUtilities
{
    // Info about a single directory or file.
    class fsFileDirectoryNode;

    std::ostream& operator << (std::ostream& os, const mkUtilities::fsFileDirectoryNode& obj);

    void unittests_filesystem();
};

class mkUtilities::fsFileDirectoryNode
{
public:

    std::filesystem::file_time_type getLastModifiedTime() const;

    void recreateContent(const std::set<std::string>& filterExtensions,
        const bool& in_flatContents = false);

    void clearContent();

    static std::shared_ptr<fsFileDirectoryNode> create(
        const std::filesystem::path& in_path);

    friend std::ostream& operator << (std::ostream& os, const mkUtilities::fsFileDirectoryNode& obj);

private:

    std::filesystem::path m_path;

    std::list<std::shared_ptr<fsFileDirectoryNode>> m_content;

    fsFileDirectoryNode(const std::filesystem::path& in_path);
    
    fsFileDirectoryNode() = delete;

    fsFileDirectoryNode(const fsFileDirectoryNode& in) = delete;

    const fsFileDirectoryNode& operator = (const fsFileDirectoryNode& in) = delete;
};

#endif
