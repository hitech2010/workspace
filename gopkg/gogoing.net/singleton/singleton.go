package main

import (
	"fmt"
	"strconv"
)

type straps struct {
	StrapMap map[string]string
}

var st straps

func InitConfig() {
	st = straps{
		StrapMap: make(map[string]string),
	}
	for i := 1; i < 4; i++ {
		t := strconv.Itoa(i)
		st.StrapMap["k"+t] = "v" + t
	}
}
func Straps(key string) string {
	return st.StrapMap[key]
}

func main() {
	InitConfig()
	v1 := Straps("k1")
	v2 := Straps("k2")
	fmt.Println(v1, v2)
}
