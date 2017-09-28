package main

type Animal interface {
	spark(string)
}

type Dog struct{}
type Cat struct{}

func (this *Dog) spark(s string) {
	println(s)
}
func (this *Cat) spark(s string) {
	println(s)
}

//both ways are ok
func Spark(a Animal, s string) {
	switch a.(type) {
	case *Dog:
		a.(*Dog).spark("a dog:" + s)
	case *Cat:
		a.spark("a cat:" + s)
	}
}

func main() {
	var d Dog
	var c Cat
	Spark(&d, "wangwang")
	Spark(&c, "miaomiao")
}
