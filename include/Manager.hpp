/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manager.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:36:14 by arakhurs          #+#    #+#             */
/*   Updated: 2023/10/05 20:24:21 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANAGER_HPP
# define MANAGER_HPP

#include "Webserv.hpp"

class Manager
{
    public:
        Manager();
        ~Manager();
        void    svrsetup(std::vector<Config>);
        void    svrrun();

    private:
        void    initializeSets();
        void    addToSet(const int i, fd_set &set);
        void    acceptNewConnection(Config &serv);
        void	removeFromSet(const int i, fd_set &set);

        std::vector<Config>     _servers;
        std::map<int, Config>   _servers_map;
        // std::map<int, Client>   _clients_map;
        fd_set                  _recv_fd_pool;
        fd_set                  _write_fd_pool;
        int                     _biggest_fd;
};

#endif