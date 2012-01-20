/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * mulp
 * Copyright (C) Onur GUZEL 2010 <onur.oguzel@gmail.com>
 * 
 * mulp is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * mulp is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "SlackFrame.h"
#include "AboutDialog.h"

//IdInit
const long SlackFrame::ID_QUIT = wxNewId();
const long SlackFrame::ID_ABOUT = wxNewId ();
const long SlackFrame::ID_SETTINGS = wxNewId ();
const long SlackFrame::ID_HELP = wxNewId ();
const long SlackFrame::ID_LISTBOX = wxNewId ();
const long SlackFrame::ID_PAGESELECT = wxNewId ();
const long SlackFrame::ID_INSTALL_FILE = wxNewId ();
const long SlackFrame::ID_INSTALL_PLUGIN = wxNewId ();
const long SlackFrame::ID_SCAN_FILE = wxNewId ();
const long SlackFrame::ID_SCAN_PLUGIN = wxNewId ();


BEGIN_EVENT_TABLE(SlackFrame,wxFrame)
	//event table
	EVT_MENU(SlackFrame::ID_QUIT,SlackFrame::OnQuit)
	EVT_MENU(SlackFrame::ID_ABOUT,SlackFrame::OnAbout)
	EVT_MENU(SlackFrame::ID_HELP,SlackFrame::OnHelp)
EVT_LIST_ITEM_SELECTED(SlackFrame::ID_PAGESELECT,SlackFrame::OnListItemSelected)
END_EVENT_TABLE()

SlackFrame::SlackFrame(const wxString& title,const wxString& image,const wxPoint& posi,const wxSize& size) 
	: wxFrame(NULL,-1,title,posi,size)
{
	this->SetSizeHints( wxSize(800,600), wxDefaultSize );
	wxMenu *menuFile = new wxMenu;
	wxMenu *menuView = new wxMenu;
	wxMenu *menuSettings = new wxMenu;
	wxMenu *menuHelp = new wxMenu;

    menuFile->AppendSeparator();
    menuFile->Append( ID_QUIT, _("E&xit") );
	menuHelp->Append(ID_HELP,_("&Manual"));
	menuHelp->Append(ID_ABOUT,_("&About"));



	menuSettings->Append(ID_INSTALL_PLUGIN,_("&Install Plugin"));
	menuSettings->Append(ID_INSTALL_FILE,_("&Install File"));
	menuSettings->Append(ID_SCAN_PLUGIN,_("&Scan Plugins"));
	menuSettings->Append(ID_SCAN_FILE,_("&Scan Files"));
	

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, _("&File") );
	menuBar->Append( menuView, _("&View") );
	menuBar->Append( menuSettings, _("&Settings") );
	menuBar->Append( menuHelp, _("&Help") );

    SetMenuBar( menuBar );

    CreateStatusBar();
	SetStatusText( _("Welcome to ") + title );	

	wxBoxSizer *mulpSizer = new wxBoxSizer(wxVERTICAL);
	
	wxBoxSizer *imagePanelSizer = new wxBoxSizer(wxVERTICAL);

	wxPanel *imagePanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxSUNKEN_BORDER | wxALL | wxEXPAND );
	wxBoxSizer *imageSizer = new wxBoxSizer(wxHORIZONTAL);
	imagePanel->SetSizer(imageSizer);
	imagePanel->Layout();
	imageSizer->Fit(imagePanel);

	imagePanel->SetBackgroundColour(wxColour(255,255,255));
	
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImage::AddHandler(pngLoader);
	wxBitmap imagemulp;
	imagemulp.LoadFile(image, wxBITMAP_TYPE_PNG);
	wxStaticBitmap *m_bitmap = new wxStaticBitmap( imagePanel, wxID_ANY, imagemulp, wxDefaultPosition, wxDefaultSize, 0 );
	
	imageSizer->Add( m_bitmap, 1, wxEXPAND | wxALL, 4 );
	
	wxBoxSizer *bSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	plugin_pages = new wxListCtrl( this, ID_PAGESELECT, wxDefaultPosition, wxDefaultSize, wxLC_ICON | wxLC_ALIGN_LEFT | wxLC_ALIGN_TOP | wxLC_SINGLE_SEL | wxSUNKEN_BORDER );
	bSizer1->Add( plugin_pages, 2, wxEXPAND | wxALL, 4 );	
	
	buttonPanel = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxSUNKEN_BORDER | wxVSCROLL | wxHSCROLL );
	buttonPanel->SetScrollRate(10,10);
	gridSizer = new wxGridSizer( 3, 3, 0, 0 );

	buttonPanel->SetBackgroundColour( wxColour( 255, 255, 255 ) );
	buttonPanel->SetSizer( gridSizer );
	buttonPanel->Layout();
	gridSizer->Fit( buttonPanel );
	
	bSizer1->Add( buttonPanel, 6, wxEXPAND | wxALL, 4 );
	imagePanelSizer->Add(imagePanel,1,wxEXPAND | wxALL,4);
	
	mulpSizer->Add(imagePanelSizer,0,wxEXPAND | wxALL,4);
	mulpSizer->Add(bSizer1,1,wxEXPAND | wxALL,4);
	
	this->image = image;
	this->SetSizer( mulpSizer );
	this->Layout();

	//plugin_pages->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( SlackFrame::OnListItemSelected ), NULL, this );

}

