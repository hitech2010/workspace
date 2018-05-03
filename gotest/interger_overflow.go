package main

import "fmt"

func main() {
	var a uint8 = 255
	var b uint8 = 2

	if b < a+uint8(1) {
		fmt.Println("overflow")
	}
	//fmt.Println(^uint8(0))
	fmt.Println(a + 1)
}
