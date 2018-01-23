package plugin

import (
	"fmt"
)

type Animal struct {
	Name string
	Kind string
}

func (a *Animal) PrintName() {
	fmt.Println(a.Name)
}
func (a *Animal) PrintKind(t string) {
	fmt.Println(t)
}
