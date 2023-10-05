/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:02:10 by arakhurs          #+#    #+#             */
/*   Updated: 2023/10/04 19:49:34 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_HPP
# define PARSING_HPP

#include "Webserv.hpp"

class Config;

class Parsing
{
    public:
        Parsing();
        ~Parsing();

    int     create(const std::string &config_file);

    void    rmcomments(std::string &content);
    void    rmspace(std::string &content);
    void    splitservers(std::string &content);
    void    svrcreate(std::string &config, Config &server);

    size_t  svrstart(size_t start, std::string &content);
    size_t  svrend(size_t start, std::string &content);

    class ErrorException : public std::exception
    {
        public:
            ErrorException(std::string str) throw(){_text = "❌ Parsing: \033[31m" + str + "\033[0m";}
            virtual char const  *what() const throw(){return (_text.c_str());}
            virtual ~ErrorException() throw(){}        
        private:
            std::string _text;
    };

    private:
        size_t						_nb_server;
        std::vector<std::string>    _config;
        std::vector<Config>         _servers;
};

#endif