#!/bin/bash

clear

echo "$(tput setaf 5)*********************************************************"
echo "*                  Pruebas parser                       *"
echo "*********************************************************"

echo "$(tput setaf 3)*****************************************************"
echo "*                  Entradas correctas               *"
echo "*****************************************************"

# Prueba 1
echo "$(tput setaf 10)Prueba 1 (GET formato correcto, puerto por defecto): ./webserv \"GET /index.html HTTP/1.1\r\nHost: www.example.com\r\nConnection: keep-alive\r\n\""
echo "$(tput setaf 9)"
./webserv $'GET /index.html HTTP/1.1\r\nHost: www.example.com\r\nConnection: keep-alive\r\n'
read foo

# Prueba 2
echo "$(tput setaf 10)Prueba 2 (GET formato correcto, puerto 433): ./webserv \"GET /index.html HTTP/1.1\r\nHost: www.example.com:433\r\nConnection: keep-alive\r\n\""
echo "$(tput setaf 9)"
./webserv $'GET /index.html HTTP/1.1\r\nHost: www.example.com:433\r\nConnection: keep-alive\r\n'
read foo


# Prueba 3
echo "$(tput setaf 10)Prueba 3 (espacio extra en Host, puerto por defecto): ./webserv \"GET /index.html HTTP/1.1\r\nHost:     www.example.com    \r\nConnection: keep-alive\r\n\""
echo "$(tput setaf 9)"
./webserv $'GET /index.html HTTP/1.1\r\nHost:     www.example.com    \r\nConnection: keep-alive\r\n'
read foo

# Prueba 4
echo "$(tput setaf 10)Prueba 4 (espacio extra en Host, puerto 433): ./webserv \"GET /index.html HTTP/1.1\r\nHost:     www.example.com:433    \r\nConnection: keep-alive\r\n\""
echo "$(tput setaf 9)"
./webserv $'GET /index.html HTTP/1.1\r\nHost:     www.example.com:433    \r\nConnection: keep-alive\r\n'
read foo

# Prueba 5
echo "$(tput setaf 10)Prueba 5 (mayúsculas y minúsculas en el nombre del campo connection, puerto por defecto): ./webserv \"GET /index.html HTTP/1.1\r\nHOST: www.example.com\r\ncOnNeCtIoN: keep-alive\r\n\""
echo "$(tput setaf 9)"
./webserv $'GET /index.html HTTP/1.1\r\nHOST: www.example.com\r\ncOnNeCtIoN: keep-alive\r\n'
read foo

# Prueba 6
echo "$(tput setaf 10)Prueba 6 (mayúsculas y minúsculas en el nombre del campo connection, puerto 433)<: ./webserv \"GET /index.html HTTP/1.1\r\nHOST: www.example.com:433\r\ncOnNeCtIoN: keep-alive\r\n\""
echo "$(tput setaf 9)"
./webserv $'GET /index.html HTTP/1.1\r\nHOST: www.example.com:433\r\ncOnNeCtIoN: keep-alive\r\n'
read foo

# Prueba 7
echo "$(tput setaf 10)Prueba 7 (DELETE formato correcto con puerto por defecto): ./webserv \"DELETE /file.txt HTTP/1.1\r\nHost: www.example.com\r\n\""
echo "$(tput setaf 9)"
./webserv $'DELETE /file.txt HTTP/1.1\r\nHost: www.example.com\r\n'
read foo

# Prueba 8
echo "$(tput setaf 10)Prueba 8 (DELETE formato correcto con puerto 433): ./webserv \"DELETE /file.txt HTTP/1.1\r\nHost: www.example.com:433\r\n\""
echo "$(tput setaf 9)"
./webserv $'DELETE /file.txt HTTP/1.1\r\nHost: www.example.com:433\r\n'
read foo

# Prueba 9
echo "$(tput setaf 10)Prueba 9 POST, con content-length, puerto por defecto): ./webserv \"POST /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nContent-Length: 32\r\n\r\n{\"username\": \"test\", \"password\": \"1234\"}\r\n\""
echo "$(tput setaf 9)"
./webserv $'POST /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nContent-Length: 40\r\n\r\n{\"username\": \"test\", \"password\": \"1234\"}\r\n'
read foo

# Prueba 10
echo "$(tput setaf 10)Prueba 10 POST, con content-length, puerto 433): ./webserv \"POST /login HTTP/1.1\r\nHost: www.example.com:433\r\nContent-Type: application/json\r\nContent-Length: 32\r\n\r\n{\"username\": \"test\", \"password\": \"1234\"}\r\n\""
echo "$(tput setaf 9)"
./webserv $'POST /login HTTP/1.1\r\nHost: www.example.com:433\r\nContent-Type: application/json\r\nContent-Length: 40\r\n\r\n{\"username\": \"test\", \"password\": \"1234\"}\r\n'
read foo

