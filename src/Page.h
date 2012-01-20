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

#ifndef _PAGE_H_
#define _PAGE_H_
#include <string>
#include "Plugin.h"
#include <list>
#include <exception>
#include "Exception.h"

class Page
{
public:
	Page();
	Page(int,std::string,std::string,std::string);
	~Page();
	std::list<Plugin*> plugins;
	void addPlugin(Plugin*);
	void setId(int m_id) {id = m_id;}
	void setName(std::string m_name) { name = m_name;}
	void setTitle(std::string m_title) {title = m_title;}
	void setImage(std::string m_image) {image = m_image;}
	int getId(){return id;}
	std::list<Plugin*> getPlugins();
	int getPluginSize();
	std::string getName() {return name;}
	std::string getTitle() {return title;}
	std::string getImage() {return image;}
	
protected:

private:
	std::string name;
	int id;
	std::string title;
	std::string image;
};
#endif // _PAGE_H_