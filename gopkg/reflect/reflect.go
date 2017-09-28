package main

import (
	"fmt"
	"reflect"
)

type MyInt int

func hello() {
	fmt.Println("hello1 world")
}
func print(in string) (out string) {
	fmt.Println("input: ", in)
	return in
}

func main() {
	//int
	var i MyInt = 1
	fmt.Println("Kind: ", reflect.TypeOf(&i).Kind(), "Type: ", reflect.TypeOf(&i))

	//func
	fv := reflect.ValueOf(hello)
	fmt.Printf("fv Kind: %v, fv Type: %v\n", fv.Kind(), fv.Type())
	fv.Call(nil)

	fv2 := reflect.ValueOf(print)
	params := make([]reflect.Value, 1)
	params[0] = reflect.ValueOf("hahah")
	rs := fv2.Call(params)
	fmt.Println(rs[0].Interface().(string))
}
