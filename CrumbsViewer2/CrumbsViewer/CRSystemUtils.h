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

#ifndef crumbs_db_test_CRSystemUtils_h
#define crumbs_db_test_CRSystemUtils_h

#include <string>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <fstream>


//#define BOOST_NO_CXX11_RVALUE_REFERENCES
//#include "boost/filesystem/operations.hpp"
//#include "boost/filesystem/path.hpp"
//#undef BOOST_NO_CXX11_RVALUE_REFERENCES


#include "CRFiles.h"

//namespace fs = boost::filesystem;


//bool bPopulateFiles(std::string &sBatesRoot ,CRFileArray &tFileArray, std::string sBasePath,int nFileType, std::ostream & out, int nMaxCount=-1);


////file system
struct file_element
{
    std::string sFullPath;
    std::string sName;
};

//bool bCreateFileList(std::ostream& out, const std::string &sBasePath, const std::string &sExt, int nMaxLevels, std::vector<file_element> &vFiles);

bool bCreateFileListV2(std::ostream& out, const std::string &sBasePath, const std::string &sExt, int nMaxLevels, std::vector<file_element> &vFiles);

#endif
