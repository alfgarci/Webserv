#!/bin/bash

clear

echo "$(tput setaf 5)*********************************************************"
echo "*                  Pruebas parser                       *"
echo "*********************************************************"

echo "$(tput setaf 3)*****************************************************"
echo "*                  Entradas correctas               *"
echo "*****************************************************"

# Prueba 1
echo "$(tput setaf 10)Prueba 1: ./webserv \"GET /index.html HTTP/1.1\nHost: www.example.com\nConnection: keep-alive\""
echo "$(tput setaf 9)"
./webserv $'GET /index.html HTTP/1.1\nHost: www.example.com\nConnection: keep-alive'
read foo

# Prueba 2
echo "$(tput setaf 10)Prueba 2 (espacio extra en Host): ./webserv \"GET /index.html HTTP/1.1\nHost:     www.example.com    \nConnection: keep-alive\""
echo "$(tput setaf 9)"
./webserv $'GET /index.html HTTP/1.1\nHost:     www.example.com\nConnection: keep-alive'
read foo

# Prueba 3
echo "$(tput setaf 10)Prueba 3 (mayúsculas y minúsculas en el nombre de los headers): ./webserv \"GET /index.html HTTP/1.1\nHOST: www.example.com\ncOnNeCtIoN: keep-alive\""
echo "$(tput setaf 9)"
./webserv $'GET /index.html HTTP/1.1\nHost: www.example.com\nConnection: keep-alive'
read foo

# Prueba 4
echo "$(tput setaf 10)Prueba 4: ./webserv \"DELETE /file.txt HTTP/1.1\nHost: www.example.com\""
echo "$(tput setaf 9)"
./webserv $'DELETE /file.txt HTTP/1.1\nHost: www.example.com'
read foo

# Prueba 5
echo "$(tput setaf 10)Prueba 5: ./webserv \"POST /login HTTP/1.1\nHost: www.example.com\nContent-Type: application/json\nContent-Length: 32\n\n{\"username\": \"test\", \"password\": \"1234\"}\""
echo "$(tput setaf 9)"
./webserv $'POST /login HTTP/1.1\nHost: www.example.com\nContent-Type: application/json\nContent-Length: 40\n\n{\"username\": \"test\", \"password\": \"1234\"}'
read foo

# Prueba 6
echo "$(tput setaf 10)Prueba 6: ./webserv \"POST /login HTTP/1.1\n\nHost: www.example.com\n\nContent-Type: application/json\nTransfer-Encoding: chunked\n\n\28\n{\"username\": \"test\", \"password\": \"1234\"}\n0\n"
echo "$(tput setaf 9)"
./webserv $'POST /login HTTP/1.1\nHost: www.example.com\nContent-Type: application/json\nTransfer-Encoding: chunked\n\n28\n{\"username\": \"test\", \"password\": \"1234\"}\n0\n'
read foo

# Prueba 7
echo "$(tput setaf 10)Prueba 7: (se comprueba que con GET se ignoran los campos relativos al cuerpo de la petición) ./webserv \"GET /login HTTP/1.1\nHost: www.example.com\nContent-Type: application/json\nContent-Length: 32\n\n{\"username\": \"test\", \"password\": \"1234\"}\""
echo "$(tput setaf 9)"
./webserv $'GET /login HTTP/1.1\nHost: www.example.com\nContent-Type: application/json\nContent-Length: 40\n\n{\"username\": \"test\", \"password\": \"1234\"}'
read foo

# Prueba 8
echo "$(tput setaf 10)Prueba 8: (se comprueba que con DELETE se ignoran los campos relativos al cuerpo de la petición) ./webserv \"POST /login HTTP/1.1\n\nHost: www.example.com\n\nContent-Type: application/json\nTransfer-Encoding: chunked\n\n\28\n{\"username\": \"test\", \"password\": \"1234\"}\n0\n"
echo "$(tput setaf 9)"
./webserv $'DELETE /login HTTP/1.1\nHost: www.example.com\nContent-Type: application/json\nTransfer-Encoding: chunked\n\n28\n{\"username\": \"test\", \"password\": \"1234\"}\n0\n'
read foo

# Prueba 9
echo "$(tput setaf 10)Prueba 9: ./webserv \"POST /login HTTP/1.1\n\nHost: www.example.com\n\nContent-Type: application/json\nTransfer-Encoding: chunked\n\n5\nHola \n7\nMundo!\n0\n"
echo "$(tput setaf 9)"
./webserv $'POST /login HTTP/1.1\nHost: www.example.com\nContent-Type: application/json\nTransfer-Encoding: chunked\n\n5\nHola \n7\nMundo!\n0\n'

read foo

echo "$(tput setaf 3)*****************************************************"
echo "*            Errores en uso del programa            *"
echo "*****************************************************"

echo "$(tput setaf 10)Prueba 10: Método erróneo ./webserv \"PATCH /resource HTTP/1.1\nHost: www.example.com\""
echo "$(tput setaf 9)"
./webserv $'PATCH /resource HTTP/1.1\nHost: www.example.com'
read foo

