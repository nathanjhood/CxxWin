/**
 * @file CMakeRC.hpp
 * @author vector-of-bool <vectorofbool@gmail.com>
 * @version 2.0.1
 * @date 2018-09-08
 *
 * @copyright Copyright (c) 2017
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#ifndef CMRC_CMRC_HPP_INCLUDED
#define CMRC_CMRC_HPP_INCLUDED

#include <cassert>
#include <functional>
#include <iterator>
#include <list>
#include <map>
#include <mutex>
#include <string>
#include <system_error>
#include <type_traits>

#if !(defined(__EXCEPTIONS) || defined(__cpp_exceptions) || defined(_CPPUNWIND) || defined(CMRC_NO_EXCEPTIONS))
#  define CMRC_NO_EXCEPTIONS 1
#endif

namespace CMakeRC
{
namespace Detail
{
/**
 * @brief Dummy struct
 *
 * @namespace CMakeRC
 * @namespace Detail
 *
 */
struct Dummy;
}
}

#define CMRC_DECLARE(LibId) \
namespace CMakeRC \
{ \
namespace Detail \
{ \
struct Dummy; \
static_assert(std::is_same<Dummy, ::CMakeRC::Detail::Dummy>::value, "CMRC_DECLARE() must only appear at the global namespace"); \
} \
} \
namespace CMakeRC \
{ \
namespace LibId \
{ \
CMakeRC::EmbeddedFileSystem GetFileSystem(); \
} \
} static_assert(true, "")

namespace CMakeRC
{
/**
 * @brief The 'File' class.
 *
 * @namespace CMakeRC
 */
class File
{
public:
    using Iterator = const char*;
    using ConstIterator = Iterator;

    /**
     * @brief Default-Construct a new 'File' object.
     *
     */
    File() = default;
    /**
     * @brief Construct a new 'File' object.
     *
     * @param beg
     * @param end
     */
    File(Iterator beg, Iterator end) noexcept : _begin(beg), _end(end) {}
    /**
     * @brief Return the beginning of an array which contains a 'File' object.
     *
     * @return Iterator
     */
    Iterator Begin() const noexcept
    {
        return _begin;
    }
    /**
     * @brief Return the beginning of an array which contains a 'File' object.
     *
     * @return Iterator
     */
    Iterator CBegin() const noexcept
    {
        return _begin;
    }
    /**
     * @brief Return the end of an array which contains a 'File' object.
     *
     * @return Iterator
     */
    Iterator End() const noexcept
    {
        return _end;
    }
    /**
     * @brief Return the end of an array which contains a 'File' object.
     *
     * @return Iterator
     */
    Iterator CEnd() const noexcept
    {
        return _end;
    }
    /**
     * @brief Return the size of an array which contains a 'File' object.
     *
     * @return std::size_t
     */
    std::size_t Size() const
    {
        return static_cast<std::size_t>(std::distance(Begin(), End()));
    }

private:
    /**
     * @brief The first char of an array which contains a 'file' object.
     *
     */
    const char* _begin = nullptr;
    /**
     * @brief The last char of an array which contains a 'file' object.
     *
     */
    const char* _end = nullptr;
};

/**
 * @brief The 'DirectoryEntry' class.
 *
 * @namespace CMakeRC
 */
class DirectoryEntry;

namespace Detail
{
/**
 * @brief The 'Directory' class.
 *
 * @namespace CMakeRC
 * @namespace Detail
 */
class Directory;

/**
 * @brief The 'FileData' class.
 *
 * @namespace CMakeRC
 * @namespace Detail
 */
class FileData;

/**
 * @brief The 'FileOrDirectory' class.
 *
 * @namespace CMakeRC
 * @namespace Detail
 */
class FileOrDirectory
{
public:
    /**
     * @brief Construct a new 'FileOrDirectory' object.
     *
     * @param f
     */
    explicit FileOrDirectory(FileData& f)
    {
        _data.FileData = &f;
    }
    /**
     * @brief Construct a new 'FileOrDirectory' object.
     *
     * @param d
     */
    explicit FileOrDirectory(Directory& d)
    {
        _data.Directory = &d;
        _is_file = false;
    }
    /**
     * @brief
     *
     * @return true
     * @return false
     */
    bool IsFile() const noexcept
    {
        return _is_file;
    }
    /**
     * @brief
     *
     * @return true
     * @return false
     */
    bool IsDirectory() const noexcept
    {
        return !IsFile();
    }
    /**
     * @brief
     *
     * @return const Directory&
     */
    const Directory& AsDirectory() const noexcept
    {
        assert(!IsFile());
        return *_data.Directory;
    }
    /**
     * @brief
     *
     * @return const FileData&
     */
    const FileData& AsFile() const noexcept
    {
        assert(IsFile());
        return *_data.FileData;
    }
private:
    union _data_t
    {
        class FileData* FileData;
        class Directory* Directory;
    } _data;
    bool _is_file = true;
};

/**
 * @brief The 'FileData' class
 * @namespace CMakeRC::Detail::
 *
 */
class FileData
{
public:
    /**
     * @brief Construct a new 'FileData' object
     *
     * @param b
     * @param e
     */
    FileData(const char* b, const char* e) : begin_ptr(b), end_ptr(e) {}
    /**
     * @brief (inaccessible) Move-Construct a new 'FileData' object
     *
     */
    FileData(const FileData&) = delete;

