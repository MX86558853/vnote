#ifndef VDIRECTORY_H
#define VDIRECTORY_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QPointer>
#include <QJsonObject>
#include "vnotebook.h"

class VFile;

class VDirectory : public QObject
{
    Q_OBJECT
public:
    VDirectory(VNotebook *p_notebook,
               const QString &p_name, QObject *p_parent = 0);
    bool open();
    void close();
    VDirectory *createSubDirectory(const QString &p_name);
    VDirectory *findSubDirectory(const QString &p_name);
    // Returns the VFile with the name @p_name.
    VFile *findFile(const QString &p_name);
    // If current dir or its sub-dir contains @p_file.
    bool containsFile(const VFile *p_file) const;
    VFile *createFile(const QString &p_name);
    void deleteSubDirectory(VDirectory *p_subDir);
    // Remove the file in the config and m_files without deleting it in the disk.
    int removeFile(VFile *p_file);
    // Remove the directory in the config and m_subDirs without deleting it in the disk.
    int removeSubDirectory(VDirectory *p_dir);
    // Add the file in the config and m_files. If @p_index is -1, add it at the end.
    // Return the VFile if succeed.
    VFile *addFile(VFile *p_file, int p_index);
    VFile *addFile(const QString &p_name, int p_index);
    VDirectory *addSubDirectory(VDirectory *p_dir, int p_index);
    VDirectory *addSubDirectory(const QString &p_name, int p_index);
    void deleteFile(VFile *p_file);
    bool rename(const QString &p_name);
    // Copy @p_srcFile to @p_destDir, setting new name to @p_destName.
    // @p_cut: copy or cut. Returns the dest VFile.
    static VFile *copyFile(VDirectory *p_destDir, const QString &p_destName,
                           VFile *p_srcFile, bool p_cut);
    static VDirectory *copyDirectory(VDirectory *p_destDir, const QString &p_destName,
                                     VDirectory *p_srcDir, bool p_cut);

    inline const QVector<VDirectory *> &getSubDirs() const;
    inline const QString &getName() const;
    inline void setName(const QString &p_name);
    inline bool isOpened() const;
    inline VDirectory *getParentDirectory();
    inline const VDirectory *getParentDirectory() const;
    inline VNotebook *getNotebook();
    inline const VNotebook *getNotebook() const;
    inline const QVector<VFile *> &getFiles() const;
    inline QString retrivePath() const;
    inline QString retriveRelativePath() const;
    inline QString getNotebookName() const;
    inline bool isExpanded() const;
    void setExpanded(bool p_expanded);
    void reorderFiles(int p_first, int p_last, int p_destStart);
    bool reorderFilesInConfig(int p_first, int p_last, int p_destStart);

    static QJsonObject createDirectoryJson();

private:
    // Get the path of @p_dir recursively
    QString retrivePath(const VDirectory *p_dir) const;
    // Get teh relative path of @p_dir recursively related to the notebook path
    QString retriveRelativePath(const VDirectory *p_dir) const;
    bool createFileInConfig(const QString &p_name, int p_index = -1);
    bool createSubDirectoryInConfig(const QString &p_name, int p_index = -1);

    QPointer<VNotebook> m_notebook;
    QString m_name;
    // Owner of the sub-directories
    QVector<VDirectory *> m_subDirs;
    // Owner of the files
    QVector<VFile *> m_files;
    bool m_opened;
    // Whether expanded in the directory tree.
    bool m_expanded;
};

inline const QVector<VDirectory *> &VDirectory::getSubDirs() const
{
    return m_subDirs;
}

inline const QString &VDirectory::getName() const
{
    return m_name;
}

inline void VDirectory::setName(const QString &p_name)
{
    m_name = p_name;
}

inline bool VDirectory::isOpened() const
{
    return m_opened;
}

inline VDirectory *VDirectory::getParentDirectory()
{
    return (VDirectory *)this->parent();
}

inline const VDirectory *VDirectory::getParentDirectory() const
{
    return (const VDirectory *)this->parent();
}

inline const QVector<VFile *> &VDirectory::getFiles() const
{
    return m_files;
}

inline QString VDirectory::getNotebookName() const
{
    return m_notebook->getName();
}

inline VNotebook *VDirectory::getNotebook()
{
    return m_notebook;
}

inline const VNotebook *VDirectory::getNotebook() const
{
    return m_notebook;
}

inline QString VDirectory::retrivePath() const
{
    return retrivePath(this);
}

inline QString VDirectory::retriveRelativePath() const
{
    return retriveRelativePath(this);
}

inline bool VDirectory::isExpanded() const
{
    return m_expanded;
}

#endif // VDIRECTORY_H
