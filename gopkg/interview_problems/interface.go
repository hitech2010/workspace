package main

import "fmt"

type People interface {
	Speak(string) string
}
type Student struct{}

func (this *Student) Speak(think string) (talk string) {
	if think == "bitch" {
		talk = "you are a good boy"
	} else {
		talk = "hi"
	}
	return
}

func main() {
	var p People = Student{} //error, Student does not implement People. Speak method have a pointer receiver.
	//var p People = &Student{} //this is right
	think := "bitch"
	fmt.Println(p.Speak(think))
}
