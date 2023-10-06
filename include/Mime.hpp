/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mime.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:48:39 by arakhurs          #+#    #+#             */
/*   Updated: 2023/10/06 19:40:15 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MIME_HPP
# define MIME_HPP

# include "Webserv.hpp"

class Mime
{
    public:
        Mime();
        std::string getMimeType(std::string extension);
 
    private:
        std::map<std::string, std::string> _mime_types;
        
};

#endif