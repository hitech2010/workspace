package main

import (
	"fmt"
	"path"
)

func main() {
	s := path.Dir("/1/2/3/4.5xt")
	fmt.Println(s)
}
