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

#ifndef _PLUGIN_H_
#define _PLUGIN_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include "Exception.h"
#include <dlfcn.h>
#include "DialogPlugin.h"

enum PLUGIN_TYPE { NONAME, DIALOG, PROGRAM, INFO };

class Plugin
{
public:
	Plugin();
	Plugin(std::string,short);
	std::string getName(){return name;}
	short getType(){return type;}
	std::string getImage(){return image;}
	std::string getTitle() {return title;}
	~Plugin();

	void setName(std::string);
	void setType(short);
	void setImage(std::string);
	void setTitle(std::string);	

	void Run() throw(NoProgramException);

protected:

private:
	std::string name;
	std::string image;
	short type;
	std::string title;
};

#endif // _PLUGIN_H_
