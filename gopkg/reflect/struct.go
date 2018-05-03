package main

import (
	"fmt"
	"reflect"
)

func main() {
	i := 1
	//fmt.Printf("%s: %v\n", reflect.TypeOf(i), reflect.ValueOf(i))
	fmt.Println(reflect.TypeOf(i), reflect.ValueOf(i))
	fmt.Printf("%T %v\n", i, i)
	fmt.Println(reflect.ValueOf(i).Type())
}
