package main

import "fmt"

func main() {
	test()
}

func test() {
	defer func() {
		fmt.Println("defer....")
	}()
	//panic("err")
	return
}
