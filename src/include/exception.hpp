#ifndef ParGen_EXCEPTION_DEF
#define ParGen_EXCEPTION_DEF

#include <ostream>
#include <exception>
#include <optional>
#include <functional>
#include <utility>
#include <filesystem>

#include <Util.hpp>
#include <Pxml.hpp>

namespace Exception{

    struct Exception : public std::runtime_error {
        Exception(std::string msg) : std::runtime_error(msg) {}
    };

    struct Warning {
        Warning(std::string msg){
            if(handler){
                handler->operator()(msg);
            }
        }
        Warning(const char* msg){
            Warning(std::string(msg));
        }
        static void regist(std::function<void(std::string)> handler){
            Warning::handler.emplace(handler);
        };
    private:
        static std::optional<std::function<void(std::string)>> handler;
    };

    struct SyntaxError : public Exception {
        PXML::Position pos;
        SyntaxError(std::string msg, PXML::Position pos) : 
            Exception(msg), pos(pos){}
    };
}

#endif