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

#ifndef _NODEINFO_H_
#define _NODEINFO_H_
#include <libxml++/libxml++.h>
#include <iostream>
#include <map>

enum NODE_TYPE {NULL_NODE=0,CONTENT_NODE,TEXT_NODE,COMMENT_NODE,ELEMENT_NODE};

class NodeInfo
{
	public:
		NodeInfo();
		NodeInfo(std::string,std::string,NODE_TYPE);
		~NodeInfo();
		std::string name;
		std::string value;
		NODE_TYPE type;
		std::map<std::string,std::string> attributes;
		xmlpp::Node::NodeList children;
		

	protected:

	private:

};

#endif // _NODEINFO_H_
