# ShroomDB
 ____  _                               ____  ____     .-"""-.
/ ___|| |__  _ __ ___   ___  _ __ ___ |  _ \| __ )   /* * * *\
\___ \| '_ \| '__/ _ \ / _ \| '_ ` _ \| | | |  _ \  :_.-:`:-._;
 ___) | | | | | | (_) | (_) | | | | | | |_| | |_) |     (_)    
|____/|_| |_|_|  \___/ \___/|_| |_| |_|____/|____/      (_)
my own custom built database. Currently only an in memory, single table database.

## Table structure
| ID | Username | Email |
|---|---|---|

Table does not save any data. All data lives in memory until the program is terminated and subsequently that memory is freed and lost.

## Statements
Select all rows in table
```
select
```

Insert a row into a table
```
insert <id> <username> <email>
ex. insert 1 bob bob@example.com
```

### To EXIT:
```bash
.exit
```
