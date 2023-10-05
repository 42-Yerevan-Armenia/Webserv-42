/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:29:26 by arakhurs          #+#    #+#             */
/*   Updated: 2023/10/05 18:59:45 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Webserv.hpp"

int main(int ac, char **av)
{
    std::string config;
    Parsing     cluster;
    Manager 	master;

    if (ac == 1 || ac == 2)
    {
        try
        {
            config = (ac == 1 ? "conf/default.conf" : av[1]);
            cluster.create(config);
            master.svrsetup(cluster.getServers());
			// master.svrrun();
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