SlackFrame::~SlackFrame()
{
	//plugin_pages->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( SlackFrame::OnListItemSelected ), NULL, this );
}



void SlackFrame::OnQuit(wxCommandEvent& event)
{
	int answer = wxMessageBox(_("Do you want to quit the application? ") + GetTitle(), _("Confirm Quit"), wxICON_QUESTION | wxYES_NO, this);

	SetStatusText(_("Exit"));

	if(answer == wxYES)
		Close(true);
}

void SlackFrame::OnAbout(wxCommandEvent& event)
{
	SetStatusText(_("About menu"));
	AboutDialog *aboutDialog = new AboutDialog(NULL,-1,GetTitle(),image,wxPoint(50, 50), wxSize(600,370));
	aboutDialog->setDevelopers(developers);
	aboutDialog->ShowModal();
	aboutDialog->Destroy();
}

void SlackFrame::OnHelp(wxCommandEvent& event)
{
	SetStatusText(_("About menu"));
	AboutDialog *aboutDialog = new AboutDialog(NULL,-1,GetTitle(),image,wxPoint(50, 50), wxSize(600,370));
	aboutDialog->setDevelopers(developers);
	aboutDialog->ShowModal();
	aboutDialog->Destroy();
}

void SlackFrame::OnListItemSelected(wxListEvent& event)
{
	gridSizer->Clear(true);
	buttonPanel->Hide();

	long itemIndex = -1;
 
  for (;;) 
  {
    itemIndex = plugin_pages->GetNextItem(itemIndex,
                                         wxLIST_NEXT_ALL,
                                         wxLIST_STATE_SELECTED);

	  if (itemIndex == -1) break;
	  
	  // Got the selected item index
	#ifdef DEBUG
		  std::cout << itemIndex  << " " << std::endl;
	#endif
	  SetStatusText(_("Page selection: ") + plugin_pages->GetItemText(itemIndex));

	  AddPlugins(itemIndex);
	  
	  
  }	
	buttonPanel->SetSize(wxDefaultSize);
	gridSizer->Layout();
	
	buttonPanel->Show();
}

void SlackFrame::Init()
{
	/**
	 * Initialize iterators for pages and plugins
	 *
	 */
	std::list<Page*>::iterator pageiter;
	
	wxImage::AddHandler( new wxPNGHandler );

	plugin_image_list = new wxImageList(48,48);

	for(pageiter = pages.begin(); pageiter != pages.end(); pageiter++)
	{
					Page *page = *pageiter;
					wxIcon icon;
					icon.LoadFile(wxString((page->getImage().c_str()),wxConvUTF8), wxBITMAP_TYPE_PNG);
					plugin_image_list->Add(icon);		
	}	
				  
	plugin_pages->SetImageList(plugin_image_list, wxIMAGE_LIST_NORMAL);
	
	for(pageiter = pages.begin(); pageiter != pages.end(); pageiter++)
	{
					Page *page = *pageiter;
					wxString title = wxString((page->getTitle()).c_str(),wxConvUTF8);
					
					wxListItem page_info;
			        page_info.SetId(page->getId());
			        page_info.SetText( title );
					page_info.SetAlign(wxLIST_FORMAT_LEFT);
			        plugin_pages->InsertItem(page_info);
					plugin_pages->SetItemImage(page_info,page->getId()-1);

	}
	AddPlugins(0);	
	
	plugin_pages->SetItemState(0, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
}

/**
 * Plugins are added as plugin buttons to button panel
 *
 */
void SlackFrame::AddPlugins(int itemIndex)
{
	 if(itemIndex != -1)
	{
		std::list<Page*>::iterator pageiter = pages.begin();
		std::advance(pageiter,itemIndex);
		Page *page = *pageiter;
		std::list<Plugin*>::iterator pluginiter;
		if(page->getPluginSize() > 1)
		{
			std::list<Plugin*> plugins = page->getPlugins();
			#ifdef DEBUG
						std::cout << plugins.size() << std::endl;
			#endif
	
			if(plugins.size() > 0)
			{
				
				for(pluginiter = plugins.begin(); pluginiter != plugins.end(); pluginiter++)
				{
					Plugin *plugin = *pluginiter;
					#ifdef DEBUG
										std::cout << plugin->getName() << std::endl;
					#endif
					PluginButton *button = new PluginButton(buttonPanel,wxID_ANY,wxString((plugin->getImage()).c_str(),wxConvUTF8),wxString((plugin->getTitle()).c_str(),wxConvUTF8),plugin);
					gridSizer->Add(button,2, wxEXPAND | wxALL,6);
				}
			}
			
		}
		
	}	
}