package main

import "fmt"

func main() {
	var arr1 []string = []string{"a", "b"}
	var arr2 []string = []string{"c"}
	arr2 = append(arr2, arr1...)
	fmt.Println(arr2)
}