    const char* begin_ptr;
    const char* end_ptr;
};

/**
 * @brief
 *
 * @param path
 * @return std::pair<std::string, std::string>
 */
inline std::pair<std::string, std::string> SplitPath(const std::string& path)
{
    auto first_sep = path.find("/");

    if (first_sep == path.npos)
    {
        return std::make_pair(path, "");
    } else {
        return std::make_pair(path.substr(0, first_sep), path.substr(first_sep + 1));
    }
}

/**
 * @brief The 'CreatedSubDirectory' struct.
 *
 * @namespace CMakeRC
 * @namespace Detail
 */
struct CreatedSubDirectory
{
    class Directory& Directory;
    class FileOrDirectory& IndexEntry;
};

/**
 * @brief The 'Directory' class.
 *
 * @namespace CMakeRC
 * @namespace Detail
 */
class Directory
{
    using BaseIterator = std::map<std::string, FileOrDirectory>::const_iterator;

public:
    /**
     * @brief Construct a new 'Directory' object.
     *
     */
    Directory() = default;

    /**
     * @brief (inaccessible) Move-Construct a new 'Directory' object.
     *
     */
    Directory(const Directory&) = delete;

    /**
     * @brief
     *
     * @param name
     * @return CreatedSubDirectory
     */
    CreatedSubDirectory AddSubDir(std::string name) &
    {
        _dirs.emplace_back();
        auto& back = _dirs.back();
        auto& fod = _index.emplace(name, FileOrDirectory{back}).first->second;
        return CreatedSubDirectory{back, fod};
    }

    /**
     * @brief
     *
     * @param name
     * @param begin
     * @param end
     * @return FileOrDirectory*
     */
    FileOrDirectory* AddFile(std::string name, const char* begin, const char* end) &
    {
        assert(_index.find(name) == _index.end());
        _files.emplace_back(begin, end);
        return &_index.emplace(name, FileOrDirectory{_files.back()}).first->second;
    }

    /**
     * @brief
     *
     * @param path
     * @return const FileOrDirectory*
     */
    const FileOrDirectory* Get(const std::string& path) const
    {
        auto pair = SplitPath(path);
        auto child = _index.find(pair.first);

        if (child == _index.end())
        {
            return nullptr;
        }
        auto& entry  = child->second;

        if (pair.second.empty())
        {
            /** We're at the end of the path */
            return &entry;
        }

        if (entry.IsFile())
        {
            /** We can't traverse into a file. Stop. */
            return nullptr;
        }
        /** Keep going down */
        return entry.AsDirectory().Get(pair.second);
    }

