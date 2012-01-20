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

#ifndef _SLACKFRAME_H_
#define _SLACKFRAME_H_
#include <wx/listctrl.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
#include <wx/listbox.h>
#include <wx/imaglist.h>
#include <wx/msgdlg.h>
#include <wx/colour.h>
#include <wx/bmpbuttn.h>
#include <wx/scrolwin.h>
#include <list>
#include "Plugin.h"
#include "Page.h"
#include "Parser.h"
#include "PluginButton.h"

class SlackFrame: public wxFrame 
{
	public:
		SlackFrame(const wxString& title,const wxString& image,const wxPoint& posi,const wxSize& size);
		virtual ~SlackFrame();
		wxListCtrl *plugin_pages;
		wxImageList *plugin_image_list;
		wxScrolledWindow *buttonPanel;
		wxGridSizer* gridSizer;
		std::list<Page*> pages;
		std::list<std::string> developers;
		std::string version;
		
		//Handlers
		void OnQuit(wxCommandEvent& event);
		void OnAbout(wxCommandEvent& event);
		void OnHelp(wxCommandEvent& event);
		virtual void OnListItemSelected(wxListEvent& event);

		void Init();
		
		void AddPlugins(int);

		
		//Identifiers
		static const long ID_QUIT;
		static const long ID_ABOUT;
		static const long ID_SETTINGS;
		static const long ID_HELP;
		static const long ID_LISTBOX;
		static const long ID_PAGESELECT;
		static const long ID_INSTALL_FILE;
		static const long ID_INSTALL_PLUGIN;
		static const long ID_SCAN_FILE;
		static const long ID_SCAN_PLUGIN;
	
		//Declarations
		DECLARE_EVENT_TABLE()
	protected:

	private:
		wxString image;

};

#endif // _SLACKFRAME_H_