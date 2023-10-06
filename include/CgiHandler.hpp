/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:42:49 by arakhurs          #+#    #+#             */
/*   Updated: 2023/10/06 21:20:50 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIHANDLER_HPP
# define CGIHANDLER_HPP

# include "Webserv.hpp"

class HttpRequest;

class CgiHandler
{
    public:
        CgiHandler();
		~CgiHandler();
		CgiHandler(std::string path);
		CgiHandler(CgiHandler const &copy);
		CgiHandler &operator=(CgiHandler const &other);

		void setCgiPid(pid_t cgi_pid);
		void setCgiPath(const std::string &cgi_path);

		const pid_t &getCgiPid() const;
		const std::string &getCgiPath() const;
		const std::map<std::string, std::string> &getEnv() const;
		std::string	getPathInfo(std::string& path, std::vector<std::string> extensions);

		std::string decode(std::string &path);
		void clear();
        void execute(short &error_code);
		void initEnv(HttpRequest& req, const std::vector<Location>::iterator it_loc);
        void initEnvCgi(HttpRequest& req, const std::vector<Location>::iterator it_loc);
        int findStart(const std::string path, const std::string delim);

        int	pipe_in[2];
		int	pipe_out[2];
    
    private:
		int									_exit_status;
		char                                **_ch_env;
		char                                **_argv;
		pid_t								_cgi_pid;
		std::string							_cgi_path;
        std::map<std::string, std::string>	_env;
};

#endif
