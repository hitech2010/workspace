package main

import (
	"fmt"
	"time"
)

func main() {
	ch := make(chan int)
	go sendData(ch)
	time.Sleep(1e9)
	go getData(ch)
}

func sendData(ch chan int) {
	ch <- 1
	ch <- 2
	ch <- 3
	ch <- 4
}

func getData(ch chan int) {
	var i int
	for {
		i = <-ch
		fmt.Printf("%d ", i)
	}
}
