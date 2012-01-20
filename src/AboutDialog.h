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

#ifndef _ABOUTDIALOG_H_
#define _ABOUTDIALOG_H_

#include <wx/intl.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/dialog.h>
#include <wx/textctrl.h>
#include <list>

class AboutDialog : public wxDialog 
{
	private:
		wxString image;
		
	protected:
		wxStaticBitmap* m_bitmap;
		wxTextCtrl *m_textCtrl;
		wxButton* m_closeButton;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCreditsButtonClicked( wxCommandEvent& event );
		virtual void OnCloseButtonClicked( wxCommandEvent& event );


		
	
	public:
		
		AboutDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxString& image = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,370 ), long style = wxDEFAULT_DIALOG_STYLE );
		~AboutDialog();
		void setDevelopers(std::list<std::string>&);
	
};

#endif // _ABOUTDIALOG_H_
