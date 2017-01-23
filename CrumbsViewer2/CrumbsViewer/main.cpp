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

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".


#ifdef __BORLANDC__
#pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/snglinst.h>
#include <wx/cmdline.h>

//HACK TO GIVE FOCUS TO MAC APP PART 1
#ifdef __WXMAC__
#include <Carbon/Carbon.h>
extern "C" { void CPSEnableForegroundOperation(ProcessSerialNumber* psn); }

#endif

#include "CRMultipleInstances.h"

#include "crumbsviewer_frame.h"



// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

// the application icon (under Windows and OS/2 it is in resources and even
// though we could still include the XPM here it would be unused)
#if !defined(__WXMSW__) && !defined(__WXPM__)
//    #include "../sample.xpm"
#endif

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------



// Define a new application type, each program should derive a class from wxApp
class MyApp : public wxApp
{
public:
    // override base class virtuals
    // ----------------------------
    
    // this one is called on application startup and is a good place for the app
    // initialization (doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)
    virtual bool OnInit();
	virtual int OnExit();
    
    virtual void OnInitCmdLine(wxCmdLineParser& parser);
    virtual bool OnCmdLineParsed(wxCmdLineParser& parser);
    
private:
    wxSingleInstanceChecker * m_singleInstanceChecker;
    long m_nStartPage;
    //CVCollection tCollection;
    
    CVCollection m_tPageCollection;
    
    
    stServer *m_server;
};


static const wxCmdLineEntryDesc g_cmdLineDesc [] =
{
    { wxCMD_LINE_SWITCH, ("h"), ("help"), ("displays help on the command line parameters"), wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_HELP },
    { wxCMD_LINE_SWITCH, ("t"), ("test"), ("test switch"), wxCMD_LINE_VAL_NONE, wxCMD_LINE_PARAM_OPTIONAL  },
    { wxCMD_LINE_OPTION, ("m"), "message", "collection message", wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL },
    { wxCMD_LINE_OPTION, ("d"), "database", "table for pages", wxCMD_LINE_VAL_NUMBER , wxCMD_LINE_PARAM_OPTIONAL },
    { wxCMD_LINE_PARAM, NULL, NULL, ("page(s) of interest"), wxCMD_LINE_VAL_NUMBER , wxCMD_LINE_PARAM_OPTIONAL | wxCMD_LINE_PARAM_MULTIPLE},
    
    { wxCMD_LINE_NONE }
};




DECLARE_APP(MyApp)
// Create a new application object: this macro will allow wxWidgets to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)
IMPLEMENT_APP(MyApp)

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    
    
//	//check it is the only instance running
//	const wxString name = wxString::Format(wxT("%s"),
//                                           GetAppName().c_str());
//	m_checker = new wxSingleInstanceChecker(name);
//	if ( m_checker->IsAnotherRunning() )
//	{
//		wxLogMessage("Another instance of Hot Hand USB Editor is already running.");
//        return false;
//	}
//    
    
    
    
	
    
    // wxLogError(wxT("Hello world!\n"));
    /* this hack enables to have a GUI on Mac OSX even if the
     * program was called from the command line (and isn't a bundle) */
#ifdef __WXMAC__
    ProcessSerialNumber psn;
    
    GetCurrentProcess( &psn );
    CPSEnableForegroundOperation( &psn );
    SetFrontProcess( &psn );
#endif
    
    //#ifdef __WXWINDOWS__
    //rrrr9	 wxSystemOptions::SetOption(wxT("msw.window.no-clip-children"),wxT("1"));
    //#endif
    
    // wxLogError("Hello world");
    
    
    {
        //enable png support?
        wxImage::AddHandler(new wxPNGHandler);
        wxInitAllImageHandlers();
    }
    
    
    // call the base class initialization method, currently it only parses a
    // few common command-line options but it could be do more in the future
    if ( !wxApp::OnInit() )
        return false;
    
    
    //wxLogMessage(wxT(" HOla (1)\n"));
    
    //wxString cmdFilename = tCollection.toString();
    //ee wxString cmdFilename = wxString::Format("%ld", m_nStartPage);
    
    //NEW METHOD
    m_singleInstanceChecker = new wxSingleInstanceChecker();//MY_APP_NAME);
    // If using a single instance, use IPC to
    // communicate with the other instance
    if (!m_singleInstanceChecker->IsAnotherRunning())
    {
        // Create a new server
        m_server = new stServer;

        if ( !m_server->Create(wxT("4242")) )
        {
            wxLogDebug(wxT("Failed to create an IPC service."));
        }
    }
    else
    {
        //wxLogMessage(wxT(" HOla (2), command:")+cmdFilename);
        //wxLogNull logNull;
        // OK, there IS another one running, so try to connect to it
        // and send it any filename before exiting.
        stClient* client = new stClient;
        
        //wxLogMessage(wxT(" HOla (3)\n"));
        // ignored under DDE, host name in TCP/IP based classes
       // wxString hostName = wxT("localhost");
        // Create the connection
        
       // printf("HOla!\n");
        
        wxString server = wxT("4242");
        wxString hostName= wxGetHostName();
        
        wxConnectionBase* connection = client->MakeConnection(hostName,
                               server, wxT("MyApp"));
        if (connection)
        {
            
            wxString cmdFilename = wxString(m_tPageCollection.sToString().c_str(), wxConvUTF8);
            ///create this for the other instance!
            
            // Ask the other instance to open a file or raise itself
            connection->Execute(cmdFilename);
            connection->Disconnect();
            delete connection;
        }
        else
        {
            
            wxMessageBox(wxT("Sorry, the existing instance may be too busy too respond.\nPlease close any open dialogs and retry."),
                         MY_APP_NAME, wxICON_INFORMATION | wxOK);
        }
        delete client;
        
     //   wxLogMessage(wxT(" HOla (end)\n"));
        return false;
    }
    

    
