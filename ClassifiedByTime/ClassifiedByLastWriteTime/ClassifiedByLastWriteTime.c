#include <tchar.h>
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <Shlwapi.h>

void findUpLevelDir(TCHAR* dirPath)
{
    size_t dirlLen = _tcsclen(dirPath);
    for(size_t i = dirlLen - 1; i >= 0; i--)
    {
        if(dirPath[i] == _T('\\'))
        {
            dirPath[i] = _T('\0');
            break;
        }
    }
}

void dealWithFindData(WIN32_FIND_DATA* pffd, TCHAR* dir)
{
    SYSTEMTIME stUTC;
    SYSTEMTIME stLocal;
    TCHAR timeDir[30];

    if(NULL != _tcsstr(pffd->cFileName, _T("ClassifiedByLastWriteTime")))
    {
        return;
    }

    if(pffd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
    {
        return;
    }

    TCHAR* newPath = calloc(_tcsclen(dir) + 30 + 260, sizeof(TCHAR));
    TCHAR* oldPath = calloc(_tcsclen(dir) + 260, sizeof(TCHAR));

    FileTimeToSystemTime(&pffd->ftLastWriteTime, &stUTC);
    SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

    _stprintf(timeDir, _T("%04u_%02u_%02u"), stLocal.wYear, stLocal.wMonth, stLocal.wDay);
    _stprintf(newPath, _T("%s\\%s"), dir, timeDir);

    if(INVALID_FILE_ATTRIBUTES == GetFileAttributes(newPath))
        CreateDirectory(newPath, NULL);

    _tcscat(newPath, "\\");
    _tcscat(newPath, pffd->cFileName);
    _tcscat(oldPath, "\\");
    _tcscat(oldPath, pffd->cFileName);

    MoveFile(oldPath, newPath);

    free(newPath);
    free(oldPath);
}

int _tmain(int argc, _TCHAR* argv[])
{
    TCHAR *dir = argv[0];
    size_t dirlLen = _tcsclen(dir);
    findUpLevelDir(dir);

    TCHAR *searchPath = calloc(dirlLen + 10, sizeof(TCHAR));
    _tcscat(searchPath, dir);
    _tcscat(searchPath, _T("\\*"));

    WIN32_FIND_DATA ffd;

    HANDLE hFind = INVALID_HANDLE_VALUE;

    hFind = FindFirstFile(searchPath, &ffd);

    dealWithFindData(&ffd, dir);

    while(FindNextFile(hFind, &ffd) != 0)
    {
        dealWithFindData(&ffd, dir);
    }

    FindClose(hFind);

    _tsystem(_T("pause"));

    free(searchPath);

    return 0;
}

