# pg-text-utils
Library for PostgreSQL with additional user-defined C text functions

## Functions
* common_prefix(str1 text, str2 text). Returns a common start of strings. `select common_prefix('123', '124');` returns `12`

* common_end(str1 text, str2 text). Returns a common ending of strings. `select common_end('123456', '0456');` returns `456`

* diff_index(str1 text, str2 text). Returns the index of the first different characters. `select count_matches('223', '224');` returns `2`

* count_matches(str1 text, str2 text). Returns the number of occurrences of the str2 in the str1. `select count_matches('24as24sas24', '24');` returns `3`

## Requirements
You need install `gcc` and `postgresql-server-dev`.  The version of `postgresql-server-dev` must match the version of PostgreSQL. For example, when installing on Ubuntu with PostgreSQL 9.6, run commands:
```
sudo apt install postgresql-server-dev-9.6
sudo apt install gcc
```
## How to install
*Installation on a local server*
Go to the project directory and run:
```
make clean all
sudo make install
```
After this,  in the catalog `/usr/lib/postgresql/X.Y/lib` should appear library `text_utils.so`.
Then execute command
```
psql -U PG_USER -f text_utils.sql YOUR_DB_NAME
```
*Installation on a remote server*
Go to the project directory and run:
```
make clean all
```
After this,  copy `text_utils.so` to the directory PG_DIR/lib on remote server.
Then execute command
```
psql -H REMOTE_HOST -U PG_USER -f text_utils.sql YOUR_DB_NAME
```