#include "mysql.h"
#include <iostream>
int main() {

	MYSQL* Mysql = mysql_init(0);

	// ֤���Լ�ȥ����һ���£����Էŵ� ����MysqlTest Ŀ¼�������ƺ��������һ�¼���
	const char* clientKeyFile = "client-key.pem";
	const char* clientCertFile = "client-cert.pem";
	const char* clientCaFile = "ca.pem";//ca�ǿ�ѡ��
	//mysql_ssl_set(my, clientKeyFile, clientCertFile,NULL,NULL,NULL);
	
	//mysql_options();
	// mysql_ssl_set �����Ҳ�����������ˡ�
	// mysql include ��lib ����x64�� 32 �����ɻ�ʧ�ܵģ������Ҫ�Լ�ȥmysql������x86��ͷ�ļ�
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