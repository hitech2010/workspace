package main

import (
	"fmt"
	"reflect"
)

type User struct {
	Name string
	Age  int
	Id   string
}

func (u *User) SayHello() {
	fmt.Printf("Name %s, Age %d, Id %s\n", u.Name, u.Age, u.Id)
}

func main() {
	u := &User{"bill", 18, "0001"}

	obj := reflect.ValueOf(u)
	e := obj.Elem()
	t := e.Type()
	for i := 0; i < e.NumField(); i++ {
		f := e.Field(i)
		fmt.Printf("%d. %s %s=%v\n", i, t.Field(i).Name, f.Type(), f.Interface())
	}

	u.SayHello()
	m := obj.MethodByName("SayHello")
	m.Call(nil)
}
