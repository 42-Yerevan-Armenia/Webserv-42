/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manager.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:36:14 by arakhurs          #+#    #+#             */
/*   Updated: 2023/10/06 20:15:44 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANAGER_HPP
# define MANAGER_HPP

# include "Webserv.hpp"
# include "Client.hpp"
# include "Response.hpp"

class Manager
{
    public:
        Manager();
        ~Manager();
        void    svrsetup(std::vector<Config>);
        void    svrrun();

    private:
        void checkTimeout();
        void initializeSets();
        void assignServer(Client &);
        void handleReqBody(Client &);
        void closeConnection(const int);
        void acceptNewConnection(Config &);
        void addToSet(const int , fd_set &);
        void readRequest(const int &, Client &);
        void sendResponse(const int &, Client &);
        void removeFromSet(const int , fd_set &);
        void sendCgiBody(Client &, CgiHandler &);
        void readCgiResponse(Client &, CgiHandler &);

        int                     _biggest_fd;
        fd_set                  _recv_fd_pool;
        fd_set                  _write_fd_pool;
        std::vector<Config>     _servers;
        std::map<int, Config>   _servers_map;
        std::map<int, Client>   _clients_map;
};

#endif