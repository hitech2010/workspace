package main

import "fmt"

func out(str string){
	if str == "hello"{
		fmt.Println(str)
	}else{
		fmt.Println("wrong str, should be 'hello'")
	}
}

func main(){
	out(str:"hello")
	//out("hello")
}
