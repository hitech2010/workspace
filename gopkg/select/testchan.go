package main

import (
	"fmt"
)

func test(c chan int, n int) {
	for i := 0; i < n; i++ {
		c <- i + 1
		fmt.Println("c <- ", i+1)
	}
}

func main() {
	n := 2
	c := make(chan int, 0)
	go test(c, n)
	for i := 0; i < n; i++ {
		fmt.Printf(" %d <- c\n", <-c)
	}
}
