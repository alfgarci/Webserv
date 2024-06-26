# *************************************************************************** #
#                                                                             #
#                                                        :::      ::::::::    #
#   Makefile                                           :+:      :+:    :+:    #
#                                                    +:+ +:+         +:+      #
#   By: aoteo-be <aoteo-be@student.42.fr>          +#+  +:+       +#+         #
#                                                +#+#+#+#+#+   +#+            #
#   Created: 2024/02/29 12:58:12 by aoteo-be          #+#    #+#              #
#   Updated: 2024/03/01 15:44:35 by aoteo-be         ###   ########.fr        #
#                                                                             #
# *************************************************************************** #

# Compilador
CXX = clang++

# Opciones de compilación
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic

# Nombre del ejecutable final
NAME = webserv

# Archivos fuente
SRCS = main.cpp HTTPRequestParse.cpp

# Archivos objeto generados a partir de los archivos fuente
OBJS = ${SRCS:.cpp=.o}

# Regla por defecto para construir el ejecutable
all: ${NAME}

# Regla para construir el ejecutable
${NAME}: ${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} -o ${NAME}

# Regla para limpiar los archivos objeto y el ejecutable
clean:
	rm -f ${OBJS}

# Regla para limpiar archivos objeto, ejecutable y generados al compilar
fclean: clean
	rm -f ${NAME}

# Regla para limpiar y reconstruir el proyecto desde cero
re: fclean all

# Targets no asociados a ficheros
.PHONY: all clean fclean re