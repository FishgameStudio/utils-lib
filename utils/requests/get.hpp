/* Get informations of a resource. */

#pragma once
#include <string>
#include <stdexcept>
#include <cstring>

#ifdef _WIN32
#    include <winsock2.h>
#    include <ws2tcpip.h>
#    pragma comment(lib, "ws2_32.lib")
using socklen_t = int;
#else
#    include <sys/socket.h>
#    include <netinet/in.h>
#    include <arpa/inet.h>
#    include <unistd.h>
#    include <netdb.h>
#endif

namespace requests {

    const int BUFFER_SIZE = 4096;

    class RESULT {
    private:
        int status_code;
        std::string html;
    public:
        RESULT(int status_code, std::string html) : status_code(status_code), html(html) {}
        int get_status_code() const {
            return status_code;
        }
        const std::string get_html() const {
            return html;
        }
    };
    
    RESULT get(const std::string& url) {

        /* Initialize Winsock */
        #ifdef _WIN32
            WSADATA wsaData;
            if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
                throw std::runtime_error("Failed to initialize Winsock");
            }
        #endif
        // Parse the URL
        std::string protocol, host, path;
        size_t pos = url.find("://");
        if (pos != std::string::npos) {
            protocol = url.substr(0, pos);
            host = url.substr(pos + 3);

            if (protocol != "https" && protocol != "http") {
                throw std::runtime_error("Only HTTP protocol is supported");
            }
        } else {
            host = url;
        }
        pos = host.find("/");
        if (pos != std::string::npos) {
            path = host.substr(pos);
            host = host.substr(0, pos);
        } else {
            path = "/";
        }

        // Create a socket
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            throw std::runtime_error("Failed to create socket");
        }
        // Resolve the host(DNS)
        struct hostent* server = gethostbyname(host.c_str());
        if (server == nullptr) {
            #ifdef _WIN32
                closesocket(sockfd);
                WSACleanup();
            #else
                close(sockfd);
            #endif
            throw std::runtime_error("Failed to resolve host");
        }

        // Set up the server address structure
        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(80);
        std::memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);
        // Connect to the server
        if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            throw std::runtime_error("Failed to connect to server");
        }

        // Send the HTTP GET request
        std::string request = "GET " + path + " HTTP/1.0\r\nHost: " + host + "\r\n\r\n";
        if (send(sockfd, request.c_str(), request.length(), 0) < 0) {
            #ifdef _WIN32
                closesocket(sockfd);
                WSACleanup();
            #else
                close(sockfd);
            #endif
            throw std::runtime_error("Failed to send request");
        }

        // Receive the response
        char buffer[BUFFER_SIZE];
        std::string response;
        int bytes_received;
        while ((bytes_received = recv(sockfd, buffer, BUFFER_SIZE - 1, 0)) > 0) {
            buffer[bytes_received] = '\0';
            response += buffer;
        }
        if (bytes_received < 0) {
            throw std::runtime_error("Failed to receive response");
        }
        // Close the socket
        #ifdef _WIN32
            closesocket(sockfd);
            WSACleanup();
        #else
            close(sockfd);
        #endif
        // Parse the response
        size_t header_end = response.find("\r\n\r\n");
        if (header_end == std::string::npos) {
            throw std::runtime_error("Invalid response");
        }
        std::string header = response.substr(0, header_end);
        std::string body = response.substr(header_end + 4);
        size_t status_pos = header.find(" ");        if (status_pos == std::string::npos) {
            throw std::runtime_error("Invalid response");
        }
        size_t status_end = header.find(" ", status_pos + 1);
        if (status_end == std::string::npos) {
            throw std::runtime_error("Invalid response");
        }
        std::string status_str = header.substr(status_pos + 1, status_end - status_pos - 1);
        int status_code = std::stoi(status_str);
        return RESULT(status_code, body);
    }

} // namespace requests