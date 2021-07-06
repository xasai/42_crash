#include "minishell.h"

#define SHOW_DEBUG 1

void    quot_flagchange(char *ch, bool *flag)
{
    *ch *= -1;
	*flag ^= true;
}

size_t get_envvalue_len(char *line, size_t envkey_len)
{
    size_t  envvalue_len;
    char    *envvalue;
	char    *envkey;

    envkey = ft_substr(line, 1, envkey_len - 1);
    if (envkey == NULL)
        exit_message("Memory allocation failure", SYS_ERROR);
    else if (*envkey == '?' || *envkey == 0)
    {
        free(envkey);
        return (1);
    }
    envvalue = crash_getenv(envkey);
    free(envkey);
    if (envvalue == NULL)
        return (0);
    envvalue_len = ft_strlen(envvalue);
    return (envvalue_len);
}

size_t get_strbufflen(char *str, size_t *str_len)
{
    size_t  tmp;
    size_t  envkey_len;
    size_t  envvalue_len;

    envkey_len = 0;
    envvalue_len = 0;
    while(str[*str_len])
    {
        if (str[*str_len] == '$')
        {
            str[*str_len] = DOLLAR_CH;
            tmp = get_envkey_len(&str[*str_len]);
            envkey_len += tmp;
            envvalue_len += get_envvalue_len(&str[*str_len], tmp);
            *str_len += tmp - 1;
        }
        ++*str_len;
    }
    return ((*str_len + envvalue_len) - envkey_len);
}

size_t get_argbuflen_withquot(char *line, size_t *arg_len)
{
    size_t  envvalue_len;
    size_t  envkey_len;
    size_t  tmp;
    bool    *qout_flag;

    qout_flag = (bool [2]){0};
    envvalue_len = 0;
    envkey_len = 0;
    while ((line[*arg_len] && (qout_flag[0] || qout_flag[1]))
           || !ft_strchr("<>| \t", line[*arg_len]))
    {
        if (line[*arg_len] == '\"' && !qout_flag[0])
            quot_flagchange(&line[*arg_len], &qout_flag[1]);
        else if (line[*arg_len] == '\'' && !qout_flag[1])
            quot_flagchange(&line[*arg_len], &qout_flag[0]);
        else if (line[*arg_len] == '$' && !qout_flag[0])
        {
            line[*arg_len] = DOLLAR_CH;
            tmp = get_envkey_len(&line[*arg_len]);
            envkey_len += tmp;
            envvalue_len += get_envvalue_len(&line[*arg_len], tmp);
            *arg_len += tmp - 1;
        }
        ++*arg_len;
    }
    return ((*arg_len + envvalue_len) - envkey_len );
}


size_t get_qoutcount(char *line, size_t arg_len)
{
    size_t count;

    count = 0;
    while(*line && arg_len--)
    {
        if(*line == DQUOT_CH || *line == QUOT_CH)
            ++count;
        ++line;
    }
    return (count);
}

static char *get_argbuf(char *line, size_t *arg_len)
{
    char    *buffer;
    size_t  qout_count;
    size_t  argbuflen_withqout;

    argbuflen_withqout = get_argbuflen_withquot(line, arg_len);
    qout_count = get_qoutcount(line, *arg_len);
    if (argbuflen_withqout == 0 && qout_count == 0)
        return (NULL);
    buffer = ft_calloc(argbuflen_withqout - qout_count + 1, sizeof(char));
    if (buffer == NULL)
        exit_message("Memory allocation failure", SYS_ERROR);
    return (buffer);
}

void    expand_env(char *buffer, char *line)
{
    size_t  envkey_len;
    char    *envvalue;
    char    *envkey;

    envkey_len = get_envkey_len(line);
    envkey = ft_substr(line, 1, envkey_len - 1);
    if(envkey == NULL)
        exit_message("Memory allocation failure", SYS_ERROR);
    else if (*envkey == '?')
    {
        envvalue = ft_itoa(g_sh->exit_status);
        if(envvalue == NULL)
            exit_message("Memory allocation failure", SYS_ERROR);
    }
    else if (*envkey == '\0')
        envvalue = "$";
    else
        envvalue = crash_getenv(envkey);
    if (envvalue != NULL)
        ft_memmove(buffer, envvalue, ft_strlen(envvalue));
    if (*envkey == '?')
        free(envvalue);
    free(envkey);
}

void    copy_arg(char *line, size_t arg_len, char *buffer)
{
    size_t  envkey_len;
    size_t  envvalue_len;
    size_t i;
    size_t j;

    i = 0;
    j = 0;
    while (j < arg_len)
    {
        if(line[j] == DOLLAR_CH)
        {
            envkey_len = get_envkey_len(&line[j]);
            envvalue_len = get_envvalue_len(&line[j], envkey_len);
            expand_env(&buffer[i], &line[j]);
            i += envvalue_len;
            j += envkey_len - 1;
        }
        else if(!ft_strchr((char [4]){DOLLAR_CH, QUOT_CH, DQUOT_CH, '\0'}, line[j]))
            buffer[i++] = line[j];
        ++j;
    }
}

char	*get_shellarg(char *line, size_t *arg_len)
{
    char    *buffer;

	buffer = get_argbuf(line, arg_len);
	copy_arg(line, *arg_len, buffer);
    return (buffer);
}

static void	line_pars(t_cmdlst *cmdl, char *line)
{
	size_t		arg_len;
	size_t		sep_len;
    char 		*arg;

	while(*line)
    {
	    arg_len = 0;
	    skip_spasech(&line);
	    arg = get_shellarg(line, &arg_len);
        line += arg_len;
        skip_spasech(&line);
	    sep_len = get_sepch(line, cmdl);
	    if (arg != NULL)
            cmdl->args = lineptrjoin(cmdl->args, arg);
        if (cmdl->sepch)
            cmdl = new_cmdlst(cmdl);
        line += sep_len;
	}
}


t_cmdlst *ft_line_analyz(char *line)
{
	t_cmdlst *cmdlst;
	
	if (ft_isempty_str(line))
		return (NULL);
	cmdlst = new_cmdlst(NULL);
	line_pars(cmdlst, line);
	return (cmdlst);
}
