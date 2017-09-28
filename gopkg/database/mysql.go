package main

import (
	"database/sql"
	"fmt"
	"log"

	_ "github.com/go-sql-driver/mysql"
)

func main() {
	db, err := sql.Open("mysql", "root:@/hxydb")
	if err != nil {
		log.Fatal(err)
	}
	defer db.Close()

	if err = db.Ping(); err != nil {
		log.Fatal(err)
	}

	//execute
	stmtIns, err := db.Prepare("INSERT INTO squareNum VALUES(?, ?)")
	if err != nil {
		log.Fatal(err)
	}
	defer stmtIns.Close()

	stmtOut, err := db.Prepare("SELECT squreNum FROM squareNum WHERE number = ?")
	if err != nil {
		log.Fatal(err)
	}
	defer stmtOut.Close()

	for i := 0; i < 25; i++ {
		_, err = stmtIns.Exec(i, i*i)
		if err != nil {
			log.Fatal(err)
		}
	}

	var squareNum int
	err = stmtOut.QueryRow(13).Scan(&squareNum)
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println("The square number of 13 is: ", squareNum)

	err = stmtOut.QueryRow(1).Scan(&squareNum)
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println("The square number of 1 is: ", squareNum)
}