#if 1
	// create the main application window
    wxString xsVersion = wxString::Format(wxT("%d.%d"),CRUMBS_VIEWER_VERSION_MAJOR, CRUMBS_VIEWER_VERSION_MINOR);    
#ifdef __WXMAC__
    xsVersion.append(wxString::Format(wxT( " mac(%d)"), CRUMBS_VIEWER_VERSION_REVISION_MAC));
#else
    xsVersion.append(wxString::Format(wxT( " win(%d)"), CRUMBS_VIEWER_VERSION_REVISION_WIN));
#endif

    
	
    CrumbsViewer_Frame * frame = new CrumbsViewer_Frame(NULL, wxID_ANY, wxT("Crumbs Document Viewer ") + xsVersion + wxT(" - crumbssoftware.com"));
    frame->vSetCollection(  m_tPageCollection );
    
    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
	//frame->vLoadDefault();
    frame->Show(true);
	//SetTopWindow(frame);
    
#endif
    
    
    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}

int MyApp::OnExit()
{
    delete m_singleInstanceChecker;
    
    return 0;
}

void MyApp::OnInitCmdLine(wxCmdLineParser& parser)
{
  //  wxCmdLineEntryDesc
    
    
    
    parser.SetDesc (g_cmdLineDesc);
    // must refuse '/' as parameter starter or cannot use "/path" style paths
    parser.SetSwitchChars (wxT("-"));
}

bool MyApp::OnCmdLineParsed(wxCmdLineParser& parser)
{
    m_tPageCollection.vClear();
    
    long temp;
    m_nStartPage=1;
    
    
    size_t nParams = parser.GetParamCount();
    
    for(int ii=0; ii< nParams; ii++)
    {
        
        wxString xsParam = parser.GetParam(ii);
        
        if(xsParam.size()>0)
        {
            xsParam.Replace(wxT(","),wxT(""));
            
            if(!xsParam.ToLong(&temp))
            {
                temp = 1;
            }
            
            
        }
//        if(!parser.GetParam(ii).ToLong(&temp) )
//        {
//            temp = 1;
//        }
        printf("page %d: %ld\n",ii, temp);
        collection_item tItem;
        tItem.lIndex = temp;
        tItem.nTable = -1;
        
        m_tPageCollection.bAddItem(tItem);
        
//        tCollection.bAddPage((int)temp);
        
        
        if(ii==0)
            m_nStartPage = temp;
    }
    
    if(m_tPageCollection.nGetSize()<1)
    {
        collection_item tItem;
        tItem.lIndex = 1;
        tItem.nTable = -1;
        //tCollection.bAddPage(1); //at least 1 page!
        m_tPageCollection.bAddItem(tItem);
    }
    
    
    //get message
    wxString xsMessage;
    
    if(parser.Found(wxT("m"),&xsMessage))
    {
        //found message
//        std::string sMessage = std::string(xsMessage.mb_str());
//        tCollection.bAddComment(sMessage);
        m_tPageCollection.m_sComment = xsMessage.ToStdString();
    }
    
    long lTable = 0;
    //look for database
    if(parser.Found(wxT("d"),&lTable))
    {
//        //found message
//        std::string sMessage = std::string(xsMessage.mb_str());
//        tCollection.bAddComment(sMessage);
    }
    else
    {
        lTable = 0;
    }

    m_tPageCollection.bSetTableTo((int)lTable,true);
   

    
    
    return true;
}



///multiple instances code
// Accepts a connection from another instance
wxConnectionBase *stServer::OnAcceptConnection(const wxString& topic)
{
  //  wxLogMessage(wxT("accept connection? topic:")+topic);
  //  printf(" tryin to accept connection\n");
    if (topic.Lower() == wxT("myapp"))
    {
//        // Check that there are no modal dialogs active
//        wxWindowList::Node* node = wxTopLevelWindows.GetFirst();
//        while (node)
//        {
//            wxDialog* dialog = wxDynamicCast(node->GetData(), wxDialog);
//            if (dialog && dialog->IsModal())
//            {
//                return NULL;
//            }
//            node = node->GetNext();
//        }
        return new stConnection();
    }
    else
        return NULL;
}





bool stConnection::OnExec(const wxString& topic,
                          const wxString& data)
{
    
    CVCollection tCollection;
    
    
    CrumbsViewer_Frame * frame = wxDynamicCast(wxGetApp().GetTopWindow(), CrumbsViewer_Frame);
    wxString filename = data;
    
    std::string sData = std::string(data.mb_str() );
    tCollection.vInitFromString(sData);
    
    if (filename.IsEmpty())
        
    {
        // Just raise the main window
        if (frame)
            frame->Raise();
    } else
    {
        frame->vSetCollection(tCollection);
        
        
    }
    return true;
}


