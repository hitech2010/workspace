package main

import "fmt"

var a []int = []int{1, 2, 3}

func changeEle(a []int) {
	if len(a) <= 0 {
		return
	}
	a[0] = 3
}

func main() {
	fmt.Printf("%+v", a)
	changeEle(a)
	fmt.Printf("%+v", a)
}
