/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:52:17 by arakhurs          #+#    #+#             */
/*   Updated: 2023/11/04 18:41:33 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Location.hpp"

Location::Location()
{
	_path = "";
	_root = "";
	_autoindex = false;
	_index = "";
	_return = "";
	_alias = "";
	_client_max_body_size = MAX_CONTENT_LENGTH;
	_methods.reserve(5);
	_methods.push_back(1);
	_methods.push_back(0);
	_methods.push_back(0);
	_methods.push_back(0);
	_methods.push_back(0);
}

Location::~Location(){}

Location::Location(const Location &copy)
{
	_path = copy._path;
	_root = copy._root;
	_autoindex = copy._autoindex;
	_index = copy._index;
	_cgi_path = copy._cgi_path;
	_cgi_ext = copy._cgi_ext;
	_return = copy._return;
	_alias = copy._alias;
    _methods = copy._methods;
	_ext_path = copy._ext_path;
	_client_max_body_size = copy._client_max_body_size;
}

Location &Location::operator=(const Location &other)
{
	if (this != &other)
	{
		_path = other._path;
		_root = other._root;
		_autoindex = other._autoindex;
		_index = other._index;
		_cgi_path = other._cgi_path;
		_cgi_ext = other._cgi_ext;
		_return = other._return;
		_alias = other._alias;
		_methods = other._methods;
		_ext_path = other._ext_path;
		_client_max_body_size = other._client_max_body_size;
    }
	return (*this);
}

void Location::setRootLocation(std::string parametr)
{
	if (ConfigFile::getTypePath(parametr) != 2)
		throw Config::ErrorException("location of root");
	_root = parametr;
}

void Location::setMethods(std::vector<std::string> methods)
{
	_methods[0] = 0;
	_methods[1] = 0;
	_methods[2] = 0;
	_methods[3] = 0;
	_methods[4] = 0;

	for (size_t i = 0; i < methods.size(); i++)
	{
		if (methods[i] == "GET")
			_methods[0] = 1;
		else if (methods[i] == "POST")
			_methods[1] = 1;
		else if (methods[i] == "DELETE")
			_methods[2] = 1;
		else if (methods[i] == "PUT")
			_methods[3] = 1;
		else if (methods[i] == "HEAD")
			_methods[4] = 1;
		else
			throw Config::ErrorException("Allow method not supported " + methods[i]);
	}
}

void Location::setAutoindex(std::string parametr)
{
	if (parametr == "on" || parametr == "off")
		_autoindex = (parametr == "on");
	else
		throw Config::ErrorException("Wrong autoindex");
}

void Location::setPath(std::string parametr){_path = parametr;}
void Location::setAlias(std::string parametr){_alias = parametr;}
void Location::setReturn(std::string parametr){_return = parametr;}
void Location::setIndexLocation(std::string parametr){_index = parametr;}
void Location::setCgiPath(std::vector<std::string> path){_cgi_path = path;}
void Location::setMaxBodySize(unsigned long parametr){_client_max_body_size = parametr;}
void Location::setCgiExtension(std::vector<std::string> extension){_cgi_ext = extension;}


void Location::setMaxBodySize(std::string parametr)
{
	unsigned long body_size = 0;

	for (size_t i = 0; i < parametr.length(); i++)
	{
		if (parametr[i] < '0' || parametr[i] > '9')
			throw Config::ErrorException("Wrong syntax: client_max_body_size");
	}
	if (!ft_stoi(parametr))
		throw Config::ErrorException("Wrong syntax: client_max_body_size");
	body_size = ft_stoi(parametr);
	_client_max_body_size = body_size;
}

const std::string                           &Location::getPath() const{return (_path);}
const std::string                           &Location::getAlias() const{return (_alias);}
const std::string                           &Location::getReturn() const{return (_return);}
const std::vector<short>                    &Location::getMethods() const{return (_methods);}
const std::vector<std::string>              &Location::getCgiPath() const{return (_cgi_path);}
const std::string                           &Location::getRootLocation() const{return (_root);}
const bool                                  &Location::getAutoindex() const{return (_autoindex);}
const std::string                           &Location::getIndexLocation() const{return (_index);}
const std::vector<std::string>              &Location::getCgiExtension() const{return (_cgi_ext);}
const std::map<std::string, std::string>    &Location::getExtensionPath() const{return (_ext_path);}
const unsigned long                         &Location::getMaxBodySize() const{return (_client_max_body_size);}

std::string Location::getPrintMethods() const
{
	std::string res;
	if (_methods[4])
		res.insert(0, "HEAD");
	if (_methods[3])
	{
		if (!res.empty())
			res.insert(0, ", ");
		res.insert(0, "PUT");
	}
	if (_methods[2])
	{
		if (!res.empty())
			res.insert(0, ", ");
		res.insert(0, "DELETE");
	}
	if (_methods[1])
	{
		if (!res.empty())
			res.insert(0, ", ");
		res.insert(0, "POST");
	}
	if (_methods[0])
	{
		if (!res.empty())
			res.insert(0, ", ");
		res.insert(0, "GET");
	}
	return (res);
}
