/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:29:26 by arakhurs          #+#    #+#             */
/*   Updated: 2023/10/04 14:59:02 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Webserv.hpp"

int main(int ac, char **av)
{
    std::string config;
    Parsing     cluster;

    if (ac == 1 || ac == 2)
    {
        try
        {
            config = (ac == 1 ? "conf/default.conf" : av[1]);
            cluster.create(config);
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