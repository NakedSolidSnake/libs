#ifndef DATABASE_H_
#define DATABASE_H_

/**
 * @brief 
 * 
 * @param hostname 
 * @param username 
 * @param password 
 * @param database 
 * @return int 
 */
int Database_init(const char *hostname, const char *username, const char *password, const char *database);

/**
 * @brief 
 * 
 * @param query 
 * @param data 
 * @return int 
 */
int Database_queryExec(char *(*query)(void *data), void *data);

/**
 * @brief 
 * 
 * @param Database_get 
 * @param user_data 
 * @return int 
 */
int Database_resultSet(void (*Database_get)(char **data, int columns, void *user_data), void *user_data);

/**
 * @brief 
 * 
 * @return int 
 */
int Database_close(void);

#endif /* DATABASE_H_ */
