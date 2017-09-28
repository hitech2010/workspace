package main

import "fmt"

type MyStr string

func main() {
	var a MyStr = "test"
	var b string = string(a)
	fmt.Println(a, b)
}
