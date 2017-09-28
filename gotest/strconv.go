package main

import (
	"fmt"
	"strconv"
)

func main() {
	a := "123"
	b := "13.14"

	aNum, _ := strconv.ParseFloat(a, 64)
	bNum, _ := strconv.ParseFloat(b, 64)

	fmt.Println(aNum, bNum)
}
