#ifndef DATABASE_H_
#define DATABASE_H_

int Database_init(const char *hostname, const char *username, const char *password, const char *database);
int Database_queryExec(char *(*query)(void *data), void *data);
int Database_close(void);

#endif /* DATABASE_H_ */
