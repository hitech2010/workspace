package main

import (
	"fmt"
	"reflect"
)

type MyInt int

func main() {
	var mi MyInt = 1
	var i int = 2

	fmt.Println("Kind:", reflect.TypeOf(mi).Kind, reflect.TypeOf(i).Kind())
	fmt.Println("Type:", reflect.TypeOf(mi), reflect.TypeOf(i))
}
