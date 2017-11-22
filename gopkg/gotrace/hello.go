package main

import (
	"os"
	"runtime/trace"
	"time"
)

func main() {
	trace.Start(os.Stderr)
	ch := make(chan int)
	go func() {
		time.Sleep(10 * time.Millisecond)
		ch <- 42
		time.Sleep(10 * time.Millisecond)
	}()

	<-ch
	trace.Stop()
}
