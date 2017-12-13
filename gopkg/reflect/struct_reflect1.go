package main

import (
	"fmt"
	"reflect"
)

type User struct {
	Name string
	Age  int
	Id   int
}

func (u User) SayHello(name string) {
	fmt.Println("Hi ", name, "I'm ", u.Name)
}

//Field Method
func Info1(obj interface{}) {
	t := reflect.TypeOf(obj)
	v := reflect.ValueOf(obj)

	fmt.Println("Type:", t.Name())
	fmt.Println("Field:")
	for i := 0; i < t.NumField(); i++ {
		f := t.Field(i)
		val := v.Field(i).Interface()
		fmt.Printf("%6s: %v=%v\n", f.Name, f.Type, val)
	}

	for i := 0; i < t.NumMethod(); i++ {
		m := t.Method(i)
		fmt.Printf("%6s: %v\n", m.Name, m.Type)
	}
}

//Kind
func Info2(obj interface{}) {
	t := reflect.TypeOf(obj)
	if t.Kind() != reflect.Struct {
		fmt.Println("Not a struct")
		return
	}
	fmt.Println("obj is a struct")
}

//Nested Field
type Manager struct {
	User
	Title string
}

func Info3(obj interface{}) {
	t := reflect.TypeOf(obj)
	f1 := t.FieldByIndex([]int{0, 0}) //get Manager.User.Name
	f2 := t.FieldByIndex([]int{0, 1}) //get Manager.User.Age
	fmt.Printf("FieldByIndex_0_0: %s, FieldByIndex_0_1: %s\n", f1.Name, f2.Name)

	v := reflect.ValueOf(obj)
	fmt.Printf("%#v\n", v.Field(0))
}

//modify struct
func Set(obj interface{}) {
	v := reflect.ValueOf(obj)
	if v.Kind() == reflect.Ptr && !v.Elem().CanSet() {
		fmt.Println("Can't be modified")
		return
	}
	v = v.Elem()
	f := v.FieldByName("Name")
	if !f.IsValid() {
		fmt.Println("f is a Zero value")
	}
	if f.Kind() == reflect.String {
		f.SetString("warm3snow")
	}
}

//invoke method
func InvokeMethod(obj interface{}) {
	v := reflect.ValueOf(obj)
	m := v.MethodByName("SayHello")
	m.Call([]reflect.Value{reflect.ValueOf("hxy")})
}

func main() {
	u := User{"bill", 18, 0001}
	m := Manager{u, "CEO"}
	Info1(u)
	Info2(u)
	Info3(m)

	Set(&u)
	fmt.Printf("%#v\n", u)

	InvokeMethod(u)
}
