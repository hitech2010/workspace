package main

import "fmt"

func main() {
	x := false
	y := true
	switch {
	case x:
		fmt.Println(x, "1")
	case y:
		fmt.Println(y, "3")
	}
	fmt.Println("end line----")
}