    /**
     * @brief The 'Iterator' class.
     *
     */
    class Iterator
    {
    public:
        using ValueType = DirectoryEntry;
        using DifferenceType = std::ptrdiff_t;
        using pointer = const ValueType*;
        using reference = const ValueType&;
        using IteratorCategory = std::input_iterator_tag;

        /**
         * @brief Default-Construct a new 'Iterator' object.
         *
         */
        Iterator() = default;

        /**
         * @brief Construct a new 'Iterator' object.
         *
         * @param iter
         * @param end
         */
        explicit Iterator(BaseIterator iter, BaseIterator end) : _base_iter(iter), _end_iter(end) {}

        /**
         * @brief
         * @return Iterator
         */
        Iterator Begin() const noexcept
        {
            return *this;
        }

        /**
         * @brief
         * @return Iterator
         */
        Iterator End() const noexcept
        {
            return Iterator(_end_iter, _end_iter);
        }

        /**
         * @brief
         * @return ValueType
         */
        inline ValueType operator*() const noexcept;

        /**
         * @brief
         * @param rhs
         * @return true
         * @return false
         */
        bool operator==(const Iterator& rhs) const noexcept
        {
            return _base_iter == rhs._base_iter;
        }

        /**
         * @brief
         *
         * @param rhs
         * @return true
         * @return false
         */
        bool operator!=(const Iterator& rhs) const noexcept
        {
            return !(*this == rhs);
        }

        /**
         * @brief
         *
         * @return Iterator&
         */
        Iterator& operator++() noexcept
        {
            ++_base_iter;
            return *this;
        }

        /**
         * @brief
         * @return Iterator
         */
        Iterator operator++(int) noexcept
        {
            auto cp = *this;
            ++_base_iter;
            return cp;
        }

    private:
        BaseIterator _base_iter;
        BaseIterator _end_iter;
    };

    using ConstIterator = Iterator;

    /**
     * @brief
     *
     * @return Iterator
     */
    Iterator Begin() const noexcept
    {
        return Iterator(_index.begin(), _index.end());
    }

    /**
     * @brief
     *
     * @return Iterator
     */
    Iterator End() const noexcept
    {
        return Iterator();
    }
private:
    std::list<FileData> _files;
    std::list<Directory> _dirs;
    std::map<std::string, FileOrDirectory> _index;
};

/**
 * @brief
 *
 * @param path
 * @return std::string
 */
inline std::string NormalizePath(std::string path)
{
    while (path.find("/") == 0)
    {
        path.erase(path.begin());
    }

    while (!path.empty() && (path.rfind("/") == path.size() - 1))
    {
        path.pop_back();
    }

    auto off = path.npos;

    while ((off = path.find("//")) != path.npos)
    {
        path.erase(path.begin() + static_cast<std::string::difference_type>(off));
    }

    return path;
}

using IndexType = std::map<std::string, const CMakeRC::Detail::FileOrDirectory*>;

} /** namespace CMakeRC::Detail */

/**
 * @brief The 'DirectoryEntry' class.
 *
 * @namespace CMakeRC
 */
class DirectoryEntry
{
    std::string _fname;
    const Detail::FileOrDirectory* _item;
public:
    /**
     * @brief (inaccessible) Default-Construct a new 'DirectoryEntry' object.
     *
     */
    DirectoryEntry() = delete;

    /**
     * @brief Construct a new 'DirectoryEntry' object.
     *
     * @param filename
     * @param item
     */
    explicit DirectoryEntry(std::string filename, const Detail::FileOrDirectory& item)
        : _fname(filename)
        , _item(&item)
    {}

