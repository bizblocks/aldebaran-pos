#include <stdio.h>
#include <sqlite3.h>

static sqlite3 *db = 0;


static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  int i;
  for(i=0; i<argc; i++){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

int main(int argc, char **argv){
  char *zErrMsg = 0;
  int rc;

  if( argc!=3 ){
    fprintf(stderr, "Usage: %s DATABASE SQL-STATEMENT\n", argv[0]);
    exit(1);
  }
  rc = sqlite3_open(argv[1], &db);
  if( rc ){
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    exit(1);
  }
//  rc = sqlite3_exec(db, argv[2], callback, 0, &zErrMsg);
//  if( rc!=SQLITE_OK ){
//    fprintf(stderr, "SQL error: %s\n", zErrMsg);
//    sqlite3_free(zErrMsg);
//  }
	sqlite3_stmt * s1, * s2, * s3, * s4, *s5;
	rc = sqlite3_prepare_v2(db, "CREATE TABLE T (a,b,c)", -1, &s1, 0);
	rc = sqlite3_prepare_v2(db, "INSERT INTO T (a,b,c) VALUES(100, 200, 300)", -1, &s2, 0);	
	rc = sqlite3_prepare_v2(db, "SELECT * FROM T", -1, &s3, 0);
	rc = sqlite3_prepare_v2(db, "DELETE FROM T", -1, &s4, 0);				
	rc = sqlite3_prepare_v2(db, "INSERT INTO T (a,b,c) VALUES(200, 300, 400)", -1, &s5, 0);
	rc = sqlite3_step(s1);
	rc = sqlite3_step(s4);	
	rc = sqlite3_step(s2);
	rc = sqlite3_step(s5);	
	fprintf(stderr, "insert result is %i\n", rc);	
	rc = sqlite3_step(s3);	
	sqlite3_finalize(s1);
	sqlite3_finalize(s2);
	sqlite3_finalize(s3);
	sqlite3_finalize(s4);
	sqlite3_finalize(s5);	
	sqlite3_close(db);
	return 0;
}

