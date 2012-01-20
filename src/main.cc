/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.cc
 * Copyright (C) Onur GUZEL 2010 <onur.oguzel@gmail.com>
 *
	mulp is free software: you can redistribute it and/or modify it
	under the terms of the GNU General Public License as published by the
	Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	mulp is distributed in the hope that it will be useful, but
	WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
	See the GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License along
	with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include <wx/wx.h>
#include <iterator>
#include "SlackFrame.h"
#include "Parser.h"
#include "Plugin.h"
#include <exception>
#include "Page.h"

class MulpApp : public wxApp
{
	public:
		virtual bool OnInit();
};

IMPLEMENT_APP(MulpApp)

bool MulpApp::OnInit()
{
	const char *mulpFile = MULP_FILE_DIR MULP_FILE;
	std::string configFile= mulpFile;
	
	#ifdef LIBXMLCPP_EXCEPTIONS_ENABLED
	try
	{
	#endif //LIBXMLCPP_EXCEPTIONS_ENABLED 
		/**
		* Set parser and get pages and plugins
		*
		*/
		Parser parser;
		parser.set_substitute_entities(true); 
		parser.parse_file(configFile);

		if(parser)
		{
		parser.initSettings();
		}
			  
		wxString apptitle = wxString((parser.title).c_str(),wxConvUTF8);
		wxString appimage = wxString((parser.image).c_str(),wxConvUTF8);
			  
		SlackFrame *slackframe = new SlackFrame(apptitle,appimage, wxPoint(50, 50), wxSize(450, 340));

		if(parser)
		{
			slackframe->pages = (parser.pages);
			slackframe->developers = (parser.developers);
			slackframe->version = (parser.version);
		}
		
		/**
		* Set pages to slackframe to show the pages on the left
		*
		*/	  
		slackframe->Init();
			  
		slackframe->Show(TRUE);
	#ifdef LIBXMLCPP_EXCEPTIONS_ENABLED
	}
	catch(const xmlpp::exception& ex)
	{
		std::cout << "libxml++ exception: " << ex.what() << std::endl;
	}
	catch(const std::exception& ex)
	{
		std::cout << "mulp exception: " << ex.what() << std::endl;
	}		  
	#endif //LIBXMLCPP_EXCEPTIONS_ENABLED
	return TRUE;
}
