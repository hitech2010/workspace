package main

import "fmt"

var cmd string

func main() {
	for {
		fmt.Println("input>>")
		fmt.Scan(&cmd)
		if cmd == "stop" || cmd == "exit" || cmd == "quit" {
			break
		}
		fmt.Println(cmd)
	}
}
