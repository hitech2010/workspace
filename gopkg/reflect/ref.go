package main

import (
	"fmt"
	"reflect"
)

type A struct {
	Obj *B
}

func (a *A) SayHello() {
	fmt.Println("A SayHello")
}

type B struct {
	Name string
}

func (b *B) SayHello() {
	fmt.Println("B SayHello")
}

func main() {
	a := A{
		Obj: &B{
			Name: "B",
		},
	}

	//reflect
	/*
		v := reflect.ValueOf(&a).Elem()
		v.MethodByName("SayHello").Call(nil)

		vv := reflect.ValueOf(*a)
		obj := vv.FieldByName("obj")
		//obj.MethodByName("SayHello").Call(nil)
		bv := reflect.ValueOf(obj).Elem()
		bv.MethodByName("SayHello").Call(nil)
		//fmt.Println(reflect.TypeOf(obj))
	*/

	/*
		t := reflect.TypeOf(a)
		fmt.Println("Type:", t.Name())

		v := reflect.ValueOf(a)
		fmt.Println("Fields:")
		for i := 0; i < v.NumField(); i++ {
			f := t.Field(i)
			val := v.Field(i).Interface() //Get value by interface()
			fmt.Printf("%s:%v=%v\n", f.Name, f.Type, val)
		}

		objVal := v.FieldByName("obj").Interface()
		fmt.Println(objVal)

		for i := 0; i < t.NumMethod(); i++ {
			m := t.Method(i)
			fmt.Printf("%s:%v\n", m.Name, m.Type)
		}
	*/

	t := reflect.TypeOf(a)
	fmt.Printf("%#v\n", t.Field(0))
	fmt.Printf("%#v\n", t.FieldByIndex([]int{0}))
	fmt.Printf("%#v\n", t.FieldByIndex([]int{0, 0})) //nested reflect

	v := reflect.ValueOf(&a)
	//fmt.Println(v.MethodByName("SayHello"))
	v.MethodByName("SayHello").Call(nil)

	v = reflect.ValueOf(a)
	val := v.FieldByName("obj").Interface()
	fmt.Println(val)

}
