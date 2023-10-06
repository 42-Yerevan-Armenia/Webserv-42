/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFile.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:03:04 by arakhurs          #+#    #+#             */
/*   Updated: 2023/10/06 21:24:13 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGFILE_HPP
# define CONFIGFILE_HPP

# include "Webserv.hpp"

class ConfigFile
{
    public:
        ConfigFile();
        ConfigFile(std::string const path);
        ~ConfigFile();

        int getSize();
        std::string getPath();
        std::string readFile(std::string path);
        static int  getType(std::string const path);
        static int  checkFile(std::string const path, int mode);
        static int  isFile(std::string const path, std::string const index);

    private:
        std::string _path;
        size_t		_size;
};

#endif