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

#ifndef CrumbsViewer_CRMultipleInstances_h
#define CrumbsViewer_CRMultipleInstances_h

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/ipc.h"
#define MY_APP_NAME wxT("crumbs_documenta_viewer")

// Connection class, for use by both communicating instances
class stConnection : public wxConnection
{
public:
    stConnection() :wxConnection() {/*wxLogMessage(wxT("new connection\n")); */}
    ~stConnection() {}
    //bool OnExecute(const wxString& topic, wxChar*data, int size, wxIPCFormat format);
    
    bool OnExec(const wxString& WXUNUSED(topic),
                const wxString& WXUNUSED(data));

};


//////////////////////
///////////////////////


// Server class, for listening to connection requests
class stServer: public wxServer
{
public:
    stServer() : wxServer() {/* wxLogMessage(wxT("New Server\n")); */}
    wxConnectionBase *OnAcceptConnection(const wxString& topic);
};


//////////////////////
///////////////////////



// Client class, to be used by subsequent instances in OnInit
class stClient: public wxClient
{
public:
    stClient() :wxClient() { /* wxLogMessage(wxT("New client\n"));*/ };
    wxConnectionBase *OnMakeConnection() {
       // wxLogMessage(wxT("Making new connection\n"));
        return new stConnection; }
};



#endif
