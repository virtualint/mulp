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

#ifndef _PLUGINBUTTON_H_
#define _PLUGINBUTTON_H_
#include <wx/wx.h>
#include <wx/event.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/colour.h>
#include "Plugin.h"

class PluginButton: public wxPanel
{
public:
	PluginButton(wxWindow*,int,const wxString&,const wxString&,Plugin*);
	PluginButton();
	virtual ~PluginButton();
	void OnPaint(wxPaintEvent& event);
	void OnMouseOver(wxMouseEvent& event);
	void OnMouseOut(wxMouseEvent& event);
	void OnMouseLeftDown(wxMouseEvent& event);

	static const long ID_IMAGEINFO;
	static const long ID_LABELINFO;
protected:

private:
	DECLARE_EVENT_TABLE()
	wxStaticBitmap *imageinfo;
	wxStaticText *labelinfo;
	wxWindow *parentPanel;
	Plugin *plugin;
};

#endif // _PLUGINBUTTON_H_