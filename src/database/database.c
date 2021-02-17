#include <stdlib.h>
#include <string.h>
#include <database/database.h>
#include <mysql/mysql.h>
#include <mysql/mysqld_error.h>
#include <mysql/plugin_auth_common.h>

static MYSQL connection;

int Database_init(const char *hostname, const char *username, const char *password, const char *database)
{
    MYSQL *ret = NULL;
    mysql_init(&connection);

    ret = mysql_real_connect(&connection, hostname, username, password, database, 0, NULL, 0);
    return ret == NULL ? EXIT_FAILURE : EXIT_SUCCESS;
}

bool Database_initAsync(const char *hostname, const char *username, const char *password, const char *database, int port, char *socket_name)
{
    bool is_connect = true;
    enum net_async_status status;
    while ((status = mysql_real_connect_nonblocking(&connection, hostname, username,
                                                    password, database, port,
                                                    socket_name, 0)) == NET_ASYNC_NOT_READY)
        ;

    if (status == NET_ASYNC_ERROR)
    { 
        is_connect = false;
    }

    return is_connect;
}

int Database_queryExec(char *(*query)(void *data), void *data)
{
    int ret = -1;
    if (!query)
    {
        return -1;
    }

    if (!data)
    {
        return -1;
    }

    ret = mysql_query(&connection, query(data));

    return !ret ? EXIT_FAILURE : EXIT_SUCCESS;
}

bool Database_queryExecAsync(char *(*query_async)(void *data), void *data)
{
    enum net_async_status status;
    if (!query_async)
    {
        false;
    }

    if (!data)
    {
        false;
    }

    char *stmt = query_async(data);

    status = mysql_real_query_nonblocking(&connection, stmt, (unsigned long)strlen(stmt));

    while (status == NET_ASYNC_NOT_READY)
    {
        status = mysql_real_query_nonblocking(&connection, stmt, (unsigned long)strlen(stmt));
    }

    return status == NET_ASYNC_ERROR ? false : true;
}

int Database_resultSet(void (*Database_get)(char **data, int columns, void *user_data), void *user_data)
{
    MYSQL_RES *result = mysql_store_result(&connection);
    if (result == NULL)
        return -1;

    int num_fields = mysql_num_fields(result);
    int num_rows = mysql_affected_rows(&connection);
    (void)num_rows;

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result)))
    {
        Database_get(row, num_fields, user_data);
    }

    mysql_free_result(result);
}

int Database_close(void)
{
    mysql_close(&connection);
    return 0;
}