    /**
     * @brief
     *
     * @return const std::string&
     */
    const std::string& Filename() const &
    {
        return _fname;
    }

    /**
     * @brief
     *
     * @return std::string
     */
    std::string Filename() const &&
    {
        return std::move(_fname);
    }

    /**
     * @brief
     *
     * @return true
     * @return false
     */
    bool IsFile() const
    {
        return _item->IsFile();
    }

    /**
     * @brief
     *
     * @return true
     * @return false
     */
    bool IsDirectory() const
    {
        return _item->IsDirectory();
    }
};

/**
 * @brief
 * @return DirectoryEntry
 */
DirectoryEntry Detail::Directory::Iterator::operator*() const noexcept
{
    assert(Begin() != End());
    return DirectoryEntry(_base_iter->first, _base_iter->second);
}

using DirectoryIterator = Detail::Directory::Iterator;

/**
 * @brief The 'EmbeddedFileSystem' class
 * @namespace CMakeRC
 */
class EmbeddedFileSystem
{
private:
    /**
     * @brief Never-null:
     */
    const CMakeRC::Detail::IndexType* _index;
    /**
     * @brief
     * @param path
     * @return const Detail::FileOrDirectory*
     */
    const Detail::FileOrDirectory* _get(std::string path) const
    {
        path = Detail::NormalizePath(path);
        auto found = _index->find(path);

        if (found == _index->end())
        {
            return nullptr;
        }
        else
        {
            return found->second;
        }
    }

public:
    /**
     * @brief Construct a new 'EmbeddedFileSystem' object
     *
     * @param index
     */
    explicit EmbeddedFileSystem(const Detail::IndexType& index)
        : _index(&index)
    {}

    /**
     * @brief
     * @param path
     * @return File
     */
    File open(const std::string& path) const
    {
        auto entry_ptr = _get(path);
        if (!entry_ptr || !entry_ptr->IsFile())
        {
#ifdef CMRC_NO_EXCEPTIONS
            fprintf(stderr, "Error no such file or directory: %s\n", path.c_str());
            abort();
#else
            throw std::system_error(make_error_code(std::errc::no_such_file_or_directory), path);
#endif
        }
        auto& dat = entry_ptr->AsFile();
        return File{dat.begin_ptr, dat.end_ptr};
    }

    /**
     * @brief
     *
     * @param path
     * @return true
     * @return false
     */
    bool IsFile(const std::string& path) const noexcept
    {
        auto entry_ptr = _get(path);
        return entry_ptr && entry_ptr->IsFile();
    }

    /**
     * @brief
     *
     * @param path
     * @return true
     * @return false
     */
    bool IsDirectory(const std::string& path) const noexcept
    {
        auto entry_ptr = _get(path);
        return entry_ptr && entry_ptr->IsDirectory();
    }

    /**
     * @brief
     *
     * @param path
     * @return true
     * @return false
     */
    bool Exists(const std::string& path) const noexcept
    {
        return !!_get(path);
    }

    /**
     * @brief
     *
     * @param path
     * @return DirectoryIterator
     */
    DirectoryIterator IterateDirectory(const std::string& path) const
    {
        auto entry_ptr = _get(path);
        if (!entry_ptr)
        {
#ifdef CMRC_NO_EXCEPTIONS
            fprintf(stderr, "Error no such file or directory: %s\n", path.c_str());
            abort();
#else
            throw std::system_error(make_error_code(std::errc::no_such_file_or_directory), path);
#endif
        }
        if (!entry_ptr->IsDirectory())
        {
#ifdef CMRC_NO_EXCEPTIONS
            fprintf(stderr, "Error not a directory: %s\n", path.c_str());
            abort();
#else
            throw std::system_error(make_error_code(std::errc::not_a_directory), path);
#endif
        }
        return entry_ptr->AsDirectory().Begin();
    }
};

} /** namespace CMakeRC */

#endif // CMRC_CMRC_HPP_INCLUDED
