package main

import (
	"fmt"
	"reflect"
)

type MyStruct struct {
	A int
	B string
}

func (this *MyStruct) SetA(a int) {
	this.A = a
}
func (this *MyStruct) SetB(b string) {
	this.B = b
}
func (this *MyStruct) String() string {
	return fmt.Sprintf("MyStruct {A: %d, B: %s}\n", this.A, this.B)
}

func main() {
	m := MyStruct{1, "wow"}
	fmt.Println("MyStruct: ", reflect.ValueOf(m))

	fmt.Println(reflect.ValueOf(&m).MethodByName("String").Call(nil)[0])

	f := reflect.ValueOf(&m)
	s := reflect.ValueOf(&m).Elem()

	//invoke method to modify member variables
	params := make([]reflect.Value, 1)
	params[0] = reflect.ValueOf(2)
	f.MethodByName("SetA").Call(params)
	f.MethodByName("SetB").Call([]reflect.Value{reflect.ValueOf("wow2")})
	fmt.Println(f.MethodByName("String").Call(nil)[0])

	//modify member by Elem.Field.Setx()
	s.Field(0).SetInt(3)
	s.FieldByName("B").SetString("wow3")
	fmt.Println(f.MethodByName("String").Call(nil)[0])
}

/*note
1. Member and Method must be exported, if Method not, an error (panic: reflect: call of reflect.Value.Call on zero Value) will happen
2. Two ways to modify Member Variables:
   First, by reflect.Values(&Struct).MethodByName("MethodName").Call(Params)
   Second, by reflect.ValueOf(&Struct).FieldByName("MemberName").Setxxx("Value")
*/
