/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 20:25:07 by arakhurs          #+#    #+#             */
/*   Updated: 2023/10/06 21:21:42 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Webserv.hpp"
# include "HttpRequest.hpp"
# include "Response.hpp"

class Client
{
    public:
        Client();
        ~Client();
        Client(Config &);
        Client(const Client &copy);
	    Client &operator=(const Client &other);

        const int                 &getSocket() const;
        const struct sockaddr_in  &getAddress() const;
        const HttpRequest         &getRequest() const;
        const time_t              &getLastTime() const;

        void                updateTime();
        void                clearClient();
        void                buildResponse();
        void                setSocket(int &);
        void                setServer(Config &);
        void                setAddress(sockaddr_in &);

        Response            response;
        HttpRequest         request;
        Config              server;

    private:
        int                 _client_socket;
        struct sockaddr_in  _client_address;
        time_t              _last_msg_time;
};

#endif