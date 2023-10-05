/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:45:58 by arakhurs          #+#    #+#             */
/*   Updated: 2023/10/05 19:03:27 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Parsing.hpp"

Parsing::Parsing(){}
Parsing::~Parsing(){}

void    Parsing::rmcomments(std::string &content)
{
    size_t  pos;

    pos = content.find('#');
    while (pos != std::string::npos)
    {
        size_t  pos_end;
        pos_end = content.find('\n', pos);
        content.erase(pos, pos_end - pos);
        pos = content.find('#');
    }
    if (content.empty())
        throw ErrorException("File is empty, only comments");
}

void    Parsing::rmspace(std::string &content)
{
    size_t  i = 0;

    while (content[i] && isspace(content[i]))
        i++;
    content = content.substr(i);
    i = content.length() - 1;
    while (i > 0 && isspace(content[i]))
        i--; 
    content = content.substr(0, i + 1);    
}

size_t  Parsing::svrstart(size_t start, std::string &content)
{
    size_t  i;
    
    for (i = start; content[i]; i++)
    {
        if (content[i] == 's')
            break;
        if (!isspace(content[i]))
            throw ErrorException("server {...}");
    }
    if (!content[i])
        return (start);
    if (content.compare(i, 6, "server") != 0)
        throw ErrorException("server {...}");
    i += 6;
    while (content[i] && isspace(content[i]))
        i++;
    if (content[i] == '{')
        return (i);
    else
        throw ErrorException("server {...}");
}

size_t  Parsing::svrend(size_t start, std::string &content)
{
    size_t  i;
    size_t  scope = 0;

    for (i = start + 1; content[i]; i++)
    {
        if (content[i] == '{')
            scope++;
        if (content[i] == '}')
        {
            if (!scope)
                return (i);
            scope--;
        }
    }
    return (start);
}

void    Parsing::splitservers(std::string &content)
{
    size_t  start = 0;
    size_t  end = 1;

    if (content.find("server", 0) == std::string::npos)
        throw ErrorException("Didn't find \033[36mserver\033[31m in .conf");
    while (start != end && start < content.length())
    {
        start = svrstart(start, content);
        end = svrend(start, content);
        if (start == end)
            throw ErrorException("Lost something {} 👀");
        _config.push_back(content.substr(start, end - start + 1));
        _nb_server++;
        start = end = 1;
    }
}

std::vector<std::string> splitParametrs(std::string line, std::string sep)
{
	std::vector<std::string>	str;
	std::string::size_type		start, end;

	start = end = 0;
	while (1)
	{
		end = line.find_first_of(sep, start);
		if (end == std::string::npos)
			break;
		std::string tmp = line.substr(start, end - start);
		str.push_back(tmp);
		start = line.find_first_not_of(sep, end);
		if (start == std::string::npos)
			break;
	}
	return (str);
}

void Parsing::svrcreate(std::string &config, Config &server)
{
	std::vector<std::string>	parametrs;
	std::vector<std::string>	error_codes;
	int		flag_loc = 1;
	bool	flag_autoindex = false;
	bool	flag_max_size = false;

    parametrs = splitParametrs(config += ' ', std::string(" \n\t"));
    if (parametrs.size() < 3)
		throw  ErrorException("Failed server validation");
    for (size_t i = 0; i < parametrs.size(); i++)
    {
        if (parametrs[i] == "listen" && (i + 1) < parametrs.size() && flag_loc)
        {
            if (server.getPort())
                throw ErrorException("Port is duplicated");
            server.setPort(parametrs[++i]);
        }
		else if (parametrs[i] == "location" && (i + 1) < parametrs.size())
        {
            std::string path;
            i++;
            if (parametrs[i] == "{" || parametrs[i] == "}")
                throw ErrorException("server{ Lost something {} 👀 }");
            path = parametrs[i];
            std::vector<std::string> codes;
            if (parametrs[++i] != "{")
                throw ErrorException("server{ Lost something {} 👀 }");
            i++;
            while (i < parametrs.size() && parametrs[i] != "}")
                codes.push_back(parametrs[i++]);
            server.setLocation(path, codes);
            if (i < parametrs.size() && parametrs[i] != "}")
                throw ErrorException("server{ Lost something {} 👀 }");
            flag_loc = 0;
        }
        else if (parametrs[i] == "host" && (i + 1) < parametrs.size() && flag_loc)
        {
            if (server.getHost())
                throw ErrorException("Host is duplicated");
            server.setHost(parametrs[++i]);
        }
		else if (parametrs[i] == "root" && (i + 1) < parametrs.size() && flag_loc)
		{
            if (!server.getRoot().empty())
                throw ErrorException("Root is duplicated");
            server.setRoot(parametrs[++i]);
        }
        else if (parametrs[i] == "error_page" && (i + 1) < parametrs.size() && flag_loc)
        {
            while (++i < parametrs.size())
            {
                error_codes.push_back(parametrs[i]);
                if (parametrs[i].find(';') != std::string::npos)
                    break;
                if (i + 1 >= parametrs.size())
                    throw ErrorException("Wrong character out of server scope{}");
            }
        }
        else if (parametrs[i] == "client_max_body_size" && (i + 1) < parametrs.size() && flag_loc)
        {
            if (flag_max_size)
                throw ErrorException("Client_max_body_size is duplicated");
            server.setClientMaxBodySize(parametrs[++i]);
            flag_max_size = true;
        }
        else if (parametrs[i] == "server_name" && (i + 1) < parametrs.size() && flag_loc)
        {
            if (!server.getServerName().empty())
				throw  ErrorException("Server_name is duplicated");
			server.setServerName(parametrs[++i]);   
        }
        else if (parametrs[i] == "index" && (i + 1) < parametrs.size() && flag_loc)
        {
			if (!server.getIndex().empty())
				throw  ErrorException("Index is duplicated");
			server.setIndex(parametrs[++i]);            
        }
        else if (parametrs[i] == "autoindex" && (i + 1) < parametrs.size() && flag_loc)
        {
			if (flag_autoindex)
				throw ErrorException("Autoindex of server is duplicated");
			server.setAutoindex(parametrs[++i]);
			flag_autoindex = true;
        }
        else if (parametrs[i] != "}" && parametrs[i] != "{")
        {
            if (!flag_loc)
 				throw  ErrorException("Parametrs after location");
			else
				throw  ErrorException("Unsupported directive");           
        }
    }
	if (server.getRoot().empty())
		server.setRoot("/;");
	if (server.getHost() == 0)
		server.setHost("localhost;");
	if (server.getIndex().empty())
		server.setIndex("index.html;");
	if (ConfigFile::isFile(server.getRoot(), server.getIndex()))
		throw ErrorException("Index from config file not found or unreadable");
	if (server.checkLocaitons())
		throw ErrorException("Locaition is duplicated");
	if (!server.getPort())
		throw ErrorException("Port not found");
	server.setErrorPages(error_codes);
	if (!server.isValidErrorPages())
		throw ErrorException("Incorrect path for error page or number of error");   
}

void Parsing::svrcheck()
{
    std::vector<Config>::iterator   it1;
    std::vector<Config>::iterator   it2;

    for (it1 = _servers.begin(); it1 != _servers.end() - 1; it1++)
        for (it2 = it1 + 1; it2 != _servers.end(); it2++)
            if (it1->getPort() == it2->getPort() && it1->getHost() == it2->getHost() && it1->getServerName() == it2->getServerName())
                throw ErrorException("Failed server validation");
}

int Parsing::create(const std::string &config_file)
{
    std::string content;
    ConfigFile  file(config_file);

    if (file.getType(file.getPath()) != 1)
        throw ErrorException("File is invalid");
    if (file.checkFile(file.getPath(), 4) == -1)
        throw ErrorException("File isn't accessible");
    content = file.readFile(config_file);
    if (content.empty())
        throw ErrorException("File is empty");
    rmcomments(content);
    rmspace(content);
    splitservers(content);
    if (_config.size() != _nb_server)
        throw ErrorException("Wrong size"); //WTF ???
    for (size_t i = 0; i < _nb_server; i++)
    {
        Config server;
        svrcreate(_config[i], server);
        _servers.push_back(server);
    }
    if (_nb_server > 1)
        svrcheck();
    return (0);
}

std::vector<Config>	Parsing::getServers(){return (this->_servers);}
