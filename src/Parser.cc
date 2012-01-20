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
#include <glibmm/convert.h> //For Glib::ConvertError
#include <iostream>
#include <cstdlib>
#include "Parser.h"

Parser::Parser() : xmlpp::DomParser()
{
}

Parser::~Parser()
{
	plugins.clear();
}

xmlpp::Node* Parser::getRootNode()
{
	return get_document()->get_root_node();
}

/**
 * Initialize all objects and read xml file
 *
 */
NodeInfo* Parser::info(const xmlpp::Node *node)
{
	NodeInfo *nodeInfo = new NodeInfo();	
	const xmlpp::ContentNode* nodeContent = dynamic_cast<const xmlpp::ContentNode*>(node);
	const xmlpp::TextNode* nodeText = dynamic_cast<const xmlpp::TextNode*>(node);
	const xmlpp::CommentNode* nodeComment = dynamic_cast<const xmlpp::CommentNode*>(node);

	if(nodeText && nodeText->is_white_space())
		return nodeInfo;

	const Glib::ustring nodename = node->get_name();

	if(!nodeText && !nodeComment && !nodename.empty())
	{

		const Glib::ustring namespace_prefix = node->get_namespace_prefix();
		if(namespace_prefix.empty())
		{
			nodeInfo->name = nodename;		  
		}
		else
		{
			nodeInfo->name = namespace_prefix + ":" + nodename;
		}
	}
	
	if(nodeText)
	{
		nodeInfo->value = nodeText->get_content();
		nodeInfo->type = TEXT_NODE;
	}
	else if(nodeComment)
	{
		nodeInfo->value = nodeComment->get_content();
		nodeInfo->type = COMMENT_NODE;	  
	}
	else if(nodeContent)
	{
		nodeInfo->value = nodeContent->get_content();
		nodeInfo->type = CONTENT_NODE;
	}
	else if(const xmlpp::Element* nodeElement = dynamic_cast<const xmlpp::Element*>(node))
	{
		nodeInfo->type = ELEMENT_NODE;
		const xmlpp::Element::AttributeList& attributes = nodeElement->get_attributes();
		  
		for(xmlpp::Element::AttributeList::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter)
		{
			const xmlpp::Attribute* attribute = *iter;
			const Glib::ustring namespace_prefix = attribute->get_namespace_prefix();	
			nodeInfo->attributes[attribute->get_name()] = attribute->get_value();
		}
		/*const xmlpp::Attribute* attribute = nodeElement->get_attribute("title");
		if(attribute)
		{
		  std::cout << "title found: =" << attribute->get_value() << std::endl;
		}*/
	}

	if(!nodeContent)
	{
		xmlpp::Node::NodeList list = node->get_children();
		xmlpp::Node::NodeList::iterator iter = list.begin();
		if(nodeInfo->type == ELEMENT_NODE)
		{
			const xmlpp::TextNode* nodeTextInfo = dynamic_cast<const xmlpp::TextNode*>(*iter);
			nodeInfo->value = nodeTextInfo->get_content();
			nodeInfo->type = TEXT_NODE;
			nodeInfo->children = list;
		}
	}
	#ifdef DEBUG
		std::cout << nodeInfo->name << " " <<  nodeInfo->value << " " << nodeInfo->type << " " << nodeInfo->children.size() << std::endl;
	#endif
	return nodeInfo;
}

NodeInfo* Parser::getNodeInfoText(const xmlpp::Node *node)
{
	NodeInfo *nodeInfo = new NodeInfo();
	const xmlpp::ContentNode* nodeContent = dynamic_cast<const xmlpp::ContentNode*>(node);
  	const xmlpp::TextNode* nodeText = dynamic_cast<const xmlpp::TextNode*>(node);		
	const xmlpp::CommentNode* nodeComment = dynamic_cast<const xmlpp::CommentNode*>(node);

	if(nodeText && nodeText->is_white_space())
		return nodeInfo;

	const Glib::ustring nodename = node->get_name();

	if(!nodeText && !nodeComment && !nodename.empty())
	{
		const Glib::ustring namespace_prefix = node->get_namespace_prefix();

		if(namespace_prefix.empty())
		{

			nodeInfo->name = nodename;		  
		}
		else
		{
			nodeInfo->name = namespace_prefix + ":" + nodename;
		}
	}

	if(nodeText)
	{
		nodeInfo->type = TEXT_NODE;
	}
	else if(nodeComment)
	{
		nodeInfo->type = COMMENT_NODE;	  
	}
	else if(nodeContent)
	{
		nodeInfo->type = CONTENT_NODE;
	}
	else
	{	  
		nodeInfo->type = ELEMENT_NODE;
	}	

	if(!nodeContent)
	{			
		xmlpp::Node::NodeList list = node->get_children();
		xmlpp::Node::NodeList::iterator iter = list.begin();
		if(nodeInfo->type == ELEMENT_NODE && list.size())
		{
			const xmlpp::TextNode* nodeTextInfo = dynamic_cast<const xmlpp::TextNode*>(*iter);
			nodeInfo->value = nodeTextInfo->get_content();
			nodeInfo->type = TEXT_NODE;
		}
	}
	#ifdef DEBUG
		std::cout << nodeInfo->name << " " <<  nodeInfo->value << " " << nodeInfo->type << std::endl;
	#endif
	return nodeInfo;	
}

