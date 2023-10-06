/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 20:33:46 by arakhurs          #+#    #+#             */
/*   Updated: 2023/10/06 19:42:10 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "Webserv.hpp"
# include "HttpRequest.hpp"

class Response
{
    public:
        static     Mime _mime;
        Response();
        ~Response();
        Response(HttpRequest &);

        void        setCgiState(int);
        void        setServer(Config &);
        void        setRequest(HttpRequest &);
        void        setErrorResponse(short code);

        std::string     getRes();
        size_t          getLen() const;
        int             getCode() const;
        int             getCgiState();

        void        clear();
        void        cutRes(size_t);
        void        buildResponse();
        void        handleCgi(HttpRequest&);

        std::string     _response_content;
        CgiHandler		_cgi_obj;
        HttpRequest     request;
        std::string removeBoundary(std::string &body, std::string &boundary);

    private:
        Config                  _server;
        std::string             _location;
        std::string             _target_file;
        std::string             _response_body;
        std::vector<uint8_t>    _body;
        short                   _code;
        char                    *_res;
		int				        _cgi;
		int				        _cgi_fd[2];
        bool                    _auto_index;
        size_t                  _body_length;
		size_t			        _cgi_response_length;

        void    date();
        void    server();
        void    location();
        void    setHeaders();
        void    connection();
        void    contentType();
        void    contentLength();
        void    setStatusLine();
        void    buildErrorBody();
        void    setServerDefaultErrorPages();
        bool    reqError();
        int     readFile();
        int     buildBody();
        int     handleTarget();
        int     handleCgi(std::string &);
        int     handleCgiTemp(std::string &);
        size_t  file_size();
};

#endif
