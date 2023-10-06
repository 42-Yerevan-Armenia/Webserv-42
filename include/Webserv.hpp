/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:30:55 by arakhurs          #+#    #+#             */
/*   Updated: 2023/10/06 21:08:41 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

//String
# include <string>
# include <cstring>
# include <fcntl.h>
# include <dirent.h>

//Stream
# include <iostream>
# include <sstream>
# include <fstream>

//STL
# include <vector>
# include <map>

//System
# include <unistd.h>
# include <sys/stat.h>

//Network
# include <arpa/inet.h>

# include "Parsing.hpp"
# include "ConfigFile.hpp"
# include "Config.hpp"
# include "Location.hpp"
# include "Logger.hpp"
# include "CgiHandler.hpp"
# include "HttpRequest.hpp"
# include "Mime.hpp"

#define CONNECTION_TIMEOUT 60
#ifdef TESTER
    #define MESSAGE_BUFFER 40000 
#else
    #define MESSAGE_BUFFER 40000
#endif

#define MAX_URI_LENGTH 4096
#define MAX_CONTENT_LENGTH 30000000

std::string     statusCodeString(short statusCode);
std::string     getErrorPage(short statusCode);
int             ft_stoi(std::string str);
int             buildHtmlIndex(std::string &, std::vector<uint8_t> &, size_t &);
unsigned int    fromHexToDec(const std::string& nb);

template <typename T>
std::string toString(const T val)
{
    std::stringstream stream;
    stream << val;
    return stream.str();
}

#endif