void Parser::print_indentation(unsigned int indentation)
{
  for(unsigned int i = 0; i < indentation; ++i)
    std::cout << " ";
}

xmlpp::NodeSet Parser::find(const xmlpp::Node* node, const Glib::ustring& xpath)
{
	xmlpp::NodeSet set = node->find(xpath);
	return set;
}

void Parser::setDevelopers()
{
	xmlpp::NodeSet set = find(getRootNode(),"/mulp/information/developers/developer");
	for(xmlpp::NodeSet::iterator i = set.begin(); i != set.end(); ++i)
	{
		NodeInfo *nodeInfo = info((*i));
		developers.push_back(nodeInfo->value);
	}
}

void Parser::setVersion()
{
	xmlpp::NodeSet set = find(getRootNode(),"/mulp/information/version");
	xmlpp::NodeSet::iterator i = set.begin();
	NodeInfo *nodeInfo = getNodeInfoText((*i));
}

void Parser::setWebsite()
{
	xmlpp::NodeSet set = find(getRootNode(),"/mulp/information/website");
	for(xmlpp::NodeSet::iterator i = set.begin(); i != set.end(); ++i)
	{
		NodeInfo *nodeInfo = getNodeInfoText((*i));
	}
}

void Parser::setAppTitle()
{
	xmlpp::NodeSet set = find(getRootNode(),"/mulp/information/apptitle");
	xmlpp::NodeSet::iterator i = set.begin();
	NodeInfo *nodeInfo = getNodeInfoText((*i));
	title = nodeInfo->value;
}

void Parser::setFeed()
{
	xmlpp::NodeSet set = find(getRootNode(),"/mulp/setting/feed");
	xmlpp::NodeSet::iterator i = set.begin();
	NodeInfo *nodeInfo = getNodeInfoText((*i));
	feed = nodeInfo->value;
}

void Parser::setImage()
{
	xmlpp::NodeSet set = find(getRootNode(),"/mulp/setting/image");
	xmlpp::NodeSet::iterator i = set.begin();
	NodeInfo *nodeInfo = getNodeInfoText((*i));
	image = nodeInfo->value;
}

void Parser::setPages()
{
	Plugin *plugin;
	Page *page;
	xmlpp::NodeSet set = find(getRootNode(),"/mulp/pages/page");
	for(xmlpp::NodeSet::iterator i = set.begin(); i != set.end(); ++i)
	{
		NodeInfo *nodeInfo = info((*i));
		page = new Page;
		for(std::map<std::string,std::string>::iterator  iter= nodeInfo->attributes.begin(); iter != nodeInfo->attributes.end();++iter)
		{
			if((*iter).first == "title") page->setTitle ((*iter).second);
			if((*iter).first == "image") page->setImage ((*iter).second);
			if((*iter).first == "id") page->setId (atoi(((*iter).second).c_str()));
			if((*iter).first == "name") page->setName ((*iter).second);
		}
		xmlpp::NodeSet plugin_set = find((*i),"plugins/plugin");
		for(xmlpp::NodeSet::iterator ii = plugin_set.begin(); ii != plugin_set.end(); ++ii)
		{
			NodeInfo *pluginInfo = info((*ii));
			plugin = new Plugin();
			for(std::map<std::string,std::string>::iterator  plugin_iter= pluginInfo->attributes.begin(); plugin_iter != pluginInfo->attributes.end();++plugin_iter)
			{
				if((*plugin_iter).first == "name")
				{
					plugin->setName((*plugin_iter).second);
				}

				if((*plugin_iter).first == "type")
				{
					int type = -1;
					if((*plugin_iter).second == "dialog")
					{
						type = DIALOG;
					}
					else if((*plugin_iter).second == "program")
					{
						type = PROGRAM;
					}
					plugin->setType(type);
				}

				if((*plugin_iter).first == "image")
				{
					plugin->setImage((*plugin_iter).second);
				}

				if((*plugin_iter).first == "title")
				{
					plugin->setTitle((*plugin_iter).second);
				}				
			}
			page->plugins.push_back(plugin);
		}
		pages.push_back(page);
	}
}

void Parser::initSettings()
{
	setDevelopers();
	setVersion();
	setAppTitle();
	setFeed();
	setImage();
	setWebsite();
	setPages();
}
#ifdef LIBXMLCPP_EXCEPTIONS_ENABLED
#endif