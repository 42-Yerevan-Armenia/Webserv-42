/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:50:47 by arakhurs          #+#    #+#             */
/*   Updated: 2023/10/04 20:03:21 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP

#include "Webserv.hpp"

class Location
{
    public:
        Location();
		~Location();
		Location(const Location &copy);
		Location &operator=(const Location &other);

 		void    setPath(std::string parametr);
		void    setAlias(std::string parametr);
		void    setReturn(std::string parametr);
		void    setAutoindex(std::string parametr);
		void    setMaxBodySize(std::string parametr);
		void    setRootLocation(std::string parametr);
		void    setIndexLocation(std::string parametr);
		void    setMaxBodySize(unsigned long parametr);
		void    setCgiPath(std::vector<std::string> path);
		void    setMethods(std::vector<std::string> methods);
		void    setCgiExtension(std::vector<std::string> extension);

		const std::string                           &getPath() const;
		const std::string                           &getAlias() const;
		const std::string                           &getReturn() const;
		const std::vector<short>                    &getMethods() const;
		const std::vector<std::string>              &getCgiPath() const;
		const bool                                  &getAutoindex() const;
		const unsigned long                         &getMaxBodySize() const;       
		const std::vector<std::string>              &getCgiExtension() const;
		const std::string                           &getRootLocation() const;
		const std::string                           &getIndexLocation() const;
		const std::map<std::string, std::string>    &getExtensionPath() const;

		std::map<std::string, std::string> _ext_path;
        std::string getPrintMethods() const; // for checking only ???

    private:
        std::string					_path;
		std::string					_root;
		std::string					_index;
		std::string					_return;
		std::string					_alias;
		std::vector<short>			_methods; // GET+ POST- DELETE- PUT- HEAD-
		std::vector<std::string>	_cgi_path;
		std::vector<std::string>	_cgi_ext;
		bool						_autoindex;
		unsigned long				_client_max_body_size;
};

#endif