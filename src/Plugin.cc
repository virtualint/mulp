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

#include "Plugin.h"

Plugin::Plugin()
{
	name = "noname";
	type = NONAME;
}

Plugin::Plugin(std::string m_name, short m_type)
{
	name = m_name;
	type = m_type;
}

Plugin::~Plugin()
{
	
}

void Plugin::setName(std::string m_name)
{
	name = m_name;
}

void Plugin::setType(short m_type)
{
	type = m_type;
}

void Plugin::setImage(std::string m_image)
{
	image = m_image;
}

void Plugin::setTitle(std::string m_title)
{
	title = m_title;
}

void Plugin::Run() throw(NoProgramException)
{
	if(type == DIALOG)
	{
		#ifdef DEBUG
				std::cout << "plugin" << "run " << std::endl;
		#endif
		const char* plugin = name.c_str();
		void *hndl = dlopen(plugin, RTLD_NOW);
		if(hndl == NULL)
		{
		   std::cerr << dlerror() << std::endl;
		   exit(-1);
		}
		else
		{						
			DialogPlugin *(*mkr)()= (DialogPlugin*(*)())dlsym(hndl, "maker");
			DialogPlugin *dialogPlugin = (*mkr)();
			if(dialogPlugin)
			{
				dialogPlugin->load();
				dialogPlugin->run();
			}
		}
			
	}
	else if(type == PROGRAM)
	{
		#ifdef DEBUG
				std::cout << "program" << "run " << std::endl;
		#endif
		const char* program = name.c_str();

		pid_t pid = fork();

		if(pid == 0)
		{
			int returnExeclp = execlp(program,program,(char*) 0);


			if(returnExeclp == -1)
			{
				throw NoProgramException();
			}
			_exit(0);
		}
		else if(pid < 0)
		{
			std::cout << "failed to fork" << std::endl;
		}
		else
		{
			#ifdef DEBUG
						std::cout << "program" << std::endl;
			#endif
		}

		#ifdef DEBUG
				std::cout << pid << std::endl;
		#endif
		
	}
}
