/////////////////////////////////////////////////////////////////////////////
// Copyright 2013 Ricardo Garcia (rago)
//  info: http://crumbssoftware.com
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
/////////////////////////////////////////////////////////////////////////////

#include <string>
#ifdef _WIN32
#include "winsock2.h"
#endif
#include <stdio.h>
#include "CRSystemUtils.h"
#include <sstream>
//#include <boost/algorithm/string.hpp>

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif


#include <wx/filefn.h>
#include <wx/filename.h>
#include <wx/dir.h>

//filetypes:
// -1: all,
// 1:tiff
// 2:ocr/pdf
// 3:text -> insert text

std::string sBatesExtract(std::string &sInput, std::string &sRoot)
{
    std::string sBates;
    //extract bates number
    size_t nPos = sInput.find(sRoot);
    size_t l = sRoot.size();
    
    if(nPos != std::string::npos)
    {
        sBates = sInput.substr(nPos+l);
        
    }

    return sBates;
}


class CRDirTraverser : public wxDirTraverser {
private:
    std::vector<file_element> &mFiles;
    wxString mFileExtension;
public:
    CRDirTraverser(std::vector<file_element> &vFiles, const wxString fileExt) : mFiles(vFiles), mFileExtension(fileExt) {
    }
    
    virtual wxDirTraverseResult OnFile(const wxString& filename)
    {
        wxFileName xFileName = wxFileName::FileName(filename);
        wxString xsFileExt = xFileName.GetExt();
        
        if (mFileExtension.CmpNoCase(xsFileExt) == 0) {
            wxString xsFileNamePlusExt = xFileName.GetName() + wxT(".") + xsFileExt;
            //printf("found file: %s", (const char*)filename.mb_str());
            file_element tElement;
            tElement.sFullPath = filename.ToStdString();
            tElement.sName     = xsFileNamePlusExt.ToStdString();
            
            mFiles.push_back(tElement);
        }

        return wxDIR_CONTINUE;
    }
    virtual wxDirTraverseResult OnDir(const wxString& WXUNUSED(dirname))
    {
        //printf("found folder...");
        //        printf("found folder: %s", (const char*)dirname.mb_str());
        return wxDIR_CONTINUE;
    }
};



bool bCreateFileListV2(std::ostream& out, const std::string &sBasePath, const std::string &sExt, int nMaxLevels, std::vector<file_element> &vFiles) {
    
    bool bStatus = true;
    
    //printf("v2: current path: %s", sBasePath.c_str());
    
    wxDir xsDir(wxString(sBasePath.c_str(), wxConvUTF8));
    
    CRDirTraverser myDT(vFiles, wxString(sExt.c_str(), wxConvUTF8));
    
//    wxString xsFileSpec = wxT("*") + wxString(sExt.c_str(), wxConvUTF8);
    xsDir.Traverse(myDT);
    int xx=1;
    
    
    
    return bStatus;
}


#if 0
bool bCreateFileList(std::ostream& out, const std::string &sBasePath, const std::string &sExt, int nMaxLevels, std::vector<file_element> &vFiles)
{
    bool bStatus = true;
    
    std::string sExtToCompare = sExt;
    //std::transform(sExtToCompare.begin(), sExtToCompare.end(), sExtToCompare.begin(), ::toupper);
    
    boost::to_upper(sExtToCompare);
    
    
    wxString xCurrentDirectory = wxGetCwd();
    
//    wxFileName xFileName = wxFileName(xCurrentDirectory);
//    bool bIsDir = xFileName.IsDir();
    out << "current path: " << xCurrentDirectory.mb_str() << std::endl;
//    out << " is directory: " << bIsDir <<std::endl;
 //    std::string sCurrentPath = fs::current_path().string();
//    out << "current path: " << sCurrentPath <<std::endl;
    
    
    
    fs::path myPath(sBasePath);
    
    if(fs::is_directory(myPath))
    {
        //keep navigating down
        
        //iterate
        fs::directory_iterator end_iter;
        for(fs::directory_iterator dir_itr(myPath); dir_itr != end_iter; dir_itr++)
        {
            //iterating all of these!
            
            try
            {
                if(fs::is_directory(dir_itr->status()))
                {
                    //this is a directory, maybe go inside!
                    //out <<" [dir] "<<dir_itr->path().string() <<std::endl;
                    //eeee bPopulateFiles(sBatesRoot, tFileArray, dir_itr->path().string(), nFileType, out,nMaxCount);
                    
                    
                    
                    //can we go down another level?
                    if(nMaxLevels > 0  || nMaxLevels == -1 )
                    {
                        int nNewMaxLevels = nMaxLevels-1;
                        
                        if(nMaxLevels == -1)
                            nNewMaxLevels = -1;
                        
                        bCreateFileList(out, dir_itr->path().string(), sExt, nNewMaxLevels, vFiles);
                    }
                }
                else if( fs::is_regular_file( dir_itr->status()))
                {
                    fs::path currentPath = dir_itr->path();
                    std::string sExtFile = currentPath.extension().string();
                    boost::to_upper(sExtFile);
                    
                    if ( sExtToCompare.size()==0 || boost::iequals(sExtFile, sExtToCompare) )
                    {
                        
                        file_element tElement;
                        tElement.sFullPath = currentPath.string();
                        tElement.sName     = currentPath.filename().string();
                        
                        vFiles.push_back(tElement);
                    }
                }
                else
                {
                    //out <<" [other] "<<dir_itr->path().string() <<std::endl;
                }
                
                
            } catch (const std::exception & ex)
            {
                std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
            }
            
        }
        
        
    }
    else if( fs::is_regular_file( myPath) )
    { //it is a file
        
        fs::path currentPath = myPath;
        std::string sExtFile = currentPath.extension().string();
        boost::to_upper(sExtFile);
        
        if ( sExtToCompare.size()==0 || boost::iequals(sExtFile, sExtToCompare) )
        {
            
            file_element tElement;
            tElement.sFullPath = currentPath.string();
            tElement.sName     = currentPath.filename().string();
            
            vFiles.push_back(tElement);
        }
        
    }
    
    return bStatus;
}

#endif
