package main

import (
	"fmt"
	"runtime"
	"sync"
)

func main() {
	runtime.GOMAXPROCS(1) //only use one CPU core
	wg := sync.WaitGroup{}
	//	wg.Add(20)

	for i := 0; i < 10; i++ {
		wg.Add(1)
		go func() { //i is global
			defer wg.Done()
			fmt.Println("i: ", i)
		}()
	}

	for i := 0; i < 10; i++ {
		wg.Add(1)
		go func(i int) { //i is local for every goroutine
			defer wg.Done()
			fmt.Println("i: ", i)
		}(i)
	}

	wg.Wait()
}
