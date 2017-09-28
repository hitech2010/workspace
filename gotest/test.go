package main

import "fmt"

func main() {
	var a string = "hello123"
	var b []byte = []byte(a)
	fmt.Printf("length: a[%d] b[%d]", len(a), len(b))
}