# Prueba 11
echo "$(tput setaf 10)Prueba 11 (POST con transfer-length y un único chunk, puerto por defecto): ./webserv \"POST /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n28\r\n{\"username\": \"test\", \"password\": \"1234\"}\r\n0\r\n\""
echo "$(tput setaf 9)"
./webserv $'POST /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n28\r\n{\"username\": \"test\", \"password\": \"1234\"}\r\n0\r\n'
read foo

# Prueba 12
echo "$(tput setaf 10)Prueba 12 (POST con transfer-length y un único chunk, puerto 433): ./webserv \"POST /login HTTP/1.1\r\nHost: www.example.com:433\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n28\r\n{\"username\": \"test\", \"password\": \"1234\"}\r\n0\r\n\""
echo "$(tput setaf 9)"
./webserv $'POST /login HTTP/1.1\r\nHost: www.example.com:433\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n28\r\n{\"username\": \"test\", \"password\": \"1234\"}\r\n0\r\n'
read foo

# Prueba 13
echo "$(tput setaf 10)Prueba 13 (POST con transfer-length, varios chunks y puerto por defecto): ./webserv \"POST /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n5\r\nHola \r\n7\r\nMundo! \r\n5\r\nCruelr\n0\r\n\""
echo "$(tput setaf 9)"
./webserv $'POST /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n5\r\nHola \r\n7\r\nMundo! \r\n5\r\nCruel\r\n0\r\n'
read foo

# Prueba 14
echo "$(tput setaf 10)Prueba 14 (POST con transfer-length, varios chunks y puerto 433): ./webserv \"POST /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n5\r\nHola \r\n7\r\nMundo! \r\n5\r\nCruelr\n0\r\n\""
echo "$(tput setaf 9)"
./webserv $'POST /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n5\r\nHola \r\n7\r\nMundo! \r\n5\r\nCruel\r\n0\r\n'
read foo

# Prueba 15
echo "$(tput setaf 10)Prueba 15 (se comprueba que con GET se ignoran los campos relativos al cuerpo de la petición): ./webserv \"GET /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nContent-Length: 32\r\n\r\n{\"username\": \"test\", \"password\": \"1234\"}\r\n\""
echo "$(tput setaf 9)"
./webserv $'GET /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nContent-Length: 40\r\n\r\n{\"username\": \"test\", \"password\": \"1234\"}\r\n'
read foo

# Prueba 16
echo "$(tput setaf 10)Prueba 16 (se comprueba que con DELETE se ignoran los campos relativos al cuerpo de la petición): ./webserv \"DELETE /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n28\r\n{\"username\": \"test\", \"password\": \"1234\"}\r\n0\r\n\""
echo "$(tput setaf 9)"
./webserv $'DELETE /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n28\r\n{\"username\": \"test\", \"password\": \"1234\"}\r\n0\r\n'
read foo

echo "$(tput setaf 3)*****************************************************"
echo "*            Errores en uso del programa            *"
echo "*****************************************************"

# Prueba 17
echo "$(tput setaf 10)Prueba 17 (Método erróneo): ./webserv \"PATCH /resource HTTP/1.1\r\nHost: www.example.com\r\n\""
echo "$(tput setaf 9)"
./webserv $'PATCH /resource HTTP/1.1\r\nHost: www.example.com\r\n'
read foo

# Prueba 18
echo "$(tput setaf 10)Prueba 18 (Versión HTTP no soportada (1)): ./webserv \"GET /index.html HTTP/1.0\r\nHost: www.example.com\r\nConnection: keep-alive\r\n\""
echo "$(tput setaf 9)"
./webserv $'GET /index.html HTTP/1.0\r\nHost: www.example.com\r\nConnection: keep-alive\r\n'
read foo

# Prueba 19
echo "$(tput setaf 10)Prueba 19 (Versión HTTP no soportada (2)): ./webserv \"GET /index.html HTTP/2.0\r\nHost: www.example.com\r\n\""
echo "$(tput setaf 9)"
./webserv $'GET /index.html HTTP/2.0\r\nHost: www.example.com\r\n'
read foo

# Prueba 20
echo "$(tput setaf 10)Prueba 20 (Método omitido): ./webserv \"/resource HTTP/1.1\r\nHost: www.example.com\r\n\""
echo "$(tput setaf 9)"
./webserv $'/resource HTTP/1.1\r\nHost: www.example.com\r\n'
read foo