echo "$(tput setaf 10)Prueba 11: Versión HTTP no soportada (1) ./webserv \"GET /index.html HTTP/1.0\nHost: www.example.com\nConnection: keep-alive\""
echo "$(tput setaf 9)"
./webserv $'GET /index.html HTTP/1.0\nHost: www.example.com\nConnection: keep-alive'
read foo

echo "$(tput setaf 10)Prueba 12: Versión HTTP no soportada (2)./webserv \"GET /index.html HTTP/2.0\nHost: www.example.com\""
echo "$(tput setaf 9)"
./webserv $'GET /index.html HTTP/2.0\nHost: www.example.com'
read foo

echo "$(tput setaf 10)Prueba 13: Método omitido ./webserv \"/resource HTTP/1.1\nHost: www.example.com\""
echo "$(tput setaf 9)"
./webserv $'/resource HTTP/1.1\nHost: www.example.com'
read foo

echo "$(tput setaf 10)Prueba 14: Error tipográfico en la versión HTTP ./webserv \"GET /index.html HPPT/1.1n\nHost: www.example.com\""
echo "$(tput setaf 9)"
./webserv $'GET /index.html HPPT/1.1n\nHost: www.example.com'
read foo

echo "$(tput setaf 10)Prueba 15: Falta la versión HTTP ./webserv \"GET /index.html\nHost: www.example.com\""
echo "$(tput setaf 9)"
./webserv "GET /index.html
Host: www.example.com"
read foo

echo "$(tput setaf 10)Prueba 16: Falta el encabezado Host ./webserv \"GET /index.html HTTP/1.1\""
echo "$(tput setaf 9)"
./webserv "GET /index.html HTTP/1.1"
read foo

echo "$(tput setaf 10)Prueba 17: Se incluyen Content Length y Transfer-Encoding ./webserv \"POST /login HTTP/1.1\nHost: www.example.com\nContent-Type: application/json\nContent-Length: 40\nTransfer-Encoding: chunked\""
echo "$(tput setaf 9)"
./webserv "POST /login HTTP/1.1
Host: www.example.com
Content-Type: application/json
Content-Length: 40
Transfer-Encoding: chunked"
read foo

echo "$(tput setaf 10)Prueba 18: Petición con cuerpo pero sin Content-Length ni Transfer-Encoding: ./webserv POST /api/data HTTP/1.1\nHost: www.example.com\nContent-Type: application/json\n{json: data}\""
echo "$(tput setaf 9)"
./webserv "POST /api/data HTTP/1.1
Host: www.example.com
Content-Type: application/json
{json: data}"
read foo

echo "$(tput setaf 10)Prueba 19: Múltiples encabezados Host ./webserv \"GET /index.html HTTP/1.1\nHost: www.example.com\nHost: www.example2.com\""
echo "$(tput setaf 9)"
./webserv "GET /index.html HTTP/1.1
Host: www.example.com
Host: www.example2.com"
read foo

echo "$(tput setaf 10)Prueba 20: Petición con múltiples encabezados Connection: ./webserv GET /index.html HTTP/1.1\nHost: www.example.com\nConnection: keep-alive\nConnection: close\""
echo "$(tput setaf 9)"
./webserv "GET /index.html HTTP/1.1
Host: www.example.com
Connection: keep-alive
Connection: close"
read foo

echo "$(tput setaf 10)Prueba 21 (se usa Content-Length con el cuerpo vacío): ./webserv \"POST /login HTTP/1.1\nHost: www.example.com\nContent-Type: application/json\nContent-Length: 32\""
echo "$(tput setaf 9)"
./webserv "POST /login HTTP/1.1
Host: www.example.com
Content-Type: application/json
Content-Length: 32"
read foo

echo "$(tput setaf 10)Prueba 22: (usando Transfer-encoding con el cuerpo vacío) ./webserv \"POST /login HTTP/1.1\nHost: www.example.com\nContent-Type: application/json\nTransfer-Encoding: chunked\""
echo "$(tput setaf 9)"
./webserv "POST /login HTTP/1.1
Host: www.example.com
Content-Type: application/json
Transfer-Encoding: chunked"
read foo

echo "$(tput setaf 10)Prueba 23: Encabezado Content-Length con valor no numérico: POST /api/upload HTTP/1.1\nHost: www.example.com\nContent-Type: application/json\nContent-Length: abc\""
echo "$(tput setaf 9)"
./webserv "POST /api/upload HTTP/1.1
Host: www.example.com
Content-Type: application/json
Content-Length: abc"
read foo

echo "$(tput setaf 10)Prueba 24: Transfer-Encoding chunked sin cuerpo: ./webserv: POST /api/upload HTTP/1.1\nHost: www.example.com\nContent-Type: application/json\nTransfer-Encoding: chunked\""
echo "$(tput setaf 9)"
./webserv "POST /api/upload HTTP/1.1
Host: www.example.com
Content-Type: application/json
Transfer-Encoding: chunked"
read foo

