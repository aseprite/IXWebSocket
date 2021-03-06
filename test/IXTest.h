/*
 *  IXTest.h
 *  Author: Benjamin Sergeant
 *  Copyright (c) 2018 Machine Zone. All rights reserved.
 */

#pragma once

#include <iostream>
#include <ixcobra/IXCobraConfig.h>
#include <ixsnake/IXAppConfig.h>
#include <ixwebsocket/IXGetFreePort.h>
#include <ixwebsocket/IXSocketTLSOptions.h>
#include <ixwebsocket/IXWebSocketServer.h>
#include <mutex>
#include <spdlog/spdlog.h>
#include <sstream>
#include <string>
#include <vector>

namespace ix
{
    // Sleep for ms milliseconds.
    void msleep(int ms);

    // Generate a relatively random string
    std::string generateSessionId();

    // Record and report websocket traffic
    void setupWebSocketTrafficTrackerCallback();
    void reportWebSocketTraffic();

    struct TLogger
    {
    public:
        template<typename T>
        TLogger& operator<<(T const& obj)
        {
            std::lock_guard<std::mutex> lock(_mutex);

            std::stringstream ss;
            ss << obj;
            spdlog::info(ss.str());
            return *this;
        }

    private:
        static std::mutex _mutex;
    };

    void log(const std::string& msg);

    bool startWebSocketEchoServer(ix::WebSocketServer& server);

    snake::AppConfig makeSnakeServerConfig(int port, bool preferTLS);

    SocketTLSOptions makeClientTLSOptions();
    SocketTLSOptions makeServerTLSOptions(bool preferTLS);
    std::string getHttpScheme();
    std::string getWsScheme(bool preferTLS);

    std::string makeCobraEndpoint(int port, bool preferTLS);

    void runPublisher(const ix::CobraConfig& config, const std::string& channel);
} // namespace ix
