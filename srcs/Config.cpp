/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:37:59 by arakhurs          #+#    #+#             */
/*   Updated: 2023/11/04 18:55:00 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Config.hpp"

Config::Config()
{
	_port = 0;
	_host = 0;
	_server_name = "";
	_root = "";
	_client_max_body_size = MAX_CONTENT_LENGTH;
	_index = "";
	_listen_fd = 0;
	_autoindex = false;
	initErrorPages();
}

Config::~Config(){}

Config::Config(const Config &copy)
{
	if (this != &copy)
	{
		_server_name = copy._server_name;
		_root = copy._root;
		_host = copy._host;
		_port = copy._port;
		_client_max_body_size = copy._client_max_body_size;
		_index = copy._index;
		_error_pages = copy._error_pages;
		_locations = copy._locations;
		_listen_fd = copy._listen_fd;
		_autoindex = copy._autoindex;
		_server_address = copy._server_address;

	}
	return ;
}

Config &Config::operator=(const Config &other)
{
	if (this != &other)
	{
		_server_name = other._server_name;
		_root = other._root;
		_port = other._port;
		_host = other._host;
		_client_max_body_size = other._client_max_body_size;
		_index = other._index;
		_error_pages = other._error_pages;
		_locations = other._locations;
		_listen_fd = other._listen_fd;
		_autoindex = other._autoindex;
		_server_address = other._server_address;
	}
	return (*this);
}

void Config::initErrorPages()
{
	_error_pages[301] = "";
	_error_pages[302] = "";
	_error_pages[400] = "";
	_error_pages[401] = "";
	_error_pages[402] = "";
	_error_pages[403] = "";
	_error_pages[404] = "";
	_error_pages[405] = "";
	_error_pages[406] = "";
	_error_pages[500] = "";
	_error_pages[501] = "";
	_error_pages[502] = "";
	_error_pages[503] = "";
	_error_pages[505] = "";
	_error_pages[505] = "";
}

void Config::setServerName(std::string server_name)
{
	checkToken(server_name);
	_server_name = server_name;
}

void Config::setHost(std::string parametr)
{
	checkToken(parametr);
	if (parametr == "localhost")
		parametr = "127.0.0.1";
	if (!isValidHost(parametr))
		throw ErrorException("Wrong syntax: host");
	_host = inet_addr(parametr.data());
}

void Config::setRoot(std::string root)
{
	checkToken(root);
	if (ConfigFile::getTypePath(root) == 2)
	{
		_root = root;
		return ;
	}
	char dir[1024];
	getcwd(dir, 1024);
	std::string full_root = dir + root;
	if (ConfigFile::getTypePath(full_root) != 2)
		throw ErrorException("Wrong syntax: root");
	_root = full_root;
}

void Config::setPort(std::string parametr)
{
	unsigned int port;
	
	port = 0;
	checkToken(parametr);
	for (size_t i = 0; i < parametr.length(); i++)
	{
		if (!std::isdigit(parametr[i]))
			throw ErrorException("Wrong syntax: port");
	}
	port = ft_stoi((parametr));
	if (port < 1 || port > 65636)
		throw ErrorException("Wrong syntax: port");
	_port = (uint16_t) port;
}

void Config::setClientMaxBodySize(std::string parametr)
{
	unsigned long body_size;
	
	body_size = 0;
	checkToken(parametr);
	for (size_t i = 0; i < parametr.length(); i++)
	{
		if (parametr[i] < '0' || parametr[i] > '9')
			throw ErrorException("Wrong syntax: client_max_body_size");
	}
	if (!ft_stoi(parametr))
		throw ErrorException("Wrong syntax: client_max_body_size");
	body_size = ft_stoi(parametr);
	_client_max_body_size = body_size;
}

void Config::setIndex(std::string index)
{
	checkToken(index);
	_index = index;
}

void Config::setAutoindex(std::string autoindex)
{
	checkToken(autoindex);
	if (autoindex != "on" && autoindex != "off")
		throw ErrorException("Wrong syntax: autoindex");
	if (autoindex == "on")
		_autoindex = true;
}

void Config::setErrorPages(std::vector<std::string> &parametr)
{
	if (parametr.empty())
		return;
	if (parametr.size() % 2 != 0)
		throw ErrorException ("Error page initialization faled");
	for (size_t i = 0; i < parametr.size() - 1; i++)
	{
		for (size_t j = 0; j < parametr[i].size(); j++) {
			if (!std::isdigit(parametr[i][j]))
				throw ErrorException("Error code is invalid");
		}
		if (parametr[i].size() != 3)
			throw ErrorException("Error code is invalid");
		short code_error = ft_stoi(parametr[i]);
		if (statusCodeString(code_error)  == "Undefined" || code_error < 400)
			throw ErrorException ("Incorrect error code: " + parametr[i]);
		i++;
		std::string path = parametr[i];
		checkToken(path);
		if (ConfigFile::getTypePath(path) != 2)
		{
			if (ConfigFile::getTypePath(_root + path) != 1)
				throw ErrorException ("Incorrect path for error page file: " + _root + path);
			if (ConfigFile::checkFile(_root + path, 0) == -1 || ConfigFile::checkFile(_root + path, 4) == -1)
				throw ErrorException ("Error page file :" + _root + path + " is not accessible");
		}
		std::map<short, std::string>::iterator it = _error_pages.find(code_error);
		if (it != _error_pages.end())
			_error_pages[code_error] = path;
		else
			_error_pages.insert(std::make_pair(code_error, path));
	}
}

void Config::setLocation(std::string path, std::vector<std::string> parametr)
{
	Location new_location;
	std::vector<std::string> methods;
	bool flag_methods = false;
	bool flag_autoindex = false;
	bool flag_max_size = false;
	int valid;

	new_location.setPath(path);
	for (size_t i = 0; i < parametr.size(); i++)
	{
		if (parametr[i] == "root" && (i + 1) < parametr.size())
		{
			if (!new_location.getRootLocation().empty())
				throw ErrorException("Root of location is duplicated");
			checkToken(parametr[++i]);
			if (ConfigFile::getTypePath(parametr[i]) == 2)
				new_location.setRootLocation(parametr[i]);
			else
				new_location.setRootLocation(_root + parametr[i]);
		}
		else if ((parametr[i] == "allow_methods" || parametr[i] == "methods") && (i + 1) < parametr.size())
		{
			if (flag_methods)
				throw ErrorException("Allow_methods of location is duplicated");
			std::vector<std::string> methods;
			while (++i < parametr.size())
			{
				if (parametr[i].find(";") != std::string::npos)
				{
					checkToken(parametr[i]);
					methods.push_back(parametr[i]);
					break ;
				}
				else
				{
					methods.push_back(parametr[i]);
					if (i + 1 >= parametr.size())
						throw ErrorException("Token is invalid");
				}
			}
			new_location.setMethods(methods);
			flag_methods = true;
		}
		else if (parametr[i] == "autoindex" && (i + 1) < parametr.size())
		{
			if (path == "/cgi-bin")
				throw ErrorException("Parametr autoindex not allow for CGI");
			if (flag_autoindex)
				throw ErrorException("Autoindex of location is duplicated");
			checkToken(parametr[++i]);
			new_location.setAutoindex(parametr[i]);
			flag_autoindex = true;
		}
		else if (parametr[i] == "index" && (i + 1) < parametr.size())
		{
			if (!new_location.getIndexLocation().empty())
				throw ErrorException("Index of location is duplicated");
			checkToken(parametr[++i]);
			new_location.setIndexLocation(parametr[i]);
		}
		else if (parametr[i] == "return" && (i + 1) < parametr.size())
		{
			if (path == "/cgi-bin")
				throw ErrorException("Parametr return not allow for CGI");
			if (!new_location.getReturn().empty())
				throw ErrorException("Return of location is duplicated");
			checkToken(parametr[++i]);
			new_location.setReturn(parametr[i]);
		}
		else if (parametr[i] == "alias" && (i + 1) < parametr.size())
		{
			if (path == "/cgi-bin")
				throw ErrorException("Parametr alias not allow for CGI");
			if (!new_location.getAlias().empty())
				throw ErrorException("Alias of location is duplicated");
			checkToken(parametr[++i]);
			new_location.setAlias(parametr[i]);
		}
		else if (parametr[i] == "cgi_ext" && (i + 1) < parametr.size())
		{
			std::vector<std::string> extension;
			while (++i < parametr.size())
			{
				if (parametr[i].find(";") != std::string::npos)
				{
					checkToken(parametr[i]);
					extension.push_back(parametr[i]);
					break ;
				}
				else
				{
					extension.push_back(parametr[i]);
					if (i + 1 >= parametr.size())
						throw ErrorException("Token is invalid");
				}
			}
			new_location.setCgiExtension(extension);
		}
		else if (parametr[i] == "cgi_path" && (i + 1) < parametr.size())
		{
			std::vector<std::string> path;
			while (++i < parametr.size())
			{
				if (parametr[i].find(";") != std::string::npos)
				{
					checkToken(parametr[i]);
					path.push_back(parametr[i]);
					break ;
				}
				else
				{
					path.push_back(parametr[i]);
					if (i + 1 >= parametr.size())
						throw ErrorException("Token is invalid");
				}
				if (parametr[i].find("/python") == std::string::npos && parametr[i].find("/bash") == std::string::npos)
					throw ErrorException("cgi_path is invalid");
			}
			new_location.setCgiPath(path);
		}
		else if (parametr[i] == "client_max_body_size" && (i + 1) < parametr.size())
		{
			if (flag_max_size)
				throw ErrorException("Maxbody_size of location is duplicated");
			checkToken(parametr[++i]);
			new_location.setMaxBodySize(parametr[i]);
			flag_max_size = true;
		}
		else if (i < parametr.size())
			throw ErrorException("Parametr in a location is invalid");
	}
	if (new_location.getPath() != "/cgi-bin" && new_location.getIndexLocation().empty())
		new_location.setIndexLocation(_index);
	if (!flag_max_size)
		new_location.setMaxBodySize(_client_max_body_size);
	valid = isValidLocation(new_location);
	if (valid == 1)
		throw ErrorException("Failed CGI validation");
	else if (valid == 2)
		throw ErrorException("Failed path in locaition validation");
	else if (valid == 3)
		throw ErrorException("Failed redirection file in locaition validation");
	else if (valid == 4)
		throw ErrorException("Failed alias file in locaition validation");
	_locations.push_back(new_location);
}

void	Config::setFd(int fd){_listen_fd = fd;}

bool Config::isValidHost(std::string host) const
{
	struct sockaddr_in sockaddr;
  	return (inet_pton(AF_INET, host.c_str(), &(sockaddr.sin_addr)) ? true : false);
}

bool Config::isValidErrorPages()
{
	std::map<short, std::string>::const_iterator it;
	for (it = _error_pages.begin(); it != _error_pages.end(); it++)
	{
		if (it->first < 100 || it->first > 599)
			return (false);
		if (ConfigFile::checkFile(getRoot() + it->second, 0) < 0 || ConfigFile::checkFile(getRoot() + it->second, 4) < 0)
			return (false);
	}
	return (true);
}

int Config::isValidLocation(Location &location) const
{
	if (location.getPath() == "/cgi-bin")
	{
		if (location.getCgiPath().empty() || location.getCgiExtension().empty() || location.getIndexLocation().empty())
			return (1);


		if (ConfigFile::checkFile(location.getIndexLocation(), 4) < 0)
		{
			std::string path = location.getRootLocation() + location.getPath() + "/" + location.getIndexLocation();
			if (ConfigFile::getTypePath(path) != 1)
			{				
				std::string root = getcwd(NULL, 0);
				location.setRootLocation(root);
				path = root + location.getPath() + "/" + location.getIndexLocation();
			}
			if (path.empty() || ConfigFile::getTypePath(path) != 1 || ConfigFile::checkFile(path, 4) < 0)
				return (1);
		}
		if (location.getCgiPath().size() != location.getCgiExtension().size())
			return (1);
		std::vector<std::string>::const_iterator it;
		for (it = location.getCgiPath().begin(); it != location.getCgiPath().end(); ++it)
		{
			if (ConfigFile::getTypePath(*it) < 0)
				return (1);
		}
		std::vector<std::string>::const_iterator it_path;
		for (it = location.getCgiExtension().begin(); it != location.getCgiExtension().end(); ++it)
		{
			std::string tmp = *it;
			if (tmp != ".py" && tmp != ".sh" && tmp != "*.py" && tmp != "*.sh")
				return (1);
			for (it_path = location.getCgiPath().begin(); it_path != location.getCgiPath().end(); ++it_path)
			{
				std::string tmp_path = *it_path;
				if (tmp == ".py" || tmp == "*.py")
				{
					if (tmp_path.find("python") != std::string::npos)
						location._ext_path.insert(std::make_pair(".py", tmp_path));
				}
				else if (tmp == ".sh" || tmp == "*.sh")
				{
					if (tmp_path.find("bash") != std::string::npos)
						location._ext_path[".sh"] = tmp_path;
				}
			}
		}
		if (location.getCgiPath().size() != location.getExtensionPath().size())
			return (1);
	}
	else
	{
		if (location.getPath()[0] != '/')
			return (2);
		if (location.getRootLocation().empty()) {
			location.setRootLocation(_root);
		}
		if (ConfigFile::isFile(location.getRootLocation() + location.getPath() + "/", location.getIndexLocation()))
			return (5);
		if (!location.getReturn().empty())
		{
			if (ConfigFile::isFile(location.getRootLocation(), location.getReturn()))
				return (3);
		}
		if (!location.getAlias().empty())
		{
			if (ConfigFile::isFile(location.getRootLocation(), location.getAlias()))
			 	return (4);
		}
	}
	return (0);
}

const uint16_t						&Config::getPort(){return (_port);}
const in_addr_t						&Config::getHost(){return (_host);}
const std::string					&Config::getRoot(){return (_root);}
const std::string					&Config::getIndex(){return (_index);}
const bool							&Config::getAutoindex(){return (_autoindex);}
const std::vector<Location>			&Config::getLocations(){return (_locations);}
const std::map<short, std::string>	&Config::getErrorPages(){return (_error_pages);}
const std::string					&Config::getServerName(){return (_server_name);}
const size_t						&Config::getClientMaxBodySize(){return (_client_max_body_size);}

const std::string &Config::getPathErrorPage(short key)
{
	std::map<short, std::string>::iterator it = _error_pages.find(key);
	if (it == _error_pages.end())
		throw ErrorException("Error_page does not exist");
	return (it->second);
}

const std::vector<Location>::iterator Config::getLocationKey(std::string key)
{
	std::vector<Location>::iterator it;
	for (it = _locations.begin(); it != _locations.end(); it++)
	{
		if (it->getPath() == key)
			return (it);
	}
	throw ErrorException("Error: path to location not found");
}

void Config::checkToken(std::string &parametr)
{
	size_t pos = parametr.rfind(';');
	if (pos != parametr.size() - 1)
		throw ErrorException("Token is invalid");
	parametr.erase(pos);
}

bool Config::checkLocaitons() const
{
	if (_locations.size() < 2)
		return (false);
	std::vector<Location>::const_iterator it1;
	std::vector<Location>::const_iterator it2;
	for (it1 = _locations.begin(); it1 != _locations.end() - 1; it1++) {
		for (it2 = it1 + 1; it2 != _locations.end(); it2++) {
			if (it1->getPath() == it2->getPath())
				return (true);
		}
	}
	return (false);
}

void	Config::setupServer(void)
{
	if ((_listen_fd = socket(AF_INET, SOCK_STREAM, 0) )  == -1 )
    {
		Logger::logMsg(RED, CONSOLE_OUTPUT, "webserv: socket error %s   Closing ....", strerror(errno));
        exit(EXIT_FAILURE);
    }

    int option_value = 1;
    setsockopt(_listen_fd, SOL_SOCKET, SO_REUSEADDR, &option_value, sizeof(int));
    memset(&_server_address, 0, sizeof(_server_address));
    _server_address.sin_family = AF_INET;
    _server_address.sin_addr.s_addr = _host;
    _server_address.sin_port = htons(_port);
    if (bind(_listen_fd, (struct sockaddr *) &_server_address, sizeof(_server_address)) == -1)
    {
		Logger::logMsg(RED, CONSOLE_OUTPUT, "webserv: bind error %s   Closing ....", strerror(errno));
        exit(EXIT_FAILURE);
    }
}

int   	Config::getFd() {return (_listen_fd); }