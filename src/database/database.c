#include <stdlib.h>
#include <database/database.h>
#include <mysql.h>

static MYSQL connection;

int Database_init(const char *hostname, const char *username, const char *password, const char *database)
{
    MYSQL *ret = NULL;
    mysql_init(&connection);

    ret = mysql_real_connect(&connection, hostname, username, password, database, 0, NULL, 0);
    return ret == NULL ? EXIT_FAILURE : EXIT_SUCCESS;
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
    return 0;
}

int Database_close(void)
{
    mysql_close(&connection);
    return 0;
}