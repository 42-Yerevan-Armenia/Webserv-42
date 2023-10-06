/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:30:55 by arakhurs          #+#    #+#             */
/*   Updated: 2023/10/06 14:18:41 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

//String
#include <string>
#include <cstring>
#include <fcntl.h>

//Stream
#include <iostream>
#include <sstream>
#include <fstream>

//STL
#include <vector>
#include <map>

//System
#include <unistd.h>
#include <sys/stat.h>

//Network
# include <arpa/inet.h>

#include "Parsing.hpp"
#include "ConfigFile.hpp"
#include "Config.hpp"
#include "Location.hpp"
#include "Logger.hpp"
#include "Manager.hpp"
#include "Client.hpp"
#include "Response.hpp"
#include "HttpRequest.hpp"

#define MAX_URI_LENGTH 4096
#define MAX_CONTENT_LENGTH 30000000

int ft_stoi(std::string str);
std::string statusCodeString(short statusCode);

#endif