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

#include "Page.h"
#include <iostream>

Page::Page()
{
	id = 0;
}

Page::Page(int m_id,std::string m_name,std::string m_title, std::string m_image)
{
	id = m_id;
	name = m_name;
	title = m_title;
	image = m_image;
}

Page::~Page()
{
	//Deconstructor
}


void Page::addPlugin(Plugin* plugin)
{
	#ifdef DEBUG
		std::cout << "Add plugin " << std::endl;
	#endif
	plugins.push_back(plugin);
}

std::list<Plugin*> Page::getPlugins()
{
	if(plugins.size() > 0)
	{
		return plugins;
	}
	else
	{
		throw NoPluginException();
	}
}

int Page::getPluginSize()
{
	if(!plugins.empty())
	{
		return (int) plugins.size();
	}
	else
	{
		return 0;
	}
}