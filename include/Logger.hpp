/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:25:57 by arakhurs          #+#    #+#             */
/*   Updated: 2023/10/04 20:30:33 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_HPP
# define LOGGER_HPP

#include "Webserv.hpp"

#define RESET          "\x1B[0m"
#define RED            "\x1B[31m"
#define LIGHT_RED      "\x1B[91m"
#define WHITE          "\x1B[37m"
#define BLINK           "\x1b[5m"
#define YELLOW         "\x1B[33m"
#define LIGHT_BLUE     "\x1B[94m"
#define CYAN           "\x1B[36m"
#define DARK_GREY      "\x1B[90m"
#define LIGHTMAGENTA   "\x1B[95m"
#define GST             4;

enum LogPrio{
    DEBUG,
    INFO,
    ERROR
};

enum L_State{
    ON,
    OFF
};


enum Mode{
    CONSOLE_OUTPUT,
    FILE_OUTPUT
};

class Logger{

    public:
        static LogPrio                          prio;
        static L_State                          state;
        static std::string                      file_name;
        static std::string                      getCurrTime();
        static std::map<LogPrio, std::string>   prio_str;

        static void         setState(L_State);
        static void         enableFileLog();
        static void         setPrio(LogPrio);
        static void         setFilenName(std::string);
        static void         logMsg(const char *, Mode, const char*, ...);
    
    private:
        static std::map<LogPrio, std::string> initMap();

};

#endif