/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:34:58 by arakhurs          #+#    #+#             */
/*   Updated: 2023/10/04 19:18:32 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "Webserv.hpp"

static std::string	srvparametrs[] = {"listen", "server_name", "root", "index", "allow_methods", "client_body_buffer_size"};

class Location;

class Config
{
    public:
        Config();
        ~Config();
        Config(const Config &copy);
		Config &operator=(const Config &other);

        int			getFd();
		void		setupServer();
		void		initErrorPages();
		bool		isValidErrorPages();
		bool		checkLocaitons() const;
		bool		isValidHost(std::string host) const;
		int			isValidLocation(Location &location) const;
		static void	checkToken(std::string &parametr);

		void setFd(int);
		void setRoot(std::string root);
		void setIndex(std::string index);
		void setHost(std::string parametr);
		void setPort(std::string parametr);
		void setAutoindex(std::string autoindex);
		void setServerName(std::string server_name);
		void setClientMaxBodySize(std::string parametr);
		void setErrorPages(std::vector<std::string> &parametr);
		void setLocation(std::string nameLocation, std::vector<std::string> parametr);

		const in_addr_t						&getHost();
		const uint16_t						&getPort();
		const std::string					&getRoot();
		const std::string					&getIndex();
		const std::string					&getServerName();
		const std::string					&getPathErrorPage(short key);
		const bool							&getAutoindex();
		const size_t						&getClientMaxBodySize();
		const std::map<short, std::string>	&getErrorPages();
		const std::vector<Location>			&getLocations();
		const std::vector<Location>::iterator getLocationKey(std::string key);

	class ErrorException : public std::exception
    {
        public:
            ErrorException(std::string str) throw(){_text = "❌ Server: \033[31m" + str + "\033[0m";}
            virtual char const  *what() const throw(){return (_text.c_str());}
            virtual ~ErrorException() throw(){}        
        private:
            std::string _text;
    };

    private:
		std::string						_server_name;
		std::string						_root;
		std::string						_index;
        
		uint16_t						_port;
		in_addr_t						_host;
        int     						_listen_fd;
		bool							_autoindex;
		unsigned long					_client_max_body_size;
        struct sockaddr_in 				_server_address;
		std::map<short, std::string>	_error_pages;
		std::vector<Location> 			_locations;
    };

#endif