# Prueba 21
echo "$(tput setaf 10)Prueba 21 (Error tipográfico en la versión HTTP): ./webserv \"GET /index.html HPPT/1.1\r\nHost: www.example.com\r\n\""
echo "$(tput setaf 9)"
./webserv $'GET /index.html HPPT/1.1\r\nHost: www.example.com\r\n'
read foo

# Prueba 22
echo "$(tput setaf 10)Prueba 22 (Falta la versión HTTP): ./webserv \"GET /index.html\r\nHost: www.example.com\r\n\""
echo "$(tput setaf 9)"
./webserv $'GET /index.html\r\nHost: www.example.com\r\n'
read foo

# Prueba 23
echo "$(tput setaf 10)Prueba 23 (Falta el encabezado Host): ./webserv \"GET /index.html HTTP/1.1\r\n\""
echo "$(tput setaf 9)"
./webserv $'GET /index.html HTTP/1.1\r\n'
read foo

# Prueba 24
echo "$(tput setaf 10)Prueba 24 (Se incluyen Content Length y Transfer-Encoding): ./webserv \"POST /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nContent-Length: 40\r\nTransfer-Encoding: chunked\r\n\""
echo "$(tput setaf 9)"
./webserv $'POST /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nContent-Length: 40\r\nTransfer-Encoding: chunked\r\n'
read foo

# Prueba 25
echo "$(tput setaf 10)Prueba 25 (Petición con cuerpo pero sin Content-Length ni Transfer-Encoding): ./webserv \"POST /api/data HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\n\r\n{json: data}\r\n\""
echo "$(tput setaf 9)"
./webserv $'POST /api/data HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\n\r\n{json: data}\r\n'
read foo

# Prueba 26
echo "$(tput setaf 10)Prueba 26 (Múltiples encabezados Host): ./webserv \"GET /index.html HTTP/1.1\r\nHost: www.example.com\r\nHost: www.example2.com\r\n\""
echo "$(tput setaf 9)"
./webserv $'GET /index.html HTTP/1.1\r\nHost: www.example.com\r\nHost: www.example2.com\r\n'
read foo

# Prueba 27
echo "$(tput setaf 10)Prueba 27 (Petición con múltiples encabezados Connection): ./webserv \"GET /index.html HTTP/1.1\r\nHost: www.example.com\r\nConnection: keep-alive\r\nConnection: close\r\n\""
echo "$(tput setaf 9)"
./webserv $'GET /index.html HTTP/1.1\r\nHost: www.example.com\r\nConnection: keep-alive\r\nConnection: close\r\n'
read foo

# Prueba 28
echo "$(tput setaf 10)Prueba 28 (se usa Content-Length con el cuerpo vacío): ./webserv \"POST /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nContent-Length: 32\r\n\""
echo "$(tput setaf 9)"
./webserv $'POST /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nContent-Length: 32\r\n'
read foo

# Prueba 29
echo "$(tput setaf 10)Prueba 29 (usando Transfer-encoding con el cuerpo vacío): ./webserv \"POST /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\""
echo "$(tput setaf 9)"
./webserv $'POST /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n'
read foo

# Prueba 30
echo "$(tput setaf 10)Prueba 30 (Encabezado Content-Length con valor no numérico): ./webserv \"POST /api/upload HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nContent-Length: abc\r\n\r\nCruel\r\n\""
echo "$(tput setaf 9)"
./webserv $'POST /api/upload HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nContent-Length: abc\r\n\r\nCruel\r\n'
read foo

# Prueba 31
echo "$(tput setaf 10)Prueba 31 (Transfer-Encoding chunked sin cuerpo): ./webserv \"POST /api/upload HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\""
echo "$(tput setaf 9)"
./webserv $'POST /api/upload HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n'
read foo

# Prueba 32
echo "$(tput setaf 10)Prueba 32 (Error en longitud (1)): ./webserv \"POST /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n1\r\nHola \r\n7\r\nMundo! \r\n5\r\nCruel\r\n0\r\n\""
echo "$(tput setaf 9)"
./webserv $'POST /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n1\r\nHola \r\n7\r\nMundo! \r\n5\r\nCruel\r\n0\r\n'
read foo

# Prueba 33
echo "$(tput setaf 10)Prueba 33 (Error en longitud (2)): ./webserv \"POST /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n5\r\nHola \r\n3\r\nMundo! \r\n5\r\nCruel\r\n0\r\n\""
echo "$(tput setaf 9)"
./webserv $'POST /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n5\r\nHola \r\n3\r\nMundo! \r\n5\r\nCruel\r\n0\r\n'
read foo

