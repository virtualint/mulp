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

#include "PluginButton.h"

const long PluginButton::ID_IMAGEINFO = wxNewId();
const long PluginButton::ID_LABELINFO = wxNewId();

BEGIN_EVENT_TABLE(PluginButton, wxPanel)
	EVT_PAINT(PluginButton::OnPaint)
	EVT_ENTER_WINDOW(PluginButton::OnMouseOver)
	EVT_LEAVE_WINDOW(PluginButton::OnMouseOut)
	EVT_LEFT_DOWN(PluginButton::OnMouseLeftDown)
END_EVENT_TABLE()

PluginButton::PluginButton(wxWindow *parent,int id,const wxString &image,const wxString &title,Plugin *m_plugin) 
: wxPanel(parent, id, wxDefaultPosition, wxSize(160, 160), wxNO_BORDER|wxTAB_TRAVERSAL)
{
	parentPanel = parent;
	wxBoxSizer *buttonSizer = new wxBoxSizer(wxVERTICAL);
	this->SetBackgroundColour(wxColour(255,255,255));

	plugin = m_plugin;
	this->SetMaxSize(wxSize(160,160));
	this->SetMinSize(wxSize(160,160));
	imageinfo = new wxStaticBitmap(this,ID_IMAGEINFO,wxBitmap(image,wxBITMAP_TYPE_ANY));
	labelinfo = new wxStaticText( this, ID_LABELINFO, title, wxDefaultPosition, wxDefaultSize, 0 );

	/**
	 * Widgets must also use the events of the widget
	 *
	 */
	imageinfo->Connect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( PluginButton::OnMouseOver ), NULL, this );
	labelinfo->Connect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( PluginButton::OnMouseOver ), NULL, this );
	imageinfo->Connect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler(PluginButton::OnMouseOut), NULL, this);
	labelinfo->Connect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler(PluginButton::OnMouseOut), NULL, this);
	imageinfo->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler(PluginButton::OnMouseLeftDown), NULL, this);
	labelinfo->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler(PluginButton::OnMouseLeftDown), NULL, this);

	labelinfo->Wrap( -1);
	buttonSizer->Add(imageinfo,2,wxALIGN_CENTER|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL,0);
	buttonSizer->Add(labelinfo,2,wxALIGN_CENTER|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL,0);

	this->SetSizer(buttonSizer);
	this->Layout();
}

PluginButton::PluginButton()
{		
}

PluginButton::~PluginButton()
{
	imageinfo->Disconnect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( PluginButton::OnMouseOver ), NULL, this );
	labelinfo->Disconnect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( PluginButton::OnMouseOver ), NULL, this );
	imageinfo->Disconnect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler(PluginButton::OnMouseOut), NULL, this);
	labelinfo->Disconnect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler(PluginButton::OnMouseOut), NULL, this);
	imageinfo->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler(PluginButton::OnMouseLeftDown), NULL, this);
	labelinfo->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler(PluginButton::OnMouseLeftDown), NULL, this);

	delete imageinfo;
	delete labelinfo;
}

void PluginButton::OnMouseOver(wxMouseEvent& event)
{
	this->SetBackgroundColour(wxNullColour);	
}

void PluginButton::OnPaint(wxPaintEvent& event)
{	
}

void PluginButton::OnMouseOut(wxMouseEvent& event)
{
	this->SetBackgroundColour(wxColour(255,255,255));
}

void PluginButton::OnMouseLeftDown(wxMouseEvent& event)
{
	plugin->Run();	
}