/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 20:25:18 by arakhurs          #+#    #+#             */
/*   Updated: 2023/10/06 14:26:41 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Client.hpp"

Client::Client(){_last_msg_time = time(NULL);}
Client::~Client(){}

Client::Client(const Client &copy)
{
	if (this != &copy)
	{
		_client_socket = copy._client_socket;
		_client_address = copy._client_address;
		request = copy.request;
		response = copy.response;
		server = copy.server;
		_last_msg_time = copy._last_msg_time;

	}
	return ;
}

Client &Client::operator=(const Client & other)
{
	if (this != &other)
	{
		_client_socket = other._client_socket;
		_client_address = other._client_address;
		request = other.request;
		response = other.response;
		server = other.server;
		_last_msg_time = other._last_msg_time;
	}
	return (*this);
}

Client::Client(Config &server)
{
    setServer(server);
    request.setMaxBodySize(server.getClientMaxBodySize());
    _last_msg_time = time(NULL);
}

void    Client::setSocket(int &sock)			{_client_socket = sock;}
void    Client::setAddress(sockaddr_in &addr)	{_client_address =  addr;}
void    Client::setServer(Config &server)		{response.setServer(server);}
void    Client::updateTime()					{_last_msg_time = time(NULL);}

const HttpRequest			&Client::getRequest() const		{return (request);}
const int					&Client::getSocket() const		{return (_client_socket);}
const time_t				&Client::getLastTime() const	{return (_last_msg_time);}
const struct sockaddr_in	&Client::getAddress() const		{return (_client_address);}

void    Client::buildResponse()
{
    response.setRequest(request);
    response.buildResponse();
}


void    Client::clearClient()
{
    response.clear();
    request.clear();
}