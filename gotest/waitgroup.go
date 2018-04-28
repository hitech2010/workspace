package main

import (
	"fmt"
	"sync"
)

func main() {
	a := []int{1, 2, 3, 4, 5, 6, 7, 8}
	size := len(a)
	sum := 0

	workers := 4
	wg := sync.WaitGroup{}
	wg.Add(workers)

	subSum := make(chan int, workers)

	for i := 0; i < workers; i++ {
		go add(&wg, a[size/workers*i:size/workers*(i+1)], subSum)
	}

	for i := 0; i < workers; i++ {
		sum += <-subSum
	}
	wg.Wait()
	fmt.Println(sum)
}

func add(wg *sync.WaitGroup, a []int, sum chan int) {
	defer wg.Done()
	r := 0
	for i := 0; i < len(a); i++ {
		r += a[i]
	}
	sum <- r
}
