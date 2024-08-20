#include "send_cgi_handle.hpp"

using std::string;
using std::stringstream;
using std::cerr;

#include <unistd.h>

// CGI directory
#define CGI_DIR "/path/to/cgi-bin/"
// Normal functioning messages
#define CONNECTION "Connection: keep-alive\n\n"
#define OK "HTTP/1.1 200 OK\n\n"
#define CGI_DIR "/path/to/cgi-bin/"

#define SEND_ERROR "HTTP/1.1 500 Internal Server Error. Error sending message. Attempt: "
#define FINAL_SEND_ERROR "HTTP/1.1 500 Internal Server Error. Failed to send message after final attempt.\n\n"
#define SOCKET_CLOSING_ERROR "Error closing socket\n\n"

// Modificación de la función para manejar datos POST
bool handle_cgi_request(const std::string& path, const std::string& postData, stringstream& message)
{
    if (path.find(CGI_DIR) == 0)
    {
        int pipefd[2];
        if (pipe(pipefd) != 0)
        {
            perror("pipe");
            return false;
        }

        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork");
            close(pipefd[0]);
            close(pipefd[1]);
            return false;
        }
        else if (pid == 0)
        {
            // Proceso hijo: ejecutar el script CGI

            // Redirigir stdin desde el pipe
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);
            close(pipefd[1]);

            // Redirigir la salida a un archivo temporal
            freopen("/tmp/cgi_output.txt", "w", stdout);

            // Ejecutar el script CGI
            execl(path.c_str(), path.c_str(), (char*)NULL);
            // Si execl retorna, hubo un error
            exit(EXIT_FAILURE);
        }
        else
        {
            // Proceso padre: enviar los datos POST al script CGI

            // Escribir los datos POST en el pipe y cerrarlo
            write(pipefd[1], postData.c_str(), postData.length());
            close(pipefd[0]);
            close(pipefd[1]);

            // Esperar a que el proceso hijo termine
            waitpid(pid, NULL, 0);

            // Leer y enviar la salida del script CGI
            FILE* cgi_output = fopen("/tmp/cgi_output.txt", "r");
            if (cgi_output)
            {
                char buffer[1024];
                while (fgets(buffer, sizeof(buffer), cgi_output))
                {
                    message << buffer;
                }
                fclose(cgi_output);
                return true;
            }
            else
            {
                perror("fopen");
                return false;
            }
        }
    }
    return false;
}

void send_response(int socket_id, const std::string& response)
{
    ssize_t bytes_sent;
    int send_attempts = 0;
    const int MAX_SEND_ATTEMPTS = 3;
    do {
        bytes_sent = send(socket_id, response.c_str(), response.size(), 0);
        if (bytes_sent == -1) {
            cerr << SEND_ERROR << send_attempts + 1 << "\n\n";
            send_attempts++;
            sleep(1); // Espera 1 segundo antes de intentar nuevamente
        }
    } while (bytes_sent == -1 && send_attempts < MAX_SEND_ATTEMPTS);

    if (bytes_sent == -1)
        cerr << FINAL_SEND_ERROR;
    if (close(socket_id) != 0)
        cerr << SOCKET_CLOSING_ERROR;
}
