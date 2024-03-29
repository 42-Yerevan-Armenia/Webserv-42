/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 20:35:25 by arakhurs          #+#    #+#             */
/*   Updated: 2023/10/06 20:19:02 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_REQUEST_HPP
# define HTTP_REQUEST_HPP

# include "Webserv.hpp"

enum HttpMethod
{
    GET,
    POST,
    DELETE,
    PUT,
    HEAD,
    NONE
};

enum ParsingState
{
    Request_Line,
    Request_Line_Post_Put,
    Request_Line_Method,
    Request_Line_First_Space,
    Request_Line_URI_Path_Slash,
    Request_Line_URI_Path,
    Request_Line_URI_Query,
    Request_Line_URI_Fragment,
    Request_Line_Ver,
    Request_Line_HT,
    Request_Line_HTT,
    Request_Line_HTTP,
    Request_Line_HTTP_Slash,
    Request_Line_Major,
    Request_Line_Dot,
    Request_Line_Minor,
    Request_Line_CR,
    Request_Line_LF,
    Field_Name_Start,
    Fields_End,
    Field_Name,
    Field_Value,
    Field_Value_End,
    Chunked_Length_Begin,
    Chunked_Length,
    Chunked_Ignore,
    Chunked_Length_CR,
    Chunked_Length_LF,
    Chunked_Data,
    Chunked_Data_CR,
    Chunked_Data_LF,
    Chunked_End_CR,
    Chunked_End_LF,
    Message_Body,
    Parsing_Done
};

class HttpRequest
{
    public:
        HttpRequest();
        ~HttpRequest();

        void        setMaxBodySize(size_t);
        void        setMethod(HttpMethod &);
        void        setBody(std::string name);
        void        setHeader(std::string &, std::string &);
        
        std::string                                 &getPath();
        std::string                                 &getBody();
        std::string                                 &getQuery();
        std::string                                 &getFragment();
        std::string                                 &getBoundary();
		std::string                                 getMethodStr();
        std::string                                 getServerName();
        std::string                                 getHeader(std::string const &);
        bool                                        getMultiformFlag();
        HttpMethod                                  &getMethod();
		const std::map<std::string, std::string>    &getHeaders() const;
        

        void        clear();
        void        printMessage();
        void        cutReqBody(int bytes);
        void        feed(char *data, size_t size);
        short       errorCode();
        bool        keepAlive();
        bool        parsingCompleted();
    
    private:
        std::string                         _path;
        std::string                         _query;
        std::string                         _storage;
        std::string                         _fragment;
        std::string                         _boundary;
        std::string                         _body_str;
        std::string                         _server_name;
        std::string                         _key_storage;
        std::vector<u_int8_t>               _body;
        std::map<u_int8_t, std::string>     _method_str;
        std::map<std::string, std::string>  _request_headers;
        ParsingState                        _state;
        HttpMethod                          _method;
        size_t                              _body_length;
        size_t                              _chunk_length;
        size_t                              _max_body_size;
        u_int8_t                            _ver_major;
        u_int8_t                            _ver_minor;
        short                               _error_code;
        short                               _method_index;
        bool                                _body_flag;
        bool                                _chunked_flag;
        bool                                _complete_flag;
        bool                                _body_done_flag;
        bool                                _multiform_flag;
        bool                                _fields_done_flag;

        void            _handle_headers();
};

#endif