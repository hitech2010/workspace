package main

import "fmt"

type People struct{}

func (this *People) ShowA() {
	fmt.Println("showA")
	this.ShowB()
}

func (this *People) ShowB() {
	fmt.Println("showB")
}

type Teacher struct {
	People
}

func (this *Teacher) ShowB() {
	fmt.Println("Teacher ShowB")
}

func main() {
	t := Teacher{}
	t.ShowA()
	t.ShowB()
}

/*
Output:
showA
showB
Teacher ShowB
*/
