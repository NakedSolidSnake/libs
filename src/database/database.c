#include <stdlib.h>
#include <database/database.h>
#include <mysql/mysql.h>

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
  if(!query){
    return -1;
  }

  if(!data){
    return -1;
  }

  ret = mysql_query(&connection, query(data));
  
  return !ret ? EXIT_FAILURE : EXIT_SUCCESS;
}

int Database_close(void)
{
  mysql_close(&connection);
  return 0;
}