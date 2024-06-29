NAME = webserv

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c++98
RM = rm -f
DEFINES = -D RUN_TEST=0

RED =   \033[0;31m
GREEN = \033[0;32m
YELLOW =    \033[0;33m
BLUE  = \033[0;34m
MAGENTA =   \033[0;35m
CYAN =  \033[0;36m
LGRAY = \033[0;37m
DGRAY = \033[1;30m
LBLUE = \033[1;34m
LGREEN = \033[1;32m
LCYAN = \033[1;36m
LRED = \033[1;31m
LMAGENTA =\033[1;35m
LYELLOW = \033[1;33m
WHITE = \033[1;37m
RESET = \033[0m

MAIN = tester_main

#-------------------------------------------------------------------SERVER_INFO

SERVER_INFO_DIR = ServerInfo

SERVER_INFO_CLASS = ServerInfo
SERVER_INFO_SRCS_CLASS = $(addsuffix .cpp, $(SERVER_INFO_CLASS))


SERVER_INFO_CHECKER = \
check_indentation \
check_indentation_level \
check_for_indentation_token \
check_for_assignment_token \
check_for_keyword_in_line \
check_for_keyword \
check_syntax \
pass_tabulations \
pass_keyword_set_chars \

SERVER_INFO_CHECKER_DIR = checker/
SERVER_INFO_CHECKER_SRCS = \
$(addprefix $(SERVER_INFO_CHECKER_DIR), $(addsuffix .cpp, $(SERVER_INFO_CHECKER)))

SERVER_INFO_IS_FUNS = \
is_char_in_keyword_set \
is_keyword_in_set \

SERVER_INFO_IS_FUNS_DIR = is_funs/
SERVER_INFO_IS_FUNS_SRCS = \
$(addprefix $(SERVER_INFO_IS_FUNS_DIR), $(addsuffix .cpp, $(SERVER_INFO_IS_FUNS)))

SERVER_INFO_STORE = \
store_file \
store_server \
store_route \
initiate_route \
initiate_server \
get_line_content \


SERVER_INFO_STORE_DIR = store/
SERVER_INFO_STORE_SRCS = \
$(addprefix $(SERVER_INFO_STORE_DIR), $(addsuffix .cpp, $(SERVER_INFO_STORE)))


SERVER_INFO_SRCS = \
	$(SERVER_INFO_SRCS_CLASS) \
	$(SERVER_INFO_CHECKER_SRCS) \
	$(SERVER_INFO_IS_FUNS_SRCS) \
	$(SERVER_INFO_STORE_SRCS) \

#-------------------------------------------------------------------TESTER

TESTER_DIR = tester

TESTER_CLASS = tester
TESTER_SRCS_CLASS = $(addsuffix .cpp, $(TESTER_CLASS))

TESTER_CHECKER = \
test_check_indentation \
test_check_indentation_level \
test_check_for_indentation_token \
test_check_for_assignment_token \
test_check_for_keyword_in_line \
test_check_for_keyword \
test_check_syntax

TESTER_CHECKER_DIR = test_checker/
TESTER_CHECKER_SRCS = \
$(addprefix $(TESTER_CHECKER_DIR), $(addsuffix .cpp, $(TESTER_CHECKER)))

TESTER_IS_FUNS = \
test_is_char_in_keyword_set \
test_is_keyword_in_set \

TESTER_IS_FUNS_DIR = test_is_funs/
TESTER_IS_FUNS_SRCS = \
$(addprefix $(TESTER_IS_FUNS_DIR), $(addsuffix .cpp, $(TESTER_IS_FUNS)))

TESTER_SRCS = \
	$(TESTER_SRCS_CLASS) \
	$(TESTER_CHECKER_SRCS) \
	$(TESTER_IS_FUNS_SRCS) \

#-------------------------------------------------------------------HTTPREQUESTPARSE


HTTPREQUESTPARSE_DIR = HTTPRequestParse

HTTPREQUESTPARSE_CLASS = HTTPRequestParse
HTTPREQUESTPARSE_SRCS_CLASS = $(addsuffix .cpp, $(HTTPREQUESTPARSE_CLASS))

HTTPREQUESTPARSE_SRCS = \
	$(HTTPREQUESTPARSE_SRCS_CLASS) \


#-------------------------------------------------------------------HTTPREQUESTCREATOR


HTTPREQUESTCREATOR_DIR = HTTPRequestCreator

HTTPREQUESTCREATOR_CLASS = HTTPRequestCreator
HTTPREQUESTCREATOR_SRCS_CLASS = $(addsuffix .cpp, $(HTTPREQUESTCREATOR_CLASS))

HTTPREQUESTCREATOR_SRCS = \
	$(HTTPREQUESTCREATOR_SRCS_CLASS) \

#-------------------------------------------------------------------SRCS

SRCS =	\
		$(addprefix $(SERVER_INFO_DIR)/, $(SERVER_INFO_SRCS)) \
		$(addprefix $(HTTPREQUESTPARSE_DIR)/, $(HTTPREQUESTPARSE_SRCS)) \
		$(addprefix $(HTTPREQUESTCREATOR_DIR)/, $(HTTPREQUESTCREATOR_SRCS)) \
		$(addprefix $(TESTER_DIR)/, $(TESTER_SRCS)) \
		$(addsuffix .cpp, $(MAIN)) \

#-------------------------------------------------------------------RULES

OBJS =	${SRCS:.cpp=.o}

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(DEFINES) -o $(NAME) $(OBJS)
	@echo "$(GREEN)\n$(NAME) compile\n$(RESET)" 

all: $(NAME)

clean: $(CLASS)
	@$(RM) $(OBJS)
	@echo "$(YELLOW)\nFiles .o cleaned\n$(RESET)"

fclean: clean
	@$(RM) $(NAME) 
	@echo "$(RED)\n$(NAME) cleaned\n$(RESET)"

re: fclean all

.PHONY: all clean fclean re test

.SILENT:
