cmake_minimum_required(VERSION 3.17)
project(minishell_o)

set(CMAKE_C_STANDARD 99)

##ADD environment variables
execute_process (
        COMMAND bash -c "env > local_env"
        )

AUX_SOURCE_DIRECTORY(src/execute/ EXECUTE_SRC)
AUX_SOURCE_DIRECTORY(src/execute/built_in BUILT_SRC)
set(SRC src/exit.c src/env.c src/init.c src/interact.c src/main.c src/readline.c
        src/pars/pars.c src/pars/lineptrjoin.c src/pars/post_obrabotka.c src/pars/substr_ignore.c
        src/pars/strreplace.c)

set(HDR_PATH ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/lib/libft/include)
set(SRC_PATH ${PROJECT_SOURCE_DIR}/src)
set(GCC_FLAGS "-Wall -Wextra -Werror -ltermcap")

add_executable( minishell
        ${SRC} ${BUILT_SRC} ${EXECUTE_SRC}
        )

##FIND TERMCAP
find_library(TERMCAP_LIBRARY termcap)
find_library(READLINE_LIBRARY readline)

##INCLUDE HDR DIR
target_include_directories( minishell PUBLIC
        ${HDR_PATH}
        )

##INCLUDE LIBRARIES
target_link_libraries(minishell
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libft/libft.a ${TERMCAP_LIBRARY} ${READLINE_LIBRARY}
        )
