#include "mysql.h"
#include <iostream>
int main() {

	MYSQL* Mysql = mysql_init(0);

	// 证书自己去创建一下呗，可以放到 连接MysqlTest 目录里面名称和这个保持一致即可
	const char* clientKeyFile = "client-key.pem";
	const char* clientCertFile = "client-cert.pem";
	const char* clientCaFile = "ca.pem";//ca是可选的
	//mysql_ssl_set(my, clientKeyFile, clientCertFile,NULL,NULL,NULL);
	
	//mysql_options();
	// mysql_ssl_set 好像找不到这个方法了。
	// mysql include 和lib 都是x64的 32 的生成会失败的，如果需要自己去mysql官网下x86的头文件
	mysql_options(Mysql, mysql_option::MYSQL_OPT_SSL_KEY, clientKeyFile);
	mysql_options(Mysql, mysql_option::MYSQL_OPT_SSL_CERT, clientCertFile);
	//mysql_options(Mysql, mysql_option::MYSQL_OPT_SSL_CA, clientCaFile);
	

	if (mysql_real_connect(
		Mysql,
		"127.0.0.1",//host
		"root",// user
		"root", // passwd
		"djangoblog", // dbName
		3306,
		NULL,
		0)) {
		const char* cipher = mysql_get_ssl_cipher(Mysql);
		mysql_set_character_set(Mysql, "utf8");
		if (mysql_query(Mysql, "SELECT * FROM accounts_bloguser WHERE id = 1") != 0)
		{
			
			printf("Error connecting to MySQL server: %s\n", mysql_error(Mysql));
			return 1;
		}
		else {
			if (MYSQL_RES* Result = mysql_store_result(Mysql))
			{
				//GetResult(Result, Results);
				int NumRow = mysql_num_fields(Result);
				MYSQL_ROW SQLRow = mysql_fetch_row(Result);
				for (int i = 0; i < NumRow; ++i) {
					if (SQLRow[i] != NULL) {
						printf("%s\n", SQLRow[i]);//value
					}
				}

				mysql_free_result(Result);
			}
		}
		printf("Error connecting to MySQL server: %s\n", cipher);
	}
	else {
		printf("Error connecting to MySQL server: %s\n", mysql_error(Mysql));
	}
	return 0;
}