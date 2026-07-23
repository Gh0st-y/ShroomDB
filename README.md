# ShroomDB
My own custom built database. Currently only an in memory, single table database.

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
