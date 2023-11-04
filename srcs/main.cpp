/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:29:26 by arakhurs          #+#    #+#             */
/*   Updated: 2023/11/04 15:23:45 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Webserv.hpp"
#include "../include/Manager.hpp"

void sigpipeHandle(int sig) { if(sig) {}}

int main(int ac, char **av)
{

    if (ac == 1 || ac == 2)
    {
        try
        {
            std::string config;
            Parsing     cluster;
            Manager 	master;
            signal(SIGPIPE, sigpipeHandle);
            config = (ac == 1 ? "configs/default.conf" : av[1]);
            cluster.create(config);
            master.svrsetup(cluster.getServers());
			master.svrrun();
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
            return (1);
        }
    }
    else
    {
        std::cerr << "❌ Error: wrong arguments" << std::endl;
        return (1);
    }
    return (0);
}