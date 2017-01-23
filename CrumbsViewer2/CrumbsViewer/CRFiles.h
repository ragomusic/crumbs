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

#ifndef crumbs_db_test_CRFiles_h
#define crumbs_db_test_CRFiles_h

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>


//create file  structure
//create file populating code.


class CRFile
{
public:
    CRFile();
    ~CRFile();
    
    void vClean();
    void vPrint(std::ostream & myout);

    int m_nIndex; //bates based index

    std::string m_sBates;
    std::string m_sTIFFPath;
    std::string m_sOCRPath;
    std::string m_sTXTPath;
    std::string m_sText; //full text
    int m_nDBID;
};



class CRFileArray
{
public:
    
    CRFileArray(int nInitialSize=100);
    ~CRFileArray();
    
    void vClean();
    bool bInsert(CRFile & tFile);
    CRFile * pGetFile(int nIndex,bool bCreate = false);
    bool bGrowArray(int nNewSize);
    void vPrint(std::ostream & out);
    
    int nGetCount();
    
    
private:
    std::vector<CRFile> m_vFiles;
};


#endif