# Prueba 34
echo "$(tput setaf 10)Prueba 34 (Error en longitud (3)): ./webserv \"POST /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n5\r\nHola \r\n7\r\nMundo! \r\n4\r\nCruel\r\n0\r\n\""
echo "$(tput setaf 9)"
./webserv $'POST /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n5\r\nHola \r\n7\r\nMundo! \r\n3\r\nCruel\r\n0\r\n'
read foo

# Prueba 35
echo "$(tput setaf 10)Prueba 35 (Error en longitud (4)): ./webserv \"POST /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n10\r\nHola \r\n10\r\nMundo! \r\n5\r\nCruel\r\n0\r\n\""
echo "$(tput setaf 9)"
./webserv $'POST /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n10\r\nHola \r\n7\r\nMundo! \r\n5\r\nCruel\r\n0\r\n'
read foo

# Prueba 36
echo "$(tput setaf 10)Prueba 36: error en longitud (5)): ./webserv \"POST /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n5\r\nHola \r\n8\r\nMundo! \r\n5\r\nCruel\r\n0\r\n\""
echo "$(tput setaf 9)"
./webserv $'POST /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n5\r\nHola \r\n8\r\nMundo! \r\n5\r\nCruel\r\n0\r\n'
read foo

# Prueba 37
echo "$(tput setaf 10)Prueba 37: (Error en longitud (6)): ./webserv \"POST /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n5\r\nHola \r\n7\r\nMundo! \r\n23\r\nCruel\r\n0\r\n\""
echo "$(tput setaf 9)"
./webserv $'POST /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n5\r\nHola \r\n7\r\nMundo! \r\n23\r\nCruel\r\n0\r\n'
read foo

# Prueba 38
echo "$(tput setaf 10)Prueba 38: (Error en valor de transfer-encoding): ./webserv \"POST /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nTransfer-Encoding: chucky\r\n\r\n5\r\nHola \r\n7\r\nMundo! \r\n5\r\nCruel<\r\n0\r\n\""
echo "$(tput setaf 9)"
./webserv $'POST /login HTTP/1.1\r\nHost: www.example.com\r\nContent-Type: application/json\r\nTransfer-Encoding: chucky\r\n\r\n5\r\nHola \r\n7\r\nMundo! \r\n5\r\nCruel\r\n0\r\n'
read foo

# Prueba 39
echo "$(tput setaf 10)Prueba 39 (POST con transfer-length, varios chunks y puerto erróneo): ./webserv \"POST /login HTTP/1.1\r\nHost: www.example.com:abc\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n5\r\nHola \r\n7\r\nMundo! \r\n5\r\nCruelr\n0\r\n\""
echo "$(tput setaf 9)"
./webserv $'POST /login HTTP/1.1\r\nHost: www.example.com:abc\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n5\r\nHola \r\n7\r\nMundo! \r\n5\r\nCruel\r\n0\r\n'
read foo

# Prueba 40
echo "$(tput setaf 10)Prueba 40 (POST con transfer-length, varios chunks y puerto fuera de rango (1)): ./webserv \"POST /login HTTP/1.1\r\nHost: www.example.com:-45\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n5\r\nHola \r\n7\r\nMundo! \r\n5\r\nCruelr\n0\r\n\""
echo "$(tput setaf 9)"
./webserv $'POST /login HTTP/1.1\r\nHost: www.example.com:-45\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n5\r\nHola \r\n7\r\nMundo! \r\n5\r\nCruel\r\n0\r\n'
read foo

# Prueba 41
echo "$(tput setaf 10)Prueba 41 (POST con transfer-length, varios chunks y puerto fuera de rango(2)): ./webserv \"POST /login HTTP/1.1\r\nHost: www.example.com:70000000000\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n5\r\nHola \r\n7\r\nMundo! \r\n5\r\nCruelr\n0\r\n\""
echo "$(tput setaf 9)"
./webserv $'POST /login HTTP/1.1\r\nHost: www.example.com:70000000000\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n5\r\nHola \r\n7\r\nMundo! \r\n5\r\nCruel\r\n0\r\n'
read foo

# Prueba 42
echo "$(tput setaf 10)Prueba 42 (POST con transfer-length, varios chunks y puerto vacío): ./webserv \"POST /login HTTP/1.1\r\nHost: www.example.com:\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n5\r\nHola \r\n7\r\nMundo! \r\n5\r\nCruelr\n0\r\n\""
echo "$(tput setaf 9)"
./webserv $'POST /login HTTP/1.1\r\nHost: www.example.com:\r\nContent-Type: application/json\r\nTransfer-Encoding: chunked\r\n\r\n5\r\nHola \r\n7\r\nMundo! \r\n5\r\nCruel\r\n0\r\n'
read foo