package main

import "fmt"

func main() {
	defer_call()
}

func defer_call() {
	defer func() {
		fmt.Println("first defer")
		if err := recover(); err != nil {
			fmt.Println("handle err:", err)
		}
	}()
	defer func() {
		fmt.Println("second defer")
	}()
	defer func() {
		fmt.Println("third defer")
	}()

	panic("trigger exception")

	fmt.Println("defer_call end")
}
