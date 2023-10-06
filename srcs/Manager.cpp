/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manager.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:36:16 by arakhurs          #+#    #+#             */
/*   Updated: 2023/10/06 13:24:46 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Manager.hpp"

Manager::Manager(){}
Manager::~Manager(){}

void    Manager::svrsetup(std::vector<Config> servers)
{
    std::cout << std::endl;
    //Logger
    _servers = servers;
    // char    buf[INET_ADDRSTRLEN];
    bool    serverDub;

    for(std::vector<Config>::iterator it1 = _servers.begin(); it1 != _servers.end(); ++it1)
    {
        serverDub = false;
        for (std::vector<Config>::iterator it2 = _servers.begin(); it2 != it1; ++it2)
        {
            if (it2->getHost() == it1->getPort() && it2->getPort() == it1->getPort())
            {
            it1->setFd(it2->getFd());
            serverDub = true;
            }
        }
        if (!serverDub)
            it1->setupServer();
        //Logger
    }
}

void    Manager::addToSet(const int i, fd_set &set)
{
    FD_SET(i, &set);
    if (i > _biggest_fd)
        _biggest_fd = 1;
}

void    Manager::initializeSets()
{
    FD_ZERO(&_recv_fd_pool);
    FD_ZERO(&_write_fd_pool);

    for (std::vector<Config>::iterator it = _servers.begin(); it != _servers.end(); ++it)
    {
        if (listen(it->getFd(), 512) == -1)
        {
            // Logger
            exit(EXIT_FAILURE);
        }
        if (fcntl(it->getFd(), F_SETFL, O_NONBLOCK) < 0)
        {
            // Logger
            exit(EXIT_FAILURE);
        }
        addToSet(it->getFd(), _recv_fd_pool);
        _servers_map.insert(std::make_pair(it->getFd(), *it));
    }
    _biggest_fd = _servers.back().getFd();
}

void	Manager::removeFromSet(const int i, fd_set &set)
{
    FD_CLR(i, &set);
    if (i == _biggest_fd)
        _biggest_fd--;
}

void    Manager::acceptNewConnection(Config &serv)
{
    struct  sockaddr_in client_address;
    long                client_address_size = sizeof(client_address);
    int                 client_sock;
    Client              new_client(serv);
    // char                buf[INET_ADDRSTRLEN];

    if ( (client_sock = accept(serv.getFd(), (struct sockaddr *)&client_address, (socklen_t*)&client_address_size)) == -1)
    {
        // Logger
        return ;
    }
    // Logger
    addToSet(client_sock, _recv_fd_pool);
    if (fcntl(client_sock, F_SETFL, O_NONBLOCK) < 0)
    {
        // Logger
        removeFromSet(client_sock, _recv_fd_pool);
        close(client_sock);
        return ;
    }
    
}

void    Manager::svrrun()
{
    fd_set  recv_set_cpy;
    fd_set  write_set_cpy;
    int     select_ret;

    _biggest_fd = 0;
    initializeSets();
    struct timeval  timer;
    while (true)
    {
        timer.tv_sec = 1;
        timer.tv_usec = 0;
        recv_set_cpy = _recv_fd_pool;
        write_set_cpy = _write_fd_pool;

        if ((select_ret = select(_biggest_fd + 1, &recv_set_cpy, &write_set_cpy, NULL, &timer)) < 0)
        {
            // Logger
            exit(1);
            continue;
        }
        for (int i = 0; i <= _biggest_fd; ++i)
        {
            if (FD_ISSET(i, &recv_set_cpy) && _servers_map.count(i))
                acceptNewConnection(_servers_map.find(i)->second);
        }
    }
    
}
