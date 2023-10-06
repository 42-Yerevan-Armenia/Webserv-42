/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFile.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:03:00 by arakhurs          #+#    #+#             */
/*   Updated: 2023/10/06 21:23:50 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ConfigFile.hpp"

ConfigFile::ConfigFile() : _size(0) {}
ConfigFile::~ConfigFile(){}
ConfigFile::ConfigFile(std::string const path) : _path(path), _size(0){}

std::string ConfigFile::getPath(){return (this->_path);}

std::string ConfigFile::readFile(std::string path)
{
    if (path.empty() || path.length() == 0)
        return NULL;
    std::ifstream   config_file(path.c_str());
    if (!config_file || !config_file.is_open())
        return NULL;
    std::stringstream   str;
    str << config_file.rdbuf();
    return (str.str());
}

int  ConfigFile::getType(std::string const path)
{
    struct stat buffer;
    int         res;
    res = stat(path.c_str(), &buffer);

    if (res == 0)
    {
        if (buffer.st_mode & S_IFREG)
            return (1);
        else if (buffer.st_mode & S_IFREG) //WTF
            return (2);
        else
            return (3);
    }
    else
        return (-1);    
}

int ConfigFile::getSize(){return (_size);}
int  ConfigFile::checkFile(std::string const path, int mode){return (access(path.c_str(), mode));}

int  ConfigFile::isFile(std::string const path, std::string const index)
{
    if (getType(index) == 1 && checkFile(index, 4) == 0)
        return (0);
    if (getType(path + index) == 1 && checkFile(path + index, 4) == 0)
        return (0);
    return (-1);
}