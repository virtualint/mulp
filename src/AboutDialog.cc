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

#include "AboutDialog.h"

AboutDialog::AboutDialog( wxWindow* parent, wxWindowID id, const wxString& title,const wxString& image, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImage::AddHandler(pngLoader);
	
	wxBitmap imageSlackcp;
	
	imageSlackcp.LoadFile(image, wxBITMAP_TYPE_PNG);
	
	m_bitmap = new wxStaticBitmap( this, wxID_ANY, imageSlackcp, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_bitmap, 0, wxALL|wxEXPAND, 4 );

	m_textCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_AUTO_URL|wxTE_CENTRE|wxTE_MULTILINE|wxTE_READONLY|wxTE_RICH|wxTE_WORDWRAP  );
	bSizer2->Add( m_textCtrl, 1, wxALL|wxEXPAND, 4 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	m_closeButton = new wxButton( this, wxID_ANY, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_closeButton, 0, wxALL, 4 );
	
	bSizer2->Add( bSizer4, 0, wxALIGN_RIGHT|wxEXPAND|wxRIGHT|wxSHAPED, 4 );
	
	this->SetSizer( bSizer2 );
	this->Layout();
	
	// Connect Events
	m_closeButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboutDialog::OnCloseButtonClicked ), NULL, this );

	Center();
	
}

AboutDialog::~AboutDialog()
{
	// Disconnect Events
	m_closeButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboutDialog::OnCloseButtonClicked ), NULL, this );
}

void AboutDialog::setDevelopers(std::list<std::string> &developers)
{
	wxString developersInfo = _("MULP - Multipurpose software panel");

	developersInfo += _("\n");
	developersInfo += _("http://mulp.sourceforge.net");
	developersInfo += _("\n\n");
	developersInfo += _("Mulp developers");
	developersInfo += _("\n");
	developersInfo +=  _("Onur GUZEL <onur.oguzel@gmail.com>\n\n");
	                    
	developersInfo += GetTitle();
	                    
	developersInfo += _(" ");
	developersInfo += _("Developers");
	for(std::list<std::string>::iterator i = developers.begin();i != developers.end(); i++)
	{
		developersInfo += _("\n") + wxString((*i).c_str(),wxConvUTF8);
	}
	m_textCtrl->SetValue(developersInfo);
	m_textCtrl->SetBackgroundColour(wxColour(255,255,255));
}

void AboutDialog::OnCloseButtonClicked(wxCommandEvent& event)
{
	Close(true);
}

void AboutDialog::OnCreditsButtonClicked(wxCommandEvent& event)
{
	
}