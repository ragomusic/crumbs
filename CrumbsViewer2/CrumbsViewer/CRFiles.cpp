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
#include <iostream>
#ifdef _WIN32
#include "winsock2.h"
#endif
#include <stdio.h>

#include "CRFiles.h"


CRFile::CRFile()
{
    vClean();
}

CRFile::~CRFile()
{
    
}

void CRFile::vClean()
{
    
    m_nIndex = -1; //none!
    m_sBates.clear();
    m_sTIFFPath.clear();
    m_sOCRPath.clear();
    m_sTXTPath.clear();
    m_sText.clear(); //full text
    m_nDBID = 0; //by default first table
}

void CRFile::vPrint(std::ostream & myout)
{
    myout <<"("<<m_nDBID<<")["<<m_nIndex<<"]";
    myout <<" B:" <<m_sBates;
    myout <<" G:" <<m_sTIFFPath;
    myout <<" O:" <<m_sOCRPath;
    myout <<" T:" <<m_sTXTPath;
    
    myout <<" [["<<m_sText.substr(0,50)<<"...("<<m_sText.size()<<")]]";
}



/////////////////////
//////CRFile Array

CRFileArray::CRFileArray(int nInitialSize)
{
    vClean();
    bGrowArray(nInitialSize);
}

CRFileArray::~CRFileArray()
{
    
}

void CRFileArray::vClean()
{
    
}

void CRFileArray::vPrint(std::ostream & out)
{
    int ii;
    int nSize = (int)m_vFiles.size();
    
    for(ii=0;ii<nSize; ii++)
    {
        m_vFiles[ii].vPrint(out);
        out <<std::endl;
        
    }
    
}

int CRFileArray::nGetCount()
{
    return (int)m_vFiles.size();

}

bool CRFileArray::bGrowArray(int nNewSize)
{
    bool bStatus = false;
    
    CRFile tFile;
    int nSize = (int)m_vFiles.size();
    
    if(nSize < nNewSize)
    {
        
        m_vFiles.resize(nNewSize, tFile);
        
        int ii;
        for(ii=nSize; ii<nNewSize; ii++)
        {
            CRFile * pFile = pGetFile(ii);
            if(pFile)
            {
                pFile->m_nIndex = ii;
            }
        }
        
        bStatus = true;
        
    }

    
    return bStatus;

    
}

bool CRFileArray::bInsert(CRFile & tFile)
{
    bool bStatus = false;
    
    int nIndex = tFile.m_nIndex;
    
    if(nIndex >= m_vFiles.size())
    {
        bGrowArray(nIndex+1);
    }
    
    if(nIndex>-1 && nIndex<m_vFiles.size())
    {
        m_vFiles[nIndex] = tFile;
    }
    
    return bStatus;
}

CRFile * CRFileArray::pGetFile(int nIndex, bool bCreate)
{
    CRFile * pFile = NULL;
    
    
    if(nIndex>=m_vFiles.size() && bCreate)
    {
        bGrowArray(nIndex+1);
    }
    
    if(nIndex > -1 && nIndex<m_vFiles.size())
    {
        pFile = &m_vFiles[nIndex];
    }
    
    
    return pFile;
}
