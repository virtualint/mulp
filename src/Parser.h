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

#ifndef _PARSER_H_
#define _PARSER_H_

#include <libxml++/libxml++.h>
#include <list>
#include <string>

#include "Plugin.h"
#include "Page.h"
#include "NodeInfo.h"


class Parser : public xmlpp::DomParser
{
public:
	Parser();
	~Parser();
	std::list<Plugin*> plugins;
	std::list<Page*> pages;
	std::list<std::string> developers;
	
	std::string title;
	std::string version;
	std::string image;
	std::string feed;
	
	void print_indentation(unsigned int);
	void initSettings();

	
	
	

protected:
//overrides:
#ifdef LIBXMLCPP_EXCEPTIONS_ENABLED

#  endif

private:
	Glib::ustring infoname;
	xmlpp::Node* getRootNode();
	NodeInfo* info(const xmlpp::Node* node);
	xmlpp::NodeSet find(const xmlpp::Node*,const Glib::ustring&);
	NodeInfo* getNodeInfoText(const xmlpp::Node* node);
	void setDevelopers();
	void setVersion();
	void setWebsite();
	void setAppTitle();
	void setFeed();
	void setImage();
	void setPages();
};

#endif // _PARSER_H_