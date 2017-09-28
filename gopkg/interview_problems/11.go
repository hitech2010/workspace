package main

import "fmt"

type People interface {
	Show()
}

type Student struct {
}

func (this *Student) Show() {
}

func live() People {
	var s *Student
	fmt.Println(s)
	return s
}

func main() {
	tmp := live()
	fmt.Println(tmp)
	fmt.Println(nil)
	if tmp == nil {
		fmt.Println("AAAA")
	} else {
		fmt.Println("BBBB")
	}
}
