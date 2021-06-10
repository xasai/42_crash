cmake_minimum_required(VERSION 3.17)
project(minishell_o)

set(CMAKE_C_STANDARD 99)

##ADD environment variables
execute_process (
        COMMAND bash -c "env > local_env"
        )

set(SRC src/exit.c src/term_init.c src/main.c src/interact.c src/readline/crash_readline.c src/pars/pars.c src/pars/lineptrjoin.c src/pars/post_obrabotka.c src/pars/substr_ignore.c)
set(HDR_PATH ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/lib/libft/include)
set(SRC_PATH ${PROJECT_SOURCE_DIR}/src)
set(GCC_FLAGS "-Wall -Wextra -Werror -ltermcap")

add_executable( minishell
        ${SRC}
        )

##FIND TERMCAP
find_library(TERMCAP_LIBRARY termcap)

##INCLUDE HDR DIR
target_include_directories( minishell PUBLIC
        ${HDR_PATH}
        )

##INCLUDE LIBRARIES
target_link_libraries(minishell
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libft/libft.a ${TERMCAP_LIBRARY}
        )
